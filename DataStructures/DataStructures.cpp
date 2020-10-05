#include <iostream>
#include "TreePrinter.h"
#include "Tree.h"
#include "AVLTree.h"

template<typename T>
class TestTree : public Tree<T>
{
	Node<T>* pRoot;

	void AddItems()
	{
		pRoot->Value = 1;
		pRoot->LeftChild = new Node<T>;
		pRoot->RightChild = new Node<T>;

		Node<T>* pRootLeftChild = pRoot->LeftChild;
		pRootLeftChild->Value = 2;
		pRootLeftChild->LeftChild = new Node<T>;
		pRootLeftChild->RightChild = new Node<T>;

		Node<T>* pRootRightChild = pRoot->RightChild;
		pRootRightChild->Value = 3;
		pRootRightChild->LeftChild = new Node<T>;
		pRootRightChild->RightChild = new Node<T>;

		Node<T>* pRootLeftLeftChild = pRootLeftChild->LeftChild;
		pRootLeftLeftChild->Value = 4;
		pRootLeftLeftChild->LeftChild = new Node<T>;

		Node<T>* pRootLeftRightChild = pRootLeftChild->RightChild;
		pRootLeftRightChild->Value = 5;

		Node<T>* pRootRightLeftChild = pRootRightChild->LeftChild;
		pRootRightLeftChild->Value = 6;

		Node<T>* pRootRightRightChild = pRootRightChild->RightChild;
		pRootRightRightChild->Value = 7;

		Node<T>* pRootLeftLeftLeftChild = pRootLeftLeftChild->LeftChild;
		pRootLeftLeftLeftChild->Value = 8;
		pRootLeftLeftLeftChild->LeftChild = new Node<T>;

		Node<T>* pRootLeftLeftLeftLeftChild = pRootLeftLeftLeftChild->LeftChild;
		pRootLeftLeftLeftLeftChild->Value = 9;
	}

public:
	TestTree()
	{
		pRoot = new Node<int>;
		AddItems();
	}

	Node<T>* GetRootNode() override
	{
		return pRoot;
	}
};

int main()
{
	TestTree<int> Test;
	AVLTree<int> AVL(&Test);
	TreePrinter Printer(&AVL);
	Printer.Print();
}
