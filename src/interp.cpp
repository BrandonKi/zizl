#include "interp.h"

#include "parser.h"

Interp::Interp(Args args): args{args} {
    parse_all_files();
}

int Interp::run() {
    return 0;
}

void Interp::parse_all_files() {
    Parser parser;
    // is there any reason to parse multiple files independently?
    // in theory they would all textually/syntactically depend on each other for this language
    for(auto file: args.files)
        parser.parse(file);
}