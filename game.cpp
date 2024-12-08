/*
* Author: Nolan Schirripa, Christine Seng, Erick Martinez, Georgia Rushing, Graham Balas
* Assignment Title:  Group Project (game.cpp)
* Assignment Description: defines game class to run and update game
* Due Date: 12/09/2024
* Date Created: 12/6/2024
* Date Last Modified: 12/07/2024
*/

#include "game.h"
#include "SDL_Plotter.h"
int Game::maxDifficulty = 3;
int Game::minDifficulty = 1;

Game::Game()
{
    ballPoint = {500, 50};
    shooter.setBallLoc(ballPoint);

    //Initialize SDL_Image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cerr << "SDL_image could not initialize! SDL_image Error: "
                  << IMG_GetError() << endl;
    }
}

Game::~Game()
{
    // Existing cleanup
    IMG_Quit();
}

void Game::run()
{
    currentState = START_SCREEN;

    while (!g.getQuit())
    {
        Block endLine;
        point p1 = {0, 100};
        point p2 = {1000, 100};
        fpsTimer.start();
        g.clear();

        switch (currentState)
        {
        case START_SCREEN:
            drawStartScreen();//TODO

            if (g.kbhit())
            {
                int key = g.getKey();
                switch (key)
                {
                case ' ': // Space key to start game
                    currentState = PLAYING;
                    ballPoint = {500, 50};
                    shooter.setBallLoc(ballPoint);
                    break;
                case 27: // ESC key to quit
                    g.setQuit(true);
                    break;
                }
            }
            break;

        case PLAYING:
            g.initSound("assets/soundHit.wav");
            // Existing game loop logic
            shape.drawLevel(startLoc, g);
            shooter.drawBall(ballPoint, BALLSIZE, BLACKCOLOR, g);

            endLine.drawLine(p1, p2, BLACKCOLOR, g);

            if (levelChanged)
            {
                shape.createLevel(startLoc);
                levelChanged = false;
            }

            if (g.mouseClick())
            {
                launchBall();
            }
            else if (isFalling)
            {
                ballFalling();
            }

            if (bottomHit())
            {
                updateLevel();

                // Check if game over condition is met
                if (checkGameOver())//TODO
                {
                    currentState = GAME_OVER;
                }

                isFalling = false;
            }
            g.update(score);
            break;

        case GAME_OVER:
            g.clear();
            drawEndScreen();//TODO

        // Check for restart or quit
            if (g.kbhit())
            {
                int key = g.getKey();
                switch (key)
                {
                case 27: // ESC key to quit
                    g.setQuit(true);
                    break;
                }
            }
            break;
        }

        // Update score on screen
        /*g.update(score);*/

        // FPS control
        g.Sleep(10);
        ++countedFrames;
    }

    g.setQuit(true);
    g.Sleep(500);
}
bool Game::checkGameOver() {
    for (int i = 0; i < shape.getAllActiveShapes().size(); ++i) {
        Block &currentBlock = shape.getAllActiveShapes().at(i);
        if (currentBlock.getLocation().y <= 150 && currentBlock.getLife() != 0) {
            setGameOver(true);
        }
    }
    return getGameOver();
}

void Game::drawStartScreen()
{
    // Clear the renderer first
    SDL_RenderClear(g.getRenderer());

    // Load the start screen image
    SDL_Surface* startScreenSurface = IMG_Load("assets/startScreen.png");
    if (!startScreenSurface) {
        std::cerr << "Unable to load start screen image! SDL_image Error: "
                  << IMG_GetError() << std::endl;
        SDL_RenderPresent(g.getRenderer());
        exit(1);
    }

    // Convert surface to texture
    SDL_Texture* startScreenTexture = SDL_CreateTextureFromSurface(g.getRenderer(), startScreenSurface);
    if (!startScreenTexture) {
        std::cerr << "Unable to create texture from start screen surface! SDL Error: "
                  << SDL_GetError() << std::endl;
        SDL_RenderPresent(g.getRenderer());
        SDL_FreeSurface(startScreenSurface);
        exit(1);
    }

    // Render the entire texture
    SDL_RenderCopy(g.getRenderer(), startScreenTexture, NULL, NULL);

    // Present the renderer
    SDL_RenderPresent(g.getRenderer());

    // Clean up
    SDL_FreeSurface(startScreenSurface);
    SDL_DestroyTexture(startScreenTexture);
}

