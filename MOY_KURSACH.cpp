#include <iostream>
#include <vector>
#include <xhash>
#include <string>
#include <algorithm>
#include <fstream>
#include <conio.h>

using namespace stdext;
namespace EverythingINeed {
	constexpr auto DescriptionSize = 100;
	constexpr auto AverageFileStringSize = 40;
	constexpr auto PasswordToCrushAProgram = 12345678;
	using std::cin;
	using std::ofstream;
	using std::cout;
	using std::endl;
	using std::sort;
	using std::ios;
	using std::fstream;
	using std::ostream;
	using std::istream;
	using std::string;
	using std::vector;
	using std::pair;
	using std::strncpy;
}

using namespace EverythingINeed;

class Inp { // статический класс для ввода
public:
	static void InputInt(int& A) {
		while (!(std::cin >> A)) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			

std::cout << "Повторите ввод\n";
		}
		std::cin.ignore(32767, '\n');
	}
	static void InputBool(bool& A) {
		while (!(std::cin >> A)) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Повторите ввод\n";
		}
		std::cin.ignore(32767, '\n');
	}
	static void InputIntDiapason(int& A, int min, int max) {
		bool pass = false;
		while (!pass) {
			while (!(std::cin >> A)) {
				std::cout << "Вы ввели неверные данные. Повторите ввод:  ";
				std::cin.clear();
				std::cin.ignore(32767, '\n');
			}
			std::cin.ignore(32767, '\n');
			if (A <= max && A >= min)pass = true;
			else std::cout << "Вы ввели число, выходящее за рамки диапазона " << min << "-" << max << ". Повторите ввод:  ";
		}
	}
	template <typename Type>
	static void InputNumberDiap(Type& A, Type min, Type max) {
		bool pass = false;
		while (!pass) {
			while (!(std::cin >> A)) {
				std::cout << "Вы ввели неверные данные. Повторите ввод:  ";
				std::cin.clear();
				std::cin.ignore(32767, '\n');
			}


			std::cin.ignore(32767, '\n');
			if (A <= max && A >= min)pass = true;
			else std::cout << "Вы ввели число, выходящее за рамки диапазона " << min << "-" << max << ". Повторите ввод:  ";
		}
	}
	static string InputPassword() {
		string s{};
		char c{};
		int len = 0;
		while (true) {
			c = _getch();//принимает значение введенных с клавиатуры символов
			if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) { //только нужные символы
				len++;
				s += c;
				_putch('*'); // вывод *
			}
			if (c == '\b') { // если backspace
				if (len > 0) {
					len--;
					cout << "\b \b";
					s.erase(s.length() - 1);
				}
			}
			if (c == '\r') { // если enter
				cout << endl;
				if (s.length() < 6) {
					system("cls");
					cout << "В пароле должно быть не меньше 6 символов\n" << endl;
					cout << "Введите пароль еще раз: ";
				}
				else break;


}
		}
		return s;
	}
};

class SimpleMutex {
	static bool isRunning;
public: 
	static void check()
	{
		if (SimpleMutex::isRunning) {
			cout << "Программа была экстренно выключена при прошлом использовании или другой экземпляр программы уже запущен.\n";
			cout << "Продолжение работы может повлечь за собой конфликты данных или иные ПЕЧАЛЬНЫЕ последствия.\n";
			cout << "Введите пароль чтобы продолжить:  ";
			int password;
			Inp::InputInt(password);
			if (password != PasswordToCrushAProgram) exit(123);
			else { cout << "Ok.\n"; system("pause"); system("cls"); }
		}
		else {
			fstream Mutex2("Mutex.info", ios::binary | ios::out | ios::in | ios::trunc);
			SimpleMutex::isRunning = true;
			Mutex2 << SimpleMutex::isRunning;
			Mutex2.close();
		}
	}
	static void Catch() {
		fstream Mutex("Mutex.info", ios::binary | ios::out | ios::in);
		if (!Mutex)
		{
			fstream Mutex2("Mutex.info", ios::binary | ios::out | ios::in | ios::trunc);


			SimpleMutex::isRunning = true;
			Mutex2 << SimpleMutex::isRunning;
			Mutex2.close();
			return;
		}
		Mutex >> SimpleMutex::isRunning;
		check();
	}
	static void Release() {
		fstream Mutex2("Mutex.info", ios::binary | ios::out | ios::in | ios::trunc);
		SimpleMutex::isRunning = false;
		Mutex2 << SimpleMutex::isRunning;
		Mutex2.close();
	}
};

