#include <iostream>
#include <xhash>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

using std::cin;
using std::ofstream;
using std::cout;
using std::endl;
using std::sort;
using std::map;
using std::ios;
using std::fstream;
using std::ostream;
using std::istream;
using std::string;
using std::vector;
using std::pair;
using std::strncpy;

using namespace stdext;

class menu {
protected:
	virtual void Menu()abstract;
};

void InputInt(int& A) {
	while (!(cin >> A)) {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Повторите ввод\n";
	}
	cin.ignore(32767, '\n');
}

class user {
	int hash = 0;   // пароль в виде хеша
	string password = ""; // пароль
	string username = ""; // имя
	bool permission = 0; // права доступа (1 - администратор)
public:

	const string& GetName() {
		return username;
	}
	void setUsername(const string& _name) {
		username = _name;
	}
	void setPassword(const string& _password) {
		password = _password;
		hash = hash_value(password);
	}
	void setPermission(const bool& _permission) {
		permission = _permission;
	}
	bool getPermission() {
		return permission;
	}
	friend ostream& operator <<(ostream& s, user& U) {
		char Un[40];
		strcpy_s(Un, U.username.c_str());
		s.write(Un, sizeof(Un));
		s.write((char*)&U.hash, sizeof((char*)&U.hash));
		s.write((char*)&U.permission, sizeof((char*)&U.permission));
		return s;
	}
	friend istream& operator >>(istream& s, user& U) {
		char Un[40];
		U.username = "";
		U.password = "";
		s.read(Un, sizeof(Un));
		U.username = Un;
		s.read((char*)&U.hash, sizeof((char*)&U.hash));
		s.read((char*)&U.permission, sizeof((char*)&U.permission));
		return s;
	}
	bool compare(const user& obj) {
		if (obj.username == this->username && obj.hash == this->hash) return 1;
		return 0;
	}
	bool compareName(const user& obj) {
		if (strcmp(obj.username.c_str(), this->username.c_str()) == 0)return 1;
		return 0;
	}
	bool compareName(const string& obj) {
		if (strcmp(obj.c_str(), this->username.c_str()) == 0)return 1;
		return 0;
	}
	void SetUser() {
		cout << "Введите имя пользователя:  ";
		string Username;
		getline(cin, Username);
		setUsername(Username);
		cout << "Введите пароль:  ";
		string Password;
		getline(cin, Password);
		setPassword(Password);
		setPermission(0);
	}
	void SetAdmin() {
		cout << "Введите имя администратора:  ";
		string Username;
		getline(cin, Username);
		setUsername(Username);
		cout << "Введите пароль:  ";
		string Password;
		getline(cin, Password);
		setPassword(Password);
		setPermission(1);
	}
};

class employee {
	string employeeName = "";		// имя рабочего
	int salary = 0;					// зп
	string position = "";			// должность

	string merit = "";				// заслуги
	int sIncreasePerc = 0;			// прибавка в %
	int sIncreaseNum = 0;			// прибавка в рублях
	int taxDecreaseNum = 0;			// налоговый вычет в рублях
	string taxDecreaseReason = "";	// причина налогового вычета

