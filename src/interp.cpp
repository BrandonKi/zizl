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
    std::vector<u64> stack;
    for(int i = 0; i < bytecode.size(); ++i) {
        switch(bytecode[i]) {
            case ir_add: {
                auto arg2 = stack.back();
                stack.pop_back();
                auto arg1 = stack.back();
                stack.back() = arg2 + arg1;
                break;
            }
            case ir_sub: {
                auto arg1 = stack.back();
                stack.pop_back();
                auto arg2 = stack.back();
                stack.back() = arg2 - arg1;
                break;
            }
            case ir_mul:
            case ir_div:
            case ir_mod:
                assert(false);
            case ir_push: {
                u64 imm = 0;
                for(int x = 0; x < 8; ++x)
                    imm |= bytecode[i + x + 1] << (x * 8);
                i += 8;
                stack.push_back(imm);
                break;
            }
            case ir_pop:
            case ir_dup:
            case ir_swap:
                assert(false);
            case ir_call:
                assert(false);
            case ir_ret:
                return stack.back();
            default:
                assert(false);
        }
    }
    return 0;
}