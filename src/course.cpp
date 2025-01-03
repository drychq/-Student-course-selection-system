//author:任纹萱
//date:25/1/2
#include "course.h"


Course::Course(const std::string& name, int id, const std::string& desc)
    : _courseName(name), _courseID(id), _description(desc) {}

std::string Course::getCourseName() const {
    return _courseName;
}

int Course::getCourseID() const {
    return _courseID;
}

std::string Course::getDescription() const {
    return _description;
}

void Course::addStudent(int studentID) {
    _studentIDs.push_back(studentID);
    _scores.push_back(-1); // Initialize score to -1 (not graded)
}

void Course::importScore(int studentID, int score) {
    bool found = false;
    for (size_t i = 0; i < _studentIDs.size(); ++i) {
        if (_studentIDs[i] == studentID) {
            _scores[i] = score;
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Error: Student ID " << studentID << " not found in course " << _courseName << std::endl;
    }
}

int Course::getScore(int studentID) const {
    for (size_t i = 0; i < _studentIDs.size(); ++i) {
        if (_studentIDs[i] == studentID) {
            return _scores[i];
        }
    }
    return -1; // Not found
}
