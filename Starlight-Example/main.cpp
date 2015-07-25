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
#include <iostream>
#include "include\Game.h"
#include "STARLIGHT_CORE\Maths\vec.h"
#include "STARLIGHT_CORE\Maths\Matrix.h"


using namespace starlight::example;
using namespace starlight::core::maths;
using namespace std;

void main(int argc,char* args[]){

	Game game(args[0]);
	game.run();

	
	
}