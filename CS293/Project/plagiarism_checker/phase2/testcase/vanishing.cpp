#include <iostream>
#include <vector>
#include <memory>
#include <string>

struct node_t {
    std::string data;
    std::shared_ptr<node_t> right;
    std::weak_ptr<node_t> left;
};

void reset(std::weak_ptr<node_t>* root) {
    *root = std::shared_ptr<node_t>();
}

int main(void) {
    std::weak_ptr<node_t>* __root;
    if (true) {
        std::shared_ptr<node_t> root = std::make_shared<node_t>();
        root->data = "root";
        root->right = std::make_shared<node_t>();
        root->right->data = "right";
        root->right->left = root;
        root->right->right = std::make_shared<node_t>();
        root->right->right->data = "right right";
        root->right->right->left = root->right;
        root->right->right->right = root;
        root->left = root->right->right;
        __root = new std::weak_ptr<node_t>(root);
    }
    std::cout << "Root is " << __root->lock()->data << std::endl;
    std::cout << "Root's right is " << __root->lock()->right->data << std::endl;
    std::cout << "Root's right's left is " << 
        __root->lock()->right->left.lock()->data << std::endl;
    reset(__root);
    std::cout << "Now a null pointer " << __root->lock() << std::endl;
    std::cout << "I made the object vanish!" << std::endl;
    return 0;
}
