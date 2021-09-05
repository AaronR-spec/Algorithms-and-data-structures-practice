template <class T> class DList;
template <class T> class DListNode; 
#pragma once
template<class T>
class DListIterator
{
public:
	DListNode<T> *node;
	DList<T> *list;

	// constructor defaults to zero:
	// it'll never be called directly by the user
	// anyway.
	DListIterator(DList<T> *l = nullptr, DListNode<T> *n = nullptr);
	void start();
	void end();
	T& item();
	bool isValid();
	void advance();
	void reverse();
};
template<class T>
DListIterator<T>::DListIterator(DList<T> *l, DListNode<T> *n)
{
	list = l;
	node = n;
}

template<class T>
void DListIterator<T>::reverse()
{
	if (node ==nullptr) {
		return;
	}
	node = node->previous;
}

template<class T>
void  DListIterator<T>::start() {
	node = list->head;
}

// reset the iterator to the last node
template<class T>
void  DListIterator<T>::end() {
	node = list->tail;
}

// get the current item
template<class T>
T&  DListIterator<T>::item() {
	return node->data;
}

// checks that we've another item ready
template<class T>
bool  DListIterator<T>::isValid() {
	return (node != nullptr);
}

// advance to the next item
template<class T>
void  DListIterator<T>::advance() {
	if (node == nullptr) {
		return;
	}
	node = node->next;
}