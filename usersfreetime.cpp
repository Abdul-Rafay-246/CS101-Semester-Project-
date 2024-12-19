#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to ask questions for a course and calculate points
int askQuestions(int courseNumber) {
    int points = 0;
    string input;
    int creditHours;

    cout << "\n\nLet's get started with Course " << courseNumber << "!\n";
    
    cout << "1. Have you studied this course before?\n";
    cout << "    1. Yes, I have some prior knowledge\n";
    cout << "    2. No, I’m starting from scratch\n";
    cout << "Your choice: ";
    cin >> input;
    if (input == "2") points += 5;

    cout << "\n2. What was your grade last time you studied this course? (if applicable)\n";
    cout << "    1. A – I nailed it! 😎\n";
    cout << "    2. B – Could have done better, but decent.\n";
    cout << "    3. C – Not the best, but I got through.\n";
    cout << "    4. D or F – Oops, major struggle! 😬\n";
    cout << "Your choice: ";
    cin >> input;
    if (input == "2") points += 2;
    else if (input == "3") points += 4;
    else if (input == "4") points += 6;

    cout << "\n3. How would you rate the complexity of this course?\n";
    cout << "    1. Easy – I can breeze through this! ✌️\n";
    cout << "    2. Moderate – It’ll be a challenge, but I’m up for it.\n";
    cout << "    3. Hard – This is going to be a tough one! 😰\n";
    cout << "Your choice: ";
    cin >> input;
    if (input == "2") points += 3;
    else if (input == "3") points += 6;

    cout << "\n4. How many credit hours is this course worth?\n";
    cout << "    1. 1-2 hours – Quick and easy.\n";
    cout << "    2. 3-4 hours – Average workload.\n";
    cout << "    3. 5 or more hours – I’ll need to dedicate some serious time! ⏰\n";
    cout << "Your choice: ";
    cin >> creditHours;
    if (creditHours <= 2) points += 2;
    else if (creditHours <= 4) points += 4;
    else points += 6;

    cout << "\n5. Is this course a core subject for your degree/major?\n";
    cout << "    1. Yes – It’s essential to my field.\n";
    cout << "    2. No – Just an elective or side course.\n";
    cout << "Your choice: ";
    cin >> input;
    if (input == "2") points += 3;

    cout << "\n6. How do you feel about your study environment?\n";
    cout << "    1. I’m motivated and focused in any environment.\n";
    cout << "    2. I prefer studying in a quiet, distraction-free place.\n";
    cout << "    3. I need some background noise to concentrate (e.g., music, coffee shop). 🎶☕\n";
    cout << "Your choice: ";
    cin >> input;
    if (input == "2") points += 4;
    else if (input == "3") points += 2;

    cout << "\n7. How many hours can you dedicate to this course each day?\n";
    cout << "    1. 1-2 hours – I can spare a bit of time.\n";
    cout << "    2. 3-4 hours – I’m ready to get serious!\n";
    cout << "    3. 5+ hours – I’m all in, let's do this! 💪\n";
    cout << "Your choice: ";
    cin >> input;
    if (input == "1") points += 6;
    else if (input == "2") points += 3;

    cout << "\n8. How would you rate your current understanding of the course topics?\n";
    cout << "    1. Beginner – I’m still learning the basics.\n";
    cout << "    2. Intermediate – I understand the concepts, but need more practice.\n";
    cout << "    3. Advanced – I’m already quite confident. 📚\n";
    cout << "Your choice: ";
    cin >> input;
    if (input == "1") points += 5;
    else if (input == "2") points += 3;

    cout << "\n9. How comfortable are you with programming concepts?\n";
    cout << "    1. Very comfortable – I code with ease. 💻\n";
    cout << "    2. Somewhat comfortable – I know the basics, but there’s room to improve.\n";
    cout << "    3. Not comfortable – I get confused with programming concepts. 😓\n";
    cout >> input;
    if (input == "2") points += 3;
    else if (input == "3") points += 6;

    return points;
}

// Function to generate personalized study planner
void generateStudyPlanner(int points[], int numCourses, bool isSpecific) {
    ofstream outFile("StudyPlanner.txt");

    if (!outFile) {
        cerr << "Error creating file!" << endl;
        return;
    }

    outFile << "Personalized Study Planner:\n";

    if (isSpecific) {
        // Array to store study hours for each day (7 days of the week)
        int dailyStudyHours[numCourses][7] = {0};  // For each course, an array to store hours for each day of the week

        // Ask user how many hours they can study each day for each course
        for (int i = 0; i < numCourses; i++) {
            outFile << "\nCourse " << (i + 1) << " Daily Schedule:\n";
            for (int day = 0; day < 7; day++) {
                cout << "How many hours can you study on day " << (day + 1) << "? (0-6 hours): ";
                cin >> dailyStudyHours[i][day];
            }
        }

        // Generate a daily study schedule for each course
        for (int i = 0; i < numCourses; i++) {
            outFile << "\nCourse " << (i + 1) << " Daily Schedule:\n";
            for (int day = 0; day < 7; day++) {
                outFile << "Day " << (day + 1) << ": " << dailyStudyHours[i][day] << " hours of study.\n";
            }
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

    int points[numCourses];  // Array to store points for each course

    for (int i = 0; i < numCourses; i++) {
        points[i] = askQuestions(i + 1);
    }

    cout << "Would you like a general schedule or a specific schedule?\n";
    cout << "1. General schedule\n2. Specific daily schedule\n";
    string scheduleChoice;
    cin >> scheduleChoice;

    bool isSpecific = (scheduleChoice == "2");

    generateStudyPlanner(points, numCourses, isSpecific);

    return 0;
}
