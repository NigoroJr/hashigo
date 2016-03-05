find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(HashigoParser parse.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(HashigoLexer lex.l ${CMAKE_CURRENT_BINARY_DIR}/tokens.cpp)
ADD_FLEX_BISON_DEPENDENCY(HashigoLexer HashigoParser)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(hashigo main.cpp
    ${BISON_HashigoParser_OUTPUTS}
    ${FLEX_HashigoLexer_OUTPUTS})
