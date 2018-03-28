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
        auto choise = TUI::choose_operation();
        switch (choise) {
            case 1: {
                if (obj->root == 0) {
                        std::cout << "Tree is empty!\n";
                        return 0;
                } else {
                    obj->output_tree(obj->root);
                }
                break;
                }
                default:
                    std::cout << "Wrong option!\n";
                    return 0;
                    }
    }
    return 0;
}

