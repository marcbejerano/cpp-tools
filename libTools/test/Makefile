#CXX=clang++

ifdef RELEASE
CXXFLAGS=--std=c++11 -fPIC -O2 -I. -I..
LDFLAGS=-s
else
CXXFLAGS=--std=c++11 -fPIC -g  -I. -I..
LDFLAGS=-rdynamic -g
endif

TARGET=testrunner
LIBS=-L.. -lTools -lcppunit
OBJECTS=ToolsTest.o
HEADERS=ToolsTest.h

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<

$(TARGET): main.o $(OBJECTS) ../libTools.so
	$(CXX) $(CFLAGS) -o $(TARGET) $(LDFLAGS) $(OBJECTS) main.o $(LIBS)

test: $(TARGET)
	LD_LIBRARY_PATH=.. ./testrunner

debug:
	DEBUG=1 make

release:
	RELEASE=1 make

debugger: $(TARGET)
	LD_LIBRARY_PATH=.. nemiver ./testrunner

check: $(TARGET)
	LD_LIBRARY_PATH=.. ldd $(TARGET)
	LD_LIBRARY_PATH=.. valgrind --leak-check=full --show-leak-kinds=all ./testrunner

clean:
	rm -f main.o $(OBJECTS) $(TARGET) cppTestBasicMathResults.xml LogFactoryTest.log

# Object dependencies
main.o:					main.cc $(HEADERS)
ToolsTest.o:			ToolsTest.cc ToolsTest.h ../Tools ../tools.h
