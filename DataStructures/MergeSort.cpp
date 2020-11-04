#include "MergeSort.h"
#include <vector>

MergeSort::MergeSort(vector<int>* pUVector)
{
	pSVector = pUVector;
	if (pSVector)
	{
		Sort();
	}
}

vector<int>* MergeSort::GetSortedItems()
{
	return pSVector;
}

void MergeSort::Sort()
{
	int iItr = 2;
	while ((iItr/2) <= (pSVector->size()))
	{
		int iPiece = iItr / 2;
		for (int i=0; i<(pSVector->size()); i+=iItr)
		{
			vector<int> vBuffer;
			for (int j = i; j < (i + iPiece); j++)
			{
				for (int k = (i + iPiece); k < (i + iItr); k++)
				{
					if ((k < (pSVector->size())) && (j < (pSVector->size())))
					{
						if ((pSVector->at(j)) < (pSVector->at(k)))
						{
							vBuffer.push_back(pSVector->at(j));
							break;
						}
						else if(DoesNotHaveItem(&vBuffer, pSVector->at(k)))
						{
							vBuffer.push_back(pSVector->at(k));
						}
					}	
				}
				if ((j < (pSVector->size())) && DoesNotHaveItem(&vBuffer, pSVector->at(j)))
				{
					vBuffer.push_back(pSVector->at(j));
				}
			}
			for (int l = (i + iPiece); l < (i + iItr); l++)
			{
				if (l < (pSVector->size()))
				{
					if (DoesNotHaveItem(&vBuffer, pSVector->at(l)))
					{
						vBuffer.push_back(pSVector->at(l));
					}
				}
			}
			for (int m = 0; m < (vBuffer.size()); m++)
			{
				if ((i+m) < (pSVector->size()))
				{
					pSVector->at(i + m) = vBuffer.at(m);
				}
			}
		}
		iItr *= 2;
	}
}

bool MergeSort::DoesNotHaveItem(vector<int>* pVector, int iItem)
{
	if (pVector)
	{
		for (int iValue : *pVector)
		{
			if (iItem == iValue)
			{
				return false;
			}
		}
	}
	return true;
}