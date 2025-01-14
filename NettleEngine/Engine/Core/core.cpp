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
		painter = new Render::HostPainter;
		painter->Init("Nettle Engine");
	}
	void Core::MainLoop()
	{
		while (painter->Begin())
		{
			game->Update();
			painter->End();
			system->EndLoop(isFocused);
			system->BeginLoop(isFocused);
		}
	}
	void Core::Destroy()
	{
		painter->Destroy();
		system->Destroy();
	}
}