#include "teacher.h"
#include "course.h"

Teacher::Teacher(const std::string& name) : name(name) {}

std::string Teacher::getName() const {
    return name;
}

void Teacher::importScore(std::shared_ptr<Course> course, int studentID, int score) {
    course->importScore(studentID, score);
}

void Teacher::viewCourses(const std::vector<std::shared_ptr<Course>>& courses) const {
    std::cout << "Courses handled by " << name << ":\n";
    for (const auto& course : courses) {
        std::cout << course->getCourseName() << " - " << course->getDescription() << "\n";
    }
}
