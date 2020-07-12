#pragma once

//const int arrayLen = 10;
#define arrayLen 10

typedef struct num {
	int positive;
	int len;
	char* digits;
}number;

number* checkMin(number* num, int n, number* min);
number* checkMax(number* num, int n, number* max);
number* compareLen(number* a, number* b);
void readNumbers(number* num, int n, number** min, number** max);
void printAll(number* num, int n);
void copyArray(number* num, number* temp, int l1, int larger, int i, int j, int k, int delta);
void add(number* a, number* b, number* result, int l1, int larger, number* temp, number* temp2, char sign);
int checkIdentical(number* a, number* b);
void subtract(number* x, number* y, number* result, number* a, number* b, char sign);
void reverseArray(number* num);
void addHandler(number* num, int i, int j, int k, int n, number** min, number** max, char symbol);
void printMin(number* min);
int power(int n);
void printMax(number* max);