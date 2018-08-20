#ifndef _HSLIB_LEVEL_H_INCLUDED_
#define _HSLIB_LEVEL_H_INCLUDED_

#include <array>
#include <climits>
#include <map>
#include <string>

namespace hslib {

    //! Standard severity level
    /**
     * Standard severity level
     */
    class StandardLevel
    {
        private:
            /** Integer leve lvalue */
            int _intLevel;
            /** Set of valid standard levels */
            static std::array<int, 8> LEVELSET;
        public:
            /** Predefined StaticLevel value: OFF (0) */
            static const int OFF = 0;
            /** Predefined StaticLevel value: FATAL (100) */
            static const int FATAL = 100;
            /** Predefined StaticLevel value: ERROR (200) */
            static const int ERROR = 200;
            /** Predefined StaticLevel value: WARN (300) */
            static const int WARN = 300;
            /** Predefined StaticLevel value: INFO (400) */
            static const int INFO = 400;
            /** Predefined StaticLevel value: DEBUG (500) */
            static const int DEBUG = 500;
            /** Predefined StaticLevel value: TRACE (600) */
            static const int TRACE = 600;
            /** Predefined StaticLevel value: ALL (INT_MAX) */
            static const int ALL = INT_MAX;

            /** Default constructor */
            StandardLevel() : _intLevel(OFF) { }
            /** Parameterized constructor.
             *  \param level Integer level value */
            explicit StandardLevel(int level) : _intLevel(level) { }
            /** Copy constructor.
             *  \param copy StandardLevel object to copy */
            StandardLevel(const StandardLevel& copy) : _intLevel(copy._intLevel) { }
            /** Assignment operator.
             *  \param copy StandardLevel object to copy
             *  \return Refernce to this StandardLevel object */
            StandardLevel& operator=(const StandardLevel& copy) { _intLevel = copy._intLevel; return *this; }
            /** Return the integer level value for this StandardLevel object.
             *  \return Integer level value */
            inline int intLevel() const { return _intLevel; }
            /**
             * Return the StandardLevel that is equal to the given intLevel. If
             * a StandardLevel cannot be found that comes closest to the required
             * intLevel (but not greater than) then the default StandardLevel::OFF
             * will be returned.
             * \param intLevel Required integer level value
             * \return A StandardLevel object
             */
            static StandardLevel getStandardLevel(int intLevel);
    };

    //! Severity level
    /**
     * Severity level
     */
    class Level
    {
        private:
            /** Standard severity level */
            StandardLevel _slevel;
            /** Level name */
            std::string _name;
            /** Standard list of predefined levels */
            static std::map<std::string, Level> LEVELS;
        public:
            /** Predefined Level object: ALL */
            static const Level ALL;
            /** Predefined Level object: DEBUG */
            static const Level DEBUG;
            /** Predefined Level object: ERROR */
            static const Level ERROR;
            /** Predefined Level object: FATAL */
            static const Level FATAL;
            /** Predefined Level object: INFO */
            static const Level INFO;
            /** Predefined Level object: OFF */
            static const Level OFF;
            /** Predefined Level object: TRACE */
            static const Level TRACE;
            /** Predefined Level object: WARN */
            static const Level WARN;
            /** Predefined category name */
            static std::string CATEGORY;

            /** Default constructor */
            Level() : _slevel(), _name("OFF") { }
            /**
             * Parameterized constructor. If the level name does not exist in
             * the global LEVELS map then it will be added for future references.
             * \param name Name of level object
             * \param level Integer level value
             */
            Level(const std::string& name, int level);
            /** Copy constructor.
             *  \param copy Level object to copy */
            Level(const Level& copy) : _slevel(copy._slevel), _name(copy._name) { }
            /** Assignment operator.
             *  \param copy Level object to copy
             *  \return Reference to this object */
            Level& operator=(const Level& copy) { _slevel = copy._slevel; return *this; }
            /** Clone method. A copy of the current object will be created and
             *  returned to the caller.
             *  \return Copy of current object */
            Level clone() { return Level(*this); }
            /**
             * Compare this Level object to the one provided.
             * <ul><li>If the objects are equal then 0 is returned</li>
             *     <li>If this Level is less than the other then -1 is returned</li>
             *     <li>If this Level is more than the other then +1 is returned</li></ul>
             * \param other Level to compare against
             * \return Integer value representing the comparison
             */
            int compareTo(const Level& other);
            /** Comparison method for equality.
             *  \param other Level object to compare against
             *  \return true is this level is equal to the other object */
            inline bool equals(const Level& other) const { return (intLevel() == other.intLevel()); }
            /** Comparison operator for equality.
             *  \param other Level object to compare against
             *  \return true is this level is equal to the other object */
            inline bool operator==(const Level& other) const { return equals(other); }
            /** Return the hash code for this level object. The hash code is computed
             *  based on the name of the Level object and not the intValue.
             *  \return hash value for this Level object */
            inline int hashCode() { return std::hash<std::string>()(name()); }
            /** Return the integer level value for this Level object.
             *  \return Integer level value */
            inline int intLevel() const { return _slevel.intLevel(); }
            /** Determine if this Level object falls within the given range of Levels.
             *  \param minLevel Minimum level
             *  \param maxLevel Maximum level
             *  \return true if this Level has a value that lies within the given limits */
            inline bool isInRange(const Level& minLevel, const Level& maxLevel) const
                { return intLevel() >= minLevel.intLevel() && intLevel() <= maxLevel.intLevel(); }
            /** Determine if this Level object is less specific (greater granularity) then the
             *  given level.
             *  \param level Maximum granularity level
             *  \return tru if this Level is less granular than the given level */
            inline bool isLessSpecificThan(const Level& level) const { return intLevel() >= level.intLevel(); }
            /** Determine if this Level object is more specific (less granularity) then the
             *  given level.
             *  \param level Minimum granularity level
             *  \return tru if this Level is more granular than the given level */
            inline bool isMoreSpecificThan(const Level& level) const { return intLevel() <= level.intLevel(); }
            /** Return this Level object's assigned name.
             *  \return Level name */
            inline const std::string name() const { return _name; }
            /** Return the string representation of this Level object. This will just return
             *  the Level's assigned name.
             *  \return String representation of this Level object */
            inline const std::string toString() const { return _name; }
            /** Return this Level object's intger value as a StandardLevel. If this Level
             *  object's integer value does not 100% match one of the predefined StandardLevel
             *  values then the closest value will be chosen.
             *  \return StandardLevel value for this Level's integer value */
            StandardLevel getStandardLevel() { return _slevel; }
            /**
             * Search the current Level cache for the requested name and return it
             * if found. If not found then create the level and add it to the Level
             * cache and then return the new Level object.
             * \param name Name of Level
             * \param intValue Integer level value
             * \return Level object with the requested values
             */
            static Level forName(const std::string& name, int intValue);
            /**
             * Find the requested Level name in the Level cache and return the Level
             * object. If the name cannot be found in the cache then the default
             * Level::OFF object will be returned.
             * \param name Name of Level to find
             * \return Level object (Level:OFF if not found)
             */
            static Level getLevel(const std::string& name);
            /**
             * Retrieve the Level object (from the Level cache) with the given
             * name. If the Level object cannot be found then the supplied default
             * Level object will be returned.
             * \param name Name of Level object to locate
             * \param defaultLevel Default Level object to return if named Level is not found.
             * \return Level object
             */
            static Level toLevel(const std::string& name, const Level& defaultLevel = Level::DEBUG);
    };
} // hslib

#endif // _HSLIB_LEVEL_H_INCLUDED_