	bool connectedToAcc = false;	// связан ли с акком
	string username = "";			// имя аккаунта

public:
	const string& getName() {
		return employeeName;
	}
	const string& getUName() {
		return username;
	}
	void outputAll() {
		cout << "Имя рабочего:  " << employeeName << endl;
		cout << "Базовая заработная плата рабочего:  " << salary << endl;
		cout << "Должность рабочего:  " << position << endl;

		if (sIncreaseNum == 0 && sIncreasePerc != 0) {
			cout << "Рабочий имеет следующие заслуги:  " << merit << " , его заработная плата была увеличена на " << sIncreasePerc << "%." << endl;
		}
		else
			if (sIncreaseNum != 0 && sIncreasePerc == 0) {
				cout << "Рабочий имеет следующие заслуги:  " << merit << " , его заработная плата была увеличена на " << sIncreasePerc << " руб." << endl;
			}
			else
				if (sIncreaseNum != 0 && sIncreasePerc != 0) {
					cout << "Рабочий имеет следующие заслуги:  " << merit << " , его заработная плата была увеличена на " << sIncreasePerc << "% и " << sIncreasePerc << " руб." << endl;
				}
				else {
					cout << "Рабочий не имеет особых заслуг.\n";
				}
		if (taxDecreaseNum != 0) {
			cout << "Налоговый вычет рабочего составляет:  " << taxDecreaseNum << " руб. и был получен по причине:   " << taxDecreaseReason << endl;
		}

		double sal = salary * (1 + 0.01 * sIncreasePerc) + sIncreaseNum;
		double taxes = sal * 0.13 - taxDecreaseNum;
		if (taxes < 0)taxes = 0;

		cout << "Заработная плата рабочего составит:  " << sal << " руб." << endl;
		cout << "Из них налогов:  " << taxes << " руб." << endl;

		if (connectedToAcc) {
			cout << "Запись связана с аккаунтом в системе.\nИмя пользвателя:  " << username << endl;
		}
		else {
			cout << "Запись не связана с аккаунтом в системе." << endl;
		}
	}
	void inputSMTH() {
		bool cycle = true;
		while (cycle) {
			system("cls");
			cout << "Выбирите поле записи, которое вы хотите изменить:\n";
			cout << "1 - Имя рабочего\n";
			cout << "2 - Заработную плату в рублях\n";
			cout << "3 - Должность рабочего\n";

			cout << "4 - Прибавку к зарплате\n";
			cout << "5 - Налоговый вычет\n";

			cout << "6 - Изменить привязанный к рабочему аккаунт в системе\n";
			cout << "0 - Выйти в меню редактирования\n";
			int choice;
			InputInt(choice);
			switch (choice) {
			case 1: {
				cout << "Введите новое имя рабочего:  ";
				getline(cin, employeeName);
				cout << "Имя рабочего редактировано!\n";
				system("pause");
				break;
			}
			case 2: {
				cout << "Введите новую заработную плату рабочего:  ";
				InputInt(salary);
				cout << "Заработная плата рабочего редактирована!\n";
				system("pause");
				break;
			}
			case 3: {
				cout << "Введите новую должность рабочего:  ";
				getline(cin, employeeName);
				cout << "Должность рабочего редактирована!\n";
				system("pause");
				break;
			}
			case 4: {
				cout << "Введите новую прибавку к зарплате в процентах:  ";
				InputInt(sIncreasePerc);
				cout << "Введите новую прибавку к зарплате в рублях:  ";
				InputInt(sIncreaseNum);
				if (sIncreasePerc || sIncreaseNum) {
					cout << "Введите новую причину для прибавки к зарплате:  ";
					getline(cin, employeeName);
				}
				cout << "Прибавка к зарплате рабочего редактирована!\n";
				break;
			}
			case 5: {
				cout << "Введите новый налоговый вычет в рублях:  ";
				InputInt(taxDecreaseNum);
				if (taxDecreaseNum) {
					cout << "Введите новую причину налогового вычета:  ";
					getline(cin, taxDecreaseReason);
				}
				cout << "Налоговый вычет редактирован!!\n";
				system("pause");
				break;
			}
			case 6: {
				bool red = true;
				char ch = 'o';
				while (ch != '0' && ch != '1') {
					cout << "Вы хотите привязать запись рабочего к аккаунту в системе? (1/0)\n";
					cin >> ch;
					cin.clear();
					cin.ignore(32000, '\n');
				}
				if (ch == '0')
				{
					if(connectedToAcc==1)
					cout << "Запись более не связана с аккаунтом в системе!\n";
					system("pause");
					red = false;
					connectedToAcc = 0;
					username = "";
				}
				while (red) {
					cout << "Введите логин для привязки к аккаунту:  ";
					getline(cin, username);
					fstream file;
					file.open("users.dat", ios::in | ios::out | ios::binary);
					file.seekp(0);
					file.seekg(0);
					while (!file.eof()) {
						user CompUser;
						file >> CompUser;
						if (CompUser.compareName(username)) {
							red = false;
							connectedToAcc = 1;
							break;
							cout << "Запись успешно связана с аккаунтом!\n";
							system("pause");
						}
					}
					if (file.eof() && red == true) {
						char y = 'q';
						while (y != 'y' && y != 'n') {
							cout << "Аккаунт не найден. Повторить ввод? (y/n)\n";
							cin >> y;
							cin.clear();
							cin.ignore(32000, '\n');
						}
						if (y == 'n') {
							if (connectedToAcc == 1)
							cout << "Запись более не связана с аккаунтом в системе!\n";
							red = false;
							connectedToAcc = 0;
							username = "";
						}
					}
					file.close();
				}
				break;
			}
			case 0: {
				cycle = false;
				break;
			}
			default: {
				cout << "Вы ввели неверное значение.\n";
			}
				   char y = 'q';
				   while (y != 'y' && y != 'n') {
					   cout << "Хотите продолжить ввод? (y/n)\n";
					   cin >> y;
					   cin.clear();
					   cin.ignore(32000, '\n');
				   }
				   if (y == 'n') {
					   cycle = false;
				   }
			}
		}
	}
	void inputAll() {
		cout << "Введите имя рабочего:  ";
		getline(cin, employeeName);
		cout << "Введите заработную плату рабочего:  ";
		InputInt(salary);
		cout << "Введите должность рабочего:  ";
		getline(cin, position);

		cout << "Введите прибавку к зарплате в процентах:  ";
		InputInt(sIncreasePerc);
		cout << "Введите прибавку к зарплате в рублях:  ";
		InputInt(sIncreaseNum);
		if (sIncreasePerc || sIncreaseNum) {
			cout << "Введите причину для прибавки к зарплате:  ";
			getline(cin, merit);
		}
		cout << "Введите налоговый вычет в рублях:  ";
		InputInt(taxDecreaseNum);
		if (taxDecreaseNum) {
			cout << "Введите причину налогового вычета:  ";
			getline(cin, taxDecreaseReason);
		}

		int choice = 2;
		while (choice != 0 && choice != 1) {
			cout << "Связать рабочего с каким-либо аккаунтом в системе? Введите 1/0:  ";
			InputInt(choice);
		}

		if (choice) {
			bool cycle = true;
			while (cycle) {
				cout << "Введите логин для привязки к аккаунту:  ";
				getline(cin, username);
				fstream file;
				file.open("users.dat", ios::in | ios::out | ios::binary);
				file.seekp(0);
				file.seekg(0);
				while (!file.eof()) {
					user CompUser;
					file >> CompUser;
					if (CompUser.compareName(username)) {
						cycle = false;
						connectedToAcc = 1;
						break;
					}
				}
				if (file.eof() && cycle == true) {
					char y = 'q';
					while (y != 'y' && y != 'n') {
						cout << "Аккаунт не найден. Повторить ввод? (y/n)\n";
						cin >> y;
						cin.clear();
						cin.ignore(32000, '\n');
					}
					if (y == 'n') {
						cycle = false;
						connectedToAcc = 0;
						username = "";
					}
				}
				file.close();
			}
		}
	}

