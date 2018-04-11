/* Copyright 2018 Khachatryan M. G., Chepic P. I. */
#include "Tree.hpp"
using namespace BSTTree;
int main(int argc, char* argv[]) {
    std::vector <int> nodes;
    for (int i = 1; i < argc; i++) {
        nodes.push_back(atoi(argv[i]));
    }
    if (TUI::check_nodes(nodes) == false) {
        std::cout << "Some nodes are not valid!\n";
        return 0;
    }
    nodes = TUI::preprocessing(nodes);

    Tree* obj = new Tree(nodes);

    while (true) {
        auto choice = TUI::choose_operation();
        switch (choice) {
            case 1: {
                if (obj->root == 0) {
                        std::cout << "Tree is empty!\n";
                        return 0;
                } else {
                    obj->output_tree(obj->root,0);
                }
                break;
            }
            case 2: {
                if (obj->root == 0) {
                        std::cout << "Tree is empty!\n";
                        return 0;
                } else {
                auto choice = TUI::sub_choose();
                switch (choice) {
                    case TUI::traversal_order::pre: {
                        obj->pre_order(obj->root);
                        std::cout << std::endl;
                        break;
                    }
                    case TUI::traversal_order::in: {
                        obj->in_order(obj->root);
                        std::cout << std::endl;
                        break;
                    }
                    case TUI::traversal_order::post: {
                        obj->post_order(obj->root);
                        std::cout << std::endl;
                        break;
                    }
                    default: {
                        std::cout << "Wrong option!\n";
                        return 0;
                    }
                }
                }
                break;
            }
            case 3: {
                int value;
                std::cout << "Enter a value for the new node: ";
                std::cin >> value;
                if (value == 0) {
                    std::cout << "Wrong value!\n";
                    return 0;
                } else if (TUI::exist_node(obj->root,value)) {
                    std::cout << "The node already exists in the tree\n";
                    break;

                } else {
                    obj->root = insert_Node(obj->root, value);
                    break;
                }


            }
            case 8: {
                std::string choice;
                std::cout << "Are you sure you want to quit ? (Yes|No)\n";
                std::cin >> choice;
                if (choice == "Yes") {
                    delete obj;
                    return 0;

                } else if (choice == "No") {
                    break;

                } else {
                    std::cout << "Wrong option!\n";
                    return 0;
                }


            }
                default: {
                    std::cout << "Wrong option!\n";
                    return 0;
                }
        }
    }
    return 0;
}

