#pragma once
#include "Tree.h"
#include <iostream>

enum class ChildType
{
	Left, Right, Root
};

template<typename T>
struct AVLNode : Node<T>
{
	int iTreeHeight;
	int iLTreeHeight;
	int iRTreeHeight;
	int GetBalanceFactor()
	{
		if (iLTreeHeight > iRTreeHeight)
		{
			return iLTreeHeight - iRTreeHeight;
		}
		else
		{
			return iRTreeHeight - iLTreeHeight;
		}
	}
};

template<typename T>
class AVLTree : public Tree<T>
{
	AVLNode<T>* pRoot;
	void CreateTree(AVLNode<T>* pAVLNode, Node<T>* pNode)
	{
		pAVLNode->Value = pNode->Value;
		if (pNode->LeftChild)
		{
			pAVLNode->LeftChild = new AVLNode<T>;
			CreateTree(static_cast<AVLNode<T>*>(pAVLNode->LeftChild), pNode->LeftChild);
		}
		if (pNode->RightChild)
		{
			pAVLNode->RightChild = new AVLNode<T>;
			CreateTree(static_cast<AVLNode<T>*>(pAVLNode->RightChild), pNode->RightChild);
		}
	}

	void MarkNodes(AVLNode<T>* pAVLNode)
	{
		if (pAVLNode->LeftChild)
		{
			MarkNodes(static_cast<AVLNode<T>*>(pAVLNode->LeftChild));
		}
		if (pAVLNode->RightChild)
		{
			MarkNodes(static_cast<AVLNode<T>*>(pAVLNode->RightChild));
		}
		int iLeftTreeHeight = 0;
		int iRightTreeHeight = 0;
		int iTreeHeight = 0;

		AVLNode<T>* LeftChild = static_cast<AVLNode<T>*>(pAVLNode->LeftChild);
		if (LeftChild)
		{
			iLeftTreeHeight = LeftChild->iTreeHeight;
		}
		else
		{
			iLeftTreeHeight = 0;
		}

		AVLNode<T>* RightChild = static_cast<AVLNode<T>*>(pAVLNode->RightChild);
		if (RightChild)
		{
			iRightTreeHeight = RightChild->iTreeHeight;
		}
		else
		{
			iRightTreeHeight = 0;
		}
		
		if (iLeftTreeHeight > iRightTreeHeight)
		{
			iTreeHeight = iLeftTreeHeight + 1;
		}
		else
		{
			iTreeHeight = iRightTreeHeight + 1;
		}

		pAVLNode->iLTreeHeight = iLeftTreeHeight;
		pAVLNode->iRTreeHeight = iRightTreeHeight;
		pAVLNode->iTreeHeight = iTreeHeight;

		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Node : " << pAVLNode->Value << std::endl;
		std::cout << "LTreeHeight : " << pAVLNode->iLTreeHeight << std::endl;
		std::cout << "RTreeHeight : " << pAVLNode->iRTreeHeight << std::endl;
		std::cout << "TreeHeight : " << pAVLNode->iTreeHeight << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		
	}

	void GotoSubTree(AVLNode<T>* pUNode, AVLNode<T>* pParent, ChildType Type)
	{
		if (pUNode->LeftChild)
		{
			GotoSubTree(static_cast<AVLNode<T>*>(pUNode->LeftChild), pUNode, ChildType::Left);
		}
		if (pUNode->RightChild)
		{
			GotoSubTree(static_cast<AVLNode<T>*>(pUNode->RightChild), pUNode, ChildType::Right);
		}
		if (pUNode->GetBalanceFactor() > 1)
		{
			AVLNode<T>* pBNode = BalanceSubTree(pUNode);
			if (pParent)
			{
				if (Type == ChildType::Left)
				{
					pParent->LeftChild = pBNode;
				}
				else
				{
					pParent->RightChild = pBNode;
				}
			}
			else
			{
				pRoot = pBNode;
			}
		}
	}

	AVLNode<T>* BalanceSubTree(AVLNode<T>* pUNode)
	{
		if (pUNode->iRTreeHeight > pUNode->iLTreeHeight)
		{
			AVLNode<T>* pRChild = static_cast<AVLNode<T>*>(pUNode->RightChild);
			if (pRChild->iRTreeHeight > pRChild->iLTreeHeight)
			{
				return LeftRotate(pUNode);
			}
			else
			{
				return RightLeftRotate(pUNode);
			}
		}
		else
		{
			AVLNode<T>* pLChild = static_cast<AVLNode<T>*>(pUNode->LeftChild);
			if (pLChild->iRTreeHeight > pLChild->iLTreeHeight)
			{
				return LeftRightRotate(pUNode);
			}
			else
			{
				return RightRotate(pUNode);
			}
		}
	}

	AVLNode<T>* LeftRightRotate(AVLNode<T>* pUNode)
	{
		pUNode->LeftChild = LeftRotate(static_cast<AVLNode<T>*>(pUNode->LeftChild));
		return RightRotate(pUNode);
	}

	AVLNode<T>* RightLeftRotate(AVLNode<T>* pUNode)
	{
		pUNode->RightChild = RightRotate(static_cast<AVLNode<T>*>(pUNode->LeftChild));
		return LeftRotate(pUNode);
	}

	AVLNode<T>* LeftRotate(AVLNode<T>* pUNode)
	{
		AVLNode<T>* pRightChild = static_cast<AVLNode<T>*>(pUNode->RightChild);
		AttachChild(pRightChild, pUNode, ChildType::Left);
		pUNode->RightChild = nullptr;
		return pRightChild;
	}

	AVLNode<T>* RightRotate(AVLNode<T>* pUNode)
	{
		AVLNode<T>* pLeftChild = static_cast<AVLNode<T>*>(pUNode->LeftChild);
		AttachChild(pLeftChild, pUNode, ChildType::Right);
		pUNode->LeftChild = nullptr;
		return pLeftChild;
	}

	void AttachChild(AVLNode<T>* pParent, AVLNode<T>* pChild, ChildType Type)
	{
		if (Type == ChildType::Left)
		{
			if (!(pParent->LeftChild))
			{
				pParent->LeftChild = pChild;
			}
			else
			{
				AttachChild(static_cast<AVLNode<T>*>(pParent->LeftChild), pChild, ChildType::Left);
			}
		}
		else if (Type == ChildType::Right)
		{
			if (!(pParent->RightChild))
			{
				pParent->RightChild = pChild;
			}
			else
			{
				AttachChild(static_cast<AVLNode<T>*>(pParent->RightChild), pChild, ChildType::Right);
			}
		}
	}

public:
	AVLTree(Tree<T>* pTree)
	{
		pRoot = new AVLNode<T>;
		CreateTree(pRoot, pTree->GetRootNode());
		MarkNodes(pRoot);
		GotoSubTree(pRoot, nullptr, ChildType::Root);
	}

	AVLNode<T>* GetRootNode() override
	{
		return pRoot;
	}
};