bool SimpleMutex::isRunning = false;

class Item { // товар
protected:
	string TName;
	string TDescription;
public:
	virtual void inputAll() = 0;
	virtual void outputAll() = 0;
	virtual void redact() = 0;
};

class tariff:protected Item {
	int Price = 0;
	int AmountOfUsers = 0;
	int AmountOfMB = 0;
	int AmountOfMinutes = 0;
public:
	void inputAll()final {


		cout << "Введите имя тарифа:  ";
		getline(cin, TName);
		cout << "Введите описание тарифа:  ";
		getline(cin, TDescription);
		cout << "Введите количество мегабайтов интернета в тарифе:  ";
		Inp::InputIntDiapason(AmountOfMB, 0, 100000);
		cout << "Введите количество минут в тарифе:  ";
		Inp::InputIntDiapason(AmountOfMinutes, 0, 100000);
		cout << "Введите стоимость тарифа:  ";
		Inp::InputNumberDiap(Price, 1, 200);
		AmountOfUsers = 0;
	}
	void outputAll()final {
		cout << "\tИмя тарифа:  " << TName << endl;
		cout << "\tОписание тарифа:  " << TDescription << endl;
		cout << "\tКоличество мегабайтов интернета в тарифе:  " << AmountOfMB << endl;
		cout << "\tКоличество минут звонков в тарифе:  " << AmountOfMinutes << endl;
		cout << "\tСтоимость тарифа:  " << Price << " руб." << endl;
	}
	void redact()final {
		cout << "Которое из полей тарифа вы хотите редактировать?\n";
		cout << "\t1 - имя" << endl;
		cout << "\t2 - описание" << endl;
		cout << "\t3 - кол-во мегабайтов интернета" << endl;
		cout << "\t4 - кол-во минут звонков" << endl;
		cout << "\t5 - стоимость" << endl;
		cout << "\t6 - весь тариф" << endl;
		cout << "\t0 - отмена" << endl;
		int choice;
		Inp::InputIntDiapason(choice, 0, 6);
		switch (choice) {
		case 1: {


			cout << "Старое имя тарифа:  " << TName << endl;
			cout << "Введите новое имя тарифа:  ";
			getline(cin, TName);
			break;
		}
		case 2: {
			cout << "Старое описание тарифа:  " << TDescription << endl;
			cout << "Введите новое описание тарифа:  ";
			getline(cin, TDescription);
			break;
		}
		case 3: {
			cout << "Старое количество мегабайтов интернета в тарифе:  " << AmountOfMB << endl;
			cout << "Введите новое количество мегабайтов интернета в тарифе:  ";
			Inp::InputIntDiapason(AmountOfMB, 0, 100000);
			break;
		}
		case 4: {
			cout << "Старое количество минут звонков в тарифе:  " << AmountOfMinutes << endl;
			cout << "Введите новое количество минут звонков в тарифе:  ";
			Inp::InputIntDiapason(AmountOfMinutes, 0, 100000);
			break;
		}
		case 5: {
			cout << "Старая стоимость тарифа:  " << Price << " руб." << endl;
			cout << "Введите новую стоимость тарифа:  ";
			Inp::InputNumberDiap(Price, 1, 200);
			break;
		}
		case 6: {


			int users = this->AmountOfUsers;
			inputAll();
			this->AmountOfUsers = users;
			break;
		}
		case 0: {
			cout << "Ok.\n";
			return;
			break;
		}
		}
		cout << "Изменения внесены." << endl;
	}
	int getPrice(){
		return Price;
	}
	inline void upUsers() { AmountOfUsers++; }
	inline void downUsers() { AmountOfUsers--; }
	inline int getUsers() { return AmountOfUsers; }
	friend ostream& operator <<(ostream& s, tariff& U) {
		char desc[DescriptionSize];
		strcpy_s(desc, U.TDescription.c_str());
		s.write(desc, sizeof(desc));
		char naem[AverageFileStringSize];
		strcpy_s(naem, U.TName.c_str());
		s.write(naem, sizeof(naem));

		s.write((char*)&U.Price, sizeof((char*)&U.Price));
		s.write((char*)&U.AmountOfMB, sizeof((char*)&U.AmountOfMB));
		s.write((char*)&U.AmountOfMinutes, sizeof((char*)&U.AmountOfMinutes));
		s.write((char*)&U.AmountOfUsers, sizeof((char*)&U.AmountOfUsers));
		return s;
	}


