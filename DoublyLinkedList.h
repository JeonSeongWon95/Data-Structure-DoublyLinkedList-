#pragma once

#include <assert.h>

template<typename T>
class ListNode //List에 들어갈 Node 하나의 class를 생성해준다.
{
	template<typename T>
	friend class DoublyLinkedList;
	//Node는 List에서 접근하여 사용하는 단위이기 때문에 생성자와 소멸자를 외부에서 접근할 수 없도록
	//private으로 선언해준다. 단, 이런 경우 LinkedList에서도 접근이 불가하므로 friend 키워드를 사용해준다.

	template<typename T>
	friend class ListIterator;

public:
	ListNode<T>* PreNode;
	//이전 노드의 주소를 저장할 변수
	ListNode<T>* NextNode;
	//다음 노드의 주소를 저장할 변수
	T Data;
	//실제 데이터를 저장할 변수

private:
	ListNode() 
	{
		PreNode = nullptr;
		NextNode = nullptr;
		//노드의 생성자에서 Ptr들을 모두 초기화 시켜준다.
	}
	
	~ListNode() 
	{
	}
};

template <typename T>
class ListIterator //List내에서 각 노드를 순회하며 원하는 노드를 가져오거나, 전체 Data를 가져오는 동작을 할 기능을 만들어주자.
{
	template <typename T>
	friend class DoublyLinkedList;
	//DoublyLinkedList에서 접근할 수 있도록 friend 처리해주도록 한다.

public:
	ListNode<T>* Iterator;
	//외부에서 접근할 수 있도록 ListNode형 포인터 하나를 멤버 변수로 선언해준다.

	ListIterator() 
	{
		Iterator = nullptr;
		//생성자에서 초기화
	}

	~ListIterator() 
	{

	}

	bool operator == (const ListIterator<T>& Other) // ==을 우리가 재정의 해주는 함수. 인자로 동일한 타입을 받아오되
													// 복사되지 않도록 & 참조로 가져오며 변하지 않도록 const로 상수화하여 받아온다.
	{
		return Iterator == Other.Iterator;
		//Iterator와 Other의 주소가 동일한지 확인하여 반환해준다.
		//Iterator는 결국 ListNode의 주소를 저장하는 포인터 변수이기 때문에 주소값을 비교하는 것이다.
	}

	bool operator != (const ListIterator<T>& Other)
	{
		//!=을 재정의하는 함수
		return Iterator != Other.Iterator;
	}

	void operator ++ ()
	{
		//증가 연산자를 재정의하는 함수. 배열의 Index처럼 증가하면 다음 노드를 Iterator가 가르키도록 설정한다.
		Iterator = Iterator->NextNode;
	}

	void operator -- ()
	{
		//증가 연산자를 재정의하는 함수. 배열의 Index처럼 감소하면 이전 노드를 Iterator가 가르키도록 설정한다.
		Iterator = Iterator->PreNode;
	}

	T operator *()
	{
		//포인터형이므로 *을 재정의하여 사용하면 내부 데이터를 가져오도록 한다.
		return Iterator->Data;
	}
};

template <typename T>
class Reverse_ListIterator //Iterator의 증감 연산자를 반대로 동작하는 Reverse 버전도 만들어보자.
{
	template <typename T>
	friend class DoublyLinkedList;
	//DoublyLinkedList에서 접근할 수 있도록 friend 처리해주도록 한다.

public:
	ListNode<T>* Iterator;
	//외부에서 접근할 수 있도록 ListNode형 포인터 하나를 멤버 변수로 선언해준다.

	Reverse_ListIterator()
	{
		Iterator = nullptr;
		//생성자에서 초기화
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
		//증가 연산자를 재정의하는 함수. 증가하면 이전 노드를 가르키도록 설정
		Iterator = Iterator->PreNode;
	}

