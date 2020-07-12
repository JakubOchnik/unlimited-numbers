#include "headers.h"
#include <stdio.h>
#include <stdlib.h>


void subtract(number* x, number* y, number* result, number* a, number* b, char sign);
void checkSpace(number* num, long long i, int* n)
{
	int change = 0;
	if (*n == 0 && i > (arrayLen - 1))
	{
		(*n)++;
		change = 1;
	}
	if (i > ((*n) * 2 * (arrayLen)-1) && (*n) != 0)
	{
		(*n) *= 2;
		change = 1;
	}
	/*i = numer litery
	n - iloœæ pomno¿eñ*/
	if (change == 1)
	{
		char* temp_digits = (char*)realloc(num->digits, 2 * (*n) * arrayLen * sizeof(char));
		if (temp_digits != NULL)
		{
			num->digits = temp_digits;
			//free(temp_digits);
		}
		else
			printf("Failed to reallocate an array!");
	}
	change = 0;
}

number* checkMin(number* num, int n, number* min)
{
	if (n == 0)
		min = num;
	if (n > 0)
	{
		if (min->positive == 0 && num->positive == 0)
		{
			//OBIE UJEMNE, WIEKSZA JEST MNIEJSZA
			if (min->len < num->len)
				min = num;
			else if (min->len == num->len)
			{
				//ITERACJA PO KOLEI
				for (int i = 0; i < num->len; i++)
				{
					if ((num->digits[i] - '0' != min->digits[i] - '0'))
					{
						if (num->digits[i] - '0' > min->digits[i] - '0')
						{
							min = num;
							break;
						}
						else
							break;
					}
				}
			}
		}
		else if (min->positive == 1 && num->positive == 1)
		{
			//OBIE DODATNIE, KROTSZA MNIEJSZA
			if (min->len > num->len)
				min = num;
			else if (min->len == num->len)
			{
				//ITERACJA PO KOLEI
				for (int i = 0; i < num->len; i++)
				{
					if ((num->digits[i] - '0' != min->digits[i] - '0'))
					{
						if (num->digits[i] - '0' < min->digits[i] - '0')
						{
							min = num;
							break;
						}
						else
							break;
					}
				}
			}
		}
		//NOWA UJEMNA, STARA DODATNIA
		else if (min->positive == 1 && num->positive == 0)
			min = num;
	}
	return min;
}

number* checkMax(number* num, int n, number* max)
{
	if (n == 0)
		max = num;
	if (n > 0)
	{
		if (max->positive == 1 && num->positive == 1)
		{
			//OBIE DODATNIE
			if (max->len < num->len)
				max = num;
			else if (max->len == num->len)
			{
				//ITERACJA PO KOLEI
				for (int i = 0; i < num->len; i++)
				{
					if ((num->digits[i] - '0' != max->digits[i] - '0'))
					{
						if (num->digits[i] - '0' > max->digits[i] - '0')
						{
							max = num;
							break;
						}
						else
							break;
					}
				}
			}
		}
		else if (max->positive == 0 && num->positive == 0)
		{
			if (max->len < num->len)
				max = num;
			else if (max->len == num->len)
			{
				//ITERACJA PO KOLEI
				for (int i = 0; i < num->len; i++)
				{
					if ((num->digits[i] - '0' != max->digits[i] - '0'))
					{
						if (num->digits[i] - '0' < max->digits[i] - '0')
						{
							max = num;
							break;
						}
						else
							break;
					}
				}
			}
		}
		else if (max->positive == 0 && num->positive == 1)
			max = num;
	}
	return max;
}

number* compareLen(number* a, number* b)
{
	if (a->len < b->len)
		return b;
	else if (a->len > b->len)
		return a;
	else if (a->len == b->len)
	{
		for (int i = 0; i < a->len; i++)
		{
			if ((a->digits[i] - '0' != b->digits[i] - '0'))
			{
				if (a->digits[i] - '0' > b->digits[i] - '0')
					return a;
				else if (a->digits[i] - '0' < b->digits[i] - '0')
					return b;
			}
		}
	}
	return a;
}
void readNumbers(number* num, int n, number** min, number** max)
{
	int i = 0;
	int z = 0;
	int arrayCount = 0;
	int temp;
	int digit;
	/* WCZYTANIE LICZB */
	temp = getchar();
	while (temp != EOF && z < n)
	{
		temp = getchar();
		if (temp != '\n')
		{
			if (temp == '-')
				num->positive = 0;
			else {
				/*
				i = POZYCJA KURSORA LICZBY
				z = NUMER S£OWA
				n = ILOŒÆ S£ÓW
				*/
				digit = temp;// -'0';
				//digit = temp;
				if (i == 0)
					num->digits[i] = digit;
				else if (i != 0)
				{
					checkSpace(num, i, &arrayCount);
					num->digits[i] = digit;
				}
				i++;
			}
		}
		else
		{
			num->len = i;
			*max = checkMax(num, z, *max);
			*min = checkMin(num, z, *min);
			arrayCount = 0;
			z++;
			if (z < n)
			{
				/*
				PRZESUWANIE WSKA¯NIKA STRUKTURY NA NASTÊPN¥ STRUKTURÊ, JAK TABLICA
				WYZEROWANIE KURSORA LICZBY (i = 0)
				WYZEROWANIE UJEMNOSCI
				*/
				num++;
				i = 0;
			}
			else
			{
				num = num - (n - 1);
			}
		}
	}
}

