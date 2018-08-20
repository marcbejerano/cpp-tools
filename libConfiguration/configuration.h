#ifndef _HSLIB_CONFIGURATION_H_INCLUDED_
#define _HSLIB_CONFIGURATION_H_INCLUDED_

#include <Properties>
#include <map>
#include <set>
#include <string>

namespace hslib {

    //! INI-style configuration class
    /**
     * Configuration object that handles multi-property sections
     * in a document. Each section is delimited by a bracketed
     * name or title followed by name/value pairs in the format
     * recognized by the Properties class.
     */
    class Configuration
    {
        private:
            /** Configuration data */
            std::map<std::string, Properties> data;
        public:
            /** Default section title */
            static const std::string DEFAULT_SECTION;
            /**
             * Default constructor
             */
            Configuration() : data() { }
            /**
             * Copy constructor.
             * \param copy Configuration object to copy.
             */
            Configuration(const Configuration& copy);
            /**
             * Parameter constructor that reads a configuration from a string.
             * \param text String to read
             */
            explicit Configuration(const std::string& text) : data() { load(text); }
            /**
             * Parameter constructor that reads a configuration from a stream.
             * \param in Input stream.
             */
            explicit Configuration(std::istream& in) : data() { load(in); }
            /**
             * Assignment operator.
             * \param copy Configuration object to copy.
             * \return Reference to this object.
             */
            Configuration& operator=(const Configuration& copy);
            /**
             * Return the boolean status for the existence of the named section
             * in the current configuration.
             * \param section Name of section to search for.
             * \return True if the named section exists.
             */
            bool hasSection(const std::string& section) const;
            /**
             * Return a set of all of the sections in this configuration. The
             * set will include the DEFAULT_SECTION if it has been utilized.
             * \return Set of section names
             */
            const std::set<std::string> sections() const;
            /**
             * Set the named property to the given value in the specified section.
             * \param section Section
             * \param key Key
             * \param value Value
             * \return Reference to this object.
             */
            Configuration& setProperty(const std::string& section,
                    const std::string& key, const std::string& value);
            /**
             * Set the named property to the given value in the default section.
             * \param key Key
             * \param value Value
             * \return Reference to this object.
             */
            inline Configuration& setProperty(const std::string& key, const std::string& value)
            { return setProperty(DEFAULT_SECTION, key, value); }
            /**
             * Return the named property from the given section. If the property does not
             * exist in the given section then the default value will be returned.
             * \param section Section
             * \param key Key
             * \param defaultValue Default value
             * \return Value for the named key or the defaultValue.
             */
            std::string getProperty(const std::string& section,
                    const std::string& key,
                    const std::string& defaultValue);
            /**
             * Return the named property from the default section. If the property does not
             * exist in the given section then the default value will be returned.
             * \param key Key
             * \param defaultValue Default value
             * \return Value for the named key or the defaultValue.
             */
            inline std::string getProperty(const std::string& key, const std::string& defaultValue)
            { return getProperty(DEFAULT_SECTION, key, defaultValue); }
            /**
             * Return all properties for the named section. If the named section
             * does not exist then an empty Properties object will be returned.
             * \param section Section
             * \return Properties from the named section.
             */
            const Properties getProperties(const std::string& section = DEFAULT_SECTION) const;
            /**
             * Set the Properties object at the given section with a copy of
             * the given properties. If the section already exists then the
             * properties at that section will be replaced with the given properties.
             * \param section Section name
             * \param props Properties
             * \return Reference to this object.
             */
            Configuration& setProperties(const std::string& section, const Properties& props);
            /**
             * Set the entire set of properties for the named section. This will replace
             * any properties that currently exist at the named section.
             * \param props Properties to set
             * \return Reference to this object.
             */
            inline Configuration& setProperties(const Properties& props)
            { return setProperties(DEFAULT_SECTION, props); }
            /**
             * Load the configuration contents from the given string data.
             * \param data String data
             * \return Reference to this object
             */
            Configuration& load(const std::string& data);
            /**
             * Load the configuration contents from the given stream.
             * \param in Input stream
             * \return Reference to this object
             */
            Configuration& load(std::istream& in);
            /**
             * Store the current container data into the given string.
             * \param data String that will receive the formatted contents of this container.
             * \return Reference to this object.
             */
            Configuration& store(std::string& data);
            /**
             * Store the current container data into the given output stream.
             * \param out Output stream
             * \return Reference to this object
             */
            Configuration& store(std::ostream& out);
    };

} // hslib

#endif // _HSLIB_CONFIGURATION_H_INCLUDED_
