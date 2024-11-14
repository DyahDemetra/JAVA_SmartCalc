# SmartCalc v3.0

**SmartCalc v3.0** — это мощный десктопный калькулятор, разработанный на языке Java с использованием паттернов MVVM/MVP. Программа предоставляет удобный и интуитивно понятный графический интерфейс, а также поддерживает широкий спектр математических функций и операций.

### Ключевые особенности:

- **Поддержка различных типов чисел**: калькулятор работает как с целыми, так и с вещественными числами, включая числа в экспоненциальной записи.
- **Инфиксная и польская нотация**: поддержка стандартных арифметических операций в инфиксной и обратной польской нотации.
- **Математические функции**: калькулятор поддерживает вычисления для таких математических функций, как косинус, синус, тангенс, логарифмы и другие.

### Построение графиков:

SmartCalc v3.0 обладает расширенными возможностями для визуализации математических функций:

- **Графики с переменной `x`**: программа позволяет строить графики для произвольных функций, заданных через выражения с переменной `x` в инфиксной нотации. Это включает в себя такие функции, как синус, косинус, логарифмы и другие.
  
- **Диапазоны для графиков**: для построения графика можно задать область определения и область значений функции, ограничиваясь диапазоном от -1 000 000 до 1 000 000. Вывод графика происходит с адаптивной сеткой и масштабом, позволяющим точно отобразить значения функции.

- **Параметры отображения**: графики строятся с отображением координатных осей, масштабируемыми осями и сеткой, которая автоматически адаптируется к выбранному диапазону значений. Это обеспечивает максимальную наглядность и удобство для пользователя при анализе функций.

- **Точность**: для вычислений и построения графиков используется высокая точность, до 7 знаков после запятой, что особенно важно для сложных математических выражений.

### Дополнительные функции:

- **Арифметические операции**: калькулятор поддерживает стандартные арифметические операции: сложение, вычитание, умножение, деление, возведение в степень, остаток от деления и унарный минус.
  
- **Математические функции**: помимо стандартных операций, доступны такие функции, как косинус, синус, тангенс, логарифмы, квадратный корень и другие.

- **Архитектура и модульность**: ядро калькулятора, включающее алгоритмы для вычислений и обработки выражений в польской и инфиксной нотации, реализовано на C/C++ и подключено как динамическая библиотека, что обеспечивает высокую производительность и гибкость.

### Технические детали:

- Программа использует паттерны MVVM/MVP для чёткого разделения бизнес-логики и представления.
- Все вычисления выполняются с высокой точностью, поддерживая до 7 знаков после запятой.

SmartCalc v3.0 — это идеальный инструмент для решения сложных математических задач с акцентом на точность и удобство визуализации данных. Удобный интерфейс и мощные вычислительные возможности делают его отличным выбором как для студентов и преподавателей, так и для профессионалов, работающих с математическими выражениями и функциями.


# Настройка проекта SmartCalc

Следуйте инструкциям ниже, чтобы собрать и запустить проект SmartCalc.

## 1. Создать папку `target`
Этот шаг очистит предыдущую сборку и упакует проект.
```bash
mvn clean package
```

## 2. Запуск программы без создания .exe
Если вам нужно просто запустить программу без создания исполняемого файла, используйте следующую команду:
```bash
java --module-path "C:\Users\stani\code\javafx-sdk-17.0.12\lib" --add-modules javafx.controls,javafx.fxml -jar target/SmartCalc-1.0-SNAPSHOT.jar
```

## 3. Создать папку для SmartCalc.exe
Чтобы создать папку, содержащую исполняемый файл SmartCalc (`SmartCalc.exe`), используйте команду:
```bash
jpackage --input target --name SmartCalc --main-jar SmartCalc-1.0-SNAPSHOT.jar --main-class school21.smartcalc.application.smartcalc.HelloApplication --type app-image
```

## 4. Создание кастомного runtime-пространства (если нужно)
Если возникают проблемы, вы можете сначала создать кастомное runtime-пространство с помощью следующей команды:
```bash
jlink --module-path "C:\Program Files\Java\jdk-17.0.2\jmods;C:\Users\stani\code\javafx-sdk-17.0.12\lib" --add-modules javafx.controls,javafx.fxml --output target/runtime
```

## 5. Повторный запуск команды `jpackage` с кастомным runtime-пространством
После создания кастомного runtime-пространства можно повторно запустить команду `jpackage`, указав его:
```bash
jpackage --input target --name SmartCalc --main-jar SmartCalc-1.0-SNAPSHOT.jar --main-class school21.smartcalc.application.smartcalc.HelloApplication --type app-image --runtime-image target/runtime --java-options "-Dprism.order=sw"
```