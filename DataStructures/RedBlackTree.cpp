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

	if (!pRChild && !pLChild)
	{
		pNode->iBlackHeight = (pNode->bIsRed) ? 1 : 2;
	}
	else if (!pRChild)
	{
		if ((pLChild->iBlackHeight) != 1)
		{
			if (pLChild->bIsRed)
			{
				RedBlackNode* pLLChild = ToRedBlackNode(pLChild->LeftChild);
				RedBlackNode* pLRChild = ToRedBlackNode(pLChild->RightChild);
				if (pLLChild)
				{
					pLLChild->bIsRed = true;
					pLLChild->iBlackHeight = pLLChild->iBlackHeight - 1;
				}
				if (pLRChild)
				{
					pLRChild->bIsRed = true;
					pLRChild->iBlackHeight = pLRChild->iBlackHeight - 1;
				}
			}
			else
			{
				pLChild->bIsRed = true;
			}
			pLChild->iBlackHeight = pLChild->iBlackHeight - 1;
			//UpdateBlackHeight(pLChild);
		}
		pNode->iBlackHeight = (pNode->bIsRed) ? 1 : 2;
		/*else 
		{
			pNode->iBlackHeight = (pNode->bIsRed) ? 1 : 2;
		}*/
	}
	else if (!pLChild)
	{
		if ((pRChild->iBlackHeight) != 1)
		{
			if (pRChild->bIsRed)
			{
				RedBlackNode* pRLChild = ToRedBlackNode(pRChild->LeftChild);
				RedBlackNode* pRRChild = ToRedBlackNode(pRChild->RightChild);
				if (pRLChild)
				{
					pRLChild->bIsRed = true;
					pRLChild->iBlackHeight = pRLChild->iBlackHeight - 1;
				}
				if (pRRChild)
				{
					pRRChild->bIsRed = true;
					pRRChild->iBlackHeight = pRRChild->iBlackHeight - 1;
				}
			}
			else
			{
				pRChild->bIsRed = true;
			}
			pRChild->iBlackHeight = pRChild->iBlackHeight - 1;
			//UpdateBlackHeight(pRChild);
		}
		/*else
		{
			pNode->iBlackHeight = (pNode->bIsRed) ? 1 : 2;
		}*/
		pNode->iBlackHeight = (pNode->bIsRed) ? 1 : 2;
	}
	else if ((pLChild->iBlackHeight) == (pRChild->iBlackHeight))
	{
		int iChildHeight = pRChild->iBlackHeight;
		pNode->iBlackHeight = (pNode->bIsRed) ? iChildHeight : (iChildHeight + 1);
	}
	else if((pLChild->iBlackHeight) > (pRChild->iBlackHeight))
	{
		if (pLChild->bIsRed)
		{
			RedBlackNode* pLLChild = ToRedBlackNode(pLChild->LeftChild);
			RedBlackNode* pLRChild = ToRedBlackNode(pLChild->RightChild);
			if (pLLChild)
			{
				pLLChild->bIsRed = true;
				pLLChild->iBlackHeight = pLLChild->iBlackHeight - 1;
			}
			if (pLRChild)
			{
				pLRChild->bIsRed = true;
				pLRChild->iBlackHeight = pLRChild->iBlackHeight - 1;
			}
		}
		else
		{
			pLChild->bIsRed = true;
		}
		pLChild->iBlackHeight = pLChild->iBlackHeight - 1;
		//UpdateBlackHeight(pLChild);
		int iChildHeight = pRChild->iBlackHeight;
		pNode->iBlackHeight = (pNode->bIsRed) ? iChildHeight : (iChildHeight + 1);
	}
	else if ((pLChild->iBlackHeight) < (pRChild->iBlackHeight))
	{
		if (pRChild->bIsRed)
		{
			RedBlackNode* pRLChild = ToRedBlackNode(pRChild->LeftChild);
			RedBlackNode* pRRChild = ToRedBlackNode(pRChild->RightChild);
			if (pRLChild)
			{
				pRLChild->bIsRed = true;
				pRLChild->iBlackHeight = pRLChild->iBlackHeight - 1;
			}
			if (pRRChild)
			{
				pRRChild->bIsRed = true;
				pRRChild->iBlackHeight = pRRChild->iBlackHeight - 1;
			}
		}
		else
		{
			pRChild->bIsRed = true;
		}
		pRChild->iBlackHeight = pRChild->iBlackHeight - 1;
		//UpdateBlackHeight(pRChild);
		int iChildHeight = pLChild->iBlackHeight;
		pNode->iBlackHeight = (pNode->bIsRed) ? iChildHeight : (iChildHeight + 1);
	}
	
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
			//CheckBlackHeight(ToRedBlackNode(pRoot), bAppliedHeightFix);
			//if (bAppliedHeightFix)
			//{
			//	//UpdateBlackHeight(ToRedBlackNode(pRoot));
			//	EnsureRedBlackRule(pNode, pParent);
			//}
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

