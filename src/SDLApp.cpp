#include <SDLApp.h>
#include <Game.h>
#include <stdexcept>
using namespace std;

SDLApp::SDLApp(){
	//Initializes the SDL components
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
	}	
	//Initializes the SDL_Image
	
	int initFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int retFlags = IMG_Init(initFlags);
	
	if(retFlags != initFlags){
		throw runtime_error(IMG_GetError());
	}
	//The window and renderer pointers are set to NULL for safety
	window_ = NULL;
	renderer_ = NULL;
	//If there is a joystick when the game starts, it will be used
	if(SDL_NumJoysticks() > 0){
		stick_ = SDL_JoystickOpen(0);
	}
	else stick_ = NULL;
	
	//This will make the Joystick commands able to be processed more easily
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_JoystickEventState(SDL_ENABLE);
}

SDLApp::~SDLApp(){
	SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(renderer_);
	SDL_JoystickClose(0);
	stick_ = NULL;
	IMG_Quit();
	SDL_Quit();
}
	
void 
SDLApp::Init(const string & title, int width, int height, Uint32 flags){
	//Creates the window for the splash screen
	window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	
	if (window_ == nullptr){
	cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
	}
	
	//Creates the renderer element for the given window
	renderer_ = SDL_CreateRenderer(window_, -1, 
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer_ == nullptr){
	cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
	}

}
//// Returns the renderer
SDL_Renderer *
SDLApp::GetRenderer(){
	return renderer_;
}

//// Creates a texture and returns it
SDL_Texture *
SDLApp::LoadTexture(const string & path){
	SDL_Texture * texture = IMG_LoadTexture(renderer_, path.c_str());
	if (texture == NULL) throw runtime_error(SDL_GetError());
	
	return texture;
}

//// Loads the texture in to the renderer
void 
SDLApp::Load(SDL_Texture * tex){

	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(tex,255);
	SDL_RenderCopy(renderer_, tex, NULL, NULL);

}

void 
SDLApp::Render(){
	
	SDL_RenderPresent(renderer_);
	SDL_RenderClear(renderer_);
	
}

void
SDLApp::LoadPlayer(SDL_Texture * tex, int x, int y){
	
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
	SDL_RenderCopy(renderer_, tex, &src, &dest);

}

void
SDLApp::HandleInput(){
	SDL_Event ev;
	while (SDL_PollEvent(&ev)){
		switch (ev.type){
		case SDL_QUIT:
			
			break;
		case SDL_KEYDOWN:
			{
				Command *pCmd = CommandUtils::Parse(ev);
				pCmd->Execute(*Game::GetInstance());
				delete pCmd;
			}
			break;
		case SDL_JOYBUTTONDOWN:
			{
				Command *pCmd = CommandUtils::Parse(ev);
				pCmd->Execute(*Game::GetInstance());
				delete pCmd;
			}
			break;
		case SDL_JOYHATMOTION:
			{
				Command *pCmd = CommandUtils::Parse(ev);
				pCmd->Execute(*Game::GetInstance());
				delete pCmd;
			}
			break;

		//These will check the status of joysticks
		case SDL_JOYDEVICEADDED:
			stick_ = SDL_JoystickOpen(0);
			SDL_JoystickEventState(SDL_ENABLE);
			break;
		case SDL_JOYDEVICEREMOVED:
			SDL_JoystickClose(0);
			stick_ = NULL;
			std::cout << "Bye" << endl;
			break;
		}
	}
	
}
