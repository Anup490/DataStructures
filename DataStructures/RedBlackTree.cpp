#include "RedBlackTree.h"

RedBlackTree::RedBlackTree()
{
	pRoot = 0;
}

void RedBlackTree::Add(int iValue) 
{
	if (pRoot)
	{
		RedBlackNode* pNode = CreateNewNode(iValue);
		ApplyBinaryInsertion(pRoot, pNode);
		EnsureRedBlackRuleInTreeAfterInsertion(ToRedBlackNode(pRoot), nullptr);
	}
	else
	{
		pRoot = CreateNewNode(iValue);
	}
	EnsureRedBlackRuleInRoot(ToRedBlackNode(pRoot));
}

RedBlackNode* RedBlackTree::CreateNewNode(int iValue)
{
	RedBlackNode* pNode = new RedBlackNode;
	pNode->Value = iValue;
	pNode->bIsRed = true;
	pNode->iBlackHeight = 1;
	return pNode;
}

void RedBlackTree::Delete(int iValue) 
{
	ApplyBinaryDeletion(nullptr, pRoot, iValue);
	EnsureRedBlackRuleInTreeAfterDeletion(ToRedBlackNode(pRoot), nullptr);
	EnsureRedBlackRuleInRoot(ToRedBlackNode(pRoot));
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
		ConvertToRedNode(pLChild);
		ConvertToRedNode(pRChild);
	}
	else
	{
		pNode->bIsRed = true;
	}
	(pNode->iBlackHeight)--;
}

void RedBlackTree::ConvertToRedNode(RedBlackNode* pBlackNode)
{
	if (pBlackNode)
	{
		pBlackNode->bIsRed = true;
		(pBlackNode->iBlackHeight)--;
	}
}

void RedBlackTree::EnsureRedBlackRuleInTreeAfterInsertion(RedBlackNode* pNode, RedBlackNode* pParent)
{
	if (pNode->LeftChild)
	{
		EnsureRedBlackRuleInTreeAfterInsertion(ToRedBlackNode(pNode->LeftChild), pNode);
	}
	if (pNode->RightChild)
	{
		EnsureRedBlackRuleInTreeAfterInsertion(ToRedBlackNode(pNode->RightChild), pNode);
	}
	EnsureRedBlackRuleAfterInsertion(pNode,pParent);
}

void RedBlackTree::EnsureRedBlackRuleAfterInsertion(RedBlackNode* pNode, RedBlackNode* pParent)
{
	BalanceStrategy Strategy = GetBalanceStrategyForInsertion(pNode);
	if (Strategy == BalanceStrategy::Recolour)
	{
		ApplyRecolouring(pNode);
	}
	else if(Strategy != BalanceStrategy::None)
	{
		RedBlackNode* pNewNode = GetBalancedNode(pNode, pParent, Strategy);
		UpdateBlackHeight(pNewNode);
		EnsureRedBlackRuleInTreeAfterInsertion(pNewNode, pParent);
	}
}

BalanceStrategy RedBlackTree::GetBalanceStrategyForInsertion(RedBlackNode* pNode)
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
	RaiseBlackHeightIfBlack(pLChild);
	pRChild->bIsRed = !(pRChild->bIsRed);
	RaiseBlackHeightIfBlack(pRChild);
}

void RedBlackTree::RaiseBlackHeightIfBlack(RedBlackNode* pNode)
{
	if (!(pNode->bIsRed))
	{
		(pNode->iBlackHeight)++;
	}
}

