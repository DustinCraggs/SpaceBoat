#include "Graphics.hpp"
#include <unistd.h>

int main(){
	std::cout << "Start" << std::endl;
	Graphics graphics;
	while( !graphics.shouldClose() ){
		graphics.nextFrame();
	}
}