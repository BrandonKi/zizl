#ifndef ZIZL_LEXER_H
#define ZIZL_LEXER_H
#include "common.h"

class Lexer {
  public:
    Lexer(std::string_view);

    Token lex_token();

    Token peek_token();
    Token next_token();
    Token current_token();
    Token check_token(Token);

  private:
    std::string_view filedata;
    i64 index;
    Token last_token;

    Token lex_id();
    Token lex_number();
    Token lex_colon();
    Token lex_dash();

    void consume_comment();
};

#endif // ZIZL_LEXER_H
