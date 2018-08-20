#CXX=clang++

TOOLS_LIB=../../libTools
PROPERTIES_LIB=../../libProperties
CONFIGURATION_LIB=../../libConfiguration

SUPPORT_INCLUDES=-I$(TOOLS_LIB) -I$(PROPERTIES_LIB) -I$(CONFIGURATION_LIB)
SUPPORT_LIBS=-L$(CONFIGURATION_LIB) -lConfiguration -L$(PROPERTIES_LIB) -lProperties -L$(TOOLS_LIB) -lTools
RUN_TEST_LIBS=$(CONFIGURATION_LIB):$(PROPERTIES_LIB):$(TOOLS_LIB)

ifdef RELEASE
CXXFLAGS=--std=c++11 -fPIC -O2 -I. -I.. $(SUPPORT_INCLUDES)
LDFLAGS=-s
else
CXXFLAGS=--std=c++11 -fPIC -g -Wall -I. -I.. $(SUPPORT_INCLUDES)
LDFLAGS=-rdynamic -g
endif

TARGET=testrunner
LIBS=-L.. -lLogging $(SUPPORT_LIBS) -lcppunit
OBJECTS=LevelTest.o PropertiesTest.o ToolsTest.o ConfigurationTest.o \
		ExceptionTest.o EventTest.o PatternLayoutTest.o AppenderTest.o \
		LoggerTest.o LogFactoryTest.o
HEADERS=ConfigurationTest.h EventTest.h ExceptionTest.h LevelTest.h \
		PatternLayoutTest.h PropertiesTest.h ToolsTest.h AppenderTest.h \
		LoggerTest.h LogFactoryTest.h

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<

$(TARGET): main.o $(OBJECTS) ../libLogging.so
	$(CXX) $(CFLAGS) -o $(TARGET) $(LDFLAGS) $(OBJECTS) main.o $(LIBS)

test: $(TARGET)
	LD_LIBRARY_PATH=..:$(RUN_TEST_LIBS) ./testrunner

debug:
	DEBUG=1 make

release:
	RELEASE=1 make

debugger: $(TARGET)
	LD_LIBRARY_PATH=..:$(RUN_TEST_LIBS) nemiver ./testrunner

check: $(TARGET)
	LD_LIBRARY_PATH=..:$(RUN_TEST_LIBS) ldd $(TARGET)
	LD_LIBRARY_PATH=..:$(RUN_TEST_LIBS) valgrind --leak-check=full --show-leak-kinds=all ./testrunner

clean:
	rm -f main.o $(OBJECTS) $(TARGET) cppTestBasicMathResults.xml LogFactoryTest.log

# Object dependencies
main.o:					main.cc $(HEADERS)
LevelTest.o:			LevelTest.cc LevelTest.h ../Level ../level.h
ExceptionTest.o:		ExceptionTest.cc ExceptionTest.h ../exception.h ../Exception
EventTest.o:			EventTest.cc EventTest.h ../event.h ../Event
PatternLayoutTest.o:	PatternLayoutTest.cc PatternLayoutTest.h ../patternlayout.h ../PatternLayout
AppenderTest.o:			AppenderTest.cc AppenderTest.h ../appender.h ../Appender
LoggerTest.o:			LoggerTest.cc LoggerTest.h ../logger.h ../Logger
LogFactoryTest.o:		LogFactoryTest.cc LogFactoryTest.h ../logfactory.h ../LogFactory
