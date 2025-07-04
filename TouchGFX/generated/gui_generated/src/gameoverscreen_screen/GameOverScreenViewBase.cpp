/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/gameoverscreen_screen/GameOverScreenViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <images/BitmapDatabase.hpp>

GameOverScreenViewBase::GameOverScreenViewBase() :
    buttonCallback(this, &GameOverScreenViewBase::buttonCallbackHandler)
{
    __background.setPosition(0, 0, 320, 240);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    background.setPosition(0, 0, 320, 240);
    background.setColor(touchgfx::Color::getColorFromRGB(129, 247, 239));
    add(background);

    GameOver.setXY(45, 56);
    GameOver.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    GameOver.setLinespacing(0);
    GameOver.setTypedText(touchgfx::TypedText(T___SINGLEUSE_5KWO));
    add(GameOver);

    restartButton.setXY(73, 182);
    restartButton.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_PRESSED_ID));
    restartButton.setLabelText(touchgfx::TypedText(T___SINGLEUSE_WVY5));
    restartButton.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    restartButton.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    restartButton.setAction(buttonCallback);
    add(restartButton);

    finalScoreText.setPosition(73, 90, 213, 30);
    finalScoreText.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    finalScoreText.setLinespacing(0);
    Unicode::snprintf(finalScoreTextBuffer, FINALSCORETEXT_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_I1O9).getText());
    finalScoreText.setWildcard(finalScoreTextBuffer);
    finalScoreText.setTypedText(touchgfx::TypedText(T___SINGLEUSE_2IHK));
    add(finalScoreText);

    highScoreText.setPosition(73, 0, 225, 27);
    highScoreText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    highScoreText.setLinespacing(0);
    Unicode::snprintf(highScoreTextBuffer, HIGHSCORETEXT_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_L38S).getText());
    highScoreText.setWildcard(highScoreTextBuffer);
    highScoreText.setTypedText(touchgfx::TypedText(T___SINGLEUSE_066F));
    add(highScoreText);
}

GameOverScreenViewBase::~GameOverScreenViewBase()
{

}

void GameOverScreenViewBase::setupScreen()
{

}

void GameOverScreenViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &restartButton)
    {
        //restartGame
        //When restartButton clicked change screen to Screen1
        //Go to Screen1 with no screen transition
        application().gotoScreen1ScreenNoTransition();
    }
}
