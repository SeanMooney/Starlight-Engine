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
namespace starlight{
	namespace core{
		namespace graphics{
			class STARLIGHTAPI ShaderAttribute{
			private:
				static std::mutex mutex;  // protects bind and unbind
			public:
				STARLIGHT_UINT location,offset,count;
				GLenum type;
			private:
			public:
				ShaderAttribute(ShaderAttribute&&)=default;
				ShaderAttribute(STARLIGHT_UINT location,STARLIGHT_UINT offset,STARLIGHT_UINT count,GLenum type);
				void bind()const;
				void unbind()const;
			};
		}
	}
}