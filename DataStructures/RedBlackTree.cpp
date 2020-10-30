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
			if ((Strategy == BalanceStrategy::LeftRotation) || (Strategy == BalanceStrategy::LeftRightRotation))
			{
				CheckBlackHeight(ToRedBlackNode(pNode->LeftChild));
			}
			else if ((Strategy == BalanceStrategy::RightRotation) || (Strategy == BalanceStrategy::RightLeftRotation))
			{
				CheckBlackHeight(ToRedBlackNode(pNode->RightChild));
			}
			FixRedBlackIssue(pNode,pParent);
		}
	}
}

BalanceStrategy RedBlackTree::GetBalanceStrategy(RedBlackNode* pNode)
{
	if (!(pNode->bIsRed))
	{
		RedBlackNode* pLChild = ToRedBlackNode(pNode->LeftChild);
		RedBlackNode* pRChild = ToRedBlackNode(pNode->RightChild);
		if (pLChild && (pLChild->bIsRed))
		{
			if ((pLChild->LeftChild) && (ToRedBlackNode(pLChild->LeftChild)->bIsRed))
			{
				return (pRChild && (pRChild->bIsRed)) ? (BalanceStrategy::Recolour) : (BalanceStrategy::RightRotation);
			}
			if ((pLChild->RightChild) && (ToRedBlackNode(pLChild->RightChild)->bIsRed))
			{
				return (pRChild && (pRChild->bIsRed)) ? (BalanceStrategy::Recolour) : (BalanceStrategy::LeftRightRotation);
			}
		}
		else if (pRChild && (pRChild->bIsRed))
		{
			if ((pRChild->LeftChild) && (ToRedBlackNode(pRChild->LeftChild)->bIsRed))
			{
				return (pLChild && (pLChild->bIsRed)) ? (BalanceStrategy::Recolour) : (BalanceStrategy::RightLeftRotation);
			}
			if ((pRChild->RightChild) && (ToRedBlackNode(pRChild->RightChild)->bIsRed))
			{
				return (pLChild && (pLChild->bIsRed)) ? (BalanceStrategy::Recolour) : (BalanceStrategy::LeftRotation);
			}
		}
	}
	return BalanceStrategy::None;
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
		RedBlackNode* pLRChild = ToRedBlackNode(pNode->LeftChild->RightChild);
		pNode->bIsRed = true;
		pLRChild->bIsRed = false;
		ApplyLeftRightRotation(pNode, pParent);
		break;
	}
	case BalanceStrategy::RightLeftRotation:
	{
		RedBlackNode* pRLChild = ToRedBlackNode(pNode->RightChild->LeftChild);
		pNode->bIsRed = true;
		pRLChild->bIsRed = false;
		ApplyRightLeftRotation(pNode, pParent);
		break;
	}
	case BalanceStrategy::LeftRotation:
	{
		RedBlackNode* pRChild = ToRedBlackNode(pNode->RightChild);
		pNode->bIsRed = true;
		pRChild->bIsRed = false;
		ApplyLeftRotation(pNode, pParent);
		break;
	}
	case BalanceStrategy::RightRotation:
	{
		RedBlackNode* pLChild = ToRedBlackNode(pNode->LeftChild);
		pNode->bIsRed = true;
		pLChild->bIsRed = false;
		ApplyRightRotation(pNode, pParent);
		break;
	}
	}
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
}

void RedBlackTree::ApplyRightRotation(RedBlackNode* pNode, RedBlackNode* pParent)
{
	RedBlackNode* pNewNode = ToRedBlackNode(pNode->LeftChild);
	AttachChild(pNewNode, pNode, ChildType::Right);
	pNode->LeftChild = nullptr;
	ReplaceNode(pNode, pNewNode, pParent);
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

void RedBlackTree::CheckBlackHeight(RedBlackNode* pNode)
{
	if (pNode)
	{
		if (pNode->LeftChild)
		{
			CheckBlackHeight(ToRedBlackNode(pNode->LeftChild));
		}
		if (pNode->RightChild)
		{
			CheckBlackHeight(ToRedBlackNode(pNode->RightChild));
		}
		SetBlackHeight(pNode);
	}
}

void RedBlackTree::SetBlackHeight(RedBlackNode* pNode)
{
	if (!(pNode->LeftChild) || !(pNode->RightChild))
	{
		pNode->iBlackHeight = (pNode->bIsRed) ? 1 : 2;
	}
	else if ((ToRedBlackNode(pNode->LeftChild)->iBlackHeight) == (ToRedBlackNode(pNode->RightChild)->iBlackHeight))
	{
		RedBlackNode* pLChild = ToRedBlackNode(pNode->LeftChild);
		int iChildHeight = pLChild->iBlackHeight;
		pNode->iBlackHeight = (pNode->bIsRed) ? iChildHeight : ++iChildHeight;
	}
	else
	{
		RedBlackNode* pLChild = ToRedBlackNode(pNode->LeftChild);
		RedBlackNode* pRChild = ToRedBlackNode(pNode->RightChild);
		if ((pLChild->iBlackHeight) != (pRChild->iBlackHeight))
		{
			FixBlackHeight(((pLChild->iBlackHeight) > (pRChild->iBlackHeight)) ? pLChild : pRChild);
		}
	}
}

void RedBlackTree::FixBlackHeight(RedBlackNode* pNode)
{
	if (!(pNode->bIsRed))
	{
		pNode->bIsRed = true;
		(pNode->iBlackHeight)--;
	}
}

RedBlackNode* RedBlackTree::ToRedBlackNode(Node<int>* pNode)
{
	return static_cast<RedBlackNode*>(pNode);
}