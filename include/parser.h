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
    std::vector<Lexer> lexer_stack;
    Ir ir_builder;
    std::unordered_set<std::string> symbol_table;

    void parse_top_level();
    void parse_include();
    void parse_function();
    void parse_native_function();
    void parse_function_header();
    std::vector<Type> parse_type_pack();
    void parse_expression();

    Type id_to_type(Span);
    Lexer& lexer();
    std::string find_and_read_file(std::string_view);
};

#endif // ZIZL_PARSER_H
