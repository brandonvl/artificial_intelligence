#include "Game.h"
#include "Drawer.h"
#include "Cow.h"
#include "Rabbit.h"
#include <memory>
#include <list>
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "Vehicle.h"
#include <iostream>
#include "RandomGenerator.h"
#include <algorithm>
#include <map>

Game::Game()
{
	_drawer = new Drawer("KMINT - Application 5",800,800);
	//_drawer->load("cow", R"(assets/cow.png)");
	//_drawer->load("rabbit", R"(assets/rabbit.png)");
	//_drawer->load("weapon", R"(assets/weapon.png)");
	//_drawer->load("pill", R"(assets/pill.png)");
	//_drawer->load("gameover", R"(assets/gameover.png)");
	loadInstanceColorImages();

	//_rabbit = new Rabbit(*this);
	//_rabbit->makeMachine(*this);
	//EntityMgr.registerEntity(_rabbit);
	//_cow = new Cow(*this);
	//_cow->makeMachine(*this);
	//EntityMgr.registerEntity(_cow);
	_geneticInstances.push_back(new GameGeneticInstance(*this, GameGeneticInstanceColor::RED, RandomGenerator::random(10, 30), RandomGenerator::random(10, 30), RandomGenerator::random(10, 30), RandomGenerator::random(10, 30)));
	_geneticInstances.push_back(new GameGeneticInstance(*this, GameGeneticInstanceColor::BLUE, RandomGenerator::random(10, 30), RandomGenerator::random(10, 30), RandomGenerator::random(10, 30), RandomGenerator::random(10, 30)));
	_geneticInstances.push_back(new GameGeneticInstance(*this, GameGeneticInstanceColor::YELLOW, RandomGenerator::random(10, 30), RandomGenerator::random(10, 30), RandomGenerator::random(10, 30), RandomGenerator::random(10, 30)));
	_geneticInstances.push_back(new GameGeneticInstance(*this, GameGeneticInstanceColor::GREEN, RandomGenerator::random(10, 30), RandomGenerator::random(10, 30), RandomGenerator::random(10, 30), RandomGenerator::random(10, 30)));

	std::cout << "-------------- First generation ------------ \n";

	for (auto &it : _geneticInstances) {
		showChances(it->getCow());
	}

	std::cout << "-------------- End First generation --------- \n";


	
}

Game::~Game()
{
	delete _drawer;
}

void Game::stop() {
	_running = false;
}

void Game::run()
{
	_running = true;

	Uint32 oldTime;
	Uint32 curTime = SDL_GetTicks();
	double time_elapsed;

	while (_running) {

		oldTime = curTime;
		curTime = SDL_GetTicks();
		time_elapsed = (curTime - oldTime) / 1000.0;

		Dispatch.dispatchDelayedMessages();
		handleEvents();
		update(time_elapsed);
		draw();
	}
}

void Game::startRound() {

	
}

bool Game::isRoundFinished() {
	return (SDL_GetTicks() - _startTimeStamp) / 1000 >= 30;
}

void Game::update(const double &time_elapsed)
{
	if (_rounds < 5)
	{
		if (_rounds != 5 && _startTimeStamp == -1) {
			++_rounds;
			_startTimeStamp = SDL_GetTicks();
		}

		if (isRoundFinished()) {
			// TODO - apply genetic algorithm
			std::cout << "Round finished";
			_startTimeStamp = -1;
			applyGeneticAlgorithm();
		}
		else{
			for (auto &it : _geneticInstances) {
				it->update(*this, time_elapsed);
			}
		}
	}
}

