/**
 * @file modAlphaCipher.h
 * @brief Заголовочный файл для класса модифицированного алфавитного шифра
 * @author Генералов Л.К.
 * @version 1.0
 * @copyright ИБСТ ПГУ
 * @date 2025
 * 
 * @details
 * Реализация модифицированного шифра на основе алфавита с поддержкой
 * русского языка. Шифр использует ключ для сдвига символов в алфавите.
 */

#pragma once
#include <map>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#include <stdexcept>

/**
 * @class cipher_error
 * @brief Класс исключения для ошибок шифрования
 * 
 * Наследуется от std::invalid_argument. Используется для обработки
 * ошибок, связанных с валидацией ключа, текста и операциями шифрования.
 */
class cipher_error : public std::invalid_argument {
public:
    /**
     * @brief Конструктор с строковым параметром
     * @param what_arg Сообщение об ошибке
     */
    explicit cipher_error(const std::string& what_arg) : 
        std::invalid_argument(what_arg) {}
    
    /**
     * @brief Конструктор с C-строкой
     * @param what_arg Сообщение об ошибке
     */
    explicit cipher_error(const char* what_arg) : 
        std::invalid_argument(what_arg) {}
};

/**
 * @class modAlphaCipher
 * @brief Класс для шифрования и дешифрования текста
 * 
 * Класс реализует модифицированный алфавитный шифр с поддержкой
 * русского алфавита. Шифрование происходит путем сдвига символов
 * на основе ключа.
 */
class modAlphaCipher
{
private:
    /// Русский алфавит в верхнем регистре (33 буквы)
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    
    /// Отображение символов в числовые индексы
    std::map<wchar_t, int> alphaNum;
    
    /// Ключ шифрования в числовом представлении
    std::vector<int> key;
    
    /**
     * @brief Преобразует строку в вектор числовых индексов
     * @param s Входная строка
     * @return Вектор индексов символов в алфавите
     */
    std::vector<int> convert(const std::wstring& s);
    
    /**
     * @brief Преобразует вектор числовых индексов в строку
     * @param v Вектор индексов
     * @return Строка символов
     */
    std::wstring convert(const std::vector<int>& v);
    
    // Вспомогательные методы для проверки символов
    bool isValidChar(wchar_t c);
    bool isUpperChar(wchar_t c);
    wchar_t toUpperChar(wchar_t c);
    
    /**
     * @brief Валидирует ключ шифрования
     * @param s Входной ключ
     * @return Валидный ключ в верхнем регистре
     * @throw cipher_error если ключ пустой или содержит недопустимые символы
     */
    inline std::wstring getValidKey(const std::wstring& s);
    
    /**
     * @brief Валидирует открытый текст
     * @param s Входной текст
     * @return Валидный текст в верхнем регистре
     * @throw cipher_error если текст пустой после фильтрации
     */
    inline std::wstring getValidOpenText(const std::wstring& s);
    
    /**
     * @brief Валидирует зашифрованный текст
     * @param s Входной зашифрованный текст
     * @return Валидный зашифрованный текст
     * @throw cipher_error если текст пустой или содержит строчные буквы
     */
    inline std::wstring getValidCipherText(const std::wstring& s);
    
public:
    /// Конструктор по умолчанию удален
    modAlphaCipher() = delete;
    
    /**
     * @brief Конструктор с ключом
     * @param skey Ключ шифрования
     * @throw cipher_error если ключ пустой, содержит недопустимые символы
     *        или является слабым (все символы одинаковые)
     */
    modAlphaCipher(const std::wstring& skey);
    
    /**
     * @brief Шифрует текст
     * @param open_text Открытый текст для шифрования
     * @return Зашифрованный текст
     * @throw cipher_error если текст пустой после фильтрации
     */
    std::wstring encrypt(const std::wstring& open_text);
    
    /**
     * @brief Дешифрует текст
     * @param cipher_text Зашифрованный текст
     * @return Расшифрованный текст
     * @throw cipher_error если текст пустой или содержит строчные буквы
     */
    std::wstring decrypt(const std::wstring& cipher_text);
};

// Реализация inline методов после объявления класса

inline bool modAlphaCipher::isValidChar(wchar_t c) {
    // Проверяем только русские буквы
    return (c >= L'А' && c <= L'Я') || (c >= L'а' && c <= L'я') || c == L'Ё' || c == L'ё';
}

inline bool modAlphaCipher::isUpperChar(wchar_t c) {
    // Проверяем только прописные русские буквы
    return (c >= L'А' && c <= L'Я') || c == L'Ё';
}

inline wchar_t modAlphaCipher::toUpperChar(wchar_t c) {
    // Преобразуем в прописные русские буквы
    if (c >= L'а' && c <= L'я') return c - L'а' + L'А';
    if (c == L'ё') return L'Ё';
    return c;
}

inline std::wstring modAlphaCipher::getValidKey(const std::wstring& s)
{
    if (s.empty())
        throw cipher_error("Empty key");
    
    std::wstring tmp(s);
    for (auto & c:tmp) {
        if (!isValidChar(c))
            throw cipher_error("Invalid key");
        c = toUpperChar(c);
    }
    return tmp;
}

inline std::wstring modAlphaCipher::getValidOpenText(const std::wstring& s)
{
    std::wstring tmp;
    for (auto c:s) {
        if (isValidChar(c)) {
            tmp.push_back(toUpperChar(c));
        }
    }
    if (tmp.empty())
        throw cipher_error("Empty open text");
    return tmp;
}

inline std::wstring modAlphaCipher::getValidCipherText(const std::wstring& s)
{
    if (s.empty())
        throw cipher_error("Empty cipher text");
    
    for (auto c:s) {
        if (!isUpperChar(c))
            throw cipher_error("Invalid cipher text");
    }
    return s;
}
