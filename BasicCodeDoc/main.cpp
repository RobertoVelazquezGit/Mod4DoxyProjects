// ============================================================================
// Lab Solution: Basic Code Documentation and Comments
// Complete implementation with proper documentation throughout
// ============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>

using namespace std;

/**
 * @file main.cpp
 * @brief Arithmetic and statistics calculator demonstration.
 * Author: Student Name
 * Date: December 15, 2024
 * Purpose: A comprehensive calculator library providing basic arithmetic,
 *          advanced mathematical functions, memory operations, and statistical
 *          calculations for educational and practical use.
 *
 * This library provides two main classes:
 * - Calculator: Basic and advanced mathematical operations with memory
 * - StatisticsCalculator: Statistical analysis of data sets
 *
 * Version: 1.0
 * Dependencies: Standard C++ library (cmath for mathematical functions)
 */

 /**
  * Calculator class provides basic arithmetic operations, advanced mathematical
  * functions, and memory storage capabilities.
  *
  * This class is designed for general-purpose calculations and includes error
  * handling for common edge cases like division by zero and invalid inputs.
  *
  * Usage Example:
  *   Calculator calc;
  *   double result = calc.add(5.0, 3.0);  // Returns 8.0
  *   calc.storeInMemory(result);
  *   double stored = calc.recallFromMemory();  // Returns 8.0
  *
  * Note: This class is not thread-safe. Use separate instances for concurrent access.
  */
class Calculator {
private:
    double memory;   ///< Stores a single value in calculator memory
    bool hasError;   ///< Tracks if an error has occurred during operations

public:
    /**
     * Constructor initializes calculator with clean state.
     * Sets memory to 0.0 and clears any error flags.
     */
    Calculator() {
        // Initialize calculator with default values
        memory = 0.0;
        hasError = false;
    }

    /**
     * Adds two numbers together.
     * @param a First number to add
     * @param b Second number to add
     * @return Sum of a and b
     *
     * Example: add(5.0, 3.0) returns 8.0
     */
    double add(double a, double b) {
        // Perform simple addition - no error conditions possible
        return a + b;
    }

    /**
     * Subtracts the second number from the first.
     * @param a Number to subtract from (minuend)
     * @param b Number to subtract (subtrahend)
     * @return Difference of a minus b
     *
     * Example: subtract(10.0, 3.0) returns 7.0
     */
    double subtract(double a, double b) {
        return a - b;
    }

    /**
     * Multiplies two numbers together.
     * @param a First number to multiply
     * @param b Second number to multiply
     * @return Product of a and b
     *
     * Example: multiply(4.0, 2.5) returns 10.0
     */
    double multiply(double a, double b) {
        return a * b;
    }

    /**
     * Divides the first number by the second.
     * @param a Dividend (number to be divided)
     * @param b Divisor (number to divide by)
     * @return Quotient of a divided by b
     * @throws invalid_argument if b equals zero
     *
     * Example: divide(15.0, 3.0) returns 5.0
     * Note: Division by zero will throw an exception and set error flag
     */
    double divide(double a, double b) {
        // Check for division by zero before performing operation
        if (b == 0.0) {
            hasError = true;
            throw invalid_argument("Division by zero");
        }
        return a / b;
    }

    /**
     * Calculates the square root of a number.
     * @param value Number to find square root of (must be non-negative)
     * @return Square root of the input value
     * @throws invalid_argument if value is negative
     *
     * Example: squareRoot(16.0) returns 4.0
     * Mathematical note: Uses the standard library sqrt function
     */
    double squareRoot(double value) {
        // Square root is undefined for negative numbers in real number system
        if (value < 0) {
            hasError = true;
            throw invalid_argument("Cannot calculate square root of negative number");
        }
        return sqrt(value);
    }

