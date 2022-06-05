#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InputMatrix(int**&, int&);
void SaveToFile(int**&, int&);
void LoadFromFile(int**&, int&);
void FillRandMatrix(int**&, int&);
void PrintAllPaths(int**&, int&);
void PrintRoad(int**&, int&, int, int);
void PrintIncidentMatrix(int**&, int&);
void AddPoint(int**&, int&);

int main()
{
	int work = 1;

	int** matrix = NULL;
	int points = 0;

	while (work)
	{
		system("cls");

		if (matrix != NULL)
		{
			printf("MATRIX:\n");
			for (int i = 0; i < points; i++)
			{
				for (int j = 0; j < points; j++)
				{
					printf("%d  ", matrix[i][j]);
				}
				printf("\n");
			}
		}

		printf("Choose a variant:\n");
		printf("1.Input adjency matrix\n");
		printf("2.Print matrix to file\n");
		printf("3.Load matrix from file\n");
		printf("4.Fill matrix with random values\n");
		printf("5.Print all paths of graph\n");
		printf("6.Print incident matrix\n");
		printf("7.Add point\n");
		printf("8.Exit\n");

		char ch;
		scanf(" %c", &ch);

		system("cls");
		switch (ch)
		{
		case '1':
		{
			InputMatrix(matrix, points);
			break;
		}
		case '2':
		{
			SaveToFile(matrix, points);
			break;
		}
		case '3':
		{
			LoadFromFile(matrix, points);
			break;
		}
		case '4':
		{
			FillRandMatrix(matrix, points);
			break;
		}
		case '5':
		{
			PrintAllPaths(matrix, points);
			break;
		}
		case '6':
		{
			PrintIncidentMatrix(matrix, points);
			break;
		}
		case '7':
		{
			AddPoint(matrix, points);
			break;
		}
		case '8':
		{
			work = 0;
			break;
		}
		default:
		{
			printf("Input error.\n");
			system("pause");
			break;
		}
		}
	}

	if (matrix != NULL)
	{
		for (int i = 0; i < points; i++)
		{
			free(matrix[i]);
		}
		free(matrix);
	}

	return 0;
}

void InputMatrix(int**& matr, int& p)
{
	if (matr != NULL)
	{
		for (int i = 0; i < p; i++)
		{
			free(matr[i]);
		}
		free(matr);

		matr = NULL;
		p = 0;
	}

	printf("Input count of points: ");
	while (p <= 1)
	{
		scanf("%d", &p);
		if (p <= 1)
		{
			printf("Count of points need be more than 1\n");
		}
	}

	matr = (int**)malloc(sizeof(int*) * p);
	for (int i = 0; i < p; i++)
	{
		matr[i] = (int*)malloc(sizeof(int) * p);
	}

	printf("Input matrix values:\n");

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < p; j++)
		{
			matr[j][i] = 0;
		}

		printf("Point %d:\n", i + 1);
		printf("Input numbers of connected points or 0 to end\n");

		int point = 0;
		do
		{
			scanf_s("%d", &point);
			if (point > p)
			{
				printf("Number of point need be less than %d\n", p);
			}
			else if (point == i + 1)
			{
				printf("This graph need be without circles with 0 length\n");
			}
			else if (point != 0)
			{
				matr[i][point - 1] = 1;
				matr[point - 1][i] = 1;
			}
		} while (point != 0);
	}
}

void SaveToFile(int**& matr, int& p)
{
	if (matr == NULL)
	{
		printf("Matrix doesnt exist\n");
		system("pause");
		return;
	}

	char path[256];
	strcpy(path, "");

	printf("Input file path/name to save:\n");
	scanf(" %255s", path);

	FILE* f = fopen(path, "w");
	if (f)
	{
		fprintf(f, "%d\n", p);
		for (int i = 0; i < p; i++)
		{
			for (int j = 0; j < p; j++)
			{
				fprintf(f, "%d  ", matr[i][j]);
			}
			fprintf(f, "\n");
		}

		fclose(f);
	}
	else
	{
		printf("Error of opening file\n");
		system("pause");
	}
}

void LoadFromFile(int**& matr, int& p)
{
	if (matr != NULL)
	{
		for (int i = 0; i < p; i++)
		{
			free(matr[i]);
		}
		free(matr);

		matr = NULL;
		p = 0;
	}

	char path[256];
	strcpy(path, "");

	printf("Input file path/name to load:\n");
	scanf(" %255s", path);

	FILE* f = fopen(path, "r");
	if (f)
	{
		fscanf(f, "%d", &p);

		matr = (int**)malloc(sizeof(int*) * p);
		for (int i = 0; i < p; i++)
		{
			matr[i] = (int*)malloc(sizeof(int) * p);
		}

		for (int i = 0; i < p; i++)
		{
			for (int j = 0; j < p; j++)
			{
				fscanf(f, "%d", &matr[i][j]);
			}
		}

		fclose(f);
	}
	else
	{
		printf("Error of opening file\n");
		system("pause");
	}
}

