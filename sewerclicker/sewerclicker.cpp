#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <locale.h>    

using namespace std;

int target_cps;
HWND gameWindow = nullptr;

void initGameWindow() {
    gameWindow = FindWindowA("LWJGL", nullptr);
    if (gameWindow == nullptr) {
        std::cerr << "Game window not found. Make sure the game is running." << std::endl;
        exit(1);
    }
}

void sendClickMessage() {
    if (gameWindow) {
        PostMessage(gameWindow, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(0, 0));
        PostMessage(gameWindow, WM_LBUTTONUP, 0, MAKELPARAM(0, 0));
    }
}

int main() {
    std::wcout << u8R"(
          _____  ___ __    __   ___ ____  
         / ___/ /  _|  T__T  T /  _|    \ 
        (   \_ /  [_|  |  |  |/  [_|  D  )
         \__  Y    _|  |  |  Y    _|    / 
         /  \ |   [_l  `  '  |   [_|    \ 
         \    |     T\      /|     |  .  Y
          \___l_____j \_/\_/ l_____l__j\_j v0.0.1

                Made by: askiesec
                 
        )";  '\n';
    std::cout << "        Enter Target CPS: ";
    std::cin >> target_cps;

    initGameWindow();
    const int interval = 1000 / target_cps;

    while (true) {
        while (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            sendClickMessage();
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
    }

    setlocale(LC_ALL, "");

    return 0;
}