    /**
     * Raises a base number to the power of an exponent.
     * @param base The base number
     * @param exponent The power to raise the base to
     * @return base raised to the power of exponent
     *
     * Example: power(2.0, 3.0) returns 8.0 (2³ = 8)
     * Mathematical note: Uses the standard library pow function
     */
    double power(double base, double exponent) {
        // Calculate base^exponent using standard library function
        return pow(base, exponent);
    }

    /**
     * Stores a value in calculator memory for later retrieval.
     * @param value The number to store in memory
     *
     * Example: storeInMemory(42.0) saves 42.0 for later use
     * Note: Only one value can be stored at a time; new values overwrite old ones
     */
    void storeInMemory(double value) {
        // Store the value, replacing any previously stored value
        memory = value;
    }

    /**
     * Retrieves the value currently stored in calculator memory.
     * @return The value stored in memory (0.0 if nothing has been stored)
     *
     * Example: If 42.0 was stored, recallFromMemory() returns 42.0
     * Note: This is a const function - it doesn't modify the calculator state
     */
    double recallFromMemory() const {
        // Return the stored memory value without modifying it
        return memory;
    }

    /**
     * Clears the calculator memory, setting it back to 0.0.
     * Used to reset memory when starting fresh calculations.
     */
    void clearMemory() {
        memory = 0.0;
    }

    /**
     * Checks if any errors have occurred during calculations.
     * @return true if errors have occurred, false otherwise
     *
     * Useful for checking calculator state after a series of operations
     */
    bool hasErrors() const {
        return hasError;
    }

    /**
     * Clears the error flag, resetting calculator to normal operation.
     * Call this after handling an error to continue using the calculator.
     */
    void clearErrors() {
        hasError = false;
    }
};

/**
 * StatisticsCalculator provides statistical analysis capabilities for data sets.
 *
 * This class manages a collection of numeric values and can calculate various
 * statistical measures such as mean, minimum, and maximum values.
 *
 * Usage Pattern:
 *   1. Create StatisticsCalculator instance
 *   2. Add data values using addValue()
 *   3. Calculate statistics using calculation methods
 *   4. Clear data when ready to analyze a new set
 *
 * Example:
 *   StatisticsCalculator stats;
 *   stats.addValue(10.0);
 *   stats.addValue(20.0);
 *   double mean = stats.calculateMean();  // Returns 15.0
 */
class StatisticsCalculator {
private:
    vector<double> data;  ///< Stores all data points for statistical analysis

public:
    /**
     * Constructor creates an empty statistics calculator ready for data input.
     * The internal data vector is automatically initialized as empty.
     */
    StatisticsCalculator() {
        // Constructor implementation (no additional setup needed)
        // The vector is automatically initialized as empty
    }

    /**
     * Adds a new data point to the statistical data set.
     * @param value Numeric value to add to the data set
     *
     * Example: addValue(15.5) adds 15.5 to the data set
     * Note: Data points are stored in the order they are added
     */
    void addValue(double value) {
        // Add the new value to the end of the data vector
        data.push_back(value);
    }

    /**
     * Calculates the arithmetic mean (average) of all data points.
     * @return The mean value of the data set
     * @throws runtime_error if no data points have been added
     *
     * Formula: mean = (sum of all values) / (number of values)
     * Example: For data set {10, 20, 30}, mean = 60/3 = 20.0
     */
    double calculateMean() const {
        if (data.empty()) {
            throw runtime_error("Cannot calculate mean of empty data set");
        }

        // Sum all values in the data set
        double sum = 0.0;
        for (double value : data) {
            sum += value;
        }

        // Divide sum by count to get average
        return sum / data.size();
    }

    /**
     * Finds the smallest value in the data set.
     * @return The minimum value among all data points
     * @throws runtime_error if no data points have been added
     *
     * Algorithm: Linear search through all values to find the smallest
     * Example: For data set {10, 5, 20, 3}, minimum = 3
     */
    double findMinimum() const {
        if (data.empty()) {
            throw runtime_error("Cannot find minimum of empty data set");
        }

        // Start with first value as initial minimum candidate
        double minValue = data[0];

        // Compare each subsequent value to find smaller ones
        for (size_t i = 1; i < data.size(); i++) {
            if (data[i] < minValue) {
                minValue = data[i];  // Update minimum when smaller value found
            }
        }

        return minValue;
    }

