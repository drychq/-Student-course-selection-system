#pragma once

#include "student.h"
#include "teacher.h"
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

    void userInterface();
    void saveData(const std::string& dbname);
    void loadData(const std::string& dbname);


private:
    std::vector<std::shared_ptr<Student>> _students;
    std::vector<std::shared_ptr<Teacher>> _teachers;
    std::vector<std::shared_ptr<Course>> _courses;
};
