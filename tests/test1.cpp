/* Copyright 2018 Khachatryan M. G., Chepic P. I. */
#include "catch.hpp"
#include "Tree.hpp"
#include "Tui.hpp"
using namespace DecTree;
TEST_CASE("Test program", "[file]") {
     std::vector <std::vector <double>> features;
     std::vector <std::string> classes;

     std::vector <std::vector <double>> train_X;
     std::vector <std::vector <double>> test_X;

     std::vector <std::string> train_Y;
     std::vector <std::string> test_Y;

     std::vector <std::vector <double>> features_to_predict;
     std::vector <std::string> predicted;

     TUI::CSVReader(features,classes,4,"iris_df.csv");
     DecisionTree* obj = new DecisionTree();
     DecisionTree::splitData(features,classes,train_X,train_Y,test_X,test_Y,70);
     obj->fit(train_X,train_Y);
     DecisionTree obj2(*obj);
     predicted = obj2.predict(test_X);
     double accuracy = DecisionTree::accuracy(test_Y,predicted);
     DecisionTree obj3;
     obj3 = obj2;
     obj3.visualiseTree("VisualTree_4feature");


     features.clear();
     classes.clear();
     train_X.clear();
     test_X.clear();
     train_Y.clear();
     test_Y.clear(); 
     features_to_predict.clear();
     predicted.clear();

     TUI::CSVReader(features,classes,4,"iris_df.csv");
     TUI::extractFeature(features,{0,1});

     DecisionTree* obj4 = new DecisionTree();
     DecisionTree::splitData(features,classes,train_X,train_Y,test_X,test_Y,70);
     obj4->fit(train_X,train_Y);
     obj3.visualiseTree("VisualTree_2feature");
     DecisionTree obj5(std::move(*obj4));                                                                                    REQUIRE(obj4->empty());
     DecisionTree obj6;
     obj6 = std::move(obj3);
     REQUIRE(obj3.empty()); 
}
