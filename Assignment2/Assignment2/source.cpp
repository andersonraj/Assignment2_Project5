#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
#ifdef PRE_RELEASE
    std::string email;
#endif
};

int main() {
    // 1. Print application mode (Standard vs Pre-Release)
#ifdef PRE_RELEASE
    std::cout << "Application is running Pre-Release source code." << std::endl;
#else
    std::cout << "Application is running Standard source code." << std::endl;
#endif

    std::vector<STUDENT_DATA> students;

    // 2. Select file based on PRE_RELEASE directive
#ifdef PRE_RELEASE
    std::ifstream file("StudentData_Emails.txt");
    std::string filename = "StudentData_Emails.txt";
#else
    std::ifstream file("StudentData.txt");
    std::string filename = "StudentData.txt";
#endif

    if (!file.is_open()) {
        std::cerr << "Error opening " << filename << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string lastName, firstName;

#ifdef PRE_RELEASE
        std::string email;
        // Format: LastName, FirstName, Email
        if (std::getline(ss, lastName, ',') &&
            std::getline(ss, firstName, ',') &&
            std::getline(ss, email)) {

            // Trim leading space if present
            if (!firstName.empty() && firstName[0] == ' ') {
                firstName.erase(0, 1);
            }
            if (!email.empty() && email[0] == ' ') {
                email.erase(0, 1);
            }

            STUDENT_DATA student;
            student.lastName = lastName;
            student.firstName = firstName;
            student.email = email;
            students.push_back(student);
        }
#else
        // Format: LastName, FirstName
        if (std::getline(ss, lastName, ',') && std::getline(ss, firstName)) {
            if (!firstName.empty() && firstName[0] == ' ') {
                firstName.erase(0, 1);
            }

            STUDENT_DATA student;
            student.lastName = lastName;
            student.firstName = firstName;
            students.push_back(student);
        }
#endif
    }

    file.close();

    // 3. Debug output
#ifdef _DEBUG
    std::cout << "--- DEBUG: Student Data ---" << std::endl;
    for (const auto& student : students) {
#ifdef PRE_RELEASE
        std::cout << "Name: " << student.firstName << " " << student.lastName
            << " | Email: " << student.email << std::endl;
#else
        std::cout << "Name: " << student.firstName << " " << student.lastName << std::endl;
#endif
    }
#endif

    return 1;
}