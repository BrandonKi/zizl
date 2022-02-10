#include "parser.h"

Parser::Parser(std::string_view filename): lexer{read_file(filename)}, ir_builder{} {

}

std::vector<u8> Parser::parse() {
    parse_top_level();
/*
    Token tkn{};
    while(tkn.kind != TokenKind::end_of_file) {
        tkn = lexer.next_token();
        std::cout << tokenkind_to_string(tkn.kind) << "\n";
    }
*/

    return ir_builder.get_bytecode_buffer();
}

void Parser::parse_top_level() {
    if(lexer.check_token(TokenKind::id))
        parse_function();
}

// HEADER:
//     id :: type_pack -> type_pack
// BODY:
//     expression
void Parser::parse_function() {
    parse_function_header();
    parse_expression();
    ir_builder.pretty_print_buffer();
}

void Parser::parse_function_header() {
    Token id = lexer.current_token();
    lexer.next_token();
    lexer.verify_token(TokenKind::double_colon);
    auto itypes = parse_type_pack();
    lexer.verify_token(TokenKind::arrow);
    auto otypes = parse_type_pack();
    // TODO pass id, itypes, and otypes
    ir_builder.start_function();
}

// ()
// id
// (id)
// (id, id, id)
// id, id, id
std::vector<Type> Parser::parse_type_pack() {
    std::vector<Type> result;
    bool in_paren = false;
    if(lexer.expect_token(TokenKind::left_paren))
        in_paren = true;
    if(lexer.check_token(TokenKind::id)) {
        while(true) {
            if(lexer.check_token(TokenKind::id)) {
                result.push_back(id_to_type(lexer.current_token().span));
                lexer.next_token();
            }
            if(lexer.check_token(TokenKind::comma))
                lexer.next_token();
            else if(lexer.expect_token(TokenKind::right_paren) && in_paren)
                return result;
            else if(!in_paren)
                return result;
            else
               assert(false);
        }
    }
    else if(lexer.expect_token(TokenKind::right_paren))
        return result;
    else
        assert(false);
    return result;
}

void Parser::parse_expression() {
    using enum TokenKind;
    while(true) {
        switch(lexer.current_token().kind) {
            case int_literal:
                ir_builder.build_push(10);    // TODO convert to int
                break;
            case float_literal:
            case string_literal:
            case id:
                assert(false);

            case add:
                ir_builder.build_add();
                break;
            case sub:
                ir_builder.build_sub();
                break;
            case mul:
                ir_builder.build_mul();
                break;
            case div:
                ir_builder.build_div();
                break;
            case mod:
                ir_builder.build_mod();
                break;
            case less_than:
            case greater_than:
                assert(false);
                break;

            case dup:
                ir_builder.build_dup();
                break;
            case pop:
                ir_builder.build_pop();
                break;
            case swap:
                ir_builder.build_swap();
                break;

            //colon,
            //double_colon,
            //left_paren,
            //right_paren,
            //arrow,
            //comma,

            case ret:
                ir_builder.build_ret();
                return;
            case end_of_file:
                break;
            default:
                assert(false);
        }
        lexer.next_token();
    }
}


// TODO implement this
Type Parser::id_to_type(Span id) {
    return Type::zizl_int;
}

