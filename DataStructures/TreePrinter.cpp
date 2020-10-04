#include "TreePrinter.h"
#include "Tree.h"
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

struct Line
{
	Line(Node<int>* pNode, int iLineNo)
		:pNodeItem(pNode),iLineNumber(iLineNo)
	{}

	Node<int>* GetNode()
	{
		return pNodeItem;
	}

	int GetLineNumber()
	{
		return iLineNumber;
	}

private:
	Node<int>* pNodeItem;
	int iLineNumber;
};

TreePrinter::TreePrinter(Tree<int>* pTree) : pTree(pTree)
{
	pLineQueue = new queue<Line*>();
	pLineVector = new vector<Line*>();
}

void TreePrinter::Print()
{
	CreateLines();
	int iPreviousLineNo = 0;
	int iInitialGaps = 100;
	int iItemGaps = iInitialGaps;
	for (int i=0; i<pLineVector->size(); i++)
	{
		Line* pLine = pLineVector->at(i);
		if ((i!=0) && (iPreviousLineNo != pLine->GetLineNumber()))
		{
			cout << endl;
			cout << endl;
			for (int i = 0; i < iInitialGaps; i++)
			{
				cout << " ";
			}
			iItemGaps = iInitialGaps * 2;
			iInitialGaps/=2;
		}
		else if (iPreviousLineNo == pLine->GetLineNumber())
		{
			for (int i = 0; i < iItemGaps; i++)
			{
				cout << " ";
			}
		}
		else if (i == 0)
		{
			for (int i = 0; i < iInitialGaps; i++)
			{
				cout << " ";
			}
			iInitialGaps/=2;
		}
		cout << pLine->GetNode()->Value;
		iPreviousLineNo = pLine->GetLineNumber();
	}
}

void TreePrinter::CreateLines()
{
	Line* pFirstLine = new Line(pTree->GetRootNode(), 1);
	pLineQueue->push(pFirstLine);
	AddLineToQueue(pLineQueue->front());
}

void TreePrinter::AddLineToQueue(Line* pLine)
{
	Node<int>* pNode = pLine->GetNode();
	if (pNode->LeftChild)
	{
		Line* pNewLine = new Line(pNode->LeftChild, pLine->GetLineNumber() + 1);
		pLineQueue->push(pNewLine);
	}
	if (pNode->RightChild)
	{
		Line* pNewLine = new Line(pNode->RightChild, pLine->GetLineNumber() + 1);
		pLineQueue->push(pNewLine);
	}
	pLineVector->push_back(pLineQueue->front());
	pLineQueue->pop();
	if (!pLineQueue->empty())
	{
		AddLineToQueue(pLineQueue->front());
	}
}