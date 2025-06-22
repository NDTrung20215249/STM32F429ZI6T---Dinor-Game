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
    score(0)
{
    // Initialization will be done in setupScreen
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
    obstacleImage.setX(obstacleX);
    obstacleImage.setY(obstacleY);


    // Optional: Score text
    // Unicode::snprintf(scoreTextBuffer, SCORETEXT_SIZE, "%d", score);
    // scoreText.invalidate();
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
        velocity = -15;
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

    obstacleX -= 4;
    if (obstacleX + obstacleImage.getWidth() < 0)
    {
        obstacleX = HAL::DISPLAY_WIDTH;
        score++;

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
}
