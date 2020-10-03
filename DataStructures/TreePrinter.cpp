#include "TreePrinter.h"
#include "Tree.h"
#include <vector>
#include <queue>
using namespace std;

struct Line
{
	Line(Node<int>* pNode, int iLineNo)
		:pNodeItem(pNode),iLineNumber(iLineNo)
	{}

private:
	Node<int>* pNodeItem;
	int iLineNumber;
};

TreePrinter::TreePrinter(Tree<Node<int>*>* pTree)
{
	pNodeQueue = new queue<Node<int>*>();
	pLines = new vector<struct Line*>();
}

void TreePrinter::Print()
{

}

void CreateLines()
{

}

void AddLineToQueue()
{

}