#include<iostream>

using namespace std;
int field[100][100];
//-1-Мина
//0-8-Клетки

int field_p[100][100];
/*
* -2-Закрытая Клетка
* -1-Флаг
* 0-8-Открытая Клетка

*/
const int  N = 5, M = 5, K = 5;
void print_field() {
	system("cls");
	cout << "Здарова Засранец .Сыграем в Сапер?\n";
	cout << endl;
	cout << "  ";
	for (int i = 0; i < M; ++i) {
		cout << " " << i + 1;
		if (i + 1 < 10)cout << " ";
	}
	cout << endl;

	for (int i = 0; i < N; i++) {

		cout << i + 1 << " ";
		if (i + 1 < 10)cout << ' ';
		for (int j = 0; j < M; j++) {
			if (field_p[i][j] == -2)cout << "-  ";
			else if (field_p[i][j] == -1)cout << "f  ";
			else if (field_p[i][j] == -3)cout << "*  ";
			else cout << field_p[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl << endl << endl;

}
void dfs(int x, int y) {
	if (x < 0 || x >= N || y < 0 || y >= M|| field_p[x][y]>-2) return;
	field_p[x][y] = field[x][y];
    if (field[x][y] > 0)return;
	for (int i2 = x - 1; i2 <= x + 1; ++i2) {
		for (int j2 = y - 1; j2 <= y + 1; ++j2) {
			if (i2 != x || j2 != y) dfs(i2, j2);
		}
	}

}

//true-Не Взорвались
bool open_cell(int x, int y) {
	if (field[x][y] == -1)return false;
	if (field[x][y] > 0) {
		field_p[x][y] = field[x][y];
		return true;

	}
	dfs(x, y);

}
bool is_win() {
	int opened = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (field_p[i][j] >= 0) opened++;
		}
	}
	return(N * M - K == opened);
}

void end_game(bool is_win = false) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (field_p[i][j] == -1)field_p[i][j] = -2;
			if (field[i][j] == -1)field_p[i][j] = -3;
		}
	}

	print_field();
	cout << "Ты"<<' ' << (is_win ? "Выиграл!Повезло Разочек" : "Проиграл! Лох-Это Судьба") << " .Если хочешь еще раз сыграть  , то  Введи любю строку\n";
	string s;
	cin >> s;
}

int main() {
	
	
		setlocale(LC_ALL, "rus");

		
		while (true) {

			
			/*
			План Работы:
			1) Генерация Поля
			2) Вывод поля на экран
			3)Ввод команды
			4)Открытие клеток
			5)Завершение Игры

			*/
			


			srand(time(0));

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					field[i][j] = 0;
					field_p[i][j] = -2;
				}
			}
			for (int i = 0; i < K; ++i) {
				while (true) {
					int x = rand() % N;
					int y = rand() % M;
					if (field[x][y] != -1) {
						field[x][y] = -1;
						break;
					}
				}
			}
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					if (field[i][j] != -1) {
						field[i][j] = 0;


						for (int i2 = i - 1; i2 <= i + 1; ++i2) {

							for (int j2 = j - 1; j2 <= j + 1; ++j2) {
								if (i2 >= 0 && i2 < N && j2 >= 0 && j2 <= M &&
									field[i2][j2] == -1) ++field[i][j];
							}
						}
					}
				}
			}
			while (true) {
				print_field();
				cout << "Ходи Лошара ....\n";
				cout << endl;
				/*
				1o x y-Открыть Клетку
				1f x y-Поставить Флаг
				1n-Новая Игра
				1q-Завершить Игру
				*/
				string comand;
				cin >> comand;
				if (comand == "1o") {
					//Ввод Координат
					int x, y;
					cin >> x >> y;
					--x; --y;
					//Откроем Клетки
					if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] >= 0)continue;
					if (!open_cell(x, y)) {
						end_game();
						break;

						
						

					}
					if (is_win()) {
						end_game(true);
						break;

					}
				}
				else if (comand == "1f") {
					//Ввод Координат
					int x, y;
					cin >> x >> y;
					--x; --y;
					if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] >= 0)continue;
					//Постaвим Флаг
					if (field_p[x][y] == -1)field_p[x][y] = -2;
					else field_p[x][y] = -1;



				}

				else if (comand == "1n") {
					break;
				}
				else if (comand == "1q") {
					return 0;
				}
			}
		}




	
}












