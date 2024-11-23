#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// Símbolos
const char PLAYER = 'X';
const char AI = 'O';
const char EMPTY = ' ';

// Función para imprimir
void printGrid(const vector<char>& board) {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        cout << " " << (board[i] == EMPTY ? char('1' + i) : board[i]);
        if (i % 3 != 2) cout << " |";
        else if (i != 8) cout << "\n---+---+---\n";
    }
    cout << "\n";
}

// Función para verificar si alguien ha ganado
bool isWinner(const vector<char>& board, char player) {
    const int winPatterns[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Filas
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columnas
        {0, 4, 8}, {2, 4, 6}             // Diagonales
    };
    for (auto& pattern : winPatterns) {
        if (board[pattern[0]] == player && 
            board[pattern[1]] == player && 
            board[pattern[2]] == player) {
            return true;
        }
    }
    return false;
}

// Función para verificar si se lleno el grid
bool isDraw(const vector<char>& board) {
    for (char cell : board) {
        if (cell == EMPTY) return false;
    }
    return true;
}

// Función Minimax
int minimax(vector<char>& board, bool isMaximizing) {
    if (isWinner(board, AI)) return 10;
    if (isWinner(board, PLAYER)) return -10;
    if (isDraw(board)) return 0;

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < 9; i++) {
            if (board[i] == EMPTY) {
                board[i] = AI;
                int score = minimax(board, false);
                board[i] = EMPTY;
                bestScore = max(bestScore, score);
            }
        }
        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < 9; i++) {
            if (board[i] == EMPTY) {
                board[i] = PLAYER;
                int score = minimax(board, true);
                board[i] = EMPTY;
                bestScore = min(bestScore, score);
            }
        }
        return bestScore;
    }
}

// Función para encontrar el mejor movimiento para la IA
int findBestMove(vector<char>& board) {
    int bestScore = numeric_limits<int>::min();
    int move = -1;
    for (int i = 0; i < 9; i++) {
        if (board[i] == EMPTY) {
            board[i] = AI;
            int score = minimax(board, false);
            board[i] = EMPTY;
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    return move;
}

// Función para obtener una entrada válida del usuario
int getValidInput(const vector<char>& board) {
    int move;
    while (true) {
        cout << "\nTu turno: ";
        cin >> move;

        // Verificar si la entrada es válida
        if (cin.fail()) {
            cin.clear(); // Limpia el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta la entrada inválida
            cout << "Por favor, ingresa un número válido entre 1 y 9.\n";
            continue;
        }

        // Ajustar a índice 0 y verificar si el movimiento es válido
        move--;
        if (move < 0 || move >= 9 || board[move] != EMPTY) {
            cout << "Movimiento inválido. Inténtalo de nuevo.\n";
        } else {
            return move;
        }
    }
}

// Función main
int main() {
    vector<char> board(9, EMPTY);
    cout << "¡Bienvenido a Tic Tac Toe!\n";
    cout << "Elige tu posición ingresando un número (1-9):\n";
    printGrid(board);

    while (true) {
        // Turno del jugador
        int playerMove = getValidInput(board);
        board[playerMove] = PLAYER;

        printGrid(board);

        if (isWinner(board, PLAYER)) {
            cout << "¡Felicidades! ¡Ganaste!\n";
            break;
        }
        if (isDraw(board)) {
            cout << "¡Es un empate!\n";
            break;
        }

        // Turno de la IA
        cout << "\nTurno de la IA...\n";
        int aiMove = findBestMove(board);
        board[aiMove] = AI;

        printGrid(board);

        if (isWinner(board, AI)) {
            cout << "La IA ha ganado. ¡Mejor suerte la próxima vez!\n";
            break;
        }
        if (isDraw(board)) {
            cout << "¡Es un empate!\n";
            break;
        }
    }

    return 0;
}
