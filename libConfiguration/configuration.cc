#include <Configuration>
#include <Tools>
#include <iostream>
#include <sstream>

using namespace hslib;

const std::string Configuration::DEFAULT_SECTION = "__default__";

/**
 * Copy constructor
 * \param copy Configurtion to copy.
 */
Configuration::Configuration(const Configuration& copy) : data()
{
    data.insert(copy.data.cbegin(), copy.data.cend());
}

Configuration& Configuration::operator=(const Configuration& copy)
{
    data.clear();
    data.insert(copy.data.cbegin(), copy.data.cend());
    return *this;
}

/**
 * Determine if the current container has a section with the given name.
 * \param section Name of section
 * \return True if the container has a section with the given name.
 */
bool Configuration::hasSection(const std::string& section) const
{
    return data.find(section) != data.end();
}

/**
 * Return a collection of section names. The section names will only
 * include the default section IF default section data has been
 * added to the data container.
 * \return Set of section names (including default)
 */
const std::set<std::string> Configuration::sections() const
{
    std::set<std::string> results;
    for (auto ix = data.cbegin(); ix != data.cend(); ++ix)
        results.insert(ix->first);
    return results;
}

/**
 * Set the property for the specified key in the given section. If
 * the section does not exist then it is created. If the property already
 * exists then its value will be overwritten.
 * \param section Name of section
 * \param key Property key
 * \param value Property value
 * \return Reference to this object
 */
Configuration& Configuration::setProperty(const std::string& section,
        const std::string& key,
        const std::string& value)
{
    auto ix = data.find(section);
    if (ix != data.cend())
        ix->second.setProperty(key, value);
    else {
        Properties props;
        props.setProperty(key, value);
        data[section] = props;
    }
    return *this;
}

/**
 * Return the property value with the given key in the specified section.
 * If the section does not exist or the property does not exist then the
 * defaultValue will be returned.
 * \param section Name of section
 * \param key Property key
 * \param defaultValue Default property value
 * \return Property value or default if property does not exist.
 */
std::string Configuration::getProperty(const std::string& section,
        const std::string& key,
        const std::string& defaultValue)
{
    std::string result = defaultValue;
    auto ix = data.find(section);
    if (ix != data.cend())
        result = ix->second.getProperty(key, defaultValue);
    return result;
}

/**
 * Return the Properties object from the given section. If the
 * section does not exist in the container then an empty
 * Properties object will be returned.
 * \param section Name of section
 * \return Proeprties for the named section or an empty object
 */
const Properties Configuration::getProperties(const std::string& section) const
{
    Properties props;
    if (hasSection(section))
        props = data.find(section)->second;
    return props;
}

/**
 * Set the Properties object at the given section with a copy of
 * the given properties. If the section already exists then the
 * properties at that section will be replaced with the given properties.
 * \param section Section name
 * \param props Properties
 * \return Reference to this object.
 */
Configuration& Configuration::setProperties(const std::string& section,
        const Properties& props)
{
    if (hasSection(section))
        data.at(section) = props;
    else
        data[section] = props;
    return *this;
}

/**
 * Load the configuration contents from the given string data.
 * \param data String data
 * \return Reference to this object
 */
Configuration& Configuration::load(const std::string& data)
{
    std::stringstream ss(data);
    std::string s;
    std::string section = DEFAULT_SECTION;
    while (std::getline(ss, s)) {
        std::string line = trim_copy(s);
        // skip blank lines and comments
        if (line.empty()) {
            continue;
        }
        if (line.at(0) == '!' || line.at(0) == '#') {
            continue;
        }
        // sections begin with the bracket character '['
        if (line.at(0) == '[') {
            section = line.substr(1, line.find_last_of(']') - 1);
            continue;
        }

        std::string key, value;
        size_t eqx = line.find('=');
        size_t cox = line.find(':');
        size_t ix = (eqx == std::string::npos ? cox : eqx);
        // is the delimiter an equal sign or a colon?
        if (eqx != std::string::npos && cox != std::string::npos)
            ix = std::min(eqx, cox);
        // extract the key and value
        key = trim_copy(line.substr(0, ix));
        value = trim_copy(line.substr(ix + 1));
        // special case: does value terminate with a \?
        if (value.at(value.length() - 1) == '\\') {
            std::string tmpValue;
            while (value.at(value.length() - 1) == '\\') {
                value = trim_copy(value.substr(0, value.length() - 1));
                tmpValue.append(value);

                if (std::getline(ss, s))
                    value = trim_copy(s);
                else
                    value = "";
            }
            tmpValue.append(value);
            value = tmpValue;
        }
        // set the property
        setProperty(section, key, value);
    }
    return *this;
}

/**
 * Load the configuration contents from the given stream.
 * \param in Input stream
 * \return Reference to this object
 */
Configuration& Configuration::load(std::istream& in)
{
    std::istreambuf_iterator<char> eos;
    std::string text(std::istreambuf_iterator<char>(in), eos);
    return load(text);
}

/**
 * Store the current container data into the given string.
 * \param data String that will receive the formatted contents of this container.
 * \return Reference to this object.
 */
Configuration& Configuration::store(std::string& data)
{
    std::stringstream ss;

    // Default section is always the first one to be written
    if (hasSection(DEFAULT_SECTION)) {
        std::string defaultSection;
        // dump DEFAULT section property data
        Properties props(getProperties(DEFAULT_SECTION));
        props.store(defaultSection);
        ss << defaultSection;
    }

    std::set<std::string> sec = sections();
    for (auto ix = sec.cbegin(); ix != sec.cend(); ++ix) {
        if (*ix == DEFAULT_SECTION) continue;
        if (sec.size() > 1) ss << std::endl;
        ss << "[" << *ix << "]" << std::endl;
        // dump section property data
        std::string sectionData;
        Properties props(getProperties(*ix));
        props.store(sectionData);
        ss << sectionData;
    }

    data = ss.str();
    return *this;
}

/**
 * Store the current container data into the given output stream.
 * \param out Output stream
 * \return Reference to this object
 */
Configuration& Configuration::store(std::ostream& out)
{
    std::string temp;
    store(temp);
    out << temp;
    return *this;
}

