/*
 ============================================================================
 Name        : HomeTask3V13.c
 Author      : Artur Ambartsumov
 Version     :
 Copyright   : Your copyright notice
 Description : Составить программу поиска значения, наиболее часто
               встречающегося в заданной матрице. Вычисления оформить в виде
               функции, принимающей на вход матрицу, заданную в виде вектора
               векторов, и ее размеры по каждому измерению. На выход функция
               должна возвращать наиболее часто встречаемое значение.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int maxElement(const int *const *const, int, int);

int main(void) {
    //Объявление и инициализация переменных
    int row = 1; //число строк
    int col = 1; //число столбцов
    int **vectorsArr = NULL; //указатель на вектор векторов

    //Задание размерности матрицы
    printf("Введите количество строк матрицы: ");
    scanf("%d", &row);
    printf("Введите количество столбцов матрицы: ");
    scanf("%d", &col);
    //Проверка
    printf("Вы задали матрицу %d x %d\n", row, col);
    if ((row <= 0) || (col <= 0)) {
        printf("\tНевозможно создать матрицу %d x %d", row, col);
        return EXIT_SUCCESS;
    }

    //Создание вектора векторов
    vectorsArr = (int**)malloc(row * sizeof(int*));
    //Проверка
    if (vectorsArr == NULL) {
        printf("\tНе хватило места для выделения памяти!!");
        return EXIT_SUCCESS;
    }
    for (size_t i = 0; i < row; i++) {
            vectorsArr[i] = (int*)malloc(col * sizeof(int));
            if (vectorsArr[i] == NULL) {
                printf("\tНе хватило места для выделения памяти!!");
                return EXIT_SUCCESS;
            }
    }
    printf("\nВектор векторов создан успешно!\n\n");

    //Заполнение вектора векторов
    srand(time(0));
    printf("Сгенерирована матрица:\n\n");
    for (size_t i = 0; i < row; i++) {
         printf("\t");
         for (size_t j = 0; j < col; j++) {
             vectorsArr[i][j] = rand() % 20;
             printf("%d ", vectorsArr[i][j]);
         }
         printf("\n");
    }

    //Использование функции maxElement11
    printf("\nВ массиве наиболее часто встречается элемент: %d", maxElement(vectorsArr, row, col));

    //Удаление вектора векторов
    for (size_t i = 0; i < row; i++)
        free(vectorsArr[i]);
    free(vectorsArr);

    return EXIT_SUCCESS;
}

//Функция ищет элемент, который наиболее часто встречается в массиве и возвращает его значение.
//Если таких элементов несколько, то возвращается значение того, который встречается в массиве первым
int maxElement(const int *const *const vectorsArr, int row, int col) {
    //Проверка на нулевые указатели
    if (vectorsArr == NULL) {
        printf("\n\nФункция получила нулевой указатель!!\n\n");
        return 0;
    }
    printf("\nФункция приняла вектор:\n\n");
    for (size_t i = 0; i < row; i++) {
        printf("\t");
        if (vectorsArr[i] == NULL) {
            printf("\n\nФункция получила пустой указатель!!\n\n");
            return 0;
        }
        for (size_t j = 0; j < col; j++) {
            printf("%d ", vectorsArr[i][j]);
        }
        printf("\n");
    }

    //Расчётнаиболее часто встречающегося значения
    //Перебираем все элементы массива
    int maxCount = 0; //максимальное число совпадений
    int count = 0; //число совпадений для
    int maxNumber = vectorsArr[0][0];
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            count = 0;
            //Перебираем все элементы от i,j до конца
            for (size_t ii = i; ii < row; ii++) {
                for (size_t jj = j; jj < col; jj++) {
                    //Если vectorsArr[i][j] совпатает с одним из последующих, то квеличиваем счётчик
                    if (vectorsArr[i][j] == vectorsArr[ii][jj])
                        count++;
                }
            }
            if (count > maxCount) {
                maxCount = count;
                maxNumber = vectorsArr[i][j];
            }
        }
    }

    return maxNumber;
}








