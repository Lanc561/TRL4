/**
 * @file TableRouteCipher.h
 * @brief Заголовочный файл класса TableRouteCipher для табличного маршрутного шифрования
 * 
 * Содержит объявление класса TableRouteCipher и класса исключений cipher_error.
 * Реализует алгоритм шифрования на основе табличного маршрутного преобразования.
 */

#pragma once
#include <string>
#include <vector>
#include <stdexcept>

/**
 * @class cipher_error
 * @brief Класс исключений для обработки ошибок шифрования
 * 
 * Наследуется от std::invalid_argument. Используется для передачи
 * информации об ошибках, возникающих при шифровании или дешифровании.
 */
class cipher_error : public std::invalid_argument {
public:
    /**
     * @brief Конструктор с std::string
     * @param what_arg Сообщение об ошибке
     */
    explicit cipher_error(const std::string& what_arg) : 
        std::invalid_argument(what_arg) {}
    
    /**
     * @brief Конструктор с const char*
     * @param what_arg Сообщение об ошибке
     */
    explicit cipher_error(const char* what_arg) : 
        std::invalid_argument(what_arg) {}
};

/**
 * @class TableRouteCipher
 * @brief Основной класс для табличного маршрутного шифрования
 * 
 * Реализует алгоритм шифрования на основе табличного маршрутного преобразования.
 * Текст записывается в таблицу построчно, а считывается по столбцам
 * справа налево снизу вверх.
 * 
 * @note Длина текста должна быть БОЛЬШЕ ключа (количества столбцов)
 */
class TableRouteCipher
{
private:
    size_t columns; ///< Количество столбцов в таблице (ключ шифрования)
    
    /**
     * @brief Валидация ключа шифрования
     * @param key Входной ключ (количество столбцов)
     * @return Валидированный ключ типа size_t
     * @throw cipher_error Если ключ невалиден (key <= 0)
     */
    size_t getValidKey(int key);
    
    /**
     * @brief Валидация и очистка входного текста
     * @param text Входной текст для шифрования/дешифрования
     * @return Очищенный текст в верхнем регистре (только буквы)
     * @throw cipher_error Если текст пуст или не содержит букв
     */
    std::string getValidText(const std::string& text);
    
public:
    TableRouteCipher() = delete; ///< Удаленный конструктор по умолчанию
    
    /**
     * @brief Конструктор с параметром
     * @param key Ключ шифрования (количество столбцов в таблице)
     * @throw cipher_error Если ключ невалиден
     */
    TableRouteCipher(int key);
    
    /**
     * @brief Шифрование текста методом табличного маршрутного преобразования
     * @param text Текст для шифрования
     * @return Зашифрованный текст
     * @throw cipher_error Если текст невалиден или слишком короткий
     * 
     * @details Алгоритм шифрования:
     * 1. Текст записывается в таблицу построчно (слева направо)
     * 2. Таблица считывается по столбцам справа налево снизу вверх
     * 3. Результат объединяется в зашифрованную строку
     */
    std::string encrypt(const std::string& text);
    
    /**
     * @brief Дешифрование текста, зашифрованного методом табличного маршрутного преобразования
     * @param text Зашифрованный текст
     * @return Расшифрованный текст
     * @throw cipher_error Если текст невалиден или слишком короткий
     * 
     * @details Алгоритм дешифрования:
     * 1. Зашифрованный текст записывается в таблицу по столбцам справа налево снизу вверх
     * 2. Таблица считывается построчно (слева направо)
     * 3. Результат объединяется в расшифрованную строку
     */
    std::string decrypt(const std::string& text);
};
