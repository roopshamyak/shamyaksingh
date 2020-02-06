//  +---------------------------------------------+
//  |                 parser.cpp                  |
//  +---------------------------------------------+
//  |   Name:     Shamyak Singh                   |
//  |   Course:   CS 498                          |
//  |   Date:     12/10/2019                      |
//  +---------------------------------------------+

#include "parser.h"
#include "grammar.h"
#include "prints.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>

//  +---------------------------------------------+
//  |          startup(string filename)           |
//  +---------------------------------------------+
bool parser::startup(string filename)
{
    if (scan.open(filename) == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}//startup()


//  +---------------------------------------------+
//  |             compile(string fn)              |
//  +---------------------------------------------+
string parser::compile(string fn)
{
    //If startup succeeded
    if(startup(fn))
    {
        //Scan the first token from the source
        nextToken = scan.getNextToken();
        //Make a token with a non-terminal id of "TOK_N_PROGRAM" and push it to the top of the tokStack
        token start;
        start.setId(TOK_N_PROGRAM);
        tokStack.push(start);
        top = tokStack.top();
        while((tokStack.empty() == false) && (scan.isError() == false) && (nextToken.getId() != TOK_EOS))
        {
            top = tokStack.top();
            tokStack.pop();
            
            if(isNonTerminal(top))
            {
                int production = selectProd();
                
                //Production found
                if(production != -1)
                {
                    //Push the right hand side of the production to tokStack
                    pushProdRHS(production);
                    //Print out the production that was selected
                    cout << "TEST: PROD SELECTED=";
                    printProduction(production);

                } else { /*No production found...*/ }
            }
            
            else
            {
                if(top.getId() == nextToken.getId())
                {
                    //Print out that the token was consumed
                    cout << "TEST: " << TOKENID_STR[nextToken.getId()] << " consumed" << endl;
    		        //Scan the next token from the source
                    nextToken = scan.getNextToken();
                }
                
                //REJECT
                else
                {
                    return TOKENID_STR[top.getId()] + " expected!";
                }
            }
        }
        
        //REJECT: If there was an error while scanning the file (but not opening the file)
        if(scan.isError())
        {
            return scan.getError();
        }
        
        //REJECT
        else if((tokStack.empty() == true) && (nextToken.getId() != TOK_EOS))
        {
            return "Extra tokens at end of source";
        }
        
        //REJECT
        else if((nextToken.getId() == TOK_EOS) && (tokStack.empty() == false))
        {
            return "Unexpected end of source";
        }
        
        //ACCEPT
        else if(nextToken.getId() != TOK_ERROR)
        {
            return "";
        }
        
        //REJECT: Unknown Error
        else
        {
            return "UNKNOWN ERROR";
        }
    }
    
    else if(scan.isError())
    {
        //Should only return a error about opening the file
        return scan.getError();
    }

    else
    {
        return "UNKNOWN ERROR";
    }
    
}//compile()


//  +---------------------------------------------+
//  |                selectProd()                 |
//  +---------------------------------------------+
int parser::selectProd()
{
    for (int i = 0; i < GR_NUMPRODS; i++)
    {
        if (top.getId() == PROD[i][GR_LHS])
        {
            if (PROD[i][GR_FIRST_SELSET] == TOK_DEFAULT)
            {
                return i;
            }
            else
            {
                for (int j = GR_FIRST_SELSET; j <= GR_LAST_SELSET; j++)
                {
                    if (nextToken.getId() == PROD[i][j])
                    {
                        return i;
                    }
                }
            } 
        }
    }
    return -1;
}//selectProd()


//  +---------------------------------------------+
//  |           isNonTerminal(token t)            |
//  +---------------------------------------------+
bool parser::isNonTerminal(token t)
{
    if ((t.getId() <= LAST_NON_TERMINAL) && (t.getId() >= FIRST_NON_TERMINAL))
    {
        return true;
    }
    else
    {
        return false;
    }
}//isNonTerminal()


//  +---------------------------------------------+
//  |         pushProdRHS(int prodNum)            |
//  +---------------------------------------------+
void parser::pushProdRHS(int prodNum)
{
    for (int i = GR_LAST_RHS; i >= GR_FIRST_RHS; i--)
    {
        token t;
        t.setId(PROD[prodNum][i]);
        tokStack.push(t);
    }
}//pushProdRHS()
