#pragma once

template<typename T>
struct Node
{
	T Value;
	Node* LeftChild;
	Node* RightChild;
};

template<typename T>
class Tree
{
public:
	Tree() = default;
	virtual Node<T>* GetRootNode() = 0;
};
