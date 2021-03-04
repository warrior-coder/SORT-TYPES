#include <iostream>

using namespace std;

void sort_bubble(int);
void sort_selection(int);
void sort_insertion(int);
void sort_shell(int);

void split(int, int);
void merge(int, int, int);

const int n = 10;
int mas[n] = { 10,5,4,7,8,9,6,3,3,4 };
int tmas[n];

int main()
{
	cout << "Before sort: " << endl;
	for (int i = 0; i < n; i++) cout << mas[i] << ' ';
	cout << endl;

	//sort_bubble(10);
	//sort_selection(10);
	//sort_insertion(10);
	//sort_shell(10);
	split(0, 9);

	cout << "After sort: " << endl;
	for (int i = 0; i < n; i++) cout << mas[i] << ' ';
	cout << endl;
}

void sort_bubble(int n)
{
	int temp;

	for (int i = 1; i < n; i++)
		for (int j = n-1; j >= i; j--)
			if (mas[j - 1] > mas[j])
			{
				temp = mas[j-1];
				mas[j-1] = mas[j];
				mas[j] = temp;
			}
}

void sort_selection(int n)
{
	int temp, i_temp;

	for (int i = 0; i < n; i++)
	{
		i_temp = i;
		for (int j = i+1; j < n; j++)
			if (mas[i_temp] > mas[j])
				i_temp = j;

		if (i_temp != i)
		{
			temp = mas[i_temp];
			mas[i_temp] = mas[i];
			mas[i] = temp;
		}
	}
}

void sort_insertion(int n)
{
	int temp, j;

	for (int i = 1; i < n; i++)
	{
		temp = mas[i];

		for (j = i-1; j >= 0 && temp < mas[j]; j--)
			mas[j+1] = mas[j];

		mas[j+1] = temp;
	}
}

void sort_shell(int n)
{
	int temp, j;

	for (int d = 3; d > 0; d--)
		for (int i = d; i < n; i++)
		{
			temp = mas[i];

			for (j = i-d; j >= 0 && temp < mas[j]; j-=d)
				mas[j+d] = mas[j];

			mas[j+d] = temp;
		}
}

void split(int left, int right)
{
	if (left < right)
	{
		int middle = (left + right) / 2;

		split(left, middle);
		split(middle+1, right);

		merge(left, middle, right);
	}
}

void merge(int left, int middle, int right)
{
	int i = left, j = middle+1, k = 0;

	while (i <= middle && j <= right)
	{
		if (mas[i] < mas[j])
			tmas[k++] = mas[i++];
		else
			tmas[k++] = mas[j++];
	}

	while (i <= middle) tmas[k++] = mas[i++];
	while (j <= right) tmas[k++] = mas[j++];
	
	k = 0;
	while (left <= right) mas[left++] = tmas[k++];
}