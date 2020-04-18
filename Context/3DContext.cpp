#include "stdafx.h"
#include "3DContext.h"


C3DContext::C3DContext()
{
	//todo: create static object here, testing purpose only

	debugObject = new CStaticObject();

	StaticVertex *vt = (StaticVertex*)calloc(36, sizeof(StaticVertex));

	StaticVertex vt1;
	vt1.position.x = 1.0;
	vt1.position.y = -1.0;
	vt1.position.z = -1.0;
	vt1.uv0.x = 0.0;
	vt1.uv0.y = 0.0;

	StaticVertex vt2;
	vt2.position.x = 1.0;
	vt2.position.y = -1.0;
	vt2.position.z = 1.0;
	vt2.uv0.x = 0.0;
	vt2.uv0.y = 1.0;

	StaticVertex vt3;
	vt3.position.x = 1.0;
	vt3.position.y = 1.0;
	vt3.position.z = 1.0;
	vt3.uv0.x = 0.0;
	vt3.uv0.y = 1.0;

	StaticVertex vt4;
	vt4.position.x = 1.0;
	vt4.position.y = 1.0;
	vt4.position.z = -1.0;
	vt4.uv0.x = 0.0;
	vt4.uv0.y = 0.0;

	StaticVertex vt5;
	vt5.position.x = -1.0;
	vt5.position.y = -1.0;
	vt5.position.z = 1.0;
	vt5.uv0.x = 0.0;
	vt5.uv0.y = 0.0;

	StaticVertex vt6;
	vt6.position.x = -1.0;
	vt6.position.y = 1.0;
	vt6.position.z = 1.0;
	vt6.uv0.x = 1.0;
	vt6.uv0.y = 1.0;

	StaticVertex vt7;
	vt7.position.x = -1.0;
	vt7.position.y = 1.0;
	vt7.position.z = -1.0;
	vt7.uv0.x = 0.0;
	vt7.uv0.y = 1.0;

	StaticVertex vt8;
	vt8.position.x = -1.0;
	vt8.position.y = -1.0;
	vt8.position.z = -1.0;
	vt8.uv0.x = 0.0;
	vt8.uv0.y = 1.0;

	//front face
	vt[0] = vt1;
	vt[1] = vt2;
	vt[2] = vt3;

	vt[3] = vt1;
	vt[4] = vt3;
	vt[5] = vt4;

	//Top Face
	vt[6] = vt2;
	vt[7] = vt5;
	vt[8] = vt6;

	vt[9] = vt2;
	vt[10] = vt6;
	vt[11] = vt3;

	//right face
	vt[12] = vt7;
	vt[13] = vt6;
	vt[14] = vt3;

	vt[33] = vt7;
	vt[34] = vt4;
	vt[35] = vt3;

	vt[15] = vt1;
	vt[16] = vt8;
	vt[17] = vt7;

	vt[18] = vt7;
	vt[19] = vt1;
	vt[20] = vt4;

	vt[21] = vt7;
	vt[22] = vt6;
	vt[23] = vt8;

	vt[24] = vt5;
	vt[25] = vt6;
	vt[26] = vt8;

	vt[27] = vt5;
	vt[28] = vt1;
	vt[29] = vt8;

	vt[30] = vt5;
	vt[31] = vt1;
	vt[32] = vt2;

	//debugObject->Initialize(vt, 36);

	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_FRONT_AND_BACK);

	camera = new CCamera();
}


C3DContext::~C3DContext()
{
}

void C3DContext::RunContextLogic(float delta_t)
{
	/*
	*	We first draw static object. 
	*	In a first time, we set up common shader data.
	*/

	CShader *shaderStaticObject = CShaderManager::getInstance().getShader("CStaticObject_Shader");
	glUseProgram(shaderStaticObject->getShaderProgram());

	/*
	*	View Data from current active camera
	*/
	glUniformMatrix4fv(glGetUniformLocation(shaderStaticObject->getShaderProgram(), "View"),
		1, GL_FALSE,
		glm::value_ptr(camera->getMatriceView())
	);

	glUniformMatrix4fv(glGetUniformLocation(shaderStaticObject->getShaderProgram(), "Projection"),
		1, GL_FALSE,
		glm::value_ptr(COption::getInstance().getMatriceProjection())
	);

	//debugObject->Draw();
}

void C3DContext::EventProcessing(SDL_Event evt, float delta_t)
{
	if (camera) camera->Proceed_Event(evt, delta_t);
}
