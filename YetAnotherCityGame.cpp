// YetAnotherCityGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "SDL.h"
#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")

#include "GL/glew.h"
#pragma comment(lib,"glew32.lib")

#include <gl/GL.h>
#pragma comment(lib,"opengl32.lib")

//use only once before including stb_image.h in other file
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#pragma comment(lib,"freetype.lib")

#include "./Context/ContextManager.h"
#include "./Context/MainMenu.h"
#include "Option.h"
#include "./GUI/Font/FontManager.h"
#include "./Shaders/ShaderManager.h"

SDL_Window * _MainWindow = nullptr;
SDL_GLContext _glContext;
SDL_Event _SdlEvent;

CMainMenu *_MainMenuContext = nullptr;

unsigned int startFrameTime = 0;
unsigned int endFrameTime = 0;
float delta_t = 0.0;

int main(int argc, char* args[])
{
	//read option from hard drive 
	if (!COption::getInstance().Read_Option())
	{
		//if something goes wrong during option loading, display error message
	}

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << SDL_GetError() << std::endl;
		SDL_Quit();

		return -1;
	}

	_MainWindow = SDL_CreateWindow("YetAnotherCityGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		COption::getInstance().Get_Horizontal_Resolution(),
		COption::getInstance().Get_Vertical_Resolution(),
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	//opengl set-up

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	_glContext = SDL_GL_CreateContext(_MainWindow);

	if (_glContext == 0)
	{
		std::cout << SDL_GetError() << std::endl;
		SDL_DestroyWindow(_MainWindow);
		SDL_Quit();
		return -2;
	}

	/*
	* Load OpenGL 4.2 extension for Windows
	*/
	GLenum initialisationGlew = glewInit();
	if (initialisationGlew != GLEW_OK)
	{
		std::cout << glewGetErrorString(initialisationGlew) << std::endl;
		return -3;
	}

	/*
	*	FontManager initialisation
	*/
	if (!CFontManager::getInstance().Init_FontManager())
	{
		return -4;
	}

	/*
	*	Load and compile shaders
	*/
	if (!CShaderManager::getInstance().InitializeShader())
	{
		return -5;
	}

	//create the main menu
	_MainMenuContext = new CMainMenu();
	_MainMenuContext->CreateContext();
	_MainMenuContext->ActivateContext();

	//glViewport(-1.0, -1.0, COption::getInstance().Get_Horizontal_Resolution(), COption::getInstance().Get_Vertical_Resolution());

	while (CContextManager::Instance().getRunApplication())
	{
		startFrameTime = SDL_GetTicks();

		glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (CContextManager::Instance().GetCurrentActiveContext())
		{
			CContextManager::Instance().GetCurrentActiveContext()->ManageEvent();
			CContextManager::Instance().GetCurrentActiveContext()->RunContext(delta_t);
		}

		SDL_GL_SwapWindow(_MainWindow);

		endFrameTime = SDL_GetTicks();
		delta_t = (float)(endFrameTime - startFrameTime) / 1000.0;
	}

	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_MainWindow);
	SDL_Quit();

    return 0;
}