    /**
     * Finds the largest value in the data set.
     * @return The maximum value among all data points
     * @throws runtime_error if no data points have been added
     *
     * Algorithm: Linear search through all values to find the largest
     * Example: For data set {10, 5, 20, 3}, maximum = 20
     */
    double findMaximum() const {
        if (data.empty()) {
            throw runtime_error("Cannot find maximum of empty data set");
        }

        // Start with first value as initial maximum candidate
        double maxValue = data[0];

        // Compare each subsequent value to find larger ones
        for (size_t i = 1; i < data.size(); i++) {
            if (data[i] > maxValue) {
                maxValue = data[i];  // Update maximum when larger value found
            }
        }

        return maxValue;
    }

    /**
     * Returns the number of data points currently in the data set.
     * @return Count of values in the data set
     *
     * Useful for checking if enough data exists for meaningful statistics
     */
    size_t getDataCount() const {
        return data.size();
    }

    /**
     * Removes all data points from the calculator, preparing for new data set.
     * Use this when you want to start fresh with new statistical analysis.
     */
    void clearData() {
        data.clear();
    }
};

/**
 * Validates that a floating-point number is valid for calculations.
 * @param number The number to validate
 * @return true if number is valid, false if NaN or infinite
 *
 * This function checks for special floating-point values that could
 * cause problems in calculations or display. Use before storing or
 * displaying calculation results.
 *
 * Example: isValidNumber(5.0) returns true, isValidNumber(sqrt(-1)) returns false
 */
bool isValidNumber(double number) {
    // Check for Not-a-Number (NaN) and infinite values
    // These can result from invalid operations like sqrt(-1) or 1.0/0.0
    return !isnan(number) && !isinf(number);
}

/**
 * Formats a numeric result for display with specified decimal places.
 * @param result The number to format
 * @param decimalPlaces Non-negative number of decimal places to retain; passed explicitly
 * @return Formatted string representation of the number
 *
 * This function provides basic formatting for displaying calculation results.
 * Invalid numbers (NaN, infinity) are converted to error messages.
 *
 * Example: formatResult(3.14159, 2) returns "3.14"
 * Note: This is a simplified implementation; production code might use sprintf or streams
 *
 * ---
 *
 * Formatea un resultado numérico para su visualización con un número especificado de decimales.
 * @param result El número a formatear
 * @param decimalPlaces Número no negativo de lugares decimales a retener; pasado explícitamente
 * @return Representación en cadena de caracteres del número formateado
 *
 * Esta función proporciona un formato básico para mostrar resultados de cálculos.
 * Los números inválidos (NaN, infinito) se convierten en mensajes de error.
 *
 * Ejemplo: formatResult(3.14159, 2) devuelve "3.14"
 * Nota: Esta es una implementación simplificada; el código de producción podría usar sprintf o streams
 */
string formatResult(double result, int decimalPlaces) {
    // First check if the number is valid for display
    if (!isValidNumber(result)) {
        return "Error: Invalid number";
    }

    // Convert to string using standard library function
    string formatted = to_string(result);

    // Find decimal point and truncate to desired precision
    size_t decimal_pos = formatted.find('.');
    if (decimal_pos != string::npos &&
		formatted.length() > decimal_pos + decimalPlaces + 1) {  
		formatted = formatted.substr(0, decimal_pos + decimalPlaces + 1);  // second argument is the amount of characters
    }

    return formatted;
}

/**
 * Main function demonstrates the calculator library functionality.
 *
 * This program shows how to use both Calculator and StatisticsCalculator
 * classes, including basic operations, error handling, and statistical
 * analysis. It serves as both a test and a usage example.
 *
 * The demonstration includes:
 * - Basic arithmetic operations
 * - Memory storage and retrieval
 * - Advanced mathematical functions
 * - Statistical calculations on sample data
 * - Error handling examples
 */
