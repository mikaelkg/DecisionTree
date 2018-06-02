[![Build Status](https://travis-ci.org/mikaelkg/BSTTree.svg?branch=develop)](https://travis-ci.org/mikaelkg/BSTTree)
# BSTTree
Целью данного проекта является разработка программы для работы с двоичным деревом поиска (далее будем называть просто деревом) со следующим TUI:
### Select one of the following operations::
1. Display the tree on the screen
2. List the nodes of the tree
   a. Direct Bypass
   b. Transverse bypass
   c. Reverse bypass
3. Add node to tree
4. Delete a node from a tree
5. Save the tree to a file
6. Load tree from file
7. Check the availability of the node
8. Quit the program


Этапы:
1. :deciduous_tree: Реализовать обработку входных данных
2. :deciduous_tree: Реализовать 1 пункт меню - вывод дерева в стандартный поток вывода
3. :deciduous_tree: Реализовать 2 пункт меню - вывод списка узлов дерева в стандартный 
                    поток вывода с использованием указанного подхода
4. :deciduous_tree: Реализовать 8 пункт меню - завершение работы программы
5. :deciduous_tree: 
- Реализовать 3 пункт меню - добавление узла в дерево. 
- Реализовать 4 пункт меню - удаление узла из дерева
6. :deciduous_tree: Реализовать 5 пункт меню - сохранение дерева в файл
7. :deciduous_tree: 
- Реализовать 6 пункт меню - загрузка дерева из файла. 
- Реализовать 7 пункт меню - проверка наличия узла
8. :deciduous_tree: Реализовать класс Tree со следующим интерфейсом:
```сpp
namespace ${Type}Tree 
{
  enum class traversal_order {pre, in, post};
  class Tree {
  public:
    Tree();
    Tree(std::initializer_list<int> list);
    Tree(const Tree& tree);
    Tree(Tree&& tree);
    bool insert(int value);
    bool exists(int value);
    bool remove(int value);
    bool save(const string& path);
    bool load(const string& path);
    void print(traversal_order order);
    auto friend operator<<(ostream& stream, const Tree&) -> ostream& stream;
    auto operator=(const Tree&) -> Tree&;
    auto operator=(Tree&&) -> Tree&;
    ~Tree();
  private:
    Node* root;
  };
}
```
