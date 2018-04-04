/* Copyright 2018 Khachatryan M. G., Chepic P. I. */
#include "Tree.hpp"
using namespace BSTTree;
int main(int argc, char* argv[]) {
    std::vector <int> nodes;
    for (int i = 1; i < argc; i++) {
        nodes.push_back(atoi(argv[i]));
    }
    nodes = {3, 2, 1, 4, 5};
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
                    obj->output_tree(obj->root);
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
                default: {
                    std::cout << "Wrong option!\n";
                    return 0;
                }
        }
    }
    return 0;
}

