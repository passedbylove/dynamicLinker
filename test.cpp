#include "dynamicLinker.hpp"
#include <iostream>
#include <memory>
#include <string>

typedef int (funType)( int );

int main() {

  const std::string path = "./testLib.so.1.0";
  auto dl = std::make_unique<dynamicLinker::dynamicLinker>(path);
  dl->open();

  auto f = dl->getFunction<funType>("doubleIt");

  std::cout << f( 4 ) << std::endl;

  return 0;
}
