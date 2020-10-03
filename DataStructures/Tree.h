#pragma once

template<typename T>
struct Node
{
	T Value;
	Node<T>* LeftChild = 0;
	Node<T>* RightChild = 0;
};

template<typename T>
class Tree
{
public:
	Tree() = default;
	virtual Node<T>* GetRootNode() = 0;
};
