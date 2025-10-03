#pragma once
#include "Data.hpp"
#include <iostream>

using std::cout;
using std::endl;

template <typename T>
class Node
{
public:
	Node(const T& newData) : data(newData), pNext(nullptr) {}

	~Node() 
	{
		/*cout << "Node containing ";
		displayData();
		cout << "destroyed.\n";*/
	} // destructor (debugging)

	Node<T>* getpNext() const 
	{
		return pNext;
	}
	T* getData()
	{
		return &data;
	}
	void setpNext(Node<T>* next)
	{
		this->pNext = next;
	}
	void setdata(T newData)
	{
		data = newData;
	}
	void displayData()
	{
		cout << data << endl;
	}

private:
	Node<T>* pNext;
	T data;
};