	void operator -- ()
	{
		//증가 연산자를 재정의하는 함수. 감소하면 다음 노드를 가르키도록 설정
		Iterator = Iterator->NextNode;
	}

	T operator *()
	{
		//포인터형이므로 *을 재정의하여 사용하면 내부 데이터를 가져오도록 한다.
		return Iterator->Data;
	}
};



template<typename T>
class DoublyLinkedList
{

private:
	ListNode<T>* FirstNode;
	//처음 시작 노드를 저장할 변수
	ListNode<T>* LastNode;
	//마지막 노드를 저장할 변수
	int ListSize;
	//List의 저장된 Data의 갯수

public:


	bool Empty()
	{
		//List에 추가된 노드가 하나도 없는지 확인하는 함수
		return ListSize == 0;
	}

	int Size() const
	{
		//List에 추가된 노드의 수를 반환해주는 함수
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

		//처음에는 추가된 노드가 하나도 없으므로 First와 Last를 서로 연결해주도록 한다.

		ListSize = 0;

	}

	~DoublyLinkedList()
	{
		clear(); //First와 Last를 제외한 모든 노드를 지워주는 함수
		delete FirstNode;
		delete LastNode;
		//남아있는 First와 Last 노드도 지워주도록 한다.
	}

	void push_back(const T& data) //데이터를 뒤에 추가해주는 함수, &를 이용하여 복사해서 가져오지 않도록 설정해주고,
								  //원본 데이터에 접근하는 것이므로 값이 변화하지 않도록 const를 붙여준다.
	{
		ListNode<T>* Temp = new ListNode<T>;
		Temp->Data = data;
		//가져온 Data 값을 가지고 있는 새로운 노드를 만들어준다.

		ListNode<T>* PreTemp = LastNode->PreNode;
		//Last 노드(마지막 노드)의 바로 앞 노드를 가져온다.

		Temp->NextNode = LastNode;
		//뒤에 추가되는 노드이므로 이 노드의 뒤에 LastNode를 연결해준다.
		Temp->PreNode = LastNode->PreNode;
		//이전 노드는 LastNode 앞에 들어오게 되었으므로 LastNode이 가지고 있던 이전 노드의 주소값을 넘겨받는다.
		LastNode->PreNode = Temp;
		//LastNode의 Pre 앞 노드로 설정해준다.
		PreTemp->NextNode = Temp;
		//추가되기 전 마지막 노드의 다음을 추가된 노드로 설정해준다.

		++ListSize;
		//데이터가 추가되었으니 Size를 증가시켜준다.
	}

	void push_front(const T& data) 
	{
		ListNode<T>* Temp = new ListNode<T>;
		Temp->Data = data;
		//이번엔 데이터를 앞에 추가하는 함수를 구현한다.

		ListNode<T>* NextTemp = FirstNode->NextNode;
		//가장 앞 노드를 가져온다.(FirstNode 다음)


		Temp->PreNode = FirstNode;
		//첫번재 데이터를 저장하고 있는 노드이므로 FirstNode의 주소값을 PreNode로 저장한다. 
		Temp->NextNode = FirstNode->NextNode;
		//NextNode에는 기존에 있던 가장 앞 노드를 연결해준다.
		FirstNode->NextNode = Temp;
		//처음 노드가 가르키는 다음 값으로 설정해준다.
		NextTemp->PreNode = Temp;
		//기존에 있던 맨 앞 노드의 이전 주소로 추가한 노드의 주소값을 넣어준다.

		++ListSize;
	}

	void pop_front() 
	{
		if(Empty())
		{
			//노드가 하나도 추가가 안된 경우 예외처리하도록 한다.
			return assert(false);
		}

		ListNode<T>* DeleteNode;
		DeleteNode = FirstNode->NextNode;
		//첫번째 노드를 가져와 지울 노드로 설정한다.

		ListNode<T>* TempNode;
		TempNode = DeleteNode->NextNode;
		//지울 노드의 다음 노드를 미리 저장하도록 한다.

		FirstNode->NextNode = TempNode;
		TempNode->PreNode = FirstNode;
		//지울 노드를 제외하고 First와 노드를 연결시켜준다.

		--ListSize;
		delete DeleteNode;
		//List 사이즈를 감소시키고 Delete를 이용하여 노드를 지워준다.
	}

