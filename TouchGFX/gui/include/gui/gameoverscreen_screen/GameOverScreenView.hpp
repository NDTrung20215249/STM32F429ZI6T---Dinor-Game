#ifndef GAMEOVERSCREENVIEW_HPP
#define GAMEOVERSCREENVIEW_HPP
#define FINAL_SCORE_TEXT_SIZE 20

#include <touchgfx/Utils.hpp> // Make sure this is at the top
#include <touchgfx/Unicode.hpp>
#include <math.h>

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


protected:
    uint16_t finalScore; // Player final score
    uint16_t highScore; // Player high score
    Unicode::UnicodeChar finalScoreTextBuffer[10];
    Unicode::UnicodeChar highScoreTextBuffer[10];

};

#endif // GAMEOVERSCREENVIEW_HPP
