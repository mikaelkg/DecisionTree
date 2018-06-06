/* Copyright 2018 Khachatryan M. G., Chepic P. I. */
#include "Tui.hpp"
#include "Tree.hpp"
using namespace DecisionTree;


int main() {

     int count_features;
     DecTree* obj = new DecTree();
     std::vector <std::vector <double>> features;
     std::vector <std::string> classes;

     std::vector <std::vector <double>> train_X;
     std::vector <std::vector <double>> test_X;

     std::vector <std::string> train_Y;
     std::vector <std::string> test_Y;

     std::vector <std::vector <double>> features_to_predict;
     while (true) {

            auto choice = TUI::choose_operation();
            switch (choice) {
                case 1: {
                    features.clear();
                    classes.clear();
                    train_X.clear();
                    test_X.clear();
                    train_Y.clear();
                    test_Y.clear();

                    std::string path;
                    std::cout << "Enter path: ";
                    std::cin >> path;
                    if (!TUI::exist_file(path)) {
                        std::cout << "File does not exist!\n";
                        break;
                    }
                    std::cout << "Count features: ";
                    std::cin >> count_features;
                    TUI::CSVReader(features,classes,count_features,path);
                    int percent;
                    std::cout << "Percent of train data:";
                    std::cin >> percent;
                    if (percent >=100 || percent <= 0) {
                        std::cout << "Not valud percent!\n";
                        break;
                    }
                    std::vector <std::string> predicted;
                    DecTree::splitData(features,classes,train_X,train_Y,test_X,test_Y,percent);
                    obj->fit(train_X,train_Y);
                    predicted = obj->predict(test_X);
                    double accuracy = DecTree::accuracy(test_Y,predicted);
                    if (!TUI::sub_choose_test(test_Y,predicted,accuracy)) {
                        std::cout << "Wrong option!\n";
                    }
                    break;
                }
                case 2: {
                    features_to_predict.clear();
                    if (obj->empty()) {
                        std::cout << "First you need to train decision tree!\n";
                        break;
                    }

                    std::vector <std::string> predicted;
                    std::string path;
                    std::cout << "Enter path: ";
                    std::cin >> path;

                    std::cout << "Count features: ";
                    std::cin >> count_features;

                    TUI::CSVReader(features_to_predict,count_features,path);
                    predicted = obj->predict(features_to_predict);
                    if (!TUI::sub_choose_predict(features_to_predict,predicted)) {
                        std::cout << "Wrong option!\n";
                    }
                    break;
                }
                case 3: {
                    if (obj->empty()) {
                        std::cout << "First you need to train decision tree!\n";
                        break;
                    }
                    std::string path;
                    std::cout << "Enter path: ";
                    std::cin >> path;

                    std::string sub_choice;
                    std::cout << "The file already exists, overwrite ? (Yes|No)\n";
                    std::cin >> sub_choice;
                    if (sub_choice == "Yes") {
                        obj->visualiseTree(path);
                        
                    } else if (sub_choice == "No"){
                        
                    } else {
                        std::cout << "Wrong option!\n";
                        
                    }
                    break;
                }
                case 4: {
                    std::string choose;
                    std::cout << "Are you sure you want to quit ? (Yes|No)\n";
                    std::cin >> choose;
                    if (choose == "Yes") {
                        delete obj;
                        return 0;
                    } else {
                        break;
                    }
                }
                default: {
                    std::cout << "Wrong option!\n";
                    break;
                }
            }
        }
}
