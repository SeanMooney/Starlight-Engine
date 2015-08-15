/*Copyright 2015 Sean Mooney

Licensed under the Apache License,Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/
#pragma once
#include <string>
#include <iostream>
#include "GLEW\GL\glew.h"
typedef GLuint STARLIGHT_UINT;
typedef GLint STARLIGHT_INT;
typedef GLfloat STARLIGHT_FLOAT;
typedef GLdouble STARLIGHT_DOUBLE;
typedef GLchar STARLIGHT_CHAR;

#if defined(STARLIGHT_CORE_LIBRARY_EXPORT) // inside DLL
#   define STARLIGHTAPI   __declspec(dllexport)
#else // outside DLL
#   define STARLIGHTAPI   __declspec(dllimport)
#endif  // XYZLIBRARY_EXPORT

#if defined(STARLIGHT_CORE_DOUBLE_PRECISSION) // libary precission
#   define STARLIGHT_PRECISSION   double
#else // outside DLL
#   define STARLIGHT_PRECISSION   float
#endif  // XYZLIBRARY_EXPORT

#if defined(STARLIGHT_DEBUG_OUTPUT) // define to enable addtional debug code
#   define STARLIGHT_DEBUG   1
#else // outside DLL
#   define STARLIGHT_DEBUG   0
#endif  // XYZLIBRARY_EXPORT

#ifndef CLANG
#define THROW(msg) throw std::exception::exception(msg);
#else
#define THROW(msg)  std ::cerr<<msg;  exit(-1);
#endif

#define _USE_MATH_DEFINES
#include <math.h>
namespace starlight{
	namespace core{


		
		


		class STARLIGHTAPI Shared{
		private:
			Shared();
			~Shared();
		public:
			static const std::string SHARED_MESSAGE;

		};
	}
}
