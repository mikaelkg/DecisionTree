/* Copyright 2018 Khachatryan M. G., Chepic P. I.*/
#include "iostream"
#include <vector>

namespace BSTTree {
struct Node {
    int depth = 0;
    int data;
    Node* left;
    Node* right;
    explicit Node(int value);
};
Node* insert_Node(Node* root, int value);

class Tree {
 public:
    int choice;
    Node* root = 0;
    explicit Tree(std::vector <int> nodes);
    void create_tree(std::vector <int> nodes);
    void output_tree(Node* root, int count_spaces);
    void pre_order(Node* root);
    void in_order(Node* root);
    void post_order(Node* root);
    void cleanup(Node* root);
    ~Tree();
};

class TUI {
 public:
    enum class traversal_order {pre, in, post, wrong};
    static int choose_operation();
    static std::vector <int> preprocessing(std::vector <int> nodes);
    static bool check_nodes(std::vector <int> nodes);
    static bool exist_node(Node* root, int value);
    static traversal_order sub_choose();
};
}  // namespace BSTTree

