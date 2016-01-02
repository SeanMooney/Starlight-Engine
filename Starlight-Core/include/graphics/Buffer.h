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
#include <array>
#include <mutex>
namespace starlight{
	namespace core{
		namespace graphics{
			typedef std::array<int,4> RectIndicies;
			typedef std::array<int,3> TriIndicies;
			enum BufferType{ vertexBufferType,indexBufferType };
			template<BufferType T, typename U>
			class Buffer{
			protected:
				STARLIGHT_UINT bufferID;
				BufferType type;
				std::shared_ptr<std::vector<U>> data;
				GLenum usage;
			private:
			public:
				STARLIGHT_UINT getID(){ return bufferID; }
				std::shared_ptr<std::vector<U>> getData(){ return data; }
				void flush()const;
				Buffer(std::vector<U>* dataset,GLenum usage)
					:type(T),data(std::shared_ptr<std::vector<U>>(dataset)),usage(usage){
					glGenBuffers(1,&bufferID);
				}
				~Buffer(){
					glDeleteBuffers(1,&bufferID);
				}
			};

			template <typename U>
			class VertexBuffer : public Buffer<BufferType::vertexBufferType,U >{
				typedef Buffer<BufferType::vertexBufferType,U > BASE;
			private:
				static std::mutex mutex;  // protects bind and unbind
			private:
				void init()  const{
					glBufferData(GL_ARRAY_BUFFER,this->BASE::data->size()*sizeof(U),
								 this->BASE::data->data(),this->BASE::usage);
				}
			public:
				VertexBuffer(std::vector<U>* dataset,GLenum usage=GL_STATIC_DRAW) 
					: BASE(dataset,usage){
					bind();
					init();
					unbind();
				}
				void bind() const{
					glBindBuffer(GL_ARRAY_BUFFER,this->BASE::bufferID);
				}
				void unbind() const{
					glBindBuffer(GL_ARRAY_BUFFER,0);
				}
				void flush()  const{
					glBufferSubData(GL_ARRAY_BUFFER,0,
									this->BASE::data->size()*sizeof(U),
									this->BASE::data->data());
				}
			};
			template<typename U>
			std::mutex VertexBuffer<U>::mutex; // intialies mutex once and only once.

			template<typename U>
			class IndexBuffer : public Buffer<BufferType::indexBufferType,U>{
				typedef Buffer<BufferType::indexBufferType,U> BASE;
			private:
				static std::mutex mutex;  // protects bind and unbind
			private:
				void init() const{
					glBufferData(GL_ELEMENT_ARRAY_BUFFER,this->BASE::data->size()*sizeof(U),
								 this->BASE::data->data(),this->BASE::usage);
				}
			public:
				IndexBuffer(std::vector<U>* dataset,GLenum usage=GL_STATIC_DRAW) 
					: BASE(dataset,usage){
					bind();
					init();
					unbind();
				}
				void bind() const{
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->BASE::bufferID);
				}
				void unbind() const{
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
				}
				void flush() const{
					glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0,
									this->BASE::data->size()*sizeof(U),
									this->BASE::data->data());
				}
			};
			template<typename U>
			std::mutex IndexBuffer<U>::mutex; // intialies mutex once and only once.
		}
	}
}