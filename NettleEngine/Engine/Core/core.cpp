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
		system = new HostOS;
		system->Init();
	}
	void Core::MainLoop()
	{

	}
	void Core::Destroy()
	{

	}
}