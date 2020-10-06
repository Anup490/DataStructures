#include "Heap.h"
#include <initializer_list>
#include <queue>
#include <iostream>

Heap::Heap(std::initializer_list<int>* pList)
{
	pRoot = new Node<int>;
	pRoot->Value = -1;
	pQueue = new queue<Node<int>*>;
	for (int i : *pList)
	{
		bAddNode = true;
		pQueue->push(pRoot);
		AddToHeap(pQueue->front(), i);
	}
}

Node<int>* Heap::GetRootNode()
{
	return pRoot;
}

void Heap::AddToHeap(Node<int>* pNode, int iItem)
{
	if (bAddNode)
	{
		if (!pNode->LeftChild)
		{
			pNode->LeftChild = new Node<int>;
			pNode->LeftChild->Value = -1;
			bAddNode = false;
		}
		else if (!pNode->RightChild)
		{
			pNode->RightChild = new Node<int>;
			pNode->RightChild->Value = -1;
			bAddNode = false;
		}
	}
	if (pNode->LeftChild)
	{
		pQueue->push(pNode->LeftChild);
	}
	if (pNode->RightChild)
	{
		pQueue->push(pNode->RightChild);
	}
	Node<int>* pTopNode = pQueue->front();
	pQueue->pop();
	if ((iItem < pTopNode->Value) || (pTopNode->Value < 0))
	{
		int iTemp = pTopNode->Value;
		pTopNode->Value = iItem;
		iItem = iTemp;
	}
	if (!pQueue->empty())
	{
		AddToHeap(pQueue->front(), iItem);
	}
}


