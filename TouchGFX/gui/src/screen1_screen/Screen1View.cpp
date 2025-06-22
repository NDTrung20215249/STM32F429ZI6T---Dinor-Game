#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/Unicode.hpp>


uint16_t Screen1View::finalScore = 0;
uint16_t Screen1View::highScore = 0;

Screen1View::Screen1View() :
	//finalScore(0),
    trexY(0),
    velocity(0),
    gravity(1.5f),
    isJumping(false),
    obstacleX(0),
	obstacleY(0),
    score(0)
{
    // Initialization will be done in setupScreen
	//finalScore = 0;
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();

    // Position T-Rex on top of ground
    trexY = groundBox.getY() - trexImage.getHeight();
    trexImage.setY(static_cast<int>(trexY));

    // Set initial obstacle position off the right edge
    obstacleX = HAL::DISPLAY_WIDTH;
    obstacleY = 144;
    obstacleImage.setX(obstacleX);

    // Initialize score text with label
    Unicode::snprintf(scoreTextBuffer, SCORE_TEXT_SIZE, "%d", score);
    scoreText.setWildcard(scoreTextBuffer);
    scoreText.invalidate();

    //finalScore = 0;
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::onTapAreaPressed()
{
    if (!isJumping)
    {
        isJumping = true;
        velocity = -15.0f;
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

        trexImage.setY(static_cast<int>(trexY));
        trexImage.invalidate(); // Redraw at new position
    }

    // --- Obstacle movement ---
    obstacleImage.invalidate(); // Clear old obstacle

    obstacleX -= 4;
    if (obstacleX + obstacleImage.getWidth() < 0)
    {
        obstacleX = HAL::DISPLAY_WIDTH;
        score++;

        // Update score text
        Unicode::snprintf(scoreTextBuffer, SCORE_TEXT_SIZE, "%d",(int) score);
        scoreText.setWildcard(scoreTextBuffer);
        scoreText.invalidate();


    }

    obstacleImage.setX(obstacleX);
    obstacleImage.setY(obstacleY);
    obstacleImage.invalidate(); // Redraw at new position

    // --- Collision detection ---
    if (sqrt(pow(obstacleX - trexImage.getX(),2) + pow(obstacleY - trexImage.getY(),2)) < 45 )
    {
    	finalScore = score;
    	if(finalScore > highScore){
    		highScore = finalScore;
    	}
        // Collision detected: reset
        score = 0;
        obstacleX = HAL::DISPLAY_WIDTH;

        // Update score text
        Unicode::snprintf(scoreTextBuffer, SCORE_TEXT_SIZE, "%d", score);
        scoreText.setWildcard(scoreTextBuffer);
        scoreText.invalidate();
        goToGameOverScreen();
    }
}