void Game::drawEndScreen()
{
    // Clear the renderer first
    SDL_RenderClear(g.getRenderer());

    // Load the end screen image
    SDL_Surface* endScreenSurface = IMG_Load("assets/endScreen.png");
    if (!endScreenSurface) {
        std::cerr << "Unable to load end screen image! SDL_image Error: "
                  << IMG_GetError() << std::endl;

        // Fallback to the original circle drawing if image fails to load
        shape.drawCircle(startLoc, 50, {0,255,0}, g);
        SDL_RenderPresent(g.getRenderer());
        return;
    }

    // Convert surface to texture
    SDL_Texture* endScreenTexture = SDL_CreateTextureFromSurface(g.getRenderer(), endScreenSurface);
    if (!endScreenTexture) {
        std::cerr << "Unable to create texture from end screen surface! SDL Error: "
                  << SDL_GetError() << std::endl;

        // Fallback to the original circle drawing if texture creation fails
        shape.drawCircle(startLoc, 50, {0,255,0}, g);
        SDL_RenderPresent(g.getRenderer());
        SDL_FreeSurface(endScreenSurface);
        return;
    }

    // Render the entire texture
    SDL_RenderCopy(g.getRenderer(), endScreenTexture, NULL, NULL);

    // Present the renderer
    SDL_RenderPresent(g.getRenderer());

    // Clean up
    SDL_FreeSurface(endScreenSurface);
    SDL_DestroyTexture(endScreenTexture);
}

bool Game::bottomHit()
{
    return ballPoint.y > 930;
}

void Game::launchBall()
{
    clickPos = g.getMouseClick();
    ballPoint.y = 50;
    ballPoint.x = 500;
    xPos = ballPoint.x;
    yPos = ballPoint.y;
    xDist = clickPos.x - ballPoint.x;
    yDist = clickPos.y - ballPoint.y;

    shooter.setMagnitude(13);
    shooter.setDirection(atan(static_cast<double>(xDist) / yDist));

    isFalling = true;
    firstHit = false;
}

void Game::ballFalling()
{
    // apply gravity
    if (firstHit)
    {
        shooter.apply(GRAVITY);
    }
    // change y and x pos based on magnitude and direction
    yPos += shooter.getMagnitude() * cos(shooter.getDirection());
    ballPoint.y = static_cast<int>(yPos);
    if (ballPoint.y < BALLSIZE + 3)
    {
        ballPoint.y = BALLSIZE + 3;
    }

    xPos += shooter.getMagnitude() * sin(shooter.getDirection());
    ballPoint.x = static_cast<int>(xPos);
    if (ballPoint.x < BALLSIZE + 3)
    {
        ballPoint.x = BALLSIZE + 3;
    }
    else if (ballPoint.x > g.getCol() - BALLSIZE - 3)
    {
        ballPoint.x = g.getCol() - BALLSIZE - 3;
    }

    // update flag positions
    ballFlags.update(ballPoint.x, ballPoint.y, BALLSIZE, shooter.getForce());

    // if hit left or right wall
    if (ballPoint.x < 15 || ballPoint.x > 985)
    {
        shooter.setDirection(2 * M_PI - shooter.getDirection());
    }
    for (int i = 0; i < shape.getAllActiveShapes().size(); ++i)
    {
        if (HitBox::isHit(shooter.getHitBox(), shape.getAllActiveShapes().at(i).getHitBox()))
        {
            // if hit box detected, then check if flags also detect hit in correct direction
            checkHits(i);
        }
    }

    // If frame finished early syncing with fps
    frameTicks = fpsTimer.getTicks();
    if (frameTicks < SCREEN_TICKS_PER_FRAME)
    {
        // Wait remaining time
        SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    }
}

