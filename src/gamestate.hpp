#ifndef _OPEN_TOT_GAME_STATE_HPP_
#define _OPEN_TOT_GAME_STATE_HPP_

#include "util/util.hpp"

enum State {LAUNCH, LEVEL, STOP};

class GameState
{
public:
    GameState(State initialState);

    State getState() const;
    void setState(State newState);

    const std::string& getResourceFolderPath() const;
    void setResourceFolderPath(const std::string &path);

private:
    State currentState;
    std::string resourceFolderPath;
};

#endif
