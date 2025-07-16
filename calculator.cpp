#include "calculator.h"
#include <cmath>
#include <limits>

bool ReadNumber(Number& result) {
    if (cin >> result) {
        return true;
    } else {
        cerr << "Error: Numeric operand expected" << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
}

bool RunCalculatorCycle() {
    Number number;
    string command;
    Number current_number;
    char current_operation = '\0';
    Number result = 0.0;
    bool has_result = false;
    Number number_memory;
    bool in_memory = false;
    
    if (!ReadNumber(number)) {
        return false;
    }
    
    while (true) {
        if (!(cin >> command)) {
            cerr << "Error: Unknown token " << command << endl;
            break;
        }

        if (command == "q") {
            break;
        } else if (command == "c") {
            number = 0;
            result = 0;
            has_result = false;
            continue;
        } else if (command == "=") {
            cout << number << endl;
            continue;
        } else if (command == ":") {
            if (!ReadNumber(current_number)) {
                break;
            }
            number = current_number;
            continue;
        }

        // Обработка команд сохранения и загрузки без ожидания числа
        if (command == "s") {
            number_memory = number;
            in_memory = true;
            continue; // Пропускаем чтение числа
        } else if (command == "l") {
            if (in_memory) {
                number = number_memory;
            } else {
                cerr << "Error: Memory is empty" << endl;
                break;
            }
            continue; // Пропускаем чтение числа
        }

        // Читаем число только если это не s или l
        if (!ReadNumber(current_number)) {
            break;
        }

        if (command == "*" || command == "/") {
            if (command == "/" && current_number == 0) {
                number = std::numeric_limits<double>::infinity();
            } else {
                number = (command == "*") ? number * current_number : number / current_number;
            }
        } else if (command == "+" || command == "-") {
            if (has_result) {
                if (current_operation == '+') {
                    result += number;
                } else if (current_operation == '-') {
                    result -= number;
                }
                number = result;
            }
            current_operation = command[0];
            result = number;
            number = current_number;
            has_result = true;
        } else if (command == "**") {
            number = pow(number, current_number);
        } else {
            cerr << "Error: Unknown token " << command << endl;
            break;
        }

        // Обработка накопленных операций
        if (has_result && current_operation != '\0') {
            if (current_operation == '+') {
                result += number;
            } else if (current_operation == '-') {
                result -= number;
            }
            number = result;
            has_result = false;
            current_operation = '\0';
        }
    }
    
    return true;
}
