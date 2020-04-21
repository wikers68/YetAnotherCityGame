#pragma once

#include "GL/glew.h"
#include <gl/GL.h>

#include "../Shaders/Shader.h"

class CFinalRenderPass
{
public:
	CFinalRenderPass();
	~CFinalRenderPass();

	void Draw(float delta_t = 0.0f);

	void Init(GLuint TextureColor,GLuint TextureMaterialID);

private:	
	GLuint _vertexArray;
	GLuint _bufferVertex;
	GLuint _TextureSampler;

	GLuint _textureMaterialID;
	GLuint _textureColor;

	bool HasBeenInit;

	CShader *_shader;

};

