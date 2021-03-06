#pragma once
#include "Tree.h"

namespace std
{
	template <class _Elem>
	class initializer_list;

	template <class _Ty>
	class allocator;

	template <class _Ty, class _Container = allocator<_Ty>>
	class deque;

	template <class _Ty, class _Container = deque<_Ty>>
	class queue;
}

using namespace std;

class Heap : public Tree<int>
{
	Node<int>* pRoot;
	queue<Node<int>*>* pQueue;
	bool bShouldAddNode;
	void CreateHeap(initializer_list<int>* pList);
	void TraverseAndAddItem(Node<int>* pNode, int iItem);
	void AddOneEmptyNodeIfNeeded(Node<int>* pParent);
	void SwapIfNewIsSmaller(Node<int>* pNode, int& iNewItem);
	void DeleteNodes(Node<int>* pNode);
public:
	Heap(initializer_list<int>* pList);
	~Heap();
	Node<int>* GetRootNode() override;
};