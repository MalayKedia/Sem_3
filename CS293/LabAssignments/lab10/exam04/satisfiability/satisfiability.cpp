#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>

/**
 * ARE THESE EQUATIONS SATISFIABLE?
 * You are given a list of equations. You are to determine whether these are
 * satisifiable or not i.e. for all the variables present, is there a possible
 * assignment of values such that all equations are satisified. For instance,
 * "a == b, b == c, d == e" is satisfiable, but "a == b, b != a" is not.
 * Do not take more than O(n * (log(n))^2) time, where n is the number of
 * equations, since hidden testcases may have a large number of equations.
 * 
 * Alas! The equations are given all in one string and would be difficult to
 * parse! But don't worry, we have provided you with a function that will parse
 * the equations for you. The function will take the string of all equations
 * and create it into a vector of strings where each string is an equation.
 * Call it like `get_equations(all_equations)`.
 * 
 * We have provided you with one more helper function called `parse_equation`.
 * This is optional, but it converts an equation string into an array of
 * three strings, the first being an == or != according to the equation and the
 * second and third being the variables in the equation. You can use this if
 * you want, or you can parse the equations yourself. Note the equation strings
 * contain two varaibles (alphanumeric), separated by one of '==' or '!='.
 * There may or may not be spaces, but only between the variable names and the 
 * equality operator (variables themselves cannot contain spaces).
 * 
 * NOTE: You should NOT add ANY other includes. There's already all you need.
 * If at all you write log-statements, use cerr-debugging. If you print using
 * cout, then it will mess up the autograder. Ensure that your code has no
 * memory leaks or undefined behaviour, and that it compiles without warnings.
 */

// Add any helper methods, should you choose to, above this ---line---.

// -----------------------------------------------------------------------------

bool are_these_equations_satisfiable(std::string &all_equations,
        std::function<std::vector<std::string>(std::string&)> get_equations,
        std::function<std::array<std::string, 3>(std::string)> parse_equation) {
    // TODO: Write your code here
    return true; // default return value
    // END TODO;
}