#include "ExceptionTest.h"
#include <Exception>

using namespace hslib;

void ExceptionTest::testCtor()
{
    Exception ex;
}

void ExceptionTest::testCtorArgs()
{
    Exception ex("test");
    CPPUNIT_ASSERT("test" == ex.getMessage());
}

void ExceptionTest::testCtorCopy()
{
    Exception exA("test");
    Exception exB(exA);
    CPPUNIT_ASSERT("test" == exB.getMessage());
}

void ExceptionTest::testAssignment()
{
    Exception exA("test");
    Exception exB = exA;
    CPPUNIT_ASSERT("test" == exB.getMessage());
}

void ExceptionTest::testGetMessage()
{
    Exception ex("test");
    CPPUNIT_ASSERT("test" == ex.getMessage());
}

void ExceptionTest::testSetMessage()
{
    Exception ex("test");
    CPPUNIT_ASSERT("test" == ex.getMessage());
    ex.setMessage("another test");
    CPPUNIT_ASSERT("another test" == ex.getMessage());
}


