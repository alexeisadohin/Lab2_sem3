#ifndef TEST_FROM_FILE_H
#define TEST_FROM_FILE_H
#include "ArraySequence.h"
#include "ListSequence.h"
#include "Student.h"

#include <iostream>
#include <fstream>

#include <sstream>
template<typename T>
ShrdPtr<Sequence<T>> ReadStudentsFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    ShrdPtr<Sequence<T>> students(new ArraySequence<T>());
    std::string line;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        T student;
        char firstName[256];
        char lastName[256];
        int id, day, month, year, yearOfStudy;


        if (iss >> firstName >> lastName >> id >> day >> month >> year >> yearOfStudy) {

            Student tempStudent(firstName, lastName, id, new int[3]{day, month, year}, yearOfStudy);
            student = tempStudent;
            students = students->Append(student);

        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue;
        }
    }

    inputFile.close();
    return students;
}

template<typename T>
void WriteStudentsToFile(const ShrdPtr<Sequence<T>>& students, const std::string& filename) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    for (int i = 0; i < students->GetLength(); ++i) {
        outputFile << students->Get(i) << std::endl;
    }

    outputFile.close();
}
#endif //TEST_FROM_FILE_H
