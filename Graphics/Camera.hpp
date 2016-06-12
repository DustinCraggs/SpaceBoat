#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera{
public:
	Camera(int xsize = 600, int ysize = 600, float fovy = (float)(M_PI/4), float near = 0.05f, float far = 25.0f);
	void setWindowSize(int x, int y);

	// Get properties
	glm::vec2 getWindowSize();
	glm::vec3 getTarget();
	glm::vec3 getPosition();
	glm::vec3 getMoveDirection();
	glm::vec3 getUpDirection();
	glm::mat4 getProjection();
	glm::mat4 getView();
	glm::mat4 getCameraMatrix();
	glm::mat4 getOrientationMatrix();

	float getFarClippingPlane();

	// Move camera
	// Looking
	void lookAt(glm::vec3 target, glm::vec3 up);
	void lookAt(glm::vec3 position, glm::vec3 target, glm::vec3 up);
	void fixedLookAt();
	void fixedLookAt(glm::vec3 target, glm::vec3 up);
	void releaseLookAt();

	// Position
	void reposition(glm::vec3 position);
	void retarget(glm::vec3 target);
	void orbit(float radAboutX, float radAboutY);
	void zoom(float amount);
	void rotate(float radians, glm::vec3 axis);
	void rotate(glm::vec3 rotation);
	void rotate(float xrad, float yrad, float zrad);
	void move(glm::vec3 movement);
private:
	int xWindowSize, yWindowSize;
	bool orientationFixed;
	bool eyeChanged;
	bool projectionChanged;
	
	// Eye attributes
	glm::vec3 position;
	glm::vec3 orientation;
	glm::vec3 target;
	glm::vec3 up;
	float fovy, aspect, near, far;
	float xrot, yrot;

	// Camera transformations matrices
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 camera;

	void updateProjectionMatrix();
	void updateCameraMatrix();
};

#endif
