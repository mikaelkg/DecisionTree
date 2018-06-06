[![Build Status](https://travis-ci.org/mikaelkg/DecisionTree.svg?branch=develop)](https://travis-ci.org/mikaelkg/DecisionTree)
[![Build Status](https://ci.appveyor.com/api/projects/status/github/mikaelkg/bsttree)](https://ci.appveyor.com/project/mikaelkg/decisiontree) 
# DecisionTree
Целью данного проекта является разработка программы для работы с бинарным деревом принятия решений со следующим TUI:

## Select one of the following operations:  
1. Load data from a csv file  
   Divide the data into training and test samples.  
   Train decision tree on training data and test on test data  
**Enter path:  
Count features:  
Percent of train data:**  
>a. Download the results to a file  
  (file with comma delimiter,  
   where first column is real class  
   and second column is predicted class)  
b. Output the results on the screen

2. Load data from csv file and predict class  
   (possible only after training and the data format must match  
   the data format on which the decision tree was trained)  
**Enter path:  
Count features:**  
>a. Download the results to a file  
  (file with comma delimiter,  
   where first columns are features  
   and last column is predicted class)  
b. Output the results on the screen 

3. Generate dot and png file for visual representation of decision tree  
**Enter path:**  
4. Quit the program  


Этапы:
1. :deciduous_tree: Реализовать 1 пункт меню
2. :deciduous_tree: Реализовать 2 пункт меню
3. :deciduous_tree: Реализовать 3 и 4 пункт меню
4. :deciduous_tree: Реализовать класс DecTree со следующим интерфейсом:
```сpp
namespace DecisionTree {
   class DecTree {
       public:
           DecTree();
           DecTree(const DecTree& tree);
           DecTree(DecTree&& tree);
           bool empty();
           void fit(std::vector <std::vector <double>> features,std::vector <std::string> classes);
           void visualiseTree(std::string path);
           std::vector <std::string> predict(std::vector <std::vector <double>> features);
           static double accuracy(std::vector <std::string> real_class,std::vector <std::string> predicted_class);
           static void splitData(std::vector <std::vector <double>> &features,
                                 std::vector <std::string> &classes,
                                 std::vector <std::vector <double>> &train_X,
                                 std::vector <std::string> &trainY,
                                 std::vector <std::vector <double>> &test_X,
                                 std::vector <std::string> &test_Y,int percent_train);
           auto operator=(const DecTree& tree)->DecTree&;
           auto operator=(DecTree&& tree)->DecTree&;
           ~DecTree();

       private:
           Node* root;
   }
}
```

Документация: [:green_book:](https://mikaelkg.github.io/DecisionTree/index.html)

Требования:
1. :white_check_mark: Все функции по работе с деревом должны находиться в
пространстве имен DecisionTree.
2. :white_check_mark: Структура узла должна иметь определённый прототип.
3. :white_check_mark: Класс дерева должна иметь определённый прототип.
4. :white_check_mark: Файлы исходного кода должны располагаться на сервисе GitHub
в открытом репозитории с названием DecisionTree.
5. :white_check_mark: Репозиторий DecisionTree должен иметь определённую структуру
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
