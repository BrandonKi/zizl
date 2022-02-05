#include "parser.h"

Parser::Parser() {

}

void Parser::parse(std::string_view filename) {
    std::string filedata = read_file(filename);
    Lexer lexer(filedata);

    Token tkn{};
    while(tkn.kind != TokenKind::end_of_file) {
        tkn = lexer.next_token();
        std::cout << tokenkind_to_string(tkn.kind) << "\n";
    }
}