// 00101 - The Blocks Problem

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <sstream>
#include <stack>
#include <algorithm>

using namespace std;

typedef unsigned short       ushort;
typedef unsigned int         uint;
typedef unsigned long long   ull;

const uint MAX_BUFFER = 1024;
string Format(const char *fmt, ...)
{
    char formatStr[MAX_BUFFER*5] = {'\0'};
    // -- empty the buffer properly to ensure no leaks.
    memset(formatStr, '\0', sizeof(formatStr));

    va_list args;
    va_start(args, fmt);
    vsnprintf(formatStr, MAX_BUFFER*5, fmt, args);
    va_end(args);
    return string(formatStr);
}

template<class T> string toString(T val)
{
    stringstream ss;
    ss << val;
    return ss.str();
}

void Transform(string& str, int (*Func)(int))
{
    transform(str.begin(), str.end(), str.begin(), Func); 
}

uint numOfBlocks;
stack<uint>* pileOfBlocks;
uint* posOfBlock;

void EmptyStack(stack<uint>& stk)
{
    while (!stk.empty()) stk.pop();
}

void ShowTable()
{
    for (uint i = 0; i < numOfBlocks; i++)
    {
        string strPile = "";
        if (!pileOfBlocks[i].empty())
        {
            stack<uint> pile = pileOfBlocks[i];
            while (!pile.empty())
            {
                uint top = pile.top();
                pile.pop();
                //strPile = Format("%d %s", top, strPile.c_str());
                strPile.insert(0, toString(top) + " ");
            }
        }
        printf("%2d: %s\n", i, strPile.c_str());
    }
    //printf("------------------\n");
}

void ReturnHome(int x) 
{
    while (!pileOfBlocks[x].empty()) 
    {
        ReturnHome(pileOfBlocks[x].top());
        pileOfBlocks[x].pop();
    }
    pileOfBlocks[x].push(x);
    posOfBlock[x] = x;
}

void ClearAbove(int x) 
{
    while (pileOfBlocks[posOfBlock[x]].top() != x)
    {
        ReturnHome(pileOfBlocks[x].top());
        pileOfBlocks[x].pop();
    }
}

void MoveOver(uint b1, uint b2) 
{
    ClearAbove(b1);
    pileOfBlocks[posOfBlock[b2]].push(pileOfBlocks[posOfBlock[b1]].top());
    pileOfBlocks[posOfBlock[b1]].pop();
    posOfBlock[b1] = posOfBlock[b2];
}

void MoveOnto(uint b1, uint b2) 
{
    ClearAbove(b2);
    MoveOver(b1, b2);
}

void PileOver(uint b1, uint b2) 
{
    stack<int> pile;
    while (pileOfBlocks[posOfBlock[b1]].top() != b1)
    {
        pile.push(pileOfBlocks[posOfBlock[b1]].top());
        pileOfBlocks[posOfBlock[b1]].pop();
    }

    pile.push(pileOfBlocks[posOfBlock[b1]].top());
    pileOfBlocks[posOfBlock[b1]].pop();

    while (!pile.empty()) 
    {
        int top = pile.top();
        pileOfBlocks[posOfBlock[b2]].push(top);
        pile.pop();
        posOfBlock[top] = posOfBlock[b2];
    }
}

void PileOnto(uint b1, uint b2) 
{
    ClearAbove(b2);
    PileOver(b1, b2);
}

void move_onto(uint b1, uint b2) 
{ 
    while (pileOfBlocks[posOfBlock[b1]].top() != b1) 
    { 
        uint top = pileOfBlocks[posOfBlock[b1]].top(); 
        pileOfBlocks[top].push(top); 
        posOfBlock[top] = top; 
        pileOfBlocks[posOfBlock[b1]].pop(); 
    } 

    while (pileOfBlocks[posOfBlock[b2]].top() != b2) 
    { 
        uint top = pileOfBlocks[posOfBlock[b2]].top(); 
        pileOfBlocks[top].push(top); 
        posOfBlock[top] = top; 
        pileOfBlocks[posOfBlock[b2]].pop(); 
    } 

    pileOfBlocks[posOfBlock[b2]].pop(); 
    posOfBlock[b2] = b2; 
    pileOfBlocks[b2].push(b2); 

    pileOfBlocks[b2].push(pileOfBlocks[posOfBlock[b1]].top()); 
    pileOfBlocks[posOfBlock[b1]].pop(); 
    posOfBlock[b1] = b2; 
} 

void move_over(uint b1, uint b2) 
{ 
    while (pileOfBlocks[posOfBlock[b1]].top() != b1) 
    { 
        uint top = pileOfBlocks[posOfBlock[b1]].top(); 
        pileOfBlocks[top].push(top); 
        posOfBlock[top] = top; 
        pileOfBlocks[posOfBlock[b1]].pop(); 
    } 

    pileOfBlocks[posOfBlock[b2]].push(pileOfBlocks[posOfBlock[b1]].top()); 
    pileOfBlocks[posOfBlock[b1]].pop(); 
    posOfBlock[b1] = posOfBlock[b2]; 
} 

