#pragma once
#include "BinaryTree.h"

enum class BalanceStrategy
{
	Recolour, LeftRotation, RightRotation, LeftRightRotation, RightLeftRotation, RightRecolour, LeftRecolour, None
};

struct RedBlackNode : Node<int>
{
	bool bIsRed = true;
	int iBlackHeight = 0;
};

class RedBlackTree : public BinaryTree
{
	RedBlackNode* ToRedBlackNode(Node<int>* pNode);
public:
	RedBlackTree();
	void Add(int iValue) override;
	void Delete(int iValue) override;
};