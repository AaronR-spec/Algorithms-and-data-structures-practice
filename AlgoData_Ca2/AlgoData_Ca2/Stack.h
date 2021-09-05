#pragma once
#include <queue>
#include <iostream>

using namespace std;
/*
	Class decloration of the Stack implemination, using template for generic purposes and Queues for the 
	standard libaries.

	Public is the methods the can we accessed outside this file.

	Private is the data we dont want to be accessed outside this file (encapulastion)

	This is the code used to complete question Two of the ca brief.
	All functiality outlined in the brief invloving the Queue has been implemented.

*/
template<typename T>
class Stack 
{
public:
	~Stack();
	void push(T item);
	T pop();
	T front();
	int size();
	void clear();

private:
	// Queue used to represent the Stack structure
	queue<T> firstQueue;
	// Queue used to add item and swap with firstQueue to update Queue to be represented as a stack
	queue<T> secondQueue;
	// current num of elements in stack
	int count = 0;
};
/*
	We use this to add to the Stack, the item is pused onto the second queue and then the firstQueue holding
	all the values is iterated through and added to the secondQueue. Doing this makes the item added
	to the front or top of the stack. 
	We then swap second queue with first queue which is our 'stack' and increment count that is used for size calls.
	
	Parameter: T item
	Return: None

*/
// Code logic roughly taken from : 
// https://www.youtube.com/watch?v=xBugrptVRUQ
template<typename T>
void Stack<T>::push(T item) 
{
	// add to second queue first 
	this->secondQueue.push(item);
	// then add all items in first queue to the second queue
	while (!this->firstQueue.empty()) 
	{
		// dequeues off the frist queue and then added to second queue
		this->secondQueue.push(firstQueue.front());
		firstQueue.pop();
	}
	// swap the queues making first the item add to the front of the queue/stack
	// need a temp value to store primary queue
	queue<T> temp = this->firstQueue;
	// with first stored we overwrite it
	this->firstQueue = secondQueue;
	// second queue is now equal to temp(first queue)
	this->secondQueue = temp;
	this->count++;
}
/*
	Used to remove an item from the stack aka firstQueue. 
	We check if the stack is empty if it is we return a empty constructor of template type, we do this as
	NULL flagged errors and this is the only fix i could find that worked.
	
	If it is not empty we decrement the count aka current size of stack and save the item being removed, then
	pop it off the queue, then return the stored item to the user.

	Parameter: None
	Return: T (item removed)

*/
template<typename T>
T Stack<T>::pop() 
{
	// if their is no items in the stack
	if (firstQueue.empty()) 
	{
		return T();
	}
	else 
	{
		this->count--;
		// if stack has item it dequeues it from queue and returns it
		T temp = firstQueue.front();
		firstQueue.pop();
		return temp;
	}
}

/*
	Used to see the first item without removing it from the stack aka firstQueue.
	We check if the stack is empty if it is we return a empty constructor of template type, we do this as
	NULL flagged errors and this is the only fix i could find that worked.

	If it is not empty we return the item that is at the front of the queue or back of the stack.

	Parameter: None
	Return: T (item removed)

*/
template<typename T>
T Stack<T>::front()
{
	if (firstQueue.empty())
	{
		return T();
	}
	else 
	{
		return this->firstQueue.front();
	}
}
/*
	Returns count which represents the current used size of the stack.

	Parameters: None
	Return: int (current used size)

*/
template<typename T>
int Stack<T>::size() 
{
	return this->count;
}
/*
	Used to empty the stack, creates an empty queue and swaps it with both queues making them empty, wiping their data.
	Then we reset the count as we currently have no items.

	Parameter: None
	Return: None
*/
// https://stackoverflow.com/questions/709146/how-do-i-clear-the-stdqueue-efficiently
template<typename T>
void Stack<T>::clear() 
{
	// empty queue
	queue<T> empty;
	// swap empty with queues representing the stack (wiping their data)
	swap(this->firstQueue, empty);
	swap(this->secondQueue, empty);
	// reset the count 
	this->count = 0;
}
/*
	Stack Deconstructor used to delete the stack, used delete didnt work as it flagged errors. 
*/
template<typename T>
Stack<T>::~Stack() 
{
	//delete this->firstQueue;
	//delete this->secondQueue;
}








