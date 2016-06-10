#include "Model.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "../Libs/stb_image.h"

#include "../Libs/tiny_obj_loader.h"

#define VALS_PER_VERT 3
#define VALS_PER_NORM 3
#define VALS_PER_TEXEL 2

Model::Model(){

}

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

void Model::render(glm::mat4 projection, glm::mat4 model, glm::mat4 view){
	// Render each shape
	for( int i=0; i<shapes.size(); i++ ){
		renderShape(i, projection, model, view);
	}
}

void Model::renderShape(unsigned int i, glm::mat4 projection, glm::mat4 model, glm::mat4 view){
	unsigned int PID = shaders[i];
	glUseProgram(PID);

	glm::mat4 modelview = model * view;
	// Load transformation matrices
	GLint viewHandle = glGetUniformLocation(PID, "view_matrix");
	glUniformMatrix4fv(viewHandle, 1, GL_FALSE, glm::value_ptr(view));

	GLint modelViewHandle = glGetUniformLocation(PID, "modelview_matrix");
	glUniformMatrix4fv(modelViewHandle, 1, GL_FALSE, glm::value_ptr(modelview));

	GLint normalHandle = glGetUniformLocation(PID, "normal_matrix");
	glm::mat3 normal(modelview);
	glUniformMatrix3fv(normalHandle, 1, GL_FALSE, glm::value_ptr(normal));

	GLint projectionHandle = glGetUniformLocation(PID, "projection_matrix");
	glUniformMatrix4fv(projectionHandle, 1, GL_FALSE, glm::value_ptr(projection));

	unsigned int matID = shapes[i].mesh.material_ids[0];

	// Load lighting material properties
	GLint ambientHandle = glGetUniformLocation(PID, "ambient");
	GLint diffHandle = glGetUniformLocation(PID, "diffuse");
	GLint specHandle = glGetUniformLocation(PID, "specular");
	GLint shininessHandle = glGetUniformLocation(PID, "shininess");
	glUniform3fv(ambientHandle, 1, materials[matID].ambient);
	glUniform3fv(diffHandle, 1, materials[matID].diffuse);
	glUniform3fv(specHandle, 1, materials[matID].specular);
	glUniform1fv(shininessHandle, 1, &materials[matID].shininess);

	// Load textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[i]);
	GLint diffmapHandle = glGetUniformLocation(PID, "diffmap");
	glUniform1i(diffmapHandle, matID);

	glBindVertexArray(vaos[i]);
	glDrawElements(GL_TRIANGLES, shapes[i].mesh.indices.size() * sizeof(unsigned int), GL_UNSIGNED_INT, (void*)0);

	glBindVertexArray(0);
}











