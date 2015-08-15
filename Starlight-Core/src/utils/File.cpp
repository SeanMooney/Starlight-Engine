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
#include "STARLIGHT_CORE\utils\File.h"
#include "STARLIGHT_CORE\utils\Log.h"
namespace starlight{
	namespace core{
		namespace utils{

			std::string File::readFile(const std::string& path,int mode){
				std::ifstream in(path,mode);
				if(in.is_open()){
					std::stringstream ss;
					ss<<in.rdbuf();
					in.close();
					return ss.str();
				}

				Error error;
				error<<"failed to read file: "<<path;
#if STARLIGHT_DEBUG
				THROW(error.str().c_str());
#endif
			}

			File::File(){}


			File::~File(){}
		}
	}
}