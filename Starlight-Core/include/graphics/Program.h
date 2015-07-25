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
			public:
				Program(const std::string& vShaderPath,const std::string& fShaderPath);
				~Program();
				void compile();
				void enable();
				void disable();
				STARLIGHT_INT getUniformLocation(const STARLIGHT_CHAR* name);
				void setUniform1f(const STARLIGHT_CHAR* name,STARLIGHT_FLOAT value);
				void setUniform1i(const STARLIGHT_CHAR* name,STARLIGHT_INT value);
				void setUniform2f(const STARLIGHT_CHAR* name,const Vec2& vector);
				void setUniform3f(const STARLIGHT_CHAR* name,const Vec3& vector);
				void setUniform4f(const STARLIGHT_CHAR* name,const Vec4& vector);
				void setUniformMat4(const STARLIGHT_CHAR* name,const Matrix4& matrix);

			};
		}
	}
}

