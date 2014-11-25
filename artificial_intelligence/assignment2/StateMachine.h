#pragma once
#include "State.h"

class Game;

template <typename entity_type>
class StateMachine
{
private:
	entity_type *_owner;
	State<entity_type> *_previousState;
	State<entity_type> *_currentState;
	State<entity_type> *_globalState;

public:
	StateMachine(entity_type *owner) : _owner(owner), _previousState(nullptr), _currentState(nullptr), _globalState(nullptr) { };
	virtual ~StateMachine();

	void setCurrentState(State<entity_type> *currentState) { _currentState = currentState; }
	void setPreviousState(State<entity_type> *previousState) { _currentState = previousState; }
	void setGlobalState(State<entity_type> *globalState) { _currentState = globalState; }

	State<entity_type> *currentState() const { return _currentState; }
	State<entity_type> *previousState() const { return _previousState; }
	State<entity_type> *globalState() const { return _globalState; }

	void update(Game &game) const {

		if (_globalState) _globalState->update(_owner, game);

		if (_currentState) _currentState->update(_owner, game);
	}

	void changeState(State<entity_type> *newState) {

		if (newState) {
			_previousState = _currentState;
			_currentState->exit(_owner);
			_currentState = newState;
			_currentState->enter(_owner);
		}
	}

	void revertToPreviousState() {
		changeState(_previousState);
	}
};

