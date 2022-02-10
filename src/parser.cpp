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
    while(!lexer.expect_token(TokenKind::ret)) {

    }
}


// TODO implement this
Type Parser::id_to_type(Span id) {
    return Type::zizl_int;
}

