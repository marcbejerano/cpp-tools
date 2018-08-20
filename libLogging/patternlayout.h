#ifndef _HSLIB_PATTERNLAYOUT_H_INCLUDED_
#define _HSLIB_PATTERNLAYOUT_H_INCLUDED_

#include <string>
#include <Event>
#include <LoggingEvent>

namespace hslib {

    //! Abstract layout class
    /**
     * Output layout formatter.
     */
    class Layout
    {
        public:
            /**
             * Default constructor.
             */
            Layout() { }
            /**
             * Format the given event into a text string.
             * \param event Event to format
             * \return String representation of the event.
             */
            const std::string format(const Event& event) { return event.getCause(); }
    };

    //! Pattern layout class
    /**
     * Output layout formatter that uses a pattern to style the output.
     */
    class PatternLayout : public Layout
    {
        private:
            /** Pattern */
            std::string pattern;
            /** String alignment helper method */
            static const std::string align(const std::string& text, bool rightJustify, size_t minWidth, size_t maxWidth);
        public:
            /**
             * Default constructor
             */
            PatternLayout() : Layout(), pattern("%m%n") { }
            /**
             * Copy constructor.
             * \param copy PatternLayout object to copy.
             */
            PatternLayout(const PatternLayout& copy) : Layout(copy), pattern(copy.pattern) { }
            /**
             * Assignment operator.
             * \param copy PatternLayout object to copy.
             * \return Reference to this object.
             */
            PatternLayout& operator=(const PatternLayout& copy) {
                this->pattern = copy.pattern;
                return *this;
            }
            /**
             * Parameter constructor.
             * \param pattern Pattern.
             */
            explicit PatternLayout(const std::string& pattern) : Layout(), pattern(pattern) { }
            /**
             * Format the given event object according to the currently stored pattern.
             * <table>
             * <tr><th>Conversion Character</th><th>Effect</th></tr>
             * <tr><td><b>c</b></td><td>Used to output the category of the logging event. The category conversion specifier can be optionally followed by precision specifier, that is a decimal constant in brackets.<br/>
             * If a precision specifier is given, then only the corresponding number of right most components of the category name will be printed. By default the category name is printed in full.<br/>
             *
             * For example, for the category name "a.b.c" the pattern %c{2} will output "b.c".</td></tr>
             *
             * <tr><td><b>C</b></td><td>Used to output the fully qualified class name of the caller issuing the logging request. This conversion specifier can be optionally followed by precision specifier, that is a decimal constant in brackets.<br/>
             * If a precision specifier is given, then only the corresponding number of right most components of the class name will be printed. By default the class name is output in fully qualified form.<br/>
             *
             * For example, for the class name "org.apache.xyz.SomeClass", the pattern %C{1} will output "SomeClass".<br/>
             *
             * WARNING Generating the caller class information is slow. Thus, use should be avoided unless execution speed is not an issue.</td></tr>
             *
             * <tr><td><b>d</b></td><td>Used to output the date of the logging event. The date conversion specifier may be followed by a date format specifier enclosed between braces. For example, %d{%T %Z} or %d{%F %T %Z}. If no date format specifier is given then ISO8601 format is assumed.<br/>
             * The date format specifier admits the same syntax as the time pattern string of the strftime().<br/>
             *
             * For consistent results it is recommended to use the date formatters. These can be specified using one of the strings "ABSOLUTE", "DATE" and "ISO8601". For example, %d{ISO8601} or %d{ABSOLUTE}.</td></tr>
             *
             * <tr><td><b>F</b></td><td>Used to output the file name where the logging request was issued.<br/>
             * WARNING Generating caller location information is extremely slow and should be avoided unless execution speed is not an issue.</td></tr>
             *
             * <tr><td><b>l</b></td><td>Used to output location information of the caller which generated the logging event.<br/>
             * The location information depends on the JVM implementation but usually consists of the fully qualified name of the calling method followed by the callers source the file name and line number between parentheses.<br/>
             *
             * The location information can be very useful. However, its generation is extremely slow and should be avoided unless execution speed is not an issue.</td></tr>
             *
             * <tr><td><b>L</b></td><td>Used to output the line number from where the logging request was issued.<br/>
             * WARNING Generating caller location information is extremely slow and should be avoided unless execution speed is not an issue.</td></tr>
             *
             * <tr><td><b>m</b></td><td>Used to output the application supplied message associated with the logging event.</td></tr>
             * <tr><td><b>M</b></td><td>Used to output the method name where the logging request was issued.<br/>
             * WARNING Generating caller location information is extremely slow and should be avoided unless execution speed is not an issue.</td></tr>
             *
             * <tr><td><b>n</b></td><td>Outputs the platform dependent line separator character or characters.<br/>
             * This conversion character offers practically the same performance as using non-portable line separator strings such as "\n", or "\r\n". Thus, it is the preferred way of specifying a line separator.</td></tr>
             *
             * <tr><td><b>p</b></td><td>Used to output the priority of the logging event.</td></tr>
             * <tr><td><b>r</b></td><td>Used to output the number of milliseconds elapsed from the construction of the layout until the creation of the logging event.</td></tr>
             * <tr><td><b>t</b></td><td>Used to output the name of the thread that generated the logging event.</td></tr>
             * <tr><td><b>x</b></td><td>Used to output the NDC (nested diagnostic context) associated with the thread that generated the logging event.</td></tr>
             * <tr><td><b>X</b></td><td>Used to output the MDC (mapped diagnostic context) associated with the thread that generated the logging event. The X conversion character must be followed by the key for the map placed between braces, as in %X{clientNumber} where clientNumber is the key. The value in the MDC corresponding to the key will be output.<br/>
             *
             * See MDC class for more details.</td></tr>
             *
             * <tr><td><b>%</b></td><td>The sequence %% outputs a single percent sign.</td></tr>
             * </table>
             *
             * <p>By default the relevant information is output as is. However, with the aid of format modifiers it is possible to change the minimum field width, the maximum field width and justification.</p>
             *
             * <p>The optional format modifier is placed between the percent sign and the conversion character.</p>
             *
             * <p>The first optional format modifier is the <i>left justification flag</i> which is just the minus (-) character. Then comes the optional <i>minimum field width</i> modifier. This is a decimal constant that represents the minimum number of characters to output. If the data item requires fewer characters, it is padded on either the left or the right until the minimum width is reached. The default is to pad on the left (right justify) but you can specify right padding with the left justification flag. The padding character is space. If the data item is larger than the minimum field width, the field is expanded to accommodate the data. The value is never truncated.</p>
             *
             * <p>This behavior can be changed using the <i>maximum field width</i> modifier which is designated by a period followed by a decimal constant. If the data item is longer than the maximum field, then the extra characters are removed from the beginning of the data item and not from the end. For example, it the maximum field width is eight and the data item is ten characters long, then the first two characters of the data item are dropped. This behavior deviates from the printf function in C where truncation is done from the end.</p>
             *
             * <p>Below are various format modifier examples for the category conversion specifier.</p>
             *
             * <table>
             * <tr><th>Format modifier</th><th>left justify</th><th>minimum width</th><th>maximum width</th><th>comment</th></tr>
             * <tr><td>%20c</td><td>false</td><td>20</td><td>none</td><td>Left pad with spaces if the category name is less than 20 characters long.</td></tr>
             * <tr><td>%-20c</td><td>true</td><td>20</td><td>none</td><td>Right pad with spaces if the category name is less than 20 characters long.</td></tr>
             * <tr><td>%.30c</td><td>NA</td><td>none</td><td>30</td><td>Truncate from the beginning if the category name is longer than 30 characters.</td></tr>
             * <tr><td>%20.30c</td><td>false</td><td>20</td><td>30</td><td>Left pad with spaces if the category name is shorter than 20 characters. However, if category name is longer than 30 characters, then truncate from the beginning.</td></tr>
             * <tr><td>%-20.30c</td><td>true</td><td>20</td><td>30</td><td>Right pad with spaces if the category name is shorter than 20 characters. However, if category name is longer than 30 characters, then truncate from the beginning.</td></tr>
             * </table>
             *
             * \param event Logging event to use for data for the pattern
             * \return Formatted string using the Logging event for the pattern data
             */
            const std::string format(const LoggingEvent& event);
            /**
             * Return the current formatting pattern.
             * \return Formatting pattern.
             */
            const std::string getPattern() const { return pattern; }
            /**
             * Set the formatting pattern.
             * \param pattern Formatting pattern.
             * \return Reference to this object.
             */
            PatternLayout& setPattern(const std::string& pattern) { this->pattern = pattern; return *this; }
    };

} // hslib

#endif // _HSLIB_PATTERNLAYOUT_H_INCLUDED_
