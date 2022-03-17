#ifndef ZIZL_NATIVE_FUNCTIONS_H
#define ZIZL_NATIVE_FUNCTIONS_H
#include "common.h"

extern std::vector<native_function> registered_native_function_table;

#define register_native_function(fn_name)                       \
    do {                                                        \
        auto fn = native_function{#fn_name, {}, {}, &fn_name};  \
        registered_native_function_table.push_back(fn);         \
    } while(0);                                                 \

void init_native_functions();

#endif  // ZIZL_NATIVE_FUNCTIONS_H