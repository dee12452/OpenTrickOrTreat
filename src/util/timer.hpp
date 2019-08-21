#ifndef _OPEN_TOT_TIMER_HPP_
#define _OPEN_TOT_TIMER_HPP_

class Timer
{
public:
    Timer();
    Timer(unsigned int targetMs);

    void reset();
    bool check();

    unsigned int getTargetMillis() const;
    void setTargetMillis(unsigned int targetMs);
    
    unsigned int getElapsedMillis();

private:
    unsigned int targetMillis;

    unsigned int startMillis;
    unsigned int endMillis;
};

#endif
