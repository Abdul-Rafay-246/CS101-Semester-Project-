#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void signUp() {
    string userId, password, confirmPassword;
    cout << "Sign Up\n";
    cout << "Enter User ID: ";
    cin >> userId;
    cout << "Enter Password: ";
    cin >> password;
    cout << "Confirm Password: ";
    cin >> confirmPassword;

    if (password != confirmPassword) {
        cout << "Passwords do not match. Try again.\n";
        return;
    }

    // Save user details to file
    ofstream outFile("user_data.txt", ios::app);
    if (outFile.is_open()) {
        outFile << userId << " " << password << endl;
        cout << "Sign up successful!\n";
    } else {
        cout << "Error saving user details ! , Please try again \n";
    }
    outFile.close();
}

void login() {
    string userId, password, storedUserId, storedPassword;
    bool loginSuccess = false;

    cout << "Login\n";
    cout << "Enter User ID: ";
    cin >> userId;
    cout << "Enter Password: ";
    cin >> password;

    // Read user details from file
    ifstream inFile("user_data.txt");
    if (inFile.is_open()) {
        while (inFile >> storedUserId >> storedPassword) {
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
        cout << "Invalid User ID or Password. Please try again ! \n";
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n --------------Welcome to Personalised student study planner --------\n\n\n";
        
		
		cout << "1.To Sign Up ( Press 1 )\n";
        cout << "2.To Login ( press 2 )\n";
        cout << "3. To Exit the system ( press 3 )\n";
        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                signUp();
                break;
            case 2:
                login();
                break;
            case 3:
                cout << "Thankyou for using this system . Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
