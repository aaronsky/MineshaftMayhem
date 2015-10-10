
#include <vix_game.h>
#include <vix_filemanager.h>
#include <vix_pathmanager.h>
#include <vix_resourcemanager.h>
#include <vix_font.h>
#include <vix_gameobject.h>
#include <vix_scenemanager.h>
#include <vix_modelmanager.h>
#include <vix_luaengine.h>
#include <vix_luascriptmanager.h>
#include <vix_objectmanager.h>

using namespace Vixen;

class EndlessRunner : public Game
{
public:
	EndlessRunner();

	void VOnStartup();
	void VOnShutdown();
	void VOnUpdate();
	void VOnRender();

private:
	IFont*      m_font;
	Transform   fontTransform;
	bool paused;
};

EndlessRunner::EndlessRunner()
	: Game()
{

}

void EndlessRunner::VOnStartup()
{
	ObjectManager::Initialize();
    LuaEngine::Initialize();
	LuaScriptManager::Initialize();
    ModelManager::Initialize();
    SceneManager::Initialize();
    SceneManager::OpenScene(VTEXT("scene1"));

	paused = false;

	m_renderer->VSetClearColor(Vixen::Colors::Black);

	m_font = ResourceManager::OpenFont(VTEXT("Consolas_24.fnt"));

	fontTransform = Transform(20.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	

	m_window->VToggleCursor();
}

void EndlessRunner::VOnUpdate()
{
	if (Input::SingleKeyPress(IKEY::F2))
		m_window->VClose();

	if (Input::SingleKeyPress(IKEY::P))
	{
		m_window->VToggleCursor();
		paused = !paused;
		if (paused)
			SceneManager::PauseScene(VTEXT("scene1"));
		else
			SceneManager::UnpauseScene(VTEXT("scene1"));

	}

	if (!paused)
    {
		SceneManager::UpdateScene();

		
	    m_window->VTrapCursorCenter();
	}
}

void EndlessRunner::VOnRender()
{
    SceneManager::RenderScene();


	//ALL 2D UI IS DRAW AFTER SCENE IS DRAWN
	USStream ss;
	ss << "FPS: " << Time::FPS();
	m_renderer->VRenderText2D(m_font, ss.str(), Vector2(20, 20));
}

void EndlessRunner::VOnShutdown()
{
    ModelManager::DeInitialize();
	ObjectManager::DeInitialize();
    SceneManager::DeInitialize();
    LuaEngine::DeInitialize();
    delete m_font;
}



int main(int argc, char* argv[])
{
	EndlessRunner _game;

	return _game.Run();
}