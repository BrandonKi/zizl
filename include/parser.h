#ifndef ZIZL_PARSER_H
#define ZIZL_PARSER_H

#include "common.h"

#include "lexer.h"
#include "ir.h"

class Parser {
  public:
    Parser(std::string_view);

    bytecode_module parse();

  private:
    Lexer lexer;
    Ir ir_builder;

    void parse_top_level();
    void parse_function();
    void parse_function_header();
    std::vector<Type> parse_type_pack();
    void parse_expression();

    Type id_to_type(Span);
};

#endif // ZIZL_PARSER_H
