#include <iostream>
#include <string>
#include <bitset>
#include <regex>
#include <sstream>
#include <iomanip>

using namespace std;

// this struct stores each field of floating point, Sign bit (1), E bits (8), Mantissa bits (23)
struct FloatStruct {
    unsigned int S;
    unsigned int E;
    unsigned int M;
};

// helper struct to organize whole part and fraction part of the number
struct NumberStruct {
    string wholeString;
    string fractionString;

    unsigned int wholeInt;
    unsigned int fractionInt;

    unsigned int numOfDigitsAfterDecimal;

    unsigned int numerator;
    unsigned int denominator;
};


//********* helper functions **********************//
void convertToFloatPoint(string input, NumberStruct* numStruct, FloatStruct* floatStruct);
string parseInput(FloatStruct* floatStruct);

string removeLeadingSign(string input);
bool getGreaterNumber(string input1, string input2);
void parseNumber(string input, NumberStruct* numStruct);
void displayFloatingPoint(FloatStruct* floatStruct);
void adjustWholePart(NumberStruct* numStruct, FloatStruct* floatStruct);
unsigned int extractMantissa(string fractionString);
//********* helper functions **********************//


//*************** functions definitions ***********************//
void processAddition(string input1, string input2, FloatStruct* floatStruct);
void add(NumberStruct* firstNumStruct, NumberStruct* secondNumStruct, NumberStruct* resultNumStruct);

void processSubtraction(string input1, string input2, FloatStruct* floatStruct, bool firstInputGreaterthanSecondInput);
void subtract(NumberStruct* firstNumStruct, NumberStruct* secondNumStruct, NumberStruct* resultNumStruct, bool firstInputGreaterthanSecondInput);

void processMultiplication(string input1, string input2, FloatStruct* floatStruct);
string parseMultiply(string input1, string input2);
void multiply(string input, NumberStruct* numStruct);
//*************** functions definitions ***********************//


// get both inputs from the user, add them and convert it into floating point representation
void processAddition(string input1, string input2, FloatStruct* floatStruct) {

    unique_ptr<NumberStruct> firstNumStruct = make_unique<NumberStruct>();
    unique_ptr<NumberStruct> SecondNumStruct = make_unique<NumberStruct>();
    unique_ptr<NumberStruct> resultNumStruct = make_unique<NumberStruct>();


    parseNumber(input1, firstNumStruct.get());
    parseNumber(input2, SecondNumStruct.get());

    add(firstNumStruct.get(), SecondNumStruct.get(), resultNumStruct.get());

    adjustWholePart(resultNumStruct.get(), floatStruct);

    if (floatStruct->S == 0) {
        cout << "Result is: " << resultNumStruct->wholeInt << "." << resultNumStruct->fractionString << endl;
    }
    else {
        cout << "Result is: -" << resultNumStruct->wholeInt << "." << resultNumStruct->fractionString << endl;
    }

    displayFloatingPoint(floatStruct);

}
void add(NumberStruct* firstNumStruct, NumberStruct* secondNumStruct, NumberStruct* resultNumStruct) {

    int numOfDigitsAfterDecimal = 0;

    int maxDenominator = 0;
    if (firstNumStruct->numOfDigitsAfterDecimal > secondNumStruct->numOfDigitsAfterDecimal) {
        maxDenominator = firstNumStruct->denominator;
        numOfDigitsAfterDecimal = firstNumStruct->numOfDigitsAfterDecimal;
    }
    else {
        maxDenominator = secondNumStruct->denominator;
        numOfDigitsAfterDecimal = secondNumStruct->numOfDigitsAfterDecimal;
    }

    int user1Total = (firstNumStruct->wholeInt * maxDenominator) + (firstNumStruct->numerator * (maxDenominator / firstNumStruct->denominator));
    int user2Total = (secondNumStruct->wholeInt * maxDenominator) + (secondNumStruct->numerator * (maxDenominator / secondNumStruct->denominator));


    int result = user1Total + user2Total;
    int finalWhole = result / maxDenominator;
    int finalFraction = result % maxDenominator;


    // Convert to string and pad with leading zeros
    ostringstream oss;
    oss << setw(numOfDigitsAfterDecimal) << setfill('0') << finalFraction;
    string fractionString = oss.str();


    resultNumStruct->wholeInt = finalWhole;
    resultNumStruct->fractionInt = finalFraction;
    resultNumStruct->fractionString = fractionString;
}


