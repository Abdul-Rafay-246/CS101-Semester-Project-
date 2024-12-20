#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

void signUp()
{
    string userId, password, confirmPassword, authQuestion, authAnswer;
    cout << "Sign Up\n";
    cout << "Enter User ID: ";
    cin.ignore();         // Clear any leftover input from the buffer
    getline(cin, userId); // Use getline to capture full name or multi-word input
    cout << "Enter Password: ";
    cin >> password;
    cout << "Confirm Password: ";
    cin >> confirmPassword;

    if (password != confirmPassword)
    {
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

    switch (questionChoice)
    {
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
    if (outFile.is_open())
    {
        outFile << userId << "," << password << "," << authQuestion << "," << authAnswer << endl;
        cout << "Sign up successful!\n";
    }
    else
    {
        cout << "Error saving user details! Please try again.\n";
    }
    outFile.close();
}

void login()
{
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

    if (inFile.is_open())
    {
        while (getline(inFile, line))
        {
            stringstream ss(line);
            getline(ss, storedUserId, ',');
            getline(ss, storedPassword, ',');
            getline(ss, storedAuthQuestion, ',');
            getline(ss, storedAuthAnswer);

            if (userId == storedUserId && password == storedPassword)
            {
                loginSuccess = true;
                break;
            }
        }
        inFile.close();
    }
    else
    {
        cout << "Error opening user data file.\n";
        return;
    }

    if (loginSuccess)
    {
        cout << "Login successful! Welcome, " << userId << "!\n";
    }
    else
    {
        cout << "Invalid User ID or Password. Please try again!\n";
    }
}

void forgotPassword()
{
    string userId, authAnswer, newPassword, confirmPassword;
    ifstream inFile("user_data.txt");
    ofstream tempFile("temp_data.txt");
    string line, storedUserId, storedPassword, storedAuthQuestion, storedAuthAnswer;
    bool userFound = false;

    cout << "Forgot Password\n";
    cout << "Enter your User ID: ";
    cin.ignore();
    getline(cin, userId);

    if (inFile.is_open() && tempFile.is_open())
    {
        while (getline(inFile, line))
        {
            stringstream ss(line);
            getline(ss, storedUserId, ',');
            getline(ss, storedPassword, ',');
            getline(ss, storedAuthQuestion, ',');
            getline(ss, storedAuthAnswer);

            if (userId == storedUserId)
            {
                userFound = true;
                cout << storedAuthQuestion << " ";
                getline(cin, authAnswer);

                if (authAnswer == storedAuthAnswer)
                {
                    cout << "Authentication successful! Enter a new password: ";
                    cin >> newPassword;
                    cout << "Confirm new password: ";
                    cin >> confirmPassword;

                    if (newPassword == confirmPassword)
                    {
                        tempFile << storedUserId << "," << newPassword << "," << storedAuthQuestion << "," << storedAuthAnswer << endl;
                        cout << "Password successfully changed!\n";
                    }
                    else
                    {
                        cout << "Passwords do not match. Password not updated.\n";
                        tempFile << line << endl;
                    }
                }
                else
                {
                    cout << "Incorrect authentication answer. Password reset failed.\n";
                    tempFile << line << endl;
                }
            }
            else
            {
                tempFile << line << endl;
            }
        }
        inFile.close();
        tempFile.close();

        // Replace original file with updated temp file
        remove("user_data.txt");
        rename("temp_data.txt", "user_data.txt");
    }
    else
    {
        cout << "Error processing user data file.\n";
    }

    if (!userFound)
    {
        cout << "User ID not found.\n";
    }
}

int getValidInput(int min, int max)
{
    int choice;
    while (true)
    {
        cin >> choice;

        // Check if the input stream has encountered a failure (non-integer input)
        if (cin.fail())
        {
            cin.clear();                                         // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid number between " << min << " and " << max << ": ";
        }
        else if (choice >= min && choice <= max)
        {
            return choice; // Input is valid and within range
        }
        else
        {
            cout << "Invalid choice. Please enter a number between " << min << " and " << max << ": ";
        }
    }
}

string convertChoiceToRoutine(int choice)
{
    switch (choice)
    {
    case 1:
        return "Morning";
    case 2:
        return "Afternoon";
    case 3:
        return "Evening";
    case 4:
        return "All Day"; // New option for complete availability
    default:
        return "Unavailable"; // Fallback, though this should not occur due to validation
    }
}

int askQuestions(int courseNumber, string courseName)
{
    int points = 0;
    int choice;

    cout << "\n\nLet's get started with Course " << courseNumber << " (" << courseName << ")!\n";

    // Question 1: Have you studied the course previously?
    cout << "1. Have you studied this course before?\n";
    cout << "    1. Yes, I have some prior knowledge\n";
    cout << "    2. No, I'm starting from scratch\n";
    cout << "Your choice: ";
    choice = getValidInput(1, 2);
    if (choice == 2)
        points += 10;

    // Question 2: Grade last time in the course
    cout << "\n2. What was your grade last time you studied this course? (if applicable)\n";
    cout << "    1. A  (I nailed it!)\n";
    cout << "    2. B  (Could have done better, but decent.)\n";
    cout << "    3. C  (Not the best, but I got through.)\n";
    cout << "    4. D or F (Oops, major struggle!)\n";
    cout << "    5. Not Applicable.\n";
    cout << "Your choice: ";
    choice = getValidInput(1, 5);
    if (choice == 2)
        points += 4;
    else if (choice == 3)
        points += 6;
    else if (choice == 4)
        points += 10;

    // Question 3: Complexity level
    cout << "\n3. How would you rate the complexity of this course?\n";
    cout << "    1. Easy (I can breeze through this!) \n";
    cout << "    2. Moderate (It'll be a challenge, but I'm up for it.) \n";
    cout << "    3. Hard  (This is going to be a tough one!) \n";
    cout << "Your choice: ";
    choice = getValidInput(1, 3);
    if (choice == 2)
        points += 5;
    else if (choice == 3)
        points += 10;

    // Question 4: Credit hours
    cout << "\n4. How many credit hours is this course worth?\n";
    cout << "    1. 1-2 (Quick and easy.)\n";
    cout << "    2. 3-4 (Average workload.)\n";
    cout << "    3. 5 or more (I'll need to dedicate some serious time!)\n";
    cout << "Your choice: ";
    choice = getValidInput(1, 3);
    if (choice == 3)
        points += 5;

    // Question 5: Is this course core for your degree/major?
    cout << "\n5. Is this course a core subject for your degree/major?\n";
    cout << "    1. Yes (It's essential to my field.)\n";
    cout << "    2. No (Just an elective or side course.)\n";
    cout << "Your choice: ";
    choice = getValidInput(1, 2);
    if (choice == 2)
        points += 5;

    return points;
}

void generateStudyPlanner(string courseNames[], int points[], int numCourses, string routine[][3], int dailyHours[])
{
    ofstream outFile("StudyPlanner.txt");

    if (!outFile)
    {
        cerr << "Error creating file!" << endl;
        return;
    }

    outFile << "Personalized Weekly Study Planner:\n";
    outFile << "----------------------------------\n";

    string daysOfWeek[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    int totalDailyHours[7]; // To keep track of remaining available hours for each day

    // Initialize totalDailyHours with user's available hours for each day
    for (int i = 0; i < 7; i++)
    {
        totalDailyHours[i] = dailyHours[i];
    }

    for (int i = 0; i < numCourses; i++)
    {
        outFile << "\nCourse " << (i + 1) << " (" << courseNames[i] << "):\n";

        // Determine recommended study hours per week based on points
        int weeklyHours;
        if (points[i] >= 30)
        {
            weeklyHours = 6; // High priority: 6 hours
        }
        else if (points[i] >= 20)
        {
            weeklyHours = 4; // Moderate priority: 4 hours
        }
        else
        {
            weeklyHours = 2; // Low priority: 2 hours
        }

        outFile << "Recommended Total Study Hours: " << weeklyHours << " hours/week\n";
        outFile << "Suggested Weekly Schedule:\n";

        int hoursLeft = weeklyHours;

        for (int j = 0; j < 7 && hoursLeft > 0; j++)
        {
            // Skip days marked as unavailable
            if (dailyHours[j] == 0)
                continue;

            for (int slot = 0; slot < 3 && hoursLeft > 0; slot++)
            {
                if (routine[j][slot].empty() || routine[j][slot] == "Unavailable")
                    continue;

                int maxDailyHours = (routine[j][slot] == "All Day") ? 6 : dailyHours[j];
                int dailyStudyTime = min(hoursLeft, maxDailyHours);

                if (dailyStudyTime > 0 && dailyStudyTime <= totalDailyHours[j])
                {
                    outFile << "  " << daysOfWeek[j] << ": Study for " << dailyStudyTime
                            << " hour(s) in the " << routine[j][slot] << ".\n";
                    hoursLeft -= dailyStudyTime;
                    totalDailyHours[j] -= dailyStudyTime; // Update the remaining available hours for the day
                }
            }
        }

        // Redistribute remaining hours, if any
        if (hoursLeft > 0)
        {
            outFile << "  Remaining " << hoursLeft << " hour(s) need to be manually scheduled.\n";
        }
    }

    outFile.close();
    cout << "\nStudy planner with a weekly schedule has been saved to 'StudyPlanner.txt'.\n";
}

int main()
{
    bool isLoggedIn = false; // Tracks if the user is logged in
    int choice;

    while (true)
    {
        cout << "\n-------------- Welcome to Personalized Student Study Planner --------------\n";
        cout << "1. Sign Up\n";
        cout << "2. Login\n";
        cout << "3. Forgot Password\n";
        cout << "4. Generate Study Planner (Login Required)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        choice = getValidInput(1, 5);

        switch (choice)
        {
        case 1:
            signUp();
            break;
        case 2:
            login();
            isLoggedIn = true; // Set login state to true on successful login
            break;
        case 3:
            forgotPassword();
            break;
        case 4:
            if (isLoggedIn)
            {
                // Get courses and routines from the user
                cout << "Generating Study Planner...\n";

                int numCourses;
                cout << "Enter number of courses: ";
                numCourses = getValidInput(1, 10);

                string courseNames[numCourses];
                int points[numCourses];
                for (int i = 0; i < numCourses; i++)
                {
                    cout << "Enter name of course " << i + 1 << ": ";
                    cin.ignore();
                    getline(cin, courseNames[i]);
                    points[i] = askQuestions(i + 1, courseNames[i]);
                }

                string routine[7][3]; // Allows up to 3 time slots per day
                int dailyHours[7];    // Keeps track of total free hours per day
                string daysOfWeek[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

                for (int i = 0; i < 7; i++)
                {
                    cout << "Availability on " << daysOfWeek[i] << ":\n";
                    dailyHours[i] = 0;           // Initialize daily hours
                    bool dayUnavailable = false; // Flag to track if the day is unavailable

                    for (int slot = 0; slot < 3; slot++)
                    {
                        if (dayUnavailable)
                            break; // Don't ask again if the day is marked unavailable

                        cout << "    1. Morning\n";
                        cout << "    2. Afternoon\n";
                        cout << "    3. Evening\n";
                        cout << "    4. All Day\n";
                        cout << "    5. Unavailable\n";
                        cout << "Enter your choice (or 0 to stop): ";
                        int choice = getValidInput(0, 5);

                        if (choice == 0)
                            break;

                        if (choice == 5)
                        {
                            routine[i][slot] = "Unavailable";
                            dayUnavailable = true; // Mark the day as unavailable and stop asking for more slots
                            break;
                        }

                        // Prevent re-selection of the same time slot
                        bool invalidSelection = false;
                        for (int prevSlot = 0; prevSlot < 3; prevSlot++)
                        {
                            if ((choice == 1 && routine[i][prevSlot] == "Morning") ||
                                (choice == 2 && routine[i][prevSlot] == "Afternoon") ||
                                (choice == 3 && routine[i][prevSlot] == "Evening"))
                            {
                                invalidSelection = true;
                                break;
                            }
                        }

                        if (invalidSelection)
                        {
                            cout << "Invalid input: You have already selected this time slot. Please choose a different one.\n";
                            // Give the user a second chance to select a valid slot
                            slot--; // Keep the same slot index to retry
                            continue;
                        }

                        routine[i][slot] = convertChoiceToRoutine(choice);

                        if (choice == 4) // All Day
                        {
                            dailyHours[i] = 6;
                            break; // No further slots needed for All Day
                        }
                        else if (choice != 5) // Not unavailable
                        {
                            cout << "Enter number of hours you can study in this time slot: ";
                            dailyHours[i] += getValidInput(1, 6);
                        }
                    }
                }

                generateStudyPlanner(courseNames, points, numCourses, routine, dailyHours);
            }
            else
            {
                cout << "You must log in to access this feature.\n";
            }
            break;
        case 5:
            cout << "Exiting the application. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    }
}
