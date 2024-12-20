#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void signUp() {
    string userId, password, confirmPassword, authQuestion, authAnswer;
    cout << "Sign Up\n";
    cout << "Enter User ID: ";
    cin.ignore(); // Clear any leftover input from the buffer
    getline(cin, userId); // Use getline to capture full name or multi-word input
    cout << "Enter Password: ";
    cin >> password;
    cout << "Confirm Password: ";
    cin >> confirmPassword;

    if (password != confirmPassword) {
        cout << "Passwords do not match. Try again.\n";
        return;
    }

    cout << "Choose an authentication question:\n";
    cout << "1. What was your favorite teacher's name?\n";
    cout << "2. What was the name of your primary school?\n";
    cout << "3. What was your pet's name?\n";
    cout << "Enter the question number: ";
    int questionChoice;
    cin >> questionChoice;

    switch (questionChoice) {
        case 1:
            authQuestion = "What was your favorite teacher's name?";
            break;
        case 2:
            authQuestion = "What was the name of your primary school?";
            break;
        case 3:
            authQuestion = "What was your pet's name?";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
            return;
    }

    cout << authQuestion << " ";
    cin.ignore();
    getline(cin, authAnswer);

    // Save user details to file
    ofstream outFile("user_data.txt", ios::app);
    if (outFile.is_open()) {
        outFile << userId << "," << password << "," << authQuestion << "," << authAnswer << endl;
        cout << "Sign up successful!\n";
    } else {
        cout << "Error saving user details! Please try again.\n";
    }
    outFile.close();
}

void login() {
    string userId, password;
    cout << "Login\n";
    cout << "Enter User ID: ";
    cin.ignore(); // Clear any leftover input from the buffer
    getline(cin, userId);
    cout << "Enter Password: ";
    cin >> password;

    ifstream inFile("user_data.txt");
    string line, storedUserId, storedPassword, storedAuthQuestion, storedAuthAnswer;
    bool loginSuccess = false;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            stringstream ss(line);
            getline(ss, storedUserId, ',');
            getline(ss, storedPassword, ',');
            getline(ss, storedAuthQuestion, ',');
            getline(ss, storedAuthAnswer);

            if (userId == storedUserId && password == storedPassword) {
                loginSuccess = true;
                break;
            }
        }
        inFile.close();
    } else {
        cout << "Error opening user data file.\n";
        return;
    }

    if (loginSuccess) {
        cout << "Login successful! Welcome, " << userId << "!\n";
    } else {
        cout << "Invalid User ID or Password. Please try again!\n";
    }
}

void forgotPassword() {
    string userId, authAnswer, newPassword, confirmPassword;
    ifstream inFile("user_data.txt");
    ofstream tempFile("temp_data.txt");
    string line, storedUserId, storedPassword, storedAuthQuestion, storedAuthAnswer;
    bool userFound = false;

    cout << "Forgot Password\n";
    cout << "Enter your User ID: ";
    cin.ignore();
    getline(cin, userId);

    if (inFile.is_open() && tempFile.is_open()) {
        while (getline(inFile, line)) {
            stringstream ss(line);
            getline(ss, storedUserId, ',');
            getline(ss, storedPassword, ',');
            getline(ss, storedAuthQuestion, ',');
            getline(ss, storedAuthAnswer);

            if (userId == storedUserId) {
                userFound = true;
                cout << storedAuthQuestion << " ";
                getline(cin, authAnswer);

                if (authAnswer == storedAuthAnswer) {
                    cout << "Authentication successful! Enter a new password: ";
                    cin >> newPassword;
                    cout << "Confirm new password: ";
                    cin >> confirmPassword;

                    if (newPassword == confirmPassword) {
                        tempFile << storedUserId << "," << newPassword << "," << storedAuthQuestion << "," << storedAuthAnswer << endl;
                        cout << "Password successfully changed!\n";
                    } else {
                        cout << "Passwords do not match. Password not updated.\n";
                        tempFile << line << endl;
                    }
                } else {
                    cout << "Incorrect authentication answer. Password reset failed.\n";
                    tempFile << line << endl;
                }
            } else {
                tempFile << line << endl;
            }
        }
        inFile.close();
        tempFile.close();

        // Replace original file with updated temp file
        remove("user_data.txt");
        rename("temp_data.txt", "user_data.txt");
    } else {
        cout << "Error processing user data file.\n";
    }

    if (!userFound) {
        cout << "User ID not found.\n";
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n-------------- Welcome to Personalized Student Study Planner --------------\n\n";
        cout << "1. To Sign Up (Press 1)\n";
        cout << "2. To Login (Press 2)\n";
        cout << "3. Forgot Password (Press 3)\n";
        cout << "4. To Exit the System (Press 4)\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                signUp();
                break;
            case 2:
                login();
                break;
            case 3:
                forgotPassword();
                break;
            case 4:
                cout << "Thank you for using this system. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