// get both inputs from the user, subtract them and convert it into floating point representation
void processSubtraction(string input1, string input2, FloatStruct* floatStruct, bool firstInputGreaterthanSecondInput) {

    unique_ptr<NumberStruct> firstNumStruct = make_unique<NumberStruct>();
    unique_ptr<NumberStruct> SecondNumStruct = make_unique<NumberStruct>();
    unique_ptr<NumberStruct> resultNumStruct = make_unique<NumberStruct>();


    parseNumber(input1, firstNumStruct.get());
    parseNumber(input2, SecondNumStruct.get());

    subtract(firstNumStruct.get(), SecondNumStruct.get(), resultNumStruct.get(), firstInputGreaterthanSecondInput);

    adjustWholePart(resultNumStruct.get(), floatStruct);

    if (floatStruct->S == 0) {
        cout << "Result is: " << resultNumStruct->wholeInt << "." << resultNumStruct->fractionString << endl;
    }
    else {
        cout << "Result is: -" << resultNumStruct->wholeInt << "." << resultNumStruct->fractionString << endl;
    }

    displayFloatingPoint(floatStruct);

}
void subtract(NumberStruct* firstNumStruct, NumberStruct* secondNumStruct, NumberStruct* resultNumStruct, bool firstInputGreaterthanSecondInput) {

    int numOfDigitsAfterDecimal = 0;

    int maxDenominator = 0;
    if (firstNumStruct->numOfDigitsAfterDecimal > secondNumStruct->numOfDigitsAfterDecimal) {
        maxDenominator = firstNumStruct->denominator;
        numOfDigitsAfterDecimal = firstNumStruct->numOfDigitsAfterDecimal;
    }
    else {
        maxDenominator = secondNumStruct->denominator;
        numOfDigitsAfterDecimal = secondNumStruct->numOfDigitsAfterDecimal;
    }

    int user1Total = (firstNumStruct->wholeInt * maxDenominator) + (firstNumStruct->numerator * (maxDenominator / firstNumStruct->denominator));
    int user2Total = (secondNumStruct->wholeInt * maxDenominator) + (secondNumStruct->numerator * (maxDenominator / secondNumStruct->denominator));


    int result;
    if (firstInputGreaterthanSecondInput == true) {
        result = user1Total - user2Total;
    }
    else {
        result = user2Total - user1Total;
    }

    int finalWhole = result / maxDenominator;
    int finalFraction = result % maxDenominator;


    // Convert to string and pad with leading zeros
    ostringstream oss;
    oss << setw(numOfDigitsAfterDecimal) << setfill('0') << finalFraction;
    string fractionString = oss.str();


    resultNumStruct->wholeInt = finalWhole;
    resultNumStruct->fractionInt = finalFraction;
    resultNumStruct->fractionString = fractionString;
}


