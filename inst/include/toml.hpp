#ifndef INCLUDIZE_TOML_HPP
#define INCLUDIZE_TOML_HPP

#include "includize.hpp"
#include <regex>

namespace includize
{
    
template< typename CHAR_TYPE >
struct toml_spec
{
};

template<>
struct toml_spec< char >
{
    static constexpr char header_start() { return '#'; }
    static constexpr const char *regex()
    {
        return R"..(\s*\[\[include\s*"(([^"]|\")+)"\s*]])..";
    }
    
    static constexpr std::size_t file_name_index() { return 1; };
    static constexpr bool discard_characters_after_include() { return true; }
    
    static std::string unescape_filename(const std::string &str)
    {
        return std::regex_replace(str, std::regex("\\\\\""), "\"");
    }
};

template<>
struct toml_spec< wchar_t >
{
    static constexpr wchar_t header_start() { return L'#'; }
    static constexpr const wchar_t *regex()
    {
        return LR"..(\s*\[\[include\s*"(([^"]|\")+)"\s*]])..";
    }
    
    static constexpr std::size_t file_name_index() { return 1; };
    static constexpr bool discard_characters_after_include() { return true; }
    
    static std::string unescape_filename(const std::string &str)
    {
        return std::regex_replace(str, std::regex("\\\\\""), "\"");
    }
};

template< typename CHAR_T, typename TRAITS = std::char_traits< CHAR_T > >
using basic_toml_streambuf = basic_streambuf< toml_spec< CHAR_T >, CHAR_T, TRAITS >;

using toml_streambuf = basic_toml_streambuf< char >;
using wtoml_streambuf = basic_toml_streambuf< wchar_t >;

template< typename CHAR_T, typename TRAITS = std::char_traits< CHAR_T > >
using basic_toml_preprocessor = basic_preprocessor< toml_spec< CHAR_T >, CHAR_T, TRAITS >;

using toml_preprocessor = basic_toml_preprocessor< char >;
using wtoml_preprocessor = basic_toml_preprocessor< wchar_t >;
    
} // namespace includize

#endif