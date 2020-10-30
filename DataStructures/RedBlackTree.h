#pragma once
#include "Tree.h"

enum class BalanceStrategy
{
	Recolour, LeftRotation, RightRotation, LeftRightRotation, RightLeftRotation, RightRecolour, LeftRecolour, None
};

struct RedBlackNode : Node<int>
{
	bool bIsRed = true;
	int iBlackHeight = 0;
};

class RedBlackTree : public Tree<int>
{
	RedBlackNode* pRoot;

	void ApplyBinaryInsertion(RedBlackNode* pNode, RedBlackNode* pNewNode)
	{
		if ((pNewNode->Value) < (pNode->Value))
		{
			if (pNode->LeftChild)
			{
				ApplyBinaryInsertion(ToRedBlackNode(pNode->LeftChild), pNewNode);
			}
			else
			{
				pNode->LeftChild = pNewNode;
			}
		}
		else if ((pNewNode->Value) > (pNode->Value))
		{
			if (pNode->RightChild)
			{
				ApplyBinaryInsertion(ToRedBlackNode(pNode->RightChild), pNewNode);
			}
			else
			{
				pNode->RightChild = pNewNode;
			}
		}
	}

	void ApplyBinaryDeletion(RedBlackNode* pParent, RedBlackNode* pNode, int iValue)
	{
		if ((pNode->Value) == iValue)
		{
			ReplaceNode(pNode, GetSuccessor(pNode), pParent);
			delete pNode;
		}
		else if ((iValue < (pNode->Value)) && (pNode->LeftChild))
		{
			ApplyBinaryDeletion(pNode, ToRedBlackNode(pNode->LeftChild), iValue);
		}
		else if ((iValue > (pNode->Value)) && (pNode->RightChild))
		{
			ApplyBinaryDeletion(pNode, ToRedBlackNode(pNode->RightChild), iValue);
		}
	}

	RedBlackNode* GetSuccessor(RedBlackNode* pNode)
	{
		RedBlackNode* pSuccessorNode = nullptr;
		if (pNode->RightChild)
		{
			pSuccessorNode = GetInorderSuccessor(ToRedBlackNode(pNode->RightChild));
			pSuccessorNode->LeftChild = pNode->LeftChild;
			AttachToRightSubTree(ToRedBlackNode(pNode->RightChild), pSuccessorNode, ChildType::Right);
		}
		else if (pNode->LeftChild)
		{
			pSuccessorNode = ToRedBlackNode(pNode->LeftChild);
		}
		return pSuccessorNode;
	}

	RedBlackNode* GetInorderSuccessor(RedBlackNode* pNode)
	{
		if (!(pNode->LeftChild))
		{
			return pNode;
		}
		return GetInorderSuccessor(ToRedBlackNode(pNode->LeftChild));
	}

	void AttachToRightSubTree(RedBlackNode* pNode, RedBlackNode* pParent, ChildType Type)
	{
		if (pParent && (pNode != pParent))
		{
			if (pParent->RightChild)
			{
				AttachToRightSubTree(pNode, ToRedBlackNode(pParent->RightChild), ChildType::Right);
			}
			else
			{
				pParent->RightChild = pNode;
			}
		}
	}

	void ReplaceNode(RedBlackNode* pOld, RedBlackNode* pNew, RedBlackNode* pParent)
	{
		if (pParent)
		{
			if ((pParent->LeftChild) == pOld)
			{
				pParent->LeftChild = pNew;
			}
			else if ((pParent->RightChild) == pOld)
			{
				pParent->RightChild = pNew;
			}
		}
		else
		{
			pRoot = pNew;
		}
	}

	RedBlackNode* ToRedBlackNode(Node<int>* pNode)
	{
		return static_cast<RedBlackNode*>(pNode);
	}

public:
	RedBlackTree()
	{
		pRoot = 0;
	}

	RedBlackNode* GetRootNode() override
	{
		return pRoot;
	}

	void Add(int iValue)
	{
		if (pRoot)
		{
			RedBlackNode* pNode = new RedBlackNode;
			pNode->Value = iValue;
			ApplyBinaryInsertion(pRoot, pNode);
		}
		else
		{
			pRoot = new RedBlackNode;
			pRoot->Value = iValue;
		}
	}

	void Delete(int iValue)
	{
		ApplyBinaryDeletion(nullptr, pRoot, iValue);
	}
};