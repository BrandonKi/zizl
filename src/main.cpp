#include "common.h"

#include "interp.h"

Args parse_cmd_args(int argc, char* argv[]) {
    Args args;

    std::vector<std::string_view> arg_list(argv + 1, argv + argc);
    for(auto arg: arg_list) {
        if(arg == "-") {
            // support cmd line options in the future
        }
        else {
            args.file = arg;
        }
    }

    return args;
}

int main(int argc, char* argv[]) {
    auto args = parse_cmd_args(argc, argv);

    Interp interp{args};
    auto exit_code = interp.run();
    std::cout << "Exited with code: " << exit_code << "\n";
}