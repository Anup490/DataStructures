#pragma once
#include <vector>
#include <list>
using namespace std;

class HashKey
{
public:
	virtual int GetHashValue() = 0;
};

template<typename T>
struct Entry
{
	HashKey* pKey;
	T Value;
};

template<typename T>
class HashTable
{
	vector<list<Entry<T>*>*>* pVector;
public:
	HashTable()
	{
		pVector = new vector<list<Entry<T>*>*>;
		for (int i=0; i<5; i++)
		{
			list<Entry<T>*>* pList = new list<Entry<T>*>;
			pVector->push_back(pList);
		}
	}

	~HashTable()
	{
		for (list<Entry<T>*>* pList : *pVector)
		{
			delete pList;
		}
		delete pVector;
	}

	void AddItem(Entry<T>* pEntry)
	{
		AddAt(pEntry->pKey->GetHashValue(), pEntry);
	}

	T GetItem(HashKey* pKey)
	{
		return GetAt(pKey->GetHashValue(), pKey);
	}

private:
	void AddAt(int position, Entry<T>* pEntry)
	{
		if (position > pVector->size())
		{
			pVector->resize(position + 1, NULL);
		}
		list<Entry<T>*>* pList = pVector->at(position);
		if (pList)
		{
			pList->push_back(pEntry);
		}
		else
		{
			pList = new list<Entry<T>*>;
			pList->push_back(pEntry);
			int i = 0;
			for (auto it = pVector->begin(); it != pVector->end(); it++)
			{
				if (i == position)
				{
					*it = pList;
					break;
				}
				else
				{
					i++;
					continue;
				}
			}
		}
	}

	T GetAt(int position, HashKey* pKey)
	{
		list<Entry<T>*>* pList = pVector->at(position);
		for (Entry<T>* pEntry : *pList)
		{
			if (pKey == (pEntry->pKey))
			{
				return pEntry->Value;
			}
		}
		return NULL;
	}
};