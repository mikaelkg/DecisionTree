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

    setdepth(root);
    return root;
};
unsigned depth(Node* root) {
    return root?root->depth:0;
}
void setdepth(Node* root) {
    unsigned  d_left = depth(root->left);
    unsigned  d_right = depth(root->right);
    root->depth = (d_left > d_right?d_left:d_right)+1;
}
Tree::Tree(std::vector <int> nodes) {
    create_tree(nodes);
}

void Tree::create_tree(std::vector <int> nodes) {
    for (auto i : nodes) {
        this->root = insert_Node(this->root, i);
    }
};

void Tree::output_tree(Node* root) {
    if (root == 0)    return;

    output_tree(root->right);
    std::string spaces;
    int count_spaces = this->root->depth - root->depth;
    for (int i = 0; i < count_spaces - 1; i++) {
        spaces+="  ";
    }
    if (count_spaces > 0) {
        spaces+="--";
    }
    std::cout << spaces << root->data << std::endl;
    output_tree(root->left);
};

void Tree::pre_order(Node* root) {
    if (root == 0)    return;

    std::cout << root->data << " ";
    pre_order(root->left);
    pre_order(root->right);
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

bool TUI::check_nodes(std::vector <int> nodes) {
    for (auto i : nodes) {
        if (i == 0) {
            return false;
        }
    }
    return true;
}
std::vector <int> TUI::preprocessing(std::vector <int> nodes) {
    std::vector <int> set_nodes;
    for (int i = 0; i < nodes.size(); i++) {
        int flag = 0;
        for (int j = 0; j < set_nodes.size(); j++) {
            if (nodes[i] == set_nodes[j]) {
                flag = 1;
            }
        }
        if (flag == 0) {
            set_nodes.push_back(nodes[i]);
        }
    }
    return set_nodes;
}

int TUI::choose_operation() {
    int choice;
    std::cout\
            <<"Select one of the following operations::\n"\
            <<"1. Display the tree on the screen\n"\
            <<"2. List the nodes of the tree\n"\
            <<"3. Add node to tree\n"\
            <<"4. Delete a node from a tree\n"\
            <<"5. Save the tree to a file\n"\
            <<"6. Load tree from file\n"\
            <<"7. Check the availability of the node\n"\
            <<"8. Quit the program\n";

    std::cin >> choice;
    return choice;
}

TUI::traversal_order TUI::sub_choose() {
    char choice;
    std::cout\
            <<"a. Direct bypass\n"\
            <<"b. Transversal bypass\n"\
            <<"c. Reverse bypass\n";
    std::cin >> choice;
    switch (choice) {
        case 'a': {
            return TUI::traversal_order::pre;
        }
        case 'b': {
            return traversal_order::in;
        }
        case 'c': {
            return traversal_order::post;
        }
        default: {
            return traversal_order::wrong;
        }
    }
}

}  // namespace BSTTree

