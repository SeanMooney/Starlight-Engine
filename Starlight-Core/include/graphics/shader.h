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
#include "STARLIGHT_CORE\graphics\GLEW.h"
#include "STARLIGHT_CORE\utils\File.h"
#include "STARLIGHT_CORE\utils\Log.h"
#include "STARLIGHT_CORE\Maths\Matrix.h"
namespace starlight{
	namespace core{
		namespace graphics{
			using namespace starlight::core::maths;
			enum STARLIGHTAPI ShaderTypes{
				vertex,fragment
			};

			template<ShaderTypes T>
			class Shader{
			private:
				const std::string shaderPath;
				STARLIGHT_UINT shaderID;
				std::string shaderSrc;
				ShaderTypes type;
			private:
				template<ShaderTypes T>
				STARLIGHT_UINT createShader();
				template<>
				STARLIGHT_UINT createShader<ShaderTypes::vertex>(){
						return glCreateShader(GL_VERTEX_SHADER);
				};
				template<>
				STARLIGHT_UINT createShader<ShaderTypes::fragment>(){
						return glCreateShader(GL_FRAGMENT_SHADER);
				};
				void load(){
					shaderSrc=starlight::core::utils::File::readFile(shaderPath);
					shaderID=createShader<T>();
				}
				void unload(){
					glDeleteShader(shaderID);
				}

				
			public:
				Shader(const std::string& path) :shaderPath(path),type(T),shaderSrc(new char[1024]){ load(); }
				~Shader(){ unload(); }
				

				STARLIGHT_UINT getID(){ return shaderID; }
				void compile(){
					const STARLIGHT_CHAR*src=shaderSrc.c_str();
					glShaderSource(shaderID,1,&src,nullptr);
					glCompileShader(shaderID);
					STARLIGHT_INT status=0;
					glGetShaderiv(shaderID,GL_COMPILE_STATUS,&status);
					if(status==GL_FALSE){
						STARLIGHT_INT lenght;
						glGetShaderiv(shaderID,GL_INFO_LOG_LENGTH,&lenght);
						std::vector<char> error(lenght);
						glGetShaderInfoLog(shaderID,lenght,&lenght,&error[0]);
						starlight::core::utils::Error message;
						message<<"shader compilation failed: "<<__FILE__<<" "<<__LINE__<<std::endl;
						message<<"shader path: "<<shaderPath<<std::endl;
						message<<"shader error: ";
						// append error
						std::copy(error.begin(),error.end(),std::ostream_iterator<char>(message));
					} else{
						starlight::core::utils::Debug()<<"shader: "<<shaderPath<<" compiled sucessfully";
					}
				}

			};
			
			class STARLIGHTAPI VertexShader : public Shader<ShaderTypes::vertex>{
			public:
				VertexShader(const std::string& path):Shader<ShaderTypes::vertex>(path){}
			};
			class STARLIGHTAPI FragmentShader : public Shader<ShaderTypes::fragment>{
			public:
				FragmentShader(const std::string& path) :Shader<ShaderTypes::fragment>(path){}
			};
		}
	}
}