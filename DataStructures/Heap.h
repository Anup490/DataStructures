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
	bool bAddNode;
	void AddToHeap(Node<int>* pNode, int iItem);
public:
	Heap(std::initializer_list<int>* pList);
	Node<int>* GetRootNode() override;
};