	friend istream& operator >>(istream& s, tariff& U) {
		char desc[DescriptionSize];
		s.read(desc, sizeof(desc));
		U.TDescription = desc;
		char naem[AverageFileStringSize];
		s.read(naem, sizeof(naem));
		U.TName = naem;

		s.read((char*)&U.Price, sizeof((char*)&U.Price));
		s.read((char*)&U.AmountOfMB, sizeof((char*)&U.AmountOfMB));
		s.read((char*)&U.AmountOfMinutes, sizeof((char*)&U.AmountOfMinutes));
		s.read((char*)&U.AmountOfUsers, sizeof((char*)&U.AmountOfUsers));
		return s;
	}
};

class buyer {
	string Name = "";
	int Number = 0;
	int Money = 0;
	int tariffNum = 0;
public:
	void setName(const string& naem) { Name = naem; }
	void setNumber(const int& num) { Number = num; }
	void setMoney(const int& mon) { Money = mon; }
	void setTarif(const int& tar) { tariffNum = tar; }
	const string& getName() { return Name; }
	const int& getNumber() { return Number; }
	const int& getMoney() { return Money; }
	const int& getTariff() { return tariffNum; }
	void seeAll() {
		cout << "Имя пользователя:  " << Name << endl;
		cout << "Номер пользователя:  +375-00-" << Number << endl;


		cout << "Средства пользователя:  " << Money << endl;
	}
	friend ostream& operator <<(ostream& s, buyer& U) {
		char naem[AverageFileStringSize];
		strcpy_s(naem, U.Name.c_str());
		s.write(naem, sizeof(naem));

		s.write((char*)&U.Number, sizeof((char*)&U.Number));
		s.write((char*)&U.Money, sizeof((char*)&U.Money));
		s.write((char*)&U.tariffNum, sizeof((char*)&U.tariffNum));
		return s;
	}
	friend istream& operator >>(istream& s, buyer& U) {
		char naem[AverageFileStringSize];
		s.read(naem, sizeof(naem));
		U.Name = naem;

		s.read((char*)&U.Number, sizeof((char*)&U.Number));
		s.read((char*)&U.Money, sizeof((char*)&U.Money));
		s.read((char*)&U.tariffNum, sizeof((char*)&U.tariffNum));
		return s;
	}
	friend bool compareNames(const buyer a, const buyer b);
	friend bool compareNumber(buyer a, buyer b);
	friend bool compareMoney(buyer a, buyer b);
	friend bool AcompareNames(buyer a, buyer b);
	friend bool AcompareNumber(buyer a, buyer b);
	friend bool AcompareMoney(buyer a, buyer b);
};

bool compareNames(const buyer a, const buyer b) { return (a.Name < b.Name); }
bool compareNumber(buyer a, buyer b) { return (a.Number < b.Number); }
bool compareMoney(buyer a, buyer b) { return (a.Money < b.Money); }
bool AcompareNames(buyer a, buyer b) { return (a.Name > b.Name); }
bool AcompareNumber(buyer a, buyer b) { return (a.Number > b.Number); }