int main() {
    cout << "Calculator Library Documentation Demo" << endl;
    cout << "====================================" << endl;

    // Create a calculator instance for basic operations
    Calculator calc;

    cout << "\nBasic Arithmetic Operations:" << endl;

    // Demonstrate each arithmetic operation with clear examples
    try {
        // Addition: combining two positive numbers
        double result1 = calc.add(10.0, 5.0);
        cout << "10 + 5 = " << formatResult(result1, 2) << endl;

        // Subtraction: taking away smaller from larger number
        double result2 = calc.subtract(10.0, 3.0);
        cout << "10 - 3 = " << formatResult(result2, 2) << endl;

        // Multiplication: scaling one number by another
        double result3 = calc.multiply(4.0, 2.5);
        cout << "4 * 2.5 = " << formatResult(result3, 2) << endl;

        // Division: splitting one number by another
        double result4 = calc.divide(15.0, 3.0);
        cout << "15 / 3 = " << formatResult(result4, 2) << endl;

        // Demonstrate memory operations by storing and retrieving a result
        calc.storeInMemory(result4);
        cout << "Stored " << formatResult(result4, 2) << " in memory" << endl;
        cout << "Memory recall: " << formatResult(calc.recallFromMemory(), 2) << endl;

        // Show advanced mathematical functions
        double sqrtResult = calc.squareRoot(16.0);
        cout << "Square root of 16 = " << formatResult(sqrtResult, 2) << endl;

        double powerResult = calc.power(2.0, 3.0);
        cout << "2^3 = " << formatResult(powerResult, 2) << endl;

    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    // Demonstrate statistical calculations with a sample data set
    cout << "\nStatistics Operations:" << endl;

    StatisticsCalculator stats;

    // Add sample data representing test scores or measurements
    vector<double> sampleData = { 1.5, 2.3, 1.8, 3.1, 2.7, 1.9, 2.4 };

    // Load each data point into the statistics calculator
    for (double value : sampleData) {
        stats.addValue(value);
    }

    cout << "Data points: " << stats.getDataCount() << endl;

    try {
        // Calculate and display key statistical measures
        cout << "Mean: " << formatResult(stats.calculateMean(), 2) << endl;
        cout << "Minimum: " << formatResult(stats.findMinimum(), 2) << endl;
        cout << "Maximum: " << formatResult(stats.findMaximum(), 2) << endl;
    }
    catch (const exception& e) {
        cout << "Statistics error: " << e.what() << endl;
    }

    cout << "\nDocumentation demo completed!" << endl;

    return 0;
}

/*
VALIDATION CHECKLIST COMPLETED:
- File header includes comprehensive purpose, author, date, and library description

- Class-level documentation explains purpose, usage patterns, and important notes

- Function documentation includes parameter descriptions, return values, and examples

- Complex algorithms have step-by-step explanations with comments

- Error conditions are documented with specific exception types and causes

- Memory and data management strategies are clearly explained

- Utility functions have clear purpose statements and usage examples

- Main function demonstrates comprehensive library usage with detailed comments

- Comments explain the "why" behind code decisions, not just the "what"

- Documentation follows consistent format using proper comment styles throughout

- Mathematical operations include formula explanations and domain restrictions

- Thread safety and concurrency considerations are documented where relevant

COMMON MISTAKES ADDRESSED:
- Avoided redundant comments that just restate the code
- Focused on explaining purpose and reasoning rather than obvious operations
- Included parameter types and constraints in function documentation
- Added usage examples for complex or non-obvious functions
- Documented error conditions and exception handling clearly
- Explained mathematical concepts for users unfamiliar with the operations
- Used consistent documentation format throughout the entire file
- Added file-level documentation explaining the overall library structure
*/