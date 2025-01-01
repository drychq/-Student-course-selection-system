#include "student.h"
#include "course.h"

Student::Student(const std::string& name, int id) : _name(name), _studentID(id) {}

int Student::getStudentID() const {
    return _studentID;
}

std::string Student::getName() const {
    return _name;
}

void Student::selectCourse(std::shared_ptr<Course> course) {
    _enrolledCourses.push_back(course);
    course->addStudent(_studentID);
}

void Student::viewScores() const {
    std::cout << "Scores for " << _name << ":\n";
    for (const auto& course : _enrolledCourses) {
        int score = course->getScore(_studentID);
        std::cout << course->getCourseName() << ": " << (score == -1 ? "Not graded" : std::to_string(score)) << "\n";
    }
}

void Student::viewCourses() const {
    std::cout << "Courses enrolled by " << _name << ":\n";
    for (const auto& course : _enrolledCourses) {
        std::cout << course->getCourseName() << " - " << course->getDescription() << "\n";
    }
}

const std::vector<std::shared_ptr<Course>>& Student::getCourses() const {
    return _enrolledCourses;
}
