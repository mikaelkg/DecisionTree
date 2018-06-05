/* Copyright 2018 Khachatryan M. G., Chepic P. I. */
#include "Tree.hpp"
#include "Tui.hpp"
using namespace BSTTree;
int main(int argc, char* argv[]) {

    auto nodes = TUI::preprocessing(argc, argv);
    if (TUI::check_nodes(nodes) == false) {
        std::cout << "Some nodes are not valid!\n";
        return 0;
    }
    Tree* obj = new Tree(nodes);
    while (true) {
        auto choice = TUI::choose_operation();
        switch (choice) {
            case 1: {
                std::cout<<*obj;
                break;
            }
            case 2: {
                if (obj->empty()) {
                        std::cout << "Tree is empty!\n";
                        return 0;
                } else {
                    auto choice = TUI::sub_choose();
                    obj->print(choice);
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
                } else if (obj->exists(value)) {
                    std::cout << "The node already exists in the tree\n";
                    break;

                } else {
                    obj->insert(value);
                    break;
                }
            }
            case 4: {
                int value;
                std::cout << "Enter the node to delete: ";
                std::cin >> value;
                if (value == 0) {
                    std::cout << "Wrong value!\n";
                    return 0;
                } else {
                    obj->remove(value);
                    break;
                }
            }
            case 5: {
                std::string path;
                std::cout << "Enter the path to the file: ";
                std::cin >> path;
                if (TUI::exist_file(path)) {
                    std::string choice;
                    std::cout << "The file already exists, overwrite ? (Yes|No)\n";
                    std::cin >> choice;
                    if (choice == "Yes") {
                        obj->save(path);
                        break;
                    } else if (choice == "No") {
                        break;
                    } else {
                        std::cout << "Wrong option!\n";
                        return 0;
                    }
                } else {
                        obj->save(path);
                        break;
                }
            }
            case 6: {
                std::string path;
                std::cout << "Enter the path to the file: ";
                std::cin >> path;
                if (TUI::exist_file(path)) {
                    obj->load(path);
                    break;
                } else {
                        std::cout << "The file with the specified path does not exist!\n";
                        return 0;
                }
            }
            case 7: {
                int value;
                std::cout << "Enter the value for search: ";
                std::cin >> value;
                if (value == 0) {
                    std::cout << "Wrong option!\n";
                    return 0;
                } else {
                        if (obj->exists(value)) {
                            std::cout << "Node is found!\n";
                            break;
                        } else {
                            std::cout << "Node is not found!\n";
                            break;
                        }
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

