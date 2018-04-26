/* Copyright 2018 Khachatryan M. G., Chepic P. I.*/
#ifndef INCLUDE_TUI_H_
#define INCLUDE_TUI_H_
#include "Tree.hpp"
// namespace BSTTree
namespace BSTTree {
class TUI {
 public:

    static int choose_operation();
    static std::vector <int> preprocessing(int argc, char* argv[]);
    static bool check_nodes(std::vector <int> nodes);
    static traversal_order sub_choose();
};
}  // namespace BSTTree
#endif // INCLUDE_TUI_H_
