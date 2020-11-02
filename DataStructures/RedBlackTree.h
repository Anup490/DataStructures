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
	RedBlackNode* CreateNewNode(int iValue);
	void UpdateBlackHeight(RedBlackNode* pNode);
	void BalanceChildrenBlackHeight(RedBlackNode* pLChild, RedBlackNode* pRChild);
	void ReduceBlackHeight(RedBlackNode* pNode);
	void ConvertToRedNode(RedBlackNode* pBlackNode);
	void EnsureRedBlackRuleInTreeAfterInsertion(RedBlackNode* pNode, RedBlackNode* pParent);
	void EnsureRedBlackRuleAfterInsertion(RedBlackNode* pNode, RedBlackNode* pParent);
	BalanceStrategy GetBalanceStrategyForInsertion(RedBlackNode* pNode);
	bool IsRedNode(Node<int>* pNode);
	void ApplyRecolouring(RedBlackNode* pNode);
	void RaiseBlackHeightIfBlack(RedBlackNode* pNode);
	RedBlackNode* GetBalancedNode(RedBlackNode* pNode, RedBlackNode* pParent, BalanceStrategy Strategy);
	void FlipNodesColour(RedBlackNode* pBlackNode, RedBlackNode* pRedNode);
	RedBlackNode* GetBalancedNodeByLeftRightRotation(RedBlackNode* pNode, RedBlackNode* pParent);
	RedBlackNode* GetBalancedNodeByRightLeftRotation(RedBlackNode* pNode, RedBlackNode* pParent);
	RedBlackNode* GetBalancedNodeByLeftRotation(RedBlackNode* pNode, RedBlackNode* pParent);
	RedBlackNode* GetBalancedNodeByRightRotation(RedBlackNode* pNode, RedBlackNode* pParent);
	void AttachChild(RedBlackNode* pParent, RedBlackNode* pChild, ChildType Type);
	void AttachAsLeftChild(RedBlackNode* pParent, RedBlackNode* pChild);
	void AttachAsRightChild(RedBlackNode* pParent, RedBlackNode* pChild);
	void EnsureRedBlackRuleInRoot(RedBlackNode* pRoot);
	void OnDelete(Node<int>* pReplacedNode) override;
	void EnsureRedBlackRuleInTreeAfterDeletion(RedBlackNode* pNode, RedBlackNode* pParent);
	void EnsureRedBlackRuleAfterDeletion(RedBlackNode* pNode, RedBlackNode* pParent);
	RedBlackNode* GetSiblingOfDoubleBlack(RedBlackNode* pNode);
	bool IsChildDoubleBlack(RedBlackNode* pNode, RedBlackNode* pChild);
	BalanceStrategy GetBalanceStrategyForDeletion(RedBlackNode* pParent, RedBlackNode* pChild);
	bool IsRedOrNullNode(Node<int>* pNode);
	void ApplyBalanceStrategyForDeletion(RedBlackNode* pNode, RedBlackNode* pParent, BalanceStrategy Strategy);
	RedBlackNode* ToRedBlackNode(Node<int>* pNode);
public:
	RedBlackTree();
	void Add(int iValue) override;
	void Delete(int iValue) override;
};