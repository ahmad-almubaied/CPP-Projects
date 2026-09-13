#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
enum GameChoice { ROCK = 1, PAPER = 2, SCISSORS = 3 };
void setScreenColor(string winner) {
    if (winner == "computer") {
        system("color 4F"); 
    }
    else if (winner == "player") {
        system("color 2F"); 
    }
    else {
        system("color E0");  
    }
}

int getComputerChoice() {
    return (rand() % 3) + 1;
}

string choiceToString(int choice) {
    if (choice == ROCK) return "Rock";
    if (choice == PAPER) return "Paper";
    return "Scissors";
}

void startGame() {
    char playAgain;

    do {
        system("color 07");
        system("cls");

        int rounds;
        cout << "Enter how many rounds the game will be: ";
        cin >> rounds;

        int playerScore = 0;
        int computerScore = 0;
        int drawScore = 0;

        for (int i = 1; i <= rounds; i++) {
            cout << "\n================ Round [" << i << "/" << rounds << "] ================\n";
            cout << "Choose: [1] Rock, [2] Paper, [3] Scissors: ";
            int playerChoice;
            cin >> playerChoice;

            int computerChoice = getComputerChoice();

            cout << "\nPlayer Choice  : " << choiceToString(playerChoice) << endl;
            cout << "Computer Choice: " << choiceToString(computerChoice) << endl;

            if (playerChoice == computerChoice) {
                setScreenColor("draw");
                cout << "\nResult: Round Draw!\n";
                drawScore++;
            }
            else if ((playerChoice == ROCK && computerChoice == SCISSORS) ||
                (playerChoice == PAPER && computerChoice == ROCK) ||
                (playerChoice == SCISSORS && computerChoice == PAPER)) {
                setScreenColor("player");
           
                cout << "\nResult: You Won This Round!\n";
                playerScore++;
            }
            else {
                setScreenColor("computer");
                cout << "\a";
                cout << "\nResult: Computer Won This Round!\n";
                computerScore++;
            }
        }

        cout << "\n=========================================\n";
        cout << "               GAME OVER                 \n";
        cout << "=========================================\n";
        cout << "Player Wins   : " << playerScore << endl;
        cout << "Computer Wins : " << computerScore << endl;
        cout << "Draws         : " << drawScore << endl;
        cout << "=========================================\n";

        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');
}

int main() {
    srand(time(0));
    startGame();
    return 0;
}
