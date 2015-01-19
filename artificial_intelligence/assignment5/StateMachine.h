#pragma once
#include "State.h"

class Game;
struct Telegram;

template <typename entity_type>
class StateMachine
{
private:
	entity_type *_owner;
	Game *_game;
	State<entity_type> *_previousState;
	State<entity_type> *_currentState;
	State<entity_type> *_globalState;

public:
	StateMachine(entity_type *owner, Game &game) : _owner(owner), _previousState(nullptr), _currentState(nullptr), _globalState(nullptr), _game(&game) { };
	virtual ~StateMachine() { }

	void setCurrentState(State<entity_type> *currentState) { _currentState = currentState; }
	void setPreviousState(State<entity_type> *previousState) { _currentState = previousState; }
	void setGlobalState(State<entity_type> *globalState) { _globalState = globalState; }

	State<entity_type> *currentState() const { return _currentState; }
	State<entity_type> *previousState() const { return _previousState; }
	State<entity_type> *globalState() const { return _globalState; }

	void update() const {

		if (_globalState) _globalState->update(_owner, *_game);

		if (_currentState) _currentState->update(_owner, *_game);
	}

	void changeState(State<entity_type> *newState) {

		if (newState) {
			_previousState = _currentState;
			if (_previousState)	_previousState->exit(_owner, *_game);
			_currentState = newState;
			_currentState->enter(_owner, *_game);
		}
	}

	bool handleMessage(const Telegram &msg) const
	{
		if (_currentState && _currentState->onMessage(_owner, msg, *_game))
			return true;

		if (_globalState && _globalState->onMessage(_owner, msg, *_game))
			return true;

		return false;
	}

	void revertToPreviousState() {
		changeState(_previousState);
	}
};

