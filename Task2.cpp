#include <iostream>

// Прототипы функций
void cont();
void menu(short number, short var);
int ifInt();

int main() {
    menu(2, 9); // Печать информации о задаче
    std::cout << "Инициализировать при объявлении статический двумерный массив"
<< "\nцелых чисел размером MxN. Найти максимальный среди элементов, лежащих выше побочной диагонали.\n";
    std::cout << "Введите размеры массива: ";
    int M = ifInt();
    int N = ifInt();
    int array[M][N];
    int max_value = 0;

    // Ввод элементов массива
    std::cout << "Введите элементы матрицы " << M << "x" << N << ":\n";
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            array[i][j] = ifInt();
        }
    }

    // Печать введенного массива
    std::cout << "Введенная матрица:\n";
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << array[i][j] << "\t";
        }
        std::cout << "\n";
    }

    // Поиск максимального элемента выше главной диагонали
    for (int i = 0; i < M; i++) {
        for (int j = i + 1; j < N; j++) { // Только элементы выше диагонали
            if (array[i][j] > max_value) {
                max_value = array[i][j];
            }
        }
    }

    // Печать результата
    std::cout << "\nМаксимальное число над главной диагональю - " << max_value << std::endl;
    
    // Запрос на продолжение
    cont();
    return 0;
}

// Функция для запроса продолжения работы программы
void cont() {
    std::cin.ignore(10000, '\n'); // Очищаем буфер перед вводом
    char choice;
    while (true) {
        std::cout << "Хотите продолжить? (Y/N): ";
        std::cin >> choice;
        
        if (choice == 'Y' || choice == 'y') {
            main(); // Рекурсивный запуск main
            break;
        } else if (choice == 'N' || choice == 'n') {
            std::cout << "Завершение программы." << std::endl;
            break;
        } else {
            std::cout << "Некорректный ввод. Введите 'Y' для продолжения или 'N' для завершения.\n";
            std::cin.ignore(10000, '\n'); // Очищаем буфер для следующего ввода
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
            std::cin.get(after); // Читаем пробел или \n
            return num;
        }
        std::cout << "Ошибка! Введите целое число: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}
