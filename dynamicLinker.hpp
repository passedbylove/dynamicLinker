/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#if defined ( __GNUC__ ) && not defined ( __clang__ ) &&  __GNUC__ == 4 && ( __GNUC_MINOR__ < 8 || (  __GNUC_MINOR__ == 8 && __GNUC_PATCHLEVEL__ < 2 ) )
  #error GCC < 4.8.2 IS NOT SUPPORTED
#endif

#pragma once

#include <memory>
#include <iostream>
#include <functional>
#include <stdexcept>

#ifdef _WIN32
  #include <windows.h>
#else
  #include <dlfcn.h>
#endif

namespace dynamicLinker {

  class dynamicLinkerException : public std::runtime_error {
  public:
    explicit dynamicLinkerException ( const std::string& what_arg ) :
      std::runtime_error( what_arg ) {}
    explicit dynamicLinkerException ( const char* what_arg ) :
      std::runtime_error( what_arg ) {}
  };

  class openException : public dynamicLinkerException {
  public:
    explicit openException(std::string s) : dynamicLinkerException("ERROR: Cannot open dynamic library: " + s) {}
  };

  class symbolException : public dynamicLinkerException {
  public:
    explicit symbolException(std::string s) : dynamicLinkerException("ERROR: Cannot find symbol: " + s) {}
  };

  class closedException : public dynamicLinkerException {
  public:
    explicit closedException() : dynamicLinkerException("ERROR: Library was not opened!") {}
  };

  class symbolInitException : public dynamicLinkerException {
  public:
    explicit symbolInitException() : dynamicLinkerException("ERROR: Symbol was not initialized!") {}
  };

  class dynamicLinker : public std::enable_shared_from_this<dynamicLinker> {
  private:

    bool closeLib();
    void * openLib();

    class _void {
    private:
      void * myself = nullptr;
    public:
      explicit _void( void * );
      ~_void();
      void * ptr() const;
      void null();
    };


    template<typename T> class dlSymbol {};

    template<typename R, typename ...A> class dlSymbol< R(A...) >  {
    private:
      std::function< R(A...) > sym;
      std::shared_ptr<dynamicLinker> parent = nullptr;
      std::string name = "";
      void * getSymbol() {
        #ifdef _WIN32
          return GetProcAddress( (HINSTANCE) parent->lib->ptr() , name.c_str() );
        #else
          return dlsym( parent->lib->ptr(), name.c_str() );
        #endif
      }

    public:
      dlSymbol( std::shared_ptr<dynamicLinker> p, std::string n )
        : parent(p), name(n) {
          sym = std::function< R(A...) >(nullptr);
        }
      R operator()(A... arg) {
        if( sym != nullptr ) {
          return sym(arg...);
        }
        throw symbolInitException();
      }
      std::function< R(A...) > raw() {
        return sym;
      }
      void init() {

        if( parent->lib == nullptr )
          throw closedException();

        sym = std::function< R(A...) >(reinterpret_cast<  R(*)(A...)  >( getSymbol() ));

        if( sym == nullptr ) {
          char* err = nullptr;  //dlerror();
          std::string s = (err == nullptr) ? "FATAL ERROR: No error!" : std::string(err);
          throw symbolException(s);
        }
      }
    };


    std::string libPath = "";
    std::unique_ptr<_void> lib = nullptr;
    dynamicLinker();
    explicit dynamicLinker( std::string );
  public:
    static std::shared_ptr<dynamicLinker> make_new( std::string );
    ~dynamicLinker();
    bool open();
    template<typename T> dlSymbol<T> getFunction( std::string name ) {
      return dlSymbol<T>( shared_from_this(), name);
    }
  };

}; // namespace dynamicLinker
