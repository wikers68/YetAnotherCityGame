// YetAnotherCityGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "SDL.h"

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")

#include "ContextManager.h"

SDL_Window * _MainWindow = nullptr;
SDL_GLContext _glContext;
SDL_Event _SdlEvent;

bool _runApplication = true;


int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << SDL_GetError() << std::endl;
		SDL_Quit();

		return -1;
	}

	_MainWindow = SDL_CreateWindow("YetAnotherCityGame", 0, 0, 1280, 760, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	//opengl set-up

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	_glContext = SDL_GL_CreateContext(_MainWindow);

	if (_glContext == 0)
	{
		std::cout << SDL_GetError() << std::endl;
		SDL_DestroyWindow(_MainWindow);
		SDL_Quit();
	}

	while (_runApplication)
	{
		if (CContextManager::Instance().GetCurrentActiveContext())
		{
			CContextManager::Instance().GetCurrentActiveContext()->RunContext();
		}
	}

	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_MainWindow);
	SDL_Quit();

    return 0;
}