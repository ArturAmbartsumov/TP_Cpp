/*
 ============================================================================
 Name        : HomeTask4V13.c
 Author      : Artur Ambartsumov
 Version     : 1.1
 Copyright   : Your copyright notice
 Description : Создать структуру для хранения расписания электропоездов:
               времени отправления с начальной станции и списка остановок с
               указанием времени прибытия/отправления. Составить с ее
               использованием программу поиска ближайшего электропоезда до
               заданной остановки.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct myTime {
    int hour;
    int min;
    int sec;
};
void read_time(struct myTime *);
void print_time(struct myTime);


struct station {
    char station_name[21];
    struct myTime arrival_time;
};
void read_station(struct station *);
void print_station(struct station);


struct train {
    char route_name[21];
    int stations_number;
    struct station departure_station;
    struct station *stations_arr;
};
void read_train(struct train *);
void print_train(struct train);


//Функция ищет, когда через заданную станцию проедет поезд и выводит информацию на экран
//Если такой станции не существует, то выводится ошибка
void next_station(const struct train* const, const char* const);


int main(void) {
    struct train tr = {};
    read_train(&tr);
    printf("\n===========================================================================\n");
    print_train(tr);
    printf("\n===========================================================================\n");
    printf("Введите название станции, для которой\nнеобходимо найти ближайший поезд: ");
    char required_station[20];
    char c[300] = "";
    gets(c);
    strncat(required_station, c, 20);
    //scanf("%s", &required_station);
    next_station(&tr, required_station);

    //Освобождение памяти
    free(tr.stations_arr);

	return EXIT_SUCCESS;
}


void read_time(struct myTime *t) {
    if (t == NULL) {
        printf("\n\n!!!В функцию был передан нулевой указатель!!!\n\n");
        return;
    }
    printf("Введите время прибытия/отпревления (в формате 24 60 60): ");
    scanf("%d%d%d", &t->hour, &t->min, &t->sec);
    char str[5];
    gets(str);
}


void print_time(struct myTime t) {
    printf("%02d:%02d:%02d\n", t.hour, t.min, t.sec);
}


void read_station(struct station *s) {
    if (s == NULL) {
        printf("\n\n!!!В функцию был передан нулевой указатель!!!\n\n");
        return;
    }

    printf("Введите название станции (не более 20 символов): ");
    //scanf("%s", &s->station_name);
    char str[300] = "";
    gets(str);
    s->station_name[0] = '\0';
    strncat(s->station_name, str, 20);
    printf("\t");

    read_time(&s->arrival_time);
    printf("\n");
}


void print_station(struct station s) {
    printf("%s\t", s.station_name);
    print_time(s.arrival_time);
    printf("\n");
}


void read_train(struct train *tr) {
    //проверка на нулевой указатель
    if (tr == NULL) {
        printf("\n\n!!!В функцию был передан нулевой указатель!!!\n\n");
        return;
    }

    //ввод названия маршрута
    printf("Введите название маршрута электропоезда: ");
    //scanf("%s", &tr->route_name);
    char str1[300] = "";
    gets(str1);
    tr->route_name[0] = '\0';
    strncat(tr->route_name, str1, 20);

    //ввод числа остановок с проверкой корректности ввода
    while (1) {
        printf("Введите число остановок: ");
        scanf("%d", &tr->stations_number);
        gets(str1);
        if (tr->stations_number >= 1) break;
        else printf("!!!Некорректный ввод значения!!!\n");
    }

    //выделение памяти для массива станций
    tr->stations_arr = (struct station*)malloc(tr->stations_number * sizeof(struct station));
    if (tr->stations_arr == NULL) {
        printf("\n\n!!!Ошибка выделения памяти!!!\n\n");
        return;
    }

    //ввод станции отправления
    printf("\nВведите станцию отправления:\n\t");
    read_station(&tr->departure_station);

    //вводи информации об остановках
    printf("Введите остановки: \n");
    for (size_t i = 0; i < tr->stations_number; ++i) {
        printf("\t");
        read_station(&tr->stations_arr[i]);
    }
}


void print_train(struct train tr) {
    //проверка содержимого
    if ((tr.stations_arr == NULL) || (tr.stations_number < 1)) {
        printf("В функцию print_train передана структура train с некорректными данными");
        return;
    }

    //печать данных
    printf("\nЭлектропоезд %s\n", tr.route_name);
    printf("\nОтправление: ");
    print_station(tr.departure_station);
    printf("Остановки: \n\n");
    for (size_t i = 0; i < tr.stations_number; ++i) {
        print_station(tr.stations_arr[i]);
    }
}


void next_station(const struct train* const tr, const char* const required_station) {
    //проверка содержимого
    if ((tr->stations_arr == NULL) || (tr->stations_number < 1)) {
        printf("В функцию print_train передана структура train с некорректными данными");
        return;
    }

    int flag = 0;
    for (size_t i = 0; i < tr->stations_number; ++i) {
        //if (tr->stations_arr[i].station_name == required_station) {
        if (strcmp(tr->stations_arr[i].station_name, required_station) == 0) {
            flag = 1;
            printf("\n\nБлижайший поезд на станцию \"%s\" прибывает в ", required_station);
            print_time(tr->stations_arr[i].arrival_time);
            i = tr->stations_number;
        }
    }
    if (flag == 0) printf("\n\n!!!Ошибка: Через станцию \"%s\" не проходит ни один поезд!!!", required_station);
}
