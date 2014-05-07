#ifndef __Scene_h__
#define __Scene_h__

#include <Updateable.h>
#include <SDL.h>
#include <PropertyHolder.h>
#include <string>

class Scene : public Updateable, public PropertyHolder{
	protected:
	std::string name_;
	public:
	void SetName(const std::string & name);
	std::string GetName();
	virtual void Init(SDL_Renderer * renderer);
	virtual void Render(SDL_Renderer * renderer);
	virtual void Update(float second);
	virtual void OnEvent(SDL_Event & ev);
	virtual void NewText(SDL_Renderer * renderer);
};

#endif