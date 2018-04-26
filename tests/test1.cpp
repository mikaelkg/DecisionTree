/* Copyright 2018 Khachatryan M. G., Chepic P. I. */
#include "catch.hpp"
#include "Tree.hpp"
#include "Tui.hpp"
using namespace BSTTree;
TEST_CASE("Test program", "[file]") {
  std::vector <int> nodes= {8, 4, 2, 1, 3, 6, 5, 7, 12, 10, 9, 11, 14, 13, 15};
  Tree* obj = new Tree(nodes);
  obj->output_tree(obj->root,0);
  TUI::check_nodes(nodes);
  std::cout << "Direct bypass: ";
  obj->print(traversal_order::pre);
  std::cout << "Transversal bypass: ";
  obj->print(traversal_order::in);
  std::cout << "Reverse bypass: ";
  obj->print(traversal_order::post);
  obj->root = insert_Node(obj->root, 30);
  REQUIRE(obj->exist_node(obj->root, 30) == true);
  obj->root = obj->remove_Node(obj->root, 30);
  REQUIRE(obj->exist_node(obj->root, 30) == false);
  obj->root = obj->remove_Node(obj->root, 4);
  REQUIRE(obj->exist_node(obj->root, 4) == false);
  obj->root = obj->remove_Node(obj->root, 3);
  obj->root = obj->remove_Node(obj->root, 2);
  std::string path = "test.txt";
  REQUIRE(obj->exist_file("not_file.txt") == false);
  obj->write_file("test.txt");
  REQUIRE(obj->exist_file(path) == true);
  obj->read_file(path);
  delete obj;
  obj->print(traversal_order::wrong);
}
