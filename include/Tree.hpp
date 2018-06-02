/* Copyright 2018 Khachatryan M. G., Chepic P. I.*/
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
namespace BSTTree {
struct Node {
    int data;
    Node* left;
    Node* right;
    explicit Node(int value);
};

Node* min_Node(Node* root);

enum class traversal_order {pre, in, post, wrong};
class Tree {
 public:
    //!Конструктор пустого дерева
    Tree();
    //!Конструктор списка инициализации
    explicit Tree(std::initializer_list <int> list);
    //!Конструктор копирования
    explicit Tree(const Tree& tree);
    //!Конструктор перемещения
    explicit Tree(Tree&& tree);
    //!Конструктор для вектора
    explicit Tree(std::vector <int> nodes);
    //!Удаление узла
    bool remove(int value);
    //!Вставка узла
    bool insert(int value);
    //!Проверка на то, пустое ли дерево
    bool empty();
    //!Вывести дереов с определенным обходом
    void print(traversal_order order);
    //!Проверить существование узла
    bool exists(int value);
    //!Загрузить дерево из файла
    void load(std::string path);
    //!Сохранить дерево в файл
    void save(std::string path);
    //!Перегруженный оператор присваивания копирования
    auto operator=(const Tree& tree)->Tree&;
    //!Перегруженный оператор присваивания перемещения
    auto operator=(Tree&& tree)->Tree&;
    //!Перегруженный оператор вывода
    auto friend operator<<(std::ostream& stream, const Tree&) -> std::ostream&;
    //!Деструктор
    ~Tree();
 private:
    //!Корень дерева
    Node* root;
    //!Вспомогательная функция для деструктора
    void cleanup(Node* root);
    //!Фнукция для вывода дерева прямым обходом
    void pre_order(Node* root);
    //!Функция для записи дерева прямым обходом в файл
    void pre_order(Node* root, std::ofstream& out);
    //!Функция для копирования дерева прямым обходом
    void pre_order(Node* root, Tree* tree_copy);
    //!Функция для вывода дерева поеречным обходом
    void in_order(Node* root);
    //!Функция для вывода дерева обратным обходом
    void post_order(Node* root);
    //!Вспомогательная функция для функции exists
    bool asistant_exists (Node* root, int value);
    //!Вспомогательная функция для функции remove
    Node* assistant_remove(Node* root, int value);
};

}  // namespace BSTTree

#endif  // INCLUDE_TREE_H_

