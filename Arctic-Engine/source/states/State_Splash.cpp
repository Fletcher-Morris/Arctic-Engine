#include "State_Splash.h"
#include "../core/Game.h"
#include "../core/Obj.h"
#include "../example/State_Example.h"

sf::Clock timer;
sf::Sprite splash;

State_Splash::State_Splash(Game& game) : State(game) {

	game.assets.LoadTexture("ArcticSplash", "assets/textures/ArcticSplash.jpg");
	splash = sf::Sprite(game.assets.GetTexture("ArcticSplash"));
	splash.setScale((float)m_pGame->GetWindow().getSize().x / 1920.0f, (float)m_pGame->GetWindow().getSize().y / 1080.0f);
	splash.setPosition(0, 0);
	timer.restart();
}

void State_Splash::HandleEvent(sf::Event e) {
	switch (e.type)
	{
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::Escape) {
			m_pGame->Shutdown();
		}
	}
}

void State_Splash::HandleInput() {

}

void State_Splash::Update(sf::Time deltaTime) {

	if (timer.getElapsedTime().asSeconds() >= 3) {
		m_pGame->PushState<State_Example>(*m_pGame);
	}
}

void State_Splash::FixedUpdate(sf::Time deltaTime) {

}

void State_Splash::Render(sf::RenderTarget& target) {
	target.draw(splash);
}