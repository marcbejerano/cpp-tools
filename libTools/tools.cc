#include <Tools>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/stat.h>

std::string& hslib::ltrim(std::string& str) {
    auto it2 = std::find_if(str.begin(), str.end(), [](char ch){ return !std::isspace<char>(ch, std::locale::classic()); });
    str.erase(str.begin(), it2);
    return str;   
}

std::string& hslib::rtrim(std::string& str)
{
    auto it1 = std::find_if(str.rbegin(), str.rend(), [](char ch){ return !std::isspace<char>(ch, std::locale::classic()); });
    str.erase(it1.base(), str.end());
    return str;   
}

std::string& hslib::trim(std::string& str)
{
    return hslib::ltrim(hslib::rtrim(str));
}

std::string hslib::trim_copy(std::string const& str)
{
    auto s = str;
    return hslib::ltrim(hslib::rtrim(s));
}

bool hslib::startsWith(const std::string& haystack, const std::string& needle)
{
    bool result = false;
    if (needle.length() <= haystack.length())
        result = (haystack.substr(0, needle.length()) == needle);
    return result;
}

bool hslib::endsWith(const std::string& haystack, const std::string& needle)
{
    bool result = false;
    if (needle.length() <= haystack.length())
        result = (haystack.substr(haystack.length() - needle.length(), needle.length()) == needle);
    return result;
}

/**
 * Determine if the given file (filename) exists in the file system.
 * \param filename Filename, full filepath, or relative filepath.
 * \return True if the file (or directory) exists
 */
bool hslib::fileExists(const std::string& filename)
{
    struct stat buffer;
    int rc = stat(filename.c_str(), &buffer);
    return (rc == 0);
}

/**
 * Split a string into a vector of substrings using the given delimiter
 * as a separator.
 * \param text String to split
 * \param delim Member delimiter
 * \return Vector of string tokens
 */
std::vector<std::string> hslib::split(const std::string& text, const char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(text);
    std::string token;
    while (std::getline(ss, token, delim)) {
        result.push_back(token);
    }
    return result;
}

