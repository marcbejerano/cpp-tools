#ifndef _HSLIB_PROPERTIES_H_INCLUDED_
#define _HSLIB_PROPERTIES_H_INCLUDED_

#include <iostream>
#include <map>
#include <set>
#include <string>

namespace hslib {

    //! Name/Value properties class
    /**
     * Properties container styled after the java.util.Properties class.
     */
    class Properties
    {
        private:
            /** Property map data */
            std::map<std::string, std::string> propertyMap;

        public:
            /** Default constructor */
            Properties() : propertyMap() { }
            /**
             * Copy constructor.
             * \param copy Properties object to copy
             */
            Properties(const Properties& copy) {
                propertyMap.insert(copy.propertyMap.cbegin(), copy.propertyMap.cend());
            }
            /**
             * Assignment operator. This method will clear the current collection
             * and then insert the copy into it (deep copy).
             * \param copy Properties object to copy
             * \return Reference to this object
             */
            Properties& operator=(const Properties& copy) {
                propertyMap.clear();
                propertyMap.insert(copy.propertyMap.cbegin(), copy.propertyMap.cend());
                return *this;
            }
            /**
             * Set a new property or update an existing property.
             * \param key Property key
             * \param value Property value
             * \return Reference to this object
             */
            Properties& setProperty(const std::string& key, const std::string& value);
            /**
             * Return an existing property or the default value if the 
             * property key does not exist.
             * \param key Property key
             * \param defaultValue Default property value if requested key does not exist
             * \return Property value or the defaultValue.
             */
            const std::string getProperty(const std::string& key, const std::string& defaultValue = "") const;
            /**
             * Return the set of keys used in this property container.
             * \return Set of keys
             */
            const std::set<std::string> keys() const;
            /**
             * Load the properties collection by parsing the input string.
             * \param text Properties as text
             * \return Reference to this object
             */
            Properties& load(const std::string& text);
            /**
             * Load the properties collection from the given input stream.
             * \param in Input stream
             * \return Reference to this object
             */
            Properties& load(std::istream& in);
            /**
             * Store the properties (formatted and sorted) into the target string.
             * \param target String target
             * \return Reference to this object.
             */
            Properties& store(std::string& target);
            /**
             * Store the properties (formatted and sorted) into the target stream.
             * \param out Output stream
             * \return Reference to this object.
             */
            Properties& store(std::ostream& out);
    };

} // hslib

#endif // _HSLIB_PROPERTIES_H_INCLUDED_
