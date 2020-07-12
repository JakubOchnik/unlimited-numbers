#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "headers.h"

int main()
{
	int n = 0;
	int i = 0, j = 0, k = 0;
	scanf("%d", &n); //BEZ SCANF'A GETCHAR WCZYTUJE OD KOLEJNEJ CYFRY XD

	/* UTWORZENIE TABLICY DLA KAZDEJ LICZBY */
	number* numbers = (number*)malloc(n * sizeof(number));
	for (int x = 0; x < n; x++) {
		//*(numbers + x) = { 1,0 };
		(numbers + x)->positive = 1;
		(numbers + x)->len = 0;
	}
	for (int x = 0; x < n; x++)
		(numbers + x)->digits = (char*)malloc(arrayLen * sizeof(char));

	/* Min / Max */
	number* min = NULL;
	number* max = NULL;

	/* WCZYTANIE LICZB */
	readNumbers(numbers, n, &min, &max);

	char temp = 0;
	while (temp != EOF && temp != 'q')
	{
		temp = getchar();
		if (temp != '\n')
		{
			if (temp == 'm')
			{
				temp = getchar();
				if (temp == 'i')
				{
					temp = getchar();
					if (temp == 'n')
					{
						printMin(min);
					}
				}
				else if (temp == 'a')
				{
					temp = getchar();
					if (temp == 'x')
					{
						printMax(max);
					}
				}
			}
			else if (temp == 'q')
			{
				return 0;
			}
			else if (temp == '?')
			{
				printAll(numbers, n);
			}
			else if ((int)temp >= (int)('0') && (int)temp <= (int)('9'))
			{
				for (int x = 5; x >= 0; x--)
				{
					if (temp == ' ')
					{
						i /= power(x + 1);
						break;
					}
					i += (temp - '0') * power(x);
					temp = getchar();
				}
				if (temp == ' ')
				{
					char sign[2];
					scanf("= %d %s %d\n", &j, sign, &k);
					if (sign[0] == '+')
					{
						addHandler(numbers, i, j, k, n, &min, &max, '+');
					}
					else if (sign[0] == '-')
					{
						addHandler(numbers, i, j, k, n, &min, &max, '-');
					}
				}
			}
		}
	}
	free(numbers);

	return 0;
}