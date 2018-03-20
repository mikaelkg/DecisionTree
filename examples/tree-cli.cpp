#include "tree.hpp"
using namespace std;

int main(int argc, char** argv)
{
    vector <int> nodes;
    for (int i = 1; i < argc; i++) {
       nodes.push_back(atoi(argv[i]));
    }
    AVLTree::TREE* obj=new AVLTree::TREE(argc-1,nodes);
    obj->choose_operation();
    return 0;
}

