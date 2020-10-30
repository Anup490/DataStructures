#pragma once
#include "Tree.h"

template<typename T>
struct AVLNode : Node<T>
{
	int iTreeHeight;
	int iLTreeHeight;
	int iRTreeHeight;

	int GetBalanceFactor()
	{
		return (iLTreeHeight > iRTreeHeight) ? (iLTreeHeight - iRTreeHeight) : (iRTreeHeight - iLTreeHeight);
	}

	void UpdateTreeHeight()
	{
		iTreeHeight = (iLTreeHeight > iRTreeHeight) ? (iLTreeHeight + 1) : (iRTreeHeight + 1);
	}
};

template<typename T>
class AVLTree : public Tree<T>
{
	AVLNode<T>* pRoot;
	void ReplicateTree(AVLNode<T>* pAVLNode, Node<T>* pNode)
	{
		pAVLNode->Value = pNode->Value;
		if (pNode->LeftChild)
		{
			pAVLNode->LeftChild = new AVLNode<T>;
			ReplicateTree(static_cast<AVLNode<T>*>(pAVLNode->LeftChild), pNode->LeftChild);
		}
		if (pNode->RightChild)
		{
			pAVLNode->RightChild = new AVLNode<T>;
			ReplicateTree(static_cast<AVLNode<T>*>(pAVLNode->RightChild), pNode->RightChild);
		}
	}

	void TraverseByPostOrderAndMarkNodes(AVLNode<T>* pAVLNode)
	{
		if (pAVLNode->LeftChild)
		{
			TraverseByPostOrderAndMarkNodes(static_cast<AVLNode<T>*>(pAVLNode->LeftChild));
		}
		if (pAVLNode->RightChild)
		{
			TraverseByPostOrderAndMarkNodes(static_cast<AVLNode<T>*>(pAVLNode->RightChild));
		}
		MarkNode(pAVLNode);
	}

	void MarkNode(AVLNode<T>* pAVLNode)
	{
		AVLNode<T>* LeftChild = static_cast<AVLNode<T>*>(pAVLNode->LeftChild);
		AVLNode<T>* RightChild = static_cast<AVLNode<T>*>(pAVLNode->RightChild);
		int iLeftTreeHeight = (LeftChild) ? (LeftChild->iTreeHeight) : 0;
		int iRightTreeHeight = (RightChild) ? RightChild->iTreeHeight : 0;
		int iTreeHeight = (iLeftTreeHeight > iRightTreeHeight) ? (iLeftTreeHeight + 1) : (iRightTreeHeight + 1);
		pAVLNode->iLTreeHeight = iLeftTreeHeight;
		pAVLNode->iRTreeHeight = iRightTreeHeight;
		pAVLNode->iTreeHeight = iTreeHeight;
	}

	void TraverseByPostOrderAndBalance(AVLNode<T>* pUNode, AVLNode<T>* pParent, ChildType Type)
	{
		if (pUNode->LeftChild)
		{
			TraverseByPostOrderAndBalance(static_cast<AVLNode<T>*>(pUNode->LeftChild), pUNode, ChildType::Left);
			pUNode->iLTreeHeight = static_cast<AVLNode<T>*>(pUNode->LeftChild)->iTreeHeight;
		}
		if (pUNode->RightChild)
		{
			TraverseByPostOrderAndBalance(static_cast<AVLNode<T>*>(pUNode->RightChild), pUNode, ChildType::Right);
			pUNode->iRTreeHeight = static_cast<AVLNode<T>*>(pUNode->RightChild)->iTreeHeight;
		}
		pUNode->UpdateTreeHeight();
		if (pUNode->GetBalanceFactor() > 1)
		{
			AttachBalancedNodeToParent(ToNodeWithBalancedTree(pUNode), pParent, Type);
		}
	}

