#include <pugixml.hpp>

#include <iostream>
#include <string>

/**
 * Parses the L5X files.
 * TODO: Better integration with other parts
 * TODO: //Tag/Data/Structure/DataValueMember
 */

static const std::string XPATH = "//Routines/Routine/RLLContent/Rung[*]";

void parse_xml(const std::string& file_name, const std::string& xpath) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file_name.c_str());
    pugi::xpath_node_set tools = doc.select_nodes(xpath.c_str());

    for (auto&& tool : tools) {
        std::cout << "Rung " << tool.node().attribute("Number").value() << std::endl;
        std::cout << tool.node().child_value("Text") << std::endl;
    }
}
