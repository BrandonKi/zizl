#include "parser.h"

Parser::Parser(std::string_view filename): lexer_stack{}, ir_builder{} {
    lexer_stack.push_back(read_file(filename));
}

bytecode_module Parser::parse() {
    parse_top_level();
    ir_builder.pretty_print_buffer();
    return ir_builder.get_bytecode();
}

void Parser::parse_top_level() {
    if(lexer().expect_token(TokenKind::include))
        parse_include();
    while(lexer().check_token(TokenKind::id))
        parse_function();

    // if we are still parsing includes
    if(lexer_stack.size() != 1) {
        lexer_stack.pop_back();
        parse_top_level();
    }
}

// include id
void Parser::parse_include() {
    std::string id = std::string(lexer().current_token().span) + ".zizl";
    lexer().next_token();
    lexer_stack.push_back(read_file(id));
}

// HEADER:
//     id :: type_pack -> type_pack
// BODY:
//     expression
void Parser::parse_function() {
    parse_function_header();
    parse_expression();
}

// id :: type_pack -> type_pack
void Parser::parse_function_header() {
    // TODO speed
    std::string id = std::string(lexer().current_token().span);
    lexer().next_token();
    lexer().verify_token(TokenKind::double_colon);
    auto itypes = parse_type_pack();
    lexer().verify_token(TokenKind::arrow);
    auto otypes = parse_type_pack();
    ir_builder.build_fn_def(id, std::move(itypes), std::move(otypes));
}

// ()
// id
// (id)
// (id, id, id)
// id, id, id
std::vector<Type> Parser::parse_type_pack() {
    std::vector<Type> result;
    bool in_paren = false;
    if(lexer().expect_token(TokenKind::left_paren))
        in_paren = true;
    if(lexer().check_token(TokenKind::id)) {
        while(true) {
            if(lexer().check_token(TokenKind::id)) {
                result.push_back(id_to_type(lexer().current_token().span));
                lexer().next_token();
            }
            if(lexer().check_token(TokenKind::comma))
                lexer().next_token();
            else if(lexer().expect_token(TokenKind::right_paren) && in_paren)
                return result;
            else if(!in_paren)
                return result;
            else
               assert(false);
        }
    }
    else if(lexer().expect_token(TokenKind::right_paren))
        return result;
    else
        assert(false);
    return result;
}

void Parser::parse_expression() {
    using enum TokenKind;
    while(true) {
        auto token = lexer().current_token();
        auto span = token.span;
        switch(token.kind) {
            case int_literal: { // TODO signed literals
                u64 result;
                auto [ptr, ec] {std::from_chars(span.start, span.end, result)};
                if (ec != std::errc())
                    assert(false);
                ir_builder.build_push(result);
                break;
            }
            case float_literal:
            case string_literal:
                assert(false);
            case id:
                // if the id is part of the next function definition
                // then insert a ret and move on
                if(lexer().check_next_token(TokenKind::double_colon)) {
                    ir_builder.build_ret();
                    return;
                }
                // TODO speed
                ir_builder.build_fn_call(std::string(span));
                break;
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
                lexer().next_token();
                return;
            case end_of_file:
                ir_builder.build_ret();
                return;
            default:
                assert(false);
        }
        lexer().next_token();
    }
}


// TODO implement this
Type Parser::id_to_type(Span id) {
    return Type::zizl_int;
}

Lexer& Parser::lexer() {
    return lexer_stack.back();
}