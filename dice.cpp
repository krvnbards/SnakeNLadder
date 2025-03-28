#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>

using namespace std;

void diceArt(int number) {
    const char* diceFaces[6][7] = {
        {
            "█▀▀▀▀▀▀▀▀▀▀▀▀▀█",
            "█             █",
            "█             █",
            "█      ⬤      █",
            "█             █",
            "█             █",
            "█▄▄▄▄▄▄▄▄▄▄▄▄▄█"
        },
        {
            "█▀▀▀▀▀▀▀▀▀▀▀▀▀█",
            "█ ⬤           █",
            "█             █",
            "█             █",
            "█             █",
            "█           ⬤ █",
            "█▄▄▄▄▄▄▄▄▄▄▄▄▄█"
        },
        {
            "█▀▀▀▀▀▀▀▀▀▀▀▀▀█",
            "█ ⬤           █",
            "█             █",
            "█      ⬤      █",
            "█             █",
            "█           ⬤ █",
            "█▄▄▄▄▄▄▄▄▄▄▄▄▄█"
        },
        {
            "█▀▀▀▀▀▀▀▀▀▀▀▀▀█",
            "█ ⬤         ⬤ █",
            "█             █",
            "█             █",
            "█             █",
            "█ ⬤         ⬤ █",
            "█▄▄▄▄▄▄▄▄▄▄▄▄▄█"
        },
        {
            "█▀▀▀▀▀▀▀▀▀▀▀▀▀█",
            "█ ⬤         ⬤ █",
            "█             █",
            "█      ⬤      █",
            "█             █",
            "█ ⬤         ⬤ █",
            "█▄▄▄▄▄▄▄▄▄▄▄▄▄█"
        },
        {
            "█▀▀▀▀▀▀▀▀▀▀▀▀▀█",
            "█ ⬤    ⬤    ⬤ █",
            "█             █",
            "█             █",
            "█             █",
            "█ ⬤    ⬤    ⬤ █",
            "█▄▄▄▄▄▄▄▄▄▄▄▄▄█"
        }
    };

    for (int i = 0; i < 7; ++i) {
        cout << diceFaces[number - 1][i] << endl;
    }
}

void rollDiceAnimation() {
    srand(time(0));
    int revealAt = rand() % 3 + 3;

    for (int i = 0; i < revealAt; ++i) {
        int randomFace = rand() % 6 + 1;
        cout << "\033[H\033[J";
        cout << "Rolling the dice...\n";
        diceArt(randomFace);
        int delay = rand() % 300 + 500;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

void revealFinalDice() {
    int finalNumber = rand() % 6 + 1;
    cout << "\033[H\033[J";
    cout << "The dice rolled...\n";
    diceArt(finalNumber);
    cout << "You rolled a " << finalNumber << "!" << endl;
}

int main() {
    system("chcp 65001 > nul"); // needed ni bai para ma compile ang ascii art
    char choice;
    do {
        cout << "Rolling the dice...\n";
        rollDiceAnimation();
        revealFinalDice();

        cout << "Roll again? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "Goodbye!" << endl;
    return 0;
}