void printAll(number* num, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (num->digits != NULL)
		{
			if (num->positive == 0)
				printf("-");
			for (int x = 0; x < num->len; x++)
				printf("%c", num->digits[x]);
			printf("\n");
		}
		num++;
	}
	num -= (n - 1);
}

void copyArray(number* num, number* temp, int l1, int larger, int i, int j, int k, int delta)
{
	if (temp == NULL)
	{
		if (larger == 0)
		{
			for (int x = 0; x < l1; x++)
			{
				if (x < delta)
					(num + i)->digits[x] = '0';
				else
					(num + i)->digits[x] = (num + k)->digits[x - delta];
			}
			(num + i)->len = l1;
			(num + i)->positive = (num + k)->positive;
		}
		else
		{
			for (int x = 0; x < l1; x++)
			{
				if (x < delta)
					(num + i)->digits[x] = '0';
				else
					(num + i)->digits[x] = (num + j)->digits[x - delta];
			}
			(num + i)->len = l1;
			(num + i)->positive = (num + j)->positive;
		}
	}
	else
	{
		if (larger == 0)
		{
			for (int x = 0; x < l1; x++)
			{
				if (x < delta)
					temp->digits[x] = '0';
				else
					temp->digits[x] = (num + k)->digits[x - delta];
			}
			temp->len = l1;
			temp->positive = (num + k)->positive;
		}
		else
		{
			for (int x = 0; x < l1; x++)
			{
				if (x < delta)
					temp->digits[x] = '0';
				else
					temp->digits[x] = (num + j)->digits[x - delta];
			}
			temp->len = l1;
			temp->positive = (num + j)->positive;
		}
	}
}

void add(number* a, number* b, number* result, int l1, int larger, number* temp, number* temp2, char sign)
{

	//2 pierwsze przypadki
	if ((a->positive == 0 && b->positive == 0) || (a->positive == 1 && b->positive == 1)) {
		int addition = 0;
		int x, y;
		//INIT i = l1 - 1
		for (int h = 0, i = l1 - 1; h <= (l1 - 1); h++, i--) {

			/* PRZYPISYWANIE LICZB */
			x = temp->digits[i] - '0';
			if (larger == 0)
				y = a->digits[i] - '0';
			else
				y = b->digits[i] - '0';

			if (x + y + addition > 9)
			{
				int operation = (x + y + addition) % 10;
				result->digits[h] = operation + '0';
				addition = 1;
			}
			else
			{
				int operation = x + y + addition;
				result->digits[h] = operation + '0';
				addition = 0;
			}

			/* REALOKACJA I KONIEC */
			if ((i - 1) < 0 && addition != 0)
			{
				char* newResult = (char*)realloc(result->digits, (l1 + 1) * sizeof(char));
				if (newResult != NULL)
				{
					result->digits = newResult;
				}
				result->digits[h + 1] = addition + '0';
				result->len++;
			}
			x = 0;
			y = 0;
		}
		if (a->positive == 0)
			result->positive = 0;
		else
			result->positive = 1;
	} // nastepne przypadki
	else if ((a->positive == 1 && b->positive == 0) || (a->positive == 0 && b->positive == 1))
	{
		//temp2 wiekszy
		// 0 - x = temp2= wiekszy, 1 - y=temp2=wiekszy
		if (larger == 0)
		{
			number* x = temp2;
			number* y = temp;
			subtract(x, y, result, a, b, sign);
			//x to b

		}
		else
		{
			number* x = temp;
			number* y = temp2;
			subtract(x, y, result, a, b, sign);
		}
		//x to a
	}
}

int checkIdentical(number* a, number* b)
{
	for (int i = 0; i < a->len; i++)
	{
		if (a->digits[i] != b->digits[i])
			return 0;
	}
	return 1;
}

