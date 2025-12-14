# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = table_route_cipher

# Файлы
SRC = src/main.cpp src/TableRouteCipher.cpp
HEADERS = src/TableRouteCipher.h

# Сборка программы
all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -Isrc $(SRC) -o $(TARGET)

debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

clean:
	rm -f $(TARGET)
	rm -rf docs/ *.pdf

# Документация
doc: html pdf

html:
	@echo "Генерация HTML документации..."
	doxygen Doxyfile
	@echo "✓ HTML создана: docs/html/index.html"

pdf:
	@echo "Генерация PDF документации..."
	@doxygen Doxyfile
	@if [ -d "docs/latex" ]; then \
		cd docs/latex && \
		echo "Сборка LaTeX..." && \
		pdflatex -interaction=nonstopmode refman.tex && \
		makeindex refman.idx && \
		pdflatex -interaction=nonstopmode refman.tex && \
		pdflatex -interaction=nonstopmode refman.tex && \
		mv refman.pdf ../documentation.pdf && \
		echo "✓ PDF создана: docs/documentation.pdf"; \
	else \
		echo "✗ Ошибка: папка LaTeX не создана"; \
	fi

# Альтернативный PDF через wkhtmltopdf
pdf-fast:
	@if command -v wkhtmltopdf >/dev/null 2>&1; then \
		make html && \
		wkhtmltopdf --encoding UTF-8 docs/html/index.html documentation-fast.pdf && \
		echo "✓ PDF создан: documentation-fast.pdf"; \
	else \
		echo "✗ wkhtmltopdf не найден. Установите: sudo apt install wkhtmltopdf"; \
	fi

# Запуск
run: $(TARGET)
	./$(TARGET)

# Открыть документацию
open-doc: html
	@if command -v xdg-open >/dev/null; then \
		xdg-open docs/html/index.html; \
	elif command -v open >/dev/null; then \
		open docs/html/index.html; \
	else \
		echo "Откройте вручную: docs/html/index.html"; \
	fi

open-pdf: pdf
	@if [ -f "docs/documentation.pdf" ]; then \
		if command -v xdg-open >/dev/null; then \
			xdg-open docs/documentation.pdf; \
		elif command -v open >/dev/null; then \
			open docs/documentation.pdf; \
		else \
			echo "Откройте вручную: docs/documentation.pdf"; \
		fi \
	else \
		echo "PDF не найден. Сначала выполните: make pdf"; \
	fi

# Установка зависимостей
install-deps:
	@echo "Установка зависимостей..."
	@if command -v apt-get >/dev/null 2>&1; then \
		sudo apt-get update && \
		sudo apt-get install -y g++ make doxygen graphviz \
			texlive-latex-base texlive-latex-extra texlive-fonts-recommended \
			wkhtmltopdf; \
		echo "✓ Зависимости установлены (Ubuntu/Debian)"; \
	elif command -v brew >/dev/null 2>&1; then \
		brew install gcc make doxygen graphviz basictex wkhtmltopdf; \
		echo "✓ Зависимости установлены (macOS)"; \
	else \
		echo "Установите вручную: g++, make, doxygen, pdflatex"; \
	fi

# Проверка
check:
	@echo "=== Проверка файлов ==="
	@for file in src/main.cpp src/TableRouteCipher.cpp src/TableRouteCipher.h; do \
		if [ -f "$$file" ]; then \
			echo "✓ $$file"; \
		else \
			echo "✗ $$file не найден"; \
		fi \
	done
	@echo ""
	@echo "=== Проверка зависимостей ==="
	@for cmd in g++ make doxygen pdflatex; do \
		if command -v $$cmd >/dev/null 2>&1; then \
			echo "✓ $$cmd найден"; \
		else \
			echo "✗ $$cmd не найден"; \
		fi \
	done

help:
	@echo "=== Table Route Cipher ==="
	@echo "Команды:"
	@echo "  make all        - Сборка программы"
	@echo "  make debug      - Сборка с отладкой"
	@echo "  make run        - Запуск программы"
	@echo "  make clean      - Очистка"
	@echo ""
	@echo "Документация:"
	@echo "  make doc        - HTML + PDF документация"
	@echo "  make html       - Только HTML"
	@echo "  make pdf        - Только PDF (LaTeX)"
	@echo "  make pdf-fast   - Быстрый PDF (wkhtmltopdf)"
	@echo "  make open-doc   - Открыть HTML"
	@echo "  make open-pdf   - Открыть PDF"
	@echo ""
	@echo "Утилиты:"
	@echo "  make install-deps - Установить зависимости"
	@echo "  make check      - Проверка файлов"
	@echo "  make help       - Эта справка"

.PHONY: all debug clean doc html pdf pdf-fast run open-doc open-pdf check help install-deps
