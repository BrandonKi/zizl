#include "Common.h"

Args parse_cmd_args(int argc, char* argv[]) {
    Args args;

    std::vector<std::string_view> arg_list(argv, argv + argc);
    for(auto arg: arg_list) {
        if(arg == "-") {
            // support cmd line options in the future
        }
        else {
            arg_list.file.push_back(arg);
        }
    }

    return args;
}

int main(int argc, char* argv[]) {
    auto args = parse_cmd_args(argc, argv);

    Interp interp{args};
    std::cout << "Exited with code: " << interp.run() << "\n";
}