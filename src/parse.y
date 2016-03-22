%{
    #include "nodes.hpp"

    #include <memory>
    #include <string>
    #include <vector>

    extern "C" int yylex();
    extern "C" unsigned rung_count;

    std::shared_ptr<NRoot> root;
    unsigned rung_count = 0;

    void yyerror(const char* s) {
        fprintf(stderr,
                "Error at rung %d: %s\n",
                rung_count,
                s);
        std::exit(1);
    }
%}

%union {
    NRung* rung;
    NBlockish* blockish;
    NSequence* sequences;
    NParallel* parallels;
    NSegment* segment;
    NBlock* block;
    NInstruction* inst;
    NAddress* address;
    std::vector<NAddress*>* address_vec;

    int integer;
    std::string* string;
    int token;
}

%token <string> T_INSTRUCTION T_ADDRESS
%token <integer> T_INTEGER
%token <token> T_LPAREN T_RPAREN T_LBRACKET T_RBRACKET
%token <token> T_COMMA T_SEMICOLON T_COLON

%type <rung> rung
%type <blockish> blockish
%type <sequences> sequences
%type <parallels> parallels
%type <segment> segment
%type <block> block
%type <inst> inst
%type <address> address
%type <address_vec> addresses
%type <token> sep

%start program

%%

program     : rungs
            ;

rungs       : rungs rung
                {
                    root->rungs.push_back($2);
                }
            | rung
                {
                    root = std::make_shared<NRoot>();
                    root->rungs.push_back($1);
                }
            ;

rung        : blockish T_SEMICOLON
                {
                    $$ = new NRung($1, rung_count);
                    rung_count++;
                }
            | T_INTEGER T_COLON blockish T_SEMICOLON
                {
                    rung_count = static_cast<unsigned>($1);
                    $$ = new NRung($3, rung_count);
                    rung_count++;
                }
            ;

blockish    : sequences
                {
                    $$ = $1;
                }
            | parallels
                {
                    $$ = $1;
                }
            | segment
                {
                    $$ = $1;
                }
            | block
                {
                    $$ = $1;
                }
            ;

segment     : T_LBRACKET blockish T_RBRACKET
                {
                    $$ = new NSegment($2, rung_count);
                }
            ;

sequences   : sequences block
                {
                    $1->blocks.push_back($2);
                }
            | sequences segment
                {
                    $1->blocks.push_back($2);
                }
            /* Non-recursive */
            | segment segment
                {
                    $$ = new NSequence(rung_count);
                    $$->blocks.push_back($1);
                    $$->blocks.push_back($2);
                }
            | segment block
                {
                    $$ = new NSequence(rung_count);
                    $$->blocks.push_back($1);
                    $$->blocks.push_back($2);
                }
            | block segment
                {
                    $$ = new NSequence(rung_count);
                    $$->blocks.push_back($1);
                    $$->blocks.push_back($2);
                }
            | block block
                {
                    $$ = new NSequence(rung_count);
                    $$->blocks.push_back($1);
                    $$->blocks.push_back($2);
                }
            ;

parallels   : parallels sep segment
                {
                    $1->blocks.push_back($3);
                }
            | parallels sep sequences
                {
                    $1->blocks.push_back($3);
                }
            | parallels sep block
                {
                    $1->blocks.push_back($3);
                }
            /* Non-recursive */
            | sequences sep segment
                {
                    $$ = new NParallel(rung_count);
                    $$->blocks.push_back($1);
                    $$->blocks.push_back($3);
                }
            | sequences sep sequences
                {
                    $$ = new NParallel(rung_count);
                    $$->blocks.push_back($1);
                    $$->blocks.push_back($3);
                }
            | sequences sep block
                {
                    $$ = new NParallel(rung_count);
                    $$->blocks.push_back($1);
                    $$->blocks.push_back($3);
                }
            | block sep segment
                {
                    $$ = new NParallel(rung_count);
                    $$->blocks.push_back($1);
                    $$->blocks.push_back($3);
                }
            | block sep sequences
                {
                    $$ = new NParallel(rung_count);
                    $$->blocks.push_back($1);
                    $$->blocks.push_back($3);
                }
            | block sep block
                {
                    $$ = new NParallel(rung_count);
                    $$->blocks.push_back($1);
                    $$->blocks.push_back($3);
                }
            | segment sep segment
                {
                    $$ = new NParallel(rung_count);
                    $$->blocks.push_back($1);
                    $$->blocks.push_back($3);
                }
            | segment sep sequences
                {
                    $$ = new NParallel(rung_count);
                    $$->blocks.push_back($1);
                    $$->blocks.push_back($3);
                }
            | segment sep block
                {
                    $$ = new NParallel(rung_count);
                    $$->blocks.push_back($1);
                    $$->blocks.push_back($3);
                }
            ;

block       : inst T_LPAREN addresses T_RPAREN
                {
                    $$ = new NBlock($1, *$3, rung_count);
                }
            ;

inst        : T_INSTRUCTION
                {
                    $$ = new NInstruction(*$1, rung_count);
                    delete $1;
                }
            ;

addresses   : addresses sep address
                {
                    $1->push_back($3);
                }
            | address
                {
                    $$ = new std::vector<NAddress*>();
                    $$->push_back($1);
                }
            ;

address     : T_ADDRESS
                {
                    $$ = new NAddress(*$1, rung_count);
                    delete $1;
                }
            | T_INTEGER
                {
                    // TODO: How to handle constant integers?
                    $$ = new NAddress(std::to_string($1), rung_count);
                }
            ;

sep         : T_COMMA
            ;

%%

/* vim: tw=0 nowrap */