	void AttachBalancedNodeToParent(AVLNode<T>* pBNode, AVLNode<T>* pParent, ChildType Type)
	{
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

	AVLNode<T>* ToNodeWithBalancedTree(AVLNode<T>* pUNode)
	{
		if (pUNode->iRTreeHeight > pUNode->iLTreeHeight)
		{
			return GetNodeWithBalancedRightTree(static_cast<AVLNode<T>*>(pUNode));
		}
		else
		{
			return GetNodeWithBalancedLeftTree(static_cast<AVLNode<T>*>(pUNode));
		}
	}

	AVLNode<T>* GetNodeWithBalancedRightTree(AVLNode<T>* pUNode)
	{
		AVLNode<T>* pRChild = static_cast<AVLNode<T>*>(pUNode->RightChild);
		if (pRChild->iRTreeHeight > pRChild->iLTreeHeight)
		{
			return ApplyLeftRotationAndReturnNode(pUNode);
		}
		else
		{
			return ApplyRightLeftRotationAndReturnNode(pUNode);
		}
	}

	AVLNode<T>* GetNodeWithBalancedLeftTree(AVLNode<T>* pUNode)
	{
		AVLNode<T>* pLChild = static_cast<AVLNode<T>*>(pUNode->LeftChild);
		if (pLChild->iRTreeHeight > pLChild->iLTreeHeight)
		{
			return ApplyLeftRightRotationAndReturnNode(pUNode);
		}
		else
		{
			return ApplyRightRotationAndReturnNode(pUNode);
		}
	}

	AVLNode<T>* ApplyLeftRightRotationAndReturnNode(AVLNode<T>* pUNode)
	{
		pUNode->LeftChild = ApplyLeftRotationAndReturnNode(static_cast<AVLNode<T>*>(pUNode->LeftChild));
		return ApplyRightRotationAndReturnNode(pUNode);
	}

	AVLNode<T>* ApplyRightLeftRotationAndReturnNode(AVLNode<T>* pUNode)
	{
		pUNode->RightChild = ApplyRightRotationAndReturnNode(static_cast<AVLNode<T>*>(pUNode->RightChild));
		return ApplyLeftRotationAndReturnNode(pUNode);
	}

	AVLNode<T>* ApplyLeftRotationAndReturnNode(AVLNode<T>* pUNode)
	{
		AVLNode<T>* pRightChild = static_cast<AVLNode<T>*>(pUNode->RightChild);
		AttachChild(pRightChild, pUNode, ChildType::Left);
		++(pRightChild->iLTreeHeight);
		pRightChild->UpdateTreeHeight();
		pUNode->RightChild = nullptr;
		pUNode->iRTreeHeight = 0;
		pUNode->UpdateTreeHeight();
		return pRightChild;
	}

	AVLNode<T>* ApplyRightRotationAndReturnNode(AVLNode<T>* pUNode)
	{
		AVLNode<T>* pLeftChild = static_cast<AVLNode<T>*>(pUNode->LeftChild);
		AttachChild(pLeftChild, pUNode, ChildType::Right);
		++(pLeftChild->iRTreeHeight);
		pLeftChild->UpdateTreeHeight();
		pUNode->LeftChild = nullptr;
		pUNode->iLTreeHeight = 0;
		pUNode->UpdateTreeHeight();
		return pLeftChild;
	}

	void AttachChild(Node<T>* pParent, Node<T>* pChild, ChildType Type)
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

	void AttachAsLeftChild(Node<T>* pParent, Node<T>* pChild)
	{
		if (!(pParent->LeftChild))
		{
			pParent->LeftChild = pChild;
		}
		else
		{
			AttachAsLeftChild(pParent->LeftChild, pChild);
		}
	}

	void AttachAsRightChild(Node<T>* pParent, Node<T>* pChild)
	{
		if (!(pParent->RightChild))
		{
			pParent->RightChild = pChild;
		}
		else
		{
			AttachAsRightChild(pParent->RightChild, pChild);
		}
	}

	void DeleteNodes(Node<T>* pNode)
	{
		if (pNode->LeftChild)
		{
			DeleteNodes(pNode->LeftChild);
		}
		if (pNode->RightChild)
		{
			DeleteNodes(pNode->RightChild);
		}
		delete pNode;
	}

public:
	AVLTree(Tree<T>* pTree)
	{
		pRoot = new AVLNode<T>;
		ReplicateTree(pRoot, pTree->GetRootNode());
		TraverseByPostOrderAndMarkNodes(pRoot);
		TraverseByPostOrderAndBalance(pRoot, nullptr, ChildType::Root);
	}

	~AVLTree()
	{
		DeleteNodes(pRoot);
	}

	AVLNode<T>* GetRootNode() override
	{
		return pRoot;
	}
};