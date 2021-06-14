#include <iostream>
#include <random>
#include <algorithm>

#define CHECK_DOT(X,Z) (((X) >= 0) && ((X) < (Z)))
#define POINT_ITEM(a,r,c) (*((*((a) + (r))) + (c)))
#define SIZE_ARRAY(a) ((sizeof(a)) / (sizeof(a[0])))
//#define SIZE_ARRAY(a,b) ((sizeof(a)) / (sizeof(b)))

//C++11 <random>
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(0, 2);

enum GameState {WIN, NOTWIN, DRAW};
enum PLAYER {HUMAN='X', AI='O', EMPTY='_'}; 
typedef struct {
    int szX;
    int szY;
    PLAYER **map;
    int toWin;
} Field;
void setValue(PLAYER **arr, const int row, const int col, PLAYER value) {
    POINT_ITEM(arr, row, col) = value;
}
char getValue(PLAYER **arr, const int row, const int col) {
    return POINT_ITEM(arr, row, col);
}
void initField(Field&);
void printField(const Field&);
bool isEmptyCell(const Field&, const int, const int);
bool isValidCell(const Field&, const int, const int);
void playerMove(Field&);
bool checkLine(const Field&, int, int, int, int, int);
GameState checkWin(const Field&, PLAYER);
bool aiTryWin(Field&);
bool aiTryBlock(Field&);
void aiMove(Field&);
bool gameCheck(const Field& f, PLAYER dot, const std::string& winString) {
    printField(f);
    GameState result = checkWin(f, dot);
    if (result == WIN) {
        std::cout << winString << std::endl;
        return true;
    } else if (result == DRAW) {
        std::cout << "Draw" << std::endl;
        return true;
    } else
        return false;
}

int main(int argc, const char** argv) { // 1TBS
    int winCount = 0;
    Field f;
    while (true) {
        initField(f);
        printField(f);
        while (true) {
            playerMove(f);
            if (gameCheck(f, HUMAN, "Human win!")) break;
            aiMove(f);
            if (gameCheck(f, AI, "Computer win!")) break;
        }
        std::string answer;
        std::cout << "Play again? ";
        std::cin >> answer;
        // y, yes, yep, yay, yeah, Y, YES, YEP
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        if (answer.find('y') != 0) break;
    }
    
    return 0; 
}

void initField(Field& field) {
    field.szX = 3;
    field.szY = 3;
    field.toWin = 3;
    field.map = (PLAYER**) calloc(field.szY, sizeof(PLAYER *));
    for (int y = 0; y < field.szY; y++) {
        * (field.map + y) = (PLAYER*) calloc(field.szX, sizeof(PLAYER));
        for (int x = 0; x < field.szX; x++) {
            setValue(field.map, y, x, EMPTY);
        }
    }
}
void printField(const Field& field) {
    std::system("clear"); //"cls" in windows

    std::cout << "-x 1x 2x 3x" << std::endl; // чутка причесал
    for (int y = 0; y < field.szY; y++) {
      std::cout << (y + 1) << "y|";  //чутка причесал внешний вид
        for (int x = 0; x < field.szX; x++) {
            std::cout << getValue(field.map, y, x) << " |";
        }
        std::cout << std::endl;

    }
}
bool isEmptyCell(const Field& field, const int x, const int y) {
    return getValue(field.map, y, x) == EMPTY;
}
bool isValidCell(const Field& field, const int x, const int y) {
    return CHECK_DOT(x, field.szX) && CHECK_DOT(y, field.szY);
}
void playerMove(Field& field) {
    int x;
    int y;
    bool hasErrors = false;
    do {
        if (hasErrors) {
            std::cout << "your coordinate was wrong!" << std::endl;
        }
        std::cout << "Enter your move coordinates X and Y (1 to " << field.szX << ") space separated >> ";
        std::cin >> x;
        std::cin >> y;
        //<regex>
        // todo check if numbers are entered
        x--;
        y--;
        hasErrors = true;
    } while (!isValidCell(field, x, y) || !isEmptyCell(field, x, y));
    setValue(field.map, y, x, HUMAN);    
}
//!a||!b == !(a&&b)

GameState checkWin(const Field& field, PLAYER c) {
	bool hasEmpty = false;
    //todo optimize this checks))
	for (int y = 0; y < field.szY; y++) {
		for (int x = 0; x < field.szX; x++) {
			if (getValue(field.map, y, x) == EMPTY) {
				hasEmpty = true;
				continue;
			}
			if (getValue(field.map, y, x) != c) continue;
			if (checkLine(field, y, x, 1,  0, field.toWin)) return WIN;
			if (checkLine(field, y, x, 1,  1, field.toWin)) return WIN;
			if (checkLine(field, y, x, 0,  1, field.toWin)) return WIN;
			if (checkLine(field, y, x, 1, -1, field.toWin)) return WIN;
		}
	}
	return (hasEmpty) ? NOTWIN : DRAW;
}
bool checkLine(const Field& field, int y, int x, int vx, int vy, int len) {
	const int endX = x + (len - 1) * vx;
	const int endY = y + (len - 1) * vy;
	if (!isValidCell(field, endX, endY))
		return false;
	char c = getValue(field.map, y, x);
    
	for (int i = 0; i < len; i++) {
        //if (             map  [y + i * vy]  [x + i * vx]  != c)
		if (getValue(field.map, (y + i * vy), (x + i * vx)) != c)
			return false;
	}
	return true;
}
bool aiTryWin(Field& field) {
	for (int y = 0; y < field.szY; y++) {
		for (int x = 0; x < field.szX; x++) {
			if (isEmptyCell(field, x, y)) {
				setValue(field.map, y, x, AI);
				if (checkWin(field, AI) == WIN)
					return true;
				setValue(field.map, y, x, EMPTY);
			}
		}
	}
	return false;
}
bool aiTryBlock(Field& field) {
	for (int y = 0; y < field.szY; y++) {
		for (int x = 0; x < field.szX; x++) {
			if (isEmptyCell(field, x, y)) {
				setValue(field.map, y, x, HUMAN);
				if (checkWin(field, HUMAN) == WIN) {
					setValue(field.map, y, x, AI);
   					return true;
				}
				setValue(field.map, y, x, EMPTY);
			}
		}
	}
	return false;
}
void aiMove(Field& field) {
    //todo make it more clever
	if (aiTryWin(field)) return;
	if (aiTryBlock(field)) return;
	int x;
	int y;
	do {
		x = dist(mt);
		y = dist(mt);
	} while (!isEmptyCell(field, x, y));
	setValue(field.map, y, x, AI);
}

