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
#include <mutex>
#include <cereal\archives\portable_binary.hpp>
#include <cereal\archives\json.hpp>
#include <cereal\archives\xml.hpp>

#include "GLEW\GL\glew.h"
typedef  unsigned int  STARLIGHT_UINT;
typedef  int		   STARLIGHT_INT;
typedef  float		   STARLIGHT_FLOAT;
typedef  double	       STARLIGHT_DOUBLE;
typedef  char		   STARLIGHT_CHAR;

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
#define abstract =0
#endif

#ifndef STARLIGHT_ARCHIVE_BINARY
#define STARLIGHT_OUTPUT_ARCHIVE cereal::JSONOutputArchive
#define STARLIGHT_INPUT_ARCHIVE cereal::JSONInputArchive
#else
#define STARLIGHT_OUTPUT_ARCHIVE cereal::BinaryOutputArchive
#define STARLIGHT_INPUT_ARCHIVE cereal::BinaryInputArchive
#endif

#define _USE_MATH_DEFINES
#include <math.h>
namespace starlight{
	namespace core{
		template<typename P>
		class BindGaurd{
		private:
			std::lock_guard<std::mutex> lock;
			P& parent;
		public:
			BindGaurd(BindGaurd&&)=default;
			BindGaurd(const P* parent,std::mutex& lock) 
				:parent((P&)(*parent)),lock(lock){
				this->parent.bind();
			}
			~BindGaurd(){ this->parent.unbind(); }
			//friend P;
		};

		class STARLIGHTAPI Shared{
		private:
			Shared();
			~Shared();
		public:
			static const std::string SHARED_MESSAGE;
		};
	}
}
