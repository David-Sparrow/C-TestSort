#include "sort.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#define PODGLAD


//----------NAGLOWKI FUNKCJI--------------
void CreateTab( int **tab, int nSize );
void InitTab( int *tab, int nSize, int nRange );
void CopyTab( int *to, int *from, int nSize );

typedef struct Sort
{
	void( *pFunc )(int*, int);
	const char* nazwa;
}Sort;

//----------------------------------------
int main( int argc, char* argv[] )
{
	if (argc != 3)
	{
		perror( "Instrukcja: <nazwa_programu>, <rozmiar_tablicy>, <zakres_losowania>" );
		return 1;
	}


	srand( (unsigned int)time( NULL ) );

	clock_t start;
	clock_t stop;
	double sortTime;

	int *tab1 = NULL;
	int *tab2 = NULL;

	int nRozmiar = atoi( argv[1] );
	int nZakres = atoi( argv[2] );

	CreateTab( &tab1, nRozmiar );
	CreateTab( &tab2, nRozmiar );

	InitTab( tab1, nRozmiar, nZakres );
	CopyTab( tab2, tab1, nRozmiar );

	//------INICJOWANIE SORTOWAN----------

	Sort tabFunc[] = { &BubbleSort, "BubbleSort",
					&InsertionSort, "InsertionSort",
					&SelectionSort, "SelectionSort",
					&MixedSort, "MixedSort",
					&HalfInsertionSort, "HalfInsertionSort",
					&HeapSort, "HeapSort"};

	//const char * tablica[] = { "aaa", "bbb" };


	int nTabSize = sizeof( tabFunc ) / sizeof( Sort );
	for (int i = 0; i < nTabSize; i++)
	{
		start = clock();
		tabFunc[i].pFunc( tab1, nRozmiar );
		stop = clock();
		sortTime = (double)(stop - start) / CLOCKS_PER_SEC;
		printf( "\nCzas %s wynosi: %0.2lfms\n", tabFunc[i].nazwa, sortTime * 1000 );

#ifdef PODGLAD
		//-------WYSWIETLANIE TABLIC----------
		printf( "\nPIERWSZA tablica:\n" );
		for (int i = 0; i < nRozmiar; i++)
		{
			printf( "%d\n", *(tab1 + i) );
		}
		printf( "\nDRUGA tablica:\n" );
		for (int i = 0; i < nRozmiar; i++)
		{
			printf( "%d\n", *(tab2 + i) );
		}
#endif
		CopyTab( tab1, tab2, nRozmiar );
	}

	start = clock();
	QuickSort( tab1, 0, nRozmiar - 1 );
	stop = clock();
	sortTime = (double)(stop - start) / CLOCKS_PER_SEC;
	printf( "\nCzas QuickSort wynosi %0.2lfms\n", sortTime * 1000 );

#ifdef PODGLAD
	//-------WYSWIETLANIE TABLIC----------
	printf( "\nPIERWSZA tablica: \n" );
	for (int i = 0; i < nRozmiar; i++)
	{
		printf( "%d\n", *((tab1)+i) );
	}
	printf( "\nDRUGA tablica: \n" );
	for (int i = 0; i < nRozmiar; i++)
	{
		printf( "%d\n", *(tab2 + i) );
	}
#endif

	CopyTab( tab1, tab2, nRozmiar );

	start = clock();
	MergeSort( tab1, 0, nRozmiar - 1 );
	stop = clock();
	sortTime = (double)(stop - start) / CLOCKS_PER_SEC;
	printf( "\nCzas MergeSort wynosi %0.2lfms\n", sortTime * 1000 );

#ifdef PODGLAD
	//-------WYSWIETLANIE TABLIC----------
	printf( "\nPIERWSZA tablica:\n" );
	for (int i = 0; i < nRozmiar; i++)
	{
		printf( "%d\n", *((tab1)+i) );
	}
	printf( "\nDRUGA tablica:\n" );
	for (int i = 0; i < nRozmiar; i++)
	{
		printf( "%d\n", *(tab2 + i) );
	}
#endif

	CopyTab( tab1, tab2, nRozmiar );

	start = clock();
	Merge2Sort( tab1, nRozmiar );
	stop = clock();
	sortTime = (double)(stop - start) / CLOCKS_PER_SEC;
	printf( "\nCzas Merge2Sort wynosi %0.2lfms\n", sortTime * 1000 );

#ifdef PODGLAD
	//-------WYSWIETLANIE TABLIC----------
	printf( "\nPIERWSZA tablica:\n" );
	for (int i = 0; i < nRozmiar; i++)
	{
		printf( "%d\n", *((tab1)+i) );
	}
	printf( "\nDRUGA tablica:\n" );
	for (int i = 0; i < nRozmiar; i++)
	{
		printf( "%d\n", *(tab2 + i) );
	}
#endif

	free( tab1 );
	free( tab2 );

	return 0;
}

//----------------------------------------
void CreateTab( int **tab, int nSize )
{
	//*tab = new int[nSize];
	*tab = (int*)malloc( nSize * sizeof( int ) );
}
//----------------------------------------
void InitTab( int *tab, int nSize, int nRange )
{
	for (int i = 0; i < nSize; i++)
	{
		*tab = rand() % nRange;
		tab++;
	}
}
//----------------------------------------
void CopyTab( int *to, int *from, int nSize )
{
	memcpy( to, from, nSize * sizeof( int ) );
}
//----------------------------------------