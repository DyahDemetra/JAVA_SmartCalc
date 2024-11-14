# SmartCalc v3.0

**SmartCalc v3.0** is a powerful desktop calculator developed in Java using the MVVM/MVP design patterns. The program provides a user-friendly and intuitive graphical interface for users on Linux and macOS platforms, while supporting a wide range of mathematical functions and operations.

### Key Features:

- **Support for Various Number Types**: The calculator works with both integers and floating-point numbers, including numbers in exponential notation.
- **Infix and Polish Notation**: Supports standard arithmetic operations in both infix and reverse Polish notation.
- **Mathematical Functions**: The calculator supports calculations for trigonometric functions like cosine, sine, tangent, logarithms, and more.

### Graph Plotting:

SmartCalc v3.0 offers advanced functionality for visualizing mathematical functions:

- **Functions with Variable `x`**: The program allows plotting graphs for arbitrary functions expressed in infix notation with a variable `x`. This includes functions such as sine, cosine, logarithms, and others.
  
- **Plotting Range**: For graph plotting, you can specify the domain and range of the function, constrained between -1,000,000 and 1,000,000. The graph is rendered with an adaptive grid and scale, ensuring accurate representation of function values.

- **Display Options**: Graphs are plotted with coordinate axes, scalable axes, and an automatically adjusting grid, offering maximum clarity and ease of analysis for the user.

- **Precision**: The program uses high precision for calculations and graph plotting, ensuring results up to 7 decimal places, which is particularly important for complex mathematical expressions.

### Additional Features:

- **Arithmetic Operations**: The calculator supports standard arithmetic operations, such as addition, subtraction, multiplication, division, exponentiation, modulus, and unary minus.
  
- **Mathematical Functions**: In addition to arithmetic, the program provides functions for cosine, sine, tangent, logarithms, square roots, and other advanced operations.

- **Architecture and Modularity**: The core of the calculator, including algorithms for processing expressions in Polish and infix notation, is implemented in C/C++ and integrated as a dynamic library, ensuring high performance and flexibility.

### Technical Details:

- The program follows the MVVM/MVP design patterns, ensuring clear separation of business logic and presentation layers.
- All calculations are performed with high precision, supporting up to 7 decimal places.

SmartCalc v3.0 is the perfect tool for solving complex mathematical problems with an emphasis on precision and ease of data visualization. Its user-friendly interface and powerful computational capabilities make it an excellent choice for students, educators, and professionals working with mathematical expressions and functions.


# SmartCalc Project Setup

Follow the instructions below to build and run the SmartCalc project.

## 1. Create the target directory
This command will clean the previous build and package the project.
```bash
mvn clean package
```

## 2. Running the program without creating an .exe
If you just want to run the program without generating an executable, use the following command:
```bash
java --module-path "C:\path\to\your\javafx\lib" --add-modules javafx.controls,javafx.fxml -jar target/SmartCalc-1.0-SNAPSHOT.jar
```

## 3. Create a folder for the SmartCalc executable
To create the folder containing the SmartCalc executable (`SmartCalc.exe`), use this command:
```bash
jpackage --input target --name SmartCalc --main-jar SmartCalc-1.0-SNAPSHOT.jar --main-class school21.smartcalc.application.smartcalc.HelloApplication --type app-image
```

## 4. Creating a custom runtime environment (if needed)
If you encounter problems, you can create a custom runtime image first:
```bash
jlink --module-path "C:\path\to\your\jmods;C:\path\to\your\javafx\lib" --add-modules javafx.controls,javafx.fxml --output target/runtime
```

## 5. Re-run the `jpackage` command with the custom runtime environment
Once the custom runtime is created, you can re-run the `jpackage` command with the following:
```bash
jpackage --input target --name SmartCalc --main-jar SmartCalc-1.0-SNAPSHOT.jar --main-class school21.smartcalc.application.smartcalc.HelloApplication --type app-image --runtime-image target/runtime --java-options "-Dprism.order=sw"
```