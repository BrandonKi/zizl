#include "lexer.h"

Lexer::Lexer(std::string filedata): filedata{filedata}, index{this->filedata.data()}, last_token{lex_token()} {

}

Token Lexer::lex_token() {

    while(index < filedata.data() + filedata.size()) {
        switch(*index) {
            case '\n':
            case ' ':
                ++index;
                break;
            case '!':
                assert(false);
            case '"':
                assert(false);
            case '#':
                consume_comment();
                break;
            case '$':
                assert(false);
            case '%':
                return Token{Span{index, index++}, TokenKind::mod};
            case '&':
                assert(false);
            case '\'':
                assert(false);
            case '(':
                return Token{Span{index, index++}, TokenKind::left_paren};
            case ')':
                return Token{Span{index, index++}, TokenKind::right_paren};
            case '*':
                return Token{Span{index, index++}, TokenKind::mul};
            case '+':
                return Token{Span{index, index++}, TokenKind::add};
            case ',':
                return Token{Span{index, index++}, TokenKind::comma};
            case '-':
                return lex_dash();
            case '.':
                assert(false);
            case '/':
                return Token{Span{index, index++}, TokenKind::div};
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return lex_number();
            case ':':
                return lex_colon();
            case ';':
                assert(false);
            case '<':
                return Token{Span{index, index++}, TokenKind::less_than};
            case '=':
            case '>':
                return Token{Span{index, index++}, TokenKind::greater_than};
            case '?':
                assert(false);
            case '@':
                assert(false);
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'H':
            case 'I':
            case 'J':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'Q':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
                return lex_id();
            case '[':
                assert(false);
            case '\\':
                assert(false);
            case ']':
                assert(false);
            case '^':
                assert(false);
            case '_':
                assert(false);
            case '`':
                assert(false);
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                return lex_id();
            case '{':
                assert(false);
            case '|':
                assert(false);
            case '}':
                assert(false);
            case '~':
                assert(false);
            default:
                assert(false);
        }
    }
    return Token{Span{index, index}, TokenKind::end_of_file};
}

Token Lexer::lex_id() {
    char* span_start = index;

    while(is_alpha_numeric(*(index++))) {}

    Span span{span_start, index - 1};

    if(TokenKind kind = get_keyword(span); kind != TokenKind::none)
        return Token{span, kind};

    return Token{span, TokenKind::id};
}

// TODO should handle floats too
Token Lexer::lex_number() {
    char* span_start = index;

    while(is_number(*(index++))) {}

    return Token{Span{span_start, index - 1}, TokenKind::int_literal};
}

Token Lexer::lex_colon() {
    char* span_start = index;

    if(*(index + 1) == ':') {
        index += 2;
        return Token{Span{span_start, index}, TokenKind::double_colon};
    }
    else
        return Token{Span{span_start, index++}, TokenKind::colon};
}

Token Lexer::lex_dash() {
    char* span_start = index;

    if(*(index + 1) == '>') {
        index += 2;
        return Token{Span{span_start, index}, TokenKind::arrow};
    }
    else
        return Token{Span{span_start, index++}, TokenKind::sub};
}

void Lexer::consume_comment() {
    while(*(index++) != '\n') {}
}

Token Lexer::peek_token() {
    char* start_index = index;
    auto token = lex_token();
    index = start_index;
    return token;
}

Token Lexer::next_token() {
    last_token = lex_token();
    return last_token;
}

Token Lexer::current_token() {
    return last_token;
}

bool Lexer::check_token(TokenKind kind) {
    if(kind == current_token().kind) {
        return true;
    }
    return false;
}

bool Lexer::expect_token(TokenKind kind) {
    if(check_token(kind)) {
        next_token();
        return true;
    }
    return false;
}


bool Lexer::verify_token(TokenKind kind) {
    if(check_token(kind)) {
        next_token();
        return true;
    }
    assert(false);
}