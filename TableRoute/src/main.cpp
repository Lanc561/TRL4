/**
 * @file main.cpp
 * @brief Основной файл программы для тестирования TableRouteCipher
 * 
 * Содержит автоматические тесты и интерактивный режим для шифрования/дешифрования.
 * Демонстрирует работу класса TableRouteCipher и обработку исключений.
 */

#include <iostream>
#include "TableRouteCipher.h"

/**
 * @brief Функция автоматического тестирования TableRouteCipher
 * 
 * Выполняет серию тестов для проверки корректности работы шифра:
 * - Нормальная работа
 * - Обработка граничных случаев
 * - Обработка исключительных ситуаций
 */
void testCipher() {
    std::cout << "\n=== ТЕСТИРОВАНИЕ ОБРАБОТКИ ИСКЛЮЧЕНИЙ ===" << std::endl;
    
    // ТЕСТ 1: Нормальный случай - текст БОЛЬШЕ ключа (должен работать)
    std::cout << "\n--- ТЕСТ 1: Нормальная работа ---" << std::endl;
    std::cout << "Проверка: Текст 'HELLO' (5 символов) > Ключ 3" << std::endl;
    std::cout << "Ожидание: УСПЕШНОЕ шифрование и дешифрование" << std::endl;
    try {
        TableRouteCipher cipher1(3);
        std::string encrypted = cipher1.encrypt("HELLO");
        std::string decrypted = cipher1.decrypt(encrypted);
        std::cout << "[OK] РЕЗУЛЬТАТ: ТЕСТ ПРОЙДЕН" << std::endl;
        std::cout << "  Зашифровано: " << encrypted << std::endl;
        std::cout << "  Расшифровано: " << decrypted << std::endl;
    } catch (const cipher_error& e) {
        std::cout << "[FAIL] РЕЗУЛЬТАТ: ТЕСТ ПРОВАЛЕН - " << e.what() << std::endl;
    }
    
    // ТЕСТ 2: Текст РАВЕН ключу (должна быть ошибка)
    std::cout << "\n--- ТЕСТ 2: Текст равен ключу ---" << std::endl;
    std::cout << "Проверка: Текст 'WORLD' (5 символов) = Ключ 5" << std::endl;
    std::cout << "Ожидание: ОШИБКА 'Длина текста должна быть больше ключа'" << std::endl;
    try {
        TableRouteCipher cipher2(5);
        cipher2.encrypt("WORLD");
        std::cout << "[FAIL] РЕЗУЛЬТАТ: ТЕСТ ПРОВАЛЕН - Ожидалась ошибка" << std::endl;
    } catch (const cipher_error& e) {
        std::cout << "[OK] РЕЗУЛЬТАТ: ТЕСТ ПРОЙДЕН - " << e.what() << std::endl;
    }
    
    // ТЕСТ 3: Текст МЕНЬШЕ ключа (должна быть ошибка)
    std::cout << "\n--- ТЕСТ 3: Текст меньше ключа ---" << std::endl;
    std::cout << "Проверка: Текст 'HI' (2 символа) < Ключ 10" << std::endl;
    std::cout << "Ожидание: ОШИБКА 'Длина текста должна быть больше ключа'" << std::endl;
    try {
        TableRouteCipher cipher3(10);
        cipher3.encrypt("HI");
        std::cout << "[FAIL] РЕЗУЛЬТАТ: ТЕСТ ПРОВАЛЕН - Ожидалась ошибка" << std::endl;
    } catch (const cipher_error& e) {
        std::cout << "[OK] РЕЗУЛЬТАТ: ТЕСТ ПРОЙДЕН - " << e.what() << std::endl;
    }
    
    // ТЕСТ 4: Невалидный ключ (должна быть ошибка)
    std::cout << "\n--- ТЕСТ 4: Невалидный ключ ---" << std::endl;
    std::cout << "Проверка: Ключ = 0 (отрицательный или нулевой)" << std::endl;
    std::cout << "Ожидание: ОШИБКА 'Ключ должен быть положительным'" << std::endl;
    try {
        TableRouteCipher cipher4(0);
        std::cout << "[FAIL] РЕЗУЛЬТАТ: ТЕСТ ПРОВАЛЕН - Ожидалась ошибка" << std::endl;
    } catch (const cipher_error& e) {
        std::cout << "[OK] РЕЗУЛЬТАТ: ТЕСТ ПРОЙДЕН - " << e.what() << std::endl;
    }
    
    // ТЕСТ 5: Текст без буквенных символов (должна быть ошибка)
    std::cout << "\n--- ТЕСТ 5: Текст без букв ---" << std::endl;
    std::cout << "Проверка: Текст '12345' (только цифры, нет букв)" << std::endl;
    std::cout << "Ожидание: ОШИБКА 'Текст не содержит букв'" << std::endl;
    try {
        TableRouteCipher cipher5(3);
        cipher5.encrypt("12345");
        std::cout << "[FAIL] РЕЗУЛЬТАТ: ТЕСТ ПРОВАЛЕН - Ожидалась ошибка" << std::endl;
    } catch (const cipher_error& e) {
        std::cout << "[OK] РЕЗУЛЬТАТ: ТЕСТ ПРОЙДЕН - " << e.what() << std::endl;
    }
    
    // ТЕСТ 6: Пустой текст (должна быть ошибка)
    std::cout << "\n--- ТЕСТ 6: Пустой текст ---" << std::endl;
    std::cout << "Проверка: Текст '' (пустая строка)" << std::endl;
    std::cout << "Ожидание: ОШИБКА 'Текст пуст'" << std::endl;
    try {
        TableRouteCipher cipher6(3);
        cipher6.encrypt("");
        std::cout << "[FAIL] РЕЗУЛЬТАТ: ТЕСТ ПРОВАЛЕН - Ожидалась ошибка" << std::endl;
    } catch (const cipher_error& e) {
        std::cout << "[OK] РЕЗУЛЬТАТ: ТЕСТ ПРОЙДЕН - " << e.what() << std::endl;
    }
}