	friend ostream& operator <<(ostream& s, employee& U) {
		char Buf[40];
		strcpy_s(Buf, U.employeeName.c_str());
		s.write(Buf, sizeof(Buf));
		s.write((char*)&U.salary, sizeof((char*)&U.salary));
		strcpy_s(Buf, U.position.c_str());
		s.write(Buf, sizeof(Buf));

		strcpy_s(Buf, U.merit.c_str());
		s.write(Buf, sizeof(Buf));
		s.write((char*)&U.sIncreasePerc, sizeof((char*)&U.sIncreasePerc));
		s.write((char*)&U.sIncreaseNum, sizeof((char*)&U.sIncreaseNum));
		s.write((char*)&U.taxDecreaseNum, sizeof((char*)&U.taxDecreaseNum));
		strcpy_s(Buf, U.taxDecreaseReason.c_str());
		s.write(Buf, sizeof(Buf));

		s.write((char*)&U.connectedToAcc, sizeof((char*)&U.connectedToAcc));
		strcpy_s(Buf, U.username.c_str());
		s.write(Buf, sizeof(Buf));

		return s;
	}
	friend istream& operator >>(istream& s, employee& U) {
		char Buf[40];
		U.employeeName = "";
		s.read(Buf, sizeof(Buf));
		U.employeeName = Buf;
		s.read((char*)&U.salary, sizeof((char*)&U.salary));
		U.position = "";
		s.read(Buf, sizeof(Buf));
		U.position = Buf;

		U.merit = "";
		s.read(Buf, sizeof(Buf));
		U.merit = Buf;
		s.read((char*)&U.sIncreasePerc, sizeof((char*)&U.sIncreasePerc));
		s.read((char*)&U.sIncreaseNum, sizeof((char*)&U.sIncreaseNum));
		s.read((char*)&U.taxDecreaseNum, sizeof((char*)&U.taxDecreaseNum));
		U.taxDecreaseReason = "";
		s.read(Buf, sizeof(Buf));
		U.taxDecreaseReason = Buf;

		s.read((char*)&U.connectedToAcc, sizeof((char*)&U.connectedToAcc));
		U.username = "";
		s.read(Buf, sizeof(Buf));
		U.username = Buf;
		return s;
	}
	bool compareName(const string& obj) {
		if (strcmp(obj.c_str(), this->username.c_str()) == 0)return 1;
		return 0;
	}
	friend bool compareNames(employee a, employee b);
	friend bool compareSalary(employee a, employee b);
	friend bool comparePosition(employee a, employee b);
	friend bool compareTax(employee a, employee b);
	friend bool compareIncPerc(employee a, employee b);
	friend bool compareIncNum(employee a, employee b);
	friend bool acompareNames(employee a, employee b);
	friend bool acompareSalary(employee a, employee b);
	friend bool acomparePosition(employee a, employee b);
	friend bool acompareTax(employee a, employee b);
	friend bool acompareIncPerc(employee a, employee b);
	friend bool acompareIncNum(employee a, employee b);
};

