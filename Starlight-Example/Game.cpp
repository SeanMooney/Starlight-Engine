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
#include <iostream>
#include <chrono>



namespace starlight{
	namespace example{
	    std::string Game::exeLocation="";
		Game::Game(const std::string& path){
			Game::exeLocation=path+"\\..\\";
			init();
		}
//#define intervalCast std::chrono::duration_cast<std::chrono::milliseconds>
		Game::~Game(){}
		void Game::run(){
			//std::chrono::high_resolution_clock inputTimer;
			//auto inputStart=inputTimer.now();
			starlight::core::graphics::Program program(exeLocation+"shaders\\VertexShader.glsl",exeLocation+"shaders\\FragmentShader.glsl");
			GLfloat vertices[]=
			{
				0, 0, 0,
				8, 0, 0,
				0, 3, 0,
				0, 3, 0,
				8, 3, 0,
				8, 0, 0
			};

			GLuint vbo;
			glGenBuffers(1,&vbo);
			glBindBuffer(GL_ARRAY_BUFFER,vbo);
			glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
			glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
			glEnableVertexAttribArray(0);
			Matrix4 ortho=Matrix4::orthographic(0.0f,16.0f,0.0f,9.0f,-1.0f,1.0f);
			
			while(!glfwWindowShouldClose(window->get())){
				glfwPollEvents();
				glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
				program.enable();
				

				program.setUniform("pr_matrix",ortho);
				auto translate =Matrix4::translation(Vec3(1,2,0));
				program.setUniform("ml_matrix",translate);
				auto mousePos=inputManager->getMouseLocation();
				auto pos=Vec2((float)(mousePos.data.x * 16.0f/window->width),(float)(9.0f-mousePos.data.y * 9.0f/window->height));
				program.setUniform("light_pos",pos);
				program.setUniform("colour",Vec4(0.2f,0.3f,0.8f,1.0f));
				glDrawArrays(GL_TRIANGLES,0,6);
				glfwSwapBuffers(window->get());
				
				//if(intervalCast(inputTimer.now()-inputStart).count()>=50){
					inputManager->pollEvents();
					inputManager->processEvents();
					//inputStart=inputTimer.now();
				//}
			}
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
			auto trigger = std::make_pair(Keycodes::KEY_ESCAPE,false);
			inputManager->registerKeyboardEvent(trigger,terminate);
			auto print=[window=window->get()](){
				static int count=0;
				Debug()<<"this is a test: "<<count++<<std::endl;
			};
			auto printRepeat=[window=window->get()](){
				static int count=0;
				Debug()<<"this is a repeat test: "<<std::endl;
			};
			trigger=std::make_pair(Keycodes::KEY_SPACE,false);
			inputManager->registerKeyboardEvent(trigger,print);
			trigger=std::make_pair(Keycodes::KEY_SPACE,true);
			inputManager->registerKeyboardEvent(trigger,printRepeat);

			auto printPos=[im =inputManager.get()](){
				auto pos=im->getMouseLocation();
				Debug()<<pos;
				Debug()<<"POS X: "<<pos.data.x<<" POS Y: "<<pos.data.y;
			};

			inputManager->registerMouseEvent(MouseButtons::MOUSE_BUTTON_RIGHT,printPos);
		}

	}
}