#ifndef __GameScene_h__
#define __GameScene_h__

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <Scene.h>
#include <Page.h>
#include <Room.h>

class GameScene : public Scene{
	protected:
	SDL_Texture * cover_;
	SDL_Texture * pages_;
	SDL_Texture * plrtex_;
	Page * page_;
	public:
	void Init(SDL_Renderer * renderer);
	void Update(float seconds);
	void Render(SDL_Renderer * renderer);
	void OnEvent( SDL_Event & ev);
	
	void Load(SDL_Renderer * renderer, SDL_Texture * tex);
	void LoadPlayer(SDL_Renderer * renderer, SDL_Texture * tex, int x, int y);
	void LoadText(SDL_Renderer * renderer, SDL_Texture * tex);
	void NewText(SDL_Renderer * renderer);
	
	SDL_Texture * renderText(TTF_Font * font, const std::string & msg, SDL_Renderer * renderer);
};

#endif