 
    
    

    
    
   #include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to ask questions for a course and calculate points
int askQuestions(int courseNumber) {
    int points = 0;
    string input;
    int creditHours;

    cout << "\nLet's get started with Course " << courseNumber << "!\n";
    
    cout << "1. Have you studied this course before?\n";
    cout << "    1. Yes, I have some prior knowledge\n";
    cout << "    2. No, I’m starting from scratch\n";
    cout << "Your choice: ";
    cin >> input;
    if (input == "2") points += 5;

    cout << "\n2. What was your grade last time you studied this course? (if applicable)\n";
    cout << "    1. A – I did great\n";
    cout << "    2. B – Decent, but I could have done better\n";
    cout << "    3. C – Not great, but I passed\n";
    cout << "    4. D or F – Struggled significantly\n";
    cout << "Your choice: ";
    cin >> input;
    if (input == "2") points += 2;
    else if (input == "3") points += 4;
    else if (input == "4") points += 6;

    cout << "\n3. How would you rate the complexity of this course?\n";
    cout << "    1. Easy – I can breeze through this\n";
    cout << "    2. Moderate – It will be challenging, but manageable\n";
    cout << "    3. Hard – This will be tough\n";
    cout << "Your choice: ";
    cin >> input;
    if (input == "2") points += 3;
    else if (input == "3") points += 6;

    cout << "\n4. How many credit hours is this course worth?\n";
    cout << "    1. 1-2 hours – Quick and easy\n";
    cout << "    2. 3-4 hours – Average workload\n";
    cout << "    3. 5 or more hours – Significant time commitment\n";
    cout << "Your choice: ";
    cin >> creditHours;
    if (creditHours <= 2) points += 2;
    else if (creditHours <= 4) points += 4;
    else points += 6;

    cout << "\n5. Is this course a core subject for your degree/major?\n";
    cout << "    1. Yes – It’s essential\n";
    cout << "    2. No – It’s an elective\n";
    cout << "Your choice: ";
    cin >> input;
    if (input == "2") points += 3;

    cout << "\n6. How do you feel about your study environment?\n";
    cout << "    1. I’m motivated in any environment\n";
    cout << "    2. I prefer a quiet, distraction-free place\n";
    cout << "    3. I need some background noise to concentrate\n";
    cout << "Your choice: ";
    cin >> input;
    if (input == "2") points += 4;
    else if (input == "3") points += 2;

    cout << "\n7. How many hours can you dedicate to this course each day?\n";
    cout << "    1. 1-2 hours – I can spare a bit of time\n";
    cout << "    2. 3-4 hours – I’m committed to studying\n";
    cout << "    3. 5+ hours – I’m ready for a heavy workload\n";
    cout << "Your choice: ";
    cin >> input;
    if (input == "1") points += 6;
    else if (input == "2") points += 3;

    cout << "\n8. How would you rate your current understanding of the course topics?\n";
    cout << "    1. Beginner – I’m still learning the basics\n";
    cout << "    2. Intermediate – I understand most concepts\n";
    cout << "    3. Advanced – I’m very familiar with the topics\n";
    cout << "Your choice: ";
    cin >> input;
    if (input == "1") points += 5;
    else if (input == "2") points += 3;

    cout << "\n9. How comfortable are you with programming concepts?\n";
    cout << "    1. Very comfortable – I have a solid grasp of programming\n";
    cout << "    2. Somewhat comfortable – I know the basics\n";
    cout << "    3. Not comfortable – I struggle with programming\n";
    cout << "Your choice: ";
    cin >> input;
    if (input == "2") points += 3;
    else if (input == "3") points += 6;

    return points;
}

// Function to generate personalized study planner (specific daily schedule)
void generateSpecificStudyPlanner(int numCourses, int* points) {
    ofstream outFile("StudyPlanner.txt");

    if (!outFile) {
        cerr << "Error creating file!" << endl;
        return;
    }

    outFile << "Personalized Study Planner (Specific Schedule):\n";

    // Array to store study hours for each day (7 days of the week)
    int dailyStudyHours[numCourses][7] = {0};  // For each course, an array to store hours for each day of the week

    // Ask user how many hours they can study each day for each course
    for (int i = 0; i < numCourses; i++) {
        outFile << "\nCourse " << (i + 1) << " Daily Schedule (Points: " << points[i] << "):\n";

        // Calculate study hours based on points
        int totalStudyHours = points[i] / 5;  // Divide by 5 to distribute the points into hours per week (totalStudyHours is per week)

        // Distribute total study hours over 7 days
        for (int day = 0; day < 7; day++) {
            // A simple method to spread study hours over the days
            int dailyHours = totalStudyHours / 7; // Start with even distribution
            if (day == 0) { // Monday can have more hours for example, based on preferences
                dailyHours += totalStudyHours % 7;  // Spread any remainder to the first day
            }

            dailyStudyHours[i][day] = dailyHours;  // Store the calculated hours

            // Ask the user to confirm or adjust the hours for each day
            string dayName;
            switch(day) {
                case 0: dayName = "Monday"; break;
                case 1: dayName = "Tuesday"; break;
                case 2: dayName = "Wednesday"; break;
                case 3: dayName = "Thursday"; break;
                case 4: dayName = "Friday"; break;
                case 5: dayName = "Saturday"; break;
                case 6: dayName = "Sunday"; break;
            }
            outFile << dayName << ": " << dailyStudyHours[i][day] << " hours of study.\n";
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
        points[i] = askQuestions(i + 1);  // Calculate points based on user input
    }

    generateSpecificStudyPlanner(numCourses, points);  // Generate the schedule based on points

    return 0;
}
