#ifndef FOUR_H
#define FOUR_H

#include <string>
#include <initializer_list>

class Four {
private:
    size_t _size;
    unsigned char* _data;

    bool isValidDigit(unsigned char digit) const;
    unsigned char charToDigit(char c) const;
    char digitToChar(unsigned char digit) const;
    void validateNumber() const;

public:
    // Конструкторы
    Four();
    Four(const size_t& n, unsigned char t = 0);
    Four(const std::initializer_list<unsigned char>& t);
    Four(const std::string& t);
    Four(const Four& other);
    Four(Four&& other) noexcept;
    
    // Деструктор
    virtual ~Four() noexcept;
    
    // Арифметические операции
    Four add(const Four& other) const;
    Four subtract(const Four& other) const;
    
    // Операции сравнения
    bool equals(const Four& other) const;
    bool greaterThan(const Four& other) const;
    bool lessThan(const Four& other) const;
    
    // Вспомогательные методы
    std::string toString() const;
};

#endif