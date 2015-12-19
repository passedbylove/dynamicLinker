#include "dynamicLinker.hpp"
#include <iostream>
#include <memory>
#include <string>

void openException_test1() {
  const std::string path = "./test_.lib";
  auto dl = std::make_unique<dynamicLinker::dynamicLinker>(path);

  try {
    dl->open();
    auto f = dl->getFunction<int, int>("doubleIt");
    std::cout << f( 4 ) << std::endl;
  } catch( dynamicLinker::dynamicLinkerException e ) {
    std::cerr << e.what() << std::endl;
  }
}

void symbolException_test1() {
  const std::string path = "./test.lib";
  auto dl = std::make_unique<dynamicLinker::dynamicLinker>(path);

  try {
    dl->open();
    auto f = dl->getFunction<int, int>("doubleIt_");
    std::cout << f( 4 ) << std::endl;
  } catch( dynamicLinker::dynamicLinkerException e ) {
    std::cerr << e.what() << std::endl;
  }
}

void closedException_test1() {
  const std::string path = "./test.lib";
  auto dl = std::make_unique<dynamicLinker::dynamicLinker>(path);

  try {
    dl->open();
    auto f = dl->getFunction<int, int>("doubleIt");
    dl->explicitClose();
    std::cout << f( 4 ) << std::endl;
  } catch( dynamicLinker::dynamicLinkerException e ) {
    std::cerr << e.what() << std::endl;
  }
}

void closedException_test2() {
  const std::string path = "./test.lib";
  auto dl = new dynamicLinker::dynamicLinker(path);
  try {
    dl->open();
    auto f = dl->getFunction<int, int>("doubleIt");
    delete dl;
    std::cout << f( 4 ) << std::endl;
  } catch( dynamicLinker::dynamicLinkerException e ) {
    std::cerr << e.what() << std::endl;
  }
}

void working_test1() {
  const std::string path = "./test.lib";
  auto dl = new dynamicLinker::dynamicLinker(path);
  try {
    dl->open();
    auto f = dl->getFunction<int, int>("doubleIt");
    std::cout << f( 4 ) << std::endl;
  } catch( dynamicLinker::dynamicLinkerException e ) {
    std::cerr << e.what() << std::endl;
  }
}

int main() {

  openException_test1();
  symbolException_test1();
  closedException_test1();
  closedException_test2();
  working_test1();

  return 0;
}