bool AcompareMoney(buyer a, buyer b) { return (a.Money > b.Money); }

class AbstractMenu {
protected:
	virtual void UserMenu(const string& Name) = 0;
	virtual void AdminMenu(const string& Name) = 0;
};

class CenterMenu:protected AbstractMenu {
	vector<tariff> Tarifs;
	vector<buyer> Buyers;
	int numOfBuyer = 0;
	static int Otobr; // отображение тарифов в информации о пользователях.
public:
	void BuyersInF() {
		fstream file("Buyers.info", ios::binary | ios::out | ios::in | ios::trunc);
		for (int i = 0; i < (int)Buyers.size(); i++) file << Buyers[i];
		file.close();
	}
	void BuyersFromF() {
		fstream file("Buyers.info", ios::binary | ios::out | ios::in);
		if (!file) {
			fstream file("Buyers.info", ios::binary | ios::out | ios::in | ios::trunc);
			return;
		}
		Buyers.clear();
		while (2 + 2 == 4) {
			buyer a;
			file >> a;
			if (file.eof())break;
			Buyers.push_back(a);
		}
		file.close();


	}
	void TarifsInF() {
		fstream file("Tarifs.info", ios::binary | ios::out | ios::in | ios::trunc);
		for (int i = 0; i < (int)Tarifs.size(); i++) file << Tarifs[i];
		file.close();
	}
	void TarifsFromF() {
		fstream file("Tarifs.info", ios::binary | ios::out | ios::in);
		if (!file) {
			fstream file("Tarifs.info", ios::binary | ios::out | ios::in | ios::trunc);
			return;
		}
		Tarifs.clear();
		while (2 + 2 == 4) {
			tariff a;
			file >> a;
			if (file.eof())break;
			Tarifs.push_back(a);
		}
		file.close();
	}
	void findUser(const string& Name) {
		bool isThere = false;
		for (int i = 0; i < (int)Buyers.size(); i++) {
			if (Buyers[i].getName() == Name) {
				isThere = true;
				numOfBuyer = i;
				break;
			}
		}
		if (isThere == true)return;
		else {
			buyer a;
			a.setName(Name);


			bool tel = true;
			int num;
			while (tel) {
				tel = false;
				cout << "Ваш аккаунт еще не зарегистрирован в системе.\n";
				cout << "Выберите номер телефона от (+375-00-)1000000 до (+375-00-)9999999:   ";
				Inp::InputIntDiapason(num, 1000000, 9999999);
				for (int i = 0; i < (int)Buyers.size(); i++) {
					if (Buyers[i].getNumber() == num)
					{
						tel = true;
						break;
					}
				}
				if (tel == true) {
					cout << "Номер уже занят.\n";
					system("pause");
					system("cls");
				}
			}
			a.setNumber(num);
			a.setMoney(100);
			a.setTarif(-1);
			Buyers.push_back(a);
			numOfBuyer = Buyers.size() - 1;
		}
	}
	void UserMenu (const string& Name) {
		BuyersFromF();
		TarifsFromF();
		findUser(Name);
		bool cycle = true;
		while (cycle) {
			system("pause");


			system("cls");
			cout << "Меню пользователя " << Buyers[numOfBuyer].getName() << endl;
			cout << "\t1 - Просмотреть свой тариф и номер" << endl;
			cout << "\t2 - Просмотреть все тарифы" << endl;
			cout << "\t3 - Изменить свой тариф" << endl;
			cout << "\t4 - Просмотреть свой баланс" << endl;
			cout << "\t5 - Изменить свой баланс" << endl;

			cout << "\t0 - Выйти в меню входа" << endl;
			int choice;
			Inp::InputIntDiapason(choice, 0, 5);
			switch (choice) {
			case 1: {
				cout << "Ваш номер:  +375-00-" << Buyers[numOfBuyer].getNumber() << endl;
				if (Buyers[numOfBuyer].getTariff() == -1) {
					cout << "У вас пока нет тарифа.\n";
					break;
				}
				cout << "Использующийся вами тариф:\n";
				Tarifs[Buyers[numOfBuyer].getTariff()].outputAll();
				break;
			}
			case 2: {
				if (Tarifs.size() == 0)
				{
					cout << "Тарифы отсутствуют в базе.\n";
					break;
				}
				system("cls");
				cout << "\n";
				for (int i = 0; i < (int)Tarifs.size(); i++) {
					cout << "Тариф номер " << i + 1 << ":\n\n";
					Tarifs[i].outputAll();


					cout << "\n";
					cout << "------------------------------------------\n";
					cout << "\n";
				}
				cout << "Конец списка.\n";
				break;
			}
			case 3: {
				if (Tarifs.size() == 0) {
					cout << "Тарифы отсутствуют в базе.\n";
					break;
				}
				cout << "Введите номер тарифа, который вы хотите подключить:  ";
				int tar;
				Inp::InputIntDiapason(tar, 1, Tarifs.size());
				tar--;
				if (Buyers[numOfBuyer].getTariff() != -1) {
					if (Buyers[numOfBuyer].getMoney() + Tarifs[Buyers[numOfBuyer].getTariff()].getPrice() < Tarifs[tar].getPrice()) {
						cout << "У вас недостаточно средств чтобы подключить этот тариф.\n";
						break;
					}
					Buyers[numOfBuyer].setMoney(Buyers[numOfBuyer].getMoney() + Tarifs[Buyers[numOfBuyer].getTariff()].getPrice());
					Tarifs[Buyers[numOfBuyer].getTariff()].downUsers();
				}
				else {
					if (Buyers[numOfBuyer].getMoney() < Tarifs[tar].getPrice()) {
						cout << "У вас недостаточно средств чтобы подключить этот тариф.\n";


						break;
					}
				}
				Buyers[numOfBuyer].setTarif(tar);
				Tarifs[tar].upUsers();
				Buyers[numOfBuyer].setMoney(Buyers[numOfBuyer].getMoney() - Tarifs[Buyers[numOfBuyer].getTariff()].getPrice());
				break;
			}
			case 4: {
				cout << "Ваши средства:  " << Buyers[numOfBuyer].getMoney()  << " руб.\n";
				break;
			}
			case 5: {
				cout << "На какую величину вы хотели бы пополнить свой баланс? Введите число от 1 до 10000:  ";
				int value;
				Inp::InputIntDiapason(value, 1, 10000);
				Buyers[numOfBuyer].setMoney(Buyers[numOfBuyer].getMoney() + value);
				cout << "Баланс пополнен.\n";
				break;
			}
			case 0: {
				cycle = false;
				break;
			}
			}
		}
		BuyersInF();
		TarifsInF();
		system("pause");
		system("cls");
	}


