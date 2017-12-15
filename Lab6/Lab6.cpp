// Lab6.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
int Size_Motiv;
int Exaples_Lenght;
int Count_Examples;
char** Examples;
char *StringCounter;
int * Counter;
bool CounterPlus()
{
	for (int i = Size_Motiv - 1; i >= 0; i--)
	{
		if (Counter[i] < 3)
		{
			Counter[i]++;
			return true;
		}
		else
		{
			Counter[i] = 0;
		}
	}
	return false;
}
void CounterToMotiv()
{
	for (int i = 0; i < Size_Motiv; i++)
	{
		if (Counter[i] == 0)
			StringCounter[i] = 'A';
		else
			if (Counter[i] == 1)
				StringCounter[i] = 'C';
			else
				if (Counter[i] == 2)
					StringCounter[i] = 'G';
				else
					if (Counter[i] == 3)
						StringCounter[i] = 'T';
	}
}
int HamingDistnance(int step, int shift,int size)
{
	int res = 0;
	for (int i = 0; i < size; i++)
	{
		if (Examples[step][shift + i] != StringCounter[i])
			res++;
	}
	return res;
}
int MinPosition(int step,int size)
{
	int min = Size_Motiv;
	for (int i = 0; i < Exaples_Lenght - Size_Motiv + 1; i++)
	{
		int res = HamingDistnance(step, i,size);
		if (res < min)
			min = res;
	}
	return min;
}
int HamingMin(int size)
{
	int res = 0;
	for (int i = 0; i < Count_Examples; i++)
	{
		res += MinPosition(i,size);
	}
	return res;
}
void Shift(int k)
{
	for (int i = k; i < Size_Motiv;i++)
	{
		Counter[i] = 3;
	}
}
int main()
{
	FILE * pFile;
	errno_t err;
	err = fopen_s(&pFile, "input.txt", "r");
	fscanf_s(pFile, "%i", &Size_Motiv);
	char chr = '*';
	int k = 0;
	fseek(pFile, 2, SEEK_CUR);
	while ((chr != '\n') && (k<20))
	{
		fscanf_s(pFile, "%c", &chr);
		k++;
	}
	k--;
	Exaples_Lenght = k;
	fseek(pFile, -Exaples_Lenght - 2, SEEK_CUR);
	k = 0;
	while (!feof(pFile))
	{
		fscanf_s(pFile, "%c", &chr);
		k++;
	}
	Count_Examples = k / (Exaples_Lenght + 1);
	Examples = new char*[Count_Examples];
	for (int i = 0; i < Count_Examples; i++)
	{
		Examples[i] = new char[Exaples_Lenght];
	}
	fseek(pFile, 0, SEEK_SET);
	int tmp;
	fscanf_s(pFile, "%i", &tmp);
	fseek(pFile, 2, SEEK_CUR);
	for (int i = 0; i < Count_Examples; i++)
	{
		for (int j = 0; j < Exaples_Lenght; j++)
		{
			fscanf_s(pFile, "%c", &Examples[i][j]);
		}
		fscanf_s(pFile, "%c", &chr);
	}
	fclose(pFile);
	Counter = new int[Size_Motiv];
	StringCounter = new char[Size_Motiv];
	for (int i = 0; i < Size_Motiv; i++)
	{
		Counter[i] = 0;
		StringCounter[i] = 'A';
	}
	CounterToMotiv();
	char* resmativ = new char[Size_Motiv];
	int min = HamingMin(Size_Motiv);
	for (int i = 0; i < Size_Motiv; i++)
	{
		resmativ[i] = StringCounter[i];
	}
	while (CounterPlus())
	{
		CounterToMotiv();
		int res = 0;
		for(int i=1;i<Size_Motiv;i++)
		{
			res = HamingMin(i);
			if (res > min)
			{
				res = -1;
				Shift(i);
				break;
			}
		}
		if (res >= 0)
		{
			res = HamingMin(Size_Motiv);
		}
		else
		{
			continue;
		}
		if (res < min)
		{
			min = res;
			for (int i = 0; i < Size_Motiv; i++)
			{
				resmativ[i] = StringCounter[i];
			}
		}
	}
	err = fopen_s(&pFile, "output.txt", "w");
	for (int i = 0; i < Size_Motiv; i++)
	{
		fprintf_s(pFile, "%c ", resmativ[i]);
	}
	fclose(pFile);
	delete(Examples);
	delete(Counter);
	delete(resmativ);
	delete(StringCounter);
	return 0;
}


