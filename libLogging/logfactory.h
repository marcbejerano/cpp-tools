#ifndef _HSLIB_LOGFACTORY_H_INCLUDED_
#define _HSLIB_LOGFACTORY_H_INCLUDED_

#include <map>
#include <string>
#include <Appender>
#include <Logger>
#include <Properties>

namespace hslib {

    //! Logger factory
    /**
     * Logger factory. This class exists as a singleton that will create all
     * loggers, appenders, and configurations following a standards-based
     * paradigm. The logger factory is configured by the use of a file in
     * either the properties (name/value) format or a simple XML document.
     * <p><h4>logger-config.propertis</h4><pre>
     * # Copied from the Apache axis log4j properties file (and slightly edited)
     * # Set root category priority to INFO and its only appender to CONSOLE.
     * rootLogger=INFO, CONSOLE
     * 
     * # Set the enterprise logger category to FATAL and its only appender to CONSOLE.
     * logger.LogFactoryTest=INFO, LOGFILE
     * 
     * # CONSOLE is set to be a ConsoleAppender using a PatternLayout.
     * appender.CONSOLE=ConsoleAppender
     * appender.CONSOLE.Threshold=INFO
     * appender.CONSOLE.layout=PatternLayout
     * appender.CONSOLE.layout.ConversionPattern=%d{ABSOLUTE} [%5p] %m%n
     * 
     * # LOGFILE is set to be a File appender using a PatternLayout.
     * appender.LOGFILE=FileAppender
     * appender.LOGFILE.File=LogFactoryTest.log
     * appender.LOGFILE.Append=true
     * appender.LOGFILE.Threshold=INFO
     * appender.LOGFILE.layout=PatternLayout
     * appender.LOGFILE.layout.ConversionPattern=%d{ISO8601} [%5p] %F(%L) - %m%n
     * </pre></p>
     * <p><h4>logger-properties.xml</h4><pre class="code">
     * &lt;?xml version="1.0"?&gt;
     * &lt;logfactory&gt;
     *     &lt;rootLogger threshold="INFO"&gt;
     *         &lt;appender ref="CONSOLE"/&gt;
     *     &lt;/rootLogger&gt;
     * 
     *     &lt;loggers&gt;
     *         &lt;logger threshold="INFO"&gt;
     *             &lt;appender ref="CONSOLE"/&gt;
     *             &lt;appender ref="LOGFILE"/&gt;
     *         &lt;/logger&gt;
     *     &lt;/loggers&gt;
     * 
     *     &lt;appenders&gt;
     *         &lt;appender name="CONSOLE" type="ConsoleAppender"&gt;
     *             &lt;layout&gt;
     *                 &lt;patternlayout pattern="%d{ABSOLUTE} [%5p] %m%n"/&gt;
     *             &lt;/layout&gt;
     *         &lt;/appender&gt;
     * 
     *         &lt;appender name="LOGFILE" type="FileAppender"&gt;
     *             &lt;file&gt;LogFactoryTest.log&lt;/file&gt;
     *             &lt;append&gt;true&lt;/append&gt;
     *             &lt;layout&gt;
     *                 &lt;patternlayout pattern="%d{ISO8601} [%5p] %F(%L) - %m%n"/&gt;
     *             &lt;/layout&gt;
     *         &lt;/appender&gt;
     *     &lt;/appenders&gt;
     * &lt;/logfactory&gt;
     * </pre></p>
     * <p>Both of the above files represent the exact same configuration.</p>
     */
    class LogFactory
    {
        private:
            std::map<std::string, Appender*> appenders;
            std::map<std::string, Logger*> loggers;

            void loadLoggers(const Properties& props);
            void loadAppenders(const Properties& props);
            void loadConfiguration();
        public:
            /** LogFactory configuration file environment variable */
            static constexpr char const* LOGGER_CONFIG = "LOGGER_CONFIG";
            /** LogFactory default properties configuration file */
            static constexpr char const* LOGGER_CONFIG_PROPERTIES = "logger-config.properties";
            /** LogFactory default XML configuration file */
            static constexpr char const* LOGGER_CONFIG_XML = "logger-config.xml";

            /**
             * Default constructor
             */
            LogFactory();
            /**
             * Destructor. Upon destruction, this class will deallocate all
             * of the loggers and appenders that were dynamically created
             * during the load configuration phase.
             */
            ~LogFactory();
            /**
             * Locate and retrieve the named logger. If the named logger
             * cannot be located then the root logger will be returned.
             * \param name Name of the logger
             * \return Logger with the specified name or the root logger.
             */
            Logger& getLogger(const std::string& name);

            /**
             * Return the LogFactory instance that manages all of the
             * loggers and appenders.
             * \return Reference to the LogFactory instance.
             */
            static LogFactory& getInstance();
    };

} // hslib

#endif // _HSLIB_LOGFACTORY_H_INCLUDED_
