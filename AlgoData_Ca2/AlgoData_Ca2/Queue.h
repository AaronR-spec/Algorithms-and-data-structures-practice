#pragma once
#include <iostream>
using namespace std;
/*
	Class decloration of the Queue implemination, using template for generic purposes. 
	
	Public is the methods the can we accessed outside this file.

	Private is the data we dont want to be accessed outside this file (encapulastion)

	This is the code used to complete question one of the ca brief.
	All functiality outlined in the brief invloving the Queue has been implemented.

*/
template <typename T>
class Queue
{
public:
	// constructor
	Queue(int size);
	~Queue();
	// add item
	void Enqueue(T item);
	// remove item (moves rear by 1)
	T Dequeue();
	// returns size of queue
	int size();
	// wipes the queue (sets rear and front to -1)
	void clear();
	
private:
	// empty array with no fixed size, using a pointer. 
	T* Q;
	int capacity = 0;
	int count = 0;
	// front and rear are initalised as -1
	int front = -1;
	int rear = -1;

	bool isEmpty();
};
/*
	Qeueue constructor, this is called when initulaising the Queue, we get the size they want and make a Queue that size.
	Template is used so they can have an int queue or a string without chaning the code.

	Capcatity is the max size the queue can be at all times.

	Parameter: int size
	Return: Refernece to the Queue
*/
template<typename T>
Queue<T>::Queue(int size)
{
	this->Q = new T[size];
	this->capacity = size;
}
/*
	This is used to add items to the Queue, user puts what they want to add and we append it to the end of the queue.
	We need to add it to the end because queue is a first in first out structure. 

	Use modulous to loop around the queue making it a circular queue.

	Parameter: T item
	Return: None
	
*/
/*
	Code adapted from: 
	https://www.programiz.com/dsa/circular-queue 
	Access: 1/12/2020
*/
template<typename T>
void Queue<T>::Enqueue(T item)
{
	// checks if the item isnt NULL
	if (item != NULL)
	{
		// checks if the queue is full
		if ((rear + 1) % capacity == front)
		{
			cout << "Queue is full" << endl;
		}
		else
		{
			if (front == -1)
			{
				front = 0;
			}
			// instead of just incrementing it, this makes it "loop"
			rear = (rear + 1) % capacity;
			// adds item to the rear 
			Q[rear] = item;
			// tracks the size currently taken up
			this->count++;
		}
	}
}
/*
	Used to take an item for the front of the queue and is returned to the user.
	Takes the first item in the queue then changes the front so it points to the next value,
	this is how we remove it without actually removing the value.


	Parameter: None;
	Return: T (first item currently in the queue)

*/
template<typename T>
T Queue<T>::Dequeue()
{
	// checks if the queue is empty, made it a function for clean code
	if (isEmpty()) 
	{
		cout << "Queue is empty" << endl;
		// returns empty constructor as NULL flagged errors and returning 0 which is like null didnt work for string
		return T();
	}
	else
	{
		if (front == capacity)
		{
			front = rear = -1;
		}
		else {
			// takes item at the fron of the queue
			T item = Q[front];
			// current size taken up is redused by one
			this->count--;
			// instead of just incrementing front (loop modulus)
			front = (front + 1) % capacity;
			// returns the item to the user
			return item;
		}
	}
	
}
/*
	Returns the size of the queue currently that is tracked by count.

	Parameter: None
	Return: int (current used size of the queue)

*/
template<typename T>
int Queue<T>::size()
{
	return this->count;
}
/*
	Clears the queue resetting the front and rear pointers and count.
	Deletes the current Queeue and inistalises a new one for future processing, do this as it will flag an error if 
	you just delete it.

	Parameter: None
	Return: None

*/
template<typename T>
void Queue<T>::clear()
{
	delete[] this->Q;
	Q = new T[capacity];
	this->count = 0;
	this->front = -1;
	this->rear = -1;
}

/*
	Queues destructor, called when delete of the queue is used or program stops.

	Parameter: None
	Return: None

*/
template<typename T>
Queue<T>::~Queue() 
{
	delete[] this->Q;
}
/*
	Used to see if the Queue is currently emtpy, as we dont want to return items if the qeueue 
	is actually empty.
	Checks the front and rear if they are -1 its empty or if count (current used size) is less then 0

	Parameter: None
	Return: bool (empty or not)

*/
template<typename T>
bool Queue<T>::isEmpty() 
{
	// simple check if front and rear are equal to -1 which is the inital value
	if (front == -1 && rear == -1 || count <=0) 
	{
		this->front = -1;
		this->rear = -1;
		return true;
	}
	else 
	{
		return false;
	}
}