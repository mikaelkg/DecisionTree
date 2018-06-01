/* Copyright 2018 Khachatryan M. G., Chepic P. I.*/
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
namespace BSTTree {
struct Node {
    int data;
    Node* left;
    Node* right;
    explicit Node(int value);
};

Node* min_Node(Node* root);

enum class traversal_order {pre, in, post, wrong};
class Tree {
 public:
    Tree();
    explicit Tree(std::initializer_list <int> list);
    explicit Tree(const Tree& tree);
    explicit Tree(Tree&& tree);
    explicit Tree(std::vector <int> nodes);
    bool remove(int value);
    bool insert(int value);
    bool empty();
    void print(traversal_order order);
    bool exists(int value);
    void load(std::string path);
    void save(std::string path);
    auto operator=(const Tree& tree)->Tree&;
    auto operator=(Tree&& tree)->Tree&;
    auto friend operator<<(std::ostream& stream, const Tree&) -> std::ostream&;
    ~Tree();
 private:
    Node* root;
    void cleanup(Node* root);
    void pre_order(Node* root);
    void pre_order(Node* root, std::ofstream& out);
    void pre_order(Node* root, Tree* tree_copy);
    void in_order(Node* root);
    void post_order(Node* root);
    bool asistant_exists (Node* root, int value);
    Node* assistant_remove(Node* root, int value);
};

}  // namespace BSTTree

#endif  // INCLUDE_TREE_H_

