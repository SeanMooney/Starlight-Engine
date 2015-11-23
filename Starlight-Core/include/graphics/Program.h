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
#include "STARLIGHT_CORE\graphics\Shader.h"
#include "STARLIGHT_CORE\utils\Log.h"
namespace starlight{
	namespace core{
		namespace graphics{
			class STARLIGHTAPI Program{
			private:
				VertexShader vertexShader;
				FragmentShader fragmentShader;
				STARLIGHT_UINT programID;
				template <typename T>
				void setUniform(const STARLIGHT_CHAR* name,const T& value)const;
			public:
				Program(const std::string& vShaderPath,const std::string& fShaderPath);
				~Program();
				void compile();
				std::stringstream Program::getLinkerError();
				std::stringstream Program::getValidationError();
				void enable();
				void disable();
				STARLIGHT_INT getUniformLocation(const STARLIGHT_CHAR* name)const;
				

				template <>
				void setUniform(const STARLIGHT_CHAR* name,const STARLIGHT_FLOAT& value)const{
					glUniform1f(getUniformLocation(name),value);
				}

				template <>
				void setUniform(const STARLIGHT_CHAR* name,const STARLIGHT_INT& value)const{
					glUniform1i(getUniformLocation(name),value);
				}

				template <>
				void setUniform(const STARLIGHT_CHAR* name,const Vec2& vector)const{
					glUniform2f(getUniformLocation(name),vector.data.x,vector.data.y);
				}

				template <>
				void setUniform(const STARLIGHT_CHAR* name,const Vec3& vector)const{
					glUniform3f(getUniformLocation(name),vector.data.x,vector.data.y,vector.data.z);
				}

				template <>
				void setUniform(const STARLIGHT_CHAR* name,const Vec4& vector)const{
					glUniform4f(getUniformLocation(name),vector.data.x,vector.data.y,vector.data.z,vector.data.w);
				}

				template <>
				void setUniform(const STARLIGHT_CHAR* name,const Matrix4& matrix)const{
					glUniformMatrix4fv(getUniformLocation(name),1,GL_FALSE,matrix.data_array);
				}
				
			};
		}
	}
}

