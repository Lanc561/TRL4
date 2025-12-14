# Makefile для проекта модифицированного алфавитного шифра
# Автор: Генералов Л.К., Версия: 1.0, Год: 2025, Издательство: ИБСТ ПГУ

# Компилятор
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Файлы проекта
SRC_DIR = src
INC_DIR = src/headers
SOURCES = src/main.cpp src/modAlphaCipher.cpp
HEADERS = src/headers/modAlphaCipher.h
TARGET = alpha_cipher

# Документация
DOXYFILE = Doxyfile
DOC_DIR = docs
PDF_OUTPUT = docs/documentation.pdf

# Основная цель
all: $(TARGET)

# Сборка программы
$(TARGET): $(SOURCES) $(HEADERS)
	@echo "=== Сборка программы ==="
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) $(SOURCES) -o $(TARGET)
	@echo "✅ Программа собрана: $(TARGET)"

# Запуск программы
run: $(TARGET)
	@echo "=== Запуск программы ==="
	./$(TARGET)

# Генерация HTML документации
html: $(DOXYFILE) $(SOURCES) $(HEADERS)
	@echo "=== Генерация HTML документации ==="
	@mkdir -p $(DOC_DIR)
	doxygen $(DOXYFILE)
	@if [ -f "docs/html/index.html" ]; then \
		echo "✅ HTML документация создана: docs/html/index.html"; \
	else \
		echo "❌ Ошибка создания HTML документации"; \
	fi

# Генерация PDF документации
pdf: $(DOXYFILE) $(SOURCES) $(HEADERS)
	@echo "=== Генерация PDF документации ==="
	@echo "Автор: Генералов Л.К., Версия: 1.0, Год: 2025, Издательство: ИБСТ ПГУ"
	@echo ""
	
	@# 1. Очищаем старую документацию
	@rm -rf docs/latex docs/documentation.pdf
	@mkdir -p docs
	
	@# 2. Генерируем Doxygen документацию
	@echo "1. Генерация Doxygen документации..."
	@doxygen $(DOXYFILE) 2>&1 | grep -v "warning" || true
	
	@# 3. Проверяем создалась ли директория latex
	@if [ -d "docs/latex" ]; then \
		echo "2. Компиляция LaTeX в PDF..."; \
		cd docs/latex; \
		echo "   Первая компиляция..."; \
		pdflatex -interaction=nonstopmode refman.tex > /dev/null 2>&1; \
		echo "   Вторая компиляция..."; \
		pdflatex -interaction=nonstopmode refman.tex > /dev/null 2>&1; \
		if [ -f "refman.idx" ]; then \
			echo "   Создание индекса..."; \
			makeindex refman.idx > /dev/null 2>&1; \
			echo "   Финальная компиляция..."; \
			pdflatex -interaction=nonstopmode refman.tex > /dev/null 2>&1; \
		fi; \
		if [ -f "refman.pdf" ]; then \
			cp refman.pdf ../documentation.pdf; \
			echo ""; \
			echo "✅ PDF документация создана: docs/documentation.pdf"; \
		else \
			echo "❌ Ошибка: PDF не создан"; \
		fi; \
	else \
		echo "❌ Ошибка: Doxygen не создал LaTeX файлы"; \
		echo "   Проверьте Doxyfile и наличие исходных файлов"; \
	fi

# Вся документация (HTML + PDF)
doc: html pdf
	@echo "✅ Вся документация создана"
	@echo "📄 HTML: docs/html/index.html"
	@echo "📄 PDF:  docs/documentation.pdf"

# Просмотр документации
view-html:
	@if [ -f "docs/html/index.html" ]; then \
		echo "Открытие HTML документации..."; \
		xdg-open docs/html/index.html 2>/dev/null || \
		open docs/html/index.html 2>/dev/null || \
		echo "Откройте: docs/html/index.html"; \
	else \
		echo "Сначала создайте документацию: make html"; \
	fi

view-pdf:
	@if [ -f "docs/documentation.pdf" ]; then \
		echo "Открытие PDF документации..."; \
		xdg-open docs/documentation.pdf 2>/dev/null || \
		open docs/documentation.pdf 2>/dev/null || \
		echo "Откройте: docs/documentation.pdf"; \
	else \
		echo "Сначала создайте PDF: make pdf"; \
	fi

# Проверка
check:
	@echo "=== Проверка ==="
	@ls -la src/ src/headers/ 2>/dev/null || echo "Директории src/ не существует"
	@ls -la src/main.cpp src/modAlphaCipher.cpp src/headers/modAlphaCipher.h 2>/dev/null || echo "Нет исходных файлов"
	@which doxygen >/dev/null 2>&1 && echo "✅ Doxygen" || echo "❌ Doxygen не установлен"
	@which pdflatex >/dev/null 2>&1 && echo "✅ LaTeX" || echo "❌ LaTeX не установлен"
	@echo ""

# Очистка
clean:
	@echo "Очистка проекта..."
	rm -f $(TARGET)
	rm -rf docs

# Пересборка
rebuild: clean all

# Помощь
help:
	@echo "=== Доступные команды ==="
	@echo "make           - Собрать программу"
	@echo "make run       - Запустить программу"
	@echo "make html      - Создать HTML документацию"
	@echo "make pdf       - Создать PDF документацию"
	@echo "make doc       - Создать всю документацию"
	@echo "make view-html - Открыть HTML документацию"
	@echo "make view-pdf  - Открыть PDF документацию"
	@echo "make check     - Проверить файлы и зависимости"
	@echo "make clean     - Очистить проект"
	@echo "make rebuild   - Пересобрать всё"
	@echo "make help      - Эта справка"

.PHONY: all run html pdf doc view-html view-pdf check clean rebuild help
