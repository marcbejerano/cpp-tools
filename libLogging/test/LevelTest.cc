#include "LevelTest.h"
#include <functional>
#include <Level>

using namespace hslib;

void StandardLevelTest::testCtor()
{
    StandardLevel level;
}

void StandardLevelTest::testCtorArgs()
{
    StandardLevel level(12345);
    CPPUNIT_ASSERT(12345 == level.intLevel());
}

void StandardLevelTest::testCtorCopy()
{
    StandardLevel level(12345);
    StandardLevel copy(level);
    CPPUNIT_ASSERT(12345 == copy.intLevel());
}

void StandardLevelTest::testAssignment()
{
    StandardLevel level(12345);
    StandardLevel copy = level;
    CPPUNIT_ASSERT(12345 == copy.intLevel());
}

void StandardLevelTest::testIntLevel()
{
    StandardLevel level(12345);
    CPPUNIT_ASSERT(12345 == level.intLevel());
}

void StandardLevelTest::testGetStandardLevel()
{
    StandardLevel level = StandardLevel::getStandardLevel(StandardLevel::WARN);
    CPPUNIT_ASSERT(StandardLevel::WARN == level.intLevel());
    level = StandardLevel::getStandardLevel(12345);
    CPPUNIT_ASSERT(StandardLevel::TRACE == level.intLevel());
    level = StandardLevel::getStandardLevel(-12345);
    CPPUNIT_ASSERT(StandardLevel::OFF == level.intLevel());
}

void LevelTest::testCtor()
{
    Level level;
}

void LevelTest::testCtorArgs()
{
    Level level("HELLO", 12345);
}

void LevelTest::testCtorCopy()
{
    Level level("HELLO", 12345);
    Level copy(level);
    CPPUNIT_ASSERT(copy.name() == level.name());
    CPPUNIT_ASSERT(copy.intLevel() == level.intLevel());
}

void LevelTest::testAssignment()
{
    Level level("HELLO", 12345);
    Level copy = level;
    CPPUNIT_ASSERT(copy.name() == level.name());
    CPPUNIT_ASSERT(copy.intLevel() == level.intLevel());
}

void LevelTest::testClone()
{
    Level level("HELLO", 12345);
    Level copy = level.clone();
    CPPUNIT_ASSERT(copy.name() == level.name());
    CPPUNIT_ASSERT(copy.intLevel() == level.intLevel());
}

void LevelTest::testCompareTo()
{
    Level levelA(Level::OFF);
    Level levelB(Level::ALL);
    Level levelC(Level::OFF);
    CPPUNIT_ASSERT(-1 == levelA.compareTo(levelB));
    CPPUNIT_ASSERT( 0 == levelA.compareTo(levelC));
    CPPUNIT_ASSERT( 1 == levelB.compareTo(levelA));
}

void LevelTest::testEquals()
{
    Level levelA(Level::OFF);
    Level levelB(Level::ALL);
    Level levelC(Level::OFF);
    CPPUNIT_ASSERT(levelA.equals(levelC));
    CPPUNIT_ASSERT(!levelA.equals(levelB));
    CPPUNIT_ASSERT(levelA == levelC);
}

void LevelTest::testHashCode()
{
    Level level("HELLO", 12345);
    int expected = std::hash<std::string>()(std::string("HELLO"));
    CPPUNIT_ASSERT(expected == level.hashCode());
}

void LevelTest::testIntLevel()
{
    Level level("HELLO", 12345);
    CPPUNIT_ASSERT(12345 == level.intLevel());
}

void LevelTest::testIsInRange()
{
    Level level(Level::DEBUG);
    CPPUNIT_ASSERT(level.isInRange(Level::OFF, Level::ALL));
}

void LevelTest::testIsLessSpecificThan()
{
    Level level(Level::INFO);
    CPPUNIT_ASSERT(level.isLessSpecificThan(Level::ERROR));
}

void LevelTest::testIsMoreSpecificThan()
{
    Level level(Level::INFO);
    CPPUNIT_ASSERT(level.isMoreSpecificThan(Level::TRACE));
}

void LevelTest::testName()
{
    Level level("HELLO", 12345);
    CPPUNIT_ASSERT("HELLO" == level.name());
}

void LevelTest::testToString()
{
    Level level("HELLO", 12345);
    CPPUNIT_ASSERT("HELLO" == level.toString());
}

void LevelTest::testGetStandardLevel()
{
    Level level("HELLO", 12345);
    CPPUNIT_ASSERT(level.getStandardLevel().intLevel() == 12345);
}

void LevelTest::testForName()
{
    Level level = Level::forName("DEBUG", StandardLevel::DEBUG);
    CPPUNIT_ASSERT(level.intLevel() == StandardLevel::DEBUG);
    level = Level::forName("HELLO", 12345);
    CPPUNIT_ASSERT(level.intLevel() == 12345);
}

void LevelTest::testGetLevel()
{
    Level level = Level::getLevel("DEBUG");
    CPPUNIT_ASSERT(level.intLevel() == StandardLevel::DEBUG);
    level = Level::getLevel("NOT THERE");
    CPPUNIT_ASSERT(level.intLevel() == StandardLevel::OFF);
    level = Level::getLevel("fatal");
    CPPUNIT_ASSERT(level.intLevel() == StandardLevel::FATAL);
}

void LevelTest::testToLevel()
{
    Level level = Level::toLevel("DEBUG");
    CPPUNIT_ASSERT(level.intLevel() == StandardLevel::DEBUG);
    level = Level::toLevel("NOT THERE 2");
    CPPUNIT_ASSERT(level.intLevel() == StandardLevel::DEBUG);

    level = Level::toLevel("DEBUG", Level::ALL);
    CPPUNIT_ASSERT(level.intLevel() == StandardLevel::DEBUG);
    level = Level::toLevel("NOT THERE 3", Level::ERROR);
    CPPUNIT_ASSERT(level.intLevel() == StandardLevel::ERROR);
}

