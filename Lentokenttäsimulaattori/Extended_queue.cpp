#include <iostream>
using namespace std;
#include "Extended_queue.h"

Extended_queue::Extended_queue(): Queue()
{
}

bool Extended_queue::full() const
{
	return count == maxqueue;
}

int Extended_queue::size() const
/*
Post:   Return the number of entries in the Extended_queue.
*/
{
	return count;
}

void Extended_queue::clear()
/*
Post:  Delete all inputs from the queue.
*/
{
	count = 0;
	rear = maxqueue - 1;
	front = 0;
}

Error_code Extended_queue::serve_and_retrieve(Queue_entry& item)
{
	retrieve(item);
	return serve();
}
