#include <iostream>
#include <string>
#include <locale>
#include <windows.h>
#include <cmath>
#include <random>

// струтура оружия чтобы потом наследоватся от нее и сделать новое
struct Weapon {
	int damage;
	int radius;

	Weapon(int dmg, int rad) : damage(dmg), radius(rad) {}

	virtual ~Weapon() = default;
};

// ножик 
struct Knife : public Weapon {
	Knife() : Weapon(5, 1){}
};

// cнайперская винтовка
struct Rifle : public Weapon {
	Rifle() : Weapon(20, 10) {}
};

// класс игрока
class Player {
	int x = 5, y = 5;
	int money = 100;
	int hp = 100;
	const Weapon* current_weapon;
public:
	Player(const Weapon& weapon) : current_weapon(&weapon) {};

// передвижение игрока
	void move(char vector) {
		switch (vector) {
		case 'w':
			y--;
			break;
		case 'a':
			x--;
			break;
		case 's':
			y++;
			break;
		case 'd':
			x++;
			break;
		}
	}

// геттер координат
	int coords(char axis) {
		switch (axis) {
		case 'x':
			return x;
		case 'y':
			return y;
		default:
			return 0;
		}
	}

//смена оружия
	void weapon_change(const Weapon& weapon) {
		current_weapon = &weapon;
	}

// геттер урона от оружия которое держит игрок
	int attack() {
		return current_weapon->damage;
	}
// геттер радиуса атаки оружия
	int radius() {
		return current_weapon->radius;
	}

// денежки
	void money_get(int get_money) {
		money += get_money;
	}
// геттер баланса кошелька
	int wallet() {
		return money;
	}
	
// урон
	void damage(int enemy_damage) {
		hp -= enemy_damage;
	}
};

// структура врага дворфа
struct Enemy
{
	int x, y;
	int hp = 10;
	int damage = 3;
	int radius = 1;
};

// класс доски. чето я тут намудрил
class Board
{
// обьявление классов в доске чтобы она могла с ними взаимодействовать
	Rifle rifle;
	Knife knife;
	Player player;
	Enemy dwarf;

// проверка хода
	void move_check(char direct) {
		float px = static_cast<float>(player.coords('x'));
		float py = static_cast<float>(player.coords('y'));
		float ex = static_cast<float>(dwarf.x);
		float ey = static_cast<float>(dwarf.y);
		float dx = ex - px, dy = ey - py;
		float distance = std::hypot(dx, dy);

		if (px > 10 || px < 0 || py > 10 || py < 0) {
			std::cout << "тут преграда\n";Sleep(500);
			switch (direct) {
			case 'w':
				player.move('s');
				py++;
				break;
			case 'a':
				player.move('d');
				px++;
				break;
			case 's':
				player.move('w');
				py--;
				break;
			case 'd':
				player.move('a');
				px--;
				break;
			}
		}
		if (distance <= 2.0) {
			if (distance == 0.0) {
			// главная фича игры
				std::cout << "вы задавили дворфа\n";Sleep(500);
				dwarf.hp = 0;
				dwarf.x = 100;
				dwarf.y = 100;
			}
			else {
				std::cout << "рядом есть дворф\n";Sleep(500);
			}
		}
		if (px == 1 && py == 1) {
			std::cout << "тут торговец\n";Sleep(500);
		}
		else if (px == 2 && py == 9) {
			std::cout << "тут что то есть\n";Sleep(500);
		}
	}

// битва
	void fight() {
		float px = static_cast<float>(player.coords('x'));
		float py = static_cast<float>(player.coords('y'));
		float ex = static_cast<float>(dwarf.x);
		float ey = static_cast<float>(dwarf.y);
		float dx = ex - px, dy = ey - py;
		float distance = std::hypot(dx, dy);

		if (distance <= player.radius()) {
			std::cout << "вы атакавали\n";Sleep(500);
			dwarf.hp -= player.attack();
			std::cout << "enemy hp = " << dwarf.hp << std::endl;
			if (dwarf.hp <= 0) {
				dwarf.x = 100;
				dwarf.y = 100;
				std::cout << "вы убили дворфа\n";Sleep(500);
				player.money_get(30);
			}
		}
		else {
			std::cout << "аааай не попал\n";Sleep(500);
		}
		if (distance <= dwarf.radius) {
			std::cout << "вас атаковали\n";Sleep(500);
			player.damage(dwarf.damage);
		}
	}

// таверна
	void shop() {
		do {
			std::string product;
			std::cout << "добро пожаловать в лавку 'золотая кружка'.\nчто вы хотите купить?\n";Sleep(500);
			std::cout << "rifle: 999999\n	дистанция:10\n	урон:20\nknife: 10\n	дистанция:1\n	урон:5\nhealth: 20\n	: ";Sleep(500);
			std::cin >> product;
			if (product == "rifle" && player.wallet() >= 999999) {
				player.weapon_change(rifle);
				std::cout << "ваше оружие заменено\n";Sleep(500);
				player.money_get(-999999);
			}
			else if (product == "knife" && player.wallet() >= 10) {
				player.weapon_change(knife);
				std::cout << "ваше оружие заменено\n";Sleep(500);
				player.money_get(-10);
			}
			else if (product == "health" && player.wallet() >= 20) {
				player.damage(-20);
				std::cout << "вы исцелены\n";Sleep(500);
				player.money_get(-20);
			}
			else if (product == "quit") {
				std::cout << "ждем вас снова\n";Sleep(500);
				return;
			}
			else {
				std::cout << "что, счет многоват?\n";Sleep(500);
			}
		} while (true);
	}
public:
// конструктор андрея/доски
	Board() : player(knife) {
		dwarf.x = 3;
		dwarf.y = 7;
	}

// главный цикл
	void main_loop() {
		std::cout << "дарова. меня андрей звать. я буду мастером твоей игры\nвы появились в поле\n";Sleep(500);
		do {
			std::string command;
			std::cout << "статистика: x = " << player.coords('x') << " y = " << player.coords('y') << " money = " << player.wallet() << std::endl;
			std::cout << "для хода напишите одну из этих команд\n	move: пойти в какую то из сторон\n	fight: битва\n	shop: купить что то у торговца\n	dig: копать\n	quit: выйти\n	ваш ход: ";Sleep(500);
			std::cin >> command;
			if (command == "move") {
				char direct;
				std::cout << "		w: вверх\n		a: влево\n		d: вправо\n		s: вниз\n		куда: ";Sleep(500);
				std::cin >> direct;
				player.move(direct);
				move_check(direct);
			}
			else if (command == "fight") {
				fight();
			}
			else if (command == "shop") {
				if (player.coords('x') == 1 && player.coords('y') == 1)
					shop();
				else {
					std::cout << "тут нет торговца\n";Sleep(500);
				}
			}
			else if (command == "dig") {
				if (player.coords('x') == 2 && player.coords('y') == 9) {
					std::cout << "вы нашли винтовку!\n";Sleep(500);
					player.weapon_change(rifle);
				}
				else {
					std::cout << "тут ниче нет\n";Sleep(500);
				}
			}
			else if (command == "quit") {
				std::cout << "ну и иди отсюда. я пойду тогда плакать в подушку в одиночестве. спасибо за игру\n";Sleep(500);
				return;
			}
		} while (true);
	} 
};

int main() {
	setlocale(LC_ALL, "Russian");
	Board board;
	board.main_loop();
	system("pause");
}