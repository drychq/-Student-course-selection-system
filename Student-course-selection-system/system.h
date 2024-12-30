#pragma once

#include "course.h"
#include <memory>

class System
{
public:
    void addStudent(const std::string& name, int id);
    void addTeacher(const std::string& name);
    void addCourse(const std::string& name, int id, const std::string& desc);

    std::shared_ptr<Student> findStudent(int id);
    std::shared_ptr<Teacher> findTeacher(const std::string& name);
    std::shared_ptr<Course> findCourse(int id);

};
