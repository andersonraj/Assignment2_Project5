#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
};

int main() {
    std::vector<STUDENT_DATA> students;
    std::ifstream file("StudentData.txt");

    if (!file.is_open()) {
        std::cerr << "Error opening StudentData.txt" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string lastName, firstName;

        if (std::getline(ss, lastName, ',') && std::getline(ss, firstName)) {
            // Trim leading whitespace if present
            if (!firstName.empty() && firstName[0] == ' ') {
                firstName.erase(0, 1);
            }

            STUDENT_DATA student;
            student.lastName = lastName;
            student.firstName = firstName;
            students.push_back(student);
        }
    }

    file.close();

#ifdef _DEBUG
    std::cout << "--- DEBUG: Student Data ---" << std::endl;
    for (const auto& student : students) {
        std::cout << "Name: " << student.firstName << " " << student.lastName << std::endl;
    }
#endif

    return 1;
}