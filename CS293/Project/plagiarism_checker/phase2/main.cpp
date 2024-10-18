#include "plagiarism_checker.hpp"

#include <map>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// You should NOT modify ANYTHING in this file.

void student_t::flag_student(std::shared_ptr<submission_t> __submission) {
    std::cout << "I was flagged in submisssion " << __submission->id << 
        " and must defend myself in front of Prof. " <<
        __submission->professor->get_name() << "." << std::endl;
}

void professor_t::flag_professor(std::shared_ptr<submission_t> __submission) {
    std::cout << "Student " << __submission->student->get_name() << " has "
        "plagiarized in submission " << __submission->id << " and will be "
        << "receiving an FR grade." << std::endl << std::endl;
}

namespace testcases {
    std::map<std::string, std::shared_ptr<student_t>> get_students(
            std::string filename);
    std::map<std::string, std::shared_ptr<professor_t>> get_professors(
            std::string filename);
    std::vector<std::shared_ptr<submission_t>> get_originals(
            std::string test_dir);
    void execute_testcase(std::string test_dir);
}

std::map<std::string, std::shared_ptr<student_t>> testcases::get_students(
        std::string filename) {
    std::ifstream in(filename);
    std::map<std::string, std::shared_ptr<student_t>> students;
    std::string student_name;
    while (in >> student_name) {
        students[student_name] = std::make_shared<student_t>(student_name);
    }
    in.close();
    return students;
}

std::map<std::string, std::shared_ptr<professor_t>> testcases::get_professors(
        std::string filename) {
    std::ifstream in(filename);
    std::map<std::string, std::shared_ptr<professor_t>> professors;
    std::string professor_name;
    while (in >> professor_name) {
        professors[professor_name] = 
            std::make_shared<professor_t>(professor_name);
    }
    in.close();
    return professors;
}

std::vector<std::shared_ptr<submission_t>> testcases::get_originals(
        std::string test_dir) {
    std::ifstream in(test_dir + "/originals.txt");
    std::vector<std::shared_ptr<submission_t>> pre_existing_codes;
    long id;
    std::string student_name;
    std::string professor_name;
    std::string token;
    std::string code_file;
    while (in >> id >> student_name >> professor_name >> code_file) {
        std::shared_ptr<submission_t> submission = 
            std::make_shared<submission_t>();
        submission->id = id;
        submission->student = std::make_shared<student_t>(student_name);
        submission->professor = std::make_shared<professor_t>(professor_name);
        submission->codefile = test_dir + "/" + code_file + ".cpp";
        pre_existing_codes.push_back(submission);
    }
    in.close();
    return pre_existing_codes;
}


void testcases::execute_testcase(std::string test_dir) {
    std::map<std::string, std::shared_ptr<student_t>> students = 
        get_students(test_dir + "/students.txt");
    std::map<std::string, std::shared_ptr<professor_t>> professors = 
        get_professors(test_dir + "/professors.txt");
    std::vector<std::shared_ptr<submission_t>> pre_existing_codes = 
        get_originals(test_dir);
    plagiarism_checker_t checker(pre_existing_codes);
    std::ifstream in(test_dir + "/submissions.txt");
    double timestamp;
    double old_timestamp = 0.0;
    long id;
    std::string student_name;
    std::string prof_name;
    std::string code_file;
    while (in >> timestamp >> id >> student_name >> prof_name >> code_file) {
        usleep((timestamp - old_timestamp) * 1000000);
        std::shared_ptr<submission_t> submission = 
            std::make_shared<submission_t>();
        submission->id = id;
        submission->student = students[student_name];
        submission->professor = professors[prof_name];
        submission->codefile = test_dir + "/" + code_file + ".cpp";
        checker.add_submission(submission);
        old_timestamp = timestamp;
    }
}

int main(void) {
    testcases::execute_testcase("testcase");
    return 0;
}