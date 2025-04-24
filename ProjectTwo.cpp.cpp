/////////////////////////////////////////////////////////////////////////////////////////
//Tammy Wilson
//CS_300
//Project Two
//////////////////////////////////////////////////////////////////////////////////////////
// Read;.CSV courses
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
 // Define a structure to hold course details
struct Course {
    std::string title;
    std::vector<std::string> prerequisites;
};


// Function to load course data from a file
void loadCourseData(const std::string& filename, std::map<std::string, Course>& courses) {
    std::ifstream file(filename); // Open the file
    std::string line;


    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    // Read the file line by line
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string courseNumber, courseTitle, prerequisite;
        Course course;

        // Parse the course number and title
        std::getline(ss, courseNumber, ',');
        std::getline(ss, course.title, ',');

        // Parse prerequisites while handling empty entries
        while (std::getline(ss, prerequisite, ',')) {
            if (!prerequisite.empty()) {
                course.prerequisites.push_back(prerequisite);
            }
        }

        // Add the course to the map
        courses[courseNumber] = course;
    }

    file.close(); // Close the file
    std::cout << "Courses successfully loaded into the data structure!" << std::endl;
}

// Function to display the list of courses sorted alphanumerically
void displaySortedCourses(const std::map<std::string, Course>& courses) {
    if (courses.empty()) {
        std::cout << "No courses loaded yet. Please load the data first." << std::endl;
        return;
    }

    std::cout << "Here is a sample schedule:" << std::endl;
    for (const auto& pair : courses) {
        std::cout << pair.first << ", " << pair.second.title << std::endl;
    }
}

// Function to display course information
void displayCourseInfo(const std::map<std::string, Course>& courses, const std::string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        // Print the course title
        std::cout << it->first << ", " << it->second.title << std::endl;

        // Print prerequisites
        if (!it->second.prerequisites.empty()) {
            std::cout << "Prerequisites: ";
            for (const auto& prereq : it->second.prerequisites) {
                std::cout << prereq << " ";
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "Prerequisites: None" << std::endl;
        }
    }
    else {
        std::cout << "Course not found: " << courseNumber << std::endl;
    }
}

// Helper function to normalize course number input
std::string normalizeCourseNumber(const std::string& input) {
    std::string normalizedInput = input;
    std::transform(normalizedInput.begin(), normalizedInput.end(), normalizedInput.begin(), ::toupper);
    return normalizedInput;
}

// Main function with menu-driven interface
int main() {
  
    std::map < std::string, Course> courses{}; // Data structure to hold courses
    int choice; // User's menu choice

    std::cout << "Welcome to the course planner." << std::endl;

    do {
        // Display menu
        std::cout << "\n1. Load Data Structure." << std::endl;
        std::cout << "2. Print Course List." << std::endl;
        std::cout << "3. Print Course." << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "What would you like to do? ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string filename;
            std::cout << "Enter the filename: ";
            std::cin >> filename;
            loadCourseData(filename, courses);
            break;
        }
        case 2:
            displaySortedCourses(courses);
            break;
        case 3: {
            std::string inputCourseNumber;
            std::cout << "What course do you want to know about? ";
            std::cin >> inputCourseNumber;

            // Normalize input to uppercase
            std::string normalizedCourseNumber = normalizeCourseNumber(inputCourseNumber);
            displayCourseInfo(courses, normalizedCourseNumber);
            break;
        }
        case 9:
            std::cout << "Thank you for using the course planner!" << std::endl;
            break;
        default:
            std::cerr << choice << " is not a valid option." << std::endl;
        }
    } while (choice != 9);

    return 0;
}
