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

// Function to ask questions for a course and calculate points
int askQuestions(int courseNumber, string courseName) {
    int points = 0;
    int choice;
    int creditHours;

    cout << "\nFor Course " << courseNumber << " (" << courseName << "):\n";

    // Question 1: Have you studied the course previously?
    cout << "1. Have you studied the course previously?\n";
    cout << "   1 - Yes\n   2 - No\nYour choice: ";
    choice = getValidInput(1, 2);
    if (choice == 2) points += 5;

    // Question 2: Grade last time in the course
    cout << "2. What was your grade last time?\n";
    cout << "   1 - A\n   2 - B\n   3 - C\n   4 - D/F\n   5 - N/A\nYour choice: ";
    choice = getValidInput(1, 5);
    if (choice == 2) points += 2;
    else if (choice == 3) points += 4;
    else if (choice == 4) points += 6;

    // Question 3: Complexity level
    cout << "3. Rate the complexity of the course:\n";
    cout << "   1 - Easy\n   2 - Moderate\n   3 - Hard\nYour choice: ";
    choice = getValidInput(1, 3);
    if (choice == 2) points += 3;
    else if (choice == 3) points += 6;

    // Question 4: Credit hours
    cout << "4. How many credit hours is this course? (Enter an integer): ";
    cin >> creditHours;
    if (creditHours <= 2) points += 2;
    else if (creditHours <= 4) points += 4;
    else points += 6;

    // Question 5: Is this course core for your degree/major?
    cout << "5. Is this course core for your degree/major?\n";
    cout << "   1 - Yes\n   2 - No\nYour choice: ";
    choice = getValidInput(1, 2);
    if (choice == 2) points += 3;

    // Question 6: Most productive time of the day
    cout << "6. What time of the day are you most productive?\n";
    cout << "   1 - Morning\n   2 - Afternoon\n   3 - Evening\nYour choice: ";
    choice = getValidInput(1, 3);
    // No points assigned, used for scheduling purposes

    // Question 7: Hours you can dedicate
    cout << "7. How many hours can you dedicate daily to this course?\n";
    cout << "   1 - 1-2 hours\n   2 - 3-4 hours\n   3 - 5 or more hours\nYour choice: ";
    choice = getValidInput(1, 3);
    if (choice == 1) points += 6;
    else if (choice == 2) points += 3;

    // Question 8: Current understanding of the course
    cout << "8. What is your current understanding of the course topics?\n";
    cout << "   1 - Beginner\n   2 - Intermediate\n   3 - Advanced\nYour choice: ";
    choice = getValidInput(1, 3);
    if (choice == 1) points += 5;
    else if (choice == 2) points += 3;

    // Question 9: Confidence in handling course content
    cout << "9. Do you feel confident about handling this course content?\n";
    cout << "   1 - Yes\n   2 - Somewhat\n   3 - No\nYour choice: ";
    choice = getValidInput(1, 3);
    if (choice == 2) points += 3;
    else if (choice == 3) points += 6;

    // Question 10: Study preference
    cout << "10. How do you prefer to study?\n";
    cout << "   1 - Solo\n   2 - Group\nYour choice: ";
    choice = getValidInput(1, 2);
    // No points assigned, used for scheduling purposes

    return points;
}

// Function to generate personalized study planner
void generateStudyPlanner(string courseNames[], int points[], int numCourses) {
    ofstream outFile("StudyPlanner.txt");

    if (!outFile) {
        cerr << "Error creating file!" << endl;
        return;
    }

    outFile << "Personalized Study Planner:\n";
    for (int i = 0; i < numCourses; i++) {
        outFile << "\nCourse " << (i + 1) << " (" << courseNames[i] << "):\n";
        outFile << "Recommended Study Hours: ";

        if (points[i] >= 35) {
            outFile << "5-6 hours per week (High priority)\n";
        } else if (points[i] >= 20) {
            outFile << "3-4 hours per week (Moderate priority)\n";
        } else {
            outFile << "1-2 hours per week (Low priority)\n";
        }
    }

    outFile.close();
    cout << "\nStudy planner has been saved to 'StudyPlanner.txt'.\n";
}

// Main function
int main() {
    int numCourses;
    cout << "How many courses do you need help managing? ";
    cin >> numCourses;

    string courseNames[100];
    int points[100]; // Array to store points for each course (max 100 courses)

    for (int i = 0; i < numCourses; i++) {
        cout << "Enter the name of Course " << (i + 1) << ": ";
        cin.ignore();
        getline(cin, courseNames[i]);
        points[i] = askQuestions(i + 1, courseNames[i]);
    }

    generateStudyPlanner(courseNames, points, numCourses);

    return 0;
}
