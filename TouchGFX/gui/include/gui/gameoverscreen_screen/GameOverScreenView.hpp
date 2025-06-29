#ifndef GAMEOVERSCREENVIEW_HPP
#define GAMEOVERSCREENVIEW_HPP

#include <gui_generated/gameoverscreen_screen/GameOverScreenViewBase.hpp>
#include <gui/gameoverscreen_screen/GameOverScreenPresenter.hpp>
#include <gui/screen1_screen/Screen1View.hpp>

class GameOverScreenView : public GameOverScreenViewBase
{
public:
    GameOverScreenView();
    virtual ~GameOverScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
#ifndef SIMULATOR
    void startBuzzer();
#endif
protected:
    int finalScore;
    int highScore;
#ifndef SIMULATOR
    bool buzzerActive;
    int buzzerTickCounter;
    int buzzerDurationTicks;  // <- NEW: total ticks to play buzzer
    bool buzzerPinState;
#endif
};

#endif // GAMEOVERSCREENVIEW_HPP
