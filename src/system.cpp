#include "system.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <sqlite3.h>

// Helper function to execute SQL statement with error checking
bool executeSQL(sqlite3* db, const std::string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << "\n";
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

// Helper function to prepare SQL statement with error checking
bool prepareSQL(sqlite3* db, const std::string& sql, sqlite3_stmt** stmt) {
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        return false;
    }
    return true;
}

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



// Helper function to clear input stream
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void System::addStudentUI() {
    std::string name;
    int id;
    std::cout << "Enter student name: ";
    std::cin >> name;
    std::cout << "Enter student ID: ";
    std::cin >> id;
    if (std::cin.fail()) {
        std::cout << "Invalid ID. Please enter a valid number.\n";
        clearInput();
        return;
    }
    addStudent(name, id);
}

void System::addTeacherUI() {
    std::string name;
    std::cout << "Enter teacher name: ";
    std::cin >> name;
    addTeacher(name);
}

void System::addCourseUI() {
    std::string name, desc;
    int id;
    std::cout << "Enter course name: ";
    std::cin >> name;
    std::cout << "Enter course ID: ";
    std::cin >> id;
    if (std::cin.fail()) {
        std::cout << "Invalid ID. Please enter a valid number.\n";
        clearInput();
        return;
    }
    std::cin.ignore();
    std::cout << "Enter course description: ";
    std::getline(std::cin, desc);
    addCourse(name, id, desc);
}

void System::studentSelectCourseUI() {
    int studentID, courseID;
    std::cout << "Enter student ID: ";
    std::cin >> studentID;
    if (std::cin.fail()) {
        std::cout << "Invalid student ID. Please enter a valid number.\n";
        clearInput();
        return;
    }
    std::cout << "Enter course ID: ";
    std::cin >> courseID;
    if (std::cin.fail()) {
        std::cout << "Invalid course ID. Please enter a valid number.\n";
        clearInput();
        return;
    }
    auto student = findStudent(studentID);
    auto course = findCourse(courseID);
    if (student && course) {
        student->selectCourse(course);
    } else {
        std::cout << "Student or Course not found.\n";
    }
}

void System::teacherImportScoreUI() {
    std::string teacherName;
    int studentID, courseID, score;
    std::cout << "Enter teacher name: ";
    std::cin >> teacherName;
    std::cout << "Enter course ID: ";
    std::cin >> courseID;
    if (std::cin.fail()) {
        std::cout << "Invalid course ID. Please enter a valid number.\n";
        clearInput();
        return;
    }
    std::cout << "Enter student ID: ";
    std::cin >> studentID;
    if (std::cin.fail()) {
        std::cout << "Invalid student ID. Please enter a valid number.\n";
        clearInput();
        return;
    }
    std::cout << "Enter score: ";
    std::cin >> score;
    if (std::cin.fail()) {
        std::cout << "Invalid score. Please enter a valid number.\n";
        clearInput();
        return;
    }
    auto teacher = findTeacher(teacherName);
    auto course = findCourse(courseID);
    if (teacher && course) {
        teacher->importScore(course, studentID, score);
    } else {
        std::cout << "Teacher or Course not found.\n";
    }
}

void System::studentViewScoresUI() {
    int studentID;
    std::cout << "Enter student ID: ";
    std::cin >> studentID;
    if (std::cin.fail()) {
        std::cout << "Invalid student ID. Please enter a valid number.\n";
        clearInput();
        return;
    }
    auto student = findStudent(studentID);
    if (student) {
        student->viewScores();
    } else {
        std::cout << "Student not found.\n";
    }
}

void System::studentViewCoursesUI() {
    int studentID;
    std::cout << "Enter student ID: ";
    std::cin >> studentID;
    if (std::cin.fail()) {
        std::cout << "Invalid student ID. Please enter a valid number.\n";
        clearInput();
        return;
    }
    auto student = findStudent(studentID);
    if (student) {
        student->viewCourses();
    } else {
        std::cout << "Student not found.\n";
    }
}

void System::teacherViewCoursesUI() {
    std::string teacherName;
    std::cout << "Enter teacher name: ";
    std::cin >> teacherName;
    auto teacher = findTeacher(teacherName);
    if (teacher) {
        teacher->viewCourses(_courses);
    } else {
        std::cout << "Teacher not found.\n";
    }
}

void System::saveDataUI() {
    std::string dbname;
    std::cout << "Enter database name to save data: ";
    std::cin >> dbname;
    saveData(dbname);
}

void System::loadDataUI() {
    std::string dbname;
    std::cout << "Enter database name to load data: ";
    std::cin >> dbname;
    loadData(dbname);
}

