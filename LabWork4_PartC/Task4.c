#include <stdlib.h>
#include <stdio.h>

// Прототипы функций
void menu(short number, short var);
int ifInt();
void cont();
int*** allocate3DArray(int Z, int Y, int X);
void free3DArray(int*** array, int Z, int Y);
void input3DArray(int*** array, int Z, int Y, int X);
void print3DArray(int*** array, int Z, int Y, int X);
int calculateMaxDiagonalSum(int*** array, int Z);

// Главная функция
int main() {
    // Отображаем информацию о задаче
    menu(4, -1);
    printf("Дан трёхмерный динамический массив размером n^3 целых неотрицательных чисел. \n");
    printf("Необходимо определить диагональ с наибольшей суммой чисел. \nДля обхода диагоналей нельзя использовать вложенные циклы. \n");
    int Z, Y, X;
    printf("Введите размеры трехмерной матрицы: ");
    scanf("%i %i %i", &Z, &Y, &X);
    int*** array = allocate3DArray(Z, Y, X);
    
    input3DArray(array, Z, Y, X);
    print3DArray(array, Z, Y, X);
    
    calculateMaxDiagonalSum(array, Z);
    
    free3DArray(array, Z, Y);
    cont();

    return 0;
}

// Функция для отображения информации о задаче и варианте
void menu(short number, short var) {
    printf("Task %d made by Denis Pometko\n", number);
    for (int i = 0; i < 20; i++) {
        printf("x");
    }
    printf("\n");
    if (var != -1) {
        printf("Variant %d\n", var);
        for (int i = 0; i < 20; i++) {
            printf("x");
        }
        printf("\n");
        printf("Problem: \n");
    }
}

// Функция для безопасного ввода целого числа
int ifInt() {
    int num;
    char after;
    while (1) {
        if (scanf("%d%c", &num, &after) == 2 && (after == ' ' || after == '\n')) {
            return num;
        }
        printf("Ошибка! Введите целое число: ");
        while (getchar() != '\n'); // Очистка ввода
    }
}

// Функция для запроса продолжения работы программы
void cont() {
    char choice;
    while (1) {
        printf("Хотите продолжить? (Y/N): ");
        scanf(" %c", &choice);
        while (getchar() != '\n');
        if (choice == 'Y' || choice == 'y') {
            main(); // Повторный запуск main для продолжения
            break;
        } else if (choice == 'N' || choice == 'n') {
            printf("Завершение программы.\n");
            break;
        } else {
            printf("Некорректный ввод. Введите 'Y' для продолжения или 'N' для завершения.\n");
            cont();
    }
}
}

// Определение функции для выделения памяти для трехмерного массива
int*** allocate3DArray(int Z, int Y, int X) {
    int*** array = (int ***) malloc(Z * sizeof(int**));
    for (int i = 0; i < Z; i++) {
        array[i] = (int **) malloc(Y * sizeof(int*));
        for (int j = 0; j < Y; j++) {
            array[i][j] = (int *) malloc(X * sizeof(int));
        }
    }
    return array;
}

// Определение функции для освобождения памяти трехмерного массива
void free3DArray(int*** array, int Z, int Y) {
    for (int i = 0; i < Z; i++) {
        for (int j = 0; j < Y; j++) {
            free(array[i][j]);
        }
        free(array[i]);
    }
    free(array);
}

// Определение функции для ввода значений в массив
void input3DArray(int*** array, int Z, int Y, int X) {
    printf("Введите элементы массива размером %d x %d x %d:\n", Z, Y, X);
    for (int i = 0; i < Z; i++) {
        for (int j = 0; j < Y; j++) {
            for (int k = 0; k < X; k++) {
                array[i][j][k] = ifInt(); // Используем безопасный ввод
            }
        }
    }
}

// Определение функции для вывода значений массива
void print3DArray(int*** array, int Z, int Y, int X) {
    printf("Вы ввели массив:\n");
    for (int i = 0; i < Z; i++) {
        printf("Слой %d:\n", i + 1);
        for (int j = 0; j < Y; j++) {
            for (int k = 0; k < X; k++) {
                printf("%d ", array[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

// Определение функции для вычисления и вывода максимальной суммы по диагоналям
int calculateMaxDiagonalSum(int*** array, int Z) {
    int d1 = 0, d2 = 0, d3 = 0, d4 = 0;

    for (int i = 0; i < Z; i++) {
        d1 += array[i][i][i];              // Главная диагональ (0,0,0) -> (Z-1,Z-1,Z-1)
        d2 += array[i][i][Z - 1 - i];      // Диагональ (0,0,Z-1) -> (Z-1,Z-1,0)
        d3 += array[i][Z - i - 1][i];      // Диагональ (0,Z-1,0) -> (Z-1,0,Z-1)
        d4 += array[i][Z - 1 - i][Z - 1 - i]; // Диагональ (0,Z-1,Z-1) -> (Z-1,0,0)
    }

    int max_sum = d1;
    if (d2 > max_sum) max_sum = d2;
    if (d3 > max_sum) max_sum = d3;
    if (d4 > max_sum) max_sum = d4;

    printf("Суммы по диагоналям: d1 = %d, d2 = %d, d3 = %d, d4 = %d\n", d1, d2, d3, d4);
    printf("Максимальная сумма диагонали: %d\n", max_sum);

    return max_sum;
}
