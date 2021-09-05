#pragma once
template <class T>
class DListNode
{
public:
	T data;
	DListNode* next;
	DListNode* previous;

	DListNode(T item);
	void insertAfter(T newContent);
	void insertBefore(T newContent);
};
template <class T>
DListNode<T>::DListNode(T item)
{
	data = item;
	next = nullptr;
	previous = nullptr;
}

template <class T>
void DListNode<T>::insertAfter(T newContent)
{
	DListNode<T> *temp = new DListNode(newContent);
	temp->previous = this;
	temp->next = this->next;
	if (this->next != nullptr)
	{
		this->next->previous = temp;
	}
	this->next = temp;

}

template <class T>
void DListNode<T>::insertBefore(T newContent)
{
	DListNode<T> *temp = new DListNode(newContent);
	temp->previous = this->previous ;
	temp->next = this;
	if (this->previous != nullptr)
	{
		this->previous->next = temp;
	}
	this->previous = temp;

}