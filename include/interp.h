#ifndef ZIZL_INTERP_H
#define ZIZL_INTERP_H

#include "common.h"
#include "ir.h"

class Interp {
  public:
    Interp(Args);

    int run();

  private:
    Args args;
    bytecode_module bytecode;

    void parse_file();

};

#endif // ZIZL_INTERP_H
