#include "course.h"


Course::Course(const std::string& name, int id, const std::string& desc)
    : courseName(name), courseID(id), description(desc) {}

std::string Course::getCourseName() const {
    return courseName;
}

int Course::getCourseID() const {
    return courseID;
}

std::string Course::getDescription() const {
    return description;
}

void Course::addStudent(int studentID) {
    studentIDs.push_back(studentID);
    scores.push_back(-1); // Initialize score to -1 (not graded)
}

void Course::importScore(int studentID, int score) {
    bool found = false;
    for (size_t i = 0; i < studentIDs.size(); ++i) {
        if (studentIDs[i] == studentID) {
            scores[i] = score;
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Error: Student ID " << studentID << " not found in course " << courseName << std::endl;
    }
}

int Course::getScore(int studentID) const {
    for (size_t i = 0; i < studentIDs.size(); ++i) {
        if (studentIDs[i] == studentID) {
            return scores[i];
        }
    }
    return -1; // Not found
}