	void AdminMenu(const string& Name) {
		int Flag = 1;
		BuyersFromF();
		TarifsFromF();
		bool cycle = true;
		while (cycle) {
			system("pause");
			system("cls");
			cout << "Меню оператора " << Name << endl;
			cout << "\t1 - Просмотреть все тарифы" << endl;
			cout << "\t2 - Добавить тариф" << endl;
			cout << "\t3 - Редактировать тариф" << endl;
			cout << "\t4 - Удалить тариф" << endl;
			cout << "\t5 - Просмотреть пользователей" << endl;
			cout << "\t6 - Сортировать пользователей" << endl;
			cout << "\t7 - Просмотреть пользователя" << endl;
			cout << "\t8 - Сменить флаг вывода тарифов" << endl;
			cout << "\t0 - Выйти в меню входа" << endl;
			int choice;
			Inp::InputIntDiapason(choice, 0, 8);
			switch (choice) {
			case 1: {
				if (Tarifs.size() == 0)
				{
					cout << "Тарифы отсутствуют в базе.\n";
					break;
				}
				system("cls");
				for (int i = 0; i < (int)Tarifs.size(); i++) {
					cout << "Тариф номер " << i + 1 << ":\n";
					Tarifs[i].outputAll();
					cout << "\tПодключенные пользователи:  " << Tarifs[i].getUsers() << endl;
					cout << "\n";
					cout << "------------------------------------------\n";


					cout << "\n";
				}
				cout << "Конец списка.\n";
				break;
			}
			case 2: {
				tariff a;
				a.inputAll();
				Tarifs.push_back(a);
				break;
			}
			case 3: {
				if (Tarifs.size() == 0)
				{
					cout << "Тарифы отсутствуют в базе.\n";
					break;
				}
				cout << "Введите номер тарифа для редактирования от 1 до " << Tarifs.size() << ":  ";
				int red;
				Inp::InputIntDiapason(red, 1, Tarifs.size());
				Tarifs[--red].redact();
				break;
			}
			case 4: {
				if (Tarifs.size() == 0)
				{
					cout << "Тарифы отсутствуют в базе.\n";
					break;
				}
				cout << "Введите номер тарифа для удаления от 1 до " << Tarifs.size() << ":  ";
				int red;
				Inp::InputIntDiapason(red, 1, Tarifs.size());



				
				vector<tariff>::iterator del = Tarifs.begin();
				del += --red;
				if (del->getUsers() == 0) {
					Tarifs.erase(del);
				} else {
					cout << "Невозможно удалить тариф, к которому подключены пользователи.\n";
				}
				break;
			}
			case 5: {
				if (Buyers.size() == 0) {
					cout << "В системе нет пользователей.\n";
					break;
				}
				system("cls");
				for (int i = 0; i < (int)Buyers.size(); i++) {
					cout << "Информация о пользователе  " << i+1 << ":" << endl;
					Buyers[i].seeAll();
					cout << "Информация о тарифе:" << endl;
					if (Buyers[i].getTariff() != -1) {
						cout << "Номер тарифа:  " << Buyers[i].getTariff() + 1 << endl;
						if (Flag)Tarifs[Buyers[i].getTariff()].outputAll();
					}
					else {
						cout << "У пользователя нет тарифа.\n";
					}
					cout << "\n";
					cout << "------------------------------------------";
					cout << "\n";
				}


				break;
			}
			case 6: {
				if (Buyers.size() == 0) {
					cout << "В системе нет пользователей.\n";
					break;
				}
				cout << "Выберите способ сортировки:" << endl;
				cout << "\t1 - По имени\n";
				cout << "\t2 - По номеру\n";
				cout << "\t3 - По деньгам\n";
				int ch;
				Inp::InputIntDiapason(ch, 1, 3);
				cout << "Сортировать по возрастанию или по убыванию? Введите 1/0:  ";
				int ubivanie;
				Inp::InputIntDiapason(ubivanie, 0, 1);
				if (ubivanie == 1 && ch == 1) { sort(Buyers.begin(), Buyers.end(), compareNames); }
				if (ubivanie == 1 && ch == 2) { sort(Buyers.begin(), Buyers.end(), compareNumber); }
				if (ubivanie == 1 && ch == 3) { sort(Buyers.begin(), Buyers.end(), compareMoney); }
				if (ubivanie == 0 && ch == 1) { sort(Buyers.begin(), Buyers.end(), AcompareNames); }
				if (ubivanie == 0 && ch == 2) { sort(Buyers.begin(), Buyers.end(), AcompareNumber); }
				if (ubivanie == 0 && ch == 3) { sort(Buyers.begin(), Buyers.end(), AcompareMoney); }

				break;
			}
			case 7: {
				if (Buyers.size() == 0) {
					cout << "В системе нет пользователей.\n";
					break;


				}
				cout << "Введите номер пользователя для просмотра от 1 до " << Buyers.size() << ":  ";
				int num;
				Inp::InputIntDiapason(num, 1, Buyers.size());
				Buyers[--num].seeAll();
				cout << "Информация о тарифе:" << endl;
				if (Buyers[num].getTariff() == -1) {
					cout << "У пользователя нет тарифа.\n";
				}
				else {
					cout << "Номер тарифа:  " << Buyers[num].getTariff() + 1 << endl;
					if (Flag)Tarifs[Buyers[num].getTariff()].outputAll();
				}

				break;
			}
			case 8: {
				if (Flag == 1) {
					Flag = 0;
					cout << "Теперь информация о тарифе пользователя будет выводиться в сжатом виде.\n" << endl;
				}
				else {
					Flag = 1;
					cout << "Теперь информация о тарифе пользователя будет выводиться в полном виде.\n" << endl;
				}
				break;
			}
			case 0: {
				cycle = false;
				break;
			}


			}
		}
		BuyersInF();
		TarifsInF();
		system("pause");
		system("cls");
	}
};

