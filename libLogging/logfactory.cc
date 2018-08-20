#include <LogFactory>
#include <Properties>
#include <Tools>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace hslib;

LogFactory factory;

LogFactory::LogFactory() : appenders(), loggers()
{
    loadConfiguration();
}

LogFactory::~LogFactory()
{
    for (auto ix = loggers.begin(); ix != loggers.end(); ++ix) {
        Logger* logger = ix->second;
        delete logger;
    }
    for (auto ix = appenders.begin(); ix != appenders.end(); ++ix) {
        Appender* appender = ix->second;
        delete appender;
    }
    loggers.clear();
    appenders.clear();
}

void LogFactory::loadLoggers(const Properties& props)
{
    // find all of the loggers and put them in a sorted set.
    const std::set<std::string> keys = props.keys();
    for (auto ix = keys.cbegin(); ix != keys.cend(); ++ix) {
        const std::string key = *ix;
        if (startsWith(key, "rootLogger") || startsWith(key, "logger.")) {
            const std::vector<std::string> parts = split(key, '.');
            const std::string loggerName = (parts.size() == 2 ? parts[1] : "rootLogger");
            Logger* logger = new Logger(loggerName);

            const std::vector<std::string> elems = split(props.getProperty(key), ',');
            // first element is the minimum severity level
            logger->setMinimumLevel(Level::getLevel(trim_copy(elems[0])));
            // every element after the first is an appender
            for (size_t n = 1; n < elems.size(); n++) {
                const std::string appenderName = trim_copy(elems[n]);
                if (appenders.find(appenderName) != appenders.end())
                    logger->addAppender(appenders.find(appenderName)->second);
            }

            loggers[loggerName] = logger;
        }
    }
}

void LogFactory::loadAppenders(const Properties& props)
{
    // find all of the appenders and put them in a sorted set.
    // This will ensure that they are all grouped together.
    std::set<std::string> sorted;
    const std::set<std::string> keys = props.keys();
    for (auto ix = keys.cbegin(); ix != keys.cend(); ++ix) {
        const std::string key = *ix;
        if (startsWith(key, "appender.")) {
            sorted.insert(key);
        }
    }
    // sorted now contains all of the appender lines...
    Appender* appender = nullptr;
    std::string appenderType = "";
    std::string appenderName = "";
    for (auto ix = sorted.cbegin(); ix != sorted.cend(); ++ix)
    {
        const std::string key = *ix;
        const std::string value = props.getProperty(key);
        const std::vector<std::string> elems = split(key, '.');

        const size_t elemCount = elems.size();

        switch (elemCount) {
            case 2: // appender name and type format: appender.{name}={appender type}
                // Add the existing appender to the collection
                if (appender != nullptr) {
                    appenders[appenderName] = appender;
                }

                appenderType = value;
                appenderName = elems[1];
                if (appenderType == "ConsoleAppender")
                    appender = new ConsoleAppender();
                else if (appenderType == "FileAppender")
                    appender = new FileAppender;
                break;

            case 3: // 
                if (appender == nullptr) break;

                if (elems[2] == "Threshold") {
                    Level threshold = Level::getLevel(value);
                    appender->setMinimumLevel(threshold);
                }
                //else if (elems[2] == "layout")
                else if (elems[2] == "File") {
                    if (appenderType == "FileAppender") {
                        ((FileAppender*)appender)->setFilename(value);
                    }
                }
                else if (elems[2] == "Append") {
                    if (appenderType == "FileAppender") {
                        ((FileAppender*)appender)->setAppend(value[0] == 'T' || value[0] == 't');
                    }
                }
                break;
            case 4: // currently only layout.ConversionPattern
                if (elems[3] == "ConversionPattern")
                    appender->setLayout(PatternLayout(value));
                break;
            default:
                break;
        }

    }

    if (appender != nullptr && appenderName.empty() == false && appenders.find(appenderName) == appenders.end()) {
        appenders[appenderName] = appender;
    }
}

void LogFactory::loadConfiguration()
{
    std::string configFilename(getenv(LOGGER_CONFIG) == NULL ? "" : getenv(LOGGER_CONFIG));
    if (configFilename.empty()) {
        if (fileExists(LOGGER_CONFIG_PROPERTIES))
            configFilename = LOGGER_CONFIG_PROPERTIES;
        else if (fileExists(LOGGER_CONFIG_XML))
            configFilename = LOGGER_CONFIG_XML;
    }

    if (!configFilename.empty() && fileExists(configFilename)) {
        Properties props;

        std::ifstream in(configFilename);
        std::string text;
        in.seekg(0, std::ios::end);
        text.reserve(in.tellg());
        in.seekg(0, std::ios::beg);
        text.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

        std::stringstream ss(text);
        std::string line;
        if (std::getline(ss, line)) {
            if (startsWith(trim_copy(line), "<?xml")) {
                // load xml(text)
            }
            else {
                props.load(text);
            }
        }

        loadAppenders(props);
        loadLoggers(props);
    }

    // ensure that there is alwasya a rootLogger
    if (loggers.find("rootLogger") == loggers.end()) {
        Logger* logger = new Logger("rootLogger");
        logger->setMinimumLevel(Level::INFO);
        Appender* console = new ConsoleAppender(PatternLayout("%d{ABSOLUTE} [%5p] %m%n"));
        logger->addAppender(console);
        appenders["rootConsole"] = console;
        loggers["rootLogger"] = logger;
    }
}

Logger& LogFactory::getLogger(const std::string& name)
{
    Logger* result = loggers.find("rootLogger")->second;
    if (loggers.find(name) != loggers.end())
        result = loggers.find(name)->second;
    return *result;
}

LogFactory& LogFactory::getInstance()
{
    return factory;
}
