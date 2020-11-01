#include "RedBlackTree.h"

RedBlackTree::RedBlackTree()
{
	pRoot = 0;
}

void RedBlackTree::Add(int iValue) 
{
	if (pRoot)
	{
		RedBlackNode* pNode = new RedBlackNode;
		pNode->Value = iValue;
		pNode->bIsRed = true;
		pNode->iBlackHeight = 1;
		ApplyBinaryInsertion(pRoot, pNode);
		UpdateBlackHeight(ToRedBlackNode(pRoot));
		EnsureRedBlackRule(ToRedBlackNode(pRoot), nullptr);
	}
	else
	{
		pRoot = new RedBlackNode;
		pRoot->Value = iValue;
		RedBlackNode* pRedBlackRoot = ToRedBlackNode(pRoot);
		pRedBlackRoot->bIsRed = false;
		pRedBlackRoot->iBlackHeight = 2;
	}
}

void RedBlackTree::Delete(int iValue) 
{
	ApplyBinaryDeletion(nullptr, pRoot, iValue);
}

void RedBlackTree::UpdateBlackHeight(RedBlackNode* pNode)
{
	if (pNode->LeftChild)
	{
		UpdateBlackHeight(ToRedBlackNode(pNode->LeftChild));
	}
	if (pNode->RightChild)
	{
		UpdateBlackHeight(ToRedBlackNode(pNode->RightChild));
	}
	RedBlackNode* pLChild = ToRedBlackNode(pNode->LeftChild);
	RedBlackNode* pRChild = ToRedBlackNode(pNode->RightChild);
	BalanceChildrenBlackHeight(pLChild, pRChild);
	int iChildHeight = (pLChild && pRChild) ? (pLChild->iBlackHeight) : 1;
	pNode->iBlackHeight = (pNode->bIsRed) ? iChildHeight : ++iChildHeight;
}

void RedBlackTree::BalanceChildrenBlackHeight(RedBlackNode* pLChild, RedBlackNode* pRChild)
{
	if (!pRChild && pLChild && ((pLChild->iBlackHeight) != 1))
	{
		ReduceBlackHeight(pLChild);
	}
	else if (!pLChild && pRChild && ((pRChild->iBlackHeight) != 1))
	{
		ReduceBlackHeight(pRChild);
	}
	else if (pLChild && pRChild && ((pLChild->iBlackHeight) > (pRChild->iBlackHeight)))
	{
		ReduceBlackHeight(pLChild);
	}
	else if (pLChild && pRChild && ((pLChild->iBlackHeight) < (pRChild->iBlackHeight)))
	{
		ReduceBlackHeight(pRChild);
	}
}

void RedBlackTree::ReduceBlackHeight(RedBlackNode* pNode)
{
	if (pNode->bIsRed)
	{
		RedBlackNode* pLChild = ToRedBlackNode(pNode->LeftChild);
		RedBlackNode* pRChild = ToRedBlackNode(pNode->RightChild);
		if (pLChild)
		{
			pLChild->bIsRed = true;
			(pLChild->iBlackHeight)--;
		}
		if (pRChild)
		{
			pRChild->bIsRed = true;
			(pRChild->iBlackHeight)--;
		}
	}
	else
	{
		pNode->bIsRed = true;
	}
	(pNode->iBlackHeight)--;
}

void RedBlackTree::EnsureRedBlackRule(RedBlackNode* pNode, RedBlackNode* pParent)
{
	if (pNode->LeftChild)
	{
		EnsureRedBlackRule(ToRedBlackNode(pNode->LeftChild), pNode);
	}
	if (pNode->RightChild)
	{
		EnsureRedBlackRule(ToRedBlackNode(pNode->RightChild), pNode);
	}
	FixRedBlackIssue(pNode,pParent);
}

void RedBlackTree::FixRedBlackIssue(RedBlackNode* pNode, RedBlackNode* pParent)
{
	BalanceStrategy Strategy = GetBalanceStrategy(pNode);
	if (Strategy != BalanceStrategy::None)
	{
		if (Strategy == BalanceStrategy::Recolour)
		{
			ApplyRecolouring(pNode);
		}
		else
		{
			ApplyRotation(pNode,pParent,Strategy);
			bool bAppliedHeightFix = false;
			UpdateBlackHeight(ToRedBlackNode(pRoot));
			EnsureRedBlackRule(ToRedBlackNode(pRoot), nullptr);
		}
	}
}

BalanceStrategy RedBlackTree::GetBalanceStrategy(RedBlackNode* pNode)
{
	if (!(pNode->bIsRed))
	{
		RedBlackNode* pLChild = ToRedBlackNode(pNode->LeftChild);
		RedBlackNode* pRChild = ToRedBlackNode(pNode->RightChild);
		if (IsRedNode(pLChild) && IsRedNode(pLChild->LeftChild))
		{
			return (IsRedNode(pRChild)) ? (BalanceStrategy::Recolour) : (BalanceStrategy::RightRotation);
		}
		else if (IsRedNode(pLChild) && IsRedNode(pLChild->RightChild))
		{
			return (IsRedNode(pRChild)) ? (BalanceStrategy::Recolour) : (BalanceStrategy::LeftRightRotation);
		}
		else if (IsRedNode(pRChild) && IsRedNode(pRChild->LeftChild))
		{
			return (IsRedNode(pLChild)) ? (BalanceStrategy::Recolour) : (BalanceStrategy::RightLeftRotation);
		}
		else if (IsRedNode(pRChild) && IsRedNode(pRChild->RightChild))
		{
			return (IsRedNode(pLChild)) ? (BalanceStrategy::Recolour) : (BalanceStrategy::LeftRotation);
		}
	}
	return BalanceStrategy::None;
}

