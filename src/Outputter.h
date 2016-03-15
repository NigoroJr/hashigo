#ifndef OUTPUTTER_H_
#define OUTPUTTER_H_

#include <algorithm>
#include <fstream>
#include <iterator>
#include <sstream>
#include <streambuf>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * A class for generating outputs such as Verilog code or dot code for
 * graphviz.
 * This class is used by adding pairs of key (tag) and value (list of strings)
 * and finally giving it a template, which contains placeholders with names
 * that correspond to the tags. These placeholders are replaced by the list of
 * strings concatenated with a newline.
 */

class Outputter {
public:
    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    Outputter();

    // Copy constructor
    Outputter(const Outputter& other);

    // Move constructor
    Outputter(Outputter&& other);

    // Destructor
    ~Outputter();

    // Assignment operator
    Outputter&
    operator=(const Outputter& other);

    // Move assignment operator
    Outputter&
    operator=(Outputter&& other);
    /* }}} */

    /* Member methods */

    /**
     * Appends a new line of output to the given tag.
     *
     * \param[in] tag the tag in the template file
     *
     * \param[in] val the string to append as a new line
     */
    // TODO: parameter for indent? (default: 0)
    void
    append(const std::string& tag, const std::string& val);

    /**
     * Does the substitution of the template with the accumulated tags.
     *
     * \param[in] templ_path the path to the template to use
     *
     * \param[in] out_fn name of the file to output the Verilog code to
     */
    void
    finilize(const std::string& templ_path, const std::string& out_fn);

    /**
     * Does the substitution of the template with the accumulated tags.
     *
     * \param[in] templ_path the path to the template to use
     *
     * \param[in] os std::ostream instance used to output the resulting
     *               Verilog code
     */
    void
    finilize(const std::string& templ_path, std::ostream& os);

private:
    /**
     * Replaces the first match of a given string in a larger string.
     *
     * \param[in] haystack the original string to be replaced
     *
     * \param[in] needle the keyword to replace
     *
     * \param[in] new_needle what to replace it with
     */
    bool
    replace(std::string& haystack,
            const std::string& needle,
            const std::string& new_needle);

    /**
     * Replaces all occurrences of a given string in a larger string.
     *
     * \param[in] haystack the original string to be replaced
     *
     * \param[in] needle the keyword to replace
     *
     * \param[in] new_needle what to replace it with
     */
    void
    replace_all(std::string& haystack,
                const std::string& needle,
                const std::string& new_needle);

    std::unordered_map<std::string, std::vector<std::string>> tags;
};

#endif /* end of include guard */
