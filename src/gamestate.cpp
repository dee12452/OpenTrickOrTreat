#include "gamestate.hpp"

GameState::GameState(State initialState)
    : currentState(initialState)
{}

State GameState::getState() const
{
    return currentState;
}

void GameState::setState(State newState)
{
    currentState = newState;
}

const std::string& GameState::getResourceFolderPath() const
{
    return resourceFolderPath;
}

void GameState::setResourceFolderPath(const std::string &path)
{
    resourceFolderPath = path;
}
