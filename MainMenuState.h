#pragma once

#include "GameState.h"
#include "Button.h"

class MainMenuState : public State
{
private:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	void initVariables();
	void initBackground();
	void initFonts();
	virtual void initKeybinds();
	void initButtons();

public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	void updateButtons();
	virtual void updateInput(const float& dt);
	virtual void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = NULL);
	virtual void render(sf::RenderTarget* target = NULL);
};

