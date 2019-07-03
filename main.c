
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

void multiply(int *mas1, int *mas2, int **res)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			res[i][j] = 0;
			res[i][j] = mas1[i] * mas2[j];
		}
	}
}

void asm_multiply(int *A, int *B, int **R)
{
	__asm
	{
	}
}

void show(int **mas)
{
	printf("Result matrix: \n");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			printf("[%3d]", mas[i][j]);
		printf("\n");
	}
}

void fileprint(int **mas, FILE *f)
{
	fprintf(f,"Result matrix: \n");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			fprintf(f,"[%3d]", mas[i][j]);
		fprintf(f, "\n");
	}
}

void enter(int *mas, FILE *f)
{
	for (int i = 0; i < 3; i++)
			fscanf(f, "%d ", &mas[i]);
}

int main() 
{
	int sum = 0;
	FILE *FX = fopen("FX.txt", "r");
	FILE *FY = fopen("FY.txt", "r");
	FILE *FZ = fopen("FZ.txt", "w");

	int *X = (int*)malloc(3 * sizeof(int*));
	int *Y = (int*)malloc(3 * sizeof(int*));
	int **Z = (int**)malloc(3 * sizeof(int*));
	for (int i = 0; i < 3; ++i)
		Z[i] = (int*)malloc(3 * sizeof(int));

	enter(*&X, FX);
	enter(*&Y, FY);
	asm_multiply(*&X, *&Y, *&Z);
	show(*&Z);
	system("Pause");
	free(X);
	free(Y);
	free(Z);
	fclose(FX);
	fclose(FY);
	fclose(FZ);
}
