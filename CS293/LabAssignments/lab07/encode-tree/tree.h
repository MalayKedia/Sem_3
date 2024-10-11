#ifndef FBB5B07F_E120_4218_8ECA_8976E851F0D3
#define FBB5B07F_E120_4218_8ECA_8976E851F0D3

#include <array>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#define MAX_SIZE 9

/* You should NOT modify ANYTHING in this file
 *
 * Often, we face requirements to store things onto files. Data structures
 * cannot be stored directly onto files as such. They need to be converted
 * to strings before they can be written onto the file. Further, if you
 * cannot read them off the file and recover the data structures, then
 * the whole point is lost.
 * 
 * Your taks is to implement the encoding of TWO versions of N-ary trees:
 * The first is a "variable" tree: each node has a variable number of children
 * but no NULL child. The variability is indicated by the use of std::vector.
 * The second is a "fixed" tree: the number of children (and their order) of
 * each node is fixed, and there can be NULL children (N = 2 ==> binary tree).
 * This fixed-ness is indicated by the use of std::array.
 * 
 * How you encode and decode them is up to you, but, for any finite, valid tree
 * of either kind, decoding the encoded tree should produce a copy of the same.
 * Notice the use of the word "copy": you should not just encode the pointers.
 * This is because if it is written onto a file which is read by another 
 * program, then the tree cannot be recovered. It is guaranteed that the
 * input to the method "encode_tree" is a valid tree of either kind, and that
 * the input to "decode_tree" is an output off YOUR encoding only.
 * 
 * POLYMORPHISM ALERT
 * If you do not know what polymorphism is, it means that the same pointer
 * can point to different class objects. Specifically, shared_ptr<node_t>
 * can either refer to a pointer to a plain object of type `node_t` (you can
 * assume that this is not the case, since there is no tree), or to an
 * `n_ary_node_t` (variable tree object's root) or `fixed_node_t` (fixed tree).
 * The presence of any virtual method in the base class node_t makes it
 * polymorphic, so a pointer to it can point to itself or any derived class.
 * 
 * You do know know at compile time whether a pointer to the base class points
 * to a derived class or base class, and which derived class. Hence, you must
 * use `dynamic_cast<derived_class_name*>(ptr)` if `ptr` is a raw pointer, or
 * `std::dynamic_pointer_cast<derived_class_name>(ptr)` if `ptr` is a smart 
 * pointer, which is the case here (std::shared_ptr). Specifically, you should
 * try this with each of the derived class names. If the cast fails (the object
 * is not of the type derived_class), then the cast returns NULL (nullptr).
 * You should check that too, using if loops at runtime.
 * 
 * Likewise, you should also ensure that the encodings of the two kinds of 
 * tries vary significantly enough so that your decoding method can, at runtime,
 * detect the type of tree and construct it. Take care of encoding of nodes with
 * variable children (n_ary_node_t), the value N (fixed_node_t) as well as
 * null nodes. You can assume that children of one node are of the same type as
 * the node, and that nothing points directly to parent class (node_t) object.
 * 
 * INTEGER PARAMETER TEMPLATES
 * For the use of fixed size trees, the value N is a template that is known
 * at compile time. But since this template belongs to its derived class, 
 * your method (both encoding and decoding) when it takes care of the 
 * polymorphic behaviour of pointer, should also take care of the variability
 * of N. Since the range of N is small (between 1 and 9), there are only 9 
 * cases in all for fixed-size tree and your method should handle all 9 cases.
 * Specifically, when encoding, you should test separately using if loops
 * by dynamic_cast-ing to fixed_node_t<1>, fixed_node_t<2>, ...
 * You can see the "main.cpp" file for examples on such usecases.
 * 
 * You may wonder, couldn't we use a for-loop? The answer is no. Template
 * parameters should be evaluated at compile time, while everything in a 
 * for loop except the initializer statment (for (<initializer>;<cond>;<incr>)),
 * is evaluated at runtime. There are methods to prevent writing the same code
 * 9 times (or more, if N can take large values) but those involve
 * super-complicated templated code so we do not expect you to do so.
 * You can, however, just check the cases (dynamic cast 9 times) and call
 * a sub-routine that uses a templated parameter and encodes/decodes,
 * much like we have done in "main.cpp" file.
 * */

struct node_t {
    long val = 0;
    virtual ~node_t() {}
};

struct n_ary_node_t : public node_t {
    class std::vector<std::shared_ptr<node_t>> children;
};

template <size_t N = 0>
struct fixed_node_t : public node_t {
    static_assert(N <= MAX_SIZE && N >= 1);
    class std::array<std::shared_ptr<node_t>, N> children = {nullptr};
};

std::string encode_tree(std::shared_ptr<node_t> root);
std::shared_ptr<node_t> decode_tree(std::string encoded);

#endif /* FBB5B07F_E120_4218_8ECA_8976E851F0D3 */
