#include <iostream>

using namespace std;

void sort_bubble(int);

void sort_cocktail(int);

void sort_selection(int);

void sort_insertion(int);

void sort_shell(int);

void sort_merge(int, int);
void merge(int, int, int);

void sort_quick_recursion(int, int);

struct St { int L; int R; } stack[10];
void push(int, int, int&);
void pop(int&, int&, int&);
void swap(int&, int&);
void sort_quick(int[], int);

void sort_quick_compressed(int[], int);

const int n = 10;
int mas[n] = { 10,5,4,7,8,9,6,3,3,4 };
int tmas[n];

int main()
{
	cout << "Before sort: " << endl;
	for (int i = 0; i < n; i++)
		cout << mas[i] << ' ';
	cout << endl;

	//sort_bubble(10);
	//sort_cocktail(10);
	//sort_selection(10);
	//sort_insertion(10);
	//sort_shell(10);
	//sort_merge(0, 9);
	//sort_quick_recursion(0, 9);
	//sort_quick(mas, n);
	sort_quick_compressed(mas, n);

	cout << "After sort: " << endl;
	for (int i = 0; i < n; i++)
		cout << mas[i] << ' ';
	cout << endl;
}

//-+-+-+-+-+-+-+-+-BUBBLE SORT-+-+-+-+-+-+-+-+-
void sort_bubble(int n)
{
	int temp;

	for (int i = 1; i < n; i++)
		for (int j = n - 1; j >= i; j--)
			if (mas[j - 1] > mas[j])
			{
				temp = mas[j - 1];
				mas[j - 1] = mas[j];
				mas[j] = temp;
			}
}

//-+-+-+-+-+-+-+-+-COCKTAIL SORT-+-+-+-+-+-+-+-+-
void sort_cocktail(int n)
{
	int temp;
	int k, left = 0, right = n;

	do
	{
		for (int j = n-1; j > left; j--)
			if (mas[j-1] > mas[j])
			{
				temp = mas[j-1];
				mas[j-1] = mas[j];
				mas[j] = temp;
				k = j;
			}
		left = k+1;

		for (int i = 1; i < right; i++)
			if (mas[i-1] > mas[i])
			{
				temp = mas[i-1];
				mas[i-1] = mas[i];
				mas[i] = temp;
				k = i;
			}
		right = k-1;

	} while (left < right);
}

//-+-+-+-+-+-+-+-+-SELECTION SORT-+-+-+-+-+-+-+-+-
void sort_selection(int n)
{
	int temp, i_temp;

	for (int i = 0; i < n; i++)
	{
		i_temp = i;
		for (int j = i + 1; j < n; j++)
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

//-+-+-+-+-+-+-+-+-INSERTION SORT-+-+-+-+-+-+-+-+-
void sort_insertion(int n)
{
	int temp, j;

	for (int i = 1; i < n; i++)
	{
		temp = mas[i];

		for (j = i - 1; j >= 0 && temp < mas[j]; j--)
			mas[j + 1] = mas[j];

		mas[j + 1] = temp;
	}
}

//-+-+-+-+-+-+-+-+-SHELL SORT-+-+-+-+-+-+-+-+-
void sort_shell(int n)
{
	int temp, j;

	for (int d = 3; d > 0; d--)
		for (int i = d; i < n; i++)
		{
			temp = mas[i];

			for (j = i - d; j >= 0 && temp < mas[j]; j -= d)
				mas[j + d] = mas[j];

			mas[j + d] = temp;
		}
}

//-+-+-+-+-+-+-+-+-MERGE SORT-+-+-+-+-+-+-+-+-
void sort_merge(int left, int right)
{
	if (left < right)
	{
		int middle = (left + right) / 2;

		sort_merge(left, middle);
		sort_merge(middle + 1, right);

		merge(left, middle, right);
	}
}

void merge(int left, int middle, int right)
{
	int i = left, j = middle + 1, k = 0;

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

//-+-+-+-+-+-+-+-+-QUICK SORT RECURSION-+-+-+-+-+-+-+-+-
void sort_quick_recursion(int left, int right)
{
	int i = left, j = right;
	int temp, x = mas[(i + j) / 2];

	do
	{
		while (mas[i] < x && i < right) i++;
		while (mas[j] > x && j > left) j--;
		if (i <= j)
		{
			temp = mas[i];
			mas[i] = mas[j];
			mas[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);

	if (left < j) sort_quick_recursion(left, j);
	if (i < right) sort_quick_recursion(i, right);
}

//-+-+-+-+-+-+-+-+-QUICK SORT-+-+-+-+-+-+-+-+-
void push(int L, int R, int& k)
{
	stack[k].L = L;
	stack[k].R = R;
	k++;
}

void pop(int& L, int& R, int& k)
{
	k--;
	L = stack[k].L;
	R = stack[k].R;
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void sort_quick(int mas[], int n)
{
	int i, j, left, right, k = 0;
	int x;

	push(0, n-1, k);

	while (k != -1)
	{
		pop(left, right, k);

		while (left < right)
		{
			i = left;
			j = right;
			x = mas[(i + j) / 2];

			while (i <= j)
			{
				while (mas[i] < x) i++;
				while (mas[j] > x) j--;

				if (i <= j)
				{
					swap(mas[i], mas[j]);
					i++;
					j--;
				}
			}

			if ((j - left) < (right - i))
			{
				if (i < right) push(i, right, k);
				right = j;
			}
			else
			{
				if (left < j) push(left, j, k);
				left = i;
			}
		}
	}
}

//-+-+-+-+-+-+-+-+-QUICK SORT COMPRESSED-+-+-+-+-+-+-+-+-
void sort_quick_compressed(int mas[], int n)
{
	struct St
	{
		int L;
		int R;
		int k;
	} stack[10];


	int i, j, left, right, k;
	int temp, x;

	k = 0;
	stack[k].L = 0;
	stack[k].R = n-1;

	while (k != -1)
	{
		left = stack[k].L;
		right = stack[k].R;
		k--;

		while (left < right)
		{
			i = left;
			j = right;
			x = mas[(i + j) / 2];
	
			while (i <= j)
			{
				while (mas[i] < x) i++;
				while (mas[j] > x) j--;

				if (i <= j)
				{
					temp = mas[i];
					mas[i] = mas[j];
					mas[j] = temp;
					i++;
					j--;
				}
			}

			if ((j - left) < (right - i))
			{
				if (i < right)
				{
					k++;
					stack[k].L = i;
					stack[k].R = right;
				}
				right = j;
			}
			else
			{
				if (left < j)
				{
					k++;
					stack[k].L = left;
					stack[k].R = j;
				}
				left = i;
			}
		}
	}
}