// get inputs from the user, parse the numbers and multiply to get the final result
// then convert the result into floating point representation
void processMultiplication(string input1, string input2, FloatStruct* floatStruct) {

    unique_ptr<NumberStruct> numStruct = make_unique<NumberStruct>();

    string output = parseMultiply(input1, input2);

    multiply(output, numStruct.get());

    adjustWholePart(numStruct.get(), floatStruct);

    if (floatStruct->S == 0) {
        cout << "Result is: " << numStruct->wholeInt << "." << numStruct->fractionString << endl;
    }
    else {
        cout << "Result is: -" << numStruct->wholeInt << "." << numStruct->fractionString << endl;
    }

    displayFloatingPoint(floatStruct);
}
string parseMultiply(string input1, string input2) {

    int decimalPosition1 = input1.find('.');
    int numOfDigitsAfterDecimal1 = 0;


    string wholePart1;
    string fractionPart1;

    if (decimalPosition1 < 0) {
        wholePart1 = input1;
        fractionPart1 = "";
    }
    else {
        wholePart1 = input1.substr(0, decimalPosition1);
        fractionPart1 = input1.substr(decimalPosition1 + 1);
        numOfDigitsAfterDecimal1 = input1.length() - input1.find('.') - 1;
    }


    //====================================================
    //====================================================

    int decimalPosition2 = input2.find('.');
    int numOfDigitsAfterDecimal2 = 0;

    string wholePart2;
    string fractionPart2;

    if (decimalPosition2 < 0) {
        wholePart2 = input2;
        fractionPart2 = "";
    }
    else {
        wholePart2 = input2.substr(0, decimalPosition2);
        fractionPart2 = input2.substr(decimalPosition2 + 1);
        numOfDigitsAfterDecimal2 = input2.length() - input2.find('.') - 1;
    }

    string firstNumberString = wholePart1 + fractionPart1;
    string secondNumberString = wholePart2 + fractionPart2;


    unsigned long long firstNumberInt = stoi(firstNumberString);
    unsigned long long secondNumberInt = stoi(secondNumberString);


    unsigned long long result = firstNumberInt * secondNumberInt;

    int numOfDigitsAfterDecimal = numOfDigitsAfterDecimal1 + numOfDigitsAfterDecimal2;


    string finalValue = to_string(result);

    int insertPos = finalValue.length() - numOfDigitsAfterDecimal;


    if (numOfDigitsAfterDecimal != 0) { finalValue.insert(insertPos, "."); }


    return finalValue;
}
void multiply(string input, NumberStruct* numStruct) {
    int decimalPosition = input.find('.');

    string wholePart;
    string fractionPart;

    if (decimalPosition < 0) {
        wholePart = input;
        fractionPart = "0";
    }
    else {
        wholePart = input.substr(0, decimalPosition);
        fractionPart = input.substr(decimalPosition + 1);
    }


    numStruct->wholeString = wholePart;
    numStruct->fractionString = fractionPart;

    numStruct->wholeInt = stoi(wholePart);
    numStruct->fractionInt = stoi(fractionPart);

    numStruct->numOfDigitsAfterDecimal = fractionPart.length();

    numStruct->numerator = stoi(fractionPart);
    numStruct->denominator = pow(10, fractionPart.length());
}



