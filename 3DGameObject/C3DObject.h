#pragma once

/*
*	Class with common data either for static and dynamic object
*/
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Shaders/ShaderManager.h"
#include "../Shaders/Shader.h"
#include "../Option.h"
#include "../graphics/Material.h"

class C3DObject
{
public:
	C3DObject();
	~C3DObject();

	/*
	*	To initialize the object, we use a void* type for data.
	*	We that, we can pass any data format for static object, dynamic, sprite...
	*/
	virtual void Initialize(void *data, int numberOfElement) = 0;
	virtual void Draw(float delta_t = 0.0f) = 0;

	CShader *_Shader;	//shader used to draw the BaseRect

	GLuint _vertexArray;

	CMaterial *ObjectMaterial;
};

