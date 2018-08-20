#include <Properties>
#include <Tools>
#include <sstream>

using namespace hslib;

/**
 * Set a new property or update an existing property.
 * \param key Property key
 * \param value Property value
 * \return Reference to this object
 */
Properties& Properties::setProperty(const std::string& key, const std::string& value)
{
    propertyMap[key] = value;
    return *this;
}

/**
 * Return an existing property or the default value if the 
 * property key does not exist.
 * \param key Property key
 * \param defaultValue Default property value if requested key does not exist
 * \return Property value or the defaultValue.
 */
const std::string Properties::getProperty(const std::string& key, const std::string& defaultValue) const
{
    std::string result = defaultValue;
    if (propertyMap.find(key) != propertyMap.end())
        result = propertyMap.at(key);
    return result;
}

/**
 * Return the set of keys used in this property container.
 * \return Set of keys
 */
const std::set<std::string> Properties::keys() const
{
    std::set<std::string> result;
    for (auto ix = propertyMap.cbegin(); ix != propertyMap.cend(); ++ix)
    {
        result.insert(ix->first);
    }
    return result;
}

/**
 * Load the properties collection by parsing the input string.
 * \param text Properties as text
 * \return Reference to this object
 */
Properties& Properties::load(const std::string& text)
{
    std::stringstream ss(text);
    std::string s;
    while (std::getline(ss, s)) {
        std::string line = trim_copy(s);
        // skip blank lines and comments
        if (line.empty()) {
            continue;
        }
        if (line.at(0) == '!' || line.at(0) == '#') {
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
        setProperty(key, value);
    }
    return *this;
}

/**
 * Load the properties collection from the given input stream.
 * \param in Input stream
 * \return Reference to this object
 */
Properties& Properties::load(std::istream& in)
{
    std::istreambuf_iterator<char> eos;
    std::string text(std::istreambuf_iterator<char>(in), eos);
    return load(text);
}

Properties& Properties::store(std::string& target)
{
    std::stringstream ss;
    for (auto key : keys()) {
        ss << key << "=" << getProperty(key) << std::endl;
    }
    target = ss.str();
    return *this;
}

Properties& Properties::store(std::ostream& out)
{
    std::string temp;
    store(temp);
    out.write(temp.data(), temp.length());
    return *this;
}

