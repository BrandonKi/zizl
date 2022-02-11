#ifndef ZIZL_COMMON_H
#define ZIZL_COMMON_H

#include "span.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <utility>
#include <memory>
#include <string_view>
#include <charconv>
#include <unordered_map>
#include <cstdint>
#include <cassert>

using namespace std::literals;

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

struct Args {
    std::vector<std::string_view> files;
};

enum class TokenKind {
    none,
    int_literal,
    float_literal,
    string_literal,
    id,

    add,
    sub,
    mul,
    div,
    mod,
    less_than,
    greater_than,

    dup,
    pop,
    swap,

    colon,
    double_colon,
    left_paren,
    right_paren,
    arrow,
    comma,

    call,
    ret,

    end_of_file,
};

enum Type {
    zizl_int,
};

struct Token {
    Span span;
    TokenKind kind;
};

inline std::unordered_map<std::string_view, TokenKind> keywords = {
    {"ret"sv, TokenKind::ret},
};

inline TokenKind get_keyword(Span span) {
    std::string_view str = static_cast<std::string_view>(span);
    auto search = keywords.find(str);
    if (search == keywords.end())
        return TokenKind::none;
    return search->second;
}

[[nodiscard]] inline std::string read_file(std::string_view filepath) {
    std::ifstream file;
    file.open(filepath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return std::string(buffer.str());
}

inline bool is_alpha_numeric(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

inline bool is_number(char c) {
    return c >= '0' && c <= '9';
}

inline std::string_view tokenkind_to_string(TokenKind kind) {
    using enum TokenKind;

    switch(kind) {
        case int_literal:
            return "int_literal"sv;
        case float_literal:
            return "float_literal"sv;
        case string_literal:
            return "string_literal"sv;
        case id:
            return "identifier"sv;

        case add:
            return "add"sv;
        case sub:
            return "sub"sv;
        case mul:
            return "mul"sv;
        case div:
            return "div"sv;
        case mod:
            return "mod"sv;
        case less_than:
            return "less_than"sv;
        case greater_than:
            return "greater_than"sv;

        case dup:
            return "dup"sv;
        case pop:
            return "pop"sv;
        case swap:
            return "swap"sv;

        case colon:
            return "colon"sv;
        case double_colon:
            return "double_colon"sv;
        case left_paren:
            return "left_paren"sv;
        case right_paren:
            return "right_paren"sv;
        case arrow:
            return "arrow"sv;
        case comma:
            return "comma"sv;
        case call:
            return "call"sv;
        case ret:
            return "ret"sv;
        case end_of_file:
            return "end_of_file"sv;
        default:
            assert(false);
            return ""sv;
    }
}

#endif // ZIZL_COMMON_H
