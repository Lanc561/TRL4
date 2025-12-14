/**
 * @file main.cpp
 * @brief Тестирование класса modAlphaCipher
 * @author Генералов Л.К.
 * @version 1.0
 * @copyright ИБСТ ПГУ
 * @date 2025
 * 
 * @mainpage Модифицированный алфавитный шифр
 * 
 * ## Описание проекта
 * 
 * Проект реализует модифицированный алфавитный шифр с поддержкой
 * русского языка. Шифр использует ключ для сдвига символов в алфавите.
 * 
 * ## Авторские права
 * - **Автор:** Генералов Л.К.
 * - **Версия:** 1.0
 * - **Год:** 2025
 * - **Издательство:** ИБСТ ПГУ
 * 
 * ## Особенности
 * - Поддержка русского алфавита (33 буквы, включая Ё)
 * - Валидация входных данных (ключ, текст)
 * - Проверка на слабые ключи
 * - Обработка исключений
 * - Поддержка широких символов (wstring)
 * 
 * ## Структура проекта
 * - `modAlphaCipher.h` - заголовочный файл с объявлением класса
 * - `modAlphaCipher.cpp` - реализация методов класса
 * - `main.cpp` - тестирование функциональности
 * 
 * ## Алгоритм шифрования
 * Для каждого символа текста:
 * ```
 * зашифрованный_символ = (индекс_символа + индекс_ключа) mod 33
 * ```
 * 
 * ## Алгоритм дешифрования
 * Для каждого символа шифротекста:
 * ```
 * расшифрованный_символ = (индекс_шифротекста - индекс_ключа + 33) mod 33
 * ```
 * 
 * ## Пример использования
 * ```cpp
 * modAlphaCipher cipher(L"КЛЮЧ");
 * wstring encrypted = cipher.encrypt(L"ПРИВЕТ");
 * wstring decrypted = cipher.decrypt(encrypted);
 * ```
 */

#include <iostream>
#include <locale>
#include <codecvt>
#include "modAlphaCipher.h"

using namespace std;

/**
 * @brief Тестирует шифрование и дешифрование
 * @param Text Исходный текст для тестирования
 * @param key Ключ шифрования
 * @param testName Название теста
 * @param destructCipherText Флаг для порчи шифротекста (тестирование ошибок)
 * 
 * Функция выполняет полный цикл: шифрование -> (опционально порча) -> дешифрование
 * и сравнивает исходный текст с результатом дешифрования.
 */
void check(const wstring& Text, const wstring& key, const wstring& testName, 
           bool destructCipherText = false)
{
    try {
        wstring cipherText;
        wstring decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text);
        
        // Имитация порчи данных для тестирования обработки ошибок
        if (destructCipherText && !cipherText.empty())
            cipherText[0] = tolower(cipherText[0], locale("en_US.UTF-8"));
            
        decryptedText = cipher.decrypt(cipherText);
        
        wcout << L"=== " << testName << L" ===" << endl;
        wcout << L"Ключ: " << key << endl;
        wcout << L"Исходный текст: " << Text << endl;
        wcout << L"Зашифрованный: " << cipherText << endl;
        wcout << L"Расшифрованный: " << decryptedText << endl;
        
        if (Text == decryptedText)
            wcout << L"[OK] Тест пройден\n";
        else
            wcout << L"[ERROR] Ошибка!\n";
            
    } catch (const cipher_error& e) {
        wcout << L"Ошибка cipher_error: " << e.what() << endl;
    } catch (const exception& e) {
        wcout << L"Ошибка: " << e.what() << endl;
    }
    wcout << endl;
}

/**
 * @brief Главная функция программы
 * @return 0 при успешном выполнении
 * 
 * Запускает серию тестов для проверки корректности работы шифра:
 * 1. Тесты с русским текстом
 * 2. Тесты с английским текстом (должны вызывать исключения)
 * 3. Тесты с ошибочными входными данными
 */
int main()
{
    // Настройка локали для работы с широкими символами
    setlocale(LC_ALL, "en_US.UTF-8");
    locale::global(locale("en_US.UTF-8"));
    wcout.imbue(locale("en_US.UTF-8"));
    
    wcout << L"=== ТЕСТИРОВАНИЕ МОДИФИЦИРОВАННОГО АЛФАВИТНОГО ШИФРА ===\n";
    wcout << L"Автор: Генералов Л.К.\n";
    wcout << L"Версия: 1.0\n";
    wcout << L"Год: 2025\n";
    wcout << L"Издательство: ИБСТ ПГУ\n\n";
    
    // Тесты на русском языке (корректные)
    check(L"ПРИВЕТМИР", L"КЛЮЧ", L"Русский текст 1");
    check(L"ПРОГРАММИРОВАНИЕ", L"ШИФР", L"Русский текст 2");
    check(L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ", L"АЛФАВИТ", L"Полный алфавит");
    
    // Тесты с английским текстом (должны вызывать исключения)
    check(L"HELLOWORLD", L"KEY", L"Английский текст 1");
    check(L"PROGRAMMING", L"CODE", L"Английский текст 2");
    
    // Тесты исключений
    check(L"ПРИВЕТМИР", L"", L"Пустой ключ");
    check(L"123", L"KEY", L"Текст без букв");
    check(L"ПРИВЕТ", L"ААА", L"Слабый ключ (все символы одинаковые)");
    
    // Тест с порчей шифротекста
    check(L"ТЕСТ", L"ПАРОЛЬ", L"Тест с порчей шифротекста", true);
    
    wcout << L"=== ТЕСТИРОВАНИЕ ЗАВЕРШЕНО ===\n";
    
    return 0;
}
