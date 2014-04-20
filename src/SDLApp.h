#ifndef __SDLApp_h__
#define __SDLApp_h__

#include <SDL.h>
#include <SDL_image.h>
#include <Command.h>
#include <string>
#include <iostream>


class SDLApp{

protected:
	SDL_Window * window_;
	SDL_Renderer* renderer_;
	SDL_Joystick* stick_;
	
public:
	SDLApp();
	virtual ~SDLApp();
	
	void Init(const std::string & title, int width, int height, Uint32 flags = SDL_WINDOW_SHOWN);
	
	SDL_Renderer * GetRenderer();
	SDL_Texture * LoadTexture(const std::string & path);
	void Load(SDL_Texture * tex);
	void LoadPlayer(SDL_Texture * tex, int x, int y);
	void Render();
	void HandleInput();
	
	

};

#endif