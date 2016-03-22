#include "nodes.hpp"
#include "Outputter.h"
#include "L5XParser.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>

extern int yyparse();
extern "C" FILE* yyin;
extern std::shared_ptr<NRoot> root;

std::string
get_basename(const std::string& path) {
    char path_sep =
#ifdef _WIN32
        '\\';
#else
        '/';
#endif

    auto pos = path.rfind(path_sep);

    if (pos == std::string::npos) {
        return path;
    }

    return path.substr(pos + 1);
}

std::tuple<std::string, std::string>
get_extension(const std::string& path) {
    std::string basename = get_basename(path);

    std::string filename = "";
    std::string ext = "";

    auto pos = basename.find('.');
    if (pos != std::string::npos) {
        filename = basename.substr(0, pos);
        ext = basename.substr(pos + 1);

        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    }

    return std::make_tuple(filename, ext);
}

std::FILE*
open_hshg(const std::string& filepath) {
    std::FILE* in_file = std::fopen(filepath.c_str(), "r");

    if (!in_file) {
        std::cerr << "Couldn't open " << filepath << std::endl;
        std::exit(1);
    }

    return in_file;
}

int
main(const int argc, char* const argv[]) {
    yyin = stdin;

    std::string filepath{argv[1]};

    std::string filename, ext;
    if (argc >= 1) {
        std::tie(filename, ext) = get_extension(argv[1]);

        if (ext == "hshg") {
            yyin = open_hshg(filepath);
        }
        else if (ext == "l5x") {
            filepath = filename + ".hshg";

            L5XParser parser{argv[1]};
            parser.parse();
            parser.to_hshg(filepath);

            yyin = open_hshg(filepath);
        }
    }

    yyparse();

    SymTable s;
    root->populate_symtable(s);

    Outputter verilog_outputter;
    verilog_outputter.append("program_name", filename);
    root->to_verilog(verilog_outputter);
    verilog_outputter.finilize(std::string{argv[2]} + "/verilog/Main.v", "foo.v");

    Outputter dot_outputter;
    dot_outputter.append("program_name", filename);
    root->to_dot(dot_outputter);
    dot_outputter.finilize(std::string{argv[2]} + "/dot/ast.dot", "foo.dot");

    std::fclose(yyin);
    return 0;
}
