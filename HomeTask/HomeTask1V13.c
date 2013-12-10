/*
 ============================================================================
 Name        : HomeTask1V13.c
 Author      : Arthur Ambartsumov
 Version     : 1.0
 Copyright   : All rights reserved
 Description : Составить программу расчета количества расположенных внутри
               окружности точек с целочисленными координатами. Решение
               оформить в виде функции, принимающей на вход указатели на
               координаты центра окружности и ее радиус. На выходе функция
               должна возвращать указатель на результат.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int *pointsInCircle(const double *, const double *);

int main(void) {

	//объявление и инициализация переменных
	double center[2] = {0};	//массив хранящий координаты центра окружности
	double radius = 0;		//радиус окружности


	//ввод координат центра окружности и запись их в массив center
	printf("Введите (через пробел) координаты центра окружности: ");
	scanf("%lf%lf", &center[0], &center[1]);
	printf("Проверка: вы ввели\tX = %.3f\tY = %.3f\n\n", center[0], center[1]);	//проверка введенных данных



	//ввод радиуса окружности и запись его в radius
	printf("Введите радиус окружности: ");
	scanf("%lf", &radius);
	while (radius <= 0)
	{
		printf("\tОшибка: вы ввели не положительный радиус\nПовторите ввод: ");
		scanf("%lf", &radius);
	}
	printf("Проверка: вы ввели\tR = %.3lf\n\n", radius);

	//использование функции
	int *amount = pointsInCircle(center, &radius);
	if (amount == NULL)
		printf("\nОшибка: в функцию были переданы не корректные данные!");
	else
		printf("Количество точек внутри окружности N = %d\n", *amount);
	free(amount);

	return EXIT_SUCCESS;
}


//Проверяет количество точек с целочисленными координатами внутри окружности
int *pointsInCircle(const double center[2], const double *const radius)
{
	int buff = 0;
	int *counter = (int*)malloc(sizeof(int));
	*counter = buff;	//счётчик числа точек лежащих внутри окружности
	double centerL[2] = {0};	//массив, который хранит координаты центра окружности в локальной системе координат

	//проверка на ненулевые указатели
	if ((&center[0] == NULL) || (&center[1] == NULL)) return NULL;
	if ((radius == NULL) || (*radius <= 0)) return NULL;


	printf("Функция приняла радиус\tR = %.3lf\t", *radius);
	printf("Функция приняла X = %.3lf\t", *center);
	printf("Функция приняла Y = %.3lf\n\n", *(center+1));

	//определение элементов массива centerL
	for (size_t i = 0; i < (sizeof(centerL)/sizeof(double)); i++)
	{
		*(centerL + i) = *(center + i) - (int)*(center + i);
	}

	//подсчёт всех точек расположеных внутри окружности
	for (int i = -(int)(*radius+1); i <= (int)(*radius+1); i++)
	{
		for (int j = -(int)(*radius+1); j <= (int)(*radius+1); j++)
		{
			if ((*radius) * (*radius) > ((i - *centerL) * (i - *centerL) + (j - *centerL) * (j - *centerL)))
				(*counter)++;
		}
	}
	return counter;	//возврат указателя на количество точек
}



