#CXX=clang++

TOOLS_LIB=../../libTools

SUPPORT_INCLUDES=-I$(TOOLS_LIB)
SUPPORT_LIBS=-L$(TOOLS_LIB) -lTools
RUN_TEST_LIBS=$(TOOLS_LIB)

ifdef RELEASE
CXXFLAGS=--std=c++11 -fPIC -O2 -I. -I.. $(SUPPORT_INCLUDES)
LDFLAGS=-s
else
CXXFLAGS=--std=c++11 -fPIC -g  -I. -I.. $(SUPPORT_INCLUDES)
LDFLAGS=-rdynamic -g
endif

TARGET=testrunner
LIBS=-L.. -lProperties $(SUPPORT_LIBS) -lcppunit
OBJECTS=PropertiesTest.o
HEADERS=PropertiesTest.h

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<

$(TARGET): main.o $(OBJECTS) ../libProperties.so
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
PropertiesTest.o:		PropertiesTest.cc PropertiesTest.h ../Properties ../properties.h
