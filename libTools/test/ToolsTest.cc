#include "ToolsTest.h"
#include <Tools>
#include <iostream>
#include <vector>

using namespace hslib;

void ToolsTest::testRtrim()
{
    std::string testA("abcdefg   ");
    std::string testB("   abcdefg");
    std::string testC("abcdefg");
    std::string testD("   abcdefg   ");

    CPPUNIT_ASSERT("abcdefg" == rtrim(testA));
    CPPUNIT_ASSERT("   abcdefg" == rtrim(testB));
    CPPUNIT_ASSERT("abcdefg" == rtrim(testC));
    CPPUNIT_ASSERT("   abcdefg" == rtrim(testD));
}

void ToolsTest::testLtrim()
{
    std::string testA("abcdefg   ");
    std::string testB("   abcdefg");
    std::string testC("abcdefg");
    std::string testD("   abcdefg   ");

    CPPUNIT_ASSERT("abcdefg   " == ltrim(testA));
    CPPUNIT_ASSERT("abcdefg" == ltrim(testB));
    CPPUNIT_ASSERT("abcdefg" == ltrim(testC));
    CPPUNIT_ASSERT("abcdefg   " == ltrim(testD));
}

void ToolsTest::testTrim()
{
    std::string testA("abcdefg   ");
    std::string testB("   abcdefg");
    std::string testC("abcdefg");
    std::string testD("   abcdefg   ");

    CPPUNIT_ASSERT("abcdefg" == trim(testA));
    CPPUNIT_ASSERT("abcdefg" == trim(testB));
    CPPUNIT_ASSERT("abcdefg" == trim(testC));
    CPPUNIT_ASSERT("abcdefg" == trim(testD));
}

void ToolsTest::testTrimCopy()
{
    std::string testA("abcdefg   ");
    std::string testB("   abcdefg");
    std::string testC("abcdefg");
    std::string testD("   abcdefg   ");

    CPPUNIT_ASSERT("abcdefg" == trim_copy(testA));
    CPPUNIT_ASSERT("abcdefg   " == testA);
    CPPUNIT_ASSERT("abcdefg" == trim_copy(testB));
    CPPUNIT_ASSERT("   abcdefg" == testB);
    CPPUNIT_ASSERT("abcdefg" == trim_copy(testC));
    CPPUNIT_ASSERT("abcdefg" == testC);
    CPPUNIT_ASSERT("abcdefg" == trim_copy(testD));
    CPPUNIT_ASSERT("   abcdefg   " == testD);
}

void ToolsTest::testStartsWith()
{
    std::string test("this is a test");
    CPPUNIT_ASSERT(startsWith(test, "this is"));
    CPPUNIT_ASSERT(startsWith(test, "this is a test"));
    CPPUNIT_ASSERT(!startsWith(test, "this is not a test"));
}

void ToolsTest::testEndsWith()
{
    std::string test("this is a test");
    CPPUNIT_ASSERT(endsWith(test, "is a test"));
    CPPUNIT_ASSERT(endsWith(test, "this is a test"));
    CPPUNIT_ASSERT(!endsWith(test, "not a test"));
}

void ToolsTest::testFileExists()
{
    CPPUNIT_ASSERT(fileExists("ToolsTest.cc"));
    CPPUNIT_ASSERT(fileExists("FILE DOES NOT EXIST") == false);
    // check for existence of a directory
    CPPUNIT_ASSERT(fileExists("/tmp"));
}

void ToolsTest::testSplit()
{
    std::vector<std::string> elems = split("one:two::three", ':');
    CPPUNIT_ASSERT(elems.size() == 4);
    CPPUNIT_ASSERT(elems[3] == "three");
}

