#include "TreePrinter.h"
#include "Tree.h"
#include "RedBlackTree.h"
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

TreePrinter::~TreePrinter()
{
	for (int i=0; i<pLineQueue->size(); i++)
	{
		pLineQueue->pop();
	}
	for (int i = 0; i < pLineVector->size(); i++)
	{
		Line* pLine = pLineVector->at(i);
		delete pLine;
	}
	delete pLineQueue;
	delete pLineVector;
}

void TreePrinter::Print()
{
	CreateLines();
	int iPreviousLineNo = 0;
	int iInitialGaps = 100;
	for (int i=0; i<pLineVector->size(); i++)
	{
		Line* pLine = pLineVector->at(i);
		PositionCursor(i == 0, iPreviousLineNo != pLine->GetLineNumber(), iInitialGaps);
		PrintLine(pLine);
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
	PushChildInQueue(pNode, ChildType::Left, pLine);
	PushChildInQueue(pNode, ChildType::Right, pLine);
	pLineVector->push_back(pLineQueue->front());
	pLineQueue->pop();
	if (!pLineQueue->empty())
	{
		AddLineToQueue(pLineQueue->front());
	}
}

void TreePrinter::PushChildInQueue(Node<int>* pNode, ChildType Type, Line* pLine)
{
	if ((Type == ChildType::Left) && pNode && (pNode->LeftChild))
	{
		Line* pNewLine = new Line(pNode->LeftChild, pLine->GetLineNumber() + 1);
		pLineQueue->push(pNewLine);
	}
	else if ((Type == ChildType::Right) && pNode && (pNode->RightChild))
	{
		Line* pNewLine = new Line(pNode->RightChild, pLine->GetLineNumber() + 1);
		pLineQueue->push(pNewLine);
	}
	else if (pNode)
	{
		Line* pNewLine = new Line(nullptr, pLine->GetLineNumber() + 1);
		pLineQueue->push(pNewLine);
	}
}

void TreePrinter::PositionCursor(bool bIsFirstItem, bool bIsNewLine, int& iInitialGaps)
{
	int iItemGaps = iInitialGaps * 4;
	if (!bIsFirstItem && bIsNewLine)
	{
		AddGaps(true,iInitialGaps);
		iInitialGaps /= 2;
	}
	else if (!bIsNewLine)
	{
		AddGaps(false,iItemGaps);
	}
	else if (bIsFirstItem)
	{
		AddGaps(false,iInitialGaps);
		iInitialGaps /= 2;
	}
}

void TreePrinter::AddGaps(bool bChangeLine, int& iGaps)
{
	if (bChangeLine)
	{
		cout << endl;
		cout << endl;
	}
	for (int i = 0; i < iGaps; i++)
	{
		cout << " ";
	}
}

void TreePrinter::PrintLine(Line* pLine)
{
	Node<int>* pNode = pLine->GetNode();
	if (pNode)
	{
		cout << pNode->Value << GetColorIfRedBlack(pLine->GetNode()) << " " << GetHeightIfRedBlack(pLine->GetNode());
	}
	else
	{
		cout << " ";
	}
}

char TreePrinter::GetColorIfRedBlack(Node<int>* pNode)
{
	RedBlackNode* pRBNode = static_cast<RedBlackNode*>(pNode);
	if (pRBNode)
	{
		return (pRBNode->bIsRed) ? 'R' : 'B';
	}
	return 'X';
}

int TreePrinter::GetHeightIfRedBlack(Node<int>* pNode)
{
	RedBlackNode* pRBNode = static_cast<RedBlackNode*>(pNode);
	if (pRBNode)
	{
		return pRBNode->iBlackHeight;
	}
	return 0;
}