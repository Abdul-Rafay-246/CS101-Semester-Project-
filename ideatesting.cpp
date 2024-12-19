#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to validate input within a range
int getValidInput(int min, int max) {
    int choice;
    while (true) {
        cin >> choice;
        if (choice >= min && choice <= max) {
            return choice;
        } else {
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
        }
    }
}

// Function to convert choice number to routine string
string convertChoiceToRoutine(int choice) {
    switch (choice) {
        case 1: return "Morning";
        case 2: return "Afternoon";
        case 3: return "Evening";
        default: return "Unavailable"; // Fallback, though this should not occur due to validation
    }
}

// Function to ask questions for a course and calculate points
int askQuestions(int courseNumber, string courseName) {
    int points = 0;
    int choice;

    cout << "\n\nLet's get started with Course " << courseNumber << " (" << courseName << ")!\n";

    // Question 1: Have you studied the course previously?
    cout << "1. Have you studied this course before?\n";
    cout << "    1. Yes, I have some prior knowledge\n";
    cout << "    2. No, I’m starting from scratch\n";
    cout << "Your choice: ";
    choice = getValidInput(1, 2);
    if (choice == 2) points += 5;

    // Question 2: Grade last time in the course
    cout << "\n2. What was your grade last time you studied this course? (if applicable)\n";
    cout << "    1. A – I nailed it! 😎\n";
    cout << "    2. B – Could have done better, but decent.\n";
    cout << "    3. C – Not the best, but I got through.\n";
    cout << "    4. D or F – Oops, major struggle! 😬\n";
    cout << "Your choice: ";
    choice = getValidInput(1, 4);
    if (choice == 2) points += 2;
    else if (choice == 3) points += 4;
    else if (choice == 4) points += 6;

    // Question 3: Complexity level
    cout << "\n3. How would you rate the complexity of this course?\n";
    cout << "    1. Easy – I can breeze through this! ✌️\n";
    cout << "    2. Moderate – It’ll be a challenge, but I’m up for it.\n";
    cout << "    3. Hard – This is going to be a tough one! 😰\n";
    cout << "Your choice: ";
    choice = getValidInput(1, 3);
    if (choice == 2) points += 3;
    else if (choice == 3) points += 6;

    // Question 4: Credit hours
    cout << "\n4. How many credit hours is this course worth?\n";
    cout << "    1. 1-2 hours – Quick and easy.\n";
    cout << "    2. 3-4 hours – Average workload.\n";
    cout << "    3. 5 or more hours – I’ll need to dedicate some serious time! ⏰\n";
    cout << "Your choice: ";
    choice = getValidInput(1, 3);
    if (choice <= 2) points += 2;
    else if (choice == 3) points += 4;

    // Question 5: Is this course core for your degree/major?
    cout << "\n5. Is this course a core subject for your degree/major?\n";
    cout << "    1. Yes – It’s essential to my field.\n";
    cout << "    2. No – Just an elective or side course.\n";
    cout << "Your choice: ";
    choice = getValidInput(1, 2);
    if (choice == 2) points += 3;

    return points;
}

// Function to generate personalized study planner
void generateStudyPlanner(string courseNames[], int points[], int numCourses, string routine[], int dailyHours[]) {
    ofstream outFile("StudyPlanner.txt");

    if (!outFile) {
        cerr << "Error creating file!" << endl;
        return;
    }

    outFile << "Personalized Weekly Study Planner:\n";
    outFile << "----------------------------------\n";

    string daysOfWeek[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    for (int i = 0; i < numCourses; i++) {
        outFile << "\nCourse " << (i + 1) << " (" << courseNames[i] << "):\n";

        // Determine the recommended study hours per week based on points
        int weeklyHours;
        if (points[i] >= 35) {
            weeklyHours = 6; // High priority: 5-6 hours
        } else if (points[i] >= 20) {
            weeklyHours = 4; // Moderate priority: 3-4 hours
        } else {
            weeklyHours = 2; // Low priority: 1-2 hours
        }

        outFile << "Recommended Total Study Hours: " << weeklyHours << " hours/week\n";
        outFile << "Suggested Weekly Schedule:\n";

        // Allocate hours across the week based on user routine and daily preferences
        int hoursLeft = weeklyHours;
        for (int j = 0; j < 7; j++) { // Loop through days of the week
            if (hoursLeft <= 0) break;

            int dailyStudyTime = min(hoursLeft, dailyHours[j]); // Limit study time per day
            if (dailyStudyTime > 0) {
                outFile << "  " << daysOfWeek[j] << ": Study for " << dailyStudyTime 
                        << " hour(s) in the " << routine[j] << ".\n";
                hoursLeft -= dailyStudyTime;
            }
        }

        // If there are leftover hours, distribute them across available days
        if (hoursLeft > 0) {
            outFile << "  Remaining " << hoursLeft << " hour(s) to be adjusted based on availability.\n";
        }
    }

    outFile.close();
    cout << "\nStudy planner with a weekly schedule has been saved to 'StudyPlanner.txt'.\n";
}

// Main function
int main() {
    int numCourses;
    cout << "How many courses do you need help managing? ";
    cin >> numCourses;

    string courseNames[100];
    int points[100]; // Array to store points for each course (max 100 courses)
    string routine[7];
    int dailyHours[7];

    cout << "Let's set up your daily routine.\n";
    string daysOfWeek[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (int i = 0; i < 7; i++) {
        cout << "What part of the day are you free on " << daysOfWeek[i] << "? (1-Morning, 2-Afternoon, 3-Evening): ";
        int choice = getValidInput(1, 3);
        routine[i] = convertChoiceToRoutine(choice);
        cout << "How many hours can you dedicate to studying on " << daysOfWeek[i] << "? ";
        cin >> dailyHours[i];
    }

    for (int i = 0; i < numCourses; i++) {
        cout << "Enter the name of Course " << (i + 1) << ": ";
        cin.ignore();
        getline(cin, courseNames[i]);
        points[i] = askQuestions(i + 1, courseNames[i]);
    }

    generateStudyPlanner(courseNames, points, numCourses, routine, dailyHours);

    return 0;
}
