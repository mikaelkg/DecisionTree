/* Copyright 2018 Khachatryan M. G., Chepic P. I.*/
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <iostream>
#include <vector>
#include <fstream>

namespace BSTTree {
struct Node {
    int data;
    Node* left;
    Node* right;
    explicit Node(int value);
};
Node* insert_Node(Node* root, int value);
Node* min_Node(Node* root);

enum class traversal_order {pre, in, post, wrong};
class Tree {
 public:
    int choice;
    Node* root = 0;
    explicit Tree(std::vector <int> nodes);
    void create_tree(std::vector <int> nodes);
    void output_tree(Node* root, int count_spaces);
    void pre_order(Node* root);
    void pre_order(Node* root, std::ofstream& out);
    void in_order(Node* root);
    void post_order(Node* root);
    void print(traversal_order order);
    bool exist_node(Node* root, int value);
    bool exist_file(std::string path);
    void write_file(std::string path);
    void read_file(std::string path);
    void cleanup(Node* root);

    Node* remove_Node(Node* root, int value);
    ~Tree();
};

}  // namespace BSTTree

#endif  // INCLUDE_TREE_H_

