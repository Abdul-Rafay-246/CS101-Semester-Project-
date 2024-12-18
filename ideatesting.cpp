#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Function to ask questions for a course and calculate points
int askQuestions(int courseNumber) {
    int points = 0;
    string input;
    int creditHours;

    cout << "\nFor Course " << courseNumber << ":\n";

    // Question 1: Have you studied the course previously?
    cout << "Have you studied the course previously? (yes/no): ";
    cin >> input;
    if (input == "no") points += 5;

    // Question 2: Grade last time in the course
    cout << "What was your grade last time? (A/B/C/D/F or N/A): ";
    cin >> input;
    if (input == "B") points += 2;
    else if (input == "C") points += 4;
    else if (input == "D" || input == "F") points += 6;

    // Question 3: Complexity level
    cout << "Rate the complexity of the course (easy/moderate/hard): ";
    cin >> input;
    if (input == "moderate") points += 3;
    else if (input == "hard") points += 6;

    // Question 4: Credit hours
    cout << "How many credit hours is this course? (Enter an integer): ";
    cin >> creditHours;
    if (creditHours <= 2) points += 2;
    else if (creditHours <= 4) points += 4;
    else points += 6;

    // Question 5: Degree or major
    cout << "Is this course core for your degree/major? (yes/no): ";
    cin >> input;
    if (input == "no") points += 3;

    // Question 6: Most productive time of the day
    cout << "What time of the day are you most productive? (morning/afternoon/evening): ";
    cin >> input;
    // No points assigned, used for scheduling purposes

    // Question 7: Hours you can dedicate
    cout << "How many hours can you dedicate daily to this course? (1-2/3-4/5 or more): ";
    cin >> input;
    if (input == "1-2") points += 6;
    else if (input == "3-4") points += 3;

    // Question 8: Current understanding of the course
    cout << "What is your current understanding of the course topics? (beginner/intermediate/advanced): ";
    cin >> input;
    if (input == "beginner") points += 5;
    else if (input == "intermediate") points += 3;

    // Question 9: Comfortable with programming concepts
    cout << "Are you comfortable with programming concepts? (yes/somewhat/no): ";
    cin >> input;
    if (input == "somewhat") points += 3;
    else if (input == "no") points += 6;

    // Question 10: Study preference
    cout << "How do you prefer to study? (solo/group): ";
    cin >> input;
    // No points assigned, used for scheduling purposes

    return points;
}

// Function to generate personalized study planner
void generateStudyPlanner(const vector<int>& points, int numCourses) {
    ofstream outFile("StudyPlanner.txt");

    if (!outFile) {
        cerr << "Error creating file!" << endl;
        return;
    }

    outFile << "Personalized Study Planner:\n";
    for (int i = 0; i < numCourses; i++) {
        outFile << "\nCourse " << (i + 1) << ":\n";
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

    vector<int> points(numCourses);

    for (int i = 0; i < numCourses; i++) {
        points[i] = askQuestions(i + 1);
    }

    generateStudyPlanner(points, numCourses);

    return 0;
}
