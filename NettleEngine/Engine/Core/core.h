#pragma once
#include "game.h"
#include "../types.h"
#include "../System/system.h"

//======================================
//
// NETTLE ENGINE - core.h
// 
// Main singelton for the engine
// 
// This code is under the MIT license
// Daniel Turner - 2025
//
//======================================

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