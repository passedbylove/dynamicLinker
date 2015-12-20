/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#include "dynamicLinker.hpp"

namespace dynamicLinker {

  dynamicLinker::dynamicLinker( std::string path ) : libPath(path) {
  }

  std::shared_ptr<dynamicLinker> dynamicLinker::make_new( std::string path ) {
    auto x = new dynamicLinker(path);
    return std::shared_ptr<dynamicLinker>(x);
  }

  bool dynamicLinker::open() {
    // C++14:
    // lib = std::make_unique<_void>( dlopen( libPath.c_str(), RTLD_NOW | RTLD_LOCAL ) );
    _void * v = new _void( dlopen( libPath.c_str(), RTLD_NOW | RTLD_LOCAL ) );
    lib = std::unique_ptr<_void>( v );

    if ( lib->ptr() == nullptr ) {
      lib = nullptr;
      char* err = dlerror();
      std::string s = (err == nullptr) ? "FATAL ERROR: no error!" : std::string(err);
      throw openException(s);
    }

    return true;
  }

  dynamicLinker::~dynamicLinker() {
    if( lib != nullptr ) {
      if( dlclose( lib->ptr() ) < 0 ) {
        // maybe now we should free lib->ptr() ?
        return;
      }
      lib->null();
      lib = nullptr;
    }
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
