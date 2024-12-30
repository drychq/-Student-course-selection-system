#pragma once


#include <iostream>
#include <vector>
#include <string>

class Course {

public:
    Course(const std::string& name, int id, const std::string& desc);
    //初始化：课程名字，课程id,课程描述

    std::string getCourseName() const;
    //获取课程名字
    int getCourseID() const;
    //获取课程id
    std::string getDescription() const;
    //获取课程描述

    void addStudent(int studentID);
    //添加学生
    void importScore(int studentID, int score); //导入学生成绩
    int getScore(int studentID) const; //根据学生id获取该学生本课程的分数
private:
    std::string courseName;
    int courseID;
    std::string description;
    std::vector<int> studentIDs;
    std::vector<int> scores;

};
