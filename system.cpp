#include "system.h"
#include "course.h"

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
