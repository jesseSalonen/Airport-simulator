#include <iostream>
using namespace std;
#include "Queue.h"

Queue::Queue()
/*
Post: The Queue is initialized to be empty.
*/
{
    count = 0;
    rear = maxqueue - 1;
    front = 0;
}


bool Queue::empty() const
/*
Post: Return true if the Queue is empty, otherwise return false.
*/
{
    return count == 0;
}


Error_code Queue::append(const Queue_entry& item)
/*
Post: item is added to the rear of the Queue. If the Queue is full
return an Error_code of overflow and leave the Queue unchanged.
*/

{
    if (count >= maxqueue) return overflow;
    count++;
    rear = ((rear + 1) == maxqueue) ? 0 : (rear + 1);
    entry[rear] = item;
    return success;
}

Error_code Queue::append_front(const Queue_entry& item)
{
    if (count >= maxqueue) return overflow;
    count++;
    front = ((front - 1) == -1) ? maxqueue - 1 : (front - 1);
    entry[front] = item;
    return success;
}


Error_code Queue::serve()
/*
Post: The front of the Queue is removed. If the Queue
is empty return an Error_code of underflow.
*/

{
    if (count <= 0) return underflow;
    count--;
    front = ((front + 1) == maxqueue) ? 0 : (front + 1);
    return success;
}


Error_code Queue::retrieve(Queue_entry& item) const
/*
Post: The front of the Queue retrieved to the output
      parameter item. If the Queue is empty return an Error_code of underflow.
*/

{
    if (count <= 0) return underflow;
    item = entry[front];
    return success;
}


