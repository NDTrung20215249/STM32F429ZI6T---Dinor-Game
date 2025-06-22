#include <gui/gameoverscreen_screen/GameOverScreenView.hpp>

GameOverScreenView::GameOverScreenView():
	finalScore(0)
{

}

void GameOverScreenView::setupScreen()
{
    GameOverScreenViewBase::setupScreen();
    finalScore = Screen1View::finalScore;
    highScore = Screen1View::highScore;


    Unicode::snprintf(finalScoreTextBuffer, FINAL_SCORE_TEXT_SIZE, "%d", finalScore);
    finalScoreText.setWildcard(finalScoreTextBuffer);
    finalScoreText.invalidate();

    Unicode::snprintf(highScoreTextBuffer, FINAL_SCORE_TEXT_SIZE, "%d", highScore);
    highestScoreText.setWildcard(highScoreTextBuffer);
    highestScoreText.invalidate();
}

void GameOverScreenView::tearDownScreen()
{
    GameOverScreenViewBase::tearDownScreen();
}
