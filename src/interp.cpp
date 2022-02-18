#include "interp.h"

#include "parser.h"

// TODO support signed versions of these
#define BIN_OP(op)    do {                             \
                          auto arg2 = stack.back();    \
                          stack.pop_back();            \
                          auto arg1 = stack.back();    \
                          stack.back() = arg1 op arg2; \
                      } while(0)

Interp::Interp(Args args): args{args}, bytecode{} {
    parse_file();
}

void Interp::parse_file() {
    Parser parser{args.file};
    bytecode = parser.parse();
}

int Interp::run() {
    std::vector<u64> stack;
    std::vector<u64> call_stack;

    for(i64 i = bytecode.entrypoint; i < bytecode.buffer.size(); ++i) {
        switch(bytecode.buffer[i]) {
            case ir_add:
                BIN_OP(+);
                break;
            case ir_sub:
                BIN_OP(-);
                break;
            case ir_mul:
                BIN_OP(*);
                break;
            case ir_div:
                BIN_OP(/);
                break;
            case ir_mod:
                BIN_OP(%);
                break;
            case ir_push: {
                u64 imm = 0;
                for(int x = 0; x < 8; ++x)
                    imm |= bytecode.buffer[i + x + 1] << (x * 8);
                i += 8;
                stack.push_back(imm);
                break;
            }
            case ir_pop:
                stack.pop_back();
                break;
            case ir_dup:
                stack.push_back(stack.back());
                break;
            case ir_swap:
                std::iter_swap(stack.end() - 2, stack.end() - 1);
                break;
            case ir_call: {
                u64 imm = 0;
                for(int x = 0; x < 8; ++x)
                    imm |= bytecode.buffer[i + x + 1] << (x * 8);
                i += 8;
                call_stack.push_back(i);
                // TODO underflow?
                i = (i64)imm - 1;
                break;
            }
            case ir_ret:
                if(call_stack.empty())
                    return stack.back();
                else {
                    auto ret_addr = call_stack.back();
                    call_stack.pop_back();
                    i = ret_addr;
                    break;
                }
            default:
                assert(false);
        }
    }
    return 0;
}