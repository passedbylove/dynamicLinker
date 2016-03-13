/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#ifdef _WIN32
  #define DLL_EXPORT __declspec( dllexport )
#else
  #define DLL_EXPORT
#endif

int DLL_EXPORT sum( int x, int y ) {
  return x+y;
}
