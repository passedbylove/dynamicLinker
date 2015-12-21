/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#include "dynamicLinker.hpp"
#include <iostream>
#include <memory>
#include <string>

typedef int sum_type ( int x, int y );

bool openException_test1() {
  bool catched = false;

  const std::string path = "./test_.lib";
  auto dl = dynamicLinker::dynamicLinker::make_new(path);

  try {
    dl->open();
    auto f = dl->getFunction< sum_type >("sum");
    std::cout << f( 2, 3 ) << std::endl;
  } catch( dynamicLinker::dynamicLinkerException e ) {
    std::cerr << "OK! Catched error from dl: " << e.what() << std::endl;
    catched = true;
  }

  return catched;
}

bool symbolException_test1() {
  bool catched = false;

  const std::string path = "./test.lib";
  auto dl = dynamicLinker::dynamicLinker::make_new(path);

  try {
    dl->open();
    auto f = dl->getFunction< sum_type >("sum_");
    std::cout << f( 2, 3 ) << std::endl;
  } catch( dynamicLinker::dynamicLinkerException e ) {
    std::cerr << "OK! Catched error from dl: " << e.what() << std::endl;
    catched = true;
  }

  return catched;
}

int working_test1() {
  int result = 0;

  const std::string path = "./test.lib";

  auto dl = dynamicLinker::dynamicLinker::make_new(path);
  try {
    dl->open();
    auto f = dl->getFunction< sum_type >("sum");
    result = f( 2, 3 );
  } catch( dynamicLinker::dynamicLinkerException e ) {
    std::cerr << e.what() << std::endl;
  }

  return result;
}

int working_test2() {
  int result = 0;

  const std::string path = "./test.lib";

  try {
    {
      auto dl = dynamicLinker::dynamicLinker::make_new(path);
      dl->open();
      auto f = dl->getFunction< sum_type >("sum");
      dl.reset();  // dl is not deleted, because f have shared_ptr to it
      result = f( 2, 3 );
    }
  } catch( dynamicLinker::dynamicLinkerException e ) {
    std::cerr << e.what() << std::endl;
  }

  return result;
}

int main() {

  int value = 5;

  if( !openException_test1() )
    return 1;
  if( !symbolException_test1() )
    return 2;
  if( working_test1() != value )
    return 3;
  if ( working_test2() != value )
    return 4;

  return 0;
}
