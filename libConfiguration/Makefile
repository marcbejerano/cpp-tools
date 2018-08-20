#CXX=clang++

MINOR_VERSION=`echo $(VERSION)|sed -E 's/\.[0-9]*?$$//g'`
MAJOR_VERSION=`echo $(VERSION)|sed -E 's/\.[0-9]*?$$//g'|sed -E 's/\.[0-9]*?$$//g'`

TOOLS_LIB=../libTools
PROPERTIES_LIB=../libProperties
SUPPORT_INCLUDES=-I$(PROPERTIES_LIB) -I$(TOOLS_LIB)

ifdef RELEASE
CXXFLAGS=--std=c++11 -fPIC -O2 -I. $(SUPPORT_INCLUDES)
LDFLAGS=-s
else
CXXFLAGS=--std=c++11 -fPIC -g -Wall -I. $(SUPPORT_INCLUDES)
LDFLAGS=-rdynamic -g
endif

TARGET=libConfiguration.so
SOURCES=configuration.cc
HEADERS=configuration.h Configuration
OBJECTS=configuration.o

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
install: $(TARGET) configuration.h Configuration
	@install -D libConfiguration.so $(PREFIX)/lib/libConfiguration.so.$(VERSION)
	@ln -sf $(PREFIX)/lib/libConfiguration.so.$(VERSION) $(PREFIX)/lib/libConfiguration.so.$(MAJOR_VERSION)
	@ln -sf $(PREFIX)/lib/libConfiguration.so.$(VERSION) $(PREFIX)/lib/libConfiguration.so.$(MINOR_VERSION)
	@ln -sf $(PREFIX)/lib/libConfiguration.so.$(VERSION) $(PREFIX)/lib/libConfiguration.so
	@install -D configuration.h $(PREFIX)/include/configuration.h
	@install -D Configuration $(PREFIX)/include/Configuration

#install: $(TARGET) $(HEADERS)
#	$(foreach elemet,$(HEADERS),$(install -g root -o root -m 0644 -D $(element) /usr/local/include/research/$(element)))

configuration.o:configuration.cc configuration.h Configuration
