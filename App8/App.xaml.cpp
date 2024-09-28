#include <iostream>  
#include <windows.h>   
#include <cstdlib>  
#include <ctime>    
// aftours: LeRMoN, Kolia, XeSh, FlasH. school Shag, code: house worken. my tg:https://t.me/LERMONfupa <- click Ctrl+Left mouse, im check sms.Надеюсь правильно написал.     \\ 
// Кодом вдохновился из урочка 
using namespace std;

enum KeyCodes { ENTER = 13, ESCAPE = 27, LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80, SPACEBAR = 32 };
enum Colors { DARKGREEN = 2, RED = 12, YELLOW = 14, BLUE = 9 };
enum Objects { HALL, WALL, COIN, ENEMY };

void initConsole();
void generateLocation(int location[][50], int width, int height);
void displayLocation(int location[][50], int width, int height, HANDLE h);
void movePlayer(int& x, int& y, int code, int location[][50], int width, int height);
void handleCoin(int& coins, int& locationValue);

int main() {
    const int WIDTH = 50;
    const int HEIGHT = 15;
    int location[HEIGHT][WIDTH] = {};
    int coins = 0;

    initConsole();
    srand(static_cast<unsigned>(time(0)));
    generateLocation(location, WIDTH, HEIGHT);

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    displayLocation(location, WIDTH, HEIGHT, h);

    COORD position;
    position.X = 1;
    position.Y = 2;

    SetConsoleCursorPosition(h, position);
    SetConsoleTextAttribute(h, BLUE);
    cout << (char)1;

    while (true) {
        int code = _getch();
        if (code == 224)
            code = _getch();

        SetConsoleCursorPosition(h, position);
        SetConsoleTextAttribute(h, BLUE);
        cout << " ";

        switch (code) {
        case ENTER:
            break;
        case SPACEBAR:
            break;
        case ESCAPE:
            return 0;
        case RIGHT:
        case LEFT:
        case UP:
        case DOWN:
            movePlayer(position.X, position.Y, code, location, WIDTH, HEIGHT);
            break;
        default:
            cout << code << "\n";
            break;
        }

        SetConsoleCursorPosition(h, position);
        SetConsoleTextAttribute(h, BLUE);
        cout << (char)1;
        handleCoin(coins, location[position.Y][position.X]);
    }
}
void initConsole() {
    system("title Бомбер!");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 100;
    SetConsoleCursorInfo(h, &info);
}
void generateLocation(int location[][50], int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            location[y][x] = rand() % 4;
            if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
                location[y][x] = WALL;
            if ((x == 0 && y == 2) || (x == width - 1 && y == height - 3))
                location[y][x] = HALL;

            if (location[y][x] == ENEMY) {
                int prob = rand() % 10;
                if (prob != 0)
                    location[y][x] = HALL;
            }
        }
    }
}
void displayLocation(int location[][50], int width, int height, HANDLE h) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            switch (location[y][x]) {
            case HALL: 
                cout << " ";
                break;
            case WALL: // Стеночка \\ 
                SetConsoleTextAttribute(h, DARKGREEN);
                cout << (char)177;
                break;
            case COIN: // Монеточка \\ 
                SetConsoleTextAttribute(h, YELLOW);
                cout << (char)15;
                break;
            case ENEMY: // Врагусик \\ 
                SetConsoleTextAttribute(h, RED);
                cout << (char)1;
                break;
            }
        }
        cout << "\n";
    }
}

void movePlayer(int& x, int& y, int code, int location[][50], int width, int height) {
    switch (code) {
    case RIGHT:
        if (location[y][x + 1] != WALL)
            x++;
        break;
    case LEFT:
        if (x > 0 && location[y][x - 1] != WALL)
            x--;
        break;
    case UP:
        if (y > 0 && location[y - 1][x] != WALL)
            y--;
        break;
    case DOWN:
        if (y < height - 1 && location[y + 1][x] != WALL)
            y++;
        break;
    }
}

void handleCoin(int& coins, int& locationValue) {
    if (locationValue == COIN) {
        coins++;
        cout << coins << "\n";
        locationValue = HALL; // монеточка после собирание стает коридорчиком
    }
}

// aftours: LeRMoN, Kolia, XeSh, FlasH. school: Shag, code: house work. my tg:https://t.me/LERMONfupa <- click Ctrl+Left mouse, im check sms|/\|Надеюсь правильно написал.