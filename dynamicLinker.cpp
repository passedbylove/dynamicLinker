/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#include "dynamicLinker.hpp"

namespace dynamicLinker {

  dynamicLinker::dynamicLinker( std::string path ) : libPath(path) {
  }

  bool dynamicLinker::open() {
    lib = std::make_unique<_void>( dlopen( libPath.c_str(), RTLD_NOW | RTLD_LOCAL ) );

    if ( lib->ptr() == nullptr ) {
      lib = nullptr;
      throw openException();
    }

    return true;
  }

  bool dynamicLinker::explicitClose() {
    if( lib != nullptr ) {
      if( dlclose( lib->ptr() ) < 0 ) {
        // maybe now we should free lib->ptr() ?
        return false;
      }
      lib->null();
      lib = nullptr;
    }
    return true;
  }

  dynamicLinker::~dynamicLinker() {
    this->explicitClose();
  }

  dynamicLinker::_void::_void( void * ptr ) : myself(ptr) {}

  dynamicLinker::_void::~_void() {
    if( myself != nullptr )
      free(myself);
  }

  void * dynamicLinker::_void::ptr() const {
    return myself;
  }

  void dynamicLinker::_void::null() {
    myself = nullptr;
  }

}