void Game::checkHits(int index)
{
    int flagNum = ballFlags.isHit(g);
    if (flagNum != -1)
    {
        // if first hit, turn on gravity
        if (!firstHit)
        {
            firstHit = true;
        }
        shooter.setMagnitude(shooter.getMagnitude() - 0.4);
        if (shooter.getMagnitude() < 0)
        {
            shooter.setMagnitude(0);
            isFalling = false;
        }
        Block& currentBlock = shape.getAllActiveShapes().at(index);
        g.playSound("assets/soundHit.wav");
        currentBlock.decreaseLife();

        if (currentBlock.getLife() <= 0)
        {
            ++score;
        }
        if (Game::score % 5 == 0)
        {
            if (Game::maxDifficulty <= 7)
            {
                ++Game::maxDifficulty;
            }
            if (Game::minDifficulty <= 5)
            {
                ++Game::minDifficulty;
            }
        }
    }

    if (flagNum == 0)
    {
        // top hit
        shooter.setDirection(M_PI - shooter.getDirection());
    }
    else if (flagNum == 2)
    {
        // bottom hit
        shooter.setDirection(3 * M_PI - shooter.getDirection());
        // if direction is close to straight up/down, set it to the closest PI/8 value so that it doesn't get stuck bouncing up/down
        if (shooter.getDirection() >= 7.0 * M_PI / 8.0 && shooter.getDirection() <= M_PI)
        {
            shooter.setDirection(7.0 * M_PI / 8.0);
        }
        else if (shooter.getDirection() >= M_PI && shooter.getDirection() <= 9.0 * M_PI / 8.0)
        {
            shooter.setDirection(9.0 * M_PI / 8.0);
        }
    }

    else if (flagNum == 1)
    {
        // right hit
        shooter.setDirection(0 - shooter.getDirection());
        if ((shooter.getDirection() > 15.0 / 16.0 * M_PI && shooter.getDirection() < 17.0 / 16.0 * M_PI) || (shooter.
            getDirection() > 31.0 / 16.0 * M_PI) || shooter.getDirection() < 1.0 / 16.0 * M_PI)
        {
            shooter.apply(PUSHLEFT);
        }
    }
    else if (flagNum == 3)
    {
        // left hit
        shooter.setDirection(0 - shooter.getDirection());
        if ((shooter.getDirection() > 15.0 / 16.0 * M_PI && shooter.getDirection() < 17.0 / 16.0 * M_PI) || shooter.
            getDirection() > 31.0 / 16.0 || shooter.getDirection() < 1 / 16.0 * M_PI)
        {
            shooter.apply(PUSHRIGHT);
        }
    }

    else if (flagNum == 4)
    {
        // top right corner hit
        shooter.setDirection(shooter.getDirection() - M_PI);
    }
    else if (flagNum == 5)
    {
        // bottom right corner hit
        shooter.setDirection(M_PI + shooter.getDirection());
    }
    else if (flagNum == 6)
    {
        // bottom left corner hit
        shooter.setDirection(M_PI + shooter.getDirection());
    }
    else if (flagNum == 7)
    {
        // top left corner hit
        shooter.setDirection(shooter.getDirection() - M_PI);
    }
}

void Game::updateLevel()
{
    g.clear();
    // reset the ball position to the top
    ballPoint.x = 500;
    ballPoint.y = 50;
    isFalling = false;
    // redraw the ball and update/draw the new level
    shooter.drawBall(ballPoint, BALLSIZE, BLACKCOLOR, g);
    shape.nextLevel();
    levelChanged = true;
    shape.drawLevel(startLoc, g);
}
