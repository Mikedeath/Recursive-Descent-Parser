%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "MyTokens.h"
%}

%option c++
%option outfile="Scanner.cpp"
%option case-insensitive
%option noyywrap

COMMENT "//".*
WHITESPACE [\t\r\f" "]
ID ({LETTER}|"_")({LETTER}|{DIGIT})*
ADD_OP [+-]
MULT_OP [*/]
LOG_OP ("||"|"&&")
REL_OP (">"|"<"|"=="|"<="|">=")
ASSIGN (":=")
PERIOD [.]
DDPERIOD ("::")
INCR ("++")
INT_LITERAL {DIGIT}+
REAL_LITERAL {DIGIT}+"."{DIGIT}+
STRING_LITERAL ["]({LETTER}|{DIGIT}|" "|[%=@,-=()_])*["] 
DATE_LITERAL {DIGIT}{DIGIT}"/"{DIGIT}{DIGIT}"/"{DIGIT}{DIGIT}{DIGIT}{DIGIT}

SEMICOLON [;]
PAR_OP [(] 
PAR_CL [)]
BRACK_OP [{] 
BRACK_CL [}] 
COMA [,] 


DIGIT [0-9]
LETTER [a-zA-Z]
DELIMITADOR [\t\r\f" "]

%%
"false" {return FALSE_LITERAL;}
"true"  {return TRUE_LITERAL;}
"while" {return WHILE;}
"if"    {return IF;}
"else"  {return ELSE;}
"return"  {return RETURN;}
"BEGIN" {return INICIO;}
"THEN"  {return IF_THEN;}
"DO"    {return DO;}
"END"   {return END;}
"static" {return STATIC_TKN;}
"int"    {return INT_TYPE;}
"anytype" {return ANYTYPE_TYPE;}
"boolean" {return BOOLEAN_TYPE;}
"void"  {return VOID_TYPE;}
"real"  {return REAL_TYPE;}
"String" {return STRING_TYPE;}
"date"  {return DATE_TYPE;}


{COMMENT} {return COMMENT;}

{ID} {return ID;}
{ADD_OP} {return ADD_OP;}
{MULT_OP} {return MULT_OP;}
{LOG_OP}  {return LOG_OP;}
{REL_OP} {return REL_OP;}
{ASSIGN} {return ASSIGN;}
{PERIOD} {return PERIOD;}
{DDPERIOD} {return DDPERIOD;}
{INCR} {return INCR;}
{INT_LITERAL}  {return INT_LITERAL;}
{REAL_LITERAL}  {return REAL_LITERAL;}
{STRING_LITERAL} {return STRING_LITERAL;}
{DATE_LITERAL} {return DATE_LITERAL;}
{SEMICOLON} {return SEMICOLON;}
{PAR_OP} {return PAR_OP;}
{PAR_CL} {return PAR_CL;}
{BRACK_OP} {return BRACK_OP;}
{BRACK_CL} {return BRACK_CL;}
{COMA} {return COMA;}


{DELIMITADOR}   {}
.               {printf("ERROR LEXICO");}

%%
