#include "nodes.hpp"
#include "Outputter.h"

#include <iostream>
#include <cstdlib>
#include <memory>

extern int yyparse();
extern "C" FILE* yyin;
extern std::shared_ptr<NRoot> root;

int
main(const int argc, char* const argv[]) {
    FILE* in_file = stdin;
    if (argc >= 1) {
        in_file = fopen(argv[1], "r");
    }

    if (!in_file) {
        std::cerr << "Couldn't open file" << std::endl;
        return 1;
    }

    yyin = in_file;

    yyparse();

    std::cout << root << std::endl;

    Outputter o;
    o.append("program_name", "CarWash");
    o.append("rungs", "0: begin\n    foo = bar;\nend");
    o.append("rungs", "1: begin\n    baz = qux;\nend");
    o.finilize(argv[2], "foo.v");

    return 0;
}
