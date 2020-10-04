#include "TreePrinter.h"
#include "Tree.h"

class TestTree : public Tree<int>
{
	Node<int>* pRoot;

public:
	TestTree()
	{
		pRoot = new Node<int>;
	}

	void AddItems()
	{
		pRoot->Value = 1;
		pRoot->LeftChild = new Node<int>;
		pRoot->RightChild = new Node<int>;

		Node<int>* pRootLeftChild = pRoot->LeftChild;
		pRootLeftChild->Value = 2;
		pRootLeftChild->LeftChild = new Node<int>;
		pRootLeftChild->RightChild = new Node<int>;

		Node<int>* pRootRightChild = pRoot->RightChild;
		pRootRightChild->Value = 3;
		pRootRightChild->LeftChild = new Node<int>;
		pRootRightChild->RightChild = new Node<int>;

		Node<int>* pRootLeftLeftChild = pRootLeftChild->LeftChild;
		pRootLeftLeftChild->Value = 4;
		pRootLeftLeftChild->LeftChild = new Node<int>;

		Node<int>* pRootLeftRightChild = pRootLeftChild->RightChild;
		pRootLeftRightChild->Value = 5;

		Node<int>* pRootRightLeftChild = pRootRightChild->LeftChild;
		pRootRightLeftChild->Value = 6;

		Node<int>* pRootRightRightChild = pRootRightChild->RightChild;
		pRootRightRightChild->Value = 7;

		Node<int>* pRootLeftLeftLeftChild = pRootLeftLeftChild->LeftChild;
		pRootLeftLeftLeftChild->Value = 8;
		pRootLeftLeftLeftChild->LeftChild = new Node<int>;

		Node<int>* pRootLeftLeftLeftLeftChild = pRootLeftLeftLeftChild->LeftChild;
		pRootLeftLeftLeftLeftChild->Value = 9;
	}

	Node<int>* GetRootNode() override
	{
		return pRoot;
	}
};


int main()
{
	TestTree Tree;
	Tree.AddItems();
	TreePrinter Printer(&Tree);
	Printer.Print();
}
