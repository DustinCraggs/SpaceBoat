#include "Graphics.hpp"

#include "Resources.hpp"

#include <iostream>
#include <GL/glew.h>

Graphics::Graphics(Resources resources){
	this->resources = resources;
	glewExperimental = true;
	if( glewInit() != GLEW_OK ){
		fprintf(stderr, "GLEW initialisation failed\n");
		exit(1);
	}
}

void Graphics::loadGraphicsData(std::string directory){
	// Get names of contents of directory

	for( int i=0; i<files.size(); i++ ){
		resources->addModel(Model(directory+files[i]));
	}
}

void Graphics::openWindow(){

}