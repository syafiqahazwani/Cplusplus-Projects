#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

const int width = 40;
const int height = 20;
int ballX, ballY, player1Y, player2Y;
int ballDirX = -1, ballDirY = -1;
int score1 = 0, score2 = 0;
bool quit = false;

void gotoxy(int x, int y) {
    COORD c;
    c.X = x; c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";
            if (i == ballY && j == ballX)
                cout << "O";
            else if (j == 1 && i >= player1Y && i < player1Y + 4)
                cout << "|";
            else if (j == width - 2 && i >= player2Y && i < player2Y + 4)
                cout << "|";
            else
                cout << " ";
            if (j == width - 1) cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    cout << "Player: " << score1 << "  Computer: " << score2 << endl;
}

void input() {
    if (_kbhit()) {
        char c = _getch();
        if (c == 'w' || c == 'W') player1Y--;
        if (c == 's' || c == 'S') player1Y++;
        if (c == 27) quit = true;
    }
}

void logic() {
    ballX += ballDirX;
    ballY += ballDirY;

    // Ball hits top or bottom
    if (ballY == 0 || ballY == height - 1)
        ballDirY *= -1;

    // Player 1 paddle collision
    if (ballX == 2 && ballY >= player1Y && ballY <= player1Y + 3)
        ballDirX *= -1;

    // Player 2 (computer) paddle collision
    if (ballX == width - 3 && ballY >= player2Y && ballY <= player2Y + 3)
        ballDirX *= -1;

    // Score
    if (ballX <= 0) {
        score2++;
        ballX = width / 2;
        ballY = height / 2;
        ballDirX = -1;
    }
    if (ballX >= width - 1) {
        score1++;
        ballX = width / 2;
        ballY = height / 2;
        ballDirX = 1;
    }

    // Computer AI movement
    if (player2Y + 1 < ballY)
        player2Y++;
    else if (player2Y + 1 > ballY)
        player2Y--;

    // Boundaries for paddles
    if (player1Y < 0) player1Y = 0;
    if (player1Y + 4 > height) player1Y = height - 4;
    if (player2Y < 0) player2Y = 0;
    if (player2Y + 4 > height) player2Y = height - 4;

    // End game condition
    if (score1 == 5 || score2 == 5) quit = true;
}

int main() {
    ballX = width / 2;
    ballY = height / 2;
    player1Y = height / 2 - 2;
    player2Y = height / 2 - 2;

    while (!quit) {
        draw();
        input();
        logic();
        Sleep(60); // slow down game speed
    }

    system("cls");
    cout << (score1 == 5 ? "You Win!" : "Computer Wins!") << endl;
    cout << "Final Score - You: " << score1 << " Computer: " << score2 << endl;
    return 0;
}
