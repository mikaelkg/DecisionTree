/* Copyright 2018 Khachatryan M. G., Chepic P. I. */
#include "catch.hpp"
#include "Tree.hpp"
using namespace BSTTree;
TEST_CASE("Extra nodes must be removed", "[file]") {
  std::vector <int> nodes= {1, 2, 2, 3, 1};
  nodes = TUI::preprocessing(nodes);
  REQUIRE(nodes.size() == 3);
  REQUIRE(nodes[0] == 1);
  REQUIRE(nodes[1] == 2);
  REQUIRE(nodes[2] == 3);
}