void FillRandMatrix(int**& matr, int& p)
{
	if (matr != NULL)
	{
		for (int i = 0; i < p; i++)
		{
			free(matr[i]);
		}
		free(matr);

		matr = NULL;
		p = 0;
	}

	printf("Input count of points: ");
	while (p <= 1)
	{
		scanf("%d", &p);
		if (p <= 1)
		{
			printf("Count of points need be more than 1\n");
		}
	}

	matr = (int**)malloc(sizeof(int*) * p);
	for (int i = 0; i < p; i++)
	{
		matr[i] = (int*)malloc(sizeof(int) * p);
	}

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < p; j++)
		{
			matr[j][i] = 0;
		}

		for (int j = 0; j < i + 1; j++)
		{
			matr[i][j] = rand() % 2;
			matr[j][i] = matr[i][j];
		}
	}
}

void PrintAllPaths(int**& matr, int& p)
{
	if (matr == NULL)
	{
		printf("Matrix doesnt exist\n");
		system("pause");
		return;
	}

	int first = 0;

	printf("Input first point (from 1 to %d): ", p);
	while (first <= 0 || first > p)
	{
		scanf("%d", &first);

		if (first <= 0)
		{
			printf("Incorrect input. Value need be more than 0\n");
		}
		else if (first > p)
		{
			printf("Incorrect input. Value need be less than %d\n", p + 1);
		}
	}

	first--;

	PrintRoad(matr, p, first, 0);
	system("pause");
}

void PrintRoad(int**& matr, int& p, int first, int path)
{
	int subpath = path;
	int* arr = (int*)malloc(sizeof(int) * p);
	for (int i = p - 1; i >= 0; i--)
	{
		arr[i] = subpath % 10;
		if (arr[i] == first + 1)
		{
			free(arr);
			return;
		}
		subpath /= 10;
	}

	int flag = 0;
	for (int i = 0; i < p; i++)
	{
		if (arr[i] != 0)
		{
			printf("%d ->", arr[i]);
			flag = 1;
		}
	}
	if (flag)printf("\n");

	for (int i = 0; i < p; i++)
	{
		if (matr[first][i] == 1)
		{
			PrintRoad(matr, p, i, path * 10 + 1 + first);
		}
	}
	free(arr);
}

void PrintIncidentMatrix(int**& matr, int& p)
{
	if (matr == NULL)
	{
		printf("Matrix doesnt exist\n");
		system("pause");
		return;
	}

	int l = 0;
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < i + 1; j++)
		{
			l += matr[i][j];
		}
	}

	if (l == 0)
	{
		printf("Matrix hasnt lines\n");
		system("pause");
		return;
	}

	int** incMatr = (int**)malloc(sizeof(int*) * p);

	for (int i = 0; i < p; i++)
	{
		incMatr[i] = (int*)malloc(sizeof(int) * l);
	}

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < l; j++)
		{
			incMatr[i][j] = 0;
		}
	}

	int numOfLne = 0;

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < i + 1; j++)
		{
			if (matr[i][j] == 1)
			{
				incMatr[i][numOfLne] = 1;
				incMatr[j][numOfLne] = 1;
				numOfLne++;
			}
		}
	}

	printf("Incident matrix:\n");
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < l; j++)
		{
			printf("%d  ", incMatr[i][j]);
		}
		printf("\n");
	}
	system("pause");

	for (int i = 0; i < p; i++)
	{
		free(incMatr[i]);
	}
	free(incMatr);
}

void AddPoint(int**& matr, int& p)
{
	if (matr == NULL)
	{
		printf("Matrix doesnt exist\n");
		system("pause");
		return;
	}

	int** newMatr = (int**)malloc(sizeof(int*) * (p + 1));
	for (int i = 0; i < p; i++)
	{
		newMatr[i] = (int*)malloc(sizeof(int) * (p + 1));
	}

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < p; j++)
		{
			newMatr[j][i] = matr[j][i];
		}
	}

	for (int i = 0; i < p; i++)
	{
		free(matr[i]);
	}
	free(matr);

	matr = newMatr;
	p++;

	printf("Point %d:\n", p);
	printf("Input numbers of connected points or 0 to end\n");

	int point = 0;
	do
	{
		scanf_s("%d", &point);
		if (point > p)
		{
			printf("Number of point need be less than %d\n", p);
		}
		else if (point == p)
		{
			printf("This graph need be without circles with 0 length\n");
		}
		else if (point != 0)
		{
			matr[p - 1][point - 1] = 1;
			matr[point - 1][p - 1] = 1;
		}
	} while (point != 0);
}
