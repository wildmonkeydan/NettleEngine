#pragma once

//======================================
//
// NETTLE ENGINE - game.h
// 
// Game interface for end-user
// 
// This code is under the MIT license
// Daniel Turner - 2025
//
//======================================

namespace Nettle {
	class Game {
	public:
		virtual bool Start() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void End() = 0;
	};
}