#include <iostream>
#include "TreePrinter.h"
#include "Tree.h"
#include "AVLTree.h"

template<typename T>
class TestTree : public Tree<T>
{
	Node<T>* p1;

	void AddItems()
	{
		p1->Value = 50;
		p1->LeftChild = new Node<T>;
		p1->RightChild = new Node<T>;

		Node<T>* p2 = p1->LeftChild;
		p2->Value = 17;
		p2->LeftChild = new Node<T>;
		p2->RightChild = new Node<T>;

		Node<T>* p4 = p2->LeftChild;
		p4->Value = 9;
		p4->RightChild = new Node<T>;

		Node<T>* p5 = p2->RightChild;
		p5->Value = 23;
		p5->LeftChild = new Node<T>;

		Node<T>* p7 = p4->RightChild;
		p7->Value = 14;
		p7->LeftChild = new Node<T>;

		Node<T>* p9 = p7->LeftChild;
		p9->Value = 12;

		Node<T>* p8 = p5->LeftChild;
		p8->Value = 19;

		Node<T>* p3 = p1->RightChild;
		p3->Value = 76;
		p3->LeftChild = new Node<T>;

		Node<T>* p6 = p3->LeftChild;
		p6->Value = 54;
		p6->RightChild = new Node<T>;

		Node<T>* p10 = p6->RightChild;
		p10->Value = 72;
		p10->LeftChild = new Node<T>;

		Node<T>* p11 = p10->LeftChild;
		p11->Value = 67;
	}

public:
	TestTree()
	{
		p1 = new Node<int>;
		AddItems();
	}

	Node<T>* GetRootNode() override
	{
		return p1;
	}
};

int main()
{
	TestTree<int> Test;
	AVLTree<int> AVL(&Test);
	std::cout << "UNBALANCED TREE" << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	TreePrinter UBTPrinter(&Test);
	UBTPrinter.Print();
	std::cout << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "BALANCED TREE" << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	TreePrinter BTPrinter(&AVL);
	BTPrinter.Print();
	std::cout << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
}
