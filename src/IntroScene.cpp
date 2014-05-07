#include <IntroScene.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include <Game.h>

using namespace std;

void 
IntroScene::Init(SDL_Renderer * renderer){
	splash_ = IMG_LoadTexture(renderer, "res/main.bmp");
	if (splash_ == NULL) throw runtime_error(IMG_GetError());
}

void 
IntroScene::Update(float seconds){
	boxRGBA( Game::GetInstance()->GetSDLApp()->GetRenderer(), 0,0, 1000, 700, 0,0,0, (Uint8)255);
}

void 
IntroScene::Render(SDL_Renderer * renderer){
	SDL_SetRenderDrawColor(renderer, 0,0,0,255);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, splash_, NULL, NULL);
}

void 
IntroScene::OnEvent( SDL_Event & ev){
	switch(ev.type){
	case SDL_QUIT:
		Game::GetInstance()->SetProperty("running", false);
		break;
	default:
		break;
	}
}