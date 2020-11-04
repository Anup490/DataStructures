#include "MergeSort.h"
#include <vector>


MergeSort::MergeSort(vector<int>* pUVector)
{
	pSVector = pUVector;//new vector<int>;
	if (pSVector)
	{
		Sort(pSVector);
	}
}

vector<int>* MergeSort::GetSortedItems()
{
	return pSVector;
}

void MergeSort::Sort(vector<int>* pUVector)
{
	int iItr = 2;
	while ((iItr/2) <= (pUVector->size()))
	{
		for (int i=0; i<(pUVector->size()); i+=iItr)
		{
			int iPiece = iItr / 2;
			for (int j=i; j<(i + iPiece); j++)
			{
				for (int k = (i + iPiece); k<(i+iItr); k++)
				{
					if ((k < (pUVector->size())) && (j < (pUVector->size())))
					{
						if ((pUVector->at(j)) > (pUVector->at(k)))
						{
							Swap(pUVector->at(j), pUVector->at(k));
						}
					}
				}	
			}
			for (int l = (i + iPiece); l < (i + iItr - 1); l++)
			{
				if ((l + 1) < (pUVector->size()))
				{
					if ((pUVector->at(l)) > (pUVector->at(l + 1)))
					{
						Swap(pUVector->at(l), pUVector->at(l + 1));
					}
				}
			}
		}
		iItr *= 2;
	}

	if ((pUVector->size() % 4) != 0)
	{
		int iStart = iItr / 4;
		int iEnd = iItr / 2;
		for (int l = iStart; l < iEnd; l++)
		{
			if ((l + 1) < (pUVector->size()))
			{
				if ((pUVector->at(l)) > (pUVector->at(l + 1)))
				{
					Swap(pUVector->at(l), pUVector->at(l + 1));
				}

			}
		}
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

void MergeSort::Swap(int& iA, int& iB)
{
	int iTemp = iA;
	iA = iB;
	iB = iTemp;
}