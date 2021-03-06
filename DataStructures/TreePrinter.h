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
	std::queue<struct Line*>* pLineQueue;
	std::vector<struct Line*>* pLineVector;
	Tree<int>* pTree;
	void CreateLines();
	void AddLineToQueue(Line* pLine);
	void PushChildInQueue(Node<int>* pNode, enum class ChildType Type, Line* pLine);
	void PositionCursor(bool bIsFirstItem, bool bIsNewLine, int& iInitialGaps);
	void AddGaps(bool bChangeLine,int& iGaps);
	void PrintLine(Line* pLine);
	char GetColorIfRedBlack(Node<int>* pNode);
	int GetHeightIfRedBlack(Node<int>* pNode);
public:
	TreePrinter(Tree<int>* pTree);
	~TreePrinter();
	void Print();
};