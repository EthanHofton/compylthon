#include <iostream>
#include <unistd.h>
#include <vector>

#include <cpy/cpy_config.hpp>

void version() {
    std::cout << "cpy version: " << cpy_VERSION_MAJOR << "." << cpy_VERSION_MINOR << "." << cpy_VERSION_PATCH << std::endl;
    exit(0);
}

void usage() {
    std::cout << "Usage: cpy [-c] [-s] [-v] [-o output_file] [-h] [input_files...]" << std::endl;
    exit(0);
}

int main(int argc, char** argv) {
    int c;
    bool objects_only = false;
    bool asm_only = false;
    std::string output_name = "a.out";
    std::vector<std::string> input_files;

    while ((c = getopt(argc, argv, "cso:vh")) != -1) {
        switch (c) {
            case 'c':
                objects_only = true;
                break;
            case 's':
                asm_only = true;
                break;
            case 'o':
                output_name = optarg;
                break;
            case 'v':
                version();
                break;
            case 'h':
                usage();
                break;
            case '?':
                if (optopt == 'o') {
                    std::cerr << "Option -o requires an argument." << std::endl;
                } else if (isprint(optopt)) {
                    std::cerr << "Unknown option -" << static_cast<char>(optopt) << std::endl;
                } else {
                    std::cerr << "Unknown option character" << std::endl;
                }
                usage();
            default:
                abort();
        }
    }

    // Store non-flag arguments in the input_files vector
    for (int i = optind; i < argc; ++i) {
        input_files.push_back(argv[i]);
    }

    if (input_files.empty()) {
        std::cerr << "No input files" << std::endl;
        usage();
    }

    if (objects_only && asm_only) {
        std::cerr << "Cannot specify both -c and -s" << std::endl;
        usage();
    }

    // Example: Print the flags and input_files
    // std::cout << "objects_only: " << objects_only << std::endl;
    // std::cout << "asm_only: " << asm_only << std::endl;
    // std::cout << "output_name: " << output_name << std::endl;
    //
    // std::cout << "Input files:" << std::endl;
    // for (const std::string& input_file : input_files) {
    //     std::cout << input_file << std::endl;
    // }

    return 0;
}
