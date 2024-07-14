#pragma once

#include <assert.h>

template<typename T>
class ListNode //List�� �� Node �ϳ��� class�� �������ش�.
{
	template<typename T>
	friend class DoublyLinkedList;
	//Node�� List���� �����Ͽ� ����ϴ� �����̱� ������ �����ڿ� �Ҹ��ڸ� �ܺο��� ������ �� ������
	//private���� �������ش�. ��, �̷� ��� LinkedList������ ������ �Ұ��ϹǷ� friend Ű���带 ������ش�.

	template<typename T>
	friend class ListIterator;

public:
	ListNode<T>* PreNode;
	//���� ����� �ּҸ� ������ ����
	ListNode<T>* NextNode;
	//���� ����� �ּҸ� ������ ����
	T Data;
	//���� �����͸� ������ ����

private:
	ListNode() 
	{
		PreNode = nullptr;
		NextNode = nullptr;
		//����� �����ڿ��� Ptr���� ��� �ʱ�ȭ �����ش�.
	}
	
	~ListNode() 
	{
	}
};

template <typename T>
class ListIterator //List������ �� ��带 ��ȸ�ϸ� ���ϴ� ��带 �������ų�, ��ü Data�� �������� ������ �� ����� ���������.
{
	template <typename T>
	friend class DoublyLinkedList;
	//DoublyLinkedList���� ������ �� �ֵ��� friend ó�����ֵ��� �Ѵ�.

public:
	ListNode<T>* Iterator;
	//�ܺο��� ������ �� �ֵ��� ListNode�� ������ �ϳ��� ��� ������ �������ش�.

	ListIterator() 
	{
		Iterator = nullptr;
		//�����ڿ��� �ʱ�ȭ
	}

	~ListIterator() 
	{

	}

	bool operator == (const ListIterator<T>& Other) // ==�� �츮�� ������ ���ִ� �Լ�. ���ڷ� ������ Ÿ���� �޾ƿ���
													// ������� �ʵ��� & ������ �������� ������ �ʵ��� const�� ���ȭ�Ͽ� �޾ƿ´�.
	{
		return Iterator == Other.Iterator;
		//Iterator�� Other�� �ּҰ� �������� Ȯ���Ͽ� ��ȯ���ش�.
		//Iterator�� �ᱹ ListNode�� �ּҸ� �����ϴ� ������ �����̱� ������ �ּҰ��� ���ϴ� ���̴�.
	}

	bool operator != (const ListIterator<T>& Other)
	{
		//!=�� �������ϴ� �Լ�
		return Iterator != Other.Iterator;
	}

	void operator ++ ()
	{
		//���� �����ڸ� �������ϴ� �Լ�. �迭�� Indexó�� �����ϸ� ���� ��带 Iterator�� ����Ű���� �����Ѵ�.
		Iterator = Iterator->NextNode;
	}

	void operator -- ()
	{
		//���� �����ڸ� �������ϴ� �Լ�. �迭�� Indexó�� �����ϸ� ���� ��带 Iterator�� ����Ű���� �����Ѵ�.
		Iterator = Iterator->PreNode;
	}

	T operator *()
	{
		//���������̹Ƿ� *�� �������Ͽ� ����ϸ� ���� �����͸� ���������� �Ѵ�.
		return Iterator->Data;
	}
};

template <typename T>
class Reverse_ListIterator //Iterator�� ���� �����ڸ� �ݴ�� �����ϴ� Reverse ������ ������.
{
	template <typename T>
	friend class DoublyLinkedList;
	//DoublyLinkedList���� ������ �� �ֵ��� friend ó�����ֵ��� �Ѵ�.

public:
	ListNode<T>* Iterator;
	//�ܺο��� ������ �� �ֵ��� ListNode�� ������ �ϳ��� ��� ������ �������ش�.

	Reverse_ListIterator()
	{
		Iterator = nullptr;
		//�����ڿ��� �ʱ�ȭ
	}

	~Reverse_ListIterator()
	{

	}

	bool operator == (const Reverse_ListIterator<T>& Other)
	{
		return Iterator == Other.Iterator;
	}

	bool operator != (const Reverse_ListIterator<T>& Other)
	{
		return Iterator != Other.Iterator;
	}

	void operator ++ ()
	{
		//���� �����ڸ� �������ϴ� �Լ�. �����ϸ� ���� ��带 ����Ű���� ����
		Iterator = Iterator->PreNode;
	}

