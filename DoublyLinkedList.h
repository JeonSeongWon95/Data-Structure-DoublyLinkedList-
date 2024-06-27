
#pragma once

#include <assert.h>


template<typename T>
class Node
{
public:
	Node* PreNode;
	Node* NextNode;
	T Data;

private:
	Node();
	~Node();
};



template<typename T>
class DoublyLinkedList
{
	friend class Node<T>;

public:
	DoublyLinkedList();
	virtual ~DoublyLinkedList();

	Node<T>* FirstNode;
	Node<T>* LastNode;
	int Size;

	void push_back(T data);
	void push_front(T data);
	void pop_front();
	void pop_back();
	void clear();
	T Get_front();
	T Get_back();
	bool Empty();
	int Size();

};

template<typename T>
inline DoublyLinkedList<T>::DoublyLinkedList()
{
	Node<T>* FirstNode = new Node;
	Node<T>* LastNode = new Node;

	FirstNode.NextNode = LastNode;
	FirstNode.PreNode = nullptr;
	LastNode.PreNode = FirstNode;
	LastNode.NextNode = nullptr;
	Size = 0;
}

template<typename T>
inline DoublyLinkedList<T>::~DoublyLinkedList()
{
	clear();

}

template<typename T>
inline void DoublyLinkedList<T>::push_back(T data)
{
	Node<T> Temp = new Node;
	Temp.Data = T data;

	Temp.NextNode = LastNode;
	Temp.PreNode = LastNode->PreNode;
	LastNode->PreNode = Temp;

	++Size;
}

template<typename T>
inline void DoublyLinkedList<T>::push_front(T data)
{
	Node<T> Temp = new Node;
	Temp.Data = T data;

	Temp.PreNode = FirstNode;
	Temp.NextNode = FirstNode->NextNode;
	FirstNode->NextNode = Temp;

	++Size;

}

template<typename T>
inline void DoublyLinkedList<T>::pop_front()
{
	if (empty())
	{
		assert(false);
	}

	Node<T>* Temp;
	Temp = FirstNode->NextNode;

	FirstNode->NextNode = Temp->NextNode;
	Temp->PreNode = FirstNode;

	--Size;
	delete Temp;
}

template<typename T>
inline void DoublyLinkedList<T>::pop_back()
{
	if (empty())
	{
		assert(false);
	}

	Node<T>* Temp;
	LastNode->PreNode = Temp;

	LastNode->PreNode = Temp->PreNode;
	Temp->NextNode = LastNode;

	--Size;
	delete Temp;
}

template<typename T>
inline void DoublyLinkedList<T>::clear()
{
	if (empty())
	{
		assert(false);
	}

	Node<T>* DeleteNode;
	Node<T>* DepoNode;

	DeleteNode = FirstNode->NextNode;

	while (DeleteNode->NextNode != nullptr)
	{
		DepoNode = DeleteNode->NextNode;
		delete DeleteNode;
		DeleteNode = DepoNode;
	}

	FirstNode->NextNode = LastNode;
	LastNode->PreNode = FirstNode;

}

template<typename T>
inline T DoublyLinkedList<T>::Get_front()
{
	return FirstNode->NextNode->Data;
}

template<typename T>
inline T DoublyLinkedList<T>::Get_back()
{
	return LastNode->PreNode->Data;
}

template<typename T>
inline bool DoublyLinkedList<T>::Empty()
{
	return Size == 0;
}

template<typename T>
inline int DoublyLinkedList<T>::Size()
{
	return Size;
}

template<typename T>
inline Node<T>::~Node()
{
}
