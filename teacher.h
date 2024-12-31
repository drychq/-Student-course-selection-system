#pragma once



#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Course;

class Teacher {

public:
    Teacher(const std::string& name);

    std::string getName() const;

    void importScore(std::shared_ptr<Course> course, int studentID, int score);
    void viewCourses(const std::vector<std::shared_ptr<Course>>& courses) const;
private:
    std::string _name;
};

