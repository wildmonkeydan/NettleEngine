///
///		Nettle Engine - Daniel Turner 2024
/// 
///		main.cpp
///		Example of how to use the engine with windows
/// 
/// 
///		This engine is under MIT licence
///

#include "nettle.h"

class Test : public Nettle::Game {
    bool Start() override { return true; };
    void Update() override {};
    void Render() override {};
    void End() override {};
};

int main() {
    Test test;

    Nettle::Core::GetCore().Run(&test);

	return 0;
}