#ifndef ZIZL_LEXER_H
#define ZIZL_LEXER_H
#include "common.h"

class Lexer {
  public:
    Lexer();

    Token peek_token();
    Token next_token();
    Token current_token();
    Token check_token(Token);

};

#endif // ZIZL_LEXER_H
