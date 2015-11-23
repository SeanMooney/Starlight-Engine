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
#include "STARLIGHT_CORE\Shared.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <iterator>
#include <STARLIGHT_CORE\graphics\GLEW.h>
namespace starlight{
	namespace core{
		namespace utils{
			




			class STARLIGHTAPI Debug : public std::stringstream{
			private:
				std::ostream& out;
			public:
				Debug(std::ostream& stream=std::cout) :out(stream){}
				~Debug(){ flush(); }

				bool isEmpty(){ return this->rdbuf()->in_avail()==0; }

				void flush(){
#if STARLIGHT_DEBUG
					if(!isEmpty())
						out<<"DEBUG: "<<this->str()<<std::endl;
#endif
				}
			};

			class STARLIGHTAPI Error : public std::stringstream{
			private:
				std::ostream& out;
			public:
				Error(std::ostream& stream=std::cerr) :out(stream){}
				~Error(){ flush(); }

				bool isEmpty(){ return this->rdbuf()->in_avail()==0; }

				void flush(){
					out<<"ERROR: "<<this->str()<<std::endl;
				}
			};
			static void printGLError(char* file,char* func,int line){
				GLenum error=glGetError();
				if(error!=GL_NO_ERROR)
					Debug()<<"GL_ERROR: "<<error
					<<"\tFile: "<<file
					<<"\tFunction: "<<func
					<<"\tLine: "<<line;
			}
#define PRINT_GL_ERROR() starlight::core::utils::printGLError(__FILE__,__FUNCTION__,__LINE__)

		}
	}
}

