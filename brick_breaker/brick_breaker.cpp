#include <iostream>
#include <conio.h>      // For _kbhit() and _getch()
#include <windows.h>    // For system("cls")
#include <thread>       // For sleep_for
#include <chrono>       // For milliseconds
#include <vector>

using namespace std;

// Screen size
const int width = 40;
const int height = 20;

// Game objects
int ballX, ballY;
int ballDirX = 1, ballDirY = -1;
int paddleX = width / 2 - 3;
const int paddleWidth = 6;
bool gameOver = false;

// Brick data
const int brickRows = 3;
const int brickCols = 10;
bool bricks[brickRows][brickCols];

// Initialize game state
void initGame() {
    ballX = width / 2;
    ballY = height - 4;

    // Initialize bricks
    for (int i = 0; i < brickRows; ++i) {
        for (int j = 0; j < brickCols; ++j) {
            bricks[i][j] = true;
        }
    }
}

// Draw screen
void drawScreen() {
    system("cls");

    // Top border
    for (int i = 0; i < width + 2; ++i) cout << "#";
    cout << endl;

    for (int y = 0; y < height; ++y) {
        cout << "#"; // Left wall
        for (int x = 0; x < width; ++x) {
            if (x == ballX && y == ballY)
                cout << "O"; // Ball
            else if (y == height - 1 && x >= paddleX && x < paddleX + paddleWidth)
                cout << "="; // Paddle
            else {
                bool brickHere = false;
                for (int i = 0; i < brickRows; ++i) {
                    for (int j = 0; j < brickCols; ++j) {
                        int brickX = j * 4;
                        int brickY = i + 2;
                        if (x >= brickX && x < brickX + 4 && y == brickY && bricks[i][j]) {
                            cout << "#";
                            brickHere = true;
                            break;
                        }
                    }
                    if (brickHere) break;
                }
                if (!brickHere)
                    cout << " ";
            }
        }
        cout << "#" << endl; // Right wall
    }

    // Bottom border
    for (int i = 0; i < width + 2; ++i) cout << "#";
    cout << endl;
}

// Ball movement logic
void moveBall() {
    int nextX = ballX + ballDirX;
    int nextY = ballY + ballDirY;

    // Collision with walls
    if (nextX <= 0 || nextX >= width - 1)
        ballDirX *= -1;

    if (nextY <= 0)
        ballDirY *= -1;

    // Collision with paddle
    if (nextY == height - 1 && nextX >= paddleX && nextX < paddleX + paddleWidth) {
        ballDirY *= -1;
    }

    // Collision with bricks
    for (int i = 0; i < brickRows; ++i) {
        for (int j = 0; j < brickCols; ++j) {
            int brickX = j * 4;
            int brickY = i + 2;
            if (nextY == brickY && nextX >= brickX && nextX < brickX + 4 && bricks[i][j]) {
                bricks[i][j] = false;
                ballDirY *= -1;
            }
        }
    }

    ballX += ballDirX;
    ballY += ballDirY;

    if (ballY >= height)
        gameOver = true;
}

// Move paddle based on user input
void movePaddle() {
    if (_kbhit()) {
        char key = _getch();
        if (key == 'a' || key == 'A') {
            if (paddleX > 0)
                paddleX -= 2;
        } else if (key == 'd' || key == 'D') {
            if (paddleX + paddleWidth < width)
                paddleX += 2;
        }
    }
}

int main() {
    initGame();

    while (!gameOver) {
        drawScreen();
        moveBall();
        movePaddle();
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // delay for smoother play
    }

    system("cls");
    cout << "\n\n\tGame Over! Thanks for playing.\n";
    cout << "\tPress any key to exit...";
    _getch();
    return 0;
}
