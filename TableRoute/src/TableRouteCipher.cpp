/**
 * @file TableRouteCipher.cpp
 * @brief Реализация методов класса TableRouteCipher
 * 
 * Содержит реализацию алгоритма табличного маршрутного шифрования.
 */

#include "TableRouteCipher.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cctype>

/**
 * @brief Конструктор класса TableRouteCipher
 * @param key Ключ шифрования (количество столбцов)
 * @throw cipher_error Если ключ невалиден
 * 
 * Инициализирует объект шифра с заданным ключом.
 * Вызывает метод валидации ключа.
 */
TableRouteCipher::TableRouteCipher(int key)
{
    columns = getValidKey(key);
}

/**
 * @brief Шифрование текста методом табличного маршрутного преобразования
 * @param text Текст для шифрования
 * @return Зашифрованный текст
 * @throw cipher_error Если текст невалиден или слишком короткий
 * 
 * @details Алгоритм:
 * 1. Валидация и очистка текста
 * 2. Проверка, что длина текста больше ключа
 * 3. Создание таблицы и заполнение построчно
 * 4. Чтение таблицы по столбцам справа налево снизу вверх
 */
std::string TableRouteCipher::encrypt(const std::string& text)
{
    std::string validText = getValidText(text);
    
    // Проверка что текст БОЛЬШЕ ключа (количества столбцов)
    if (validText.length() <= columns) {
        throw cipher_error("Длина текста должна быть больше ключа (количества столбцов)");
    }
    
    size_t length = validText.length();
    size_t rows = (length + columns - 1) / columns;

    // Создаем таблицу и заполняем ее по строкам слева направо
    std::vector<std::vector<char>> table(rows, std::vector<char>(columns, ' '));
    size_t index = 0;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            if (index < length) {
                table[i][j] = validText[index++];
            }
        }
    }

    // Читаем по столбцам СНИЗУ ВВЕРХ, начиная с ПРАВОГО столбца
    std::string result;
    for (int j = columns - 1; j >= 0; j--) {
        for (int i = rows - 1; i >= 0; i--) {
            if (table[i][j] != ' ') {
                result += table[i][j];
            }
        }
    }
    
    return result;
}

/**
 * @brief Дешифрование текста, зашифрованного методом табличного маршрутного преобразования
 * @param text Зашифрованный текст
 * @return Расшифрованный текст
 * @throw cipher_error Если текст невалиден или слишком короткий
 * 
 * @details Алгоритм:
 * 1. Валидация и очистка текста
 * 2. Проверка, что длина текста больше ключа
 * 3. Создание таблицы и заполнение по столбцам справа налево снизу вверх
 * 4. Чтение таблицы построчно слева направо
 */
std::string TableRouteCipher::decrypt(const std::string& text)
{
    std::string validText = getValidText(text);
    
    // Проверка что текст БОЛЬШЕ ключа (количества столбцов)
    if (validText.length() <= columns) {
        throw cipher_error("Длина текста должна быть больше ключа (количества столбцов)");
    }
    
    size_t length = validText.length();
    size_t rows = (length + columns - 1) / columns;

    // Создаем таблицу для заполнения
    std::vector<std::vector<char>> table(rows, std::vector<char>(columns, ' '));
    
    // Определяем какие ячейки заполнены
    std::vector<std::vector<bool>> filled(rows, std::vector<bool>(columns, false));
    size_t total_filled = 0;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            if (total_filled < length) {
                filled[i][j] = true;
                total_filled++;
            }
        }
    }

    // Заполняем таблицу по столбцам справа налево СНИЗУ ВВЕРХ
    size_t text_index = 0;
    for (int j = columns - 1; j >= 0; j--) {
        for (int i = rows - 1; i >= 0; i--) {
            if (filled[i][j] && text_index < length) {
                table[i][j] = validText[text_index++];
            }
        }
    }

    // Читаем таблицу по строкам слева направо
    std::string result;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            if (filled[i][j]) {
                result += table[i][j];
            }
        }
    }
    
    return result;
}

/**
 * @brief Валидация ключа шифрования
 * @param key Входной ключ (количество столбцов)
 * @return Валидированный ключ типа size_t
 * @throw cipher_error Если ключ невалиден (key <= 0)
 * 
 * Проверяет, что ключ является положительным целым числом.
 */
size_t TableRouteCipher::getValidKey(int key)
{
    if (key <= 0) {
        throw cipher_error("Ключ должен быть положительным");
    }
    return static_cast<size_t>(key);
}

/**
 * @brief Валидация и очистка входного текста
 * @param text Входной текст для шифрования/дешифрования
 * @return Очищенный текст в верхнем регистре (только буквы)
 * @throw cipher_error Если текст пуст или не содержит букв
 * 
 * Удаляет все не-буквенные символы и преобразует текст в верхний регистр.
 */
std::string TableRouteCipher::getValidText(const std::string& text)
{
    if (text.empty()) {
        throw cipher_error("Текст пуст");
    }
    std::string result;
    for (char c : text) {
        if (isalpha(c)) {
            result += toupper(c);
        }
    }
    if (result.empty()) {
        throw cipher_error("Текст не содержит букв");
    }
    return result;
}
