#include "native_functions.h"

extern std::vector<native_function> registered_native_function_table = {};


// read_int :: () -> int
u64 read_int(std::vector<u64>& input) {
    static_cast<void>(input);
    i64 i;
    std::cin >> i;
    return {std::bit_cast<u64>(i)};
}

// write_int :: int -> ()
u64 write_int(std::vector<u64>& input) {
    std::cout << input.back();
    input.pop_back();
    return {};
}

void init_native_functions() {
    register_native_function(read_int);
    register_native_function(write_int);

}