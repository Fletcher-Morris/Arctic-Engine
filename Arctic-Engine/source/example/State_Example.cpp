#include "State_Example.h"
#include "../core/Game.h"
#include "../core/Obj.h"

State_Example::State_Example(Game& game) : State(game) {

	if (game.assets.LoadObj("teapot", "assets/models/teapot.obj")) {
		Obj leCube = game.assets.GetObj("teapot");
	}
}

void State_Example::HandleEvent(sf::Event e) {
	switch (e.type)
	{
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::Escape) {
			m_pGame->Shutdown();
		}
	}
}

void State_Example::HandleInput() {

}

void State_Example::Update(sf::Time deltaTime) {

}

void State_Example::FixedUpdate(sf::Time deltaTime) {

}

void State_Example::Render(sf::RenderTarget& target) {

}