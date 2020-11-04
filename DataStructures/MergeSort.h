#pragma once

namespace std
{
	template <class _Ty>
	class allocator;

	template <class _Ty, class _Alloc = allocator<_Ty>>
	class vector;
}

using namespace std;

class MergeSort
{
	vector<int>* pSVector;
	void Sort();
	bool IsItemInFirstPositionLessThanSecond(int iPosition1, int iPosition2);
	void AddToBufferAt(int iPosition, vector<int>& vBuffer);
	bool DoesNotHaveItem(vector<int>& vVector, int iItem);
	void AddRemainingToBuffer(int iStart, int iEnd, vector<int>& vBuffer);
	void CopyToSVector(int iStart, vector<int>& vFrom);
public:
	MergeSort(vector<int>* pUVector);
	vector<int>* GetSortedItems();
};