bool compareNames(employee a, employee b) { return (a.employeeName < b.employeeName); }
bool compareSalary(employee a, employee b) { return (a.salary < b.salary); }
bool comparePosition(employee a, employee b) { return (a.position < b.position); }
bool compareTax(employee a, employee b) { return (a.taxDecreaseNum < b.taxDecreaseNum); }
bool compareIncPerc(employee a, employee b) { return (a.sIncreasePerc < b.sIncreasePerc); }
bool compareIncNum(employee a, employee b) { return (a.sIncreaseNum < b.sIncreaseNum); }

bool acompareNames(employee a, employee b) { return (a.employeeName < b.employeeName); }
bool acompareSalary(employee a, employee b) { return (a.salary < b.salary); }
bool acomparePosition(employee a, employee b) { return (a.position < b.position); }
bool acompareTax(employee a, employee b) { return (a.taxDecreaseNum < b.taxDecreaseNum); }
bool acompareIncPerc(employee a, employee b) { return (a.sIncreasePerc < b.sIncreasePerc); }
bool acompareIncNum(employee a, employee b) { return (a.sIncreaseNum < b.sIncreaseNum); }

class empMenu : public menu {
	string name = "";
	bool permission = 0;
	vector<employee> Vec;
public:
	void ShowInfoByName(const string& namee) {
		getFromFile();
		system("cls");
		if (Vec.size() == 0)cout << "В системе пока что нет рабочих.\n";
		else {
			bool found = false;
			for (int i = 0; i < (int)Vec.size(); i++) {
				if (!strcmp(namee.c_str(), Vec[i].getUName().c_str())) {
					cout << "Информация о рабочем номер " << i + 1 << ":\n";
					Vec[i].outputAll();
					found = true;
				}
			}
			if (!found) {
				cout << "Запись рабочего, привязанная к вашему аккаунту, отсутствует в базе.\n";
			}
		}
		system("pause");
	};

	void setName(const string& namee) { name = namee; };
	void getInFile() {
		fstream file;
		file.open("employees.dat", ios::in | ios::trunc | ios::out | ios::binary);

		for (int i = 0; i < (int)Vec.size(); i++)file << Vec[i];
		cout << "Все записи рабочих успешно сохранены в файле.\n";
	}
	void getFromFile() {
		ofstream a("employees.dat", ios::app);
		a.close();

		Vec.clear();

		fstream file;
		file.open("employees.dat", ios::in | ios::out | ios::binary);
		employee buffer;
		while (true) {
			file >> buffer;
			if (file.eof())break;
			Vec.push_back(buffer);
		}
		cout << "Все записи рабочих успешно загружены из файла.\n";
	}