bool RedBlackTree::IsRedNode(Node<int>* pNode)
{
	RedBlackNode* pRBNode = ToRedBlackNode(pNode);
	return (pRBNode && (pRBNode->bIsRed));
}

void RedBlackTree::ApplyRecolouring(RedBlackNode* pNode)
{
	RedBlackNode* pLChild = ToRedBlackNode(pNode->LeftChild);
	RedBlackNode* pRChild = ToRedBlackNode(pNode->RightChild);
	pNode->bIsRed = !(pNode->bIsRed);
	pLChild->bIsRed = !(pLChild->bIsRed);
	pRChild->bIsRed = !(pRChild->bIsRed);
}

void RedBlackTree::ApplyRotation(RedBlackNode* pNode, RedBlackNode* pParent, BalanceStrategy Strategy)
{
	switch (Strategy)
	{
		case BalanceStrategy::LeftRightRotation:
		{
			FlipNodesColour(pNode, ToRedBlackNode(pNode->LeftChild->RightChild));
			ApplyLeftRightRotation(pNode, pParent);
			break;
		}
		case BalanceStrategy::RightLeftRotation:
		{
			FlipNodesColour(pNode, ToRedBlackNode(pNode->RightChild->LeftChild));
			ApplyRightLeftRotation(pNode, pParent);
			break;
		}
		case BalanceStrategy::LeftRotation:
		{
			FlipNodesColour(pNode, ToRedBlackNode(pNode->RightChild));
			ApplyLeftRotation(pNode, pParent);
			break;
		}
		case BalanceStrategy::RightRotation:
		{
			FlipNodesColour(pNode, ToRedBlackNode(pNode->LeftChild));
			ApplyRightRotation(pNode, pParent);
			break;
		}
	}
}

void RedBlackTree::FlipNodesColour(RedBlackNode* pBlackNode, RedBlackNode* pRedNode)
{
	pBlackNode->bIsRed = true;
	pRedNode->bIsRed = false;
}

void RedBlackTree::ApplyLeftRightRotation(RedBlackNode* pNode, RedBlackNode* pParent)
{
	ApplyLeftRotation(ToRedBlackNode(pNode->LeftChild), pNode);
	ApplyRightRotation(pNode, pParent);
}

void RedBlackTree::ApplyRightLeftRotation(RedBlackNode* pNode, RedBlackNode* pParent)
{
	ApplyRightRotation(ToRedBlackNode(pNode->RightChild), pNode);
	ApplyLeftRotation(pNode, pParent);
}

void RedBlackTree::ApplyLeftRotation(RedBlackNode* pNode, RedBlackNode* pParent)
{
	RedBlackNode* pNewNode = ToRedBlackNode(pNode->RightChild);
	AttachChild(pNewNode, pNode, ChildType::Left);
	pNode->RightChild = nullptr;
	ReplaceNode(pNode, pNewNode, pParent);
	ToRedBlackNode(pRoot)->bIsRed = false;
}

void RedBlackTree::ApplyRightRotation(RedBlackNode* pNode, RedBlackNode* pParent)
{
	RedBlackNode* pNewNode = ToRedBlackNode(pNode->LeftChild);
	AttachChild(pNewNode, pNode, ChildType::Right);
	pNode->LeftChild = nullptr;
	ReplaceNode(pNode, pNewNode, pParent);
	ToRedBlackNode(pRoot)->bIsRed = false;
}

void RedBlackTree::AttachChild(RedBlackNode* pParent, RedBlackNode* pChild, ChildType Type)
{
	if (Type == ChildType::Left)
	{
		AttachAsLeftChild(pParent, pChild);
	}
	else if (Type == ChildType::Right)
	{
		AttachAsRightChild(pParent, pChild);
	}
}

void RedBlackTree::AttachAsLeftChild(RedBlackNode* pParent, RedBlackNode* pChild)
{
	if (!(pParent->LeftChild))
	{
		pParent->LeftChild = pChild;
	}
	else
	{
		AttachAsLeftChild(ToRedBlackNode(pParent->LeftChild), pChild);
	}
}

void RedBlackTree::AttachAsRightChild(RedBlackNode* pParent, RedBlackNode* pChild)
{
	if (!(pParent->RightChild))
	{
		pParent->RightChild = pChild;
	}
	else
	{
		AttachAsRightChild(ToRedBlackNode(pParent->RightChild), pChild);
	}
}

RedBlackNode* RedBlackTree::ToRedBlackNode(Node<int>* pNode)
{
	return static_cast<RedBlackNode*>(pNode);
}