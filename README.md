[![Build Status](https://travis-ci.org/mikaelkg/DecisionTree.svg?branch=develop)](https://travis-ci.org/mikaelkg/DecisionTree)
[![Build Status](https://ci.appveyor.com/api/projects/status/github/mikaelkg/bsttree)](https://ci.appveyor.com/project/mikaelkg/decisiontree) 
# DecisionTree
Целью данного проекта является разработка программы для работы с бинарным деревом принятия решений (далее будем называть просто деревом) со следующим TUI:
```
Select one of the following operations::
1. Load data from a csv file  
   Divide the data into training and test samples.  
   Train decision tree on training data and test on test data  
Enter path:  
Count features:  
Percent of train data:  
a. Download the results to a file  
  (file with comma delimiter,  
   where first column is real class  
   and second column is predicted class)  
b. Output the results on the screen  
2. Load data from csv file and predict class  
   (possible only after training and the data format must match  
   the data format on which the decision tree was trained)  
Enter path:
Count features:  
a. Download the results to a file  
  (file with comma delimiter,  
   where first columns are features  
   and last column is predicted class)  
b. Output the results on the screen 
3. Generate dot and png file for visual representation of decision tree  
Enter path:  
4. Quit the program  
```

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

Документация: [:green_book:](https://mikaelkg.github.io/BSTTree/index.html)

Требования:
1. :white_check_mark: Все функции по работе с деревом должны находиться в
пространстве имен ${Type}Tree.
2. :white_check_mark: Структура узла должна иметь определённый прототип.
3. :white_check_mark: Класс дерева должна иметь определённый прототип.
4. :white_check_mark: Файлы исходного кода должны располагаться на сервисе GitHub
в открытом репозитории с названием ${Type}Tree.
5. :white_check_mark: Репозиторий ${Type}Tree должен иметь определённую структуру
6. :white_check_mark: Код должен быть читабельным и оформлен в едином стиле.
astyle
7. :white_check_mark: Файлы исходного кода должны пройти проверку утилитой
cpplint.
8. :white_check_mark: Оформить README.md файл, содержащий описание проекта.
9. :white_check_mark: Оформить .gitignore файл, создать отдельную ветку develop,
каждый этап помечать соответствующим тэгом.
10. :white_check_mark: Создать CMakeLists.txt для автоматизации сборки проекта.
11. :white_check_mark: Добавить в CMakeLists.txt автоматизацию процесса сборки
примеров.
12. :white_check_mark: Обеспечить 100% покрытие кода с использованием фреймворка
Catch.
13. :white_check_mark: Обеспечить непрерывный процесс сборки проекта с
использованием сервиса Travis CI .
14. :white_check_mark: Обеспечить непрерывный процесс сборки и тестирование проекта
с использованием сервисов Travis CI и AppVeyor.
15. :white_check_mark: Написать документацию к проекту с использованием инструмента
doxygen и разместить ее на сервисе GitHub Page.
16. :white_check_mark: Добавить в CMakeLists.txt автоматизацию процесса
пакетирования.
17. :x: Обеспечить размещение пакета проекта на сервисе GitHub
Release при успешном слиянии ветки develop и master.
