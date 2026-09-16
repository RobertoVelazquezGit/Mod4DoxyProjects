# BasicCodeDoc

Educational C++ console application demonstrating source-code documentation
through a calculator and a small statistical data set. The implementation and
the demonstration program are contained in main.cpp.

## Main features

- Arithmetic operations: addition, subtraction, multiplication and division.
- Square roots and exponentiation.
- Storage, retrieval and clearing of a single calculator memory value.
- An error flag for division by zero and square roots of negative numbers.
- Statistical operations: arithmetic mean, minimum, maximum and data count.
- Helpers for detecting non-finite numbers and formatting results.

## Main classes and functions

- Calculator: arithmetic, mathematical operations, memory and error state.
- StatisticsCalculator: stores values and computes descriptive statistics.
- isValidNumber(): checks whether a number is finite.
- formatResult(): converts a result to text and truncates decimal digits.
- main(): demonstrates both calculators with sample values and exception handling.

## Usage example

```cpp
Calculator calc;
double result = calc.add(5.0, 3.0);
calc.storeInMemory(result);
double stored = calc.recallFromMemory(); // 8.0

StatisticsCalculator stats;
stats.addValue(10.0);
stats.addValue(20.0);
double mean = stats.calculateMean(); // 15.0
```

## Behavior and limitations

Calculator::divide() throws `std::invalid_argument` for a zero divisor, and
Calculator::squareRoot() throws the same exception for a negative input.
Both operations set the error flag; Calculator::clearErrors() resets it.
Statistical calculations throw `std::runtime_error` when the data set is empty.

formatResult() requires an explicit decimal-place argument and truncates the
string produced by `std::to_string`; it does not round to the requested precision.
Use a non-negative decimal-place count. With zero decimal places, the current
implementation retains the decimal point. Non-finite results produce
`Error: Invalid number`. The calculator classes do not provide synchronization
for concurrent access.

## Requirements and build

- Visual Studio Community with the C++ desktop development tools and MSVC v143.
- Windows SDK and the existing Visual Studio solution.
- The Debug x64 configuration uses C++17.
- Doxygen and Graphviz (`dot` available on `PATH`) for documentation generation.

Open `Mod4DoxyProjects.sln` in Visual Studio, select BasicCodeDoc as the startup
project, select Debug and x64, and build and run the project.

## Generate and browse the documentation

From the BasicCodeDoc directory, run:

```powershell
doxygen Doxyfile
```

Open `docs/html/index.html` to browse the documentation. This README is the main
page. Class and file pages provide API descriptions, private member documentation,
source navigation, include diagrams, and call/caller graphs where relationships
exist. The configuration scans source and Markdown files recursively and excludes
generated documentation and build output. Only HTML output is enabled.

Regenerate the documentation after changing source comments or this README.
