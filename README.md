# Plugin Calculator
Консольный калькулятор с плагинами на C++

## Сборка и запуск
**1️⃣ Клонировать проект**

git clone https://github.com/Jujun1or/plugin-calculator

cd calculator

**2️⃣ Сборка (в корень проекта)**

cmake -B .

cmake --build .

**3️⃣ Запустить**

./calc.exe

## Структура проекта
src/ — исходный код калькулятора

plugins/ — скомпилированные плагины (.dll)

plugins/plugins_source/ — исходники плагинов (.cpp)

## Как добавить новый плагин
**1️⃣ Добавь .cpp файл в папку:**
plugins/plugins_source/

например:
plugins/plugins_source/funcpow.cpp

**2️⃣ Калькулятор автоматически скомпилирует этот плагин (.cpp → .dll) и сохранит его в plugins/**

**3️⃣ После этого новая функция будет доступна сразу:**

Enter expression: pow(2, 8)
Result: 256

## Особенности
Калькулятор пересобирает и подгружает плагины перед каждым выражением

## Примеры использования
Enter expression: 16 + 4 * (3 - 1)

Result: 24

Enter expression: sin(deg(30))

Result: 0.5

Enter expression: ln(8)

Result: 2.0794

Enter expression: pow(2, 8)

Result: 256