RedBlackNode* RedBlackTree::GetBalancedNode(RedBlackNode* pNode, RedBlackNode* pParent, BalanceStrategy Strategy)
{
	switch (Strategy)
	{
		case BalanceStrategy::LeftRightRotation:
		{
			FlipNodesColour(pNode, ToRedBlackNode(pNode->LeftChild->RightChild));
			return GetBalancedNodeByLeftRightRotation(pNode, pParent);
		}
		case BalanceStrategy::RightLeftRotation:
		{
			FlipNodesColour(pNode, ToRedBlackNode(pNode->RightChild->LeftChild));
			return GetBalancedNodeByRightLeftRotation(pNode, pParent);
		}
		case BalanceStrategy::LeftRotation:
		{
			FlipNodesColour(pNode, ToRedBlackNode(pNode->RightChild));
			return GetBalancedNodeByLeftRotation(pNode, pParent);
		}
		case BalanceStrategy::RightRotation:
		{
			FlipNodesColour(pNode, ToRedBlackNode(pNode->LeftChild));
			return GetBalancedNodeByRightRotation(pNode, pParent);
		}
	}
	return pNode;
}

void RedBlackTree::FlipNodesColour(RedBlackNode* pBlackNode, RedBlackNode* pRedNode)
{
	pBlackNode->bIsRed = true;
	(pBlackNode->iBlackHeight)--;
	pRedNode->bIsRed = false;
	(pRedNode->iBlackHeight)++;
}

RedBlackNode* RedBlackTree::GetBalancedNodeByLeftRightRotation(RedBlackNode* pNode, RedBlackNode* pParent)
{
	pNode->LeftChild = GetBalancedNodeByLeftRotation(ToRedBlackNode(pNode->LeftChild), pNode);
	return GetBalancedNodeByRightRotation(ToRedBlackNode(pNode), pParent);
}

RedBlackNode* RedBlackTree::GetBalancedNodeByRightLeftRotation(RedBlackNode* pNode, RedBlackNode* pParent)
{
	pNode->RightChild = GetBalancedNodeByRightRotation(ToRedBlackNode(pNode->RightChild), pNode);
	return GetBalancedNodeByLeftRotation(ToRedBlackNode(pNode), pParent);
}

RedBlackNode* RedBlackTree::GetBalancedNodeByLeftRotation(RedBlackNode* pNode, RedBlackNode* pParent)
{
	RedBlackNode* pNewNode = ToRedBlackNode(pNode->RightChild);
	AttachChild(pNewNode, pNode, ChildType::Left);
	pNode->RightChild = nullptr;
	ReplaceNode(pNode, pNewNode, pParent);
	return pNewNode;
}

