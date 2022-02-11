#ifndef ZIZL_IR_H
#define ZIZ_IR_H
#include "common.h"

enum ir_instruction: u8 {
    ir_add,
    ir_sub,
    ir_mul,
    ir_div,
    ir_mod,

    ir_push,
    ir_pop,
    ir_dup,
    ir_swap,

    ir_if,      //
    ir_else,    // need to figure out how these will work
    ir_then,    // lowering control flow to raw jumps seems easiest
    ir_call,
    ir_ret,
};

struct ir_function {
    std::string id;
    std::vector<Type> input_types;
    std::vector<Type> output_types;
    u64 buffer_location;
};

class Ir {
  public:
    Ir(): function_table{}, bytecode_buffer{} {}

    void build_fn_def(std::string, std::vector<Type>, std::vector<Type>);

    void build_add();
    void build_sub();
    void build_mul();
    void build_div();
    void build_mod();

    void build_push(u64);
    void build_pop();
    void build_dup();
    void build_swap();

    void build_fn_call(std::string);
    void build_ret();

    std::vector<u8> get_bytecode_buffer();
    void pretty_print_buffer();
    void push_imm(u64);

  private:
    std::vector<ir_function> function_table;
    std::vector<u8> bytecode_buffer;

};

#endif // ZIZL_IR_H
