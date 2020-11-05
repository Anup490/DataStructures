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
	int iIterationStep = 2;
	int iPiece = iIterationStep / 2;
	while (iPiece <= (pSVector->size()))
	{
		for (int i=0; i<(pSVector->size()); i+=iIterationStep)
		{
			vector<int> vBuffer;
			for (int j = i; j < (i + iPiece); j++)
			{
				for (int k = (i + iPiece); k < (i + iIterationStep); k++)
				{
					if (IsItemInFirstPositionLessThanSecond(j,k))
					{
						AddToBufferAt(j, vBuffer);
						break;
					}
					else 
					{
						AddToBufferAt(k, vBuffer);
					}
				}
				AddToBufferAt(j, vBuffer);
			}
			AddRemainingToBuffer(i + iPiece, i + iIterationStep, vBuffer);
			CopyToSVector(i, vBuffer);
		}
		iIterationStep *= 2;
		iPiece = iIterationStep / 2;
	}
}

bool MergeSort::IsItemInFirstPositionLessThanSecond(int iPosition1, int iPosition2)
{
	if ((iPosition1 < (pSVector->size())) && (iPosition2 < (pSVector->size())))
	{
		return (pSVector->at(iPosition1)) < (pSVector->at(iPosition2));
	}
	return false;
}

void MergeSort::AddToBufferAt(int iPosition, vector<int>& vBuffer)
{
	if ((iPosition < (pSVector->size())) && DoesNotHaveItem(vBuffer, pSVector->at(iPosition)))
	{
		vBuffer.push_back(pSVector->at(iPosition));
	}
}

bool MergeSort::DoesNotHaveItem(vector<int>& vVector, int iItem)
{
	for (int iValue : vVector)
	{
		if (iItem == iValue)
		{
			return false;
		}
	}
	return true;
}

void MergeSort::AddRemainingToBuffer(int iStart, int iEnd, vector<int>& vBuffer)
{
	for (int l = iStart; l < iEnd; l++)
	{
		if (l < (pSVector->size()))
		{
			if (DoesNotHaveItem(vBuffer, pSVector->at(l)))
			{
				vBuffer.push_back(pSVector->at(l));
			}
		}
	}
}

void MergeSort::CopyToSVector(int iStart, vector<int>& vFrom)
{
	for (int m = 0; m < (vFrom.size()); m++)
	{
		if ((iStart + m) < (pSVector->size()))
		{
			pSVector->at(iStart + m) = vFrom.at(m);
		}
	}
}