	void Menu() {
		getFromFile();
		bool cycle = true;
		while (cycle) {
			system("pause");
			system("cls");

			cout << "Главное меню\n";
			cout << "Меню администратора " << name << ":\n";
			cout << "1 - Просмотреть записи рабочих\n";
			cout << "2 - Изменить записи рабочих\n";
			cout << "0 - Выйти в меню входа в аккаунт\n";

			int choice;
			InputInt(choice);
			switch (choice) {
			case 1: {
				menu2();
				break;
			}
			case 2: {
				menu3();
				break;
			}
			case 0: {
				getInFile();
				cycle = false;
				break;
			}
			default: {
				cout << "Неверный ввод!\n";
			}
			}
		}
	}

	void seeAllInfo() {
		system("cls");
		if (Vec.size() == 0)cout << "В системе пока что нет рабочих.\n";
		else {
			cout << "Информация о рабочих:\n\n";
			for (int i = 0; i < (int)Vec.size(); i++) {
				cout << "Информация о рабочем номер " << i + 1 << ":\n";
				Vec[i].outputAll();
			}
		}
	}
	void seeAllNames() {
		system("cls");
		if (Vec.size() == 0)cout << "В системе пока что нет рабочих.\n";
		else {
			cout << "Имена рабочих:\n\n";
			for (int i = 0; i < (int)Vec.size(); i++) {
				cout << i + 1 << " - " << Vec[i].getName() << endl;
			}
		}
	}
	void seeByName() {
		system("cls");
		if (Vec.size() == 0)cout << "В системе пока что нет рабочих.\n";
		else {
			string Namee;
			cout << "Введите имя рабочего для поиска:  ";
			getline(cin, Namee);
			bool found = false;
			for (int i = 0; i < (int)Vec.size(); i++) {
				if (!strcmp(Namee.c_str(), Vec[i].getName().c_str())) {
					cout << "Информация о рабочем номер " << i + 1 << ":\n";
					Vec[i].outputAll();
					found = true;
				}
			}
			if (!found) {
				cout << "Запись о рабочем с таким именем отсутствует в базе.\n";
			}
		}
	};
	void sortMenu() {
		int sorT = 0;
		int UP = 0;
		while (sorT > 6 || sorT < 1) {
			system("cls");
			cout << "Выбирите тип сортировки:\n";
			cout << "1 - Сортировка по имени рабочего.\n";
			cout << "2 - Сортировка по имени рабочего.\n";
			cout << "3 - Сортировка по имени рабочего.\n";
			cout << "4 - Сортировка по имени рабочего.\n";
			cout << "5 - Сортировка по имени рабочего.\n";
			cout << "6 - Сортировка по имени рабочего.\n";
			InputInt(sorT);
		}
		while (UP != 1 && UP != 2) {
			system("cls");
			cout << "1 - сортировать по возрастанию\n";
			cout << "2 - сортировать по убыванию\n";
			InputInt(UP);
		}
		switch (sorT) {
		case 1: {
			if (UP == 1) { sort(Vec.begin(), Vec.end(), compareNames); }
			else
				if (UP == 2) { sort(Vec.begin(), Vec.end(), acompareNames); }
			cout << "Записи отсортированы.\n";
			break;
		}
		case 2: {
			if (UP == 1) { sort(Vec.begin(), Vec.end(), compareSalary); }
			else
				if (UP == 2) { sort(Vec.begin(), Vec.end(), acompareSalary); }
			cout << "Записи отсортированы.\n";
			break;
		}
		case 3: {
			if (UP == 1) { sort(Vec.begin(), Vec.end(), comparePosition); }
			else
				if (UP == 2) { sort(Vec.begin(), Vec.end(), acomparePosition); }
			cout << "Записи отсортированы.\n";
			break;
		}
		case 4: {
			if (UP == 1) { sort(Vec.begin(), Vec.end(), compareTax); }
			else
				if (UP == 2) { sort(Vec.begin(), Vec.end(), acompareTax); }
			cout << "Записи отсортированы.\n";
			break;
		}
		case 5: {
			if (UP == 1) { sort(Vec.begin(), Vec.end(), compareIncPerc); }
			else
				if (UP == 2) { sort(Vec.begin(), Vec.end(), acompareIncPerc); }
			cout << "Записи отсортированы.\n";
			break;
		}
		case 6: {
			if (UP == 1) { sort(Vec.begin(), Vec.end(), compareIncNum); }
			else
				if (UP == 2) { sort(Vec.begin(), Vec.end(), acompareIncNum); }
			cout << "Записи отсортированы.\n";
			break;
		}
		}
	}

