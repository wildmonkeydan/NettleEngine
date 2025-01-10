#pragma once
#include "game.h"
#include "../System/system.h"

namespace Nettle {
	class Core {
	public:
		static Core& GetCore() { static Core instance; return instance; }
		Core(Core&) = delete;

		void Run(Game* pgame);
	private:
		Core();

		void Init();
		void MainLoop();
		void Destroy();

		Game* game = nullptr;
		System::System* system = nullptr;
		bool isFocused = true;
	};
}