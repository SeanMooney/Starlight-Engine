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

			std::stringstream Program::getLinkerError(){
				std::stringstream ss;
				GLint isLinked=0;
				glGetProgramiv(programID,GL_LINK_STATUS,(int *)&isLinked);
				if(isLinked==GL_FALSE){
					GLint maxLength=0;
					glGetProgramiv(programID,GL_INFO_LOG_LENGTH,&maxLength);

					//The maxLength includes the NULL character
					std::vector<GLchar> infoLog(maxLength);
					glGetProgramInfoLog(programID,maxLength,&maxLength,&infoLog[0]);
					std::copy(infoLog.begin(),infoLog.end(),std::ostream_iterator<char>(ss));

				}

				return ss;

			}

			std::stringstream Program::getValidationError(){
				std::stringstream ss;
				GLint valid=0;
				glGetProgramiv(programID,GL_VALIDATE_STATUS,&valid);
				if(valid==GL_FALSE){
					GLint maxLength=0;
					glGetProgramiv(programID,GL_INFO_LOG_LENGTH,&maxLength);

					//The maxLength includes the NULL character
					std::vector<GLchar> infoLog(maxLength);
					glGetProgramInfoLog(programID,maxLength,&maxLength,&infoLog[0]);
					std::copy(infoLog.begin(),infoLog.end(),std::ostream_iterator<char>(ss));

				}

				return ss;

			}


			void Program::compile(){
				vertexShader.compile();
				PRINT_GL_ERROR();
				fragmentShader.compile();
				PRINT_GL_ERROR();
				glAttachShader(programID,vertexShader.getID());
				PRINT_GL_ERROR();
				glAttachShader(programID,fragmentShader.getID());
				PRINT_GL_ERROR();
				glLinkProgram(programID);
				PRINT_GL_ERROR();
				std::stringstream linkError=getLinkerError();
				if(linkError.tellp()>0){
					starlight::core::utils::Error message;
					message<<"program linking failed: "<<__FILE__<<" "<<__LINE__<<std::endl;
					message<<"linker error: " <<linkError.str();
					// append error
				} else{
					starlight::core::utils::Debug()<<"program linking sucessful";
				}
				glValidateProgram(programID);
				PRINT_GL_ERROR();
				std::stringstream validationError=getValidationError();
				if(validationError.tellp()>0){
					starlight::core::utils::Error message;
					message<<"program validation failed: "<<__FILE__<<" "<<__LINE__<<std::endl;
					message<<"validation error: "<<validationError.str();
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