RedBlackNode* RedBlackTree::GetBalancedNodeByRightRotation(RedBlackNode* pNode, RedBlackNode* pParent)
{
	RedBlackNode* pNewNode = ToRedBlackNode(pNode->LeftChild);
	AttachChild(pNewNode, pNode, ChildType::Right);
	pNode->LeftChild = nullptr;
	ReplaceNode(pNode, pNewNode, pParent);
	return pNewNode;
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

void RedBlackTree::EnsureRedBlackRuleInRoot(RedBlackNode* pRoot)
{
	pRoot->bIsRed = false;
	int iChildHeight = (pRoot->RightChild) ? ToRedBlackNode(pRoot->RightChild)->iBlackHeight : 1;
	pRoot->iBlackHeight = ++iChildHeight;
}

void RedBlackTree::OnDelete(Node<int>* pReplacedNode)
{
	RedBlackNode* pNode = ToRedBlackNode(pReplacedNode);
	if (IsRedNode(pNode))
	{
		pNode->bIsRed = false;
		(pNode->iBlackHeight)++;
	}
}

void RedBlackTree::EnsureRedBlackRuleInTreeAfterDeletion(RedBlackNode* pNode, RedBlackNode* pParent)
{
	if (pNode->LeftChild)
	{
		EnsureRedBlackRuleInTreeAfterDeletion(ToRedBlackNode(pNode->LeftChild), pNode);
	}
	if (pNode->RightChild)
	{
		EnsureRedBlackRuleInTreeAfterDeletion(ToRedBlackNode(pNode->RightChild), pNode);
	}
	EnsureRedBlackRuleAfterDeletion(pNode, pParent);
}

void RedBlackTree::EnsureRedBlackRuleAfterDeletion(RedBlackNode* pNode, RedBlackNode* pParent)
{
	RedBlackNode* pDoubleBlackSibling = GetSiblingOfDoubleBlack(pNode);
	if (pDoubleBlackSibling)
	{
		BalanceStrategy Strategy = GetBalanceStrategyForDeletion(pNode, pDoubleBlackSibling);
		ApplyBalanceStrategyForDeletion(pNode, pParent, Strategy);
	}
	UpdateBlackHeight(ToRedBlackNode(pNode));
	EnsureRedBlackRuleInTreeAfterInsertion(ToRedBlackNode(pNode), pParent);
}

RedBlackNode* RedBlackTree::GetSiblingOfDoubleBlack(RedBlackNode* pNode)
{
	RedBlackNode* pLChild = ToRedBlackNode(pNode->LeftChild);
	RedBlackNode* pRChild = ToRedBlackNode(pNode->RightChild);
	if (IsChildDoubleBlack(pNode, pLChild))
	{
		return pRChild;
	}
	else if (IsChildDoubleBlack(pNode, pRChild))
	{
		return pLChild;
	}
	return nullptr;
}

bool RedBlackTree::IsChildDoubleBlack(RedBlackNode* pNode, RedBlackNode* pChild)
{
	return ((!pChild) && (pNode->bIsRed) && ((pNode->iBlackHeight) > 1))
		|| ((!pChild) && !(pNode->bIsRed) && ((pNode->iBlackHeight) > 2))
		|| (pChild && (pNode->bIsRed) && ((pNode->iBlackHeight) > ((pChild->iBlackHeight) + 1)))
		|| (pChild && !(pNode->bIsRed) && ((pNode->iBlackHeight) > ((pChild->iBlackHeight) + 2)));
}

BalanceStrategy RedBlackTree::GetBalanceStrategyForDeletion(RedBlackNode* pParent, RedBlackNode* pChild)
{
	if (pChild->bIsRed)
	{
		return ((pParent->LeftChild) == pChild)? BalanceStrategy::LeftRotation: BalanceStrategy::RightRotation;
	}
	else if (IsRedOrNullNode(pChild->LeftChild) || IsRedOrNullNode(pChild->RightChild))
	{
		return ((pParent->LeftChild) == pChild) ? BalanceStrategy::LeftRecolour : BalanceStrategy::RightRecolour;
	}
	else if ((pParent->LeftChild) == pChild)
	{
		return (ToRedBlackNode(pChild->LeftChild)->bIsRed) ? BalanceStrategy::RightRotation : BalanceStrategy::LeftRightRotation;
	}
	else if ((pParent->RightChild) == pChild)
	{
		return (ToRedBlackNode(pChild->LeftChild)->bIsRed) ? BalanceStrategy::LeftRotation : BalanceStrategy::RightLeftRotation;
	}
	return BalanceStrategy::None;
}

bool RedBlackTree::IsRedOrNullNode(Node<int>* pNode)
{
	return (!pNode || IsRedNode(pNode));
}

void RedBlackTree::ApplyBalanceStrategyForDeletion(RedBlackNode* pNode, RedBlackNode* pParent, BalanceStrategy Strategy)
{
	if (Strategy != BalanceStrategy::None)
	{
		(pNode->iBlackHeight)--;
		if (Strategy == BalanceStrategy::LeftRecolour)
		{
			pNode->bIsRed = false;
			ConvertToRedNode(ToRedBlackNode(pNode->LeftChild));
		}
		else if (Strategy == BalanceStrategy::RightRecolour)
		{
			pNode->bIsRed = false;
			ConvertToRedNode(ToRedBlackNode(pNode->RightChild));
		}
		else
		{
			pNode = GetBalancedNode(pNode, pParent, Strategy);
		}
	}
}

RedBlackNode* RedBlackTree::ToRedBlackNode(Node<int>* pNode)
{
	return static_cast<RedBlackNode*>(pNode);
}