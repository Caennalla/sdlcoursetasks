#include <GameScene.h>
#include <SDL_image.h>
#include <Game.h>
#include <Command.h>

using namespace std;

void 
GameScene::Init(SDL_Renderer * renderer){
  //Clears the first image
  SDL_SetRenderDrawColor(renderer, 255,255,255,0);
  this->Render(renderer);
  //Textures for all the other images used
  cover_ = IMG_LoadTexture(renderer, "res/cover.png");
  pages_ = IMG_LoadTexture(renderer, "res/pages.png");
  //Loads the starting screen
  this->Load(renderer, cover_);
  this->Load(renderer, pages_);
  //Texture for the player
  plrtex_ = IMG_LoadTexture(renderer, "res/player0.png");
  //Load the player, for now the player will always start from the middle
  Game::GetInstance()->GetPlayer().Sety(350);
  Game::GetInstance()->GetPlayer().Setx(500);
  this->LoadPlayer(renderer, plrtex_, Game::GetInstance()->GetPlayer().Getx(), Game::GetInstance()->GetPlayer().Gety());
  TTF_Font * font = SDLApp::LoadFont("res/dungeon0.xml");
  //Creates the page 
  page_ = new Page();
  //This should initialize the page with custom width and height.
  //For some reason using half of the window size didn't work as the text was widened to the whole window
  page_->Init(renderer, (size_t)300, (size_t)200);
  *page_ <<(Game::GetInstance()->GetCurrentRoom()->GetEnterMessage());
  page_->Compose(font);
  page_->_justification = Justification::Left;
  page_->RenderContent(renderer);
  this->Render(renderer);
  TTF_CloseFont(font);
 
}

void 
GameScene::Update(float seconds){
	
}

void 
GameScene::Render(SDL_Renderer * renderer){
	this->Load(renderer, cover_);
    this->Load(renderer, pages_);
	this->LoadPlayer(renderer, plrtex_, Game::GetInstance()->GetPlayer().Getx(), Game::GetInstance()->GetPlayer().Gety());
	if(page_ != NULL){
		
		this->LoadText(renderer, page_->_pageTexture);
	}
	
}

void 
GameScene::OnEvent( SDL_Event & ev){
	
				Command *pCmd = CommandUtils::Parse(ev);
				pCmd->Execute(*Game::GetInstance());
				delete pCmd;
	
}

void 
GameScene::Load(SDL_Renderer * renderer, SDL_Texture * tex){

	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(tex, 255);
	SDL_RenderCopy(renderer, tex, NULL, NULL);

}

void 
GameScene::LoadText(SDL_Renderer * renderer, SDL_Texture * tex){
	//This is the destination
	SDL_Rect dest;
	dest.x = 30;
	dest.y = 50;
	dest.w = 1000/2.2;
	dest.h = 700/2;
	SDL_RenderCopy(renderer, tex, NULL, &dest);

}

void
GameScene::NewText(SDL_Renderer * renderer){
	
	TTF_Font * font = SDLApp::LoadFont("res/dungeon0.xml");
	//Deletes the old page
	delete page_;
	//Just in case
	page_ = NULL;
	//The new page
	page_ = new Page();
	page_->Init(renderer, (size_t)300, (size_t)200);
	*page_ <<(Game::GetInstance()->GetCurrentRoom()->GetEnterMessage());
	page_->Compose(font);
	page_->_justification = Justification::Left;
	page_->RenderContent(renderer);
	TTF_CloseFont(font);
}

void
GameScene::LoadPlayer(SDL_Renderer * renderer, SDL_Texture * tex, int x, int y){
	
	//Loads the character
	SDL_Rect src;
	src.x = 16;
	src.y = 2;
	src.w = 16;
	src.h = 16;
	
	//This is the destination
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = src.w*2;
	dest.h = src.h*2;
	
	//Gives renderer info about the texture
	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(tex,255);
	SDL_RenderCopy(renderer, tex, &src, &dest);

}

SDL_Texture * 
GameScene::renderText(TTF_Font * font, const std::string & msg, SDL_Renderer * renderer){

	SDL_Color color = {0,0,0, 125};
	SDL_Surface * surf = TTF_RenderText_Blended(font, msg.c_str(), color);
	if (surf == nullptr){
		throw runtime_error(SDL_GetError());
	}
	
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr){
		throw runtime_error(SDL_GetError());
	}
	
	SDL_FreeSurface(surf);
	
	return texture;
}