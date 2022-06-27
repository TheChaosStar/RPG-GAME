#include "MainMenuState.h"

void MainMenuState::initVariables()
{

}
void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window->getSize().x),
			static_cast<float>(window->getSize().y)
		)
	);
	//this->background.setPosition(0, 0);
	
	if (!this->backgroundTexture.loadFromFile("Resources/Images/Background/background.png"))
		throw "[Error::Background] Failed to load Background texture";

	this->background.setTexture(&this->backgroundTexture);
}
void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Titania-Regular.ttf"))
		throw ("[Error::Font] Could not load font");
	
}
void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key_value = "";

		while (ifs >> key >> key_value)
		{
			this->keybinds[key] = this->supportedKeys->at(key_value);
		}
	}

	ifs.close();
}
void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(
		300.f, 480.f, 250.f, 100.f,
		&this->font, "Start Game", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["SETTINGS"] = new Button(
		300.f, 580.f, 250.f, 100.f,
		&this->font, "Settings", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["EDITOR"] = new Button(
		300.f, 680.f, 250.f, 100.f,
		&this->font, "Editor", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["EXIT_STATE"] = new Button(
		300.f, 880.f, 250.f, 100.f,
		&this->font, "Quit", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

	
}
MainMenuState::~MainMenuState() 
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::updateButtons()
{
	for (auto &it : this->buttons)
		it.second->update(this->mousePosView);

	// New Game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	// Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}

}
void MainMenuState::updateInput(const float& dt)
{
}
void MainMenuState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();
}
void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
		it.second->render(target);

}
void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	target->draw(this->background);
	this->renderButtons(target);

	// Debug
/*	sf::Text mouseText;
	mouseText.setPosition(sf::Vector2f(this->mousePosView.x + 15.f, this->mousePosView.y + 15.f));
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << "[X: " << this->mousePosView.x << ", Y: " << this->mousePosView.y << "]";
	mouseText.setString(ss.str());

	target->draw(mouseText);*/

}