void subtract(number* x, number* y, number* result, number* a, number* b, char sign)
{
	// 0 - x = temp2= wiekszy, 1 - y=temp2=wiekszy

	// a = (num+j) 
	//a+0 = x = temp/temp2
	// b = (num + k) = y = temp/temp2
	// b+0 = y = temp/temp2
	int t;
	//scenariusz z zamiana x z y - 4,6 w tabelce
	//if ((compareLen(a, b) == b && a->positive == 1) || (compareLen(a, b) == a && b->positive == 1));

	//scenariusz standardowy - 3,5 w tabelce
	int mnoznik;
	int len = 0;
	char ktoraX;
	if (compareLen(a, b) == a)
		mnoznik = a->len;
	else
		mnoznik = b->len;
	if (x->positive == 0 && y->positive == 1)
	{
		number* temp = x;
		x = y;
		y = temp;
	}
	result->positive = 1;
	//po tym zakl ze x dodatni, y ujemny
	//tu sprawdzamy ktory wgl jest ktory
	if (checkIdentical(a, x) == 1)
	{
		//a jest x
		ktoraX = 'a';
	}
	else
	{
		ktoraX = 'b';
	}
	if ((ktoraX == 'a' && compareLen(a, b) == b && a->positive == 1) || (ktoraX == 'b' && compareLen(a, b) == a && b->positive == 1) || (sign == '-' && (ktoraX == 'a' && compareLen(a, b) == a && a->positive == 0) || (ktoraX == 'b' && compareLen(a, b) == b && b->positive == 0)))
	{
		//a dodatnie, b ujemne, b wieksze niz a, zmieni sie znak
		number* temp = x;
		x = y;
		y = temp;
		result->positive = 0;
	}
	int* residual = (int*)malloc(mnoznik * sizeof(int));
	for (int k = 0; k < mnoznik; k++)
		residual[k] = 0;
	for (int i = mnoznik - 1; i >= 0; i--) {
		//ZNAJDUJE NAJBLIZSZY INDEKS, Z KTOREGO POBIERA RESZTE
		int k = i;
		while ((((x->digits[k] - '0') + residual[k] - (y->digits[k] - '0') < 0) && k > 0))
		{
			k--;
		}
		if (k != i)
		{
			x->digits[k]--;
			k++;
			t = k;
			for (int z = 0; z < (i - (t - 1)); z++, k++)
			{
				residual[k] = 10 + (x->digits[k] - '0');
				if (z > 0)
					residual[k - 1]--;
			}

		}
		if (residual[i] != 0)
		{
			result->digits[i] = residual[i] - (y->digits[i] - '0') + '0';
			len++;
		}
		else
		{
			result->digits[i] = (x->digits[i] - '0') - (y->digits[i] - '0') + '0';
			len++;
		}
		result->len = len;
	}
	int l = 0;
	while (result->digits[l] == '0')
		l++;
	for (int z = 0; z < (result->len - l); z++)
		result->digits[z] = result->digits[z + l];
	result->len -= l;
	free(residual);
}

void reverseArray(number* num)
{
	int i = 0, end = num->len - 1;
	while (i < end)
	{
		char buf = num->digits[i];
		num->digits[i] = num->digits[end];
		num->digits[end] = buf;
		i++;
		end--;
	}
}

