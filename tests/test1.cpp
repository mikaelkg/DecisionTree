/* Copyright 2018 Khachatryan M. G., Chepic P. I. */
#include "catch.hpp"
#include "Tree.hpp"
#include "Tui.hpp"
using namespace BSTTree;
TEST_CASE("Test program", "[file]") {
  std::vector <int> nodes= {8, 4, 2, 1, 3, 6, 5, 7, 12, 10, 9, 11, 14, 13, 15};
  Tree* obj = new Tree(nodes);
  Tree obj2{8, 4, 2, 1, 3, 6, 5, 7, 12, 10, 9, 11, 14, 13, 15};
  Tree obj3(obj2); 
  Tree obj4; 
  Tree obj5{5,3,6};
  obj4 = std::move(obj5);
  std::cout << "obj5 must be empty:\n" << obj5;
  Tree obj6(std::move(obj2));
  std::cout << "obj2 must be empty:\n" << obj2;
  Tree obj7{5,3,6};
  obj7 = obj6;
  std::cout << "obj7 must have the same tree as obj\n";
  std::cout << "content of obj7\n";
  std::cout<<obj7;
  std::cout << "content of obj\n";
  std::cout<<*obj;
  TUI::check_nodes(nodes);
  std::cout << "Direct bypass: ";
  obj->print(traversal_order::pre);
  std::cout << "Transversal bypass: ";
  obj->print(traversal_order::in);
  std::cout << "Reverse bypass: ";
  obj->print(traversal_order::post);
  obj->insert(30);
  REQUIRE(obj->empty()==false);
  REQUIRE(obj->exists(30) == true);
  REQUIRE(obj->insert(30)==false);
  obj->remove(30);
  REQUIRE(obj->exists(30) == false);
  obj->remove(4);
  REQUIRE(obj->remove(4)==false);
  REQUIRE(obj->exists(4) == false);
  obj->remove(3);
  obj->remove(2);
  std::string path = "test.txt";
  obj->save("test.txt");
  obj->load(path);
  delete obj;
  obj->print(traversal_order::wrong);
}
