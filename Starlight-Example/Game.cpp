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
#include "include\Game.h"
#include "STARLIGHT_CORE\utils\Log.h"
#include <STARLIGHT_CORE\graphics\VertexArray.h>
#include <STARLIGHT_CORE\graphics\Buffer.h>
#include <iostream>
#include <chrono>



namespace starlight{
	namespace example{
		std::string Game::exeLocation="";
		Game::Game(const std::string& path){
			Game::exeLocation=path+"\\..\\";
			init();
		}

		Game::~Game(){}
		void Game::run(){

			PRINT_GL_ERROR();
			starlight::core::graphics::Program program(exeLocation+"shaders\\VertexShader.glsl",exeLocation+"shaders\\FragmentShader.glsl");
			PRINT_GL_ERROR();

			starlight::core::graphics::VertexArray<Vec3,STARLIGHT_UINT> vao(nullptr,nullptr);
			vao.bind();
			auto vbo=std::make_shared<VertexBuffer<Vec3>>(new std::vector<Vec3>{
				{ 0, 0, 0 },
				{ 0, 3, 0 },
				{ 8, 3, 0 },
				{ 8, 0, 0 }
			});

			vbo->bind();

			auto ibo=std::make_shared<IndexBuffer<STARLIGHT_UINT>>(new std::vector<STARLIGHT_UINT>{
				0,1,2,
				2,3,0
			});
			ibo->bind();
			vao.setBuffers(vbo,ibo);
			vao.addVertexAtribPtr(ShaderAttribute(0,offsetof(Vec3,data_array),3,GL_FLOAT));

			Matrix4 ortho=Matrix4::orthographic(0.0f,16.0f,0.0f,9.0f,-1.0f,1.0f);

			while(!glfwWindowShouldClose(window->get())){
				glfwPollEvents();
				program.enable();
				program.setUniform("pr_matrix",ortho);
				auto translate=Matrix4::translation(Vec3(1,2,0));
				program.setUniform("ml_matrix",translate);
				auto mousePos=inputManager->getMouseLocation();
				auto pos=Vec2((float)(mousePos.data.x * 16.0f/window->width),(float)(9.0f-mousePos.data.y * 9.0f/window->height));
				program.setUniform("light_pos",pos);
				program.setUniform("colour",Vec4(0.2f,0.3f,0.8f,1.0f));
				glClearColor(1.0f,1.0f,1.0f,1.0f);
				glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL);

				glfwSwapBuffers(window->get());

				inputManager->pollEvents();
				inputManager->processEvents();
			}
			ibo->unbind();
			vbo->unbind();
			vao.unbind();
			window.reset();
		}
		void Game::init(){

			using starlight::core::utils::Debug;
			window=std::make_unique<Window>();
			inputManager=std::make_unique<InputManager>();
			inputManager->registerWindowCallback(window.get());
			auto terminate=[window=window->get()](){
				glfwSetWindowShouldClose(window,GL_TRUE);
			};
			auto trigger=std::make_pair(Keycodes::KEY_ESCAPE,false);
			inputManager->registerKeyboardEvent(trigger,terminate);
			auto print=[window=window->get()](){
				static int count=0;
				Debug()<<"this is a test: "<<count++<<std::endl;
			};
			auto printRepeat=[window=window->get()](){
				static int count=0;
				Debug()<<"this is a repeat test: "<<count++<<std::endl;
			};
			trigger=std::make_pair(Keycodes::KEY_SPACE,false);
			inputManager->registerKeyboardEvent(trigger,print);
			trigger=std::make_pair(Keycodes::KEY_SPACE,true);
			inputManager->registerKeyboardEvent(trigger,printRepeat);

			auto printPos=[im=inputManager.get()](){
				auto pos=im->getMouseLocation();
				Debug()<<pos;
				Debug()<<"POS X: "<<pos.data.x<<" POS Y: "<<pos.data.y;
			};

			inputManager->registerMouseEvent(MouseButtons::MOUSE_BUTTON_RIGHT,printPos);
		}

	}
}