class menu {
protected:
	virtual void Menu()abstract;
};

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
		setPassword(Inp::InputPassword());
		setPermission(0);
	}
	void SetAdmin() {
		cout << "Введите имя администратора:  ";
		string Username;
		getline(cin, Username);
		setUsername(Username);
		cout << "Введите пароль:  ";
		setPassword(Inp::InputPassword());
		setPermission(1);
	}
};

class systemLogin : public menu {
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
				Inp::InputInt(ch);
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
	bool login() {
		fstream file;
		file.open("users.dat", ios::in | ios::out | ios::binary | ios::app);
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
			fstream file5;
			ofstream a("users.dat", ios::app);
			a.close();

			cout << "Вы хотите создать новый аккаунт? Введите 1/0:  ";
			int choicee;
			Inp::InputIntDiapason(choicee, 0, 1);
			bool cyclee = true;
			if (choicee) {
				while (cyclee) {


					file5.open("users.dat", ios::in | ios::out | ios::binary);
					file5.seekp(0);
					bool HasDatUser = false;
					user ne;
					user comp;
					ne.SetUser();
					while (!file5.eof()) {
						file5 >> comp;
						if (comp.compareName(ne) == 1)HasDatUser = true;
					}
					if (HasDatUser) {
						cout << "Пользователь с таким именем уже существует. \n";
						cout << "Хотите попоробовать снова? Введите 1/0:  ";
						int choiceee;
						Inp::InputIntDiapason(choiceee, 0, 1);
						if (!choiceee)cyclee = false;
					}
					else {
						file5.close();
						file5.open("users.dat", ios::app | ios::binary);
						file5 << ne;
						cout << "Новый пользователь добавлен.\n";
						cout << "Переход в меню входа в аккаунт.\n";
						system("pause");
						system("cls");
						cyclee = false;
					}
					file5.close();
				}


			}
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
							return false;
						}


					}
				}
				file.close();
			}
		}
		system("pause");
		return true;
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
		while (!Entered) {
			if (!login())return;
		}
		bool cycle = true;
		while (cycle) {


			int choice;
			system("cls");
			cout << "Вы вошли в систему как " << OurUser.GetName() << " - " << ((OurUser.getPermission()) ? ("Администратор") : ("Пользователь")) << " , выберите пункт меню:\n";
			cout << "1 - Перезайти в систему\n";
			if (OurUser.getPermission()) {
				cout << "2 - Войти в меню оператора\n";
				cout << "3 - Добавить пользователя\n";
				cout << "4 - Удалить пользователя\n";
				cout << "5 - Просмотреть имена всех пользователей\n";
			}
			else {
				cout << "2 - Войти в меню выбора тарифов\n";
			}
			cout << "0 - Выйти из программы\n";
			Inp::InputInt(choice);
			switch (choice) {
			case 1: {
				login();
				break;
			}
			case 2: {
				if (OurUser.getPermission()) {
					CenterMenu a;
					a.AdminMenu(OurUser.GetName());
				}
				else {
					CenterMenu a;
					a.UserMenu(OurUser.GetName());
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
				cycle = false;
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


	SmartPointer(const SmartPointer& obj) :smartPtr(obj.smartPtr) {
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

int main(int argc, char* argv[])
{
	system("chcp 1251");
	system("cls");
	SimpleMutex::Catch();
    
	systemLogin a;
	a.Menu();

	SimpleMutex::Release();
}