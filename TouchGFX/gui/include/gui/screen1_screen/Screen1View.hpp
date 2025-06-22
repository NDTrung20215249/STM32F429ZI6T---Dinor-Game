#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP
#define SCORE_TEXT_SIZE 20

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/Utils.hpp> // Make sure this is at the top
#include <touchgfx/Unicode.hpp>
#include <math.h>


class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}

    virtual void setupScreen();
    virtual void tearDownScreen();

    // Game logic functions
    virtual void handleTickEvent();                // Game loop tick
    virtual void onTapAreaPressed();       // Triggered by tap button
    static uint16_t finalScore;		// Player final score
    static uint16_t highScore;		// Player highs score

protected:
    // T-Rex physics
    int trexY;             // Current Y position of T-Rex
    int velocity;          // Jump velocity
    int gravity;           // Gravity strength
    bool isJumping;        // True when in jump phase
    Unicode::UnicodeChar scoreTextBuffer[10];
    // Obstacle movement
    int obstacleX;         // X position of obstacle
    int obstacleY;
    // Game state
    uint16_t score;             // Player score

    // Optional: Score buffer for text area (if using wildcard)
    // TCHAR scoreTextBuffer[SCORETEXT_SIZE];
};

#endif // SCREEN1VIEW_HPP
