#include "catch.hpp"
#include <tree.hpp>

TEST_CASE("The nodes were recorded correctly", "[file]") {
  int argc=4;
  vector <int> nodes= {1,2,3};
  AVLTree::TREE* obj=new AVLTree::TREE(argc-1,nodes);

  REQUIRE(obj->root->data == 1);
  REQUIRE(obj->root->right->data == 2);
  REQUIRE(obj->root->right->right->data == 3);
}
