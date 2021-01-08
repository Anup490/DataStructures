#include <iostream>
#include <initializer_list>
#include <vector>
#include "TreePrinter.h"
#include "Tree.h"
#include "AVLTree.h"
#include "Heap.h"
#include "RedBlackTree.h"
#include "MergeSort.h"
#include "HashTable.h"

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

void test_AVL()
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

void test_heap()
{
	initializer_list<int> List({35,33,42,10,14,19,27,44,26,31});
	Heap Hp(&List);
	TreePrinter Printer(&Hp);
	Printer.Print();
}

void test_red_black_tree()
{
	BinaryTree BTree;
	BTree.Add(35);
	BTree.Add(33);
	BTree.Add(42);
	BTree.Add(10);
	BTree.Add(14);
	BTree.Add(19);
	BTree.Add(27);
	BTree.Add(44);
	BTree.Add(26);
	BTree.Add(31);

	AVLTree<int> AVL(&BTree);

	RedBlackTree RBTree;
	RBTree.Add(35);
	RBTree.Add(33);
	RBTree.Add(42);
	RBTree.Add(10);
	RBTree.Add(14);
	RBTree.Add(19);
	RBTree.Add(27);
	RBTree.Add(44);
	RBTree.Add(26);
	RBTree.Add(31);

	RBTree.Delete(27);

	std::cout << "AVL TREE" << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	TreePrinter AVLTPrinter(&AVL);
	AVLTPrinter.Print();
	std::cout << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "RED BLACK TREE" << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	TreePrinter RBTPrinter(&RBTree);
	RBTPrinter.Print();
	std::cout << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
}

void test_merge_sort()
{
	vector<int> Vector({ 35,33,42,10,14,19,27,44,26,31,23,88,45,13,21,77,34,97,2 });
	//vector<int> Vector({ 14,33,27,10,35,19,42,44 });
	//vector<int> Vector({ 35,33,42,10,14,19,27,44,26,31 });
	MergeSort Sorter(&Vector);
	vector<int>* pSortedVector = Sorter.GetSortedItems();
	for (int i : *pSortedVector)
	{
		cout << i << endl;
	}
}

void test_hash_table()
{
	class : public HashKey
	{
		string* pKey;
	public:
		void SetKey(string* pStringKey)
		{
			pKey = pStringKey;
		}

		int GetHashValue() override
		{
			return pKey->length();
		}
	} TestKey;

	HashTable<string> Table;
	string data = "Nicolette Shea";
	TestKey.SetKey(&data);
	Entry<string> entry = { &TestKey, data };
	Table.AddItem(&entry);
	cout << "Stored data is " << data << endl;
	string retrievedData = Table.GetItem(&TestKey);
	cout << "Retrieved data is " << retrievedData << endl;
}

int main()
{
	test_hash_table();
}
