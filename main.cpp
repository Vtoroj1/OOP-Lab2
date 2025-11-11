#include <iostream>
#include "four.h"

int main() {
    try {
        std::cout << "=== Тестирование конструкторов ===" << std::endl;
        
        Four num1;
        std::cout << "Конструктор по умолчанию: " << num1.toString() << std::endl;
        
        Four num2(3, 2);
        std::cout << "Заполняющий конструктор (3, 2): " << num2.toString() << std::endl;
        
        Four num3{1, 2, 0};
        std::cout << "Конструктор из initializer_list {1,2,0}: " << num3.toString() << std::endl;
        
        Four num4("210");
        std::cout << "Конструктор из строки \"210\": " << num4.toString() << std::endl;
        
        Four num5 = num3;
        std::cout << "Конструктор копирования (копия num3): " << num5.toString() << std::endl;

        std::cout << "\n=== Сравнение объектов ===" << std::endl;
        
        if (num3.equals(num5)) {
            std::cout << "num3 равно num5" << std::endl;
        } else {
            std::cout << "num3 не равно num5" << std::endl;
        }
        
        if (num2.equals(num4)) {
            std::cout << "num2 равно num4" << std::endl;
        } else {
            std::cout << "num2 не равно num4" << std::endl;
        }
        
        Four larger("321");
        Four smaller("123");
        if (larger.greaterThan(smaller)) {
            std::cout << larger.toString() << " больше " << smaller.toString() << std::endl;
        }
        
        if (smaller.lessThan(larger)) {
            std::cout << smaller.toString() << " меньше " << larger.toString() << std::endl;
        }
        
        Four long_num("1000");
        Four short_num("333");
        if (long_num.greaterThan(short_num)) {
            std::cout << long_num.toString() << " больше " << short_num.toString() << " (разная длина)" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\n=== Программа завершена успешно ===" << std::endl;
    return 0;
}