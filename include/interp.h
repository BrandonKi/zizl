#ifndef ZIZL_INTERP_H
#define ZIZL_INTERP_H

#include "common.h"

class Interp {
  public:
    Interp(Args args): args{args} {}

    int run();

  private:
    Args args;

    void parse_all_files();

};

#endif // ZIZL_INTERP_H
