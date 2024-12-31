#include "student.h"
#include "course.h"

Student::Student(const std::string& name, int id) : name(name), studentID(id) {}

int Student::getStudentID() const {
    return studentID;
}

std::string Student::getName() const {
    return name;
}

void Student::selectCourse(std::shared_ptr<Course> course) {
    enrolledCourses.push_back(course);
    course->addStudent(studentID);
}

void Student::viewScores() const {
    std::cout << "Scores for " << name << ":\n";
    for (const auto& course : enrolledCourses) {
        int score = course->getScore(studentID);
        std::cout << course->getCourseName() << ": " << (score == -1 ? "Not graded" : std::to_string(score)) << "\n";
    }
}

void Student::viewCourses() const {
    std::cout << "Courses enrolled by " << name << ":\n";
    for (const auto& course : enrolledCourses) {
        std::cout << course->getCourseName() << " - " << course->getDescription() << "\n";
    }
}

const std::vector<std::shared_ptr<Course>>& Student::getCourses() const {
    return enrolledCourses;
}
