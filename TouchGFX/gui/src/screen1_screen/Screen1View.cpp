#include <gui/screen1_screen/Screen1View.hpp>

int Screen1View::finalScore = 0;
int Screen1View::highScore = 0;

Screen1View::Screen1View() :
    trexY(0),
    velocity(0),
    gravity(1.5f),
    isJumping(false),
    obstacleX(0),
    obstacleY(0),
    obstacleSpeed(0),
    animationFrameCounter(0),
    currentTrexFrame(0),
    score(0),
    isScoreFlashing(false),
    flashCounter(0)
#ifndef SIMULATOR
    , buzzerActive(false),
    buzzerTickCounter(0),
    buzzerDurationTicks(10),
    buzzerPinState(false)
#endif
{
    // Constructor body
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();

    // Position T-Rex on top of ground
    trexY = groundBox.getY() - trexImage.getHeight();
    trexImage.setY(trexY);
    // Set initial obstacle position off the right edge
    obstacleX = HAL::DISPLAY_WIDTH;
    obstacleY = 146;
    obstacleSpeed = 4 + rand() % 3;
    obstacleImage.setX(obstacleX);
    obstacleImage.setY(obstacleY);
    animationFrameCounter = 0;
    currentTrexFrame = 0;
    backgroundBrightness = 255; // Start as full day
    isNight = false;
    isScoreFlashing = false;
    flashCounter = 0;
    scoreText.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0)); // Black Text
    scoreText.invalidate();


    // Optional: Score text
    // Unicode::snprintf(scoreTextBuffer, SCORETEXT_SIZE, "%d", score);
    // scoreText.invalidate();
}
#ifndef SIMULATOR
void Screen1View::startBuzzer()
{
    buzzerActive = true;
    buzzerTickCounter = 0;
    buzzerPinState = false;
}
#endif
void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::onTapAreaPressed()
{
    if (!isJumping)
    {
        isJumping = true;
        velocity = -15;
#ifndef SIMULATOR
        startBuzzer();

#endif
    }
}

void Screen1View::handleTickEvent()
{
    // --- Jumping ---
    if (isJumping)
    {
        trexImage.invalidate(); // Clear old image

        trexY += velocity;
        velocity += gravity;

        if (trexY >= groundBox.getY() - trexImage.getHeight())
        {
            trexY = groundBox.getY() - trexImage.getHeight();
            velocity = 0;
            isJumping = false;
        }

        trexImage.setY(trexY);
        trexImage.invalidate(); // Redraw at new position
    }

    // --- Obstacle movement ---
    obstacleImage.invalidate(); // Clear old obstacle

    obstacleX -= obstacleSpeed;

    if (obstacleX + obstacleImage.getWidth() < 0)
    {
        obstacleX = HAL::DISPLAY_WIDTH;
        obstacleSpeed = 4 + rand() % 2;
        score++;
        // Every 10 points, toggle day/night
        if (score %5 == 0)
        {
            isNight = !isNight;
            isScoreFlashing = true;
            flashCounter = 0;
        }

        Unicode::snprintf(scoreTextBuffer, SCORETEXT_SIZE, "%d", score);
        scoreText.invalidate();
    }

    obstacleImage.setX(obstacleX);
    obstacleImage.setY(obstacleY);

    obstacleImage.invalidate(); // Redraw at new position
    // --- Cloud movement ---
    cloud1.invalidate(); // Clear old obstacle

        cloud1X -= 1;
        if (cloud1X + cloud1.getWidth() < 0)
        {
            cloud1X = HAL::DISPLAY_WIDTH;

            // Unicode::snprintf(scoreTextBuffer, SCORETEXT_SIZE, "%d", score);
            // scoreText.invalidate();
        }

        cloud1.setX(cloud1X);
        cloud1.invalidate(); // Redraw at new position
 // Cloud 2
        cloud2.invalidate(); // Clear old obstacle

            cloud2X -= 1.25;
            if (cloud2X + cloud2.getWidth() < 0)
            {
                cloud2X = HAL::DISPLAY_WIDTH;

                Unicode::snprintf(scoreTextBuffer, SCORETEXT_SIZE, "%d", score);
                scoreText.invalidate();
            }

            cloud2.setX(cloud2X);
            cloud1.invalidate(); // Redraw at new position

// --- T-Rex manual animation ---
            if (isJumping)
            {
                // Show jump frame while T-Rex is in the air
                trexImage.setBitmap(Bitmap(BITMAP_TREXFRAME0_ID));
                trexImage.invalidate();
            }
            else
            {
                // Animate running when on ground
                animationFrameCounter++;

                if (animationFrameCounter >= 5) // Change every 5 ticks
                {
                    currentTrexFrame = 1 - currentTrexFrame;

                    if (currentTrexFrame == 0)
                    {
                        trexImage.setBitmap(Bitmap(BITMAP_TREXFRAME0_ID));
                    }
                    else
                    {
                        trexImage.setBitmap(Bitmap(BITMAP_TREXFRAME1_ID));
                    }

                    trexImage.invalidate();
                    animationFrameCounter = 0;
                }
            }

    // --- Collision detection ---
    if (sqrt(pow(obstacleX - trexImage.getX(),2)+pow(obstacleY - trexImage.getY(),2))<44)
    {
        // Collision detected: reset
    	finalScore = score;
    	if(highScore < finalScore){
    		highScore = finalScore;
    	}

        score = 0;
        obstacleX = HAL::DISPLAY_WIDTH;


        Unicode::snprintf(scoreTextBuffer, SCORETEXT_SIZE, "%d", score);
        scoreText.invalidate();

        gameOverTransition();
    }
    // Smooth background transition
    if (isNight && backgroundBrightness > 50)
    {
        backgroundBrightness -= 3; // Darken
    }
    else if (!isNight && backgroundBrightness < 255)
    {
        backgroundBrightness += 3; // Brighten
    }

    // Compute RGB color based on brightness
    uint8_t r = backgroundBrightness;
    uint8_t g = backgroundBrightness;
    uint8_t b = backgroundBrightness;

    // Apply background color smoothly
    colortype color = touchgfx::Color::getColorFromRGB(r, g, b);
    background.setColor(color);
    background.invalidate();
    // Flash Color Score
    if (isScoreFlashing)
    {
        flashCounter++;

        // Flash between red and black every 5 ticks
        if (flashCounter % 10 < 5)
        {
            scoreText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0)); // Red
            //scoreText.setTypedText(touchgfx::TypedText(T___SINGLEUSE_UY6F));
        }
        else
        {
            scoreText.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0)); // Black
        }

        scoreText.invalidate();

        // Stop flashing after 30 ticks (~600ms)
        if (flashCounter > 30)
        {
            isScoreFlashing = false;
            scoreText.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0)); // Final black
            scoreText.invalidate();
        }
    }

//Buzzer Time
#ifndef SIMULATOR
    if (buzzerActive)
    {
        if (buzzerTickCounter < buzzerDurationTicks)
        {
            buzzerPinState = !buzzerPinState;
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, buzzerPinState ? GPIO_PIN_SET : GPIO_PIN_RESET);
            buzzerTickCounter++;
        }
        else
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // Turn off
            buzzerActive = false; // Stop buzzer
        }
    }
#endif

}
