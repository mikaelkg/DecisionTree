/* Copyright 2018 Khachatryan M. G., Chepic P. I. */
#ifndef DECISIONTREE_H
#define DECISIONTREE_H
#define FMT_HEADER_ONLY
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <fstream>
#include <fmt/format.h>
#include <string>
#include <stdio.h>
#include <random>
#include <stdlib.h>

namespace DecisionTree {
struct Node {
    std::vector <std::vector <double>> X;
    std::vector <int> Y;
    std::vector <int> values;
    double threshold;
    int feature_choose = -1;
    double gini;
    std::string class_;
    Node* left;
    Node* right;

    Node(std::vector <std::vector <double>> features,std::vector <int> classes,
         int count_classes, std::map <int,std::string> reverse_dict);
    std::vector <int> count_in_class(std::vector <int> classes,int count_classes);
    double gini_index(std::vector <int> values);

    Node(Node* root);

};

class DecTree
{
    public:
	//!Стандартный конструктор
        DecTree();
	//!Конструктор копирования
        explicit DecTree(const DecTree& tree);
	//!Конструктор перемещения
        explicit DecTree(DecTree&& tree);
	//!Метод для определения, пустое ли дерево
        bool empty();
	//!Обучение дерева
        void fit(std::vector <std::vector <double>> features,std::vector <std::string> classes);
	//!Визуализация дерева
        void visualiseTree(std::string path);
	//!Определить класс объектов по вектору признаков
        std::vector <std::string> predict(std::vector <std::vector <double>> features);
	//!Определить точность работы
        static double accuracy(std::vector <std::string> real_class,std::vector <std::string> predicted_class);
	//!Разлелить данные на тестовые и тренировочные подвыборки
        static void splitData(std::vector <std::vector <double>> &features,
                              std::vector <std::string> &classes,
                              std::vector <std::vector <double>> &train_X,
                              std::vector <std::string> &trainY,
                              std::vector <std::vector <double>> &test_X,
                              std::vector <std::string> &test_Y,int percent_train);
	//!Оператор присваивания для копирования
        auto operator=(const DecTree& tree)->DecTree&;
	//!Оператор присваивани для перемещения
        auto operator=(DecTree&& tree)->DecTree&;
	//!Деструктор
        ~DecTree();

    private:
	//!Количество классов участвоваших в обучении
        int count_classes;
	//!Количество признаков у каждого объекта
        int count_features;
	//!Словарь для перевода из чисел обратно в названия классов
        std::map <int,std::string> reverse_dict;
	//!Корень дерева
        Node* root;
	//!Вспомогательная функция для predict
        std::string helpPredict(Node* root, std::vector <double> feature);
	//!Разделение узлов по наиболее эффективному порогу
        void splitNode(Node* root);
	//!Вычислить индекс gini при конкретном пороге
        std::pair <double,bool> splitGiniIndex(std::vector <std::vector <double>> features,
                                       std::vector <int> classes, int feature_choose,
                                       double threashold);
	//!Вычислить порог при котором индекс gini минимален
        std::map <std::string, double> minsplitGiniIndex(std::vector <std::vector <double>> features,
                               std::vector <int> classes, int feature_choose);
	//!Вспомогательная функция для визуализации
        std::string helpVisuliseTree(Node* root);
	//!Функция для очистки дерева
        void cleanup(Node* root);
	//!Прямой обход дерева (нужен только для оператора копирования)
        void pre_order(Node* root, Node* &root_copy);
};
} // namespace DecTree
#endif // DECISIONTREE_H

