#pragma once



#include <iostream>
#include <vector>
#include <string>

class Course {
public:
    Course(const std::string& name, int id, const std::string& desc);

    std::string getCourseName() const;
    int getCourseID() const;
    std::string getDescription() const;

    void addStudent(int studentID);
    void importScore(int studentID, int score);
    int getScore(int studentID) const;
private:
    std::string _courseName;
    int _courseID;
    std::string _description;
    std::vector<int> _studentIDs;
    std::vector<int> _scores;
};


