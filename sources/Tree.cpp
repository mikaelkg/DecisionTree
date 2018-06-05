/* Copyright 2018 Khachatryan M. G., Chepic P. I. */
#include "Tree.hpp"

namespace DecTree {
Node::Node(std::vector <std::vector <double>> features,std::vector <int> classes,
           int count_classes, std::map <int,std::string> reverse_dict) {
    X = features;
    Y = classes;

    values = count_in_class(classes,count_classes);
    gini = gini_index(values);
    class_ = reverse_dict[std::distance(values.begin(),std::max_element(values.begin(),values.end()))];
    threshold;
    feature_choose;
    left = nullptr;
    right = nullptr;
};
std::vector <int> Node::count_in_class(std::vector <int> classes,int count_classes) {
    std::vector <int> answer(count_classes);
    for (int i = 0; i < count_classes; i++) {
        int count_elements = std::count(classes.begin(),classes.end(),i);
        answer[i] = count_elements;
    }
    return answer;
}
void DecisionTree::splitData(std::vector <std::vector <double>> &features,
                             std::vector <std::string> &classes,
                             std::vector <std::vector <double>> &train_X,
                             std::vector <std::string> &train_Y,
                             std::vector <std::vector <double>> &test_X,
                             std::vector <std::string> &test_Y,int percent_train) {
   std::vector <int> rand_ind;
    for (int i = 0; i < classes.size(); i++) {
        rand_ind.push_back(i);
    }
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(rand_ind.begin(), rand_ind.end(), g);
    for (int i = 0; i < classes.size()*percent_train/100; i++) {
        train_X.push_back(features[rand_ind[i]]);
        train_Y.push_back(classes[rand_ind[i]]);
    }

    for (int i = (classes.size()*percent_train/100); i < classes.size(); i++) {
        test_X.push_back(features[rand_ind[i]]);
        test_Y.push_back(classes[rand_ind[i]]);
    }

}

double Node::gini_index(std::vector <int> values) {
    int count_values = std::accumulate(values.begin(),values.end(),0);
    double answer = 0;
    for (auto i: values) {
        double p = (double)i/count_values;
        answer += p*(1-p);
    }
    return answer;
}
DecisionTree::DecisionTree() {
    this->root = 0;
}
void DecisionTree::fit(std::vector <std::vector <double>> features,std::vector <std::string> classes) {
    cleanup(this->root);

    std::set <std::string> s;
    std::copy(std::begin(classes), std::end(classes), std::inserter(s, s.begin()));
    this->count_classes = s.size();
    this->count_features = features[0].size();
    std::map <std::string,int> dict;

    int counter = 0;
    for (auto i: s) {
        this->reverse_dict[counter] = i;
        dict[i] = counter;
        counter++;
    }
    std::vector <int> int_classes;
    for (auto i: classes) {
        int_classes.push_back(dict[i]);
    }

    this->root = new Node(features,int_classes,this->count_classes,this->reverse_dict);
    splitNode(this->root);
}
std::vector <std::string> DecisionTree::predict(std::vector <std::vector <double>> features) {
    std::vector <std::string> answer;
    for (auto i: features) {
        answer.push_back(helpPredict(this->root, i));
    }
    return answer;
}
std::string DecisionTree::helpPredict(Node* root, std::vector <double> feature) {
    if (root->feature_choose == -1) {
        return root->class_;
    } else if (feature[root->feature_choose] <= root->threshold) {
        return helpPredict(root->right,feature);
    } else {
        return helpPredict(root->left,feature);
    }

}
void DecisionTree::visualiseTree(std::string path) {
    std::string digraph = "";
    digraph += "digraph Tree {\n";
    digraph += "node [shape=box] ;\n";
    digraph += helpVisuliseTree(this->root);
    digraph += "}";

    std::ofstream file(path+".dot");
    file<<digraph;
    file.close();
    std::string command = fmt::format("dot -Tpng {0}.dot -o {0}.png",path);
    system(command.c_str());
}
std::string DecisionTree::helpVisuliseTree(Node* root) {
    static int depth = -1;
    static std::vector <int> distance;
    depth ++;
    std::string vec_string = "[ ";

    for (auto i: root->values) {
        vec_string += std::to_string(i) + " ";
    }
    vec_string += "]";
    std::string out = "";
    if (root->feature_choose != -1) {
     out = fmt::format("{} [label=\"X[{}] <= {}\\ngini = {:.2f}\\nvalue = {}\"] ;\n",
                                  depth,root->feature_choose,root->threshold,root->gini,vec_string);
    } else {
    out = fmt::format("{} [label=\"gini = {:.2f}\\nvalue = {}\\nclass = {}\"] ;\n",
                                  depth,root->gini,vec_string,root->class_);
    }
    if (distance.size() != 0) {
        out += fmt::format("{} -> {} ;\n",depth - distance[distance.size()-1],depth);
    }
    if (root->left != nullptr) {

        for (int i = 0; i < distance.size(); i++) {
            distance[i]++;
        }
        distance.push_back(1);
        out += helpVisuliseTree(root->left);
    }
    if (root->right != nullptr) {
        for (int i = 0; i < distance.size(); i++) {
            distance[i]++;
        }
        out += helpVisuliseTree(root->right);
        distance.pop_back();
    }

    return out;
}
void DecisionTree::splitNode(Node* root) {
    if (root->gini != 0) {
        std::map <std::string, double> dict = minsplitGiniIndex(root->X,root->Y,0);
        std::map <std::string, double> dict_new = dict;
        for (int i = 1; i < this->count_features; i++) {
            dict_new = minsplitGiniIndex(root->X,root->Y,i);
            if (dict_new["gini"] < dict["gini"]) {
                dict = dict_new;
            }
        }
        std::vector <std::vector <double>> root_left_X;
        std::vector <int> root_left_Y;

        std::vector <std::vector <double>> root_right_X;
        std::vector <int> root_right_Y;
        if (!dict["notDevidedFlag"]) {
            for (int i = 0; i < root->Y.size(); i++) {
                if (root->X[i][dict["feature_choose"]] <= dict["threshold"]) {
                    root_right_X.push_back(root->X[i]);
                    root_right_Y.push_back(root->Y[i]);
                } else {
                    root_left_X.push_back(root->X[i]);
                    root_left_Y.push_back(root->Y[i]);
                }
            }

            root->X.clear();
            root->Y.clear();
            root->threshold = dict["threshold"];
            root->feature_choose = dict["feature_choose"];

            root->left = new Node(root_left_X,root_left_Y,this->count_classes,this->reverse_dict);
            root->right = new Node(root_right_X,root_right_Y,this->count_classes,this->reverse_dict);

            splitNode(root->left);
            splitNode(root->right);
        }
    }
}
std::pair <double,bool> DecisionTree::splitGiniIndex(std::vector <std::vector <double>> features,
                                    std::vector <int> classes, int feature_choose,
                                    double threashold) {
    std::vector <int> left_classes(this->count_classes);
    std::vector <int> right_classes(this->count_classes);

    bool notDevidedFlag = false;
    int count_right_elements = 0;
    int count_left_elements = 0;
    for (int i = 0; i < classes.size(); i++) {
        if (features[i][feature_choose] <= threashold) {
            right_classes[classes[i]]++;
            count_right_elements++;
        } else {
            left_classes[classes[i]]++;
            count_left_elements++;
        }
    }
    int count_elements = count_left_elements+count_right_elements;
    double left_answer;
    double right_answer;
    if (count_left_elements == 0) {
        left_answer = 0;
        notDevidedFlag = true;
    } else {
        for (auto i: left_classes) {
            double p = (double)i/count_left_elements;
            left_answer += p*(1-p);
        }
    }
    for (auto i: right_classes) {
        double p = (double)i/count_right_elements;
        right_answer += p*(1-p);
    }

    left_answer = (double)count_left_elements/count_elements*left_answer;
    right_answer = (double)count_right_elements/count_elements*right_answer;
    return std::make_pair(left_answer + right_answer,notDevidedFlag);
}

std::map <std::string, double> DecisionTree::minsplitGiniIndex(std::vector <std::vector <double>> features,
                                       std::vector <int> classes, int feature_choose) {
        std::pair <double,bool> gini_and_flag;
        gini_and_flag = splitGiniIndex(features, classes, feature_choose, features[0][feature_choose]);
        double gini = gini_and_flag.first;
        bool notDevidedFlag = gini_and_flag.second;
        std::map <std::string, double> dict = {{"gini",gini},
                                               {"threshold", features[0][feature_choose]},
                                               {"feature_choose",feature_choose},
                                               {"notDevidedFlag",notDevidedFlag}};
        for (int i = 1; i < classes.size(); i++) {
            gini_and_flag = splitGiniIndex(features, classes, feature_choose, features[i][feature_choose]);
            gini = gini_and_flag.first;
            notDevidedFlag = gini_and_flag.second;
            if (gini < dict["gini"]) {
                dict["gini"] = gini;
                dict["threshold"] = features[i][feature_choose];
                dict["feature_choose"] = feature_choose;
                dict["notDevidedFlag"] = notDevidedFlag;
            }
        }
        return dict;
}
DecisionTree::~DecisionTree() {
    cleanup(this->root);
}
void DecisionTree::cleanup (Node* root) {
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
double DecisionTree::accuracy(std::vector <std::string> real_class,std::vector <std::string> predicted_class) {
    int correct = 0;
    int wrong = 0;
    for (int i = 0; i < real_class.size(); i++) {
        if (real_class[i] == predicted_class[i]) {
            correct++;
        } else {
            wrong++;
        }
    }
    return (double) correct / (correct + wrong);
}
bool DecisionTree::empty() {
    return (this->root == 0);
}
Node::Node(Node* root) {

    values = root->values;
    gini = root->gini;

    threshold = root->threshold;
    feature_choose = root->feature_choose;
    class_ = root->class_;
    left = nullptr;
    right = nullptr;
};
void DecisionTree::pre_order(Node* root, Node* &root_copy) {
    if (root == 0)    return;
    root_copy = new Node(root);
    pre_order(root->left, root_copy->left);
    pre_order(root->right, root_copy->right);
};
DecisionTree::DecisionTree(const DecisionTree& tree) {

    pre_order(tree.root,this->root);
    //std::cout << this->root->gini;
}
DecisionTree::DecisionTree(DecisionTree&& tree) {
    this->root = tree.root;
    tree.root = nullptr;
}
auto DecisionTree::operator=(const DecisionTree &tree)->DecisionTree& {
    if (this != &tree) {
        cleanup(this->root);
        this->root = 0;
        pre_order(tree.root,this->root);
    }
    return *this;
}
auto DecisionTree::operator=(DecisionTree&& tree)->DecisionTree& {
    this->root = tree.root;
    tree.root = nullptr;
    return *this;
}
} // namespace DecTree



