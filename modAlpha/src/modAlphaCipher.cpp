/**
 * @file modAlphaCipher.cpp
 * @brief Реализация методов класса modAlphaCipher
 * @author Генералов Л.К.
 * @version 1.0
 * @copyright ИБСТ ПГУ
 * @date 2025
 * 
 * @details
 * Содержит реализацию основных методов шифрования и дешифрования,
 * а также вспомогательных методов преобразования.
 */

#include "modAlphaCipher.h"
#include <iostream>
#include <locale>
#include <codecvt>

using namespace std;

/**
 * @brief Конструктор класса modAlphaCipher
 * @param skey Ключ шифрования
 * @throw cipher_error если ключ слабый (все символы одинаковые)
 * 
 * Инициализирует алфавит и преобразует ключ в числовое представление.
 */
modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    // Инициализация отображения символ -> индекс
    for(unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    
    // Валидация ключа
    std::wstring validKey = getValidKey(skey);
    
    // Проверка на слабый ключ (все одинаковые символы)
    bool isWeakKey = true;
    if (validKey.size() > 1) {
        wchar_t firstChar = validKey[0];
        for (size_t i = 1; i < validKey.size(); i++) {
            if (validKey[i] != firstChar) {
                isWeakKey = false;
                break;
            }
        }
    }
    if (isWeakKey && validKey.size() > 0) {
        throw cipher_error("Weak key");
    }
    
    // Преобразование ключа в числовое представление
    key = convert(validKey);
}

/**
 * @brief Шифрует открытый текст
 * @param open_text Открытый текст для шифрования
 * @return Зашифрованный текст
 * @throw cipher_error если текст пустой после фильтрации
 * 
 * Алгоритм шифрования: (символ_текста + символ_ключа) mod размер_алфавита
 */
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::vector<int> work = convert(getValidOpenText(open_text));
    for(unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

/**
 * @brief Дешифрует зашифрованный текст
 * @param cipher_text Зашифрованный текст
 * @return Расшифрованный текст
 * @throw cipher_error если текст пустой или содержит строчные буквы
 * 
 * Алгоритм дешифрования: (символ_шифротекста - символ_ключа + размер_алфавита) mod размер_алфавита
 */
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::vector<int> work = convert(getValidCipherText(cipher_text));
    for(unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

/**
 * @brief Преобразует строку в вектор числовых индексов
 * @param s Входная строка
 * @return Вектор индексов символов в алфавите
 * 
 * Каждый символ строки преобразуется в его позицию в алфавите.
 * Символы, отсутствующие в алфавите, игнорируются.
 */
std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for(auto c : s) {
        if (alphaNum.find(c) != alphaNum.end()) {
            result.push_back(alphaNum[c]);
        }
    }
    return result;
}

/**
 * @brief Преобразует вектор числовых индексов в строку
 * @param v Вектор индексов
 * @return Строка символов
 * 
 * Каждый индекс преобразуется в соответствующий символ алфавита.
 * Индексы вне диапазона алфавита игнорируются.
 */
std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for(auto i : v) {
        if (i >= 0 && i < (int)numAlpha.size()) {
            result.push_back(numAlpha[i]);
        }
    }
    return result;
}
