/*—оздать вводом с клавиаутры два файла FX и FY, содержащих одинаковое 
заданное число целочисленных матриц-стобцов X = (x1, x2, x3) и 
матриц-строк Y = (y1, y2, y3). ѕолучить из файлов FX и FY файл FZ, 
произведени€ Z = XY и определители матриц Z.*/

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
	mov si,0			//i=0
	lp11:   mov cx,0    //j=0
	lp12:   mov ax,si   //i
    mul q           //i*q
    mov bx,ax       //i*q
    add bx,cx       //i*q+j
    shl bx,2        //[i][j]
    fldz            //0
    mov di,bx       //сохранить индекс[i][j]
    fstp    R[bx]   //R[i][j]=0
    mov bp,0        //k=0
lp13:   mov ax,si   //i
    mul n			//i*n
    mov bx,ax       //i*n
    add bx,bp       //i*n+k
    shl bx,2        //[i][k]
    fld A[bx]       //A[i][k]
    mov ax,bp       //k
    mul q           //k*q
    mov bx,ax       //k*q
    add bx,cx       //k*q+j
    shl bx,2        //[k][j]
    fmul    B[bx]   //A[i][k]*B[k][j]
    fadd    R[di]   //R[i][j]+A[i][k]*B[k][j]
    fstp    R[di]   //R[i][j]=R[i][j]+A[i][k]*B[k][j]
    inc bp			//k=k+1
    cmp bp,n        //k<n
    jb  lp13        //если меньше - продолжить
    inc cx			//j=j+1
    cmp cx,q        //j<q
    jb  lp12        //если меньше - продолжить
    inc si			//i=i+1
    cmp si,m        //i<m
    jb  lp11        //если меньше - продолжить
	}
}

int det(int **res)   //нахождение определител€
{
	/*_asm {
		xor  si, si

		mov  cx, n
		@1:
		xor  bx, bx
		xor  di, di
		push cx
		mov  cx, n
		@2:
		push bx
		push cx
		push di
		push si

		xor  bx, bx
		mov  cx, n
		@3:
		mov  ax, word ptr mas[si]
		xor dx, dx
		imul word ptr mas[di]
		add  bx, ax
		add  si, 2
		add  di, 2 * n
		loop @3

		mov  ax, bx
		pop  si
		pop  di
		pop  cx
		pop  bx
		mov  word ptr res[bx + si], ax
		add  bx, 2
		add  di, 2
		loop @2

		pop  cx
		add  si, 2 * n
		loop @1
	}*/
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