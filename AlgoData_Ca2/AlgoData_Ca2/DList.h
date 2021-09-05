template <class T> class DListIterator;
template <class T> class DListNode;

#pragma once
#include "DListNode.h"
#include "DListIterator.h"

template<class T>
class DList
{
public:
	DListNode<T>* head, * tail;
	int count;

	DList();
	void prepend(T data);
	void append(T data);
	void removeHead();
	void removeTail();
	DListIterator<T> getIterator();
	void remove(DListIterator<T>& iterator);
	void insert(DListIterator<T>& iter, T data);

	int size();

	~DList();
};

template<class T>
DList<T>::DList()
{
	head = tail = nullptr;
	count = 0;
}

template<class T>
void DList<T>::prepend(T data)
{
	DListNode<T>* newNode = new DListNode<T>(data);
	newNode->next = head;
	newNode->previous = nullptr;
	head->previous = newNode;
	head = newNode;

	if (tail == nullptr)
	{
		tail = head;
	}
	count++;
}

template<class T>
void DList<T>::append(T data)
{
	if (head == nullptr) {
		// create a new head node

		head = tail = new DListNode<T>(data);
	}
	else {
		// insert a new node after the tail

		tail->insertAfter(data);

		// update the tail pointer
		tail = tail->next;
	}
	count++;
}

template<class T>
void  DList<T>::removeHead() {
	DListNode<T>* oldHead = head;
	head = head->next;
	delete oldHead;
	oldHead = nullptr;
	head->previous = nullptr;

	count--;
}

template<class T>
void  DList<T>::removeTail()
{
	if (tail == head)
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
		DListNode<T>* oldTail = tail;
		tail = oldTail->previous;
		delete oldTail;
		oldTail = nullptr;
		tail->next = nullptr;
	}
	count--;
}

template<class T>
void DList<T>::remove(DListIterator<T>& iterator)
{
	if (iterator.list != this) {
		return;
	}

	if (!iterator.isValid()) {
		return;
	}
	if (iterator.node == head) {
		iterator.advance();
		removeHead();
		return;
	}
	else
	{
		/* otherwise,
		scan through the list to get the node prior to
		the one selected by the iterator paramter.
		*/
		DListIterator<T> previousNode = getIterator();
		while (previousNode.node->next != iterator.node) {
			previousNode.advance();
		}

		/*
		if the node to be deleted is the tail, we need
		to update the tail pointer.
		*/
		if (previousNode.node->next == tail) {
			tail = previousNode.node;
		}

		// re-link the list
		previousNode.node->next = iterator.node->next;
		if (iterator.node->next != nullptr)
		{
			iterator.node->next->previous = previousNode.node;
		}

		// now do the deletion
		delete iterator.node;
		count--;
	}
}

template <class T>
void DList<T>::insert(DListIterator<T>& iter, T data)
{
	if (iter.list != this) {
		return;
	}

	if (!iter.isValid()) {
		return;
	}
	if (iter.node == tail)
	{
		append(data);
	}
	else if (iter.node == head)
	{
		prepend(data);
	}
	else
	{
		iter.node->insertBefore(data);
		count++;
	}
}
template <class T>
DListIterator<T> DList<T>::getIterator()
{
	return DListIterator<T>(this, head);
}
template<class T>
int DList<T>::size()
{
	return count;
}

template<class T>
DList<T>::~DList() {
	DListNode<T>* iterator, * next;
	iterator = head;
	while (iterator != 0) {
		// save pointer to the next node
		next = iterator->next;
		// delete the current node
		delete iterator;
		// make the next node the current one
		iterator = next;
	}
}