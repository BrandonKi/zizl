#ifndef ZIZL_LEXER_H
#define ZIZL_LEXER_H
#include "common.h"

class Lexer {
  public:
    Lexer(std::string);

    Token lex_token();

    Token peek_token();
    Token next_token();
    Token current_token();
    bool check_token(TokenKind);
    bool check_next_token(TokenKind);
    bool expect_token(TokenKind);
    bool verify_token(TokenKind);

    bool has_token();

  private:
    std::string filedata;
    char* index;
    Token last_token;

    Token lex_id();
    Token lex_number();
    Token lex_colon();
    Token lex_dash();

    void consume_comment();
};

#endif // ZIZL_LEXER_H