	void menu2() {
		bool cycle = true;
		while (cycle) {
			system("pause");
			system("cls");

			cout << "Просмотр записей\n";
			cout << "Меню администратора " << name << ":\n";
			cout << "1 - Просмотреть все записи рабочих\n";
			cout << "2 - Просмотреть все имена рабочих\n";
			cout << "3 - Просмотреть запись рабочего по имени\n";
			cout << "4 - Сортировать записи рабочих\n";
			cout << "0 - Выйти в главное меню\n";

			int choice;
			InputInt(choice);
			switch (choice) {
			case 1: {
				seeAllInfo();
				break;
			}
			case 2: {
				seeAllNames();
				break;
			}
			case 3: {
				seeByName();
				break;
			}
			case 4: {
				sortMenu();
				break;
			}
			case 0: {
				cycle = false;
				break;
			}
			}
		}
	}

	void redactByNum() {
		int num = 0;
		while (num < 1 || num >(int)Vec.size()) {
			if (Vec.size() % 100 > 4 && Vec.size() % 100 <= 20) cout << "На данный момент в системе " << Vec.size() << " записей.\n"; else
				if (Vec.size() % 10 == 1)	cout << "На данный момент в системе " << Vec.size() << " запись.\n"; else
					if (Vec.size() % 10 < 5) cout << "На данный момент в системе " << Vec.size() << " записи.\n"; else
						cout << "На данный момент в системе " << Vec.size() << " записей.\n";
			cout << "Введите номер записи рабочего, которую вы хотите редактировать:  ";
			InputInt(num);
		}
		Vec[--num].inputSMTH();
	}
	void delByNum() {
		int num = 0;
		while (num < 1 || num >(int)Vec.size()) {
			if (Vec.size() % 100 > 4 && Vec.size() % 100 <= 20) cout << "На данный момент в системе " << Vec.size() << " записей.\n"; else
				if (Vec.size() % 10 == 1)	cout << "На данный момент в системе " << Vec.size() << " запись.\n"; else
					if (Vec.size() % 10 < 5) cout << "На данный момент в системе " << Vec.size() << " записи.\n"; else
						cout << "На данный момент в системе " << Vec.size() << " записей.\n";
			cout << "Введите номер записи рабочего, которую вы хотите удалить:  ";
			InputInt(num);
		}
		vector<employee>::iterator del = Vec.begin();
		del += --num;
		Vec.erase(del);
	}
	void addRab() {
		employee a;
		a.inputAll();
		Vec.push_back(a);
		cout << "Новая запись добавлена.\n";
	}

	void menu3() {
		bool cycle = true;
		while (cycle) {
			system("pause");
			system("cls");

			cout << "Изменение записей\n";
			cout << "Меню администратора " << name << ":\n";
			cout << "1 - Редактировать запись рабочего\n";
			cout << "2 - Удалить запись рабочего\n";
			cout << "3 - Сохранить внесенные изменения\n";
			cout << "4 - Откатить внесенные изменения\n";
			cout << "5 - Добавить запись рабочего\n";
			cout << "0 - Выйти в главное меню\n";

			int choice;
			InputInt(choice);
			switch (choice) {
			case 1: {
				redactByNum();
				break;
			}
			case 2: {
				delByNum();
				break;
			}
			case 3: {
				getInFile();
				break;
			}
			case 4: {
				getFromFile();
				break;
			}
			case 5: {
				addRab();
				break;
			}
			case 0: {
				cycle = false;
				break;
			}
			}
		}
	}
};

