/*
 ============================================================================
 Name        : HomeTask5V13.c
 Author      : Artur Ambartsumov
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : В вашем распоряжении — квадратная матрица из 10 000 x 10 000
               чисел. Составьте наивный алгоритм подсчета сумм диагональных
               элементов матрицы (для каждой диагонали), а затем перепишите
               его с учетом оптимизации работы с кэш-памятью.
 ============================================================================
 */

#define CPU_CYCLE_TIMING
//#define MICROSEC_TIMING

#define MATRIX_SIZE 10000

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

#ifdef CPU_CYCLE_TIMING
#include <x86intrin.h>
#endif

#ifdef MICROSEC_TIMING
#include <sys/time.h>
#endif


void init_matrix(int***); //выделяет место для матрици и заполняет случайными элементами
void print_matrix(int**); //печатает матрицу
void naiv_sum_matrix(int**, int, int**, int*); //производит наивное суммирование диагональных элементов
void sum_matrix(int**, int, int**, int*); //производит суммирование диагональных элементов

int main(void) {
    int** matrix = NULL;
    init_matrix(&matrix);
    //print_matrix(matrix);

    int *diag_sum = NULL;
    int diag_number = 0;
    int matrix_size = MATRIX_SIZE;


//Наивный способ
//===============================================================================//
#ifdef CPU_CYCLE_TIMING
    uint64_t time1, time2;
    time1 = __rdtsc();
#endif

#ifdef MICROSEC_TIMING
    uint64_t usec1;
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
#endif

    naiv_sum_matrix(matrix, matrix_size, &diag_sum, &diag_number); //вычисление
    printf("Наивный метот отработал\n");

#ifdef MICROSEC_TIMING
    gettimeofday(&tv2, NULL);
    usec1  = (tv2.tv_sec - tv1.tv_sec) * 1000000L +
            (tv2.tv_usec - tv1.tv_usec);
    printf("Execution time:\t%10lld microseconds\n\n", usec1);
#endif

#ifdef CPU_CYCLE_TIMING
    time2 = __rdtsc();
    printf("Execution time:\t%10lld cycles\n\n", time2 - time1);
#endif

    free (diag_sum);
//===============================================================================//




//Оптимизированный способ
//===============================================================================//
#ifdef CPU_CYCLE_TIMING
    uint64_t time3, time4;
    time3 = __rdtsc();
#endif

#ifdef MICROSEC_TIMING
    uint64_t usec2;
    struct timeval tv3, tv4;
    gettimeofday(&tv1, NULL);
#endif

    sum_matrix(matrix, matrix_size, &diag_sum, &diag_number);
    printf("Оптимизированный метод метот отработал\n");

#ifdef MICROSEC_TIMING
    gettimeofday(&tv4, NULL);
    usec2  = (tv4.tv_sec - tv3.tv_sec) * 1000000L +
            (tv4.tv_usec - tv3.tv_usec);
    printf("Execution time:\t%10lld microseconds\n\n", usec2);
#endif

#ifdef CPU_CYCLE_TIMING
    time4 = __rdtsc();
    printf("Execution time:\t%10lld cycles\n\n", time4 - time3);
#endif

    free (diag_sum);
//===============================================================================//

	return EXIT_SUCCESS;
}






void init_matrix(int*** matrix) {
    //Создание вектора векторов
    *matrix = (int**)malloc(MATRIX_SIZE * sizeof(int*));
    //Проверка
    if (*matrix == NULL) {
        printf("\tНе хватило места для выделения памяти!!");
        return;
    }
    for (size_t i = 0; i < MATRIX_SIZE; i++) {
            (*matrix)[i] = (int*)malloc(MATRIX_SIZE * sizeof(int));
            //проверка
            if ((*matrix)[i] == NULL) {
                printf("\tНе хватило места для выделения памяти!!");
                return;
            }
    }
    printf("\nВектор векторов создан успешно!\n\n");

    //Заполнение вектора векторов
    srand(time(0));
    for (size_t i = 0; i < MATRIX_SIZE; i++) {
         for (size_t j = 0; j < MATRIX_SIZE; j++) {
             (*matrix)[i][j] = rand() % 10;
         }
    }
}

void print_matrix(int** matrix) {
    printf("Сгенерирована матрица:\n\n");
    for (size_t i = 0; i < MATRIX_SIZE; i++) {
         printf("\t");
         for (size_t j = 0; j < MATRIX_SIZE; j++) {
             printf("%d ", matrix[i][j]);
         }
         printf("\n");
    }
}


void naiv_sum_matrix(int** matrix, int matrix_size, int** diag_sum, int* diag_number) {
    //проверка
    if (matrix == NULL) {
        printf("В функцию передан нулевой указатель");
        return;
    }
    for (size_t i = 0; i < matrix_size; ++i)
        if (matrix[i] == NULL) {
            printf("В функцию передан нулевой указатель");
            return;
        }
    if (diag_sum == NULL) {
        printf("В функцию передан нулевой указатель");
        return;
    }

    //Инициализация
    *diag_number = (2 * matrix_size - 1);
    *diag_sum = (int*)malloc(*diag_number * sizeof(int));
    for (size_t i = 0; i < *diag_number; ++i) {
        (*diag_sum)[i] = 0;
    }

    //суммирование наивным алгоритмом
    //суммирование от 0 до (diag_number / 2)
    for (size_t i = 1; i < *diag_number / 2 + 2; ++i) {
        size_t y = matrix_size - i;
        for (size_t x = 0; x < i; ++x, ++y) {
            (*diag_sum)[i - 1] += matrix[y][x];
        }
    }
    //суммирование остальных элементов
    for (size_t i = *diag_number / 2; i >= 1; --i) {
        size_t x = matrix_size - i;
        for (size_t y = 0; y < i; ++x, ++y) {
            (*diag_sum)[*diag_number - i] += matrix[y][x];
        }
    }
}

void sum_matrix(int** matrix, int matrix_size, int** diag_sum, int* diag_number) {
    //проверка
    if (matrix == NULL) {
        printf("В функцию передан нулевой указатель");
        return;
    }
    for (size_t i = 0; i < matrix_size; ++i)
        if (matrix[i] == NULL) {
            printf("В функцию передан нулевой указатель");
            return;
        }
    if (diag_sum == NULL) {
        printf("В функцию передан нулевой указатель");
        return;
    }

    //Инициализация
    *diag_number = (2 * matrix_size - 1);
    *diag_sum = (int*)malloc(*diag_number * sizeof(int));
    for (size_t i = 0; i < *diag_number; ++i) {
        (*diag_sum)[i] = 0;
    }

    //Суммирование
    int diag = *diag_number / 2 ;
    for (size_t row = 0; row < matrix_size; ++row) {
        int i = diag;
        for (size_t col = 0; col < matrix_size; ++col) {
            (*diag_sum)[i] += matrix[row][col];
            i++;
        }
        diag--;
    }
}














