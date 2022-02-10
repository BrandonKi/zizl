#ifndef ZIZL_INTERP_H
#define ZIZL_INTERP_H

#include "common.h"

class Interp {
  public:
    Interp(Args);

    int run();

  private:
    Args args;
    std::vector<u8> bytecode;

    void parse_all_files();

};

#endif // ZIZL_INTERP_H
