/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#if not defined (__unix__) && not defined(__unix) && not defined (unix) && ( (not defined (__APPLE__) || not defined (__MACH__)) )
  #error THIS SOFTWARE IS ONLY FOR UNIX-LIKE SYSTEMS!
#endif

#pragma once

#include <memory>
#include <iostream>
#include <dlfcn.h>
#include <functional>
#include <stdexcept>

namespace dynamicLinker {

  class dynamicLinkerException : public std::runtime_error {
  public:
    dynamicLinkerException ( const std::string& what_arg ) :
      std::runtime_error( what_arg ) {}
    dynamicLinkerException ( const char* what_arg ) :
      std::runtime_error( what_arg ) {}
  };

  class openException : public dynamicLinkerException {
  public:
    openException() : dynamicLinkerException("Cannot open dynamic library: " + std::string(dlerror())) {}
  };

  class symbolException : public dynamicLinkerException {
  public:
    symbolException() : dynamicLinkerException("Cannot find symbol: " + std::string(dlerror())) {}
  };

  class closedException : public dynamicLinkerException {
  public:
    closedException() : dynamicLinkerException("Dynamic library was closed. Cannot run function from it!") {}
  };

  class dynamicLinker {
  private:

    class _void {
    private:
      void * myself = nullptr;
    public:
      _void( void * );
      ~_void();
      void * ptr() const;
      void null();
    };

    template<typename R, typename A> class dlSymbol {
    private:
      std::function< R(A) > sym = nullptr;
      dynamicLinker &parent;
    public:
      dlSymbol( dynamicLinker &p, std::function< R(A) > s )
        : sym(s), parent(p) {}
      R operator()(A arg) {
        if( parent.lib == nullptr )
          throw closedException();
        return sym(arg);
      }
      std::function< R(A) > raw() {
        return sym;
      }
    };

    std::string libPath = "";
    std::unique_ptr<_void> lib = nullptr;
  public:
    dynamicLinker( std::string );
    ~dynamicLinker();
    bool open();
    bool explicitClose();
    template<typename R, typename A> dlSymbol<R,A> getFunction( std::string name ) {
      auto sym = dlSymbol<R,A>( *this, std::function< R(A) >(reinterpret_cast<  R(*)(A)  >(  dlsym(lib->ptr(), name.c_str())  )) );
      if( sym.raw() == nullptr )
        throw symbolException();
      return sym;
    }
  };

};