void addHandler(number* num, int i, int j, int k, int n, number** min, number** max, char symbol)
{
	/*
	i=indeks tej ktora bedzie wynikiem
	j,k = j+k
	*/
	int l1, l2;
	int larger;
	int delta;
	//l1 > l2
	if ((num + j)->len > (num + k)->len)
	{
		l1 = (num + j)->len;
		l2 = (num + k)->len;
		larger = 0;
	}
	else
	{
		l1 = (num + k)->len;
		l2 = (num + j)->len;
		larger = 1;
	}
	delta = l1 - l2;

	if (i >= n)
	{
		number* temp_array = (number*)realloc(num, (i + 1) * sizeof(number));
		if (temp_array != NULL)
		{
			num = temp_array;
		}
		else
			printf("Failed to reallocate a struct array!");
		for (int t = n; t < i; t++)
		{
			(num + t)->digits = NULL;
		}
		(num + i)->digits = (char*)malloc(l1 * sizeof(char));
		copyArray(num, NULL, l1, larger, i, j, k, delta);
	}
	else if (i < n && i != j && i != k)
	{
		if (symbol == '-')
		{
			if ((num + k)->positive == 0)
				(num + k)->positive = 1;
			else
				(num + k)->positive = 0;

		}
		free((num + i)->digits);
		(num + i)->digits = (char*)malloc(l1 * sizeof(char));
		(num + i)->len = l1;
		copyArray(num, NULL, l1, larger, i, j, k, delta); //kopiuje mniejszy na i
		//GITUWA, MOZNA PISAC NA ISTNIEJACEJ
		//TEMP b jako kopia result?

		//liczba1 
		number temp;
		temp.digits = (char*)malloc(l1 * sizeof(char));
		for (int z = 0; z < l1; z++)
			temp.digits[z] = (num + i)->digits[z];
		temp.len = l1; //l1 zawsze wiekszy jest
		temp.positive = (num + i)->positive;
		if (!((num + j)->positive == 1 && (num + k)->positive == 1 || ((num + j)->positive == 0 && (num + k)->positive == 0))) {
			//2 liczba, temp2 jest wiekszy
			number temp2;
			temp2.digits = (char*)malloc(l1 * sizeof(char));
			for (int z = 0; z < l1; z++)
			{
				if (larger == 0)
				{
					temp2.digits[z] = (num + j)->digits[z];
					temp2.len = (num + j)->len;
					temp2.positive = (num + j)->positive;

				}
				else
				{
					temp2.digits[z] = (num + k)->digits[z];
					temp2.len = (num + k)->len;
					temp2.positive = (num + k)->positive;
				}
			}
			temp2.len = l2;
			add(num + j, num + k, num + i, l1, larger, &temp, &temp2, symbol);
			free(temp2.digits);
		}
		else
		{
			add(num + j, num + k, num + i, l1, larger, &temp, NULL, symbol);
			reverseArray(num + i);
		}

		if (symbol == '-')
		{
			if ((num + k)->positive == 0)
				(num + k)->positive = 1;
			else
				(num + k)->positive = 0;

		}
		//check min max

		for (int l = 0; l < n; l++) {
			*max = checkMax(num + l, 1, *max);
			*min = checkMin(num + l, 1, *min);
		}
		free(temp.digits);
	}
	else if (i < n && (i == j || i == k))
	{
		if (symbol == '-')
		{
			if ((num + k)->positive == 0)
				(num + k)->positive = 1;
			else
				(num + k)->positive = 0;

		}
		//ALOKACJA TEMP
		number temp, result;
		temp.len = l1;
		//tu gdzies znak
		temp.digits = (char*)malloc(l1 * sizeof(char));

		result.digits = (char*)malloc(l1 * sizeof(char));
		result.len = l1;
		result.positive = 1;
		copyArray(num, &temp, l1, larger, i, j, k, delta); //kopiuje na tempa ten mniejszy?
		if (!((num + j)->positive == 1 && (num + k)->positive == 1 || ((num + j)->positive == 0 && (num + k)->positive == 0))) {
			//2 liczba
			number temp2;
			temp2.digits = (char*)malloc(l1 * sizeof(char));
			for (int z = 0; z < l1; z++)
			{
				if (larger == 0)
				{
					temp2.digits[z] = (num + j)->digits[z];
					temp2.len = (num + j)->len;
					temp2.positive = (num + j)->positive;

				}
				else
				{
					temp2.digits[z] = (num + k)->digits[z];
					temp2.len = (num + k)->len;
					temp2.positive = (num + k)->positive;
				}
			}
			temp2.len = l2;
			add(num + j, num + k, &result, l1, larger, &temp, &temp2, symbol);
			free(temp2.digits);
		}
		else
		{
			add(num + j, num + k, &result, l1, larger, &temp, NULL, symbol);
			reverseArray(&result);
		}
		//kopiowanie result na num+i
		if ((num + i)->len < result.len)
		{
			char* newResult = (char*)realloc((num + i)->digits, (result.len) * sizeof(char));
			if (newResult != NULL)
			{
				(num + i)->digits = newResult;
			}
			(num + i)->len = result.len;
			(num + i)->positive = result.positive;
		}
		for (int x = 0; x < result.len; x++)
			(num + i)->digits[x] = result.digits[x];
		(num + i)->positive = result.positive;
		(num + i)->len = result.len;
		for (int l = 0; l < n; l++) {
			*max = checkMax(num + l, 1, *max);
			*min = checkMin(num + l, 1, *min);
		}
		free(temp.digits);
		free(result.digits);
	}
}

void printMin(number* min)
{
	if (min->positive == 0)
		printf("-");
	for (int i = 0; i < min->len; i++)
		printf("%c", min->digits[i]);
	printf("\n");
}

int power(int n)
{
	int x = 1;
	for (int i = 0; i < n; i++)
	{
		x *= 10;
	}
	return x;
}

void printMax(number* max)
{
	if (max->positive == 0)
		printf("-");
	for (int i = 0; i < max->len; i++)
		printf("%c", max->digits[i]);
	printf("\n");
}