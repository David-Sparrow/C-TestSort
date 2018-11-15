#include "sort.h"
#include <stdlib.h>
#include <string.h>

#define nMAX 10000
//---------------------------------------
void BubbleSort( int* t, int nSize )
{

	for (int i = 0; i < nSize - 1; i++) {
		for (int j = nSize - 1; j > i; j--) {
			if (t[j] < t[j - 1]) {
				int temp = t[j - 1];
				t[j - 1] = t[j];
				t[j] = temp;
			}
		}
	}
}
//----------------------------------------
void InsertionSort( int* t, int nSize )
{
	for (int i = 0; i < nSize; ++i) {
		int tmp = t[i];
		for (int j = i; j > 0 && tmp < t[j - 1]; j--) {
			t[j] = t[j - 1];
			t[j - 1] = tmp;
		}
	}
}
//----------------------------------
void SelectionSort( int* t, int nSize )
{
	for (int i = 0; i < nSize - 1; ++i) {
		int min = t[i];
		int min_x = i;
		for (int j = i + 1; j < nSize; ++j) {
			if (t[j] < t[min_x]) {
				min = t[j];
				min_x = j;
			}
		}
		t[min_x] = t[i];
		t[i] = min;
	}
}
//------------------------------------
void MixedSort( int* t, int nSize )
{
	int min = 1;
	int max = nSize - 1;
	int x;
	while (min <= max)
	{
		for (int i = max; i >= min; i--)
		{
			if (t[i - 1] > t[i])
			{
				int tmp = t[i - 1];
				t[i - 1] = t[i];
				t[i] = tmp;
				x = i;
			}
		}
		min = x + 1;
		for (int i = min; i <= max; i++)
		{
			if (t[i - 1] > t[i])
			{
				int tmp = t[i - 1];
				t[i - 1] = t[i];
				t[i] = tmp;
				x = i;
			}
		}
		max = x - 1;
	}
}
//---------------------------------------
void HalfInsertionSort( int* t, int nSize )
{
	int key;
	int i, j;
	int right, left, mid;

	for (i = 1; i < nSize; i++)
	{
		key = t[i];
		left = 0;
		right = i - 1;

		while (left <= right)
		{
			mid = (left + right) / 2;
			if (key < t[mid]) right = mid - 1;
			else left = mid + 1;
		}

		for (j = i - 1; j >= left; j--)
		{
			t[j + 1] = t[j];
		}

		t[left] = key;
	}
}

//-----------------------------------------
void QuickSort( int* t, int pocz, int nSize )
{
	int i = pocz;
	int j = nSize;
	int x = t[(pocz + nSize) / 2];
	do
	{
		while (t[i] < x) i++;
		while (x < t[j]) j--;
		if (i <= j)
		{
			int temp = t[i];
			t[i] = t[j];
			t[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);
	if (pocz < j) QuickSort( t, pocz, j );
	if (i < nSize) QuickSort( t, i, nSize );
}
//-----------------------------------------
void HeapSort( int* t, int nSize )
{
	int i;
	for (i = (nSize) / 2; i >= 0; i--)
		UpDate( t, i, nSize );
	for (i = nSize - 1; i > 0; i--)
	{
		int temp = t[0];
		t[0] = t[i];
		t[i] = temp;
		UpDate( t, 0, i - 1 );
	}
}
//------------------------------------------
void UpDate( int* t, int l, int p )
{
	if (l == p) return;
	int i = l;
	int j = 2 * i + 1;
	int temp = t[i];
	while (j <= p)
	{
		if (j < p)
			if (t[j] < t[j + 1])j++;
		if (temp >= t[j]) break;
		t[i] = t[j];
		i = j;
		j = 2 * i + 1;
	}
	t[i] = temp;

}
//------------------------------------------
void MergeSort( int* t, int left, int right )
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		MergeSort( t, left, mid );
		MergeSort( t, mid + 1, right );
		Merge( t, left, right );
	}
}
//--------------------------------------
void Merge( int*t, int left, int right )
{
	int* t1 = (int*)calloc( (size_t)(right - left + 1), sizeof( int ) );
	for (int i = left, j = 0; i <= right; i++, j++)
	{
		t1[j] = t[i];

	}
	int i = 0;
	int mid = ((right - left) / 2);
	int rgt = right - left;
	int j = mid + 1;
	int current = left;

	while (i <= mid && j <= rgt)
	{
		if (t1[i] <= t1[j])
		{
			t[current] = t1[i++];
		}
		else
		{
			t[current] = t1[j++];
		}
		current++;
	}
	while (i <= mid)
	{
		t[current++] = t1[i++];
		
	}
	free( t1 );
}
//--------------------------------------
void Merge2Sort( int* t, int nSize )
{
	int tmp1[nMAX] = { 0 };
	int tmp2[nMAX] = { 0 };
	int nSerie;

	do
	{
		int j = 0;
		int k = 0;

		int i = 0;
		while (i < nSize)
		{
			while (i < nSize - 1 && t[i] <= t[i + 1])
				tmp1[j++] = t[i++];
			tmp1[j++] = t[i++];

			while (i < nSize - 1 && t[i] <= t[i + 1])
				tmp2[k++] = t[i++];
			if (i < nSize)
				tmp2[k++] = t[i++];
		}
		int nLast1 = j;
		int nLast2 = k;

		nSerie = 0;
		i = j = k = 0;

		while ((j < nLast1) && (k < nLast2))
		{
			bool bEndSerie = false;
			while (!bEndSerie)
			{
				if (tmp1[j] <= tmp2[k])
				{
					bEndSerie = Copy( t, &i, tmp1, &j, nLast1 );
					if (bEndSerie)
						CopySerie( t, &i, tmp2, &k, nLast2 );
				}
				else
				{
					bEndSerie = Copy( t, &i, tmp2, &k, nLast2 );
					if (bEndSerie)
						CopySerie( t, &i, tmp1, &j, nLast1 );
				}
			}
			nSerie++;
		}
		while (j < nLast1)
		{
			CopySerie( t, &i, tmp1, &j, nLast1 );
			nSerie++;
		}
	} while (nSerie > 1);
}
//---------------
bool Copy( int *t, int* i, int* tmp, int* ix, int nLast )
{
	t[(*i)++] = tmp[(*ix)++];
	if (*ix == nLast)
		return true;
	return tmp[*ix - 1] > tmp[*ix];
}
//-------------
void CopySerie( int *t, int* i, int* tmp, int* ix, int nLast )
{
	bool bEnd = false;
	do
	{
		bEnd = Copy( t, i, tmp, ix, nLast );
	} while (!bEnd);
}
//--------------------------------------
