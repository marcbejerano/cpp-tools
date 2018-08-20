#include <Level>
#include <functional>
#include <cctype>

using namespace hslib;

/*
 * Standard Level array of predefined level values
 */
std::array<int, 8> StandardLevel::LEVELSET = {
    StandardLevel::OFF,
    StandardLevel::FATAL,
    StandardLevel::ERROR,
    StandardLevel::WARN,
    StandardLevel::INFO,
    StandardLevel::DEBUG,
    StandardLevel::TRACE,
    StandardLevel::ALL
};

/**
 * Return the StandardLevel that is equal to the given intLevel. If
 * a StandardLevel cannot be found that comes closest to the required
 * intLevel (but not greater than) then the default StandardLevel::OFF
 * will be returned.
 * \param intLevel Required integer level value
 * \return A StandardLevel object
 */
StandardLevel StandardLevel::getStandardLevel(int intLevel)
{
    StandardLevel level(StandardLevel::OFF);
    for (auto it = StandardLevel::LEVELSET.cbegin(); it != StandardLevel::LEVELSET.cend(); ++it)
    {
        if (*it > intLevel)
            break;
        else
            level = StandardLevel(*it);
    }
    return level;
}

/*
 * Map of known Level value objects.
 */
std::map<std::string, Level> Level::LEVELS;

const Level Level::OFF("OFF", StandardLevel::OFF);
const Level Level::FATAL("FATAL", StandardLevel::FATAL);
const Level Level::ERROR("ERROR", StandardLevel::ERROR);
const Level Level::WARN("WARN", StandardLevel::WARN);
const Level Level::INFO("INFO", StandardLevel::INFO);
const Level Level::DEBUG("DEBUG", StandardLevel::DEBUG);
const Level Level::TRACE("TRACE", StandardLevel::TRACE);
const Level Level::ALL("ALL", StandardLevel::ALL);

/**
 * Parameterized constructor. If the level name does not exist in
 * the global LEVELS map then it will be added for future references.
 * \param name Name of level object
 * \param level Integer level value
 */
Level::Level(const std::string& name, int level) : _slevel(level), _name(name)
{
    std::string s(name);
    for (size_t n = 0; n < s.length(); n++) s[n] = ::toupper(s[n]);
    if (Level::LEVELS.find(s) == Level::LEVELS.end()) {
        Level::LEVELS[s] = *this;
    }
}

/**
 * Compare this Level object to the one provided.
 * <ul><li>If the objects are equal then 0 is returned</li>
 *     <li>If this Level is less than the other then -1 is returned</li>
 *     <li>If this Level is more than the other then +1 is returned</li></ul>
 * \param other Level to compare against
 * \return Integer value representing the comparison
 */
int Level::compareTo(const Level& other)
{
    int result = 0; // equal
    if (intLevel() != other.intLevel())
    {
        if (intLevel() < other.intLevel())
            result = -1;
        else
            result = 1;
    }
    return result;
}

/**
 * Search the current Level cache for the requested name and return it
 * if found. If not found then create the level and add it to the Level
 * cache and then return the new Level object.
 * \param name Name of Level
 * \param intValue Integer level value
 * \return Level object with the requested values
 */
Level Level::forName(const std::string& name, int intValue)
{
    std::string s(name);
    for (size_t n = 0; n < s.length(); n++) s[n] = ::toupper(s[n]);
    if (Level::LEVELS.find(s) != Level::LEVELS.end())
        return Level::LEVELS[s];
    else
        return Level(name, intValue);
}

/**
 * Find the requested Level name in the Level cache and return the Level
 * object. If the name cannot be found in the cache then the default
 * Level::OFF object will be returned.
 * \param name Name of Level to find
 * \return Level object (Level:OFF if not found)
 */
Level Level::getLevel(const std::string& name)
{
    std::string s(name);
    for (size_t n = 0; n < s.length(); n++) s[n] = ::toupper(s[n]);
    if (Level::LEVELS.find(s) != Level::LEVELS.end())
        return Level::LEVELS[s];
    else
       return Level::OFF;
}

/**
 * Retrieve the Level object (from the Level cache) with the given
 * name. If the Level object cannot be found then the supplied default
 * Level object will be returned.
 * \param name Name of Level object to locate
 * \param defaultLevel Default Level object to return if named Level is not found.
 * \return Level object
 */
Level Level::toLevel(const std::string& name, const Level& defaultLevel)
{
    std::string s(name);
    for (size_t n = 0; n < s.length(); n++) s[n] = ::toupper(s[n]);
    if (Level::LEVELS.find(s) != Level::LEVELS.end())
        return Level::LEVELS[s];
    else
        return defaultLevel;
}

