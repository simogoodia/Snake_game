#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
using namespace std;

class snake_game {
private:
	// Direction
	enum Direction { top, right, bottom, left };
	// Map rules
	struct Map {
		int width, height, fruitX, fruitY;
	};
	// Snake form
	struct Snake {
		int headX, headY, tail_N, tailX[100], tailY[100];
		Direction dir;

	};
	// Player
	struct Player {
		int score;
		bool game_over;
	};
public:
	Map map;
	Snake snake;
	Player player;
	void rand_fruit() {
		srand(time(NULL));
		map.fruitX = rand() % (map.width - 2) + 1;
		map.fruitY = rand() % (map.height - 2) + 1;
	}
	void setting() {
		//Map
		map.width = 60;
		map.height = 20;
		// Map
		rand_fruit();
		// Snake
		snake.headX = map.width / 2;
		snake.headY = map.height / 2;
		snake.tail_N = 0;
		// Snake
		// Player
		player.score = 0;
		player.game_over = false;
		// Player
	}
	void print_press() {
			cout << "\t\tPress 'w' to move snake to UP\n";
			cout << "\t\tPress 'd' to move snake to RIGHT\n";
			cout << "\t\tPress 's' to move snake to DOWN\n";
			cout << "\t\tPress 'a' to move snake to LEFT\n";
			cout << "\t\tPress 'q' to move snake to EXIT\n";
			cout << "\t\tNote: lowercase letters!\n\n";
	}
	void draw() {
		system("cls");
		print_press();
		for (int i = 0; i < map.height; i++) {
			for (int j = 0; j < map.width; j++) {

				if (i == 0 || i == map.height - 1) cout << "#"; // y-axis of Map
				else if (j == 0 || j == map.width - 1) cout << "#"; // x-axis of Map
				else if (i == snake.headY && j == snake.headX) cout << "O"; // Position Head Snake on Map
				else if (i == map.fruitY && j == map.fruitX) cout << "$"; // Position fruit on Map
				else {
					bool printed = false;
					for (int k = 0; k < snake.tail_N; k++) {
						if (i == snake.tailY[k] && j == snake.tailX[k]) {
							cout << "o";
							printed = true;
							break;
						}
					}
					if (!printed) cout << " ";
				}
			}
			cout << "\n";
		}
		cout << "\t\t\tPlayer Score: " << player.score;
	}
	void input() {
		if (_kbhit()) {
			char ch = _getch();
			switch (ch) {
			case 'w': snake.dir = top; break;
			case 'd': snake.dir = right; break;
			case 's': snake.dir = bottom; break;
			case 'a': snake.dir = left; break;
			case 'q': exit(0); break;
			}
		}
	}
	void move() {
		snake_tail();
		switch (snake.dir) {
		case top: snake.headY--; break;
		case right: snake.headX++; break;
		case bottom: snake.headY++; break;
		case left: snake.headX--; break;
		}
	}
	void snake_tail() {
		int prevX = snake.tailX[0];
		int prevY = snake.tailY[0];
		int prev2X, prev2Y;
		snake.tailX[0] = snake.headX;
		snake.tailY[0] = snake.headY;
		for (int i = 1; i < snake.tail_N; i++) {
			prev2X = snake.tailX[i];
			prev2Y = snake.tailY[i];
			snake.tailX[i] = prevX;
			snake.tailY[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y;
		}
	}
	// Draw Game Over
	void draw_game_over() {
		cout << "\n";
		cout << "\t\t\t\t\t\t -------------\n";
		cout << "\t\t\t\t\t\t / Game Over /\n";
		cout << "\t\t\t\t\t\t -------------\n";
		cout << "\n\n";
	}
	// Draw Game Over
	void logic() {
		if (snake.headY < 0 || snake.headY > map.height - 1) {
			player.game_over = true;
			system("cls");
			draw_game_over();
			exit(0);
		}
		if (snake.headX < 0) snake.headX = map.width - 1;
		else if (snake.headX > map.width) snake.headX = 0;
		if (snake.headX == map.fruitX) {
			player.score += 10;
			rand_fruit();
			snake.tail_N++;
		}
		for (int i = 0; i < snake.tail_N; i++) {
			if (snake.tailX[i] == snake.headX && snake.tailY[i] == snake.headY) {
				player.game_over = true;
				system("cls");
				draw_game_over();
				cout << "\t\t\t\t\tPlayer Score: " << player.score;
				exit(0);
			}
		}
	}
};

int main() {
	snake_game snake;
	cout << "You want play? Y or N  ";
	if (_getch() == 'Y' || _getch() == 'y') {
		snake.setting();
		while (!snake.player.game_over) {
			snake.draw();
			snake.input();
			snake.move();
			snake.logic();
			Sleep(120);
		}
	}
	else {
		return 0;
	}
	system("pause");
	return 0;
}