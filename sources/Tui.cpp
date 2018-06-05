/* Copyright 2018 Khachatryan M. G., Chepic P. I. */
#include "Tui.hpp"
std::vector <std::string> TUI::split(std::string strToSplit, char delimeter) {
    std::stringstream ss(strToSplit);
    std::string item;
	std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
	{
		splittedStrings.push_back(item);
    }
	return splittedStrings;
}
bool TUI::CSVWriter(std::vector <std::string> real_class,std::vector <std::string> predicted_class,
                    std::string path) {
    std::ofstream file(path);
    for (int i = 0; i < real_class.size() - 1; i++) {
        file << real_class[i] << ',' << predicted_class[i] << std::endl;
    }
    file << real_class[real_class.size() - 1] << ',' << predicted_class[real_class.size() - 1];
    file.close();
}
bool TUI::CSVWriter(std::vector <std::vector <double>> features_to_predict,std::vector <std::string> predicted_class,
                    std::string path) {
    std::ofstream file(path);
    for (int i = 0; i < predicted_class.size() - 1; i++) {
        for (int j = 0; j < features_to_predict[0].size(); j++) {
            file << features_to_predict[i][j] << ',';
        }
        file << predicted_class[i] << std::endl;
    }
    for (int j = 0; j < features_to_predict[0].size(); j++) {
        file << features_to_predict[predicted_class.size() - 1][j] << ',';
    }
    file << predicted_class[predicted_class.size() - 1];
    file.close();
}
bool TUI::CSVReader(std::vector <std::vector <double>> &features, std::vector <std::string> &classes,
                    int count_features, std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        file.close();
        return false;
    }
    std::vector <std::string> split_string;
    std::string str;
    while (std::getline(file,str,'\n')) {
        split_string = split(str,',');
        if (split_string.size() < count_features) {
            break;
        }
        std::vector <double> arr(count_features);
        features.push_back(arr);
        for (int i = 0; i < split_string.size() - 1; i++ ){
            features[features.size()-1][i] = atof(split_string[i].c_str());
        }
        classes.push_back(split_string[count_features]);
    }
    file.close();
    return true;
}
bool TUI::CSVReader(std::vector <std::vector <double>> &features,int count_features, std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        file.close();
        return false;
    }
    std::vector <std::string> split_string;
    std::string str;
    while (std::getline(file,str,'\n')) {
        split_string = split(str,',');
        if (split_string.size() < count_features) {
            break;
        }
        std::vector <double> arr(count_features);
        features.push_back(arr);
        for (int i = 0; i < split_string.size() - 1; i++ ){
            features[features.size()-1][i] = atof(split_string[i].c_str());
        }
    }
    file.close();
    return true;
}
int TUI::choose_operation() {
    int choice;
    std::cout\
            <<"Select one of the following operations:\n"\
            <<"1. Load data from a csv file\n"\
            <<"   Divide the data into training and test samples.\n"\
              "   Train decision tree on training data and test on test data\n"\
            <<"2. Load data from csv file and predict class\n"\
              "  (possible only after training and the data format must match\n"\
              "   the data format on which the decision tree was trained)\n"\
            <<"3. Generate dot and file for visual representation of decision tree\n"\
            <<"4. Quit the program\n";

    std::cin >> choice;
    return choice;
}
bool TUI::sub_choose_test(std::vector <std::string> &real_class,std::vector <std::string> &predicted_class,
                             double accuracy) {
    char decision;
    std::string path;
    std::cout << "a. Download the results to a file\n"\
                 "   (file with comma delimiter,\n"\
                 "    where first column is real class\n"\
                 "    and second column is predicted class)\n"\
              << "b. Output the results on the screen\n";
    std::cin >> decision;

    if (decision == 'a') {
        std::cout << "Enter path: ";
        std::cin >> path;
        if (TUI::exist_file(path)) {
            std::string sub_choice;
            std::cout << "The file already exists, overwrite ? (Yes|No)\n";
            std::cin >> sub_choice;
            if (sub_choice == "Yes") {
                TUI::CSVWriter(real_class,predicted_class,path);
                printf("Accuracy: %.2f%%\n",100*accuracy);
            } else if (sub_choice == "No") {
                return true;
            } else {
                std::cout << "Wrong option!\n";
            }
            return true;
        } else {
            TUI::CSVWriter(real_class,predicted_class,path);
            printf("Accuracy: %.2f%%\n",100*accuracy);
        }
    } else if (decision == 'b') {
        printf("%-30s %s","Real class","Predicted class\n");

        for (int i = 0; i < predicted_class.size(); i++) {
            printf("%-30s %s\n",real_class[i].c_str(),predicted_class[i].c_str());
        }
        printf("Accuracy: %.2f%%\n",100*accuracy);
        return true;
    } else {
        return false;
    }
}
bool TUI::sub_choose_predict(std::vector <std::vector <double>> &features_to_predict,
                             std::vector <std::string> &predicted_class) {
    char decision;
    std::string path;
    std::cout << "a. Download the results to a file\n"\
                 "   (csv file with comma delimiter,\n"\
                 "    where first column is real class\n"\
                 "    and second column is predicted class)\n"\
              << "b. Output the results on the screen\n";
    std::cin >> decision;

    if (decision == 'a') {
        std::cout << "Enter path: ";
        std::cin >> path;
        if (TUI::exist_file(path)) {
            std::string sub_choice;
            std::cout << "The file already exists, overwrite ? (Yes|No)\n";
            std::cin >> sub_choice;
            if (sub_choice == "Yes") {
                TUI::CSVWriter(features_to_predict,predicted_class,path);
            } else if (sub_choice == "No") {
                return true;
            } else {
                std::cout << "Wrong option!\n";
            }
            return true;
        } else {
            TUI::CSVWriter(features_to_predict,predicted_class,path);
        }
    } else if (decision == 'b') {
        for (int i = 0; i < features_to_predict[0].size(); i++) {
            printf("%s%-3i","Feature",i+1);
        }
            printf("%-10s\n","Class");
        for (int i = 0; i < predicted_class.size(); i++) {
            for (int j = 0; j < features_to_predict[0].size(); j++) {
                printf("%-10.2f",features_to_predict[i][j]);
            }
            printf("%s\n",predicted_class[i].c_str());
        }
        return true;
    } else {
        return false;
    }
}
bool TUI::exist_file(std::string path) {
    std::ifstream file(path);
    if (file.is_open()) {
        file.close();
        return true;
    } else {
        file.close();
        return false;
    }
}

void TUI::extractFeature(std::vector <std::vector <double>> &features, std::vector <int> indexes) {
    for (int i = 0; i < features.size(); i++) {
        std::vector <double> buf;
        for (int j = 0; j < indexes.size(); j++) {
            buf.push_back(features[i][indexes[j]]);
        }
        features[i] = buf;
    }
}
