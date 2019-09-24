
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
void print(string);

ifstream in("test.txt");
ifstream in2("test.txt");
yyFlexLexer *lexer = new yyFlexLexer(&in);
yyFlexLexer *lexer_for_LookA = new yyFlexLexer(&in2);
int lookA;
int token;

int main()
{

    lookA = lexer_for_LookA->yylex();

    if (Program() == true)
    {
        cout << "GRAMATICA CORRECTA"<<endl;
    }
    else
    {
        cout << "GRAMATICA INCORRECTA";
    }
    return 0;
}
void print(string fname){
    cout<<fname+": "<<endl;
    cout<<"TOKEN=";
    cout<<lexer->YYText()<<endl;
    cout<<endl;
}

bool Program()
{
     cout<<"Program"<<endl;
       cout<<endl;
    if (opt_funct_decl())
    {
      
        return true;
    }
    return false;
}
bool opt_funct_decl()
{
    cout<<"opt_funct_decl"<<endl;
      cout<<endl;
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
 cout<<"funct_head"<<endl;
   cout<<endl;
    if (funct_name())
    {
        //si es PAR_OP

        if (lookA == PAR_OP)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            print("PAR_OP");
            if (param_list_opt())
            {
                //si es PAR_CL
                if (lookA == PAR_CL)
                {
                   
                    lookA = lexer_for_LookA->yylex();
                    token = lexer->yylex();
                     print("PAR_CL");
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
  cout<<"funct_name"<<endl;
    cout<<endl;
    if (funct_type())
    {
        //is ID
        if (lookA == ID)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            print("ID");
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
      cout<<"funct_type"<<endl;
        cout<<endl;
    if (lookA == STATIC_TKN)
    {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
        print("STATIC_TKN");
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
  cout<<"decl_type: "<<endl;
 

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
         cout<<"TOKEN= ";
        cout<<lexer->YYText()<<endl;
        cout<<endl;
        return true;
    }
    return false;
}
bool param_list_opt()
{
      cout<<"param_list_opt: ";
    if (lookA == VOID_TYPE || lookA == INT_TYPE ||
        lookA == ANYTYPE_TYPE ||
        lookA == BOOLEAN_TYPE ||
        lookA == REAL_TYPE ||
        lookA == DATE_TYPE ||
        lookA == STRING_TYPE)
    {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
        cout<<lexer->YYText()<<endl;
        cout<<endl;
        if (lookA == PAR_CL)
        {
            print("PAR_CL");
            return true;
        }
        else if (lookA == COMA)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            print("COMA");
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
    cout<<"decl_param"<<endl;
      cout<<endl;
    if (decl_type())
    {

        if (lookA == ID)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            print("ID");
            return true;
        }
        
    }
    return false;
}
bool body()
{
      cout<<"body"<<endl;
        cout<<endl;
    if (lookA == BRACK_OP)
    {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
        print("BRACK_OP");
        if (stmt_list())
        {

            if (lookA == BRACK_CL)
            {
                token = lexer->yylex();
                lookA = lexer_for_LookA->yylex();
                print("BRACK_CL");
                return true;
            }
            else {
                
            if(stmt_list()){
            if (lookA == BRACK_CL)
            {
                token = lexer->yylex();
                lookA = lexer_for_LookA->yylex();
                print("BRACK_CL");
                return true;
            }
                }
            }
            
        }
       
    }
    return false;
}
bool stmt_list()
{
      cout<<"stmt_list"<<endl;
        cout<<endl;

   return stmts();
}
bool stmts()
{
      cout<<"stmts"<<endl;
      cout<<endl;
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
      cout<<"stmt"<<endl;
      cout<<endl;
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
         //Si hay mas de un stmt
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
      cout<<"if_stmt"<<endl;
        cout<<endl;
    if (lookA == IF)
    {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
        print("IF");
        if (lookA == PAR_OP)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            print("PAR_OP");
            if (bool_expr())
            {
                if (lookA == PAR_CL)
                {
                    token = lexer->yylex();
                    lookA = lexer_for_LookA->yylex();
                    print("PAR_CL");
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
      cout<<"while_stmt"<<endl;
        cout<<endl;
    if (lookA == WHILE)
    {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
        print("WHILE");
        if (lookA == PAR_OP)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            print("PAR_OP");
            if (bool_expr())
            {
                if (lookA == PAR_CL)
                {
                    token = lexer->yylex();
                    lookA = lexer_for_LookA->yylex();
                    print("PAR_CL");
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
      cout<<"return_stmt"<<endl;
        cout<<endl;
    if (lookA == RETURN)
    {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
        print("PAR_RETURN");
        if (lookA == SEMICOLON)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            print("PAR_SEMICOLON");
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
                    print("PAR_CL");
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
      cout<<"expr_stmt"<<endl;
        cout<<endl;
    if (assign_stmt())
    {
        if (lookA == SEMICOLON)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            print("SEMICOLON");
            return true;
        }
    }
}
bool assign_stmt()
{
      cout<<"assign_stmt"<<endl;
        cout<<endl;
    if (decl_type())
    {
        if (lookA == ID)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            print("ID");
            if (lookA == ASSIGN)
            {
                token = lexer->yylex();
                lookA = lexer_for_LookA->yylex();
                print("ASSIGN");
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
      cout<<"bool_expr:"<<endl;
      cout<<"TOKEN=";
    if (lookA == TRUE_LITERAL || lookA == FALSE_LITERAL)
    {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
        cout<<lexer->YYText()<<endl;
        cout<<endl;
        return true;
    }
    else if (lookA == INT_LITERAL || lookA == REAL_LITERAL || lookA == DATE_LITERAL || lookA == STRING_LITERAL)
    {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
         cout<<lexer->YYText()<<endl;
        cout<<endl;
        if (lookA == LOG_OP)
        {
            token = lexer->yylex();
            lookA = lexer_for_LookA->yylex();
            print("LOG_OP");
            if (constant())
            {
                return true;
            }
        }
        else if (lookA == REL_OP)
        {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
         print("REL_OP");
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
      cout<<"Constant: "<<endl;
      cout<<"TOKEN=";
    if (lookA == INT_LITERAL ||
        lookA == REAL_LITERAL ||
        lookA == DATE_LITERAL ||
        lookA == STRING_LITERAL)
    {
        token = lexer->yylex();
        lookA = lexer_for_LookA->yylex();
           cout<<lexer->YYText()<<endl;
        cout<<endl;
        return true;
    }
    return false;
}
