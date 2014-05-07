#include <Scene.h>


void
Scene::SetName(const std::string & name){
	name_ = name;
}

std::string 
Scene::GetName(){
	return name_;
}

void 
Scene::Init(SDL_Renderer * renderer){

}

void
Scene::Render(SDL_Renderer * renderer){

}
void 
Scene::Update(float second){

}
void 
Scene::OnEvent(SDL_Event & ev){

}

void 
Scene::NewText(SDL_Renderer * renderer){

}