	void pop_back() 
	{
		if (Empty()) 
		{
			//노드가 하나도 없는 경우 예외처리 하도록 한다.
			return assert(false);
		}

		ListNode<T>* DeleteNode;
		DeleteNode = LastNode->PreNode;
		//가장 마지막 노드를 지워야 하므로 Last 노드의 이전 노드를 가져오도록 한다.

		ListNode<T>* TempNode;
		TempNode = DeleteNode->PreNode;
		//지울 노드의 이전 노드를 미리 저장한다.

		LastNode->PreNode = TempNode;
		TempNode->NextNode = LastNode;
		//지울 노드를 제외하고 마지막 노드와 Last 노드를 연결해준다.

		--ListSize;
		delete DeleteNode;
		//사이즈를 감소시키고, 지울 노드를 delete로 지워준다.
	}

	void clear() //First와 Last를 제외 모든 노드를 제거하는 함수
	{
		ListNode<T>* DeleteNode;
		//제거할 노드를 받아올 변수를 선언해준다.

		DeleteNode = FirstNode->NextNode;
		//선언한 노드는 첫번째 노드의 주소를 저장하도록 한다.

		while (DeleteNode != LastNode)
		{
			ListNode<T>* DepoNode;
			DepoNode = DeleteNode->NextNode;
			//미리 지울 노드의 다음 노드 주소를 저장해놓도록 한다.
			//저장하지 않으면 노드가 지워지고 나서 다음 노드로 접근할 수가 없다.
			delete DeleteNode;
			DeleteNode = DepoNode;
			//노드를 지워주고 아까 저장해둔 다음 노드 주소를 지울 노드로 저장한다.
		}

		FirstNode->NextNode = LastNode;
		LastNode->PreNode = FirstNode;
		//First 와 Last를 서로 연결해준다.

		ListSize = 0;
	}

	T Get_front() const
	{
		//첫번째 Data를 가져오는 함수

		if(Empty())
		{
			//가져올 데이터가 없는 경우 예외처리
			assert(false);
		}

		return FirstNode->NextNode->Data;
	}

	T Get_back() const
	{
		//마지막 Data를 가져오는 함수

		if(Empty())
		{
			//가져올 데이터가 없는 경우 예외처리
			assert(false);
		}

		return LastNode->PreNode->Data;
	}

	ListIterator<T> begin() 
	{
		//첫번째 노드를 가리키는 Iterator를 갖고있는 Iter 객체를 반환하는 함수
		ListIterator<T> Iter;
		Iter.Iterator = FirstNode->NextNode;

		return Iter;
	}

	ListIterator<T> End()
	{
		//마지막 노드를 가르키는 Iterator를 갖고있는 Iter 객체를 반환하는 함수
		ListIterator<T> Iter;
		Iter.Iterator = LastNode->PreNode;

		return Iter;
	}

	Reverse_ListIterator<T> rbegin()
	{
		//Iterator와 반대로 Begin에서 마지막 노드를 가져오도록 설정
		//증가 연산시 이전 노드로 타고 오기 때문
		Reverse_ListIterator<T> Iter;
		Iter.Iterator = LastNode->PreNode;

		return Iter;
	}

	Reverse_ListIterator<T> rEnd()
	{
		//Iterator와 반대로 End에서 첫번째 노드를 가져오도록 설정
		//감소 연산시 다음 노드로 타고 오기 때문
		Reverse_ListIterator<T> Iter;
		Iter.Iterator = FirstNode->NextNode;

		return Iter;
	}

};