// main function
int main() {

    unique_ptr<NumberStruct> numStruct = make_unique<NumberStruct>();
    unique_ptr<FloatStruct> floatStruct = make_unique<FloatStruct>();
    string decimalNumber;

    int choice;

    do {

        cout << "\n=== Menu ===\n";
        cout << "1. Convert decimal number to floating point.\n";
        cout << "2. Add two decimal point numbers\n";
        cout << "3. Subtract two decimal point numbers\n";
        cout << "4. Multiply two decimal point numbers\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Clear input buffer in case of invalid input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        if (choice == 1) {
            decimalNumber = parseInput(floatStruct.get());
            convertToFloatPoint(decimalNumber, numStruct.get(), floatStruct.get());
            displayFloatingPoint(floatStruct.get());
        }

        if (choice == 5) {
            cout << "Exiting...\n";
            return 0;
        }

        if (choice == 2 || choice == 3 || choice == 4) {

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            string userInput;
            cout << endl << "Enter two numbers: ";
            getline(cin, userInput);

            stringstream ss(userInput);
            string input1, input2;
            char operation;

            ss >> input1 >> operation >> input2;

            if (input1.length() == 0 || input2.length() == 0) {
                cout << "Error, invalid format\n" << endl;
                return -1;
            }

            // (1 + 2) or (1 - 2) or (1 * 2)
            if (input1[0] != '-' && input2[0] != '-') {

                if (operation == '+') {
                    floatStruct->S = 0;
                    processAddition(input1, input2, floatStruct.get());
                }

                if (operation == '-') {
                    bool firstInputGreaterthanSecondInput = getGreaterNumber(input1, input2);
                    if (firstInputGreaterthanSecondInput == true) {
                        floatStruct->S = 0;
                        processSubtraction(input1, input2, floatStruct.get(), true);
                    }
                    else {
                        floatStruct->S = 1;
                        processSubtraction(input1, input2, floatStruct.get(), false);
                    }
                }

                if (operation == '*') {
                    floatStruct->S = 0;
                    processMultiplication(input1, input2, floatStruct.get());
                }

            }


            // (1 + -2) or (1 - -2) or (1 * -2)
            if (input1[0] != '-' && input2[0] == '-') {
                input2 = removeLeadingSign(input2);

                if (operation == '+') {
                    bool firstInputGreaterthanSecondInput = getGreaterNumber(input1, input2);
                    if (firstInputGreaterthanSecondInput == true) {
                        floatStruct->S = 0;
                        processSubtraction(input1, input2, floatStruct.get(), true);
                    }
                    else {
                        floatStruct->S = 1;
                        processSubtraction(input1, input2, floatStruct.get(), false);
                    }
                }
                if (operation == '-') {
                    floatStruct->S = 0;
                    processAddition(input1, input2, floatStruct.get());
                }
                if (operation == '*') {
                    floatStruct->S = 1;
                    processMultiplication(input1, input2, floatStruct.get());
                }
            }


            // (-1 + 2) or (-1 - 2) or (-1 * 2)
            if (input1[0] == '-' && input2[0] != '-') {
                input1 = removeLeadingSign(input1);

                if (operation == '+') {
                    // NOTE: I reversed the signs because i am using absolute value in getGreatNumber() function
                    bool firstInputGreaterthanSecondInput = getGreaterNumber(input1, input2);
                    if (firstInputGreaterthanSecondInput == true) {
                        floatStruct->S = 1;
                        processSubtraction(input1, input2, floatStruct.get(), true);
                    }
                    else {
                        floatStruct->S = 0;
                        processSubtraction(input1, input2, floatStruct.get(), false);
                    }
                }
                if (operation == '-') {
                    floatStruct->S = 1;
                    processAddition(input1, input2, floatStruct.get());
                }
                if (operation == '*') {
                    floatStruct->S = 1;
                    processMultiplication(input1, input2, floatStruct.get());
                }

            }


            // (-1 + -2) or (-1 - -2) or (-1 * -2)
            if (input1[0] == '-' && input2[0] == '-') {
                input1 = removeLeadingSign(input1);
                input2 = removeLeadingSign(input2);

                if (operation == '+') {
                    floatStruct->S = 1;
                    processAddition(input1, input2, floatStruct.get());
                }
                if (operation == '-') {
                    // NOTE: I reversed the signs because i am using absolute value in getGreatNumber() function
                    bool firstInputGreaterthanSecondInput = getGreaterNumber(input1, input2);
                    if (firstInputGreaterthanSecondInput == true) {
                        floatStruct->S = 1;
                        processSubtraction(input1, input2, floatStruct.get(), true);
                    }
                    else {
                        floatStruct->S = 0;
                        processSubtraction(input1, input2, floatStruct.get(), false);
                    }
                }
                if (operation == '*') {
                    floatStruct->S = 0;
                    processMultiplication(input1, input2, floatStruct.get());
                }

            }

        }


    } while (choice != 5);

    return 0;
}


// these two functions gets the input from the user
// and parses the string into helper struct to organize whole part and fractional part
string parseInput(FloatStruct* floatStruct) {

    string input;
    cout << "\nEnter a decimal number: ";
    cin >> input;

    string sign;
    string number;

    // Regex to match optional sign followed by a decimal number
    regex pattern(R"(^(-?)(\d+(\.\d+)?$))");
    smatch match;

    if (regex_match(input, match, pattern)) {
        sign = match[1];   // "-" or empty
        number = match[2]; // e.g., "1.00", "52.00005"
    }
    else {
        cout << "Error: Invalid format. Please enter a decimal like -2.03 or 1.0" << endl;
    }

    if (sign == "-") {
        floatStruct->S = 1;
    }
    else {
        floatStruct->S = 0;
    }
    return number;
}
void convertToFloatPoint(string input, NumberStruct* numStruct, FloatStruct* floatStruct) {

    int decimalPosition = input.find('.');

    string wholePart;
    string fractionPart;

    if (decimalPosition < 0) {
        wholePart = input;
        fractionPart = "0";
    }
    else {
        wholePart = input.substr(0, decimalPosition);
        fractionPart = input.substr(decimalPosition + 1);
    }


    numStruct->wholeString = wholePart;
    numStruct->fractionString = fractionPart;

    numStruct->wholeInt = stoi(wholePart);
    numStruct->fractionInt = stoi(fractionPart);

    numStruct->numOfDigitsAfterDecimal = fractionPart.length();

    numStruct->numerator = stoi(fractionPart);
    numStruct->denominator = pow(10, fractionPart.length());

    adjustWholePart(numStruct, floatStruct);
}


