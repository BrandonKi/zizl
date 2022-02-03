#ifndef ZIZL_COMMON_H
#define ZIZL_COMMON_H

#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <string_view>

struct Args {
    std::vector<std::string> files;
};

enum class TokenKind {
    int_literal,
    float_literal,
    string_literal,
    identifier,

    add,
    sub,
    mul,
    div,
    mod,
    less_than,
    greater_than,

    dup,
    pop,

    colon,
    double_colon,
    left_paren,
    right_paren,
    arrow,

};

struct Token {

};

#endif // ZIZL_COMMON_H
