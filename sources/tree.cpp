/* Copyright 2018 Khachatryan M. G. */

#include "tree.hpp"
namespace AVLTree {
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
};

TREE::TREE(int count_nodes, vector <int> nodes) {
    check_digits(count_nodes, nodes);
    create_tree(nodes);
}
void TREE::choose_operation() {
    cout\
            <<"Select one of the following operations::\n"\
            <<"1. Display the tree on the screen\n"\
            <<"2. List the nodes of the tree\n"\
            <<"3. Add node to tree\n"\
            <<"4. Delete a node from a tree\n"\
            <<"5. Save the tree to a file\n"\
            <<"6. Load tree from file\n"\
            <<"7. Check the availability of the node\n"\
            <<"8. Quit the program\n";

    cin >> choice;
    try {
        if (choice<1 || choice>8) {
            throw 1;
        }
        this->choice = choice;
    }
    catch(int x) {
        cout << "Wrong option!";
    }
}

void TREE::check_digits(int count_nodes, vector <int> nodes) {
    try {
        for (auto i : nodes) {
            if (i == 0) {
                throw 2;
            }
        }
        for (int i = 0; i < count_nodes - 1; i++) {
            for (int j = i+1; j < count_nodes; j++) {
                if (nodes[i] == nodes[j]) {
                    throw 3;
                }
            }
        }
    }
    catch(int x) {
        if (x == 2) {
            cout << "Wrong node!";
        } else {
            cout << "Duplicate nodes!";
        }
    }
};

void TREE::create_tree(vector <int> nodes) {
    for (auto i : nodes) {
        this->root = insert_Node(this->root, i);
    }
};
}  // namespace AVLTree
