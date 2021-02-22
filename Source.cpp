#include <iostream>
#include <ctime>
#include <math.h>
#define N 11
#define MY_ERROR_FILE 1

void fillArrayByHand(float mas[][N], int& rows, int& cols);
void fillArrayByRandom(float mas[][N], int& rows, int& cols);
void fillArrayByFunc(float mas[][N], int &rows, int &cols);
void fillArray(float mas[][N], int &rows, int &cols);
void printArray(float mas[][N], int rows, int cols);
int saveArray(float mas[][N], int rows, int cols);
int fillArrayByFile(float mas[][N], int& rows, int& cols);
int saveArrayInBinary(float mas[][N], int rows, int cols);
int fillArrayByBinary(float mas[][N], int& rows, int& cols);
float geometricMean(float mas[][N], int rows, int cols, float &max);
int colOfMaxNumber(float mas[][N], int rows, int cols, float& max);

int main()
{
	system("chcp 1251");
	srand(time(0));

	int rows, cols;
	float mas[N][N], max;
	
	fillArray(mas, rows, cols);
	printArray(mas, rows, cols);

	printf("������� �������������� ������ � ���������� ��������� ������� = %f\n\n", geometricMean(mas, rows, cols, max));

	system("pause");
	return 0;
}

//���������� �������.
void fillArray(float mas[][N], int &rows, int &cols)
{
	int choice;
	printf("�������� ������ ���������� �������:\n1)���������� �������.\n2)���� � ����������.\n"
		"3)� ������� �������.\n4)�� ���������� �����.\n5)�� ��������� �����.\n");
	do
		scanf_s("%i", &choice);
	while (choice < 1 || choice > 5);
	switch (choice)
	{
	case 1: fillArrayByRandom(mas, rows, cols); break;
	case 2: fillArrayByHand(mas, rows, cols); break;
	case 3: fillArrayByFunc(mas, rows, cols); break;
	case 4: fillArrayByFile(mas, rows, cols); break;
	case 5: fillArrayByBinary(mas, rows, cols); break;
	}
}
//���������� ������� � ������� ����������.
void fillArrayByHand(float mas[][N], int &rows, int &cols)
{
	printf("������� ���������� ����� � ��������, �� �� ����� 10:\n");
	printf("rows = ");
	do scanf_s("%i", &rows); while (rows < 0 || rows > 10);
	printf("cols = ");
	do scanf_s("%i", &cols); while (cols < 0 || cols > 10);
	int number;
	for (int i = 1; i < rows+1; i++)
	{
		for (int j = 1; j < cols+1; j++)
		{
			scanf_s("%i", &number);
			mas[i][j] = number;
		}
	}
	saveArray(mas, rows, cols);
	saveArrayInBinary(mas, rows, cols);
}
//���������� ������� ��������.
void fillArrayByRandom(float mas[][N], int &rows, int &cols)
{
	printf("������� ���������� ����� � ��������, �� �� ����� 10:\n");
	printf("rows = ");
	do scanf_s("%i", &rows); while (rows < 0 || rows > 10);
	printf("cols = ");
	do scanf_s("%i", &cols); while (cols < 0 || cols > 10);
	int A, B;
	printf("������� ������� ��������� ����� � � �\nA = ");
	scanf_s("%i", &A);
	printf("B = ");
	scanf_s("%i", &B);
		
	for (int i = 1; i < rows+1; i++)
	{
		for (int j = 1; j < cols+1; j++)
		{
			mas[i][j] = rand() % (B - A + 1) + A;
		}
	}
	saveArray(mas, rows, cols);
	saveArrayInBinary(mas, rows, cols);
}
//���������� ������� � ������� �������.
void fillArrayByFunc(float mas[][N], int &rows, int &cols)
{
	printf("������� ���������� ����� � ��������, �� �� ����� 10:\n");
	printf("rows = ");
	do scanf_s("%i", &rows); while (rows < 0 || rows > 10);
	printf("cols = ");
	do scanf_s("%i", &cols); while (cols < 0 || cols > 10);
	for (int i = 1; i < rows+1; i++)
	{
		for (int j = 1; j < cols+1; j++)
		{
			float a, b;
			
			a = (float)i; b = (float)j; 
			if (i <= j)
				mas[i][j] = exp(b - a);
			else
				mas[i][j] = exp(a / b);
		}
	}
	saveArray(mas, rows, cols);
	saveArrayInBinary(mas, rows, cols);
}
//����� �������.
void printArray(float mas[][N], int rows, int cols)
{
	for (int i = 1; i < rows+1; i++) 
	{
		printf("\n");
		for (int j = 1; j < cols+1; j++)
		{
			printf("%7.1f ", mas[i][j]);
		}
	}
	printf("\n");
}
//���������� ������� � ���������� ��������� � ���������� �������� ��������������� ��� �����.
float geometricMean(float mas[][N], int rows, int cols, float &max)
{
	int properCol;
	properCol = colOfMaxNumber(mas, rows, cols, max);
	printf("���������� ������� = %.1f � ��������� � %i-� �������\n\n", max, properCol);
	float productNumbers = 1.0;
	printf("�������� ������: ");
	for (int i = 1; i < rows+1; i++)
	{
		productNumbers *= mas[i][properCol];
		printf("%.1f ", mas[i][properCol]);
	}
	printf("\n\n");
	if(productNumbers>=0)
	return pow(productNumbers, 1.0/(rows));
}
// ���������� ������������� �������� �������.
int colOfMaxNumber(float mas[][N], int rows, int cols, float& max)
{
	int properCol = 0;
	for (int i = 1; i < rows + 1; i++)
	{
		for (int j = 1; j < cols + 1; j++)
		{
			if (mas[i][j] > max)
			{
				max = mas[i][j];
				properCol = j;
			}
		}
	}
	return properCol;
}
// ���������� ������� � ��������� ����.
int saveArray(float mas[][N], int rows, int cols)
{
	FILE* file;
	if (fopen_s(&file, "file.txt", "w") != 0)
	{
		printf("File error!");
		return MY_ERROR_FILE;
	}
	fprintf(file, "%i ", rows);
	fprintf(file, "%i \n", cols);
	for (int i = 1; i < rows + 1; i++)
	{
		for (int j = 1; j < cols + 1; j++)
		{
			fprintf(file, "%.1f\n", mas[i][j]);
		}
	}
	fclose(file);
	return 0;
}
// ���������� ������� �� ���������� �����.
int fillArrayByFile(float mas[][N], int &rows, int &cols)
{
	FILE* file;
	if (fopen_s(&file, "file.txt", "r") != 0)
	{
		printf("File error!");
		return MY_ERROR_FILE;
	}
	fscanf_s(file, "%i ", &rows);
	fscanf_s(file, "%i \n", &cols);
	for (int i = 1; i < rows + 1; i++)
	{
		for (int j = 1; j < cols + 1; j++)
		{
			fscanf_s(file, "%f\n", &mas[i][j]);
		}
	}
	fclose(file);
	return 0;
}
// ���������� ������� � �������� ����.
int saveArrayInBinary(float mas[][N], int rows, int cols)
{
	FILE* binaryFile;
	if (fopen_s(&binaryFile, "binaryFile.bin", "wb") != 0)
	{
		printf("File error!");
		return MY_ERROR_FILE;
	}
	fwrite(&rows, sizeof(int), 1, binaryFile);
	fwrite(&cols, sizeof(int), 1, binaryFile);
	for (int i = 1; i < rows + 1; i++)
	{
		for (int j = 1; j < cols + 1; j++)
		{
			fwrite(mas, sizeof(float), cols*rows, binaryFile);
		}
	}
	fclose(binaryFile);

	return 0;
}
// ���������� ������� �� ��������� �����.
int fillArrayByBinary(float mas[][N], int &rows, int &cols)
{
	FILE* binaryFile;
	if (fopen_s(&binaryFile, "binaryFile.bin", "rb") != 0)
	{
		printf("File error!");
		return MY_ERROR_FILE;
	}
	fread(&rows, sizeof(int), 1, binaryFile);
	fread(&cols, sizeof(int), 1, binaryFile);
	for (int i = 1; i < rows + 1; i++)
	{
		for (int j = 1; j < cols + 1; j++)
		{
			fread(mas, sizeof(float), cols * rows, binaryFile);
		}
	}
	fclose(binaryFile);
	return 0;
}