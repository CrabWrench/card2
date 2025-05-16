#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const int DECK_SIZE = 36;
const int HAND_SIZE = 18;

// Функция для инициализации и перемешивания колоды
void initializeAndShuffleDeck(int deck[]) {
    // Заполняем колоду значениями от 6 до 14 (6,7,8,9,10,Валет=11,Дама=12,Король=13,Туз=14)
    for (int i = 0; i < DECK_SIZE; ++i) {
        deck[i] = 6 + (i % 9);
    }

    // Перемешиваем колоду
    srand(time(0));
    for (int i = 0; i < DECK_SIZE; ++i) {
        int j = rand() % DECK_SIZE;
        swap(deck[i], deck[j]);
    }
}

// Функция для раздачи карт игрокам
void dealCards(const int deck[], int player1Hand[], int player2Hand[]) {
    for (int i = 0; i < HAND_SIZE; ++i) {
        player1Hand[i] = deck[i];
        player2Hand[i] = deck[i + HAND_SIZE];
    }
}

// Функция для определения победителя раунда
int determineRoundWinner(int card1, int card2) {
    if (card1 > card2) return 1;
    if (card2 > card1) return 2;
    return 0; // Ничья
}

// Функция для игры
void playGame(int player1Hand[], int player2Hand[],
    int player1Discard[],
    int& discardCount1, int& discardCount2) {
    int cardsPlayed = 0;

    while (cardsPlayed < HAND_SIZE) {
        int card1 = player1Hand[cardsPlayed];
        int card2 = player2Hand[cardsPlayed];

        cout << "Раунд " << cardsPlayed + 1 << ": ";
        cout << "Игрок 1 (" << card1 << ") vs Игрок 2 (" << card2 << ") - ";

        int winner = determineRoundWinner(card1, card2);

        if (winner == 1) {
            cout << "Игрок 1 побеждает!" << endl;
            player1Discard[discardCount1++] = card1;
            player1Discard[discardCount1++] = card2;
        }
        else if (winner == 2) {
            cout << "Игрок 2 побеждает!" << endl;
            player1Discard[discardCount2++] = card1;
            player1Discard[discardCount2++] = card2;
        }
        else {
            cout << "Ничья! Карты идут в сброс каждого игрока" << endl;
            player1Discard[discardCount1++] = card1;
            player1Discard[discardCount2++] = card2;
        }

        cardsPlayed++;
    }
}

// Функция для вывода результатов
void printResults(int player1Discard[],
    int discardCount1, int discardCount2) {
    cout << "\n=== Результаты игры ===" << endl;
    cout << "Игрок 1: " << discardCount1 << " карт в сбросе" << endl;
    cout << "Игрок 2: " << discardCount2 << " карт в сбросе" << endl;

    if (discardCount1 > discardCount2) {
        cout << "Победил Игрок 1!" << endl;
    }
    else if (discardCount2 > discardCount1) {
        cout << "Победил Игрок 2!" << endl;
    }
    else {
        cout << "Ничья!" << endl;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int deck[DECK_SIZE];               // Массив колоды
    int player1Hand[HAND_SIZE];        // Массив руки первого игрока
    int player2Hand[HAND_SIZE];        // Массив руки второго игрока
    int playerDiscard[DECK_SIZE];     // Массив сброса первого игрока

    int discardCount1 = 0;             // Счетчик сброса первого игрока
    int discardCount2 = 0;             // Счетчик сброса второго игрока

    // Инициализация игры
    initializeAndShuffleDeck(deck);
    dealCards(deck, player1Hand, player2Hand);

    // Играем
    playGame(player1Hand, player2Hand,
        playerDiscard,discardCount1, discardCount2);

    // Выводим результаты
    printResults(playerDiscard, discardCount1, discardCount2);

    return 0;
}