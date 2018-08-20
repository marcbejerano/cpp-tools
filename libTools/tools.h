#ifndef _HSLIB_TOOLS_H_INCLUDED_
#define _HSLIB_TOOLS_H_INCLUDED_

#include <algorithm>
#include <string>
#include <vector>

namespace hslib {

    /**
     * Remove all whitespace from the left side of the given string. This
     * function will update the given string in-place.
     * \param str String to trim
     * \return Trimmed string
     */
    std::string& ltrim(std::string& str);
    /**
     * Remove all whitespace from the right side of the given string. This
     * function will update the given string in-place.
     * \param str String to trim
     * \return Trimmed string
     */
    std::string& rtrim(std::string& str);
    /**
     * Remove all whitespace from the both sides of the given string. This
     * function will update the given string in-place.
     * \param str String to trim
     * \return Trimmed string
     */
    std::string& trim(std::string& str);
    /**
     * Remove all whitespace from the both sides of the given string. This
     * function will make a copy of the given string and return the trimmed
     * version of the copy. The original will be untouched.
     * \param str String to trim
     * \return Trimmed string
     */
    std::string trim_copy(std::string const & str);
    /**
     * Determine if the haystack string begins with the needle string.
     * \param haystack String to check
     * \param needle String to search for
     * \return True if the haystack starts with needle
     */
    bool startsWith(const std::string& haystack, const std::string& needle);
    /**
     * Determine if the haystack string ends with the needle string.
     * \param haystack String to check
     * \param needle String to search for
     * \return True if the haystack ends with needle
     */
    bool endsWith(const std::string& haystack, const std::string& needle);
    /**
     * Determine if the given file (filename) exists in the file system.
     * \param filename Filename, full filepath, or relative filepath.
     * \return True if the file (or directory) exists
     */
    bool fileExists(const std::string& filename);
    /**
     * Split a string into a vector of substrings using the given delimiter
     * as a separator.
     * \param text String to split
     * \param delim Member delimiter
     * \return Vector of string tokens
     */
    std::vector<std::string> split(const std::string& text, const char delim= ',');

} // hslib

#endif // _HSLIB_TOOLS_H_INCLUDED_

