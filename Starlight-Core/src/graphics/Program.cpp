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

			STARLIGHT_INT Program::getUniformLocation(const STARLIGHT_CHAR* name){
				return glGetUniformLocation(programID,name);
			}

			void Program::setUniform1f(const STARLIGHT_CHAR* name,STARLIGHT_FLOAT value){
				glUniform1f(getUniformLocation(name),value);
			}

			void Program::setUniform1i(const STARLIGHT_CHAR* name,STARLIGHT_INT value){
				glUniform1i(getUniformLocation(name),value);
			}

			void Program::setUniform2f(const STARLIGHT_CHAR* name,const Vec2& vector){
				glUniform2f(getUniformLocation(name),vector.data.x,vector.data.y);
			}

			void Program::setUniform3f(const STARLIGHT_CHAR* name,const Vec3& vector){
				glUniform3f(getUniformLocation(name),vector.data.x,vector.data.y,vector.data.z);
			}

			void Program::setUniform4f(const STARLIGHT_CHAR* name,const Vec4& vector){
				glUniform4f(getUniformLocation(name),vector.data.x,vector.data.y,vector.data.z,vector.data.w);
			}

			void Program::setUniformMat4(const STARLIGHT_CHAR* name,const Matrix4& matrix){
				glUniformMatrix4fv(getUniformLocation(name),1,GL_FALSE,matrix.data_array);
			}
		}
	}
}