class systemLogin: public menu {
	user OurUser;
	bool Entered = 0;
public:
	void delUser() {
		fstream file;
		if (OurUser.getPermission() == 1) {
			user DelUser;
			user Buf;
			bool a = true;
			while (a) {
				cout << "Введите имя пользователя для удаления.\n";
				string name;
				getline(cin, name);
				DelUser.setUsername(name);
				a = OurUser.compareName(DelUser);
				if (a) cout << "Нельзя удалить активного пользователя!\n";
			}
			file.open("users.dat", ios::in | ios::out | ios::binary);
			ofstream file1;
			file.seekp(0);
			file1.open("temp.dat", ios::binary);
			bool deleted = false;
			while (!file.eof()) {
				file >> Buf;
				if (file.eof())break;
				if (Buf.compareName(DelUser))deleted = true;
				else {
					file1 << Buf;
				}
			}
			if (deleted)cout << "Пользователь удален.\n";
			else cout << "Нет такого пользователя\n";
			file.close();
			file1.close();
			remove("users.dat");
			try {
				int err = rename("temp.dat", "users.dat");
				if (err)throw 1;
			}
			catch (int) {
				cout << "Файл не переименован. Что-то пошло не так.\n";
				exit(1);
			}
			system("pause");
		}
		else {
			cout << "У вас нет прав на удаление пользователя. Войдите в аккант с правами администратора. \n";
			system("pause");
		}
	}
	void addUser() {
		fstream file;
		if (OurUser.getPermission()) {
			int ch;         // Выбор пункта меню
			bool cy = true; // Цикл ввода
			while (cy) {
				cout << "Введите 0 чтобы добавить простого пользователя\n        1 чтобы добавить администратора \n        2 чтобы выйти.\n";
				InputInt(ch);
				if (ch == 1) {
					file.open("users.dat", ios::in | ios::out | ios::binary);
					file.seekp(0);
					bool HasDatUser = false;
					user ne;
					user comp;
					ne.SetAdmin();
					while (file.eof()) {
						file >> comp;
						if (comp.compareName(ne) == 1)HasDatUser = true;
					}
					if (HasDatUser) {
						cout << "Пользователь с таким именем уже существует. \n";
					}
					else {
						file.seekg(0, ios::end);
						file << ne;
						cout << "Новый администратор добавлен.\n";
						cy = false;
					}
					file.close();
				}
				else if (ch == 0) {
					file.open("users.dat", ios::in | ios::out | ios::binary);
					file.seekp(0);
					bool HasDatUser = false;
					user ne;
					user comp;
					ne.SetUser();
					while (!file.eof()) {
						file >> comp;
						if (comp.compareName(ne) == 1)HasDatUser = true;
					}
					if (HasDatUser) {
						cout << "Пользователь с таким именем уже существует. \n";
					}
					else {
						file.close();
						file.open("users.dat", ios::app | ios::binary);
						file << ne;
						cout << "Новый пользователь добавлен.\n";
						cy = false;
					}
					file.close();
				}
				else if (ch == 2)
				{
					cy = false;
				}
				else
				{
					cout << "Неверный ввод. Повторите попытку.\n";
				}
			}
		}
		else {
			cout << "У вас нет прав на добавление пользователя. Войдите в аккант с правами администратора. \n";
		}
		system("pause");
	}
	void login() {
		fstream file;
		file.open("users.dat", ios::in | ios::out | ios::binary);
		file.seekg(0, ios::end);
		int size;
		size = (int)file.tellg();
		file.close();
		if (size == 0) {
			file.open("users.dat", ios::in | ios::out | ios::binary);
			cout << "В системе нет пользователей. Добавьте пользователя для начала работы:\n";
			OurUser.SetAdmin();
			file << OurUser;
			Entered = 1;
			file.close();
		}
		else {
			bool cycle = true;
			while (cycle) {
				file.open("users.dat", ios::in | ios::out | ios::binary);
				user Input;
				Input.SetUser();
				file.seekp(0);
				file.seekg(0);
				while (!file.eof()) {
					user CompUser;
					file >> CompUser;
					if (CompUser.compare(Input)) {
						cycle = false;
						OurUser.setPermission(CompUser.getPermission());
						cout << "Вход успешен!\n";
						OurUser.setUsername(Input.GetName());
						Entered = 1;
						break;
					}
				}
				if (file.eof() && cycle == true) {
					system("cls");
					while (true) {
						cout << "Аккаунт не найден. Повторить ввод?(y/n)\n";
						char y;
						cin >> y;
						cin.ignore(32767, '\n');
						if (y == 'y')break;
						if (y == 'n')
						{
							cycle = false; break;
						}
					}
				}
				file.close();
			}
		}
		system("pause");
	}
	void seeUsers() {
		fstream file;
		if (OurUser.getPermission() == 1) {
			user ShowUser;
			file.open("users.dat", ios::in | ios::out | ios::binary);
			file.seekp(0);
			int num = 1;
			while (!file.eof()) {
				file >> ShowUser;
				if (!file.eof()) cout << num++ << " - " << ShowUser.GetName() << " - " << ((ShowUser.getPermission()) ? ("Администратор") : ("Пользователь")) << endl;
			}
			file.close();
		}
		else {
			cout << "У вас нет прав на просмотр всех пользователей. Войдите в аккант с правами администратора. \n";
		}
		system("pause");
	}

