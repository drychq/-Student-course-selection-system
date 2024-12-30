#pragma once


#include <iostream>
#include <vector>
#include <string>

class Course {
private:
    std::string courseName;
    int courseID;
    std::string description;
    std::vector<int> studentIDs;
    std::vector<int> scores;

public:
    Course(const std::string& name, int id, const std::string& desc);

    std::string getCourseName() const;
    int getCourseID() const;
    std::string getDescription() const;

    void addStudent(int studentID);
    void importScore(int studentID, int score); //导入学生成绩
    int getScore(int studentID) const;
};


