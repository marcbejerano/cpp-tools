#CXX=clang++

MINOR_VERSION=`echo $(VERSION)|sed -E 's/\.[0-9]*?$$//g'`
MAJOR_VERSION=`echo $(VERSION)|sed -E 's/\.[0-9]*?$$//g'|sed -E 's/\.[0-9]*?$$//g'`

TOOLS_LIB=../libTools
PROPERTIES_LIB=../libProperties
CONFIGURATION_LIB=../libConfiguration

SUPPORT_INCLUDES=-I$(CONFIGURATION_LIB) -I$(PROPERTIES_LIB) -I$(TOOLS_LIB)

ifdef RELEASE
CXXFLAGS=--std=c++11 -fPIC -O2 -I. $(SUPPORT_INCLUDES)
LDFLAGS=-s
else
CXXFLAGS=--std=c++11 -fPIC -g -Wall -I. $(SUPPORT_INCLUDES)
LDFLAGS=-rdynamic -g
endif

TARGET=libLogging.so
SOURCES=level.cc loggingevent.cc patternlayout.cc appender.cc logger.cc logfactory.cc
HEADERS=level.h Level loggingevent.h LoggingEvent patternlayout.h PatternLayout appender.h Appender \
		logger.h Logger event.h Event exception.h Exception logfactory.h LogFactory
OBJECTS=level.o loggingevent.o patternlayout.o appender.o logger.o logfactory.o

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

.PHONY: test
test: $(TARGET)
	@cd test && make test

.PHONY: install
install: $(TARGET) $(HEADERS)
	@install -D libLogging.so $(PREFIX)/lib/libLogging.so.$(VERSION)
	@ln -sf $(PREFIX)/lib/libLogging.so.$(VERSION) $(PREFIX)/lib/libLogging.so.$(MAJOR_VERSION)
	@ln -sf $(PREFIX)/lib/libLogging.so.$(VERSION) $(PREFIX)/lib/libLogging.so.$(MINOR_VERSION)
	@ln -sf $(PREFIX)/lib/libLogging.so.$(VERSION) $(PREFIX)/lib/libLogging.so
	@install -D level.h $(PREFIX)/include/level.h
	@install -D Level $(PREFIX)/include/Level
	@install -D loggingevent.h $(PREFIX)/include/loggingevent.h
	@install -D LoggingEvent $(PREFIX)/include/LoggingEvent
	@install -D event.h $(PREFIX)/include/event.h
	@install -D Event $(PREFIX)/include/Event
	@install -D patternlayout.h $(PREFIX)/include/patternlayout.h
	@install -D PatternLayout $(PREFIX)/include/PatternLayout
	@install -D appender.h $(PREFIX)/include/appender.h
	@install -D Appender $(PREFIX)/include/Appender
	@install -D logger.h $(PREFIX)/include/logger.h
	@install -D Logger $(PREFIX)/include/Logger
	@install -D logfactory.h $(PREFIX)/include/logfactory.h
	@install -D LogFactory $(PREFIX)/include/LogFactory
	@install -D exception.h $(PREFIX)/include/exception.h

#install: $(TARGET) $(HEADERS)
#	$(foreach elemet,$(HEADERS),$(install -g root -o root -m 0644 -D $(element) /usr/local/include/research/$(element)))

level.o:		level.cc level.h Level
loggingevent.o:	loggingevent.cc loggingevent.h LoggingEvent event.h Event
patternlayout.o:patternlayout.cc patternlayout.h PatternLayout event.h loggingevent.h Event LoggingEvent
appender.o:		appender.cc appender.h Appender
logger.o:		logger.cc logger.h LoggingEvent Appender Level
logfactory.o:	logfactory.cc logfactory.h LogFactory Appender Logger
