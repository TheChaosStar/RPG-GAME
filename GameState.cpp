#include "GameState.h"

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

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
void GameState::initTextures()
{
	if (!this->textures["PLAYER_IDLE"].loadFromFile("Resources/Images/Sprites/Player/idle.png"))
		throw "[Error::Player] Could not load player texture";
}
void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_IDLE"], sf::Vector2f(5.f, 5.f));
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	std::cout << "Hello from GameState" << std::endl;

	this->initKeybinds();
	this->initTextures();
	this->initPlayers();
}
GameState::~GameState()
{
	delete this->player;
}

void GameState::updateInput(const float& dt)
{
	// Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1, 0, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1, 0, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0, -1, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0, 1, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();

}
void GameState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->player->update(dt);
}
void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	
	this->player->render(target);
	
}