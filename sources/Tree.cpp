/* Copyright 2018 Khachatryan M. G., Chepic P. I. */
#include "Tree.hpp"
namespace BSTTree {
Node::Node(int value) {
    data = value;
    left = right = 0;
};

Node* insert_Node(Node* root, int value) {
    if ( root == 0 ) {
        return new Node(value);
    } else if (value < root->data) {
        root->left = insert_Node(root->left, value);
    } else {
        root->right = insert_Node(root->right, value);
    }

    return root;
};
Node* min_Node(Node* root) {
    if ( root->left == 0 ) {
        return root;
    }
    return min_Node(root->left);
}

Tree::Tree(std::vector <int> nodes) {
    create_tree(nodes);
}

void Tree::create_tree(std::vector <int> nodes) {
    for (auto i : nodes) {
        this->root = insert_Node(this->root, i);
    }
};

void Tree::output_tree(Node* root, int count_spaces) {
    if (root == 0)    return;

    output_tree(root->right,count_spaces+1);
    std::string spaces;
    for (int i = 0; i < count_spaces - 1; i++) {
        spaces+="  ";
    }
    if (count_spaces > 0) {
        spaces+="--";
    }
    std::cout << spaces << root->data << std::endl;
    output_tree(root->left,count_spaces+1);
};

void Tree::pre_order(Node* root) {
    if (root == 0)    return;

    std::cout << root->data << " ";
    pre_order(root->left);
    pre_order(root->right);
};
void Tree::pre_order(Node* root, std::ofstream& out) {
    if (root == 0)    return;
    out << root->data << " ";
    pre_order(root->left, out);
    pre_order(root->right, out);
};
void Tree::in_order(Node* root) {
    if (root == 0)    return;


    in_order(root->left);
    std::cout << root->data << " ";
    in_order(root->right);
};

void Tree::post_order(Node* root) {
    if (root == 0)    return;


    in_order(root->left);
    in_order(root->right);
    std::cout << root->data << " ";
};
Tree::~Tree() {
    cleanup(this->root);
}
void Tree::cleanup (Node* root) {
    if(root == 0) return;
    if(root->left != 0) {
        cleanup(root->left);
        root->left = 0;
    }
    if(root->right != 0 ) {
        cleanup(root->right);
        root->right = 0;
    }
    delete root;
  }
Node* Tree::remove_Node(Node* root, int value) {
    if (root == 0) return root;
    if (value < root->data) {
        root->left = remove_Node(root->left, value);
    } else if (value > root->data) {
        root->right = remove_Node(root->right, value);
    } else if (value == root->data) {
        if (root->left != 0 && root->right != 0) {
            root->data = min_Node(root->right)->data;
            root->right = remove_Node(root->right, root->data);
        } else {
            if (root->left != 0) {
                root = root->left;
            } else {
                root = root->right;
            }
        }
    }
    return root;
}
void Tree::print(traversal_order order) {
    switch (order) {
        case traversal_order::pre: {
            this->pre_order(this->root);
            std::cout << std::endl;
            break;
        }
        case traversal_order::in: {
            this->in_order(this->root);
            std::cout << std::endl;
            break;
        }
        case traversal_order::post: {
            this->post_order(this->root);
            std::cout << std::endl;
            break;
        }
        default: {
            std::cout << "Wrong option!\n";
            exit(0);
        }
    }
}
bool Tree::exist_node(Node* root, int value) {
    if ( root == 0) {
        return false;
    } else if (value < root->data) {
        return exist_node(root->left, value);
    } else if  (value > root->data) {
        return exist_node(root->right, value);
    } else {
        return true;
    }

    return root;
}
bool Tree::exist_file(std::string path) {
    std::ifstream file(path);
    if (file.is_open()) {
        file.close();
        return true;
    } else {
        file.close();
        return false;
    }
}
void Tree::write_file(std::string path) {
    std::ofstream file(path);
    this->pre_order(this->root, file);
    file.close();
    std::cout << "The tree is successfully written!\n";
}
void Tree::read_file(std::string path) {
    std::ifstream file(path);
    int val;
    this->cleanup(this->root);
    this->root = 0;
    while (file >> val) {
        this->root = insert_Node(this->root, val);
    }
    file.close();
    std::cout << "The tree was successfully loaded\n";
}
}  // namespace BSTTree

