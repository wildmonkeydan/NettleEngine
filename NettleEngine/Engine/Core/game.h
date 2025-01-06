#pragma once

namespace Nettle {
	class Game {
	public:
		virtual bool Start() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void End() = 0;
	};
}