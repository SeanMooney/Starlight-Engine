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

			enum BufferType{ vertex,index };
			template<BufferType T, typename U>
			class Buffer{
			private:
				STARLIGHT_UINT bufferID;
				BufferType type;
				std::vector<U> data;
				GLenum usage;
			private:
				template<typename P>
				class BindGaurd{
				public:
					P* parent;
					BindGaurd(P* parent):parent(parent){parent->bind()}
					~BindGaurd(){parent->unbind()}
				}; friend class BindGuard;
				void init()const abstract;
				void bind() const abstract ;
				void unbind()const abstract ;
			public:
				STARLIGHT_UINT getID(){ return bufferID; }
				std::vector<U>* getData(){ return &data; }
				void flush()const abstract ;
				template<typename P>
				BindGaurd<P>&& getBindGuard() const abstract;
				Buffer(std::vector<U>&& dataset,GLenum usage):type(T),data(std::forward(dataset)),usage(usage){
					glGenBuffers(1,&bufferID);
					bind();
					init();
					unbind();
				}
				~Buffer(){
					glDeleteBuffers(1,&bufferID);
				}
			};

			template <typename U>
			class STARLIGHTAPI VertexBuffer : public Buffer<BufferType::vertex,std::vector<U> >{
				void init()  const override{
					glBufferData(GL_ARRAY_BUFFER,data.size()*sizeof(U),data.data(),usage);
				}
				void bind() const override{
					glBindBuffer(GL_ARRAY_BUFFER,bufferID);
				}
				void unbind() const override{
					glBindBuffer(GL_ARRAY_BUFFER,0);
				}
			public:
				VertexBuffer(std::vector<U>&& dataset,GLenum usage=GL_STATIC_DRAW) : Buffer<BufferType::vertex>(std::forward(dataset),usage){}
				void flush()  const override{
					glBufferSubData(GL_ARRAY_BUFFER,data.size()*sizeof(U),data.data(),usage);
				}
				BindGaurd<VertexBuffer>&& getBindGuard() const override{
					return BindGaurd(this);
				}
			};
			template<typename U>
			class STARLIGHTAPI IndexBuffer : public Buffer<BufferType::index,std::vector<U> >{
				void init() const override{
					glBufferData(GL_ELEMENT_ARRAY_BUFFER,data.size()*sizeof(U),data.data(),usage);
				}
				void bind() const override{
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,bufferID);
				}
				void unbind() const override{
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
				}
			public:
				IndexBuffer(std::vector<U>&& dataset,GLenum usage=GL_STATIC_DRAW) : Buffer<BufferType::index>(std::forward(dataset),usage){}
				void flush() const override{
					glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,data.size()*sizeof(U),data.data(),usage);
				}
				BindGaurd<IndexBuffer>&& getBindGuard() const override{
					return BindGaurd(this);
				}
			};
		}
	}
}