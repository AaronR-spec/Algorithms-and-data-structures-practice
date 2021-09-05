#pragma once
#include "Tree.h"

template <class T>
class TreeIterator
{
public:	
	Tree<T> *node;
	DListIterator<Tree<T>*> childIter;

	TreeIterator(Tree<T>* root);
	void resetIterator();
	void root();
	void up();
	void down();
	void childBack();
	void childForth();
	void childStart();
	void childEnd();
	void appendChild(T item);
	void preppendChild(T item);
	void insertChildBefore();
	void insertChildAfter();
	void removeChild();
	bool childValid();
	T childItem();
	T item();
};
template <class T>
TreeIterator<T>::TreeIterator(Tree<T>* root)
{
	node = root;
	resetIterator();
}

template <class T>
void TreeIterator<T>::resetIterator()
{
	if (node != nullptr)
	{
		
		childIter = node->children->getIterator();
	}
	else
	{
		childIter = nullptr;
	}
}

template <class T>
void TreeIterator<T>::root()
{
	if (node->parent != nullptr)
	{
		node = node->parent;
		root();
	}
	else
	{
		resetIterator();
	}
}

template <class T>
void TreeIterator<T>::up()
{
	if (node->parent != nullptr)
	{
		node = node->parent;
		
	}
	resetIterator();
}

template <class T>
void TreeIterator<T>::down()
{
	if (childIter.isValid())
	{
		node = childIter.item();
		resetIterator();
	}

}

template <class T>
void TreeIterator<T>::childBack()
{
	if (childIter.isValid())
	{
		childIter.reverse();
	}
}

template <class T>
void TreeIterator<T>::childForth()
{
	if (childIter.isValid())
	{
		childIter.advance();
		
	}
}

template <class T>
void TreeIterator<T>::childStart()
{
	if (childIter.isValid())
	{
		childIter.start();
	}
}

template <class T>
void TreeIterator<T>::childEnd()
{
	if (childIter.isValid())
	{
		childIter.end();
	}
}

template <class T>
void TreeIterator<T>::appendChild(T item)
{
	Tree<T> *temp = new Tree<T>(item);
	temp->parent = node;
	node->children->append(temp);
	
	resetIterator();
}

template <class T>
void TreeIterator<T>::preppendChild(T item)
{
		Tree<T> temp = new Tree<T>(item);
		temp.parent = node;
		node->children->prepend(temp);
		resetIterator();
}

template <class T>
void TreeIterator<T>::insertChildBefore()
{
	
		Tree<T*> temp = new Tree(item);
		temp.parent = node;
		node->children.insert(childIter, temp);
	
}

template <class T>
void TreeIterator<T>::insertChildAfter()
{

	Tree<T*> temp = new Tree(item);
	temp.parent = node;
	node->children.insert(temp);


}

template <class T>
void TreeIterator<T>::removeChild()
{
	node->children->remove(childIter);
}

template <class T>
bool TreeIterator<T>::childValid()
{
	return childIter.isValid();
}

template <class T>
T TreeIterator<T>::childItem()
{
	return childIter->node->data;
}

template <class T>
T TreeIterator<T>::item()
{
	return node->data;
}