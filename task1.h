/*
    Code written by:
	Panagiotis Karoutsos, 02034
	Olga Vasileiou, 01691
    Stefania Douliaka, 00974
*/

#ifndef FUNCS_H
#define SIZE 1024
typedef struct age
{
	int years, months;
}age;
typedef struct pet
{
	int id;
	char* sex; 
	char* breed;
	age* pet_age;
}pet;


int countLines(char* FN);
void bubbleSort(pet p[], int n);
void mainMenu();
int lowerbd(pet p[], int start, int end, char x[64]);
int upperbd(pet p[], int start, int end, char x[64]);
int binarySearch(pet p[], int l, int r, char x[64]);

#define FUNCS_H
#endif
