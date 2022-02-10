#include "interp.h"

#include "parser.h"

Interp::Interp(Args args): args{args}, bytecode{} {
    parse_all_files();
}

void Interp::parse_all_files() {
    // FIXME is there any reason to parse multiple files independently?
    // in theory they would all textually/syntactically depend on each other for this language
    //for(auto file: args.files) {
    Parser parser{args.files[0]};
    bytecode = parser.parse();
    //}
}

int Interp::run() {
    return 0;
}