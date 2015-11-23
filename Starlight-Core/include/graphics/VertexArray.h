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
#include <STARLIGHT_CORE\Shared.h>
#include <STARLIGHT_CORE\graphics\Buffer.h>
#include <STARLIGHT_CORE\graphics\GLEW.h>
#include <STARLIGHT_CORE\Maths\vec.h>
#include <STARLIGHT_CORE\graphics\Shader.h>

namespace starlight{
	namespace core{
		namespace graphics{
			using namespace starlight::core::maths;
			template<typename T=Vec3, typename U=RectIndicies>
			class  VertexArray{
				friend class BindGuard;
			private:
				std::shared_ptr<VertexBuffer<T>> vbo;
				std::shared_ptr<IndexBuffer<U>> ibo;
				STARLIGHT_UINT vaoID;
				static std::mutex mutex;  // protects bind and unbind
			private:
			public:
				VertexArray(std::shared_ptr<VertexBuffer<T>> vertexData,std::shared_ptr<IndexBuffer<U>> indexData)
					:vbo(vertexData)
					,ibo(indexData){
					glGenVertexArrays(1,&vaoID);
				}
				~VertexArray(){};

				void bind(){ glBindVertexArray(vaoID); }
				void unbind(){ glBindVertexArray(0); }
				void addVertexAtribPtr(ShaderAttribute&& attrib){
					auto& bg=attrib.getBindGuard();
					glVertexAttribPointer(attrib.location,attrib.count,attrib.type,GL_FALSE,sizeof(T),reinterpret_cast<void*>(attrib.offset));
				}
				BindGaurd<VertexArray>&& getBindGuard() const{
					return BindGaurd<VertexArray>(this, mutex);
				}

				std::shared_ptr<VertexBuffer<T>> getVBO(){ return vbo; };
				std::shared_ptr<IndexBuffer<U>> getIBO(){ return ibo; };

				void setBuffers(std::shared_ptr<VertexBuffer<T>>vb,std::shared_ptr<IndexBuffer<U>>ib){ vbo=vb;ibo=ib; }

			};
			template<typename T,typename U>
			std::mutex VertexArray<T,U>::mutex; // intialies mutex once and only once.
		}
	}
}
