// Live Update Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <filesystem>
#include <time.h>
namespace fs = std::filesystem;
void onUpdate( );

void sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

std::string path;
int main(int argc, char* argv[]) {


    std::cout << "argument count: " << argc << '\n';
    if (argc > 1) {
        path = argv[1];
    }
    else {
        std::cout << "please input file path\n";
        std::cin >> path;
    }

    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << '\n';
    }

    std::ifstream f(path, std::ios::in);
    if (f.fail()) {
        std::cout << "#################\n";
        std::cout << "# ERROR IN PATH #\n";
        std::cout << "#################\n";
        sleep(1000);
        return 1;
        onUpdate( );
    }
    f.close( );

    fs::file_time_type lastTime = fs::last_write_time(path);

    while (!GetAsyncKeyState(VK_DELETE)) {
        if (lastTime != fs::last_write_time(path)) {
            lastTime = fs::last_write_time(path);
            char buff[70];
            std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
            std::time_t now_c = std::chrono::system_clock::to_time_t(now);
            std::tm now_tm;
            localtime_s(&now_tm, &now_c);
            strftime(buff, sizeof(buff), "%T", &now_tm);
            std::cout << "File Changed at " << buff << "\n";
            onUpdate( );
        }
        
        

        sleep(100);
    }

    std::cin.get();
    return 0;
}

void onUpdate( ) {

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
