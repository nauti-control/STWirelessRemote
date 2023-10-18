#ifndef COMMANDSTACK_H
#define COMMANDSTACK_H
#define MAX 10

#include "Commands.h"

class CommandStack
{

private:
    int top;
    void updateArrayAfterPop();
    

public:
    int myStack[MAX]; // stack array

    CommandStack() { top = -1; }
    bool push(int x);
    int pop();
    bool isEmpty();
    
};
#endif