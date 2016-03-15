#include "nodes.hpp"
#include "Outputter.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

extern int yyparse();
extern "C" FILE* yyin;
extern std::shared_ptr<NRoot> root;

std::string
get_extension(const std::string& filename) {
    std::string ext = "";

    auto pos = filename.find('.');
    if (pos != std::string::npos) {
        ext = filename.substr(pos + 1);

        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    }

    return ext;
}

int
main(const int argc, char* const argv[]) {
    yyin = stdin;

    if (argc >= 1) {
        std::string ext = get_extension(argv[1]);

        if (ext == "hshg") {
            FILE* in_file = fopen(argv[1], "r");

            if (!in_file) {
                std::cerr << "Couldn't open " << argv[1] << std::endl;
                return 1;
            }

            yyin = in_file;
        }
        else if (ext == "l5x") {
            // TODO: parse l5x file and pipe it into the parser
        }
    }

    // yyparse();

    Visitor v;

    std::cout << root << std::endl;
    root->traverse(v);

    Outputter o;
    o.append("program_name", "CarWash");
    o.append("rungs", "0: begin\n    foo = bar;\nend");
    o.append("rungs", "1: begin\n    baz = qux;\nend");
    o.finilize(argv[2], "foo.v");

    return 0;
}
