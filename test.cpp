#include "dynamicLinker.hpp"
#include <iostream>
#include <memory>
#include <string>

void openException_test1() {
  const std::string path = "./test_.lib";
  auto dl = dynamicLinker::dynamicLinker::make_new(path);

  try {
    dl->open();
    auto f = dl->getFunction<int, int, int>("sum");
    std::cout << f( 2, 3 ) << std::endl;
  } catch( dynamicLinker::dynamicLinkerException e ) {
    std::cerr << e.what() << std::endl;
  }
}

void symbolException_test1() {
  const std::string path = "./test.lib";
  auto dl = dynamicLinker::dynamicLinker::make_new(path);

  try {
    dl->open();
    auto f = dl->getFunction<int, int, int>("sum_");
    std::cout << f( 2, 3 ) << std::endl;
  } catch( dynamicLinker::dynamicLinkerException e ) {
    std::cerr << e.what() << std::endl;
  }
}

void working_test1() {
  const std::string path = "./test.lib";
  auto dl = dynamicLinker::dynamicLinker::make_new(path);
  try {
    dl->open();
    auto f = dl->getFunction<int, int, int>("sum");
    std::cout << f( 2, 3 ) << std::endl;
  } catch( dynamicLinker::dynamicLinkerException e ) {
    std::cerr << e.what() << std::endl;
  }
}

void working_test2() {
  const std::string path = "./test.lib";

  try {
    {
      auto dl = dynamicLinker::dynamicLinker::make_new(path);
      dl->open();
      auto f = dl->getFunction<int, int, int>("sum");
      dl.reset();  // dl is not deleted, because f have shared_ptr to it
      std::cout << f( 2, 3 ) << std::endl;
    }
  } catch( dynamicLinker::dynamicLinkerException e ) {
    std::cerr << e.what() << std::endl;
  }
}

int main() {

  openException_test1();
  symbolException_test1();
  working_test1();
  working_test2();

  return 0;
}
