#include "four.h"
#include <stdexcept>
#include <algorithm>
#include <cstring>

bool Four::isValidDigit(unsigned char digit) const {
    return digit >= 0 && digit <= 3;
}

unsigned char Four::charToDigit(char c) const {
    if (c >= '0' && c <= '3') {
        return static_cast<unsigned char>(c - '0');
    }
    throw std::invalid_argument("Некорректная цифра для четвертичного числа");
}

char Four::digitToChar(unsigned char digit) const {
    if (digit <= 3) {
        return static_cast<char>('0' + digit);
    }
    throw std::invalid_argument("Некорректная цифра для четвертичного числа");
}

Four::Four() : _size(1) {
    _data = new unsigned char[1];
    _data[0] = 0;
}

Four::Four(const size_t& n, unsigned char t) : _size(n) {
    if (!isValidDigit(t)) {
        throw std::invalid_argument("Некорректная цифра для четвертичного числа");
    }
    if (n == 0) {
        _data = nullptr;
        return;
    }
    _data = new unsigned char[n];
    std::fill(_data, _data + n, t);
    validateNumber();
}

Four::Four(const std::initializer_list<unsigned char>& t) : _size(t.size()) {
    if (_size == 0) {
        _data = nullptr;
        return;
    }
    _data = new unsigned char[_size];
    
    size_t i = 0;
    for (auto it = t.end(); it != t.begin(); ) {
        --it;
        if (!isValidDigit(*it)) {
            delete[] _data;
            throw std::invalid_argument("Некорректная цифра для четвертичного числа");
        }
        _data[i++] = *it;
    }
    validateNumber();
}

Four::Four(const std::string& t) : _size(t.length()) {
    if (_size == 0) {
        _data = nullptr;
        return;
    }
    _data = new unsigned char[_size];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = charToDigit(t[_size - 1 - i]);
    }
    validateNumber();
}

Four::Four(const Four& other) : _size(other._size) {
    if (_size == 0) {
        _data = nullptr;
        return;
    }
    _data = new unsigned char[_size];
    std::copy(other._data, other._data + _size, _data);
}

Four::Four(Four&& other) noexcept : _size(other._size), _data(other._data) {
    other._size = 0;
    other._data = nullptr;
}

Four::~Four() noexcept {
    delete[] _data;
}

Four Four::add(const Four& other) const {
    size_t maxSize = std::max(_size, other._size);
    Four result(maxSize + 1, 0);
    unsigned char carry = 0;
    for (size_t i = 0; i < maxSize || carry; ++i) {
        unsigned char sum = carry;
        if (i < _size) {
            sum += _data[i];
        }
        
        if (i < other._size) {
            sum += other._data[i];
        }
        
        carry = sum / 4;
        result._data[i] = sum % 4;
    }
    
    result.removeLeadingZeros();
    result.validateNumber();
    return result;
}

Four Four::subtract(const Four& other) const {
    if (this->lessThan(other)) {
        throw std::invalid_argument("Нельзя вычесть из большего числа");
    }
    
    size_t maxSize = std::max(_size, other._size);
    Four result(maxSize, 0);
    int borrow = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        int digit = -borrow;
        if (_size > i) {
            digit += _data[i];
        }

        if (other._size > i) {
            digit -= other._data[i];
        }
        
        if (digit < 0) {
            borrow = 1;
            digit += 4;
        } else {
            borrow = 0;
        }
        
        result._data[i] = static_cast<unsigned char>(digit);
    }
    
    if (borrow != 0) {
        throw std::invalid_argument("Нельзя вычесть из большего числа");
    }
    
    result.removeLeadingZeros();
    result.validateNumber();
    return result;
}

bool Four::equals(const Four& other) const {
    if (_size != other._size){
        return false;
    }
    return std::equal(_data, _data + _size, other._data);
}

bool Four::greaterThan(const Four& other) const {
    if (_size != other._size) {
        return _size > other._size;
    }
    for (size_t i = _size; i > 0; --i) {
        if (_data[i - 1] != other._data[i - 1]) {
            return _data[i - 1] > other._data[i - 1];
        }
    }
    return false;
}

bool Four::lessThan(const Four& other) const {
    if (_size != other._size) {
        return _size < other._size;
    }
    for (size_t i = _size; i > 0; --i) {
        if (_data[i - 1] != other._data[i - 1]) {
            return _data[i - 1] < other._data[i - 1];
        }
    }
    return false;
}

std::string Four::toString() const {
    if (_size == 0) {
        return "0";
    }
    
    std::string result;
    for (size_t i = _size; i > 0; --i) {
        result += digitToChar(_data[i - 1]);
    }
    return result;
}

void Four::resize(size_t newSize) {
    if (newSize == _size) return;
    
    unsigned char* newData = new unsigned char[newSize]();
    if (_data) {
        size_t copySize = std::min(_size, newSize);
        std::copy(_data, _data + copySize, newData);
        delete[] _data;
    }
    _data = newData;
    _size = newSize;
}

void Four::removeLeadingZeros() {
    size_t leadingZeros = 0;
    while (leadingZeros < _size && _data[_size - 1 - leadingZeros] == 0) {
        ++leadingZeros;
    }
    
    if (leadingZeros == _size) {
        resize(1);
        _data[0] = 0;
    } else if (leadingZeros > 0) {
        size_t newSize = _size - leadingZeros;
        unsigned char* newData = new unsigned char[newSize];
        std::copy(_data, _data + _size - leadingZeros, newData);
        delete[] _data;
        _data = newData;
        _size = newSize;
    }
}

void Four::validateNumber() const {
    for (size_t i = 0; i < _size; ++i) {
        if (!isValidDigit(_data[i])) {
            throw std::invalid_argument("Некорректная цифра для четвертичного числа");
        }
    }
}