void Game::applyGeneticAlgorithm()
{
	int geneticSize = _geneticInstances.size();
	double totalPoints = 0.0;
	std::vector<int> points;
	for (size_t i = 0; i < geneticSize; ++i) {

		int point = _geneticInstances[i]->getCow().getPoints() - _geneticInstances[i]->getRabbit().getPoints();
		points.push_back(point);
	}

	int minValue = *std::min_element(points.begin(), points.end(), [&](int a, int b) {
		return a < b;
	});

	int maxValue = *std::max_element(points.begin(), points.end(), [&](int a, int b) {
		return a < b;
	});

	double percLow = 100 / _geneticInstances.size();
	double percHigh = 100 - percLow;
	double numerator = maxValue - minValue;

	for (auto &it : points) {
		if (numerator == 0.0)
			it = minValue;
		else
		it = round(percLow + ((it - minValue) / numerator) * percHigh);


		totalPoints += it;
	}

	std::map<int, double> expectedMapping;
	std::vector<GameGeneticInstance*> madeIt;

	for (size_t i = 0; i < points.size(); ++i) {
		double expectedNumber = points[i] / totalPoints * geneticSize;
		expectedMapping.insert({ i, expectedNumber });

		if (expectedNumber >= 1.0)
			madeIt.push_back(_geneticInstances[i]);
	}

	auto bestElement = std::max_element(expectedMapping.begin(), expectedMapping.end(), [&](std::pair<int, double> a, std::pair<int, double> b) {
		return a.second < b.second;
	});

	std::cout << "\n\n\nThe best Genetics were: " + _geneticInstances[bestElement->first]->getColorExtention() + "\n";
	showChances(_geneticInstances[bestElement->first]->getCow());

	while (madeIt.size() < geneticSize) {
		auto maxElement = std::max_element(expectedMapping.begin(), expectedMapping.end(), [&](std::pair<int, double> a, std::pair<int, double> b) {
			return (a.second - static_cast<int>(a.second)) < (b.second - static_cast<int>(b.second)); 
		});

		madeIt.push_back(_geneticInstances[maxElement->first]);

		expectedMapping.erase(maxElement);

	}

	std::vector<GameGeneticInstanceColor> colors;
	colors.push_back(GameGeneticInstanceColor::RED);
	colors.push_back(GameGeneticInstanceColor::BLUE);
	colors.push_back(GameGeneticInstanceColor::YELLOW);
	colors.push_back(GameGeneticInstanceColor::GREEN);

	_geneticInstances.clear();

	std::cout << "---------------------- New generation ----------------- \n";

	for (size_t i = 0; i < madeIt.size(); ++i)
	{
		GameGeneticInstance *child = new GameGeneticInstance(*this, colors[i], madeIt[i]->getCow().getHideChance(), madeIt[i]->getCow().getSeekPillChance(), madeIt[madeIt.size() - (i+1)]->getCow().getSeekWeaponChance(), madeIt[madeIt.size() - (i+1)]->getCow().getFleeChance());
		_geneticInstances.push_back(child);

		showChances(child->getCow());
	}

	std::cout << "------------------------ End new generation -----------\n";
}

void Game::showChances(Cow &cow)
{
	std::cout << "Color: " << cow.getGeneticInstance()->getColorExtention() << "\n";
	std::cout << "HideChance: " << cow.getHideChance() << "\n";
	std::cout << "SeekPillChance: " << cow.getSeekPillChance() << "\n";
	std::cout << "SeekWeaponChance: " << cow.getSeekWeaponChance() << "\n";
	std::cout << "FleeChance: " << cow.getFleeChance() << "\n\n";
}

void Game::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			stop();
	}
}

void Game::draw()
{
	_drawer->prepareForDraw();
	for (auto &it : _geneticInstances) {
		it->draw(*this, 0.0);
	}
	_drawer->render();
}

void Game::respawnRandom(Vehicle *objectToRespawn, int xStart, int xEnd, int yStart, int yEnd){

	int x, y;

	x = RandomGenerator::random(xStart, xEnd);
	y = RandomGenerator::random(yStart, yEnd);

	objectToRespawn->setPosition(Vector2D(x, y));
}

void Game::loadInstanceColorImages() {

	// RED
	_drawer->load("cowRed", R"(assets/cow.png)");
	_drawer->load("rabbitRed", R"(assets/rabbit.png)");
	_drawer->load("weaponRed", R"(assets/weapon.png)");
	_drawer->load("pillRed", R"(assets/pill.png)");

	_drawer->setColorOverLay("cowRed", 255, 0, 0);
	_drawer->setColorOverLay("rabbitRed", 255, 0, 0);
	_drawer->setColorOverLay("weaponRed", 255, 0, 0);
	_drawer->setColorOverLay("pillRed", 255, 0, 0);

	// BLUE
	_drawer->load("cowBlue", R"(assets/cow.png)");
	_drawer->load("rabbitBlue", R"(assets/rabbit.png)");
	_drawer->load("weaponBlue", R"(assets/weapon.png)");
	_drawer->load("pillBlue", R"(assets/pill.png)");

	_drawer->setColorOverLay("cowBlue", 0, 255, 255);
	_drawer->setColorOverLay("rabbitBlue", 0, 255, 255);
	_drawer->setColorOverLay("weaponBlue", 0, 255, 255);
	_drawer->setColorOverLay("pillBlue", 0, 255, 255);

	// GREEN
	_drawer->load("cowGreen", R"(assets/cow.png)");
	_drawer->load("rabbitGreen", R"(assets/rabbit.png)");
	_drawer->load("weaponGreen", R"(assets/weapon.png)");
	_drawer->load("pillGreen", R"(assets/pill.png)");

	_drawer->setColorOverLay("cowGreen", 0, 255, 0);
	_drawer->setColorOverLay("rabbitGreen", 0, 255, 0);
	_drawer->setColorOverLay("weaponGreen", 0, 255, 0);
	_drawer->setColorOverLay("pillGreen", 0, 255, 0);

	// YELLOW
	_drawer->load("cowYellow", R"(assets/cow.png)");
	_drawer->load("rabbitYellow", R"(assets/rabbit.png)");
	_drawer->load("weaponYellow", R"(assets/weapon.png)");
	_drawer->load("pillYellow", R"(assets/pill.png)");

	_drawer->setColorOverLay("cowYellow", 255, 255, 0);
	_drawer->setColorOverLay("rabbitYellow", 255, 255, 0);
	_drawer->setColorOverLay("weaponYellow", 255, 255, 0);
	_drawer->setColorOverLay("pillYellow", 255, 255, 0);
}