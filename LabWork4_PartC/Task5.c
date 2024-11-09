#include <stdlib.h>
#include <stdio.h>

// Прототипы функций
void menu(short number, short var);
int ifInt();
void cont();
char** allocateCharArray(int rows, int columns);
void freeCharArray(char** array, int rows);
void inputCharArray(char** array, int rows, int columns);
void printCharArray(char** array, int rows, int columns);
void calculateMines(char** array, int rows, int columns);

//Основая функция
int main() {
    menu(5, -1);
    printf("На вход подаётся поле для игры в ""сапёр"" размером n*m символов, где символ '.' означает пустое место, а символ '*' - бомбу.\n"); 
    printf("Требуется дополнить это поле числами, как в оригинальной игре.\n");
    printf("Введите размеры поля: ");
    int rows,columns;
    scanf("%i %i", &rows, &columns);
    
    char** array = allocateCharArray(rows, columns);
    
    printf("Введите элементы массива %d x %d (используйте '.' для пустых ячеек и '*' для мин):\n", rows, columns);
    inputCharArray(array, rows, columns);

    printf("\nИсходный массив:\n");
    printCharArray(array, rows, columns);

    calculateMines(array, rows, columns);

    printf("\nМассив с количеством соседних мин:\n");
    printCharArray(array, rows, columns);

    freeCharArray(array, rows);
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

// Функция для выделения памяти под двумерный массив символов
char** allocateCharArray(int rows, int columns) {
    char** array = (char **) malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        array[i] = (char*) malloc(columns * sizeof(char));
    }
    return array;
}

// Функция для освобождения памяти двумерного массива
void freeCharArray(char** array, int rows) {
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

// Функция для ввода значений в массив
void inputCharArray(char** array, int rows, int columns) {
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            scanf(" %c", &array[i][j]);
        }
    }
}

// Функция для вывода массива
void printCharArray(char** array, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c ", array[i][j]);
        }
        printf("\n");
    }
}

// Функция для подсчета мин вокруг каждой ячейки и обновления массива
void calculateMines(char** array, int rows, int columns) {
    int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1}; // Смещения по горизонтали
    int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1}; // Смещения по вертикали

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (array[i][j] == '.') {
                int count = 0;
                
                // Проверка соседних ячеек
                for (int k = 0; k < 8; k++) {
                    int newX = j + dx[k];
                    int newY = i + dy[k];

                    // Условие: новая ячейка должна быть внутри границ массива и содержать мину '*'
                    if (newX >= 0 && newX < columns && newY >= 0 && newY < rows && array[newY][newX] == '*') {
                        count++;
                    }
                }

                // Обновляем ячейку, если рядом есть мины
                if (count != 0) {
                    array[i][j] = count + '0';
                }
            }
        }
    }
}
