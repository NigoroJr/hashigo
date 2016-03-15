set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_package(PugiXML REQUIRED)

BISON_TARGET(HashigoParser parse.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(HashigoLexer lex.l ${CMAKE_CURRENT_BINARY_DIR}/tokens.cpp)
ADD_FLEX_BISON_DEPENDENCY(HashigoLexer HashigoParser)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(SymTable SHARED ${CMAKE_CURRENT_SOURCE_DIR}/SymTable.cpp)
add_library(Outputter SHARED ${CMAKE_CURRENT_SOURCE_DIR}/Outputter.cpp)

add_executable(hashigo main.cpp
    SymTable
    Outputter
    ${BISON_HashigoParser_OUTPUTS}
    ${FLEX_HashigoLexer_OUTPUTS})
