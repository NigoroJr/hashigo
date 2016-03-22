#include "L5XParser.h"

using prettify_pattern_t = L5XParser::prettify_pattern_t;

const std::string L5XParser::BASIC_XPATH = "//Routines/Routine/RLLContent/Rung[*]";
const std::string L5XParser::TIMER_NAME_XPATH = "//Tag";
const std::string L5XParser::TIMER_ADDR_XPATH = "./Data/Structure/DataValueMember";
const std::vector<prettify_pattern_t> L5XParser::PRETTIFY_PATTERNS = {
    // Add one space after closing parenthesis
    {std::regex{"\\)\\s*"},         ") "},
    // Use only one space after ']'
    {std::regex{"\\)\\s*\\]\\s*"},  ")] "},
    // Always put a space after ','
    {std::regex{"\\s*,\\s*"},       ", "},
    // No spaces after trailing semicolon
    {std::regex{"\\)\\s*;\\s*"},    ");"},
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
L5XParser::L5XParser()
    : file_path{}
    , rungs{}
{
}

L5XParser::L5XParser(const std::string& file_path)
    : file_path{file_path}
    , rungs{}
{
}

// Copy constructor
L5XParser::L5XParser(const L5XParser& other)
    : file_path{other.file_path}
    , rungs{other.rungs}
{
}

// Move constructor
L5XParser::L5XParser(L5XParser&& other)
    : file_path{std::move(other.file_path)}
    , rungs{std::move(other.rungs)}
{
}

// Destructor
L5XParser::~L5XParser()
{
}

// Assignment operator
L5XParser&
L5XParser::operator=(const L5XParser& other) {
    file_path = std::move(other.file_path);
    rungs = std::move(other.rungs);
    return *this;
}

// Move assignment operator
L5XParser&
L5XParser::operator=(L5XParser&& other) {
    file_path = std::move(other.file_path);
    rungs = std::move(other.rungs);
    return *this;
}
/* }}} */

void
L5XParser::parse() {
    basic_parse();
    timer_parse();
}

void
L5XParser::to_hshg(const std::string& fn) const {
    std::ofstream ofs{fn};

    if (!ofs.good()) {
        throw std::runtime_error{"Couldn't open file: " + fn};
    }

    to_hshg(ofs);
}

std::ostream&
L5XParser::to_hshg(std::ostream& os) const {
    // Create a string of all rungs
    auto all_rungs = prettify(rungs);
    all_rungs = replace_timers(all_rungs);

    os << all_rungs << std::flush;
    return os;
}

void
L5XParser::basic_parse() {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file_path.c_str());
    if (result.status != pugi::xml_parse_status::status_ok) {
        throw std::runtime_error{"Couldn't read L5X file"};
    }
    pugi::xpath_node_set tools = doc.select_nodes(BASIC_XPATH.c_str());

    for (auto&& tool : tools) {
        auto val = tool.node().attribute("Number").value();
        unsigned rung_count = static_cast<unsigned>(std::atoi(val));
        std::string text = tool.node().child_value("Text");

        rungs[rung_count] = text;
    }
}

void
L5XParser::timer_parse() {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file_path.c_str());
    if (result.status != pugi::xml_parse_status::status_ok) {
        throw std::runtime_error{"Couldn't read L5X file"};
    }
    pugi::xpath_node_set tools = doc.select_nodes(TIMER_NAME_XPATH.c_str());

    for (auto& tool : tools) {
        std::string name{tool.node().attribute("Name").value()};
        std::string type{tool.node().attribute("DataType").value()};

        if (type != "TIMER") {
            continue;
        }

        Timer t;
        t.name = name;

        pugi::xpath_node_set addrs = tool.node().select_nodes(TIMER_ADDR_XPATH.c_str());
        for (auto&& addr : addrs) {
            std::string addr_name{addr.node().attribute("Name").value()};
            std::string value{addr.node().attribute("Value").value()};

            if (addr_name == "PRE") {
                t.PRE = static_cast<unsigned>(std::atoi(value.c_str()));
            }
            else if (addr_name == "ACC") {
                t.ACC = static_cast<unsigned>(std::atoi(value.c_str()));
            }
            else if (addr_name == "EN") {
                t.EN = value == "1";
            }
            else if (addr_name == "TT") {
                t.TT = value == "1";
            }
            else if (addr_name == "DN") {
                t.DN = value == "1";
            }
        }

        timers.insert(t);
    }
}

std::string
L5XParser::prettify(const std::map<unsigned, std::string>& rungs) const {
    std::ostringstream oss;

    unsigned rung_num;
    std::string rung;
    for (const auto& p : rungs) {
        std::tie(rung_num, rung) = p;

        // Apply given substitutions
        std::regex re;
        std::string to_replace;
        for (const auto& replace_patterns : PRETTIFY_PATTERNS) {
            std::tie(re, to_replace) = replace_patterns;

            rung = std::regex_replace(rung, re, to_replace);
        }

        oss << rung_num << ": " << rung << std::endl;
    }

    return oss.str();
}

std::string
L5XParser::replace_timers(const std::string& rungs) const {
    // Make a copy
    std::string to_ret{std::move(rungs)};

    char buf[512];
    for (const Timer& t : timers) {
        // Extra addresses that we replace      <------->
        std::regex re{"(TO[NF])\\(" + t.name + "(,?[^)]*)\\)"};

        auto n = t.name.c_str();
        std::sprintf(buf,
                     "$1(%s, %s.PRE, %s.ACC, %s.EN, %s.TT, %s.DN)",
                     n, n, n, n, n, n);
        std::string to_replace{buf};

        to_ret = std::regex_replace(to_ret, re, to_replace);
    }

    return to_ret;
}
