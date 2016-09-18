/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#ifdef _WIN32
  #define TEST_LIB "./test.dll"
#else
  #define TEST_LIB "./test.lib"
#endif

#include "dynamicLinker.hpp"
#include <iostream>
#include <memory>
#include <string>

typedef int sum_type ( int x, int y );

bool openException_test1() {
  bool catched = false;

  const std::string path = "./none.lib";
  auto dl = dynamicLinker::dynamicLinker::make_new(path);
  auto f = dl->getFunction< sum_type >("sum");

  try {
    dl->open();
    f.init();
    std::cout << f( 2, 3 ) << std::endl;
  } catch( const dynamicLinker::dynamicLinkerException& e ) {
    //std::cerr << "OK! Catched exception from dl: " << e.what() << std::endl;
    catched = true;
  }

  return catched;
}

bool symbolException_test1() {
  bool catched = false;

  const std::string path = TEST_LIB;
  auto dl = dynamicLinker::dynamicLinker::make_new(path);
  auto f = dl->getFunction< sum_type >("sum_");

  try {
    dl->open();
    f.init();
    std::cout << f( 2, 3 ) << std::endl;
  } catch( const dynamicLinker::dynamicLinkerException& e ) {
    //std::cerr << "OK! Catched exception from dl: " << e.what() << std::endl;
    catched = true;
  }

  return catched;
}

bool closedException_test1() {
  bool catched = false;

  const std::string path = TEST_LIB;
  auto dl = dynamicLinker::dynamicLinker::make_new(path);
  auto f = dl->getFunction< sum_type >("sum");

  try {
    f.init();
    std::cout << f( 2, 3 ) << std::endl;
  } catch( const dynamicLinker::dynamicLinkerException& e ) {
    //std::cerr << "OK! Catched exception from dl: " << e.what() << std::endl;
    catched = true;
  }

  return catched;
}

bool symbolInitException_test1() {
  bool catched = false;

  const std::string path = TEST_LIB;
  auto dl = dynamicLinker::dynamicLinker::make_new(path);
  auto f = dl->getFunction< sum_type >("sum");

  try {
    dl->open();
    std::cout << f( 2, 3 ) << std::endl;
  } catch( const dynamicLinker::dynamicLinkerException& e ) {
    //std::cerr << "OK! Catched exception from dl: " << e.what() << std::endl;
    catched = true;
  }

  return catched;
}

int working_test1() {
  int result = 0;

  const std::string path = TEST_LIB;

  auto dl = dynamicLinker::dynamicLinker::make_new(path);
  auto f = dl->getFunction< sum_type >("sum");

  try {
    dl->open();
    f.init();
    result = f( 2, 3 );
  } catch( const dynamicLinker::dynamicLinkerException& e ) {
    std::cerr << e.what() << std::endl;
  }

  return result;
}

int working_test2() {
  int result = 0;

  const std::string path = TEST_LIB;
  auto dl = dynamicLinker::dynamicLinker::make_new(path);
  auto f = dl->getFunction< sum_type >("sum");

  try {
    dl->open();
    dl.reset();  // dl is not deleted, because f have shared_ptr to it
    f.init();
    result = f( 2, 3 );
  } catch( const dynamicLinker::dynamicLinkerException& e ) {
    std::cerr << e.what() << std::endl;
  }

  return result;
}

int test() {
  int value = 5;

  if( !openException_test1() ) {
    return 1;
  }
  if( !symbolException_test1() ) {
    return 2;
  }
  if( !closedException_test1() ) {
    return 3;
  }
  if( !symbolInitException_test1() ) {
    return 4;
  }
  if( working_test1() != value ) {
    return 5;
  }
  if ( working_test2() != value ) {
    return 6;
  }

  return 0;
}

int main() {

  int status = test();

  if( status == 0 ) {
    std::cout << "Test passed." << std::endl;
  } else {
    std::cerr << "Test failed!" << std::endl;
    return status;
  }

  return 0;

}