	void operator -- ()
	{
		//���� �����ڸ� �������ϴ� �Լ�. �����ϸ� ���� ��带 ����Ű���� ����
		Iterator = Iterator->NextNode;
	}

	T operator *()
	{
		//���������̹Ƿ� *�� �������Ͽ� ����ϸ� ���� �����͸� ���������� �Ѵ�.
		return Iterator->Data;
	}
};



template<typename T>
class DoublyLinkedList
{

private:
	ListNode<T>* FirstNode;
	//ó�� ���� ��带 ������ ����
	ListNode<T>* LastNode;
	//������ ��带 ������ ����
	int ListSize;
	//List�� ����� Data�� ����

public:


	bool Empty()
	{
		//List�� �߰��� ��尡 �ϳ��� ������ Ȯ���ϴ� �Լ�
		return ListSize == 0;
	}

	int Size() const
	{
		//List�� �߰��� ����� ���� ��ȯ���ִ� �Լ�
		return ListSize;
	}

	DoublyLinkedList()
	{
		FirstNode = new ListNode<T>;
		LastNode = new ListNode<T>;

		FirstNode->NextNode = LastNode;
		FirstNode->PreNode = nullptr;
		LastNode->PreNode = FirstNode;
		LastNode->NextNode = nullptr;

		//ó������ �߰��� ��尡 �ϳ��� �����Ƿ� First�� Last�� ���� �������ֵ��� �Ѵ�.

		ListSize = 0;

	}

	~DoublyLinkedList()
	{
		clear(); //First�� Last�� ������ ��� ��带 �����ִ� �Լ�
		delete FirstNode;
		delete LastNode;
		//�����ִ� First�� Last ��嵵 �����ֵ��� �Ѵ�.
	}

	void push_back(const T& data) //�����͸� �ڿ� �߰����ִ� �Լ�, &�� �̿��Ͽ� �����ؼ� �������� �ʵ��� �������ְ�,
								  //���� �����Ϳ� �����ϴ� ���̹Ƿ� ���� ��ȭ���� �ʵ��� const�� �ٿ��ش�.
	{
		ListNode<T>* Temp = new ListNode<T>;
		Temp->Data = data;
		//������ Data ���� ������ �ִ� ���ο� ��带 ������ش�.

		ListNode<T>* PreTemp = LastNode->PreNode;
		//Last ���(������ ���)�� �ٷ� �� ��带 �����´�.

		Temp->NextNode = LastNode;
		//�ڿ� �߰��Ǵ� ����̹Ƿ� �� ����� �ڿ� LastNode�� �������ش�.
		Temp->PreNode = LastNode->PreNode;
		//���� ���� LastNode �տ� ������ �Ǿ����Ƿ� LastNode�� ������ �ִ� ���� ����� �ּҰ��� �Ѱܹ޴´�.
		LastNode->PreNode = Temp;
		//LastNode�� Pre �� ���� �������ش�.
		PreTemp->NextNode = Temp;
		//�߰��Ǳ� �� ������ ����� ������ �߰��� ���� �������ش�.

		++ListSize;
		//�����Ͱ� �߰��Ǿ����� Size�� ���������ش�.
	}

	void push_front(const T& data) 
	{
		ListNode<T>* Temp = new ListNode<T>;
		Temp->Data = data;
		//�̹��� �����͸� �տ� �߰��ϴ� �Լ��� �����Ѵ�.

		ListNode<T>* NextTemp = FirstNode->NextNode;
		//���� �� ��带 �����´�.(FirstNode ����)


		Temp->PreNode = FirstNode;
		//ù���� �����͸� �����ϰ� �ִ� ����̹Ƿ� FirstNode�� �ּҰ��� PreNode�� �����Ѵ�. 
		Temp->NextNode = FirstNode->NextNode;
		//NextNode���� ������ �ִ� ���� �� ��带 �������ش�.
		FirstNode->NextNode = Temp;
		//ó�� ��尡 ����Ű�� ���� ������ �������ش�.
		NextTemp->PreNode = Temp;
		//������ �ִ� �� �� ����� ���� �ּҷ� �߰��� ����� �ּҰ��� �־��ش�.

		++ListSize;
	}

