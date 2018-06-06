/* Copyright 2018 Khachatryan M. G., Chepic P. I. */
#include "catch.hpp"
#include "Tree.hpp"
#include "Tui.hpp"
using namespace DecisionTree;
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
     DecTree* obj = new DecTree();
     DecTree::splitData(features,classes,train_X,train_Y,test_X,test_Y,70);
     obj->fit(train_X,train_Y);
     DecTree obj2(*obj);
     predicted = obj2.predict(test_X);
     double accuracy = DecTree::accuracy(test_Y,predicted);
     TUI::CSVWriter(test_Y,predicted,"../artifacts/real_predicted.csv");
     TUI::print(test_Y,predicted,accuracy);
     DecTree obj3;
     obj3 = obj2;
     obj3.visualiseTree("../artifacts/VisualTree_4feature");

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

     DecTree* obj4 = new DecTree();
     DecTree::splitData(features,classes,train_X,train_Y,test_X,test_Y,70);
     obj4->fit(train_X,train_Y);
     obj4->visualiseTree("../artifacts/VisualTree_2feature");
     DecTree obj5(std::move(*obj4));
     REQUIRE(obj4->empty());

     DecTree obj6;
     obj6 = std::move(obj3);
     REQUIRE(obj3.empty());
     TUI::CSVReader(features_to_predict,4,"iris_df_test.csv");
     predicted = obj6.predict(features_to_predict);
     TUI::CSVWriter(features_to_predict,predicted,"../artifacts/predict_results.csv");
     TUI::print(features_to_predict,predicted);
    
}
