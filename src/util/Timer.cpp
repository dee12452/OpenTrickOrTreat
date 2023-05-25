#include "Util.h"

Timer::Timer() : Timer(0) {}

Timer::Timer(Uint64 targetMs) : m_target(targetMs) {
        m_start = SDL_GetTicks64();
        m_end = SDL_GetTicks64();
}

void Timer::reset() {
    m_start = SDL_GetTicks64();
    m_end = SDL_GetTicks64();
}

bool Timer::check() {
    return getElapsedMillis() >= m_target;
}

void Timer::setTargetMs(Uint64 targetMs) {
    m_target = targetMs;
}

Uint64 Timer::getElapsedMillis() {
    m_end = SDL_GetTicks64();
    if(m_end < m_start)
    {
        reset();
    }
    return m_end - m_start;
}
