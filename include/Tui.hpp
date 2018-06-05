/* Copyright 2018 Khachatryan M. G., Chepic P. I. */
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>

#ifndef TUI_H
#define TUI_H


class TUI
{
 public:
    static int choose_operation();
    static bool CSVReader(std::vector <std::vector <double>> &features, std::vector <std::string> &classes,
                          int count_features, std::string path);
    static bool CSVReader(std::vector <std::vector <double>> &features, int count_features, std::string path);
    static bool CSVWriter(std::vector <std::string> real_class,std::vector <std::string> predicted_class,
                          std::string path);
    static bool CSVWriter(std::vector <std::vector <double>> features_to_predict,std::vector <std::string> predicted_class,
                          std::string path);
    static bool exist_file(std::string path);
    static bool sub_choose_test(std::vector <std::string> &real_class,std::vector <std::string> &predicted_class,
                                double accuracy);
    static bool sub_choose_predict(std::vector <std::vector <double>> &features_to_predict,
                                   std::vector <std::string> &predicted_class);
    static void extractFeature(std::vector <std::vector <double>> &features, std::vector <int> indexes);
 private:
    static std::vector <std::string> split(std::string strToSplit, char delimeter);
};

#endif // TUI_H

