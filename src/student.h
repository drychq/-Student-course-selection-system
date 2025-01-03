#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Course;

class Student {
private:
    std::string name;
    int studentID;
    std::vector<std::shared_ptr<Course>> enrolledCourses;

public:
    Student(const std::string& name, int id);

    int getStudentID() const;
    std::string getName() const;

    void selectCourse(std::shared_ptr<Course> course);
    void viewScores() const;
    void viewCourses() const;
    const std::vector<std::shared_ptr<Course>>& getCourses() const;
};

