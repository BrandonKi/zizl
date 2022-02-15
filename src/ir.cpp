#include "ir.h"

using enum ir_instruction;

void Ir::build_fn_def(std::string id, std::vector<Type> itypes, std::vector<Type> otypes) {
    auto address = bytecode.buffer.size();
    ir_function fn{id, itypes, otypes, address};
    function_table.push_back(fn);
    if(id == "main"sv)
        bytecode.entrypoint = address;
}

void Ir::build_add() {
    bytecode.buffer.push_back(ir_add);
}

void Ir::build_sub() {
    bytecode.buffer.push_back(ir_sub);
}

void Ir::build_mul() {
    bytecode.buffer.push_back(ir_mul);
}

void Ir::build_div() {
    bytecode.buffer.push_back(ir_div);
}

void Ir::build_mod() {
    bytecode.buffer.push_back(ir_mod);
}

void Ir::build_push(u64 imm) {
    bytecode.buffer.push_back(ir_push);
    push_imm(imm);
}

void Ir::build_pop() {
    bytecode.buffer.push_back(ir_pop);
}

void Ir::build_dup() {
    bytecode.buffer.push_back(ir_dup);
}

void Ir::build_swap() {
    bytecode.buffer.push_back(ir_swap);
}

void Ir::build_fn_call(std::string id) {
    // TODO possibly match functions depending on function args
    // although it would be pretty hard because of the nature of the language
    // it should probably be done in sema not here

    // TODO optimize (hash table maybe??)

    // find id in function_table
    u64 index = 0;
    for(auto& fn: function_table) {
        if(fn.id == id) {
            // emit a call with index from function_table
            bytecode.buffer.push_back(ir_call);
            push_imm(fn.buffer_location);
            return;
        }
    }
    assert(false);    // could not find function
}

void Ir::build_ret() {
    bytecode.buffer.push_back(ir_ret);
}

bytecode_module Ir::get_bytecode() {
    return bytecode;
}

void Ir::pretty_print_buffer() {
    for(int i = 0; i < bytecode.buffer.size(); ++i) {
        switch(bytecode.buffer[i]) {
            case ir_add:
                std::cout << "add\n";
                break;
            case ir_sub:
                std::cout << "sub\n";
                break;
            case ir_mul:
                std::cout << "mul\n";
                break;
            case ir_div:
                std::cout << "div\n";
                break;
            case ir_mod:
                std::cout << "mod\n";
                break;

            case ir_push: {
                std::cout << "push\t";
                u64 imm = 0;
                for(int x = 0; x < 8; ++x)
                    imm |= bytecode.buffer[i + x + 1] << (x * 8);
                std::cout << imm << "\n";
                i += 8;
                break;
            }
            case ir_pop:
                std::cout << "pop\n";
                break;
            case ir_dup:
                std::cout << "dup\n";
                break;
            case ir_swap:
                std::cout << "swap\n";
                break;
            case ir_call: {
                std::cout << "call\t";
                u64 imm = 0;
                for(int x = 0; x < 8; ++x)
                    imm |= bytecode.buffer[i + x + 1] << (x * 8);
                std::cout << imm << "\n";
                i += 8;
                break;
            }
            case ir_ret:
                std::cout << "ret\n";
                break;
        }
    }
}

void Ir::push_imm(u64 imm) {
    bytecode.buffer.push_back((imm & 0x00000000000000ff) >> 0);
    bytecode.buffer.push_back((imm & 0x000000000000ff00) >> 8);
    bytecode.buffer.push_back((imm & 0x0000000000ff0000) >> 16);
    bytecode.buffer.push_back((imm & 0x00000000ff000000) >> 24);
    bytecode.buffer.push_back((imm & 0x000000ff00000000) >> 32);
    bytecode.buffer.push_back((imm & 0x0000ff0000000000) >> 40);
    bytecode.buffer.push_back((imm & 0x00ff000000000000) >> 48);
    bytecode.buffer.push_back((imm & 0xff00000000000000) >> 56);
}