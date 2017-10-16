#pragma once

//#include <boost/noncopyable.hpp>
#include <memory>
#include "framework/Observer.hpp"

namespace KM
{

class IState 
{
public:
	IState(const IState&) = delete;
	IState& operator=(IState const&) = delete;
	virtual ~IState() {}

	virtual void OnEnter(void* owner, int previousStateId) = 0;
	virtual void OnExit(void* owner, int nextStateId) = 0;
	virtual void OnSuspend(void* owner, int pushedStateId) = 0;
	virtual void OnResume(void* owner, int poppedStateId) = 0;
};

typedef std::shared_ptr<IState> StatePtr;
typedef std::shared_ptr<const IState> ConstStatePtr;


class GameState : public IState, Observed
{
    public:
	virtual void OnEnter(void* owner, int previousStateId) {};
	virtual void OnExit(void* owner, int nextStateId) {};
	virtual void OnSuspend(void* owner, int pushedStateId) {};
	virtual void OnResume(void* owner, int poppedStateId) {};
};

typedef std::shared_ptr<GameState> GameStatePtr;
typedef std::shared_ptr<const GameState> GameConstStatePtr;


class GameStateManager
{
    private:
        std::vector<IState> states;
        Subject subject;
public:
	GameStateManager() {}
	GameStateManager(const GameStateManager&) = delete;
	GameStateManager& operator=(const GameStateManager&) = delete;
	~GameStateManager() {}

    void AddState(IState& newState) {
        //states.push_back(newState);
//        subject.registerObserver(newState);
    }
};

}