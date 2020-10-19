#include "Heap.h"
#include <initializer_list>
#include <queue>
#include <iostream>

Heap::Heap(initializer_list<int>* pList)
{
	pRoot = new Node<int>;
	pRoot->Value = -1;
	pQueue = new queue<Node<int>*>;
	CreateHeap(pList);
}

Heap::~Heap()
{
	DeleteNodes(pRoot);
}

Node<int>* Heap::GetRootNode()
{
	return pRoot;
}

void Heap::CreateHeap(initializer_list<int>* pList)
{
	for (int i : *pList)
	{
		bShouldAddNode = true;
		pQueue->push(pRoot);
		TraverseAndAddItem(pQueue->front(), i);
	}
}

void Heap::TraverseAndAddItem(Node<int>* pNode, int iNewItem)
{
	AddOneEmptyNodeIfNeeded(pNode);
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
	SwapIfNewIsSmaller(pTopNode, iNewItem);
	if (!pQueue->empty())
	{
		TraverseAndAddItem(pQueue->front(), iNewItem);
	}
}

void Heap::AddOneEmptyNodeIfNeeded(Node<int>* pParent)
{
	if (bShouldAddNode && (pParent->Value != -1))
	{
		if (!pParent->LeftChild)
		{
			pParent->LeftChild = new Node<int>;
			pParent->LeftChild->Value = -1;
			bShouldAddNode = false;
		}
		else if ((!pParent->RightChild) && (pParent->LeftChild->Value != -1))
		{
			pParent->RightChild = new Node<int>;
			pParent->RightChild->Value = -1;
			bShouldAddNode = false;
		}
	}
}

void Heap::SwapIfNewIsSmaller(Node<int>* pNode, int& iNewItem)
{
	if ((iNewItem < pNode->Value) || (pNode->Value < 0))
	{
		int iTemp = pNode->Value;
		pNode->Value = iNewItem;
		iNewItem = iTemp;
	}
}

void Heap::DeleteNodes(Node<int>* pNode)
{
	if (pNode->LeftChild)
	{
		DeleteNodes(pNode->LeftChild);
	}
	if (pNode->RightChild)
	{
		DeleteNodes(pNode->RightChild);
	}
	delete pNode;
}