/**
 * @brief Основная функция программы
 * @return 0 при успешном завершении, 1 при ошибке
 * 
 * Запускает автоматические тесты и предоставляет интерактивный режим
 * для шифрования/дешифрования текста.
 */
int main()
{
    // Запускаем автоматические тесты
    testCipher();
    
    std::cout << "\n=== ИНТЕРАКТИВНЫЙ РЕЖИМ ===" << std::endl;
    std::cout << "Теперь вы можете протестировать шифрование вручную:" << std::endl;
    
    try {
        int key;
        std::cout << "Введите ключ (число столбцов): ";
        std::cin >> key;

        TableRouteCipher cipher(key); 

        int op;
        std::string text;
        do {
            std::cout << "\nВыберите операцию:\n";
            std::cout << "1 — Зашифровать текст\n";
            std::cout << "2 — Расшифровать текст\n";
            std::cout << "0 — Выход\n";
            std::cout << "Ваш выбор: ";
            std::cin >> op;

            if (op == 1 || op == 2) {
                std::cout << "Введите текст: ";
                std::cin.ignore();
                std::getline(std::cin, text);

                try {
                    if (op == 1) {
                        std::string encrypted = cipher.encrypt(text);
                        std::cout << "[ЗАШИФРОВАНО] Зашифрованный текст: " << encrypted << "\n";
                    } else if (op == 2) {
                        std::string decrypted = cipher.decrypt(text);
                        std::cout << "[РАСШИФРОВАНО] Расшифрованный текст: " << decrypted << "\n";
                    }
                } catch (const cipher_error& e) {
                    std::cout << "[ОШИБКА] Ошибка шифрования: " << e.what() << "\n";
                    std::cout << "[ПОДСКАЗКА] Длина текста должна быть БОЛЬШЕ ключа (" << key << ")" << "\n";
                } catch (const std::exception& e) {
                    std::cout << "[ОШИБКА] Неизвестная ошибка: " << e.what() << "\n";
                }
            } else if (op != 0) {
                std::cout << "[ПРЕДУПРЕЖДЕНИЕ] Неверный выбор. Попробуйте снова.\n";
            }

        } while (op != 0);

        std::cout << "До свидания!\n";

    } catch (const cipher_error& e) {
        std::cerr << "[ОШИБКА] Ошибка инициализации: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "[ОШИБКА] Неизвестная ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
