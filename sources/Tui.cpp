#include "Tui.hpp"
namespace BSTTree {
bool TUI::check_nodes(std::vector <int> nodes) {
    for (auto i : nodes) {
        if (i == 0) {
            return false;
        }
    }
    return true;
}
std::vector <int> TUI::preprocessing(int argc, char* argv[]) {
    std::vector <int> nodes;
    for (int i = 1; i < argc; i++) {
        nodes.push_back(atoi(argv[i]));
    }
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
            <<"Select one of the following operations:\n"\
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

traversal_order TUI::sub_choose() {
    char choice;
    std::cout\
            <<"a. Direct bypass\n"\
            <<"b. Transversal bypass\n"\
            <<"c. Reverse bypass\n";
    std::cin >> choice;
    switch (choice) {
        case 'a': {
            return traversal_order::pre;
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

} // namespace BSTTree
