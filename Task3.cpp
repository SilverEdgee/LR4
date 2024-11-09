#include <iostream>

// Прототипы вспомогательных функций
void menu(short number, short var);
int ifInt();
void cont();

int main() {
    // Отображаем информацию о задаче
    menu(3, 9);
    std::cout << "Память для массива выделить динамически. Определить, является ли заданная матрица N-го порядка магическим"
 << "\nквадратом, т.е. такой матрицей, в которой сумма элементов во всех строках и столбцах одинакова.\n";
    std::cout << "Введите порядок матрицы: ";
    bool is_square = true;
    int rows = ifInt();       // Количество строк
    if(rows == 2) {
        std::cout << "Не существует магического квадрата 2-ого порядка";
        return 0;
    } 
    int columns = rows;  // Количество столбцов
    int sum = 0;             // Сумма элементов первой строки
    int** arr = new int*[rows]; // Выделение памяти под массив указателей

    // Выделение памяти под двухмерный массив
    for (int i = 0; i < rows; i++) {
        arr[i] = new int[columns];
    }

    // Ввод элементов массива
    std::cout << "Введите элементы матрицы " << rows << "x" << columns << ":\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            arr[i][j] = ifInt();
        }
    }

    // Печать введенного массива
    std::cout << "Введенная матрица:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << arr[i][j] << "\t";
        }
        std::cout << "\n";
    }

    // Рассчитываем сумму первой строки
    for (int j = 0; j < columns; j++) {
        sum += arr[0][j];
    }

    // Проверка сумм строк
    for (int i = 1; i < rows && is_square; i++) {
        int row_sum = 0;
        for (int j = 0; j < columns; j++) {
            row_sum += arr[i][j];
        }
        if (row_sum != sum) {
            is_square = false;
            break;
        }
    }

    // Проверка сумм столбцов
    for (int j = 0; j < columns && is_square; j++) {
        int column_sum = 0;
        for (int i = 0; i < rows; i++) {
            column_sum += arr[i][j];
        }
        if (column_sum != sum) {
            is_square = false;
            break;
        }
    }

    // Вывод результата
    if (is_square) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    // Освобождение памяти
    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;

    // Запрос на продолжение
    cont();
}

// Функция для запроса продолжения работы программы
void cont() {
    char choice;
    while (true) {
        std::cout << "Хотите продолжить? (Y/N): ";
        std::cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            main(); // Повторный запуск main для продолжения
            break;
        } else if (choice == 'N' || choice == 'n') {
            std::cout << "Завершение программы." << std::endl;
            break;
        } else {
            std::cout << "Некорректный ввод. Введите 'Y' для продолжения или 'N' для завершения.\n";
            std::cin.ignore(10000, '\n');
        }
    }
}

// Функция для отображения информации о задаче и варианте
void menu(short number, short var) {
    std::cout << "Task " << number << " made by Denis Pometko\n";
    for (int i = 0; i < 20; i++) {
        std::cout << "x";
    }
    std::cout << "\n";
    if (var != -1) {
        std::cout << "Variant " << var << std::endl;
        for (int i = 0; i < 20; i++) {
            std::cout << "x";
        }
        std::cout << "\n";
        std::cout << "Problem: ";
    }
}

// Функция для безопасного ввода целого числа
int ifInt() {
    int num;
    char after;
    while (true) {
        if (std::cin >> num && ((after = std::cin.peek()) == ' ' || after == '\n')) {
            std::cin.get(after);
            return num;
        }
        std::cout << "Ошибка! Введите целое число: ";
        std::cin.clear();
    }
}
