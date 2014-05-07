#ifndef __SDLApp_h__
#define __SDLApp_h__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include <Command.h>
#include <string>
#include <iostream>
#include <map>
#include <sstream>

class Scene;

class SDLApp{

protected:
	SDL_Window * window_;
	SDL_Renderer* renderer_;
	SDL_Joystick* stick_;
	std::map<std::string, Scene *> scenes_;
	Scene* currentScene_;
	Uint32 time_;
	
public:
	SDLApp();
	virtual ~SDLApp();
	
	void Init(const std::string & title, int width, int height, Uint32 flags = SDL_WINDOW_SHOWN);
	
	SDL_Renderer * GetRenderer();
	SDL_Texture * LoadTexture(const std::string & path);
	void Load(SDL_Texture * tex);
	void LoadPlayer(SDL_Texture * tex, int x, int y);
	void Render();
	void Update();
	void HandleInput();
	
	void AddScene(Scene * scene);
	void DeleteScene(const std::string & name);
	void SetCurrentScene(const std::string & name);
	static TTF_Font* LoadFont(const std::string & filename);
	Scene * GetCurrentScene();
	SDL_Window * GetWindow();
	
	

};

#endif