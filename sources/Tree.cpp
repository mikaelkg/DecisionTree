/* Copyright 2018 Khachatryan M. G., Chepic P. I. */
#include "Tree.hpp"
namespace BSTTree {
Node::Node(int value) {
    data = value;
    left = right = 0;
};

bool Tree::insert(int value) {
    if (this->root == 0) {
        this->root = new Node(value);
    } else {
        Node* bufer = this->root;
        while (true) {
            if ( value < bufer->data ) {
                if (bufer->left == 0) {
                    bufer->left = new Node(value);
                    break;
                } else {
                    bufer = bufer->left;
                }
            }
            if (value > bufer->data) {
                // if left not exists
                if (bufer->right == 0) {
                    bufer->right = new Node(value);
                    break;
                } else {
                     bufer = bufer->right;
                }
            }
            if (value == bufer->data) {
                return false;
            }
        }
    }
    return true;
};
bool Tree::empty() {
    return (this->root == 0);
}
Node* min_Node(Node* root) {
    if ( root->left == 0 ) {
        return root;
    }
    return min_Node(root->left);
}

Tree::Tree() {
    this->root = 0;
}

Tree::Tree(std::initializer_list<int> list) {
    this->root = 0;
    for (auto i : list) {
        insert(i);
    }
}
Tree::Tree(std::vector <int> nodes) {
    this->root = 0;
    for (auto i : nodes) {
        insert(i);
    }
}
void Tree::pre_order(Node* root) {
    if (root == 0)    return;

    std::cout << root->data << " ";
    pre_order(root->left);
    pre_order(root->right);
};
void Tree::pre_order(Node* root, std::ofstream& out) {
    if (root == 0)    return;
    out << root->data << " ";
    pre_order(root->left, out);
    pre_order(root->right, out);
};
void Tree::pre_order(Node* root, Tree* tree_copy) {
    if (root == 0)    return;
    tree_copy->insert(root->data);
    pre_order(root->left, tree_copy);
    pre_order(root->right, tree_copy);
};

void Tree::in_order(Node* root) {
    if (root == 0)    return;
    in_order(root->left);
    std::cout << root->data << " ";
    in_order(root->right);
};

void Tree::post_order(Node* root) {
    if (root == 0)    return;
    in_order(root->left);
    in_order(root->right);
    std::cout << root->data << " ";
};
Tree::~Tree() {
    cleanup(this->root);
}
void Tree::cleanup (Node* root) {
    if(root == 0) return;
    if(root->left != 0) {
        cleanup(root->left);
        root->left = 0;
    }
    if(root->right != 0 ) {
        cleanup(root->right);
        root->right = 0;
    }
    delete root;
  }
bool Tree::remove(int value) {
    if (this->exists(value)) {
        assistant_remove(this->root,value);
        return true;
    } else {
        return false;

    }
}
Node* Tree::assistant_remove(Node* root, int value) {
    if (root == 0) return root;
    if (value < root->data) {
        root->left = assistant_remove(root->left, value);
    } else if (value > root->data) {
        root->right = assistant_remove(root->right, value);
    } else if (value == root->data) {
        if (root->left != 0 && root->right != 0) {
            root->data = min_Node(root->right)->data;
            root->right = assistant_remove(root->right, root->data);
        } else {
            if (root->left != 0) {
                root = root->left;
            } else {
                root = root->right;
            }
        }
    }
    return root;
}
void Tree::print(traversal_order order) {
    switch (order) {
        case traversal_order::pre: {
            this->pre_order(this->root);
            std::cout << std::endl;
            break;
        }
        case traversal_order::in: {
            this->in_order(this->root);
            std::cout << std::endl;
            break;
        }
        case traversal_order::post: {
            this->post_order(this->root);
            std::cout << std::endl;
            break;
        }
        default: {
            std::cout << "Wrong option!\n";
            exit(0);
        }
    }
}
bool Tree::exists(int value) {
    return asistant_exists(this->root,value);
}
bool Tree::asistant_exists (Node* root, int value) {
    if ( root == 0) {
        return false;
    } else if (value < root->data) {
        return asistant_exists(root->left, value);
    } else if  (value > root->data) {
        return asistant_exists(root->right, value);
    } else {
        return true;
    }
}

void Tree::save(std::string path) {
    std::ofstream file(path);
    this->pre_order(this->root, file);
    file.close();
    std::cout << "The tree is successfully written!\n";
}
void Tree::load(std::string path) {
    std::ifstream file(path);
    int val;
    this->cleanup(this->root);
    this->root = 0;
    while (file >> val) {
        insert(val);
    }
    file.close();
    std::cout << "The tree was successfully loaded\n";
}
Tree::Tree(const Tree& tree) {
    this->root = 0;
    pre_order(tree.root,this);
}
Tree::Tree(Tree&& tree) {
    this->root = tree.root;
    tree.root = 0;
}
auto Tree::operator=(const Tree &tree)->Tree& {
    if (this != &tree) {
        cleanup(this->root);
        this->root = 0;
        pre_order(tree.root,this);
    }
    return *this;
}
auto Tree::operator=(Tree&& tree)->Tree& {
    this->root = tree.root;
    tree.root = 0;
    return *this;
}
auto operator<<(std::ostream& stream, const Tree& tree)->std::ostream& {
    if (tree.root == 0) {
        stream << "Tree is empty!\n";
        return stream;
    }
    int count_spaces=0;
    std::stack <Node*> nodeStack;
    std::stack <int> spacesStack;

    Node *curr = tree.root;
    while (true)
    {
        if (curr != 0)
        {
            spacesStack.push(count_spaces);
            nodeStack.push(curr);
            curr = curr->right;
            count_spaces+=1;
            continue;
        }
        if (nodeStack.empty())
        {
            return stream;;
        }
        do  {
            curr = nodeStack.top();
            nodeStack.pop();

            count_spaces=spacesStack.top();
            spacesStack.pop();

            std::string spaces;
            for (int i = 0; i < count_spaces - 1; i++) {
                spaces+="  ";
            }
            if (count_spaces > 0) {
                spaces+="--";
            }
            stream << spaces << curr->data << std::endl;

            } while (curr->left == 0 && !nodeStack.empty());
        curr = curr->left;
        count_spaces+=1;
    }

}

}  // namespace BSTTree

