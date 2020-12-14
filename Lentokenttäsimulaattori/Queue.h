#pragma once
#include "Utility.h"
#include "Plane.h"
const int maxqueue = 20; //  small value for testing
typedef Plane Queue_entry;

class Queue {
public:
	Queue();
	bool empty() const;
	Error_code serve();
	Error_code append(const Queue_entry& item);
	Error_code append_front(const Queue_entry& item);
	Error_code retrieve(Queue_entry& item) const;

protected:
	int count;
	int front, rear;
	Queue_entry entry[maxqueue];
};

