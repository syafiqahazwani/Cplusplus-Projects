#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

const int Width = 50;
const int Height = 20;

struct Position {
    int x, y;
};

void gotoxy(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(consoleHandle, &info);
    info.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void drawBorder() {
    for (int i = 0; i < Width; i++) {
        gotoxy(i, 0); cout << "#";
        gotoxy(i, Height - 1); cout << "#";
    }
    for (int i = 1; i < Height - 1; i++) {
        gotoxy(0, i); cout << "#";
        gotoxy(Width - 1, i); cout << "#";
    }
}

void drawMaze() {
    // Horizontal lines
    for (int i = 4; i < 45; i++) gotoxy(i, 3), cout << "*";
    for (int i = 2; i < 48; i++) gotoxy(i, 7), cout << "*";
    for (int i = 6; i < 44; i++) gotoxy(i, 12), cout << "*";
    for (int i = 8; i < 38; i++) gotoxy(i, 16), cout << "*";

    // Vertical lines
    for (int i = 4; i < 14; i++) gotoxy(10, i), cout << "*";
    for (int i = 2; i < 18; i++) gotoxy(20, i), cout << "*";
    for (int i = 6; i < 17; i++) gotoxy(30, i), cout << "*";
    for (int i = 3; i < 17; i++) gotoxy(40, i), cout << "*";

    // Blocks
    for (int i = 23; i <= 26; i++) {
        for (int j = 9; j <= 11; j++) {
            gotoxy(i, j); cout << "*";
        }
    }

    // Extra maze parts
    for (int i = 15; i < 35; i++) gotoxy(i, 5), cout << "*";
    for (int i = 25; i < 35; i++) gotoxy(i, 9), cout << "*";
    for (int i = 12; i < 16; i++) gotoxy(5, i), cout << "*";
    for (int i = 15; i < 19; i++) gotoxy(15, i), cout << "*";

    // Central block
    for (int i = 18; i < 21; i++) {
        for (int j = 14; j < 17; j++) {
            gotoxy(i, j); cout << "*";
        }
    }
}

bool isWall(int x, int y) {
    if (x <= 0 || x >= Width - 1 || y <= 0 || y >= Height - 1) return true;

    // Same pattern as drawMaze (mirror walls logic)
    if (y == 3 && x >= 4 && x < 45) return true;
    if (y == 5 && x >= 15 && x < 35) return true;
    if (y == 7 && x >= 2 && x < 48) return true;
    if (y == 9 && x >= 25 && x < 35) return true;
    if (y == 12 && x >= 6 && x < 44) return true;
    if (y == 16 && x >= 8 && x < 38) return true;

    if (x == 5 && y >= 12 && y < 16) return true;
    if (x == 10 && y >= 4 && y < 14) return true;
    if (x == 15 && y >= 15 && y < 19) return true;
    if (x == 20 && y >= 2 && y < 18) return true;
    if (x == 30 && y >= 6 && y < 17) return true;
    if (x == 40 && y >= 3 && y < 17) return true;

    if (x >= 23 && x <= 26 && y >= 9 && y <= 11) return true;
    if (x >= 18 && x <= 20 && y >= 14 && y <= 16) return true;

    return false;
}

int main() {
    hideCursor();
    system("cls");

    Position player = { 2, 2 };
    Position goal = { Width - 3, Height - 2 };

    drawBorder();
    drawMaze();

    gotoxy(player.x, player.y); cout << "@";
    gotoxy(goal.x, goal.y); cout << "()";

    while (true) {
        Position next = player;

        if (_kbhit()) {
            char key = _getch();

            if (key == 72) next.y--;      // Up
            else if (key == 80) next.y++; // Down
            else if (key == 75) next.x--; // Left
            else if (key == 77) next.x++; // Right

            if (!isWall(next.x, next.y)) {
                gotoxy(player.x, player.y); cout << " ";
                player = next;
                gotoxy(player.x, player.y); cout << "@";
            }

            if (player.x == goal.x && player.y == goal.y) {
                gotoxy(2, Height);
                cout << "🎉 You reached the goal! Well done! 🎉";
                break;
            }
        }

        Sleep(30);
    }

    return 0;
}
