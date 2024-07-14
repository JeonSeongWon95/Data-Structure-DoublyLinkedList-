#include "DoublyLinkedList.h"
#include <iostream>

using namespace std;

int main()
{
	DoublyLinkedList<int> MyIntList;

	for(int i = 0; i < 100; ++i)
	{
		MyIntList.push_back(i);
	}
	
	cout << MyIntList.Size() << endl;

	ListIterator<int> iter;
	Reverse_ListIterator<int> R_iter;

	for(iter = MyIntList.begin(); iter != MyIntList.End(); ++iter)
	{
		cout << *iter << endl;
	}

	for(R_iter = MyIntList.rbegin(); R_iter != MyIntList.rEnd(); ++R_iter)
	{
		cout << *R_iter << endl;
	}

	return 0;
}