	void Menu() {
		fstream file;
		ofstream a("users.dat", ios::app);
		a.close();
		while (!Entered) {
			login();
		}
		while (true) {
			int choice;
			system("cls");
			cout << "Вы вошли в систему как " << OurUser.GetName() << " - " << ((OurUser.getPermission()) ? ("Администратор") : ("Пользователь")) << " , выбирите пункт меню:\n";
			cout << "1 - Перезайти в систему\n";
			if (OurUser.getPermission()) {
				cout << "2 - Войти в меню расчета зарплаты\n";
				cout << "3 - Добавить пользователя\n";
				cout << "4 - Удалить пользователя\n";
				cout << "5 - Просмотреть имена всех пользователей\n";
			}
			else {
				cout << "2 - Войти в меню просмотра зарплаты\n";
			}
			cout << "0 - Выйти из программы\n";
			InputInt(choice);
			switch (choice) {
			case 1: {
				login();
				break;
			}
			case 2: {
				if (OurUser.getPermission()) {
					empMenu a;
					a.Menu();
				}
				else {
					empMenu a;
					a.ShowInfoByName(OurUser.GetName());
				}
				break;
			}
			case 3: {
				addUser();
				break;
			}
			case 4: {
				delUser();
				break;
			}
			case 5: {
				seeUsers();
				break;
			}
			case 0: {
				exit(0);
			}
			}
		}
	}
};

template <class T>
struct Status {
	T* ptr;
	int counter;
};

template <class T>
class SmartPointer {
	Status<T>* smartPtr;
public:
	SmartPointer(T* ptr = 0) {
		if (!ptr) smartPtr = NULL;
		else {
			smartPtr = new Status<T>;
			smartPtr->ptr = ptr;
			smartPtr->counter = 1;
		}
	}
	SmartPointer(const SmartPointer& obj):smartPtr(obj.smartPtr) {
		if (smartPtr) smartPtr->counter++;
	}
	~SmartPointer() {
		if (smartPtr) {
			smartPtr->counter--;
			if (smartPtr->counter <= 0) {
					delete smartPtr->ptr;
				delete smartPtr;
			}
		}
	}
	SmartPointer& operator=(const SmartPointer& obj) {
		if (smartPtr) {
			smartPtr->counter--;
				if (smartPtr->counter <= 0) {
					delete smartPtr->ptr;
					delete smartPtr;
				}
		}
		smartPtr = obj.smartPtr;
		if (smartPtr) smartPtr->counter++;
			return *this;
	}
	T* operator->() const {
		if (smartPtr) return smartPtr->ptr;
		else return NULL;
	}
	void showCounter() { cout << smartPtr->counter; }
}; 

int main()
{
	setlocale(LC_ALL, "RU");
	SmartPointer<systemLogin> a(new systemLogin);
	a->Menu();
}
