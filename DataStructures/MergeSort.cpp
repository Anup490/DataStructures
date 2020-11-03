#include "MergeSort.h"
#include <vector>


MergeSort::MergeSort(vector<int>* pUVector)
{
	pSVector = new vector<int>;
	if (pUVector)
	{
		Sort(pUVector);
	}
}

vector<int>* MergeSort::GetSortedItems()
{
	return pSVector;
}

MergeSort::~MergeSort()
{
	delete pSVector;
}

void MergeSort::Sort(vector<int>* pUVector)
{
	int iItr = 4;
	while (iItr <= (pUVector->size()))
	{
		for (int i=0; i<(pUVector->size()); i+=iItr)
		{
			int iPiece = iItr / 2;
			for (int j=i; j<(i + iPiece); j++)
			{
				for (int k=(j + iPiece); k<iItr; k++)
				{
					if ((k<(pUVector->size())) && (j < (pUVector->size())))
					{
						if ((pUVector->at(j)) < (pUVector->at(k)))
						{
							pSVector->push_back(pUVector->at(j));
							break;
						}
						else if (DoesNotHaveItem(pUVector->at(k)))
						{
							pSVector->push_back(pUVector->at(k));
						}
					}
				}	
			}
			for (int l = (i + iPiece); l < iItr; l++)
			{
				if (l < (pUVector->size()))
				{
					if (DoesNotHaveItem(pUVector->at(l)))
					{
						pSVector->push_back(pUVector->at(l));
					}
				}
			}
		}
		iItr *= 2;
	}
}

bool MergeSort::DoesNotHaveItem(int iItem)
{
	for (int iValue : *pSVector)
	{
		if (iItem == iValue)
		{
			return false;
		}
	}
	return true;
}