void RedBlackTree::CheckBlackHeight(RedBlackNode* pNode, bool& bHasAppliedFix)
{
	if (pNode)
	{
		if (pNode->LeftChild)
		{
			CheckBlackHeight(ToRedBlackNode(pNode->LeftChild), bHasAppliedFix);
		}
		if (pNode->RightChild)
		{
			CheckBlackHeight(ToRedBlackNode(pNode->RightChild), bHasAppliedFix);
		}
		SetBlackHeight(pNode, bHasAppliedFix);
	}
}

void RedBlackTree::SetBlackHeight(RedBlackNode* pNode, bool& bHasAppliedFix)
{
	/*if ((!(pNode->LeftChild)) && (!(pNode->RightChild)))
	{
		pNode->iBlackHeight = (pNode->bIsRed) ? 1 : 2;
	}
	else */
	if ((pNode->LeftChild) && (pNode->RightChild))
	{
		RedBlackNode* pLChild = ToRedBlackNode(pNode->LeftChild);
		RedBlackNode* pRChild = ToRedBlackNode(pNode->RightChild);
		if ((pLChild->iBlackHeight) > (pRChild->iBlackHeight))
		{
			bHasAppliedFix = true;
			FixBlackHeight(pLChild, pRChild->iBlackHeight);
		}
		else if ((pRChild->iBlackHeight) > (pLChild->iBlackHeight))
		{
			bHasAppliedFix = true;
			FixBlackHeight(pRChild, pLChild->iBlackHeight);
		}
		/*if ((pLChild->iBlackHeight) == (pRChild->iBlackHeight))
		{
			int iChildHeight = pLChild->iBlackHeight;
			pNode->iBlackHeight = (pNode->bIsRed) ? iChildHeight : (iChildHeight + 1);
		}
		else
		{
			if ((pLChild->iBlackHeight) > (pRChild->iBlackHeight))
			{
				bHasAppliedFix = true;
				FixBlackHeight(pLChild, pRChild->iBlackHeight);
			}
			else if ((pRChild->iBlackHeight) > (pLChild->iBlackHeight))
			{
				bHasAppliedFix = true;
				FixBlackHeight(pRChild, pLChild->iBlackHeight);
			}
		}*/
	}
	else if (pNode->LeftChild)
	{
		RedBlackNode* pLChild = ToRedBlackNode(pNode->LeftChild);
		if ((pLChild->iBlackHeight) > 1)
		{
			bHasAppliedFix = true;
			FixBlackHeight(pLChild, 1);
		}
	}
	else if (pNode->RightChild)
	{
		RedBlackNode* pRChild = ToRedBlackNode(pNode->RightChild);
		if ((pRChild->iBlackHeight) > 1)
		{
			bHasAppliedFix = true;
			FixBlackHeight(pRChild, 1);
		}
	}
}

void RedBlackTree::FixBlackHeight(RedBlackNode* pNode, const int iResultHeight)
{
	/*int iHeightToReduce = iResultHeight;
	if (pNode->LeftChild)
	{
		FixBlackHeight(ToRedBlackNode(pNode->LeftChild), (iHeightToReduce == 1) ? iHeightToReduce : --iHeightToReduce);
	}
	if (pNode->RightChild)
	{
		FixBlackHeight(ToRedBlackNode(pNode->RightChild), (iHeightToReduce == 1) ? iHeightToReduce : --iHeightToReduce);
	}
	if ((pNode->iBlackHeight) > iResultHeight)
	{
		if (!(pNode->bIsRed))
		{
			pNode->bIsRed = true;
		}
		pNode->iBlackHeight = 1;
		if (pNode->LeftChild)
		{
			int iChildHeight = ToRedBlackNode(pNode->LeftChild)->iBlackHeight;
			pNode->iBlackHeight = (pNode->bIsRed)?iChildHeight:(iChildHeight + 1);
		}
		else if (pNode->RightChild)
		{
			int iChildHeight = ToRedBlackNode(pNode->RightChild)->iBlackHeight;
			pNode->iBlackHeight = (pNode->bIsRed) ? iChildHeight : (iChildHeight + 1);
		}
	}*/

	if (!(pNode->bIsRed))
	{
		pNode->bIsRed = true;
	}
	/*pNode->iBlackHeight = 1;
	if (pNode->LeftChild)
	{
		int iChildHeight = ToRedBlackNode(pNode->LeftChild)->iBlackHeight;
		pNode->iBlackHeight = (pNode->bIsRed)?iChildHeight:(iChildHeight + 1);
	}
	else if (pNode->RightChild)
	{
		int iChildHeight = ToRedBlackNode(pNode->RightChild)->iBlackHeight;
		pNode->iBlackHeight = (pNode->bIsRed) ? iChildHeight : (iChildHeight + 1);
	}*/
}

RedBlackNode* RedBlackTree::ToRedBlackNode(Node<int>* pNode)
{
	return static_cast<RedBlackNode*>(pNode);
}