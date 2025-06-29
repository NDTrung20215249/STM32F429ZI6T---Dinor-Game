#include <gui/gameoverscreen_screen/GameOverScreenView.hpp>

GameOverScreenView::GameOverScreenView() :
	finalScore(0),
#ifndef SIMULATOR
    buzzerActive(false),
    buzzerTickCounter(0),
    buzzerDurationTicks(10),
    buzzerPinState(false)
#endif
{

}
void GameOverScreenView::startBuzzer()
{
    buzzerActive = true;
    buzzerTickCounter = 0;
    buzzerDurationTicks = 30; // Longer buzz duration for death

    buzzerPinState = false;
}
void GameOverScreenView::setupScreen()
{
    GameOverScreenViewBase::setupScreen();
    finalScore = Screen1View::finalScore;
    highScore = Screen1View::highScore;

    Unicode::snprintf(finalScoreTextBuffer, FINALSCORETEXT_SIZE, "%d", finalScore);
    finalScoreText.invalidate();

    Unicode::snprintf(highScoreTextBuffer, HIGHSCORETEXT_SIZE, "%d", highScore);
    highScoreText.invalidate();

    startBuzzer();
}


void GameOverScreenView::tearDownScreen()
{
    GameOverScreenViewBase::tearDownScreen();
}

void GameOverScreenView::handleTickEvent(){
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
