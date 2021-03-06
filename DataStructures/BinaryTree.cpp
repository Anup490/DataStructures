#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	pRoot = 0;
}

BinaryTree::~BinaryTree()
{
	DeleteNodes(pRoot);
}

void BinaryTree::Add(int iValue)
{
	if (pRoot)
	{
		Node<int>* pNode = new Node<int>;
		pNode->Value = iValue;
		ApplyBinaryInsertion(pRoot, pNode);
	}
	else
	{
		pRoot = new Node<int>;
		pRoot->Value = iValue;
	}
}

void BinaryTree::Delete(int iValue)
{
	ApplyBinaryDeletion(nullptr, pRoot, iValue);
}

Node<int>* BinaryTree::GetRootNode()
{
	return pRoot;
}

void BinaryTree::ApplyBinaryInsertion(Node<int>* pNode, Node<int>* pNewNode)
{
	if ((pNewNode->Value) < (pNode->Value))
	{
		if (pNode->LeftChild)
		{
			ApplyBinaryInsertion(pNode->LeftChild, pNewNode);
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
			ApplyBinaryInsertion(pNode->RightChild, pNewNode);
		}
		else
		{
			pNode->RightChild = pNewNode;
		}
	}
}

void BinaryTree::ApplyBinaryDeletion(Node<int>* pParent, Node<int>* pNode, int iValue)
{
	if ((pNode->Value) == iValue)
	{
		Node<int>* pSuccessor = GetSuccessor(pNode);
		ReplaceNode(pNode, pSuccessor, pParent);
		OnDelete(pSuccessor);
		delete pNode;
	}
	else if ((iValue < (pNode->Value)) && (pNode->LeftChild))
	{
		ApplyBinaryDeletion(pNode, pNode->LeftChild, iValue);
	}
	else if ((iValue > (pNode->Value)) && (pNode->RightChild))
	{
		ApplyBinaryDeletion(pNode, pNode->RightChild, iValue);
	}
}

void BinaryTree::ReplaceNode(Node<int>* pOld, Node<int>* pNew, Node<int>* pParent)
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

void BinaryTree::DeleteNodes(Node<int>* pNode)
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

Node<int>* BinaryTree::GetSuccessor(Node<int>* pNode)
{
	Node<int>* pSuccessorNode = nullptr;
	if (pNode->RightChild)
	{
		pSuccessorNode = GetInorderSuccessor(pNode->RightChild, pNode);
		pSuccessorNode->LeftChild = pNode->LeftChild;
		AttachToRightSubTree(pNode->RightChild, pSuccessorNode, ChildType::Right);
	}
	else if (pNode->LeftChild)
	{
		pSuccessorNode = pNode->LeftChild;
	}
	return pSuccessorNode;
}

Node<int>* BinaryTree::GetInorderSuccessor(Node<int>* pNode, Node<int>* pParent)
{
	if (!(pNode->LeftChild))
	{
		if ((pParent->LeftChild) == pNode) {
			pParent->LeftChild = nullptr;
		}
		return pNode;
	}
	return GetInorderSuccessor(pNode->LeftChild, pNode);
}

void BinaryTree::AttachToRightSubTree(Node<int>* pNode, Node<int>* pParent, ChildType Type)
{
	if (pParent && (pNode != pParent))
	{
		if (pParent->RightChild)
		{
			AttachToRightSubTree(pNode, pParent->RightChild, ChildType::Right);
		}
		else
		{
			pParent->RightChild = pNode;
		}
	}
}