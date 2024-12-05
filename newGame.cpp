#include "newGame.h"

int Game::score = 0;
int Game::maxDifficulty = 3;
int Game::minDifficulty = 1;

Game::Game(){
    ballPoint = {500, 50};
    shooter.setBallLoc(ballPoint);
}

void Game::run(){
    while (!g.getQuit()){
    	Block endLine;
    	point p1 = {0, 100};
    	point p2 = {1000, 100};
    	if (!gameOver) {
			fpsTimer.start();
			g.clear();

			shape.drawLevel(startLoc, g);
			shooter.drawBall(ballPoint, BALLSIZE, BLACKCOLOR, g);

			endLine.drawLine(p1, p2, BLACKCOLOR, g);
			setGameOver();

			if (levelChanged){
				shape.createLevel(startLoc);
				levelChanged = false;
			}
			if (g.mouseClick() && !gameOver){
				launchBall();
			}
			if (isFalling)
			{
				ballFalling();
			}
			if (bottomHit()){
				updateLevel();
			}

			//while in the game loop, update the screen
			g.Sleep(10);
			++countedFrames;
			g.update();
    	}
    	else {
    		displayGameOverScreen();
    	}
    }

    g.setQuit(true);
    g.Sleep(500);
}

bool Game::bottomHit(){
    return ballPoint.y > 980;
}

void Game::launchBall(){
    clickPos = g.getMouseClick();
    ballPoint.y = 50;
    ballPoint.x = 500;
    xPos = ballPoint.x;
    yPos = ballPoint.y;
    xDist = clickPos.x - ballPoint.x;
    yDist = clickPos.y - ballPoint.y;

    shooter.setMagnitude(13);
    shooter.setDirection(atan(static_cast<double>(xDist) / yDist));

    // ballColor = BLACKCOLOR;
    isFalling = true;
    firstHit = false;
}

void Game::ballFalling(){

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

    // if hit left wall
    if (ballPoint.x < 15)
    {
        shooter.setDirection(2 * M_PI - shooter.getDirection());
    }
    // if hit right wall
    else if (ballPoint.x > 985)
    {
        shooter.setDirection(2 * M_PI - shooter.getDirection());
    }
    for (int i = 0; i < shape.getAllActiveShapes().size(); ++i)
    {
    	Block &currentBlock = shape.getAllActiveShapes().at(i);

        if (HitBox::isHit(shooter.getHitBox(), currentBlock.getHitBox()))
        { // if hit box detected, then check if flags also detect hit in correct direction
            flagNum = ballFlags.isHit(g);
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

                g.initSound("sounds/soundHit.wav");
                g.playSound("sounds/soundHit.wav");
                cout << "Before: Block life: " << currentBlock.getLife() << endl;
                cout << "square hit !!" << endl;
                currentBlock.decreaseLife();
                cout << "After: Block life: " << currentBlock.getLife() << endl;

                ++Game::score;
                cout << "Score: " << Game::score << endl;
                if (Game::score % 5 == 0) {
                	if (Game::maxDifficulty <= 7) {
                		++Game::maxDifficulty;
                	}
                	if (Game::minDifficulty <= 5) {
                		++Game::minDifficulty;
                	}


                	cout << "Max difficulty is now: " << Game::maxDifficulty << endl;
                	cout << "Min difficulty is now: " << Game::minDifficulty << endl;
                }

                cout << endl;

            }

            if (flagNum == 0)
            { // top hit
                cout << "top flag initial: " << shooter.getDirection() << endl;
                shooter.setDirection(M_PI - shooter.getDirection());
                cout << "top flag new: " << shooter.getDirection() << endl;
            }
            else if (flagNum == 2)
            { // bottom hit
                cout << "bottom flag: " << shooter.getDirection() << endl;
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
                cout << "bottom flag new: " << shooter.getDirection() << endl;
            }

            else if (flagNum == 1)
            { // right hit
                cout << "right flag: " << shooter.getDirection() << endl;
                shooter.setDirection(0 - shooter.getDirection());
                if ((shooter.getDirection() > 15.0 / 16.0 * M_PI && shooter.getDirection() < 17.0 / 16.0 * M_PI) || (shooter.getDirection() > 31.0 / 16.0 * M_PI) || shooter.getDirection() < 1.0 / 16.0 * M_PI)
                {
                    shooter.apply(PUSHLEFT);
                }
                cout << "right flag new: " << shooter.getDirection() << endl;
            }
            else if (flagNum == 3)
            { // left hit
                cout << "left flag: " << shooter.getDirection() << endl;
                shooter.setDirection(0 - shooter.getDirection());
                if ((shooter.getDirection() > 15.0 / 16.0 * M_PI && shooter.getDirection() < 17.0 / 16.0 * M_PI) || shooter.getDirection() > 31.0 / 16.0 || shooter.getDirection() < 1 / 16.0 * M_PI)
                {
                    shooter.apply(PUSHRIGHT);
                }
                cout << "left flag new: " << shooter.getDirection() << endl;
            }

            else if (flagNum == 4)
            { // top right corner hit
                cout << "TOP RIGHT CORNER" << endl;
                shooter.setDirection(shooter.getDirection() - M_PI);
            }
            else if (flagNum == 5)
            { // bottom right corner hit
                cout << "BOTTOM RIGHT CORNER" << endl;
                shooter.setDirection(M_PI + shooter.getDirection());
            }
            else if (flagNum == 6)
            { // bottom left corner hit
                cout << "BOTTOM LEFT CORNER" << endl;
                shooter.setDirection(M_PI + shooter.getDirection());
            }
            else if (flagNum == 7)
            { // top left corner hit
                cout << "TOP LEFT CORNER" << endl;
                shooter.setDirection(shooter.getDirection() - M_PI);
            }
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


void Game::updateLevel(){

    g.clear();

    cout << "POSITION RESET" << endl;
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

void Game::setGameOver() {
	for (int i = 0; i < shape.getAllActiveShapes().size(); ++i) {
		Block &currentBlock = shape.getAllActiveShapes().at(i);
	    if (currentBlock.getLocation().y <= 100 && currentBlock.getLife() != 0) {
	    	cout << "GAME OVER!!!!" << endl;
	    	gameOver = true;
	    	//exit(0);
	    }
	}
}

void Game::displayGameOverScreen() {
	g.clear();
	g.update();
}

