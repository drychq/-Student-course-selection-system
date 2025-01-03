#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Course;

class Student {
public:
    Student(const std::string& name, int id);

    int getStudentID() const;
    std::string getName() const;

    void selectCourse(std::shared_ptr<Course> course);
    void viewScores() const;
    void viewCourses() const;
    const std::vector<std::shared_ptr<Course>>& getCourses() const;

private:
    std::string _name;
    int _studentID;
    std::vector<std::shared_ptr<Course>> _enrolledCourses;


};
