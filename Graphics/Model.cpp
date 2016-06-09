#include "Model.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "tiny_obj_loader.h"

#define VALS_PER_VERT 3
#define VALS_PER_NORM 3
#define VALS_PER_TEXEL 2

Model::Model(std::string path){
	// Extract path to file
	int pos = path.rfind("/");
	if( pos != std::string::npos ){
		objDir = path.substr(0, pos + 1);
	}else{
		objDir = "";
	}

	// Get shapes and materials
	std::string error;
	bool nonfatal = tinyobj::LoadObj(shapes, materials, error, path.c_str(), objDir.c_str());
	if( !error.empty() ){
		std::cerr << error;
	}
	if( !nonfatal ){
		exit(1);
	}
	genVaos();
	genTextures();
}


void Model::genVaos(){
	vaos.resize(shapes.size());
	glGenVertexArrays(shapes.size(), vaos.data());

	for( int i=0; i<shapes.size(); i++ ){
		loadVao(i);
	}
}

void Model::loadVao(unsigned int i){
	// Current mesh
	tinyobj::mesh_t mesh = shapes[i].mesh;

	glBindVertexArray(vaos[i]);

	// Set up buffers for vertices, normals, texcoords, and indices
	unsigned int buffer[4];
	glGenBuffers(4, buffer);

	// Load vertices
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, mesh.positions.size() * sizeof(float), &mesh.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, VALS_PER_VERT, GL_FLOAT, GL_FALSE, 0, 0);

	// Load normals
	if( mesh.normals.size() == 0 ){
		mesh.normals.resize(mesh.positions.size(), 0.0f);
	}
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, mesh.normals.size() * sizeof(float), &mesh.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, VALS_PER_VERT, GL_FLOAT, GL_FALSE, 0, 0);			

	// Load texcoords
	if( mesh.texcoords.size() == 0 ){
		mesh.texcoords.resize(mesh.positions.size(), 0.0f);
	}
	glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
	glBufferData(GL_ARRAY_BUFFER, mesh.texcoords.size() * sizeof(float), &mesh.texcoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, VALS_PER_TEXEL, GL_FLOAT, GL_FALSE, 0, 0);

	// Load indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), &mesh.indices[0], GL_STATIC_DRAW);
}

void Model::genTextures(){
	textures.resize(materials.size());
	glGenTextures(materials.size(), textures.data());

	// Load each texture
	glActiveTexture(GL_TEXTURE0);
	for( int i=0; i<materials.size(); i++ ){
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		std::string texname = materials[i].diffuse_texname;
		if( !texname.empty() ){
			loadTexture(texname);
		}else{
			loadDefaultTexture();
		}
	}
}

void Model::loadTexture(std::string path){
	int x, y, n;
	unsigned char *data = stbi_load(path.c_str(), &x, &y, &n, 3);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
	glGenerateMipmap(GL_TEXTURE_2D);
}


void Model::loadDefaultTexture(){
	unsigned char colour[] = {255, 255, 255};
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, colour);
}



// *** TEST ***
// int main(){
// 	glewExperimental = true;
// 	if( glewInit() != GLEW_OK ){
// 		fprintf(stderr, "GLEW initialisation failed\n");
// 		exit(1);
// 	}
// }











