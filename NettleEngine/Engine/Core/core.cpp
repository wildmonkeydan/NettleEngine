#include "core.h"
#include "../platforms.h"

namespace Nettle {
	void Core::Run(Game* pgame)
	{
		Init();

		game = pgame;

		game->Start();
		MainLoop();
		game->End();

		Destroy();
	}
	void Core::Init()
	{
		system = new System::HostOS;
		system->Init();
	}
	void Core::MainLoop()
	{
		system->BeginLoop(isFocused);
		game->Update();
		system->EndLoop(isFocused);
	}
	void Core::Destroy()
	{
		system->Destroy();
	}
}