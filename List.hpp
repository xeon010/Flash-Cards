#pragma once
#include <iostream>
#include <fstream>
#include "Node.hpp"


using std::cout;
using std::endl;

template <typename T>
class List
{
public:
	List()
	{
		this->pHead = nullptr;
	}
	~List()
	{
		while (this->pHead != nullptr)
		{
			Node<T>* pNext = pHead->getpNext();
			delete pHead;
			pHead = pNext;
		}
	}
	void updateLeaderBoard(PlayerCard newPlayer)
	{
		if (this->getpHead() == nullptr)
		{
			this->insertAtFront(newPlayer);
			return;
		}
		Node<T>* pCurr = this->getpHead();
		Node<T>* pPrev = nullptr;
		while (pCurr != nullptr && pCurr->getData()->score >= newPlayer.score)
		{
			pPrev = pCurr;
			pCurr = pCurr->getpNext();
		}
		Node<T>* pNew = new Node<T>(newPlayer);
		if (pPrev == nullptr) // highest score
		{
			pNew->setpNext(this->getpHead());
			pHead = pNew;
		}
		else // insert after front somewhere (in between pPrev and pCurr)
		{
			pNew->setpNext(pCurr);
			pPrev->setpNext(pNew);
		}
	}
	void clear()
	{
		while (this->pHead != nullptr)
		{
			Node<T>* pNext = pHead->getpNext();
			delete pHead;
			pHead = pNext;
		}
		this->pHead = nullptr;
	}

	Node<T>* getpHead() const
	{
		return this->pHead;
	}
	Node<T>* getpEnd()
	{
		Node<T>* pCurr = this->getpHead();
		while (pCurr->getpNext() != nullptr)
		{
			pCurr = pCurr->getpNext();
		}
		return pCurr;
	}

	void insertAtFront(const T& newData)
	{
		Node<T>* pNew = new Node<T>(newData);
		pNew->setpNext(this->pHead);
		this->pHead = pNew;
	}
	void insertAtEnd(const T& newData)
	{
		{
			if (this->pHead == nullptr)
			{
				this->pHead = new Node<T>(newData);
			}
			else
			{
				Node<T>* pCurr = this->pHead;
				while (pCurr->getpNext() != nullptr)
				{
					pCurr = pCurr->getpNext();
				}
				pCurr->setpNext(new Node<T>(newData));
			}
		}
	}
	void displayContents() const
	{
		{
			if (this->pHead == nullptr)
			{
				return;
			}


			Node<T>* pCurr = this->pHead;
			while (pCurr != nullptr)
			{
				pCurr->displayData();
				pCurr = pCurr->getpNext();
			}
		}
		std::cout << endl;
	}
	void removeatFront()
	{
		{
			if (this->pHead == nullptr)
			{
				return;
			}
			else
			{
				Node<T>* pRemoved = this->pHead;
				this->pHead = pHead->getpNext();
				delete pRemoved;
			}
		}
	}
	void removeatEnd()
	{
		if (this->pHead == nullptr)
		{
			return;
		}
		else
		{
			Node<T>* pRemoved = this->getpEnd();
			Node<T>* pCurr = this->getpHead();
			while (pCurr->getpNext()->getpNext() != nullptr)
			{
				pCurr = pCurr->getpNext();
			}
			pCurr->setpNext(nullptr);
			delete pRemoved;
		}
	}

	int sizeOf()
	{
		Node<T>* pCurr = this->getpHead();
		int count = 0;
		while (pCurr != nullptr)
		{
			count++;
			pCurr = pCurr->getpNext();
		}
		return count;
	}

	void resetList()
	{
		Node<CommandQuestion>* pCurr = pHead;
		while (pCurr != nullptr)
		{
			if (pCurr->getData()->asked == true)
			{
				pCurr->getData()->asked = false;
			}
			pCurr = pCurr->getpNext();
		}
	}

	void removeCommand(std::string name)
	{
		if (this->getpHead() == nullptr)
		{
			std::cerr << "Could not remove command: empty list\n";
			return;
		}
		Node<CommandQuestion>* pCurr = pHead;
		Node<CommandQuestion>* pPrev = nullptr;
		while (pCurr != nullptr)
		{
			if (pCurr->getData()->command == name)
			{
				if (pPrev == nullptr)
				{
					pHead = pCurr->getpNext();
				}
				else
				{
					pPrev->setpNext(pCurr->getpNext());
				}
				delete pCurr;
				return;
			}
			pPrev = pCurr;
			pCurr = pCurr->getpNext();
		}

		std::cerr << "Could not find command to delete.\n";
	}
	void writeOut(std::ofstream& outputFile);
	void displayTop3()
	{
		Node<PlayerCard>* pCurr = pHead;
		int count = 1;
		std::cout << "~~Leaderboard~~\n";
		while (pCurr != nullptr && count < 4)
		{
			std::cout << count << ". " << pCurr->getData()->name << " Points:" << pCurr->getData()->score << std::endl;
			pCurr = pCurr->getpNext();
			count++;
		}
	}
private:
	Node<T>* pHead;
	// data - need a tracker to tell if	question has been asked, right/wrong answer
};

template <>
inline void List<CommandQuestion>::writeOut(std::ofstream& outputFile)
{
	Node<CommandQuestion>* pCurr = pHead;
	while (pCurr != nullptr)
	{
		outputFile << pCurr->getData()->command << "," << pCurr->getData()->definition << "," << pCurr->getData()->points << std::endl;
		pCurr = pCurr->getpNext();
	}
}

template <>
inline void List<PlayerCard>::writeOut(std::ofstream& outputFile)
{
	Node<PlayerCard>* pCurr = pHead;
	while (pCurr != nullptr)
	{
		outputFile << pCurr->getData()->name << "," << pCurr->getData()->score << "\n";
		pCurr = pCurr->getpNext();
	}
}