	void pop_front() 
	{
		if(Empty())
		{
			//��尡 �ϳ��� �߰��� �ȵ� ��� ����ó���ϵ��� �Ѵ�.
			return assert(false);
		}

		ListNode<T>* DeleteNode;
		DeleteNode = FirstNode->NextNode;
		//ù��° ��带 ������ ���� ���� �����Ѵ�.

		ListNode<T>* TempNode;
		TempNode = DeleteNode->NextNode;
		//���� ����� ���� ��带 �̸� �����ϵ��� �Ѵ�.

		FirstNode->NextNode = TempNode;
		TempNode->PreNode = FirstNode;
		//���� ��带 �����ϰ� First�� ��带 ��������ش�.

		--ListSize;
		delete DeleteNode;
		//List ����� ���ҽ�Ű�� Delete�� �̿��Ͽ� ��带 �����ش�.
	}

	void pop_back() 
	{
		if (Empty()) 
		{
			//��尡 �ϳ��� ���� ��� ����ó�� �ϵ��� �Ѵ�.
			return assert(false);
		}

		ListNode<T>* DeleteNode;
		DeleteNode = LastNode->PreNode;
		//���� ������ ��带 ������ �ϹǷ� Last ����� ���� ��带 ���������� �Ѵ�.

		ListNode<T>* TempNode;
		TempNode = DeleteNode->PreNode;
		//���� ����� ���� ��带 �̸� �����Ѵ�.

		LastNode->PreNode = TempNode;
		TempNode->NextNode = LastNode;
		//���� ��带 �����ϰ� ������ ���� Last ��带 �������ش�.

		--ListSize;
		delete DeleteNode;
		//����� ���ҽ�Ű��, ���� ��带 delete�� �����ش�.
	}

	void clear() //First�� Last�� ���� ��� ��带 �����ϴ� �Լ�
	{
		ListNode<T>* DeleteNode;
		//������ ��带 �޾ƿ� ������ �������ش�.

		DeleteNode = FirstNode->NextNode;
		//������ ���� ù��° ����� �ּҸ� �����ϵ��� �Ѵ�.

		while (DeleteNode != LastNode)
		{
			ListNode<T>* DepoNode;
			DepoNode = DeleteNode->NextNode;
			//�̸� ���� ����� ���� ��� �ּҸ� �����س����� �Ѵ�.
			//�������� ������ ��尡 �������� ���� ���� ���� ������ ���� ����.
			delete DeleteNode;
			DeleteNode = DepoNode;
			//��带 �����ְ� �Ʊ� �����ص� ���� ��� �ּҸ� ���� ���� �����Ѵ�.
		}

		FirstNode->NextNode = LastNode;
		LastNode->PreNode = FirstNode;
		//First �� Last�� ���� �������ش�.

		ListSize = 0;
	}

	T Get_front() const
	{
		//ù��° Data�� �������� �Լ�

		if(Empty())
		{
			//������ �����Ͱ� ���� ��� ����ó��
			assert(false);
		}

		return FirstNode->NextNode->Data;
	}

	T Get_back() const
	{
		//������ Data�� �������� �Լ�

		if(Empty())
		{
			//������ �����Ͱ� ���� ��� ����ó��
			assert(false);
		}

		return LastNode->PreNode->Data;
	}

	ListIterator<T> begin() 
	{
		//ù��° ��带 ����Ű�� Iterator�� �����ִ� Iter ��ü�� ��ȯ�ϴ� �Լ�
		ListIterator<T> Iter;
		Iter.Iterator = FirstNode->NextNode;

		return Iter;
	}

	ListIterator<T> End()
	{
		//������ ��带 ����Ű�� Iterator�� �����ִ� Iter ��ü�� ��ȯ�ϴ� �Լ�
		ListIterator<T> Iter;
		Iter.Iterator = LastNode->PreNode;

		return Iter;
	}

	Reverse_ListIterator<T> rbegin()
	{
		//Iterator�� �ݴ�� Begin���� ������ ��带 ���������� ����
		//���� ����� ���� ���� Ÿ�� ���� ����
		Reverse_ListIterator<T> Iter;
		Iter.Iterator = LastNode->PreNode;

		return Iter;
	}

	Reverse_ListIterator<T> rEnd()
	{
		//Iterator�� �ݴ�� End���� ù��° ��带 ���������� ����
		//���� ����� ���� ���� Ÿ�� ���� ����
		Reverse_ListIterator<T> Iter;
		Iter.Iterator = FirstNode->NextNode;

		return Iter;
	}

};