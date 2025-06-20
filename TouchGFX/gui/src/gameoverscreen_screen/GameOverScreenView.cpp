#include <gui/gameoverscreen_screen/GameOverScreenView.hpp>

GameOverScreenView::GameOverScreenView() :
	finalScore(0)
{

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
}

void GameOverScreenView::tearDownScreen()
{
    GameOverScreenViewBase::tearDownScreen();
}
