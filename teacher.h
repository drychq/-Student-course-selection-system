#pragma once



#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Course;

class Teacher {
private:
    std::string name;

public:
    Teacher(const std::string& name);

    std::string getName() const;

    void importScore(std::shared_ptr<Course> course, int studentID, int score);
    void viewCourses(const std::vector<std::shared_ptr<Course>>& courses) const;
};

