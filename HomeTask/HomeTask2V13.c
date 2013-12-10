/*
 ============================================================================
 Name        : HomeTask1V13.c
 Author      : Arthur Ambartsumov
 Version     : 1.0
 Copyright   : All rights reserved
 Description : Составить программу, определяющую сонаправленность векторов
               заданному. Вычисления оформить в виде функции, принимающей на
               вход массив 3-мерных радиус-векторов и еще один 3-мерный
               радиус-вектор, сонаправленность которому мы будем определять.
               3-мерный радиус-вектор задается массивом указателей на три
               координаты этого вектора в пространстве. Сонаправленность
               означает наличие положительной проекции одного вектора на
               другой. На выход функция должна возвращать массив указателей
               на номера сонаправленных векторов.
 ============================================================================
 */

#define FALSE 0
#define TRUE 1
#define ERROR 2
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>



int *vectorsComp(const double *const, const double *const, const int, int*);
int collinearVectors(const double *const rVector1, const double *const rVector2);


int main(void) {

	//объявление и инициализация переменных
	double rVector[3] = {0};	//массив координат этолонного радиус вектора
	int number_of_vectors = 0;	//количество векторов, которые необходимо проверить
	double *arrVector = NULL;	//массив координат нескольких радиус-векторов
	int amount = 0;	//переменная в которую будет записано количество сонаправленных векторов
	int *collinear_vectors = NULL;	//указатель на массив содержащий номера сонаправленных векторов

	//Ввод координат вектора с которым будем сравнивать
	printf("Введите координаты радиус-вектора: ");
	scanf("%lf%lf%lf", &rVector[0], &rVector[1], &rVector[2]);
	printf("Проверка. Вы ввели вектор с координатами: (%.2lf, %.2lf, %.2lf)\n\n", rVector[0], rVector[1], rVector[2]);

	if (!(rVector[0]) && !(rVector[1]) && !(rVector[2]))
	{
		printf("Вектор имеет нулевую длину!! Выполнение программы невозможно.");
		return EXIT_SUCCESS;
	}

	//Ввод количества проверяемых векторов и проверка
	printf("Введите количество векторов, которые необходимо проверить: ");
	scanf("%d", &number_of_vectors);
	while (number_of_vectors <= 0){
	    printf("Вы ввели не корректное значение, повторите ввод: ");
	    scanf("%d", &number_of_vectors);
	}
	printf("Проверка. Введённое количество векторов: N = %d\n\n", number_of_vectors);

	//Выделение памяти и проверка
	arrVector = (double*)calloc((number_of_vectors * 3), sizeof(double));
	//проверка на успешное выделение памяти для массива arrVector
	while (arrVector == NULL)
	{
		printf("\tДля требуемого количества векторов не может быть выделена память\nПовторите ввод: ");
		scanf("%d", &number_of_vectors);
		printf("Проверка. Введённое количество векторов: N = %d\n\n", number_of_vectors);
		arrVector = (double*)calloc((number_of_vectors * 3), sizeof(double));
	}

	//Ввод координат  векторов
	printf("Ввод координат векторов:\n");
	for (size_t i = 0; i <= (number_of_vectors * 3 - 1); i += 3)
	{
		printf("\tВведите координаты %zd вектора: ", (i / 3 + 1));
		scanf("%lf%lf%lf", (arrVector + i), (arrVector + i + 1), (arrVector + i + 2));
	}
	//Выыод координат на экран
	printf("\nПроверка координат векторов:\n");
	for (size_t i = 0; i <= (number_of_vectors * 3 - 1); i += 3)
	{
		printf("\tКоординаты %zd вектора: (%.2lf, %.2lf, %.2lf)\n", (i / 3 + 1), *(arrVector + i), *(arrVector + i + 1), *(arrVector + i + 2));
	}


	//использование функции vectorsComp
	collinear_vectors = vectorsComp(rVector, arrVector, number_of_vectors, &amount);
	if (collinear_vectors == NULL) {
	    printf("\nФункция vectorsComp вернула нулевой указатель!!\n");
	    return EXIT_SUCCESS;
	}
	printf("\nВсего векторов сонаправлено: %d\n", amount);

	//вывод номеров сонаправленных векторов
	if (!amount)
			printf("Ни один из векторов не сонаправлен исходному");
	else
	{
		printf ("Вектора под номерами ");
		for (size_t i = 0; i <= amount - 1; i++) printf("%d ", *(collinear_vectors + i));
		printf ("сонаправлены исходному вектору");
	}


	//Освобождение памяти
	free(collinear_vectors);
	free(arrVector);

	return EXIT_SUCCESS;
}

//Функция сравнивает набор радиус-векторов с этолонным
int *vectorsComp(const double *const rVector, const double *const arrVector, const int number_of_vectors, int *counter)
{
    //Проверка указателей
    if ((rVector == NULL) || (arrVector == NULL) || (counter == NULL)) {
        printf("\nВ vectorsComp функцию был передан нулевой указатель!!!\n");
        return NULL;
    }

	*counter = 0;	//обнуление количества сонаправленых векторов
	int *array_of_numbers;	//массив содержащий номера сонаправленых векторов
	array_of_numbers = (int*)calloc(number_of_vectors, sizeof(int));	//выделение памяти для массива содержащего намера векторов
	for (size_t i = 0; i < (number_of_vectors); i++)
	{
		switch (collinearVectors(rVector, (arrVector + i * 3)))
		{
			case TRUE:	//если вектора сонаправлены
			{
				*(array_of_numbers + *counter) = i + 1;	//записать в array_of_numbers номер текущего вектора
				(*counter)++;	//увеличить счётчик сонаправленых векторов
				break;
			}
			case ERROR:	//если при вычислении возникла ошибка
			{
				printf("\nВектор под номером %zd нулевой длины, произошло деление на ноль!\n\n", i + 1);	//вывести предупреждение
				break;
			}
			default: break;
		}
	}
	return array_of_numbers;
}

//Проверяет на сонаправленность 2 радиус-вектора.
//Если они сонапоавлены, то возвращает TRUE, если не сонаправлены то FALSE
//Если произошло деление на ноль, то возвращается ERROR
int collinearVectors (const double *const rVector1, const double *const rVector2)
{
    //Проверка указателей
    if ((rVector1 == NULL) || (rVector2 == NULL)) {
        printf("\nВ vectorsComp функцию был передан нулевой указатель!!!\n");
        return ERROR;
    }

	double cosAlf = 0;	//косинус угла между векторами
	double scalar_multiplication = 0;		//скалярное произведение векторов
	double modVector1 = 0;	//модуль вектора 1
	double modVector2 = 0;	//модуль вектора 2

	//вычисление косинуса
	scalar_multiplication = *(rVector1) * (*(rVector2)) + *(rVector1 + 1) * (*(rVector2 + 1)) + *(rVector1 + 2) * (*(rVector2 + 2));
	modVector1 = sqrt (*(rVector1) * (*(rVector1)) + *(rVector1 + 1) * (*(rVector1 + 1)) + *(rVector1 + 2) * (*(rVector1 + 2)));
	modVector2 = sqrt (*(rVector2) * (*(rVector2)) + *(rVector2 + 1) * (*(rVector2 + 1)) + *(rVector2 + 2) * (*(rVector2 + 2)));
	if ((modVector1 == 0) || (modVector2 == 0))
		return ERROR;
	else
		cosAlf = scalar_multiplication / (modVector1 * modVector2);

	//проверка сонаправленности
	if (cosAlf > 0) return TRUE;
	else return FALSE;
}




