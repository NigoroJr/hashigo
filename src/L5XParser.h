#ifndef L5XPARSER_H_
#define L5XPARSER_H_

#include "l5x/Timer.hpp"

#include <pugixml.hpp>

#include <fstream>
#include <map>
#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_set>

/**
 * Parses the L5X files.
 */
class L5XParser {
public:
    using prettify_pattern_t = std::pair<std::regex, std::string>;

    static const std::string BASIC_XPATH;
    static const std::string TIMER_NAME_XPATH;
    static const std::string TIMER_ADDR_XPATH;
    static const std::vector<prettify_pattern_t> PRETTIFY_PATTERNS;

    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    L5XParser();

    /**
     * Path to the L5X file to parse.
     */
    L5XParser(const std::string& file_path);

    // Copy constructor
    L5XParser(const L5XParser& other);

    // Move constructor
    L5XParser(L5XParser&& other);

    // Destructor
    ~L5XParser();

    // Assignment operator
    L5XParser&
    operator=(const L5XParser& other);

    // Move assignment operator
    L5XParser&
    operator=(L5XParser&& other);
    /* }}} */

    /**
     * Parses the L5X file by finding the basic rung structures and the
     * additional information regarding timers.
     * This method internally calls the basic_parse and timer_parse for these
     * two operations.
     */
    void
    parse();

    /**
     * Outputs the parsed Ladder Logic to a file in a format that can be
     * parsed by the parser.
     */
    void
    to_hshg(const std::string& fn) const;

    /**
     * Outputs the parsed Ladder Logic to a stream in a format that can be
     * parsed by the parser.
     */
    std::ostream&
    to_hshg(std::ostream& os) const;

// private:
    /**
     * Parses the basic rung structures.
     * The basic rung structure is the sequence of instructions followed by
     * addresses. For example, XIC(Local.4:I)OTE(Local.3:O); can be a rung.
     */
    void
    basic_parse();

    /**
     * Parses the information pertaining to timers.
     * In an L5X file, the numbers for the timers (such as how much time it
     * needs to wait) are not embedded in the basic rung structures; rather,
     * they are at a different location. This method reads that information
     * and populates the data structure so that the output file contains those
     * values.
     */
    void
    timer_parse();

    /**
     * Removes redundant spaces, adds spaces where necessary to make the
     * output more readable.
     *
     * \return the prettified string
     */
    std::string
    prettify(const std::map<unsigned, std::string>& rungs) const;

    std::string
    replace_timers(const std::string& rungs) const;

    std::string file_path;

    // There is a "Number" attribute in the L5X so map is used instead of
    // a vector
    std::map<unsigned, std::string> rungs;

    std::unordered_set<Timer> timers;
};

#endif /* end of include guard */
