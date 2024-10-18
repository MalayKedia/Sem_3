#include "../tokenizer.hpp"
// You should NOT modify ANYTHING in this file.

class student_t;
class professor_t;
struct submission_t;

class student_t {
public:
    student_t(std::string __name) : name(__name) {}
    std::string get_name(void) { return name; }
    void flag_student(std::shared_ptr<submission_t> __submission);
protected:
    std::string name;
};

class professor_t {
public:
    professor_t(std::string __name) : name(__name) {}
    std::string get_name(void) { return name; }
    void flag_professor(std::shared_ptr<submission_t> __submission);
protected:
    std::string name;
};

struct submission_t {
    long id;
    std::shared_ptr<student_t> student;
    std::shared_ptr<professor_t> professor;
    std::string codefile;
};