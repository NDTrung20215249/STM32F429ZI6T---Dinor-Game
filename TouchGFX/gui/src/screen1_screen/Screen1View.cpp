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
#ifndef SIMULATOR
void saveHighScoreToFlash(uint32_t highScore)
{
    HAL_FLASH_Unlock();

    // Erase the sector
    FLASH_EraseInitTypeDef eraseInit;
    uint32_t sectorError = 0;

    eraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
    eraseInit.Sector = FLASH_SECTOR_11; // Sector 11
    eraseInit.NbSectors = 1;
    eraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;

    if (HAL_FLASHEx_Erase(&eraseInit, &sectorError) != HAL_OK)
    {
        // Handle error here
        HAL_FLASH_Lock();
        return;
    }

    // Write the data
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_SECTOR_SAVE_ADDRESS, highScore) != HAL_OK)
    {
        // Handle error here
    }

    HAL_FLASH_Lock();
}

uint32_t readHighScoreFromFlash()
{
    uint32_t value = *(uint32_t*)FLASH_SECTOR_SAVE_ADDRESS;

    // Optional: if erased Flash returns 0xFFFFFFFF, treat as 0
    if (value == 0xFFFFFFFF)
        return 0;
    return value;
}
#endif
void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();

    // Position T-Rex on ground
    trexY = groundBox.getY() - trexImage.getHeight();
    trexImage.setY(trexY);

    // Initial obstacle position
    obstacleX = HAL::DISPLAY_WIDTH;
    obstacleY = 146;
    obstacleSpeed = 4 + rand() % 3;

    obstacleImage.setX(obstacleX);
    obstacleImage.setY(obstacleY);

    animationFrameCounter = 0;
    currentTrexFrame = 0;

    backgroundBrightness = 255;
    isNight = false;
    isScoreFlashing = false;
    flashCounter = 0;

    scoreText.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    scoreText.invalidate();
#ifndef SIMULATOR
    highScore = readHighScoreFromFlash();
#endif
    Unicode::snprintf(highScoreTextBuffer, HIGHSCORETEXT_SIZE, "%d", highScore);
    highScoreText.invalidate();
}

#ifndef SIMULATOR
void Screen1View::startBuzzer()
{
    buzzerActive = true;
    buzzerTickCounter = 0;
    buzzerDurationTicks = 10; // Longer buzz duration for death

    buzzerPinState = false;
}

#endif

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}
void Screen1View::onTapAreaPressed()
{
    // No action anymore; jump is triggered via hardware button
}
void Screen1View::handleTickEvent()
{
#ifndef SIMULATOR
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
    {
        if (!isJumping)
        {
            isJumping = true;
            velocity = -15;
            startBuzzer();
        }
    }
#endif

    // --- Jumping ---
    if (isJumping)
    {
        trexImage.invalidate();

        trexY += velocity;
        velocity += gravity;

        if (trexY >= groundBox.getY() - trexImage.getHeight())
        {
            trexY = groundBox.getY() - trexImage.getHeight();
            velocity = 0;
            isJumping = false;
        }

        trexImage.setY(trexY);
        trexImage.invalidate();
    }

    // --- Obstacle movement ---
    obstacleImage.invalidate();

    obstacleX -= obstacleSpeed;

    if (obstacleX + obstacleImage.getWidth() < 0)
    {
        obstacleX = HAL::DISPLAY_WIDTH;
        obstacleSpeed = 4 + rand() % 2;
        score++;

        if (score % 5 == 0)
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
    obstacleImage.invalidate();

    // --- Cloud 1 ---
    cloud1.invalidate();
    cloud1X -= 1;
    if (cloud1X + cloud1.getWidth() < 0)
        cloud1X = HAL::DISPLAY_WIDTH;
    cloud1.setX(cloud1X);
    cloud1.invalidate();

    // --- Cloud 2 ---
    cloud2.invalidate();
    cloud2X -= 1.25;
    if (cloud2X + cloud2.getWidth() < 0)
        cloud2X = HAL::DISPLAY_WIDTH;
    cloud2.setX(cloud2X);
    cloud2.invalidate();

    // --- T-Rex animation ---
    if (isJumping)
    {
        trexImage.setBitmap(Bitmap(BITMAP_TREXFRAME0_ID));
        trexImage.invalidate();
    }
    else
    {
        animationFrameCounter++;
        if (animationFrameCounter >= 5)
        {
            currentTrexFrame = 1 - currentTrexFrame;
            if (currentTrexFrame == 0)
                trexImage.setBitmap(Bitmap(BITMAP_TREXFRAME0_ID));
            else
                trexImage.setBitmap(Bitmap(BITMAP_TREXFRAME1_ID));

            trexImage.invalidate();
            animationFrameCounter = 0;
        }
    }

    // --- Collision ---
    if (sqrt(pow(obstacleX - trexImage.getX(),2) + pow(obstacleY - trexImage.getY(),2)) < 44)
    {
        finalScore = score;
        if (highScore < finalScore)
            highScore = finalScore;
#ifndef SIMULATOR
         saveHighScoreToFlash(highScore);
#endif
        score = 0;
        obstacleX = HAL::DISPLAY_WIDTH;

        Unicode::snprintf(scoreTextBuffer, SCORETEXT_SIZE, "%d", score);
        scoreText.invalidate();

        gameOverTransition();
    }

    // --- Background transition ---
    if (isNight && backgroundBrightness > 50)
        backgroundBrightness -= 3;
    else if (!isNight && backgroundBrightness < 255)
        backgroundBrightness += 3;

    colortype color = touchgfx::Color::getColorFromRGB(
        backgroundBrightness,
        backgroundBrightness,
        backgroundBrightness);
    background.setColor(color);
    background.invalidate();

    // --- Score flashing ---
    if (isScoreFlashing)
    {
        flashCounter++;
        if (flashCounter % 10 < 5)
            scoreText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
        else
            scoreText.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
        scoreText.invalidate();
        if (flashCounter > 30)
        {
            isScoreFlashing = false;
            scoreText.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
            scoreText.invalidate();
        }
    }

#ifndef SIMULATOR
    // --- Buzzer toggle ---
    if (buzzerActive)
    {
        if (buzzerTickCounter < buzzerDurationTicks)
        {
            buzzerPinState = !buzzerPinState;
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,
                buzzerPinState ? GPIO_PIN_SET : GPIO_PIN_RESET);
            buzzerTickCounter++;
        }
        else
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            buzzerActive = false;
        }
    }
#endif
}
