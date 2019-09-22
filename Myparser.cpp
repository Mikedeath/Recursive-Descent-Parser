
#include <FlexLexer.h>
#include "MyTokens.h"
#include <iostream>
#include <fstream>
using namespace std;

bool Program(void);
bool opt_funct_decl(void);
bool funct_head(void);
bool funct_name(void);
bool funct_type(void);
bool decl_type(void);
bool param_list_opt(void);
bool decl_param(void);
bool body(void);
bool stmt_list(void);
bool stmts(void);
bool stmt(void);
bool if_stmt(void);
bool while_stmt(void);
bool return_stmt(void);
bool expr_stmt(void);
bool assign_stmt(void);
bool bool_expr(void);
bool constant(void);

ifstream in("entrada.txt");
ifstream in2("entrada.txt");
yyFlexLexer *lexer = new yyFlexLexer(&in);
yyFlexLexer *lexer_for_LookA = new yyFlexLexer(&in2);
int lookA;
int token;

int main()
{

    lookA = lexer_for_LookA->yylex();

    if (Program() == true)
    {
        cout << "sirve";
    }
    else
    {
        cout << "no sirve";
    }
    return 0;
}

bool Program()
{
    if (opt_funct_decl())
    {
        return true;
    }
    return false;
}
bool opt_funct_decl()
{
    if (funct_head())
    {
        if (body())
        {
            return true;
        }
    }
    return false;
}
bool funct_head()
{

    if (funct_name())
    {
        //si es PAR_OP

        if (lookA == PAR_OP)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            if (param_list_opt())
            {
                //si es PAR_CL
                if (lookA == PAR_CL)
                {
                    lookA = lexer_for_LookA->yylex();
                    token = lexer->yylex();
                    return true;
                }
                return false;
            }
            return false;
        }
    }

    return false;
}
bool funct_name()
{

    if (funct_type())
    {
        //is ID
        if (lookA == ID)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            return true;
        }
        else
        {
            return false;
        }
    }

    return false;
}
bool funct_type()
{
    //STATIC TOKEN

    if (lookA == STATIC_TKN)
    {
        token = lexer->yylex();
        cout << lexer->YYText() << endl;
        lookA = lexer_for_LookA->yylex();
        cout << lexer_for_LookA->YYText() << endl;
        ;
        if (decl_type())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}
bool decl_type()
{

    if (lookA == VOID_TYPE ||
        lookA == INT_TYPE ||
        lookA == ANYTYPE_TYPE ||
        lookA == BOOLEAN_TYPE ||
        lookA == REAL_TYPE ||
        lookA == DATE_TYPE ||
        lookA == STRING_TYPE)
    {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
        return true;
    }
    return false;
}
bool param_list_opt()
{
    if (lookA == VOID_TYPE || lookA == INT_TYPE ||
        lookA == ANYTYPE_TYPE ||
        lookA == BOOLEAN_TYPE ||
        lookA == REAL_TYPE ||
        lookA == DATE_TYPE ||
        lookA == STRING_TYPE)
    {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
        if (lookA == PAR_CL)
        {
            return true;
        }
        else if (lookA == COMA)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            if (param_list_opt())
            {
                return true;
            }
        }
    } //Si es epsilon
    else if (lookA == PAR_CL)
    {
        return true;
    }
    else
    {
        return false;
    }

    return false;
}
bool decl_param()
{
    if (decl_type())
    {

        if (lookA == ID)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            return true;
        }
        
    }
    return false;
}
bool body()
{
    if (lookA == BRACK_OP)
    {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
        if (stmt_list())
        {
            if (lookA == BRACK_CL)
            {
                token = lexer->yylex();
                lookA = lexer_for_LookA->yylex();
                return true;
            }
            
        }
       
    }
    return false;
}
bool stmt_list()
{

   return stmts();
}
bool stmts()
{
    if (lookA == BRACK_CL)
    {
        return true;
    }
    else 
    {
        return stmt();
    }
    return false;
}
bool stmt()
{
    if (lookA == WHILE)
    {
      return while_stmt();       
    }
    else if (lookA == IF)
    {
        return if_stmt();
    }
    else if (lookA == RETURN)
    {
    return return_stmt();
        
    }
    else if (expr_stmt())
    {
         //Check to see If we havent reached the end of the body (in other words, if the next token isnt an '}'), then continue calling statement because there's literally more statements to parse
        if (lookA != BRACK_CL)
            return stmt();
        return true;
    }
    else{
      return false;
    }

}
bool if_stmt()
{
    if (lookA == IF)
    {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
        if (lookA == PAR_OP)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            if (bool_expr())
            {
                if (lookA == PAR_CL)
                {
                    token = lexer->yylex();
                    lookA = lexer_for_LookA->yylex();
                    if (body())
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
bool while_stmt()
{
    if (lookA == WHILE)
    {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
        if (lookA == PAR_OP)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            if (bool_expr())
            {
                if (lookA == PAR_CL)
                {
                    token = lexer->yylex();
                    lookA = lexer_for_LookA->yylex();
                    if (body())
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
bool return_stmt()
{
    if (lookA == RETURN)
    {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
        if (lookA == SEMICOLON)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            return true;
        }
       
        else if (lookA == INT_LITERAL ||
                 lookA == REAL_LITERAL ||
                 lookA == DATE_LITERAL ||
                 lookA == STRING_LITERAL)
        {
            if (constant())
            {
                if (lookA == SEMICOLON)
                {
                    token = lexer->yylex();
                    lookA = lexer_for_LookA->yylex();
                    return true;
                }
            }
        }
        else
        {
            return false;
        }
    }
    return false;
}
bool expr_stmt()
{
    if (assign_stmt())
    {
        if (lookA == SEMICOLON)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            return true;
        }
    }
}
bool assign_stmt()
{
    if (decl_type())
    {
        if (lookA == ID)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            if (lookA == ASSIGN)
            {
                token = lexer->yylex();
                lookA = lexer_for_LookA->yylex();
                if (constant())
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool bool_expr()
{
    
    if (lookA == TRUE_LITERAL || lookA == FALSE_LITERAL)
    {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
        return true;
    }
    else if (lookA == INT_LITERAL || lookA == REAL_LITERAL || lookA == DATE_LITERAL || lookA == STRING_LITERAL)
    {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
        if (lookA == LOG_OP)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            if (constant())
            {
                return true;
            }
        }
        else if (lookA == REL_OP)
        {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
            if (constant())
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return false;
}

bool constant()
{
    if (lookA == INT_LITERAL ||
        lookA == REAL_LITERAL ||
        lookA == DATE_LITERAL ||
        lookA == STRING_LITERAL)
    {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
        return true;
    }
    return false;
}
