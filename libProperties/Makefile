#CXX=clang++

MINOR_VERSION=`echo $(VERSION)|sed -E 's/\.[0-9]*?$$//g'`
MAJOR_VERSION=`echo $(VERSION)|sed -E 's/\.[0-9]*?$$//g'|sed -E 's/\.[0-9]*?$$//g'`

TOOLS_LIB=../libTools
SUPPORT_INCLUDES=-I$(TOOLS_LIB)

ifdef RELEASE
CXXFLAGS=--std=c++11 -fPIC -O2 -I. $(SUPPORT_INCLUDES)
LDFLAGS=-s
else
CXXFLAGS=--std=c++11 -fPIC -g -Wall -I. $(SUPPORT_INCLUDES)
LDFLAGS=-rdynamic -g
endif

TARGET=libProperties.so
SOURCES=properties.cc
HEADERS=properties.h Properties
OBJECTS=properties.o

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<

$(TARGET):	$(OBJECTS)
	$(CXX) -shared $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) -o $(TARGET)
	cd test && make

.PHONY: debug
debug:
	@DEBUG=1 make

.PHONY: release
release:
	@RELEASE=1 make

docs: $(HEADERS) $(SOURCES)
	@doxygen Doxyfile

check: $(TARGET)
	@cppcheck --enable=all --std=c++11 --report-progress --platform=unix64 --language=c++ *.cc *.h > /dev/null
	@sloccount --filecount --addlangall --personcost 170000 ${PWD} > sloccount.out
	@cd test && make check

.PHONY: clean
clean:
	@rm -fr $(OBJECTS) $(TARGET) docs/html sloccount.out 2>/dev/null
	@rm -fr .data && mkdir .data
	@cd test && make clean

test: $(TARGET) test/testrunner
	@cd test && make test

.PHONY: install
install: $(TARGET) properties.h Properties
	@install -D libProperties.so $(PREFIX)/lib/libProperties.so.$(VERSION)
	@ln -sf $(PREFIX)/lib/libProperties.so.$(VERSION) $(PREFIX)/lib/libProperties.so.$(MAJOR_VERSION)
	@ln -sf $(PREFIX)/lib/libProperties.so.$(VERSION) $(PREFIX)/lib/libProperties.so.$(MINOR_VERSION)
	@ln -sf $(PREFIX)/lib/libProperties.so.$(VERSION) $(PREFIX)/lib/libProperties.so
	@install -D properties.h $(PREFIX)/include/properties.h
	@install -D Properties $(PREFIX)/include/Properties

#install: $(TARGET) $(HEADERS)
#	$(foreach elemet,$(HEADERS),$(install -g root -o root -m 0644 -D $(element) /usr/local/include/research/$(element)))

properties.o:	properties.cc properties.h Properties $(TOOLS_LIB)/Tools $(TOOLS_LIB)/tools.h
