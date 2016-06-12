#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <iostream>
#include <algorithm>
#include <glm/gtx/vector_angle.hpp>

#include "Camera.hpp"

Camera::Camera(int xsize, int ysize, float fovy, float near, float far){
	xWindowSize = xsize;
	yWindowSize = ysize;
	// Flags
	orientationFixed = false;
	eyeChanged = true;
	projectionChanged = true;

	// Default values
	position = glm::vec3(0.0f);
	orientation = glm::vec3(0.0f, 0.0f, 0.0f);
	target = glm::vec3(0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	view = glm::mat4();
	this->fovy = fovy;
	this->aspect = (float)xsize/ysize;
	this->near = near;
	this->far = far;

	xrot = 0;
	yrot = 0;
}

void Camera::setWindowSize(int x, int y){
	aspect = (float)x/y;
	projectionChanged = true;
}

// Get methods

glm::vec2 Camera::getWindowSize(){
	return glm::vec2(xWindowSize, yWindowSize);
}

glm::vec3 Camera::getTarget(){
	return target;
}

glm::vec3 Camera::getPosition(){
	return position;
}

glm::vec3 Camera::getMoveDirection(){
	return glm::normalize(target - position);
}

glm::vec3 Camera::getUpDirection(){
	return glm::normalize(up);
}

glm::mat4 Camera::getProjection(){
	if( projectionChanged ){
		updateProjectionMatrix();
	}
	return projection;
}

glm::mat4 Camera::getView(){
	if( eyeChanged ){
		updateCameraMatrix();
	}
	return view;
}

glm::mat4 Camera::getCameraMatrix(){
	if( projectionChanged ){
		updateProjectionMatrix();
	}
	if( eyeChanged ){
		updateCameraMatrix();
	}
	return camera;
}

glm::mat4 Camera::getOrientationMatrix(){
	if( eyeChanged ){
		updateCameraMatrix();
	}
	glm::mat4 orientationMat(view);
	orientationMat[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	return orientationMat;
}

// Updating matrices

inline void Camera::updateCameraMatrix(){
	// Calculate view:
	if( orientationFixed ){
		view = glm::lookAt(position, target, up);
	}
	else{
		view = glm::translate(glm::mat4(), -position);
		view = glm::rotate(view, -orientation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::rotate(view, -orientation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::rotate(view, -orientation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	camera = projection * view;
	eyeChanged = false;
}

inline void Camera::updateProjectionMatrix(){
	projection = glm::perspective(fovy, aspect, near, far);
	camera = projection * view;
	projectionChanged = false;
}

// Looking at stuff

void Camera::lookAt(glm::vec3 target, glm::vec3 up){
	view = glm::lookAt(position, target, up);
	eyeChanged = false;
	camera = projection * view;
}

void Camera::lookAt(glm::vec3 position, glm::vec3 target, glm::vec3 up){
	view = glm::lookAt(position, target, up);
	eyeChanged = false;
	camera = projection * view;
}

void Camera::fixedLookAt(){
	if( !orientationFixed ){
		view = glm::lookAt(position, target, up);
		orientationFixed = true;
		eyeChanged = true;
	}
}

void Camera::fixedLookAt(glm::vec3 target, glm::vec3 up){
	lookAt(target, up);
	this->target = target;
	this->up = up;
	orientationFixed = true;
}

void Camera::releaseLookAt(){
	eyeChanged = orientationFixed;
	orientationFixed = false;
}

// Changing camera properties

void Camera::move(glm::vec3 movement){
	position += movement;
	target += movement;
	lookAt(target, up);
}

void Camera::reposition(glm::vec3 position){
	this->position = position;
	eyeChanged = true;
}

void Camera::retarget(glm::vec3 target){
	this->target = target;
	eyeChanged = true;
}

void Camera::orbit(float radAboutX, float radAboutY){
	// Make target effective origin
	position -= target;
	xrot += radAboutX;
	yrot += radAboutY;
	// rotate position by xrad, yrad in camera coords
	glm::vec3 viewX = glm::vec3(glm::row(view, 0));
	position = glm::rotate(position, -radAboutX, viewX);
	up = glm::rotate(up, -radAboutX, viewX);
	position = glm::rotate(position, radAboutY, up);

	// Reset position of target
	position += target;
	lookAt(target, up);
}

// Rotates camera around target, and then points camera back at target
void Camera::restrictedOrbit(float radAboutX, float radAboutY){
	// Difference between current rotation and Pi/2
	double diff = M_PI_2 - std::abs(xrot);
	double newXAngle = xrot - radAboutX;
	if( newXAngle >= M_PI_2 ){
		radAboutX = -diff + 0.00001;
		// radAboutX = 0;
	}else if( newXAngle <= 0 ){
		radAboutX = xrot;
		// radAboutX = 0;
	}
	// Get position of target relative to camera
	glm::vec3 tarToCam = position - target;
	// Get x-axis of camera in world coordinates
	glm::vec3 viewX = glm::vec3(glm::row(view, 0));
	// Rotate around target
	tarToCam = glm::rotate(tarToCam, radAboutX, viewX);
	tarToCam = glm::rotate(tarToCam, radAboutY, up);

	xrot -= radAboutX;
	yrot += radAboutY;
	
	// Place camera at new position
	position = tarToCam + target;
	lookAt(target, up);
}

void Camera::resetYOrbit(){
	// glm::vec3 viewX = glm::normalize(glm::vec3(glm::row(view, 0)));
	// double currentAngle = glm::angle(viewX, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::vec3 tarToCam = position - target;
	tarToCam = glm::rotate(tarToCam, -yrot, up);
	yrot = 0;
	position = tarToCam + target;
	lookAt(target, up);
}

void Camera::zoom(float amount){
	glm::vec3 direction = target - position;
	if( glm::length(direction) > amount ){
		position += amount * glm::normalize(direction);
		eyeChanged = true;
	}
}

// Orientation
void Camera::rotate(float radians, glm::vec3 axis){
	axis /= length(axis);
	orientation += radians * axis;
}

void Camera::rotate(glm::vec3 rotation){
	orientation += rotation;
}

void Camera::rotate(float xrad, float yrad, float zrad){
	orientation += glm::vec3(xrad, yrad, zrad);
}

