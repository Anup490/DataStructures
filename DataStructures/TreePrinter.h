#pragma once

namespace std
{
	template <class _Ty>
	class allocator;

	template <class _Ty, class _Alloc = allocator<_Ty>>
	class deque;

	template <class _Ty, class _Container = deque<_Ty>>
	class queue;

	template <class _Ty, class _Alloc = allocator<_Ty>>
	class vector;
}

template<typename T>
class Tree;

template<typename T>
class Node;

class TreePrinter
{
	std::queue<Node<int>*>* pNodeQueue;
	std::vector<struct Line*>* pLines;
	void CreateLines();
	void AddLineToQueue();
public:
	TreePrinter(Tree<Node<int>*>* pTree);
	void Print();
};