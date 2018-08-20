#CXX=clang++

MINOR_VERSION=`echo $(VERSION)|sed -E 's/\.[0-9]*?$$//g'`
MAJOR_VERSION=`echo $(VERSION)|sed -E 's/\.[0-9]*?$$//g'|sed -E 's/\.[0-9]*?$$//g'`

ifdef RELEASE
CXXFLAGS=--std=c++11 -fPIC -O2 -I.
LDFLAGS=-s
else
CXXFLAGS=--std=c++11 -fPIC -g -Wall -I.
LDFLAGS=-rdynamic -g
endif

TARGET=libTools.so
SOURCES=tools.cc
HEADERS=tools.h Tools
OBJECTS=tools.o

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
install: $(TARGET) tools.h Tools
	@install -D libTools.so $(PREFIX)/lib/libTools.so.$(VERSION)
	@ln -sf $(PREFIX)/lib/libTools.so.$(VERSION) $(PREFIX)/lib/libTools.so.$(MAJOR_VERSION)
	@ln -sf $(PREFIX)/lib/libTools.so.$(VERSION) $(PREFIX)/lib/libTools.so.$(MINOR_VERSION)
	@ln -sf $(PREFIX)/lib/libTools.so.$(VERSION) $(PREFIX)/lib/libTools.so
	@install -D tools.h $(PREFIX)/include/tools.h
	@install -D Tools $(PREFIX)/include/Tools

#install: $(TARGET) $(HEADERS)
#	$(foreach elemet,$(HEADERS),$(install -g root -o root -m 0644 -D $(element) /usr/local/include/research/$(element)))

tools.o:		tools.cc tools.h Tools
