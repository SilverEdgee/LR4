#include <iostream>

// Прототипы функций
void cont();
void menu(short number, short var);
int ifInt();
void printArray(const int arr[], int size, const char *name);

int main() {
    menu(1, 9); // Печатаем информацию о задаче
    std::cout << "Ввести одномерный статический массив из k чисел. Сформировать два новых массива: в первый записать отрицательные" 
    << "\n элементы исходного массива, во второй - все остальные. \n";
    std::cout << "Введите количество чисел массива: ";
    int k = ifInt();
    int originalArray[k];
    std::cout << "Введите " << k << " чисел:" << std::endl;
    for (int i = 0; i < k; i++) {
        std::cout << "Элемент " << i + 1 << ": ";
        originalArray[i] = ifInt();
    }
    int negativeArray[k];
    int nonNegativeArray[k];
    int negCount = 0;
    int nonNegCount = 0;

    // Разделяем элементы на отрицательные и неотрицательные
    for (int i = 0; i < k; i++) {
        if (originalArray[i] < 0) {
            negativeArray[negCount++] = originalArray[i];
        } else {
            nonNegativeArray[nonNegCount++] = originalArray[i];
        }
    }

    printArray(originalArray, k, "Исходный массив");
    std::cout << "\nРезультат:" << std::endl;
    printArray(negativeArray, negCount, "Отрицательные элементы");
    printArray(nonNegativeArray, nonNegCount, "Неотрицательные элементы");
    cont(); // Спрашиваем, нужно ли продолжать
    return 0;
}

// Функция для запроса продолжения работы программы
void cont() {
    char choice;
    while (true) {
        std::cout << "Хотите продолжить? (Y/N): ";
        std::cin >> choice;

        if (choice == 'Y' || choice == 'y') {
            main();
            break;
        } else if (choice == 'N' || choice == 'n') {
            std::cout << "Завершение программы." << std::endl;
            break;
        } else {
            std::cout << "Некорректный ввод. Пожалуйста, введите 'Y' для продолжения или 'N' для завершения.\n";
            std::cin.ignore(10000, '\n');
        }
    }
}

// Функция для отображения меню
void menu(short number, short var) {
    std::cout << "Task " << number << " by Denis Pometko\n";
    for (int i = 0; i < 20; i++) std::cout << "x";
    std::cout << "\n";

    if (var != -1) {
        std::cout << "Variant " << var << std::endl;
        for (int i = 0; i < 20; i++) std::cout << "x";
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

// Функция для печати массива с именем
void printArray(const int arr[], int size, const char * name) {
    std::cout << name << ": ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
