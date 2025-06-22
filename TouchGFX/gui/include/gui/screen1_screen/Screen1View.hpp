#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
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
    static int finalScore;	//final score value
    static int highScore;	//high score value
protected:
    // T-Rex physics
    int trexY;             // Current Y position of T-Rex
    int velocity;          // Jump velocity
    int gravity;           // Gravity strength
    bool isJumping;        // True when in jump phase

    // Obstacle movement
    int obstacleX;         // X position of obstacle
    int obstacleY;         // Y position of obstacle

    int cloud1X;
    float cloud2X;
    // Game state
    int score;             // Player score


    // Optional: Score buffer for text area (if using wildcard)
    // TCHAR scoreTextBuffer[SCORETEXT_SIZE];
};

#endif // SCREEN1VIEW_HPP
