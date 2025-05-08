/*
 * Assignment 3 - Developing List Data Structures and Artificial Neural Networks
 * file : main.cpp
 * Data Structures and Algorithms
 * Author: Võ Tiến
 * Link FB : https://www.facebook.com/Shiba.Vo.Tien
 * Link Group : https://www.facebook.com/groups/khmt.ktmt.cse.bku
 * Date: 27.11.2024

g++ -fsanitize=address -fsanitize=undefined -std=c++17 -o main -Iinclude -Itest -Isrc main.cpp test/unit_test/graph/unit_test.cpp -DTEST_GRAPH
g++ -std=c++17 -o main -Iinclude -Itest -Isrc main.cpp test/unit_test/graph/unit_test.cpp -DTEST_GRAPH

 * run code
    * terminal unit test array list
./main test_unit
    !./main test_unit nameFunctionUnitTest
*/

#include "main.hpp"
#ifdef TEST_GRAPH
#include "unit_test/graph/unit_test.hpp"
const string TEST_CASE = "GRAPH";
#endif
void printTestCase();

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printTestCase();
    return 1;
  }

  std::string arg1 = argv[1];
  if (arg1 == "test_unit") {
    std::cout << GREEN << BOLD << "Running unit_test/" << TEST_CASE << RESET
              << "\n";
    handleTestUnit(argc, argv);
  } else if (arg1 == "test_random") {
    std::cout << GREEN << BOLD << "Running test_random/" << TEST_CASE << RESET
              << "\n";
    // handleTestRandom(argc, argv);
  } else {
    printTestCase();
  }
}

#ifdef TEST_GRAPH
void handleTestUnit(int argc, char *argv[]) {
  UNIT_TEST_Graph unitTest;

  if (argc == 2 || (argc == 3 && std::string(argv[2]) == "all")) {
    unitTest.runAllTests();
  } else if (argc == 3) {
    unitTest.runTest(argv[2]);
  } else {
    printTestCase();
  }
}
#endif

void printTestCase() {
  std::cout << GREEN << BOLD << "terminal unit test" << RESET << std::endl;
  std::cout << RED << "./main test_unit" << RESET << std::endl;
  std::cout << RED << "./main test_unit nameFunctionUnitTest" << RESET
            << std::endl
            << std::endl;
}