#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
using namespace std;
namespace AVLTree
{
struct Node
{
    int data;
    Node* left;
    Node* right;
    Node(int value);

};
Node* insert_Node(Node* root, int value);
class TREE
{
public:
    int choice;
    Node* root=0;
    TREE(int count_nodes, vector <int> nodes);
    void choose_operation();
    void check_digits(int count_nodes,vector <int> nodes);
    void create_tree(vector <int> nodes);

};
}

