#pragma once
#include "Tree.h"

class BinaryTree : public Tree<int>
{
	Node<int>* GetSuccessor(Node<int>* pNode);
	Node<int>* GetInorderSuccessor(Node<int>* pNode);
	void AttachToRightSubTree(Node<int>* pNode, Node<int>* pParent, ChildType Type);
	void ReplaceNode(Node<int>* pOld, Node<int>* pNew, Node<int>* pParent);
protected:
	Node<int>* pRoot;
	void ApplyBinaryInsertion(Node<int>* pNode, Node<int>* pNewNode);
	void ApplyBinaryDeletion(Node<int>* pParent, Node<int>* pNode, int iValue);
public:
	BinaryTree();
	virtual void Add(int iValue);
	virtual void Delete(int iValue);
	virtual Node<int>* GetRootNode() override;
};
