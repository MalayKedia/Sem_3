#include <compare>
#include <concepts>
#include <string>

struct employee_t {
    // You should NOT add or remove ANY member variables/objects.
    std::string name;
    std::string department_name;
    long id_in_department;
    std::string job_title;
    double salary;
    // Do not add any private/public methods in this block.
    // Comparators should be implemented in the TODO section below
};

/* Your task is to ensure that the structure employee_t is totally ordered.
 * Note that the indexing of the employees is based fir on the department
 * name, then on the id_in_department. It is guaranteed that the combination
 * of department_name and id_in_department is unique.
 *
 * You should not modify the existing structure. Your task is to implement
 * comparators for the structure employee_t. Do read up on the C++20 spaceship
 * operator to understand how to implement the comparison operators, as that is
 * much faster to write than overloading the comparison operators individually.
 * Note that you still need to overload equality (==) operator alongwith the
 * spaceship (<=>) operator.
 *
 * As long as the final code is complied correctly and the ordering is done by
 * you correctly, you can add any helper functions you need and modify the 
 * TODO section as you see fit. Note that "correct ordering" implies that the
 * ordering is done based on the department_name first (alphabetical, just like
 * in a dictionary), and then on the id_in_department (numerical, ascending).
 *
 * Lastly, do not add `using namespace std;` as it is a bad practice.
 * The full problem involves the above task AND the task in the file
 * "is_valid_bst.h". You should complete both tasks.
 */

// TODO: Implement the comparison operators for the structure employee_t

bool operator == (const struct employee_t &lhs, const struct employee_t &rhs) {
  //TODO: implement ==
  return false; // dummy
}

std::strong_ordering operator <=> (const struct employee_t &lhs, 
                                    const struct employee_t &rhs) {
  //TODO: implement <==>
  return std::strong_ordering::less;//dummy
}

// End TODO
