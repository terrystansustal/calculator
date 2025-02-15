#include <iostream>   // For input and output operations
#include <vector>      // To store calculation history
#include <fstream>     // For reading and writing to files
#include <sstream>     // For converting numbers to strings
#include <limits>      // To handle invalid input properly

using namespace std;

string numToStr(double num) {
    ostringstream stream;
    stream << num;
    return stream.str();
}

// This calculator class will be handling arithmetic operations and save the history of the entered inputs
class Calculator {
private:
    vector<string> history;  // Stores past calculations for later review

public:
    // This will perform basic arithmetic operations (+, -, *, /) and will display an
    // error message if a user enters an invalid input or if being divided by zero
    double calculate(double a, char op, double b) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': 
                if (b == 0) {  
                    throw runtime_error("Error: Can't divide by zero!"); // to prevent being divided by zero
                }
                return a / b;
            default:
                throw invalid_argument("Error: Unsupported operator."); // Error message to invalid user input
        }
    }

    // saveHistory will save the history of the user's calculation in a text file so that the user
    // can review the file later for personal interest
    void saveHistory(const string &filename) {
        ofstream file(filename);  // Open file for writing
        if (!file) {  // Check if file was successfully opened
            cerr << "Error: Could not open file for writing." << endl;
            return;
        }
        for (const auto &entry : history) {  // Loop through stored history
            file << entry << endl;  // Write each entry to the file
        }
        file.close(); // Close file after writing
        cout << "History saved to " << filename << endl;
    }

    // Adds a new calculation result to the history list
    void addToHistory(const string &entry) {
        history.push_back(entry);
    }

    // This will allow to display all past calculations stored in history
    void showHistory() const {
        if (history.empty()) { // If no history is available
            cout << "No calculations yet." << endl;
        } else {
            cout << "Previous calculations:\n";
            for (const auto &entry : history) { // Display each saved calculation
                cout << entry << endl;
            }
        }
    }
};

int main() {
    Calculator calc;  // Create an instance of the Calculator class
    double num1, num2; // These are the variables for user input
    char op; // To store the operator (+, -, *, /)
    string userInput; // To store user's responses

    cout << "\n";
    cout << "===== Welcome to BYUI Calculator =====\n";

    // I decided to choose a while loop to continuously accept user input
    while (true) {
        cout << "\nEnter an equation (e.g., 5 + 3 or 10 * 10) or type 'exit' to quit: ";
        cin >> num1 >> op >> num2; // This code will read user input

        // This if statement will handle invalid input from the user
        if (cin.fail()) {  
            cin.clear();  // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore incorrect input
            cout << "Invalid input. Please enter a valid equation.\n";
            continue; // This continue will restart the loop and prompt for input again
        }

        try {
            // Perform the calculation
            double result = calc.calculate(num1, op, num2);
            // Format the result into a readable equation string
            string expression = numToStr(num1) + " " + op + " " + numToStr(num2) + " = " + numToStr(result);
            cout << "Result: " << result << endl;
            calc.addToHistory(expression); // Call the addToHistory to save the calculation in the file
        } catch (const exception &e) {  
            // If an error occurs, display the error message
            cout << e.what() << endl;
        }

        // This will ask the user if they want to continue using the calculator
        cout << "Do another calculation? (yes/no): ";
        cin >> userInput;
        if (userInput != "yes") break; // This will end the calculator program if the user doesn't enter "yes"
    }

    // This block of code will ask the user if they want to see the history of calculations
    // This code will call the showHistory()
    cout << "\nView your calculation history? (yes/no): ";
    cin >> userInput;
    if (userInput == "yes") {
        calc.showHistory();
    }

    // This will allow the user to save the calculation history to a file by saying "yes"
    // Call the saveHistory() in order to save the file
    cout << "\nSave history to a file? (yes/no): ";
    cin >> userInput;
    if (userInput == "yes") {
        calc.saveHistory("history.txt"); // Save history to a file
    }

    // This is the end of the program
    cout << "Thanks for using the BYUI Calculator! Goodbye.\n";
    return 0;
}