// helper function which removes the leading sign from numbers
string removeLeadingSign(string input) {

    string cleanedInput;

    if (!input.empty() && input[0] == '-') {
        // Substr extracts a portion of the string starting from index 1 (after the '-')
        cleanedInput = input.substr(1);
    }
    else {
        cleanedInput = input;
    }

    return cleanedInput;
}
// helper function to get the greater number to make subtraction easier
bool getGreaterNumber(string input1, string input2) {
    int number1 = stoi(input1);
    int number2 = stoi(input2);
    if (abs(number1) - abs(number2) > 0) {
        return true;
    }
    else {
        return false;
    }
}


// separates the whole part and fraction part of a number and store it in the helper struct
void parseNumber(string input, NumberStruct* numStruct) {

    int decimalPosition = input.find('.');

    string wholePart;
    string fractionPart;

    if (decimalPosition < 0) {
        wholePart = input;
        fractionPart = "0";
    }
    else {
        wholePart = input.substr(0, decimalPosition);
        fractionPart = input.substr(decimalPosition + 1);
    }


    numStruct->wholeString = wholePart;
    numStruct->fractionString = fractionPart;

    numStruct->wholeInt = stoi(wholePart);
    numStruct->fractionInt = stoi(fractionPart);

    numStruct->numOfDigitsAfterDecimal = fractionPart.length();

    numStruct->numerator = stoi(fractionPart);
    numStruct->denominator = pow(10, fractionPart.length());
}
// display the floating point fields
void displayFloatingPoint(FloatStruct* floatStruct) {
    cout << endl << "******************************" << endl;
    cout << "S: " << bitset<1>{floatStruct->S} << endl;
    cout << "E: " << bitset<8>{floatStruct->E} << endl;
    cout << "Mantissa: " << bitset<32>{floatStruct->M} << endl;
    cout << "******************************" << endl;
}


// this function shifts the whole part to the right until it becomes 1
void adjustWholePart(NumberStruct* numStruct, FloatStruct* floatStruct) {

    unsigned int wholeInt = numStruct->wholeInt;
    unsigned int mantissa = extractMantissa(numStruct->fractionString);

    int exponent = 0;


    unsigned int msbBit = 2147483648;
    unsigned int lsbBit = 1;


    // if whole part is greator than 0
    if (wholeInt > 0) {
        while (wholeInt != 1) {

            if ((wholeInt & 1) == 0) {
                wholeInt = wholeInt >> 1;
                mantissa = mantissa >> 1;
                exponent++;
            }
            else {
                wholeInt = wholeInt >> 1;
                mantissa = mantissa >> 1;
                mantissa = msbBit | mantissa;
                exponent++;
            }

        }
    }


    // if whole part is less than 1
    if (wholeInt < 1) {
        while (wholeInt != 1) {

            if ((mantissa & msbBit) == 0) {
                mantissa = mantissa << 1;
                wholeInt = wholeInt << 1;
                exponent--;
            }
            else {
                mantissa = mantissa << 1;
                wholeInt = wholeInt << 1;
                wholeInt = lsbBit | wholeInt;
                exponent--;
            }

        }
    }

    floatStruct->E = 127 + exponent;
    floatStruct->M = mantissa;
}
// this function extract the mantissa from the fractional part of a number
unsigned int extractMantissa(string fractionString) {

    int countOfNumbersAfterDecimalPoint = fractionString.length();

    unsigned int numerator = stoi(fractionString);
    unsigned int denominator = pow(10, countOfNumbersAfterDecimalPoint);

    unsigned int finalValue = 0;

    unsigned int quotient = -1;
    unsigned int remainder = -1;


    // I set 32 numbers after the decimal point for better precision
    int precision = 32;
    int count = 0;
    while (remainder != 0 && count < precision) {

        int temp = numerator * 2;

        quotient = temp / denominator;
        remainder = temp % denominator;

        numerator = remainder;
        count++;

        // If quotient is 1 then I shift
        // If quotient is 0 then no need
        if (quotient == 1) {
            // I take quotient and shift it right 2^31, 2^30 all the way to 2^16
            // I OR quotient and finalValue to get the final value 
            quotient = quotient << (32 - count);
            finalValue = finalValue | quotient;
        }

    }

    return finalValue;
}