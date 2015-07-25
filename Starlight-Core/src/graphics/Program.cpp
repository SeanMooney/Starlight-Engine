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
#include "STARLIGHT_CORE\graphics\Program.h"

namespace starlight{
	namespace core{
		namespace graphics{


			Program::Program(const std::string& vShaderPath,const std::string& fShaderPath)
			:vertexShader(VertexShader(vShaderPath)),
			fragmentShader(FragmentShader(fShaderPath)){
				programID=glCreateProgram();
				compile();
			}


			Program::~Program(){
				glDeleteProgram(programID);
			}

			void Program::compile(){
				vertexShader.compile();
				fragmentShader.compile();
				glAttachShader(programID,vertexShader.getID());
				glAttachShader(programID,fragmentShader.getID());
				glLinkProgram(programID);
				glValidateProgram(programID);
				STARLIGHT_INT status=0;
				glGetShaderiv(programID,GL_VALIDATE_STATUS,&status);
				if(status=GL_FALSE){
					STARLIGHT_INT lenght;
					glGetShaderiv(programID,GL_INFO_LOG_LENGTH,&lenght);
					std::vector<char> error(lenght);
					glGetShaderInfoLog(programID,lenght,&lenght,&error[0]);
					starlight::core::utils::Error message;
					message<<"program validation failed: "<<__FILE__<<" "<<__LINE__<<std::endl;
					message<<"validation error: ";
					// append error
					std::copy(error.begin(),error.end(),std::ostream_iterator<char>(message));
				} else{
					starlight::core::utils::Debug()<<"program validation sucessful";
				}
			
			}

			void Program::enable(){
				glUseProgram(programID);
			}
			void  Program::disable(){
				glUseProgram(0);
			}

			STARLIGHT_INT Program::getUniformLocation(const STARLIGHT_CHAR* name)const{
				return glGetUniformLocation(programID,name);
			}

			
		}
	}
}