#include "Outputter.h"

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
Outputter::Outputter()
    :  tags{}
{
}

// Copy constructor
Outputter::Outputter(const Outputter& other)
    : tags{other.tags}
{
}

// Move constructor
Outputter::Outputter(Outputter&& other)
    : tags{std::move(other.tags)}
{
}

// Destructor
Outputter::~Outputter()
{
}

// Assignment operator
Outputter&
Outputter::operator=(const Outputter& other) {
    tags = other.tags;
    return *this;
}

// Move assignment operator
Outputter&
Outputter::operator=(Outputter&& other) {
    tags = std::move(other.tags);
    return *this;
}
/* }}} */

void
Outputter::append(const std::string& tag, const std::string& val) {
    // Given tag is already there
    if (tags.find(tag) != tags.end()) {
        tags.at(tag).push_back(val);
    }
    else {
        typename decltype(tags)::mapped_type to_insert{val};
        tags.insert(std::make_pair(tag, to_insert));
    }
}

void
Outputter::finilize(const std::string& templ_path, const std::string& out_fn) {
    std::ofstream ofs{out_fn};

    if (!ofs.good()) {
        throw std::runtime_error{"Couldn't open output file: " + out_fn};
    }

    finilize(templ_path, ofs);
}

void
Outputter::finilize(const std::string& templ_path, std::ostream& os) {
    // Read in the template
    std::ifstream ifs{templ_path};

    if (!ifs.good()) {
        throw std::runtime_error{"Couldn't open template file: " + templ_path};
    }

    std::string out_verilog;
    std::istreambuf_iterator<char> isit{ifs}, dummy;
    // Note: This can be slow on a large input file
    std::copy(isit, dummy, std::back_inserter(out_verilog));
    ifs.close();

    // Replace all tags with (partial) Verilog code
    std::string tag;
    std::vector<std::string> vals;
    for (const auto& p : tags) {
        std::stringstream ss;
        std::tie(tag, vals) = p;

        // Join each value of tag with a newline character
        for (const auto& v : vals) {
            ss << v << std::endl;
        }

        ss.flush();
        replace_all(out_verilog, "${" + tag + "}", ss.str());
    }

    os << out_verilog << std::flush;
}

bool
Outputter::replace(std::string& haystack,
                  const std::string& needle,
                  const std::string& new_needle) {
    auto ind = haystack.find(needle);
    if (ind == std::string::npos) {
        return false;
    }

    haystack.replace(ind, needle.length(), new_needle);
    return true;
}

void
Outputter::replace_all(std::string& haystack,
                       const std::string& needle,
                       const std::string& new_needle) {
    while (replace(haystack, needle, new_needle)) {
        // Keep looping
    }
}
