#include <stdlib.h>
#include <stdio.h>

void menu(short number, short var);
int ifInt();
void cont();
int** oddMagicSquare(int n);
int** singlyEvenMagicSquare(int n);
int** doublyEvenMagicSquare(int n);
void printMagicSquare(int** square, int n);

// Главная функция
int main() {
    menu(6, -1);
    printf("Построить магический квадрат. Порядок квадрата задаётся пользователем. \nМаксимальный размер магического квадрата не превышает 2^32 - 1.\n");
    int n ;
    printf("Введите порядок магического квадрата: ");
    scanf("%d", &n);
    if(n == 2) {
        printf("Не существует магического квадрата 2-ого порядка");
        return 0;
    }    
    int** magicSquare = NULL;
    if (n % 2 != 0) {
        printf("Создание магического квадрата нечетного порядка %d:\n", n);
        magicSquare = oddMagicSquare(n);
    } else if (n % 4 == 0) {
        printf("Создание магического квадрата порядка %d (четное и кратное четырем):\n", n);
        magicSquare = doublyEvenMagicSquare(n);
    } else {
        printf("Создание магического квадрата порядка %d (простое четное):\n", n);
        magicSquare = singlyEvenMagicSquare(n);
    }

    printMagicSquare(magicSquare, n);

    // Освобождаем память
    for (int i = 0; i < n; i++) {
        free(magicSquare[i]);
    }
    free(magicSquare);

    return 0;
    cont();
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

// Функция для создания магического квадрата нечетного порядка
int** oddMagicSquare(int n) {
    int value = 0;
    int squareSize = n * n;
    int c = n / 2, r = 0, i;

    int** result = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++)
        result[i] = (int*)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = 0;

    while (++value <= squareSize) {
        result[r][c] = value;
        if (r == 0) {
            if (c == n - 1) {
                r++;
            } else {
                r = n - 1;
                c++;
            }
        } else if (c == n - 1) {
            r--;
            c = 0;
        } else if (result[r - 1][c + 1] == 0) {
            r--;
            c++;
        } else {
            r++;
        }
    }
    return result;
}

// Функция для создания магического квадрата порядка 4n + 2 (простое четное)
int** singlyEvenMagicSquare(int n) {
    int size = n * n;
    int halfN = n / 2;
    int subGridSize = size / 4;

    int** subGrid = oddMagicSquare(halfN);
    int gridFactors[] = {0, 2, 3, 1};

    int** result = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        result[i] = (int*)malloc(n * sizeof(int));

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            int grid = (r / halfN) * 2 + (c / halfN);
            result[r][c] = subGrid[r % halfN][c % halfN];
            result[r][c] += gridFactors[grid] * subGridSize;
        }
    }

    int nColsLeft = halfN / 2;
    int nColsRight = nColsLeft - 1;

    for (int r = 0; r < halfN; r++)
        for (int c = 0; c < n; c++) {
            if (c < nColsLeft || c >= n - nColsRight
                    || (c == nColsLeft && r == nColsLeft)) {

                if (c == 0 && r == nColsLeft)
                    continue;

                int tmp = result[r][c];
                result[r][c] = result[r + halfN][c];
                result[r + halfN][c] = tmp;
            }
        }

    for (int i = 0; i < halfN; i++)
        free(subGrid[i]);
    free(subGrid);

    return result;
}

// Функция для создания магического квадрата порядка 4n (двойное четное)
int** doublyEvenMagicSquare(int n) {
    int** result = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        result[i] = (int*)malloc(n * sizeof(int));

    int num = 1;
    int inverse = n * n + 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = num++;
        }
    }

    for (int i = 0; i < n; i++) {
        result[i][i] = inverse - result[i][i];
        result[i][n - i - 1] = inverse - result[i][n - i - 1];
    }
    return result;
}

// Функция для вывода магического квадрата
void printMagicSquare(int** square, int n) {
    if (square == NULL) {
        printf("Ошибка при создании магического квадрата.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d ", square[i][j]);
        }
        printf("\n");
    }

    printf("\nМагическая сумма: %d\n", (n * n + 1) * n / 2);
}