void System::userInterface() {
    while (true) {
        std::cout << "\n--- Course Selection System ---\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. Add Teacher\n";
        std::cout << "3. Add Course\n";
        std::cout << "4. Student Select Course\n";
        std::cout << "5. Teacher Import Score\n";
        std::cout << "6. Student View Scores\n";
        std::cout << "7. Student View Courses\n";
        std::cout << "8. Teacher View Courses\n";
        std::cout << "9. Save Data\n";
        std::cout << "10. Load Data\n";
        std::cout << "11. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid choice. Please enter a number between 1 and 11.\n";
            clearInput();
            continue;
        }

        switch (choice) {
        case 1:
            addStudentUI();
            break;
        case 2:
            addTeacherUI();
            break;
        case 3:
            addCourseUI();
            break;
        case 4:
            studentSelectCourseUI();
            break;
        case 5:
            teacherImportScoreUI();
            break;
        case 6:
            studentViewScoresUI();
            break;
        case 7:
            studentViewCoursesUI();
            break;
        case 8:
            teacherViewCoursesUI();
            break;
        case 9:
            saveDataUI();
            break;
        case 10:
            loadDataUI();
            break;
        case 11:
            return;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}

void System::saveData(const std::string& dbname) {
    sqlite3* db;
    int rc = sqlite3_open(dbname.c_str(), &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    const char* createTablesSQL =
        "CREATE TABLE IF NOT EXISTS Students (ID INT PRIMARY KEY NOT NULL, Name TEXT NOT NULL);"
        "CREATE TABLE IF NOT EXISTS Teachers (Name TEXT PRIMARY KEY NOT NULL);"
        "CREATE TABLE IF NOT EXISTS Courses (ID INT PRIMARY KEY NOT NULL, Name TEXT NOT NULL, Description TEXT NOT NULL);"
        "CREATE TABLE IF NOT EXISTS Enrollments (StudentID INT NOT NULL, CourseID INT NOT NULL, Score INT, PRIMARY KEY (StudentID, CourseID));";

    if (!executeSQL(db, createTablesSQL)) {
        sqlite3_close(db);
        return;
    }

    sqlite3_exec(db, "BEGIN TRANSACTION;", 0, 0, 0);

    sqlite3_stmt* stmt;

    const char* insertStudentSQL = "INSERT OR REPLACE INTO Students (ID, Name) VALUES (?, ?);";
    if (!prepareSQL(db, insertStudentSQL, &stmt)) {
        sqlite3_close(db);
        return;
    }
    for (const auto& student : _students) {
        sqlite3_bind_int(stmt, 1, student->getStudentID());
        sqlite3_bind_text(stmt, 2, student->getName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_step(stmt);
        sqlite3_reset(stmt);

        const auto& courses = student->getCourses();
        const char* insertEnrollmentSQL = "INSERT OR REPLACE INTO Enrollments (StudentID, CourseID, Score) VALUES (?, ?, ?);";
        sqlite3_stmt* enrollStmt;
        if (!prepareSQL(db, insertEnrollmentSQL, &enrollStmt)) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }

        for (const auto& course : courses) {
            int score = course->getScore(student->getStudentID());
            sqlite3_bind_int(enrollStmt, 1, student->getStudentID());
            sqlite3_bind_int(enrollStmt, 2, course->getCourseID());
            if (score == -1) {
                sqlite3_bind_null(enrollStmt, 3);
            } else {
                sqlite3_bind_int(enrollStmt, 3, score);
            }
            sqlite3_step(enrollStmt);
            sqlite3_reset(enrollStmt);
        }
        sqlite3_finalize(enrollStmt);
    }
    sqlite3_finalize(stmt);

    const char* insertTeacherSQL = "INSERT OR REPLACE INTO Teachers (Name) VALUES (?);";
    if (!prepareSQL(db, insertTeacherSQL, &stmt)) {
        sqlite3_close(db);
        return;
    }
    for (const auto& teacher : _teachers) {
        sqlite3_bind_text(stmt, 1, teacher->getName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_step(stmt);
        sqlite3_reset(stmt);
    }
    sqlite3_finalize(stmt);

    const char* insertCourseSQL = "INSERT OR REPLACE INTO Courses (ID, Name, Description) VALUES (?, ?, ?);";
    if (!prepareSQL(db, insertCourseSQL, &stmt)) {
        sqlite3_close(db);
        return;
    }
    for (const auto& course : _courses) {
        sqlite3_bind_int(stmt, 1, course->getCourseID());
        sqlite3_bind_text(stmt, 2, course->getCourseName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, course->getDescription().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_step(stmt);
        sqlite3_reset(stmt);
    }
    sqlite3_finalize(stmt);

    sqlite3_exec(db, "COMMIT;", 0, 0, 0);
    sqlite3_close(db);
}

void System::loadData(const std::string& dbname) {
    sqlite3* db;
    int rc = sqlite3_open(dbname.c_str(), &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    _students.clear();
    _teachers.clear();
    _courses.clear();

    sqlite3_stmt* stmt;

    const char* selectStudentsSQL = "SELECT ID, Name FROM Students;";
    if (!prepareSQL(db, selectStudentsSQL, &stmt)) {
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        _students.push_back(std::make_shared<Student>(name, id));
    }
    sqlite3_finalize(stmt);

    const char* selectTeachersSQL = "SELECT Name FROM Teachers;";
    if (!prepareSQL(db, selectTeachersSQL, &stmt)) {
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        _teachers.push_back(std::make_shared<Teacher>(name));
    }
    sqlite3_finalize(stmt);

    const char* selectCoursesSQL = "SELECT ID, Name, Description FROM Courses;";
    if (!prepareSQL(db, selectCoursesSQL, &stmt)) {
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* desc = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        _courses.push_back(std::make_shared<Course>(name, id, desc));
    }
    sqlite3_finalize(stmt);

    const char* selectEnrollmentsSQL = "SELECT StudentID, CourseID, Score FROM Enrollments;";
    if (!prepareSQL(db, selectEnrollmentsSQL, &stmt)) {
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int studentID = sqlite3_column_int(stmt, 0);
        int courseID = sqlite3_column_int(stmt, 1);
        int score = sqlite3_column_type(stmt, 2) == SQLITE_NULL ? -1 : sqlite3_column_int(stmt, 2);

        auto student = findStudent(studentID);
        auto course = findCourse(courseID);
        if (student && course) {
            student->selectCourse(course);
            if (score != -1) {
                course->importScore(studentID, score);
            }
        }
    }
    sqlite3_finalize(stmt);

    sqlite3_close(db);
}
