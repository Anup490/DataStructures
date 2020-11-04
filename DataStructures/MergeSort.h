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
	bool DoesNotHaveItem(vector<int>* pVector, int iItem);
public:
	MergeSort(vector<int>* pUVector);
	vector<int>* GetSortedItems();
};


