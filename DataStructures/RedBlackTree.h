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
	void UpdateBlackHeight(RedBlackNode* pNode);
	void EnsureRedBlackRule(RedBlackNode* pNode, RedBlackNode* pParent);
	void FixRedBlackIssue(RedBlackNode* pNode, RedBlackNode* pParent);
	BalanceStrategy GetBalanceStrategy(RedBlackNode* pNode);
	bool IsRedNode(Node<int>* pNode);
	void ApplyRecolouring(RedBlackNode* pNode);
	void ApplyRotation(RedBlackNode* pNode, RedBlackNode* pParent, BalanceStrategy Strategy);
	void ApplyLeftRightRotation(RedBlackNode* pNode, RedBlackNode* pParent);
	void ApplyRightLeftRotation(RedBlackNode* pNode, RedBlackNode* pParent);
	void ApplyLeftRotation(RedBlackNode* pNode, RedBlackNode* pParent);
	void ApplyRightRotation(RedBlackNode* pNode, RedBlackNode* pParent);
	void AttachChild(RedBlackNode* pParent, RedBlackNode* pChild, ChildType Type);
	void AttachAsLeftChild(RedBlackNode* pParent, RedBlackNode* pChild);
	void AttachAsRightChild(RedBlackNode* pParent, RedBlackNode* pChild);
	RedBlackNode* ToRedBlackNode(Node<int>* pNode);
public:
	RedBlackTree();
	void Add(int iValue) override;
	void Delete(int iValue) override;
};