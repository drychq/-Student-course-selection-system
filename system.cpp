#include "system.h"
#include "course.h"

void System::addStudent(const std::string& name, int id) {
    _students.push_back(std::make_shared<Student>(name, id));
}

void System::addTeacher(const std::string& name) {
    _teachers.push_back(std::make_shared<Teacher>(name));
}

void System::addCourse(const std::string& name, int id, const std::string& desc) {
    _courses.push_back(std::make_shared<Course>(name, id, desc));
}

std::shared_ptr<Student> System::findStudent(int id) {
    for (const auto& student : _students) {
        if (student->getStudentID() == id) {
            return student;
        }
    }
    return nullptr;
}

std::shared_ptr<Teacher> System::findTeacher(const std::string& name) {
    for (const auto& teacher : _teachers) {
        if (teacher->getName() == name) {
            return teacher;
        }
    }
    return nullptr;
}

std::shared_ptr<Course> System::findCourse(int id) {
    for (const auto& course : _courses) {
        if (course->getCourseID() == id) {
            return course;
        }
    }
    return nullptr;
}
