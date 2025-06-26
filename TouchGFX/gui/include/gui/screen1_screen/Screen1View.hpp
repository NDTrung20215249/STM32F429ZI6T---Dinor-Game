#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/TypedText.hpp>
#include <math.h>

#ifndef SIMULATOR
#include "stm32f4xx_hal.h"  // Your HAL header for GPIOA, HAL_GPIO_WritePin, etc.
#include "main.h"           // If you have GPIO settings or macros there
#endif


#include <images/BitmapDatabase.hpp>
#include <touchgfx/Color.hpp>


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
#ifndef SIMULATOR
    void startBuzzer();
    void startDeathBuzzer();
#endif
protected:
    // T-Rex physics
    int trexY;             // Current Y position of T-Rex
    int velocity;          // Jump velocity
    int gravity;           // Gravity strength
    bool isJumping;        // True when in jump phase

    // Obstacle movement
    int obstacleX;         // X position of obstacle
    int obstacleY;         // Y position of obstacle
    int obstacleSpeed;

    int cloud1X;
    float cloud2X;
    int animationFrameCounter;
    int currentTrexFrame;
    // Game state
    int score;             // Player score
    uint8_t backgroundBrightness; // 255 = full day, 0 = full night
    bool isNight;                 // Toggle for current state
    bool isScoreFlashing;
    int flashCounter;
#ifndef SIMULATOR
    bool buzzerActive;
    int buzzerTickCounter;
    int buzzerDurationTicks;  // <- NEW: total ticks to play buzzer
    bool buzzerPinState;
#endif


    // Optional: Score buffer for text area (if using wildcard)
    // TCHAR scoreTextBuffer[SCORETEXT_SIZE];
};

#endif // SCREEN1VIEW_HPP
