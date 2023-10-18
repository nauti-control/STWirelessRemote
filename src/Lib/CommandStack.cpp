#include "CommandStack.h"

bool CommandStack::push(int item)
{
    if (top >= (MAX - 1))
    {

        return false;
    }
    else
    {
        myStack[++top] = item;

        return true;
    }
}

// removes or pops elements out of the stack
int CommandStack::pop()
{
    if (top < 0)
    {

        return -1;
    }
    else
    {

        // FIFO Queue
        int item = myStack[0];
        top--;
        if (top >= 0)
        {

            updateArrayAfterPop();
        }
        return item;
    }
}

// check if stack is empty
bool CommandStack::isEmpty()
{
    return (top < 0);
}

// ReOrg Buffer Array After pop
void CommandStack::updateArrayAfterPop()
{

    int tempStack[top + 1];

    for (int i = 0; i < top; i++)
    {
        tempStack[i] = myStack[i + 1];
    }
}