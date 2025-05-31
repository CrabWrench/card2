#include <iostream>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <thread>

class Timer {
public:
    Timer() {
        start_time = std::chrono::steady_clock::now();
    }

    void reset() {
        start_time = std::chrono::steady_clock::now();
    }

    double elapsed() {
        auto end_time = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end_time - start_time;
        return elapsed_seconds.count();
    }

private:
    std::chrono::steady_clock::time_point start_time;
};
using namespace std;

const int DECK_SIZE = 36;
const int HAND_SIZE = 18;

void initializeAndShuffleDeck(int deck[]) {
    for (int i = 0; i < DECK_SIZE; ++i) {
        deck[i] = 6 + (i % 9);
    }

    srand(time(0));
    for (int i = 0; i < DECK_SIZE; ++i) {
        int j = rand() % DECK_SIZE;
        swap(deck[i], deck[j]);
    }
}

void dealCards(const int deck[], int player1Hand[], int player2Hand[]) {
    for (int i = 0; i < HAND_SIZE; ++i) {
        player1Hand[i] = deck[i];
        player2Hand[i] = deck[i + HAND_SIZE];
    }
}

int determineRoundWinner(int card1, int card2) {
    if (card1 > card2) return 1;
    if (card2 > card1) return 2;
    return 0;
}


void playGame(int player1Hand[], int player2Hand[],
    int player1Discard[],
    int& discardCount1, int& discardCount2) {
    int cardsPlayed = 0;

    while (cardsPlayed < HAND_SIZE) {
        int card1 = player1Hand[cardsPlayed];
        int card2 = player2Hand[cardsPlayed];

        cout << "Raund " << cardsPlayed + 1 << ": ";
        cout << "Player 1 (" << card1 << ") vs Player 2 (" << card2 << ") - ";

        int winner = determineRoundWinner(card1, card2);

        if (winner == 1) {
            cout << "Player 1 WIN!" << endl;
            player1Discard[discardCount1++] = card1;
            player1Discard[discardCount1++] = card2;
        }
        else if (winner == 2) {
            cout << "Player 2 WIN!" << endl;
            player1Discard[discardCount2++] = card1;
            player1Discard[discardCount2++] = card2;
        }
        else {
            cout << "DRAW" << endl;
            player1Discard[discardCount1++] = card1;
            player1Discard[discardCount2++] = card2;
        }

        cardsPlayed++;
    }
}

// Функция для вывода результатов
void printResults(int player1Discard[],
    int discardCount1, int discardCount2) {
    cout << "\n=== game results ===" << endl;
    cout << "player 1: " << discardCount1 << " thrown cards" << endl;
    cout << "player 2: " << discardCount2 << " thrown cards" << endl;

    if (discardCount1 > discardCount2) {
        cout << "Player 1 WIN!" << endl;
    }
    else if (discardCount2 > discardCount1) {
        cout << "Player 2 WIN!" << endl;
    }
    else {
        cout << "even!" << endl;
    }
    cout << endl;
}

int main() {
    int deck[DECK_SIZE];           
    int player1Hand[HAND_SIZE];     
    int player2Hand[HAND_SIZE];     
    int playerDiscard[DECK_SIZE];     

    int discardCount1 = 0;            
    int discardCount2 = 0;            

    initializeAndShuffleDeck(deck);
    dealCards(deck, player1Hand, player2Hand);

    playGame(player1Hand, player2Hand,
        playerDiscard,discardCount1, discardCount2);

    printResults(playerDiscard, discardCount1, discardCount2);
    Timer timer;

    std::this_thread::sleep_for(std::chrono::seconds(5));

    double elapsed_time = timer.elapsed();
    return 0;
}