void pile_onto(uint b1, uint b2) 
{
    stack<uint> pile;
    while (pileOfBlocks[posOfBlock[b2]].top() != b2) 
    { 
        uint top = pileOfBlocks[posOfBlock[b2]].top(); 
        pileOfBlocks[top].push(top); 
        posOfBlock[top] = top; 
        pileOfBlocks[posOfBlock[b2]].pop(); 
    } 

    pileOfBlocks[posOfBlock[b2]].pop(); 
    posOfBlock[b2] = b2; 
    pileOfBlocks[b2].push(b2); 
    
    while (pileOfBlocks[posOfBlock[b1]].top() != b1) 
    { 
        pile.push(pileOfBlocks[posOfBlock[b1]].top()); 
        pileOfBlocks[posOfBlock[b1]].pop(); 
    } 

    pile.push(pileOfBlocks[posOfBlock[b1]].top()); 
    pileOfBlocks[posOfBlock[b1]].pop(); 

    while (!pile.empty()) 
    { 
        pileOfBlocks[posOfBlock[b2]].push(pile.top()); 
        posOfBlock[pile.top()] = posOfBlock[b2]; 
        pile.pop(); 
    } 
} 

void pile_over(uint b1, uint b2) 
{ 
    stack<uint> pile;
    while (pileOfBlocks[posOfBlock[b1]].top() != b1) 
    { 
        pile.push(pileOfBlocks[posOfBlock[b1]].top()); 
        pileOfBlocks[posOfBlock[b1]].pop(); 
    } 

    pile.push(pileOfBlocks[posOfBlock[b1]].top()); 
    pileOfBlocks[posOfBlock[b1]].pop(); 

    while (!pile.empty()) 
    { 
        pileOfBlocks[posOfBlock[b2]].push(pile.top()); 
        posOfBlock[pile.top()] = posOfBlock[b2]; 
        pile.pop(); 
    } 
}

void main()
{
    FILE* file = freopen("00101.in", "r", stdin);
    if (file != NULL)
    {
        freopen("00101.out", "w", stdout);

        //int N;
        //scanf(" %d", &N);

        //for (int i = 1; i <= N; ++i)
        {
            scanf(" %u", &numOfBlocks);

            pileOfBlocks = new stack<uint>[numOfBlocks];
            posOfBlock = new uint[numOfBlocks];
            for (uint n = 0; n < numOfBlocks; ++n)
            {
                pileOfBlocks[n].push(n);
                posOfBlock[n] = n;
            }

            while (true)
            {
                // ------------------------------------------
                string cmd;
                cin >> cmd;
                Transform(cmd, ::tolower);
                if (cmd == "quit")
                    break;
                
                uint b1, b2;
                string mode;
                cin >> b1 >> mode >> b2;

                if (b1 == b2 || posOfBlock[b1] == posOfBlock[b2]) continue;
                Transform(mode, ::tolower);

                if (cmd == "move")
                {
                    if (mode == "onto") 
                    {
                        MoveOnto(b1, b2);
                        //move_onto(b1, b2);
                    }
                    else if (mode == "over")
                    {
                        MoveOver(b1, b2);
                        //move_over(b1, b2);
                    }
                }
                else if (cmd == "pile")
                {
                    if (mode == "onto")
                    {
                        PileOnto(b1, b2);
                        //pile_onto(b1, b2);
                    }
                    else if (mode == "over")
                    {
                        PileOver(b1, b2);
                        //pile_over(b1, b2);
                    }
                }

                // ------------------------------------------
                
                //char cmd[5];
                //scanf(" %s", &cmd);
                //if (stricmp(cmd, "quit") == 0) 
                //    break;		

                //uint b1, b2;
                //char mode[5];
                //scanf(" %u %s %u", &b1, &mode, &b2);

                //if (b1 == b2 || posOfBlock[b1] == posOfBlock[b2]) continue;

                //if (stricmp(cmd, "move") == 0)
                //{
                //    if (stricmp(mode, "onto") == 0) 
                //    {
                //        MoveOnto(b1, b2);
                //        //move_onto(b1, b2);
                //    }
                //    else if (stricmp(mode, "over") == 0)
                //    {
                //        MoveOver(b1, b2);
                //        //move_over(b1, b2);
                //    }
                //}
                //else if (stricmp(cmd, "pile") == 0)
                //{
                //    if (stricmp(mode, "onto") == 0)
                //    {
                //        PileOnto(b1, b2);
                //        //pile_onto(b1, b2);
                //    }
                //    else if (stricmp(mode, "over") == 0)
                //    {
                //        PileOver(b1, b2);
                //        //pile_over(b1, b2);
                //    }
                //}
                //
                // ------------------------------------------
            }
            ShowTable();
        }
    }
    fflush(stdin);
}
