#include <iostream>
#include <vector>
#include <xhash>
#include <string>
#include <algorithm>
#include <fstream>

using namespace stdext;
namespace EverythingINeed {
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

	#define MaxLengthCol 130 //макс длина колье
	#define MaxColWeigth 150 // макс вес колье
	#define MinLengthCol 20 // мин длина колье
	#define MaxLengthBrac 30 // макс длина браслета
	#define MinLengthBrac 10 // мин длина браслета
	#define MinSizeRing 10 // мин диаметр кольца
	#define MaxSizeRing 70 // макс диаметр кольца
	#define MaxGemstonesAmount 100 // макс кол-во камней
	#define GemT1price 250 // стоимость одного бриллианта
	#define GemT2price 150
	#define GemT3price 125
	#define GemT4price 100
	#define GemT5price 50
	#define GemT6price 25
	#define GemT7price 20
	#define GemT8price 15
	#define MatT1price 30 // стоимость грамма золота 585
	#define MatT2price 25
	#define MatT3price 15
	#define MatT4price 10
	#define MatT5price 4
	#define Romb 1.1 // множитель стоимости для разного плетения
	#define Lav 1.2
	#define Figaro 1.3
	#define Singapour 1.4
	#define Nails 1 // множитель стоимости для разных типов серьг
	#define Podveskas 1.2
	#define Koltsa 1.4
	#define ArtProcessed 1.5 // обработка колец
	#define AverageRingWeight 8 // вес кольца
	#define AverageEarringWeigth 20 // вес серьг
	#define AverageBracWeigth 40 // вес браслета
	#define MasterJobFee 100 // стоимость работы мастера
	#define StarterMoneyOfMaster 30000 // стартовые деньги мастера
	#define StarterMoneyOfUser 5000 // стартовые деньги нового пользователя
	#define MasterWorkFee 80 // стоимость работы мастера над одним заказом

	#define FileBufSize 50 // размер стринга в файле. при изменении нужно будет удалить файлы, которые были уже созданы. 
	#define LoginMenuPassword 12345678 // Пароль для удаления и просмотра пользователей
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
};

class jewelry { // ювелирное украшение
protected:
	int MaterialType = 0;
	bool IsThereGemstone = 0;
	int GemstoneType = 0;
	int GemstoneAmount = 0;
public:
    virtual void inputAll() = 0;
    virtual void outputAll() = 0;
    virtual void redact() = 0;
	virtual int getPrice() = 0;
	virtual void getInFile(ostream& s) = 0;
	virtual void getFromFile(istream& s) = 0;
	virtual int getWeigth() = 0;
	virtual int getMatType() = 0;
	virtual int getGemAmount() = 0;
	virtual int getGemType() = 0;
};

class necklace : public jewelry { // колье
	int weaving = 0;
	int length = 0;
public:
	void inputAll()final {
		cout << "Заполнение информации о колье.\n";
		cout << "Введите материал, из которого будет изготовлено колье.\n";
		cout << "\t1 - Золото 585-й пробы\n";
		cout << "\t2 - Золото 375-й пробы\n";
		cout << "\t3 - Серебро 925-й пробы\n";
		cout << "\t4 - Серебро 875-й пробы\n";
		cout << "\t5 - Медицинская сталь\n";
		Inp::Inp::InputIntDiapason(MaterialType, 1, 5);
		cout << "Будут ли присутствовать драгоценные или полудрагоценные камни в колье? Введите 1/0:  ";
		Inp::InputBool(IsThereGemstone);
		if (IsThereGemstone) {
			cout << "Введите камни, которые будут в колье.\n";
			cout << "Драгоценные:\n";
			cout << "\t1 - Алмаз\n";
			cout << "\t2 - Изумруд\n";
			cout << "\t3 - Рубин\n";
			cout << "\t4 - Жемчуг\n";
			cout << "Полудрагоценные:\n";
			cout << "\t5 - Топаз\n";
			cout << "\t6 - Кварц\n";
			cout << "\t7 - Янтарь\n";
			cout << "\t8 - Опал\n";
			Inp::InputIntDiapason(GemstoneType, 1, 8);
			cout << "Введите количество камней в колье. Максимальное количество - " << MaxGemstonesAmount << ":  ";
			Inp::InputIntDiapason(GemstoneAmount, 1, MaxGemstonesAmount);
		}
		cout << "Введите тип плетения в колье.\n";
		cout << "\t1 - Ромб\n";
		cout << "\t2 - Лав\n";
		cout << "\t3 - Фигаро\n";
		cout << "\t4 - Сингапур\n";
		Inp::InputIntDiapason(weaving, 1, 4);
		cout << "Введите длину колье в сантиметрах. Максимальная длина - " << MaxLengthCol << " сантиметров:  ";
		Inp::InputIntDiapason(length, MinLengthCol, MaxLengthCol);
	}
	void outputAll()final {
		cout << "Вывод информации о колье.\n";
		cout << "Материал колье: ";
		switch (MaterialType) {
		case 1: { cout << "Золото 585-й пробы\n"; break; }
		case 2: { cout << "Золото 375-й пробы\n"; break; }
		case 3: { cout << "Серебро 925-й пробы\n"; break; }
		case 4: { cout << "Серебро 875-й пробы\n"; break; }
		case 5: { cout << "Медицинская сталь\n"; break; }
		}
		cout << "Вес материала:  " << (double)MaxColWeigth * (double)length / MaxLengthCol << " гр.\n";
		if (IsThereGemstone) {
			cout << "В колье будут " << ((GemstoneType < 5) ? "драгоценные" : "полудрагоценные") << " камни.\n";
			cout << "Название камней: ";
			switch (MaterialType) {
			case 1: { cout << "Алмаз\n"; break; }
			case 2: { cout << "Изумруд\n"; break; }
			case 3: { cout << "Рубин\n"; break; }
			case 4: { cout << "Жемчуг\n"; break; }
			case 5: { cout << "Топаз\n"; break; }
			case 6: { cout << "Кварц\n"; break; }
			case 7: { cout << "Янтарь\n"; break; }
			case 8: { cout << "Опал\n"; break; }
			}
			cout << "Их количество:  " << GemstoneAmount << "\n";
		}
		else {
			cout << "В колье не будет другоценных или полудрагоценных камней.\n";
		}
		cout << "Тип плетения:  ";
		switch (weaving) {
		case 1: { cout << "Ромб\n"; break; }
		case 2: { cout << "Лав\n"; break; }
		case 3: { cout << "Фигаро\n"; break; }
		case 4: { cout << "Сингапур\n"; break; }
		}
		cout << "Длина колье:  " << length << " сантиметров.\n";
	}
	void redact()final {
		int choice = 0;
		bool cycle = true;
		while (cycle) {
			cout << "Меню редактирования информации о колье.\n";
			cout << "Которое из полей заказа вы хотите редактировать?\n";
			cout << "\t1 - Материал\n";
			cout << "\t2 - Камни\n";
			cout << "\t3 - Тип плетения\n";
			cout << "\t4 - Длина\n";
			cout << "\tВведите 0, чтобы выйти из меню редактирования:  ";
			Inp::InputIntDiapason(choice, 0, 4);
			switch (choice) {
			case 1: {
				cout << "Введите материал, из которого будет изготовлено колье.\n";
				cout << "\t1 - Золото 585-й пробы\n";
				cout << "\t2 - Золото 375-й пробы\n";
				cout << "\t3 - Серебро 925-й пробы\n";
				cout << "\t4 - Серебро 875-й пробы\n";
				cout << "\t5 - Медицинская сталь\n";
				Inp::InputIntDiapason(MaterialType, 1, 5);
				break;
			}
			case 2: {
				cout << "Будут ли присутствовать драгоценные или полудрагоценные камни в колье? Введите 1/0:  ";
				Inp::InputBool(IsThereGemstone);
				if (IsThereGemstone) {
					cout << "Введите камни, которые будут в колье.\n";
					cout << "Драгоценные:\n";
					cout << "\t1 - Алмаз\n";
					cout << "\t2 - Изумруд\n";
					cout << "\t3 - Рубин\n";
					cout << "\t4 - Жемчуг\n";
					cout << "Полудрагоценные:\n";
					cout << "\t5 - Топаз\n";
					cout << "\t6 - Кварц\n";
					cout << "\t7 - Янтарь\n";
					cout << "\t8 - Опал\n";
					Inp::InputIntDiapason(GemstoneType, 1, 8);
					cout << "Введите количество камней в колье. Максимальное количество - " << MaxGemstonesAmount << ":  ";
					Inp::InputIntDiapason(GemstoneAmount, 1, MaxGemstonesAmount);
				}
				break;
			}
			case 3: {
				cout << "Введите тип плетения в колье.\n";
				cout << "\t1 - Ромб\n";
				cout << "\t2 - Лав\n";
				cout << "\t3 - Фигаро\n";
				cout << "\t4 - Сингапур\n";
				Inp::InputIntDiapason(weaving, 1, 4);
				break;
			}
			case 4: {
				cout << "Введите длину колье в сантиметрах. Максимальная длина - " << MaxLengthCol << " сантиметров:  ";
				Inp::InputIntDiapason(length, MinLengthCol, MaxLengthCol);
				break;
			}
			case 0: {
				cycle = false;
			}
			}
		}
	}
	int getWeigth() {
		return MaxColWeigth * length / MaxLengthCol;
	}
	int getMatType() {
		return MaterialType;
	}
	int getGemAmount() {
		return GemstoneAmount;
	}
	int getGemType() {
		return GemstoneType;
	}
	int getPrice()final {
		int price = 0;
		if (MaterialType == 1)price +=  (int)(MatT1price * (double)MaxColWeigth * (double)length / MaxLengthCol);
		if (MaterialType == 2)price +=  (int)(MatT2price * (double)MaxColWeigth * (double)length / MaxLengthCol);
		if (MaterialType == 3)price +=  (int)(MatT3price * (double)MaxColWeigth * (double)length / MaxLengthCol);
		if (MaterialType == 4)price +=  (int)(MatT4price * (double)MaxColWeigth * (double)length / MaxLengthCol);
		if (MaterialType == 5)price +=  (int)(MatT5price * (double)MaxColWeigth * (double)length / MaxLengthCol);
		if (IsThereGemstone) {
			if (GemstoneType == 1)price += GemT1price * GemstoneAmount;
			if (GemstoneType == 2)price += GemT2price * GemstoneAmount;
			if (GemstoneType == 3)price += GemT3price * GemstoneAmount;
			if (GemstoneType == 4)price += GemT4price * GemstoneAmount;
			if (GemstoneType == 5)price += GemT5price * GemstoneAmount;
			if (GemstoneType == 6)price += GemT6price * GemstoneAmount;
			if (GemstoneType == 7)price += GemT7price * GemstoneAmount;
			if (GemstoneType == 8)price += GemT8price * GemstoneAmount;
		}
		if (weaving == 1)price *=  (int)Romb;
		if (weaving == 2)price *=  (int)Lav;
		if (weaving == 3)price *=  (int)Figaro;
		if (weaving == 4)price *=  (int)Singapour;
		return price + MasterWorkFee;
	}
	friend ostream& operator <<(ostream& s, necklace& U) {
		s.write((char*)&U.MaterialType, sizeof((char*)&U.MaterialType));
		s.write((char*)&U.IsThereGemstone, sizeof((char*)&U.IsThereGemstone));
		s.write((char*)&U.GemstoneType, sizeof((char*)&U.GemstoneType));
		s.write((char*)&U.GemstoneAmount, sizeof((char*)&U.GemstoneAmount));
		s.write((char*)&U.weaving, sizeof((char*)&U.weaving));
		s.write((char*)&U.length, sizeof((char*)&U.length));
		return s;
	}
	friend istream& operator >>(istream& s, necklace& U) {
		s.read((char*)&U.MaterialType, sizeof((char*)&U.MaterialType));
		s.read((char*)&U.IsThereGemstone, sizeof((char*)&U.IsThereGemstone));
		s.read((char*)&U.GemstoneType, sizeof((char*)&U.GemstoneType));
		s.read((char*)&U.GemstoneAmount, sizeof((char*)&U.GemstoneAmount));
		s.read((char*)&U.weaving, sizeof((char*)&U.weaving));
		s.read((char*)&U.length, sizeof((char*)&U.length));
		return s;
	}
	void getInFile(ostream& s)final {
		s << *this;
	}
	void getFromFile(istream& s)final {
		s >> *this;
	}
};

class bracelet : public jewelry { // браслет
	int weaving = 0;
	int length = 0;
	bool IsThereWeaving = 0;
public:
	void inputAll()final {
		cout << "Заполнение информации о браслете.\n";
		cout << "Введите материал, из которого будет изготовлен браслет.\n";
		cout << "\t1 - Золото 585-й пробы\n";
		cout << "\t2 - Золото 375-й пробы\n";
		cout << "\t3 - Серебро 925-й пробы\n";
		cout << "\t4 - Серебро 875-й пробы\n";
		cout << "\t5 - Медицинская сталь\n";
		Inp::InputIntDiapason(MaterialType, 1, 5);
		cout << "Будут ли присутствовать драгоценные или полудрагоценные камни в браслете? Введите 1/0:  ";
		Inp::InputBool(IsThereGemstone);
		if (IsThereGemstone) {
			cout << "Введите камни, которые будут в браслете.\n";
			cout << "Драгоценные:\n";
			cout << "\t1 - Алмаз\n";
			cout << "\t2 - Изумруд\n";
			cout << "\t3 - Рубин\n";
			cout << "\t4 - Жемчуг\n";
			cout << "Полудрагоценные:\n";
			cout << "\t5 - Топаз\n";
			cout << "\t6 - Кварц\n";
			cout << "\t7 - Янтарь\n";
			cout << "\t8 - Опал\n";
			Inp::InputIntDiapason(GemstoneType, 1, 8);
			cout << "Введите количество камней в браслете. Максимальное количество - " << MaxGemstonesAmount << ":  ";
			Inp::InputIntDiapason(GemstoneAmount, 1, MaxGemstonesAmount);
		}
		cout << "Будет ли присутствовать плетение в браслете или браслет будет цельным? Введите 1/0:  ";
		Inp::InputBool(IsThereWeaving);
		if (IsThereWeaving) {
			cout << "Введите тип плетения в браслете.\n";
			cout << "\t1 - Ромб\n";
			cout << "\t2 - Лав\n";
			cout << "\t3 - Фигаро\n";
			cout << "\t4 - Сингапур\n";
			Inp::InputIntDiapason(weaving, 1, 4);
		}
		cout << "Введите длину браслета в сантиметрах. Максимальная длина - " << MaxLengthBrac << " сантиметров:  ";
		Inp::InputIntDiapason(length, MinLengthBrac, MaxLengthBrac);
	}
	void outputAll()final {
		cout << "Вывод информации о браслете.\n";
		cout << "Материал браслета: ";
		switch (MaterialType) {
		case 1: { cout << "Золото 585-й пробы\n"; break; }
		case 2: { cout << "Золото 375-й пробы\n"; break; }
		case 3: { cout << "Серебро 925-й пробы\n"; break; }
		case 4: { cout << "Серебро 875-й пробы\n"; break; }
		case 5: { cout << "Медицинская сталь\n"; break; }
		}
		cout << "Вес материала:  " << (double)AverageBracWeigth * (double)length / MaxLengthBrac << " гр.\n";
		if (IsThereGemstone) {
			cout << "В браслете будут " << ((GemstoneType < 5) ? "драгоценные" : "полудрагоценные") << " камни.\n";
			cout << "Название камней: ";
			switch (MaterialType) {
			case 1: { cout << "Алмаз\n"; break; }
			case 2: { cout << "Изумруд\n"; break; }
			case 3: { cout << "Рубин\n"; break; }
			case 4: { cout << "Жемчуг\n"; break; }
			case 5: { cout << "Топаз\n"; break; }
			case 6: { cout << "Кварц\n"; break; }
			case 7: { cout << "Янтарь\n"; break; }
			case 8: { cout << "Опал\n"; break; }
			}
			cout << "Их количество:  " << GemstoneAmount << "\n";
		}
		else {
			cout << "В браслете не будет другоценных или полудрагоценных камней.\n";
		}
		if (IsThereWeaving) {
			cout << "Браслет не цельный.\n";
			cout << "Тип плетения:  ";
			switch (weaving) {
			case 1: { cout << "Ромб\n"; break; }
			case 2: { cout << "Лав\n"; break; }
			case 3: { cout << "Фигаро\n"; break; }
			case 4: { cout << "Сингапур\n"; break; }
			}
		}
		else {
			cout << "Браслет цельный. Плетения нет.\n";
		}
		cout << "Длина браслета:  " << length << " сантиметров.\n";
	}
	void redact()final {
		int choice = 0;
		bool cycle = true;
		while (cycle) {
			cout << "Меню редактирования информации о браслете.\n";
			cout << "Которое из полей заказа вы хотите редактировать?\n";
			cout << "\t1 - Материал\n";
			cout << "\t2 - Камни\n";
			cout << "\t3 - Тип плетения\n";
			cout << "\t4 - Длина\n";
			cout << "\tВведите 0, чтобы выйти из меню редактирования:  ";
			Inp::InputIntDiapason(choice, 0, 4);
			switch (choice) {
			case 1: {
				cout << "Введите материал, из которого будет изготовлен браслет.\n";
				cout << "\t1 - Золото 585-й пробы\n";
				cout << "\t2 - Золото 375-й пробы\n";
				cout << "\t3 - Серебро 925-й пробы\n";
				cout << "\t4 - Серебро 875-й пробы\n";
				cout << "\t5 - Медицинская сталь\n";
				Inp::InputIntDiapason(MaterialType, 1, 5);
				break;
			}
			case 2: {
				cout << "Будут ли присутствовать драгоценные или полудрагоценные камни в браслете? Введите 1/0:  ";
				Inp::InputBool(IsThereGemstone);
				if (IsThereGemstone) {
					cout << "Введите камни, которые будут в браслете.\n";
					cout << "Драгоценные:\n";
					cout << "\t1 - Алмаз\n";
					cout << "\t2 - Изумруд\n";
					cout << "\t3 - Рубин\n";
					cout << "\t4 - Жемчуг\n";
					cout << "Полудрагоценные:\n";
					cout << "\t5 - Топаз\n";
					cout << "\t6 - Кварц\n";
					cout << "\t7 - Янтарь\n";
					cout << "\t8 - Опал\n";
					Inp::InputIntDiapason(GemstoneType, 1, 8);
					cout << "Введите количество камней в браслете. Максимальное количество - " << MaxGemstonesAmount << ":  ";
					Inp::InputIntDiapason(GemstoneAmount, 1, MaxGemstonesAmount);
				}
				break;
			}
			case 3: {
				cout << "Будет ли присутствовать плетение в браслете? Введите 1/0:  ";
				Inp::InputBool(IsThereWeaving);
				if (IsThereWeaving) {
					cout << "Введите тип плетения в браслете.\n";
					cout << "\t1 - Ромб\n";
					cout << "\t2 - Лав\n";
					cout << "\t3 - Фигаро\n";
					cout << "\t4 - Сингапур\n";
					Inp::InputIntDiapason(weaving, 1, 4);
				}
				break;
			}
			case 4: {
				cout << "Введите длину браслета в сантиметрах. Максимальная длина - " << MaxLengthBrac << " сантиметров:  ";
				Inp::InputIntDiapason(length, MinLengthBrac, MaxLengthBrac);
				break;
			}
			case 0: {
				cycle = false;
			}
			}
		}
	}
	int getWeigth() {
		return (int)((double)AverageBracWeigth * (double)length / MaxLengthBrac);
	}
	int getMatType() {
		return MaterialType;
	}
	int getGemAmount() {
		return GemstoneAmount;
	}
	int getGemType() {
		return GemstoneType;
	}
	int getPrice()final {
		int price = 0;
		if (MaterialType == 1)price +=  (int)(MatT1price * (double)AverageBracWeigth * (double)length / MaxLengthBrac);
		if (MaterialType == 2)price +=  (int)(MatT2price * (double)AverageBracWeigth * (double)length / MaxLengthBrac);
		if (MaterialType == 3)price +=  (int)(MatT3price * (double)AverageBracWeigth * (double)length / MaxLengthBrac);
		if (MaterialType == 4)price +=  (int)(MatT4price * (double)AverageBracWeigth * (double)length / MaxLengthBrac);
		if (MaterialType == 5)price +=  (int)(MatT5price * (double)AverageBracWeigth * (double)length / MaxLengthBrac);
		if (IsThereGemstone) {
			if (GemstoneType == 1)price += GemT1price * GemstoneAmount;
			if (GemstoneType == 2)price += GemT2price * GemstoneAmount;
			if (GemstoneType == 3)price += GemT3price * GemstoneAmount;
			if (GemstoneType == 4)price += GemT4price * GemstoneAmount;
			if (GemstoneType == 5)price += GemT5price * GemstoneAmount;
			if (GemstoneType == 6)price += GemT6price * GemstoneAmount;
			if (GemstoneType == 7)price += GemT7price * GemstoneAmount;
			if (GemstoneType == 8)price += GemT8price * GemstoneAmount;
		}
		if (IsThereWeaving) {
			if (weaving == 1)price *=  (int)Romb;
			if (weaving == 2)price *=  (int)Lav;
			if (weaving == 3)price *=  (int)Figaro;
			if (weaving == 4)price *=  (int)Singapour;
		}
		return price + MasterWorkFee;
	}
	friend ostream& operator <<(ostream& s, bracelet& U) {
		s.write((char*)&U.MaterialType, sizeof((char*)&U.MaterialType));
		s.write((char*)&U.IsThereGemstone, sizeof((char*)&U.IsThereGemstone));
		s.write((char*)&U.GemstoneType, sizeof((char*)&U.GemstoneType));
		s.write((char*)&U.GemstoneAmount, sizeof((char*)&U.GemstoneAmount));
		s.write((char*)&U.weaving, sizeof((char*)&U.weaving));
		s.write((char*)&U.length, sizeof((char*)&U.length));
		s.write((char*)&U.IsThereWeaving, sizeof((char*)&U.IsThereWeaving));
		return s;
	}
	friend istream& operator >>(istream& s, bracelet& U) {
		s.read((char*)&U.MaterialType, sizeof((char*)&U.MaterialType));
		s.read((char*)&U.IsThereGemstone, sizeof((char*)&U.IsThereGemstone));
		s.read((char*)&U.GemstoneType, sizeof((char*)&U.GemstoneType));
		s.read((char*)&U.GemstoneAmount, sizeof((char*)&U.GemstoneAmount));
		s.read((char*)&U.weaving, sizeof((char*)&U.weaving));
		s.read((char*)&U.length, sizeof((char*)&U.length));
		s.read((char*)&U.IsThereWeaving, sizeof((char*)&U.IsThereWeaving));
		return s;
	}
	void getInFile(ostream& s)final {
		s << *this;
	}
	void getFromFile(istream& s)final {
		s >> *this;
	}
};

class earrings : public jewelry { // серьги
	int earringType = 0;
public:
	void inputAll()final {
		cout << "Заполнение информации о серьгах.\n";
		cout << "Введите материал, из которого будут изготовлены серьги.\n";
		cout << "\t1 - Золото 585-й пробы\n";
		cout << "\t2 - Золото 375-й пробы\n";
		cout << "\t3 - Серебро 925-й пробы\n";
		cout << "\t4 - Серебро 875-й пробы\n";
		cout << "\t5 - Медицинская сталь\n";
		Inp::InputIntDiapason(MaterialType, 1, 5);
		cout << "Будут ли присутствовать драгоценные или полудрагоценные камни в серьгах? Введите 1/0:  ";
		Inp::InputBool(IsThereGemstone);
		if (IsThereGemstone) {
			cout << "Введите камни, которые будут в серьгах.\n";
			cout << "Драгоценные:\n";
			cout << "\t1 - Алмаз\n";
			cout << "\t2 - Изумруд\n";
			cout << "\t3 - Рубин\n";
			cout << "\t4 - Жемчуг\n";
			cout << "Полудрагоценные:\n";
			cout << "\t5 - Топаз\n";
			cout << "\t6 - Кварц\n";
			cout << "\t7 - Янтарь\n";
			cout << "\t8 - Опал\n";
			Inp::InputIntDiapason(GemstoneType, 1, 8);
			cout << "Введите количество камней в серьгах. Максимальное количество - " << MaxGemstonesAmount << ":  ";
			Inp::InputIntDiapason(GemstoneAmount, 1, MaxGemstonesAmount);
		}
		cout << "Введите тип серьг.\n";
		cout << "\t1 - Гвозьдики\n";
		cout << "\t2 - Подвески\n";
		cout << "\t3 - Кольца\n";
		Inp::InputIntDiapason(earringType, 1, 3);
	}
	void outputAll()final {
		cout << "Вывод информации о серьгах.\n";
		cout << "Материал серьг: ";
		switch (MaterialType) {
		case 1: { cout << "Золото 585-й пробы\n"; break; }
		case 2: { cout << "Золото 375-й пробы\n"; break; }
		case 3: { cout << "Серебро 925-й пробы\n"; break; }
		case 4: { cout << "Серебро 875-й пробы\n"; break; }
		case 5: { cout << "Медицинская сталь\n"; break; }
		}
		cout << "Вес материала:  " << AverageEarringWeigth << " гр.\n";
		if (IsThereGemstone) {
			cout << "В серьгах будут " << ((GemstoneType < 5) ? "драгоценные" : "полудрагоценные") << " камни.\n";
			cout << "Название камней: ";
			switch (MaterialType) {
			case 1: { cout << "Алмаз\n"; break; }
			case 2: { cout << "Изумруд\n"; break; }
			case 3: { cout << "Рубин\n"; break; }
			case 4: { cout << "Жемчуг\n"; break; }
			case 5: { cout << "Топаз\n"; break; }
			case 6: { cout << "Кварц\n"; break; }
			case 7: { cout << "Янтарь\n"; break; }
			case 8: { cout << "Опал\n"; break; }
			}
			cout << "Их количество:  " << GemstoneAmount << "\n";
		}
		else {
			cout << "В серьгах не будет другоценных или полудрагоценных камней.\n";
		}
		cout << "Тип серьг:  ";
		switch (earringType) {
		case 1: { cout << "Гвозьдики\n"; break; }
		case 2: { cout << "Подвески\n"; break; }
		case 3: { cout << "Кольца\n"; break; }
		}
	}
	void redact()final {
		int choice = 0;
		bool cycle = true;
		while (cycle) {
			cout << "Меню редактирования информации о серьгах.\n";
			cout << "Которое из полей заказа вы хотите редактировать?\n";
			cout << "\t1 - Материал\n";
			cout << "\t2 - Камни\n";
			cout << "\t3 - Тип серьг\n";
			cout << "\t4 - Длина\n";
			cout << "\tВведите 0, чтобы выйти из меню редактирования:  ";
			Inp::InputIntDiapason(choice, 0, 4);
			switch (choice) {
			case 1: {
				cout << "Введите материал, из которого будут изготовлены серьги.\n";
				cout << "\t1 - Золото 585-й пробы\n";
				cout << "\t2 - Золото 375-й пробы\n";
				cout << "\t3 - Серебро 925-й пробы\n";
				cout << "\t4 - Серебро 875-й пробы\n";
				cout << "\t5 - Медицинская сталь\n";
				Inp::InputIntDiapason(MaterialType, 1, 5);
				break;
			}
			case 2: {
				cout << "Будут ли присутствовать драгоценные или полудрагоценные камни в серьгах? Введите 1/0:  ";
				Inp::InputBool(IsThereGemstone);
				if (IsThereGemstone) {
					cout << "Введите камни, которые будут в серьгах.\n";
					cout << "Драгоценные:\n";
					cout << "\t1 - Алмаз\n";
					cout << "\t2 - Изумруд\n";
					cout << "\t3 - Рубин\n";
					cout << "\t4 - Жемчуг\n";
					cout << "Полудрагоценные:\n";
					cout << "\t5 - Топаз\n";
					cout << "\t6 - Кварц\n";
					cout << "\t7 - Янтарь\n";
					cout << "\t8 - Опал\n";
					Inp::InputIntDiapason(GemstoneType, 1, 8);
					cout << "Введите количество камней в серьгах. Максимальное количество - " << MaxGemstonesAmount << ":  ";
					Inp::InputIntDiapason(GemstoneAmount, 1, MaxGemstonesAmount);
				}
				break;
			}
			case 3: {
				cout << "Введите тип серьг.\n";
				cout << "\t1 - Гвозьдики\n";
				cout << "\t2 - Подвески\n";
				cout << "\t3 - Кольца\n";
				Inp::InputIntDiapason(earringType, 1, 3);
				break;
			}
			case 0: {
				cycle = false;
			}
			}
		}
	}
	int getWeigth() {
		return AverageEarringWeigth;
	}
	int getMatType() {
		return MaterialType;
	}
	int getGemAmount() {
		return GemstoneAmount;
	}
	int getGemType(){
		return GemstoneType;
	}
	int getPrice()final {
		int price = 0;
		if (MaterialType == 1)price += MatT1price * AverageEarringWeigth;
		if (MaterialType == 2)price += MatT2price * AverageEarringWeigth;
		if (MaterialType == 3)price += MatT3price * AverageEarringWeigth;
		if (MaterialType == 4)price += MatT4price * AverageEarringWeigth;
		if (MaterialType == 5)price += MatT5price * AverageEarringWeigth;
		if (IsThereGemstone) {
			if (GemstoneType == 1)price += GemT1price * GemstoneAmount;
			if (GemstoneType == 2)price += GemT2price * GemstoneAmount;
			if (GemstoneType == 3)price += GemT3price * GemstoneAmount;
			if (GemstoneType == 4)price += GemT4price * GemstoneAmount;
			if (GemstoneType == 5)price += GemT5price * GemstoneAmount;
			if (GemstoneType == 6)price += GemT6price * GemstoneAmount;
			if (GemstoneType == 7)price += GemT7price * GemstoneAmount;
			if (GemstoneType == 8)price += GemT8price * GemstoneAmount;
		}
		if (earringType == 1)price *= (int)Romb;
		if (earringType == 2)price *= (int)Podveskas;
		if (earringType == 3)price *= (int)Koltsa;
		return price + MasterWorkFee;
	}
	friend ostream& operator <<(ostream& s, earrings& U) {
		s.write((char*)&U.MaterialType, sizeof((char*)&U.MaterialType));
		s.write((char*)&U.IsThereGemstone, sizeof((char*)&U.IsThereGemstone));
		s.write((char*)&U.GemstoneType, sizeof((char*)&U.GemstoneType));
		s.write((char*)&U.GemstoneAmount, sizeof((char*)&U.GemstoneAmount));
		s.write((char*)&U.earringType, sizeof((char*)&U.earringType));
		return s;
	}
	friend istream& operator >>(istream& s, earrings& U) {
		s.read((char*)&U.MaterialType, sizeof((char*)&U.MaterialType));
		s.read((char*)&U.IsThereGemstone, sizeof((char*)&U.IsThereGemstone));
		s.read((char*)&U.GemstoneType, sizeof((char*)&U.GemstoneType));
		s.read((char*)&U.GemstoneAmount, sizeof((char*)&U.GemstoneAmount));
		s.read((char*)&U.earringType, sizeof((char*)&U.earringType));
		return s;
	}
	void getInFile(ostream& s)final {
		s << *this;
	}
	void getFromFile(istream& s)final {
		s >> *this;
	}
};

class ring : public jewelry { // кольцо
	bool IsArtisticProcessed = 0;
	int size = 0;
public:
	int getWeigth() {
		return AverageRingWeight * size / MaxSizeRing;
	}
	int getMatType() {
		return MaterialType;
	}
	int getGemAmount() {
		return GemstoneAmount;
	}
	int getGemType() {
		return GemstoneType;
	}
	void inputAll()final {
		cout << "Заполнение информации о кольце.\n";
		cout << "Введите материал, из которого будет изготовлено кольцо.\n";
		cout << "\t1 - Золото 585-й пробы\n";
		cout << "\t2 - Золото 375-й пробы\n";
		cout << "\t3 - Серебро 925-й пробы\n";
		cout << "\t4 - Серебро 875-й пробы\n";
		cout << "\t5 - Медицинская сталь\n";
		Inp::InputIntDiapason(MaterialType, 1, 5);
		cout << "Будут ли присутствовать драгоценные или полудрагоценные камни в кольце? Введите 1/0:  ";
		Inp::InputBool(IsThereGemstone);
		if (IsThereGemstone) {
			cout << "Введите камни, которые будут в кольце.\n";
			cout << "Драгоценные:\n";
			cout << "\t1 - Алмаз\n";
			cout << "\t2 - Изумруд\n";
			cout << "\t3 - Рубин\n";
			cout << "\t4 - Жемчуг\n";
			cout << "Полудрагоценные:\n";
			cout << "\t5 - Топаз\n";
			cout << "\t6 - Кварц\n";
			cout << "\t7 - Янтарь\n";
			cout << "\t8 - Опал\n";
			Inp::InputIntDiapason(GemstoneType, 1, 8);
			cout << "Введите количество камней в кольце. Максимальное количество - " << MaxGemstonesAmount << ":  ";
			Inp::InputIntDiapason(GemstoneAmount, 1, MaxGemstonesAmount);
		}
		cout << "Будет ли присутствовать художественная обработка в кольце? Введите 1/0:  ";
		Inp::InputBool(IsArtisticProcessed);
		cout << "Введите диаметр кольца в миллиметрах. Максимальный диаметр - " << MaxSizeRing << " миллиметров:  ";
		Inp::InputIntDiapason(size, MinSizeRing, MaxSizeRing);
	}
	void outputAll()final {
		cout << "Вывод информации о кольце.\n";
		cout << "Материал кольца: ";
		switch (MaterialType) {
		case 1: { cout << "Золото 585-й пробы\n"; break; }
		case 2: { cout << "Золото 375-й пробы\n"; break; }
		case 3: { cout << "Серебро 925-й пробы\n"; break; }
		case 4: { cout << "Серебро 875-й пробы\n"; break; }
		case 5: { cout << "Медицинская сталь\n"; break; }
		}
		cout << "Вес материала:  " << AverageRingWeight * size / MaxSizeRing << " гр.\n";
		if (IsThereGemstone) {
			cout << "В кольце будут " << ((GemstoneType < 5) ? "драгоценные" : "полудрагоценные") << " камни.\n";
			cout << "Название камней: ";
			switch (MaterialType) {
			case 1: { cout << "Алмаз\n"; break; }
			case 2: { cout << "Изумруд\n"; break; }
			case 3: { cout << "Рубин\n"; break; }
			case 4: { cout << "Жемчуг\n"; break; }
			case 5: { cout << "Топаз\n"; break; }
			case 6: { cout << "Кварц\n"; break; }
			case 7: { cout << "Янтарь\n"; break; }
			case 8: { cout << "Опал\n"; break; }
			}
			cout << "Их количество:  " << GemstoneAmount << "\n";
		}
		else {
			cout << "В кольце не будет другоценных или полудрагоценных камней.\n";
		}
		if (IsArtisticProcessed) {
			cout << "На кольце будет художественная обработка.\n";
		}
		else {
			cout << "На кольце не будет художественной обработки.\n";
		}
		cout << "Диаметр кольца:  " << size << " миллиметров.\n";
	}
	void redact()final {
		int choice = 0;
		bool cycle = true;
		while (cycle) {
			cout << "Меню редактирования информации о кольце.\n";
			cout << "Которое из полей заказа вы хотите редактировать?\n";
			cout << "\t1 - Материал\n";
			cout << "\t2 - Камни\n";
			cout << "\t3 - Художественная обработка\n";
			cout << "\t4 - Длина\n";
			cout << "\tВведите 0, чтобы выйти из меню редактирования:  ";
			Inp::InputIntDiapason(choice, 0, 4);
			switch (choice) {
			case 1: {
				cout << "Введите материал, из которого будет изготовлено кольцо.\n";
				cout << "\t1 - Золото 585-й пробы\n";
				cout << "\t2 - Золото 375-й пробы\n";
				cout << "\t3 - Серебро 925-й пробы\n";
				cout << "\t4 - Серебро 875-й пробы\n";
				cout << "\t5 - Медицинская сталь\n";
				Inp::InputIntDiapason(MaterialType, 1, 5);
				break;
			}
			case 2: {
				cout << "Будут ли присутствовать драгоценные или полудрагоценные камни в кольце? Введите 1/0:  ";
				Inp::InputBool(IsThereGemstone);
				if (IsThereGemstone) {
					cout << "Введите камни, которые будут в кольце.\n";
					cout << "Драгоценные:\n";
					cout << "\t1 - Алмаз\n";
					cout << "\t2 - Изумруд\n";
					cout << "\t3 - Рубин\n";
					cout << "\t4 - Жемчуг\n";
					cout << "Полудрагоценные:\n";
					cout << "\t5 - Топаз\n";
					cout << "\t6 - Кварц\n";
					cout << "\t7 - Янтарь\n";
					cout << "\t8 - Опал\n";
					Inp::InputIntDiapason(GemstoneType, 1, 8);
					cout << "Введите количество камней в кольце. Максимальное количество - " << MaxGemstonesAmount << ":  ";
					Inp::InputIntDiapason(GemstoneAmount, 1, MaxGemstonesAmount);
				}
				break;
			}
			case 3: {
				cout << "Будет ли присутствовать художественная обработка в кольце? Введите 1/0:  ";
				Inp::InputBool(IsArtisticProcessed);
				break;
			}
			case 4: {
				cout << "Введите диаметр кольца в миллиметрах. Максимальный диаметр - " << MaxLengthCol << " миллиметров:  ";
				Inp::InputIntDiapason(size, MinLengthCol, MaxLengthCol);
				break;
			}
			case 0: {
				cycle = false;
			}
			}
		}
	}
	int getPrice()final {
		int price = 0;
		if (MaterialType == 1)price += MatT1price * AverageRingWeight * size / MaxSizeRing;
		if (MaterialType == 2)price += MatT2price * AverageRingWeight * size / MaxSizeRing;
		if (MaterialType == 3)price += MatT3price * AverageRingWeight * size / MaxSizeRing;
		if (MaterialType == 4)price += MatT4price * AverageRingWeight * size / MaxSizeRing;
		if (MaterialType == 5)price += MatT5price * AverageRingWeight * size / MaxSizeRing;
		if (IsThereGemstone) {
			if (GemstoneType == 1)price += GemT1price * GemstoneAmount;
			if (GemstoneType == 2)price += GemT2price * GemstoneAmount;
			if (GemstoneType == 3)price += GemT3price * GemstoneAmount;
			if (GemstoneType == 4)price += GemT4price * GemstoneAmount;
			if (GemstoneType == 5)price += GemT5price * GemstoneAmount;
			if (GemstoneType == 6)price += GemT6price * GemstoneAmount;
			if (GemstoneType == 7)price += GemT7price * GemstoneAmount;
			if (GemstoneType == 8)price += GemT8price * GemstoneAmount;
		}
		if (IsArtisticProcessed == 1)price *= (int)ArtProcessed;
		return price + MasterWorkFee;
	}
	friend ostream& operator <<(ostream& s, ring& U) {
		s.write((char*)&U.MaterialType, sizeof((char*)&U.MaterialType));
		s.write((char*)&U.IsThereGemstone, sizeof((char*)&U.IsThereGemstone));
		s.write((char*)&U.GemstoneType, sizeof((char*)&U.GemstoneType));
		s.write((char*)&U.GemstoneAmount, sizeof((char*)&U.GemstoneAmount));
		s.write((char*)&U.IsArtisticProcessed, sizeof((char*)&U.IsArtisticProcessed));
		s.write((char*)&U.size, sizeof((char*)&U.size));
		return s;
	}
	friend istream& operator >>(istream& s, ring& U) {
		s.read((char*)&U.MaterialType, sizeof((char*)&U.MaterialType));
		s.read((char*)&U.IsThereGemstone, sizeof((char*)&U.IsThereGemstone));
		s.read((char*)&U.GemstoneType, sizeof((char*)&U.GemstoneType));
		s.read((char*)&U.GemstoneAmount, sizeof((char*)&U.GemstoneAmount));
		s.read((char*)&U.IsArtisticProcessed, sizeof((char*)&U.IsArtisticProcessed));
		s.read((char*)&U.size, sizeof((char*)&U.size));
		return s;
	}
	void getInFile(ostream& s)final {
		s << *this;
	}
	void getFromFile(istream& s)final {
		s >> *this;
	}
}; 

class RegularUser {
	string Username = "";
	int Money = 0;
public:
	const string& getName() { return Username; }
	const int& getMaoney() { return Money; }
	void setName(const string& naem) { Username = naem; }
	void setMoney(const int& mone) { Money = mone; }
	friend ostream& operator <<(ostream& s, RegularUser& U) {
		s.write((char*)&U.Money, sizeof((char*)&U.Money));
		char buf[FileBufSize];
		strcpy_s(buf, U.Username.c_str());
		s.write(buf, sizeof(buf));
		return s;
	}
	friend istream& operator >>(istream& s, RegularUser& U) {
		s.read((char*)&U.Money, sizeof((char*)&U.Money));
		char buf[FileBufSize];
		s.read(buf, sizeof(buf));
		U.Username = buf;
		return s;
	}
};

class Master {
	int GemsAmount[8] = { 0 };
	int MetalsGramms[5] = { 0 };
	int money = 0;
	string Name;
public:
	const string& getName() {
		return Name;
	}
	const int getMoney() { 
		return money; 
	}
	void setMoney(const int& moneyy) { 
		money = moneyy; 
	}
	void buyCycle() {
		bool cycle = true;
		while (cycle) {
			buy();
			cout << "Вы хотите продолжить покупку? Введите 1/0:  ";
			int yes;
			Inp::InputIntDiapason(yes, 0, 1);
			system("cls");
			if (!yes)cycle = false;
		}
	}
	void buy() {
		cout << "Ваши средства: " << money << "руб.\n";
		cout << "Вы хотите купить металлы или камни? Введите 1/0:  ";
		int ch;
		int MoneyToBuy = 0;
		Inp::InputIntDiapason(ch, 0, 1);
		if (!ch) {
			int StonesType;
			int StonesAmount;
			cout << "Какой тип камней вы хотите приобрести?.\n";
			cout << "Драгоценные:\n";
			cout << "\t1 - Алмаз.\t Стоимость 1 шт.:  " << GemT1price << "\n";
			cout << "\t2 - Изумруд.\t Стоимость 1 шт.:  " << GemT2price << "\n";
			cout << "\t3 - Рубин.\t Стоимость 1 шт.:  " << GemT3price << "\n";
			cout << "\t4 - Жемчуг.\t Стоимость 1 шт.:  " << GemT4price << "\n";
			cout << "Полудрагоценные:\n";
			cout << "\t5 - Топаз.\t Стоимость 1 шт.:  " << GemT5price << "\n";
			cout << "\t6 - Кварц.\t Стоимость 1 шт.:  " << GemT6price << "\n";
			cout << "\t7 - Янтарь.\t Стоимость 1 шт.:  " << GemT7price << "\n";
			cout << "\t8 - Опал.\t Стоимость 1 шт.:  " << GemT8price << "\n";
			Inp::InputIntDiapason(StonesType, 1, 8);
			cout << "Введите количество камней, которое вы хотите приобрести (1 - 100):  ";
			Inp::InputIntDiapason(StonesAmount, 1, 100);
			if (StonesType == 1)MoneyToBuy = StonesAmount * GemT1price; //Стоимость камней
			if (StonesType == 2)MoneyToBuy = StonesAmount * GemT2price;
			if (StonesType == 3)MoneyToBuy = StonesAmount * GemT3price;
			if (StonesType == 4)MoneyToBuy = StonesAmount * GemT4price;
			if (StonesType == 5)MoneyToBuy = StonesAmount * GemT5price;
			if (StonesType == 6)MoneyToBuy = StonesAmount * GemT6price;
			if (StonesType == 7)MoneyToBuy = StonesAmount * GemT7price;
			if (StonesType == 8)MoneyToBuy = StonesAmount * GemT8price;
			if (money >= MoneyToBuy) {
				GemsAmount[StonesType - 1] += StonesAmount;
				money -= MoneyToBuy;
				cout << "Покупка прошла успешно.\n";
			}
			else {
				cout << "Недостаточно денег для покупки. Стоимость покупки: " << MoneyToBuy << "руб.\n";
			}
		}
		else {
			cout << "Выберите метариал для покупки.\n";
			cout << "\t1 - Золото 585-й пробы.\t\t Стоимость 1 гр.:  " << MatT1price << "\n";
			cout << "\t2 - Золото 375-й пробы.\t\t Стоимость 1 гр.:  " << MatT2price << "\n";
			cout << "\t3 - Серебро 925-й пробы.\t Стоимость 1 гр.:  " << MatT3price << "\n";
			cout << "\t4 - Серебро 875-й пробы.\t Стоимость 1 гр.:  " << MatT4price << "\n";
			cout << "\t5 - Медицинская сталь.\t\t Стоимость 1 гр.:  " << MatT5price << "\n";
			int matType;
			int matWeight;
			Inp::InputIntDiapason(matType, 1, 5);
			cout << "Введите вес метариала для покупки.\n";
			cout << "Минимальный вес - 10 гр., максимальный вес - 5000 гр:  \n";
			Inp::InputIntDiapason(matWeight, 10, 5000);
			if (matType == 1)MoneyToBuy = matWeight * MatT1price; // стоимость метариалов
			if (matType == 2)MoneyToBuy = matWeight * MatT2price;
			if (matType == 3)MoneyToBuy = matWeight * MatT3price;
			if (matType == 4)MoneyToBuy = matWeight * MatT4price;
			if (matType == 5)MoneyToBuy = matWeight * MatT5price;
			if (money >= MoneyToBuy) {
				MetalsGramms[matType - 1] += matWeight;
				money -= MoneyToBuy;
				cout << "Покупка прошла успешно.\n";
			}
			else {
				cout << "Недостаточно денег для покупки. Стоимость покупки: " << MoneyToBuy << "руб.\n";
			}
		}
	}
	void setName(const string& a) {
		Name = a;
	}
	void ShowAll() {
		cout << "Инвентарь мастера " << Name << ":" << endl;
		cout << "Ваши средства: " << money << "руб.\n\n";
		cout << "Камни для работы в наличии(единиц):  \n";
		cout << "Драгоценные:\n";
		cout << "\tАлмаз - " << GemsAmount[0] << " шт.\n";
		cout << "\tИзумруд - " << GemsAmount[1] << " шт.\n";
		cout << "\tРубин - " << GemsAmount[2] << " шт.\n";
		cout << "\tЖемчуг - " << GemsAmount[3] << " шт.\n";
		cout << "Полудрагоценные:\n";
		cout << "\tТопаз - " << GemsAmount[4] << " шт.\n";
		cout << "\tКварц - " << GemsAmount[5] << " шт.\n";
		cout << "\tЯнтарь - " << GemsAmount[6] << " шт.\n";
		cout << "\tОпал - " << GemsAmount[7] << " шт.\n\n";
		cout << "Металлы для работы в наличии(граммов):  \n";
		cout << "Золото 585-й пробы - " << MetalsGramms[0] << " гр.\n";
		cout << "Золото 375-й пробы - " << MetalsGramms[1] << " гр.\n";
		cout << "Серебро 925-й пробы - " << MetalsGramms[2] << " гр.\n";
		cout << "Серебро 875-й пробы - " << MetalsGramms[3] << " гр.\n";
		cout << "Медицинская сталь - " << MetalsGramms[4] << " гр.\n";

	}
	bool minMat(int typeMet, int weigthMet, int typeGem, int amountGem) {
		if (MetalsGramms[typeMet - 1] < weigthMet)return 0;
		if (GemsAmount[typeGem - 1] < amountGem)return 0;
		MetalsGramms[typeMet - 1] -= weigthMet;
		GemsAmount[typeGem - 1] -= amountGem;
		return 1;
	}
	friend ostream& operator <<(ostream& s, Master& U) {
		for (int i = 0; i < 8; i++)
			s.write((char*)&U.GemsAmount, sizeof((char*)&U.GemsAmount));
		for (int i = 0; i < 5; i++)
			s.write((char*)&U.MetalsGramms[i], sizeof((char*)&U.MetalsGramms[i]));
		s.write((char*)&U.money, sizeof((char*)&U.money));
		char buf[FileBufSize];
		strcpy_s(buf, U.Name.c_str());
		s.write(buf, sizeof(buf));
		return s;
	}
	friend istream& operator >>(istream& s, Master& U) {
		for (int i = 0; i < 8; i++)
			s.read((char*)&U.GemsAmount[i], sizeof((char*)&U.GemsAmount[i]));
		for (int i = 0; i < 5; i++)
			s.read((char*)&U.MetalsGramms[i], sizeof((char*)&U.MetalsGramms[i]));
		s.read((char*)&U.money, sizeof((char*)&U.money));
		char buf[FileBufSize];
		s.read(buf, sizeof(buf));
		U.Name = buf;
		return s;
	}
};

class Order {
	string nameOfOrderer;
	int typeOfJewelry; // 1 - necklace, 2 - bracelet, 3 - earrings, 4 - ring.
	jewelry* Jewelry;
	int isReady; // готовность заказа. 0 - не принят, 1 - принят и в работе, 2 - готов.
	string condition; // информация о процессе принятия заказа. к примеру ожидаемая дата готовности
public:
	int getOrderPrice() {
		return Jewelry->getPrice();
	}
	const string& getOrdName(){ 
		return nameOfOrderer; 
	}
	bool createOrder(RegularUser& _Usr){
		nameOfOrderer = _Usr.getName();
		isReady = 0;
		int choice;
		cout << "Выберите тип ювелирного украшения для заказа:\n";
		cout << "\t1 - Колье\n";
		cout << "\t2 - Браслет\n";
		cout << "\t3 - Серьги\n";
		cout << "\t4 - Кольцо\n";
		Inp::InputIntDiapason(choice, 1, 4);
		system("cls");
		typeOfJewelry = choice;
		switch (choice) {
		case 1: {
			Jewelry = new necklace; break; }
		case 2: {
			Jewelry = new bracelet; break; }
		case 3: {
			Jewelry = new earrings; break; }
		case 4: {
			Jewelry = new ring; break; }
		}
		Jewelry->inputAll();
		int m = Jewelry->getPrice();
		if (_Usr.getMaoney() < m) {
			cout << "Недостаточно средств для оформления заказа.\nСтоимость заказа: " << m << "\nВаши средства: " << _Usr.getMaoney() << "\n";
			return false;
		}
		else {
			cout << "Стоимость заказа: " << m << " руб.\n";
			cout << "Ваши средства: " << _Usr.getMaoney() << " руб.\n";
			cout << "Подтвердить заказ? Введите 1/0:";
			int ch;
			Inp::InputIntDiapason(ch, 0, 1);
			if (ch == 1) {
				_Usr.setMoney(_Usr.getMaoney() - m);
				cout << "Заказ оформлен.\n";
			}
			else {
				cout << "Вы отменили заказ.\n";
			}
			return true;
		}
	}// для заказчика
	void editCondition(Master& mas) {
		if (isReady == 2) {
			cout << "Заказ готов, нельзя изменить его состояние\n";
		}
		else {
			cout << "Введите, в каком состоянии сейчас находится заказ.\n";
			cout << "\t1 - в производстве\n";
			cout << "\t2 - готов\n";
			int isR;
			Inp::InputIntDiapason(isR, 1, 2);
			if (isR == 1 && isReady == 0) {
				if (mas.minMat(Jewelry->getMatType(), Jewelry->getWeigth(), Jewelry->getGemType(), Jewelry->getGemAmount())) {
					cout << "Введите новую ожидаемую дату завершения производства заказа:  ";
					getline(cin, condition);
					cout << "Состояние заказа обновлено.\n";
					isReady = isR;
					return;
				}
				else {
					cout << "Для выполнения этого заказа у вас недостаточно материалов.\n";
					return;
				}
			} // принятие заказа
			if (isR == 2 && isReady == 0) {
				if (mas.minMat(Jewelry->getMatType(), Jewelry->getWeigth(), Jewelry->getGemType(), Jewelry->getGemAmount())) {
					mas.setMoney(Jewelry->getPrice() + mas.getMoney());
					cout << "Состояние заказа обновлено. Заказ выполнен. Полученные средства: " << Jewelry->getPrice() << " руб.\n";
					isReady = isR;
					return;
				}
				else {
					cout << "Для выполнения этого заказа у вас недостаточно материалов.\n";
					return;
				}
			} // выполнение с нуля
			if (isR == 1 && isReady == 1) {
				cout << "Вы собираетесь обновить дату завершения производства заказа.\n";
				cout << "Предыдущая дата:  " << condition << "\n";
				cout << "Введите новую ожидаемую дату завершения производства заказа:  ";
				getline(cin, condition);
				cout << "Состояние заказа обновлено.\n";
			} // обновление даты производства заказа
			if (isR == 2 && isReady == 1) {
				mas.setMoney(Jewelry->getPrice() + mas.getMoney());
				cout << "Состояние заказа обновлено. Заказ выполнен. Полученные средства: " << Jewelry->getPrice() << " руб.\n";
				isReady = isR;
				return;
			} // выполнение уже принятого заказа т.е. материалы уже использованы
		}
	} // для мастера
	void seeOrder() {
		cout << "Информация о заказе:\n";
		cout << "Имя заказчика:  " << nameOfOrderer << "\n";
		if (isReady == 0) { cout << "Заказ еще не принят.\n"; }
		if (isReady == 1) { 
			cout << "Заказ находится в работе.\n"; 
			cout << "Ожидаемое время выполнения заказа:  " << condition << "\n";
		}
		if (isReady == 2) {
			cout << "Заказ готов.\n";
		}
		Jewelry->outputAll();
	}// для всех
	void redactOrd() {
		this->Jewelry->redact();
	}
	int getState() { 
		return isReady;
	}
	friend ostream& operator <<(ostream& s, Order& U) {
		s.write((char*)&U.typeOfJewelry, sizeof((char*)&U.typeOfJewelry));
		s.write((char*)&U.isReady, sizeof((char*)&U.isReady));

		char Buf[FileBufSize];
		strcpy_s(Buf, U.condition.c_str());
		s.write(Buf, sizeof(Buf));
		strcpy_s(Buf, U.nameOfOrderer.c_str());
		s.write(Buf, sizeof(Buf));
		U.Jewelry->getInFile(s);

		return s;
	}
	friend istream& operator >>(istream& s, Order& U) {
		s.read((char*)&U.typeOfJewelry, sizeof((char*)&U.typeOfJewelry));
		s.read((char*)&U.isReady, sizeof((char*)&U.isReady));

		char Buf[FileBufSize];
		//U.condition = "";
		s.read(Buf, sizeof(Buf));
		U.condition = Buf;
		s.read(Buf, sizeof(Buf));
		U.nameOfOrderer = Buf;

		switch (U.typeOfJewelry) {
		case 1: {
			U.Jewelry = new necklace();
			U.Jewelry->getFromFile(s);
			break;
		}
		case 2: {
			U.Jewelry = new bracelet();
			U.Jewelry->getFromFile(s);
			break;
		}
		case 3: {
			U.Jewelry = new earrings();
			U.Jewelry->getFromFile(s);
			break;
		}
		case 4: {
			U.Jewelry = new ring();
			U.Jewelry->getFromFile(s);
			break;
		}
		}
		return s;
	}
	Order(const Order& obj) {
		switch (obj.typeOfJewelry) {
		case 1: {
			Jewelry = new necklace();
			break;
		}
		case 2: {
			Jewelry = new bracelet();
			break;
		}
		case 3: {
			Jewelry = new earrings();
			break;
		}
		case 4: {
			Jewelry = new ring();
			break;
		}
		}
		typeOfJewelry = obj.typeOfJewelry;
		Jewelry = obj.Jewelry;
		nameOfOrderer = obj.nameOfOrderer;
		isReady = obj.isReady;
		condition = obj.condition;
	}
	Order() { 
		typeOfJewelry = 0;
		isReady = 0;
		Jewelry = nullptr; 
	}
	friend bool compareOrders(Order a, Order b);
};

bool compareOrders(Order a, Order b) {
	if (a.isReady != b.isReady)return (a.isReady < b.isReady);
	return (a.Jewelry->getPrice() < b.Jewelry->getPrice());
}

class MainJewelryMenu {
	vector<Order> Vec;
	vector<RegularUser> Users;
	Master Jewerlyst;
	int OurUserNum = -1;
	bool isMaster = 0;
public:
	void start(const string& UserName) {
		fstream fileMas("Master.info", ios::binary | ios::out | ios::in);
		if (!fileMas.is_open()) {
			fstream fileMaster("Master.info", ios::binary | ios::out | ios::in | ios::trunc);
			Jewerlyst.setMoney(StarterMoneyOfMaster);
			Jewerlyst.setName(UserName);
			fileMaster << Jewerlyst;
			fstream fileOrd("Orders.info", ios::binary | ios::out | ios::in | ios::trunc);
			fstream fileUsr("Users.info", ios::binary | ios::out | ios::in | ios::trunc);
			isMaster = true;
			return;
		}
		else {
			fileMas >> Jewerlyst;
		}
		fstream fileOrders("Orders.info", ios::binary | ios::out | ios::in);
		while (true) {
			Order a;
			fileOrders >> a;
			if (fileOrders.eof())break;
			Vec.push_back(a);
		}
		if (Jewerlyst.getName() == UserName) {
			isMaster = true;
			return;
		}
		bool FoundUser = false;
		int numUser = 0;
		fstream fileUsers("Users.info", ios::binary | ios::out | ios::in);
		while (true) {
			RegularUser a;
			fileUsers >> a;
			if (fileUsers.eof())break;
			if (a.getName() == UserName)
			{
				FoundUser = true;
			}
			if (!FoundUser)numUser++;
			Users.push_back(a);
		}
		OurUserNum = numUser;
		if (!FoundUser) {
			RegularUser a;
			a.setMoney(5000);
			a.setName(UserName);
			Users.push_back(a);
		}
		isMaster = false;
	}
	void saveMasterChanges() {
		fstream fileMaster("Master.info", ios::binary | ios::out | ios::in | ios::trunc);
		fileMaster << Jewerlyst;
		fstream fileOrders("Orders.info", ios::binary | ios::out | ios::in | ios::trunc);
		for (int i = 0; i < (int)Vec.size(); i++) fileOrders << Vec[i];
	}
	void saveUserChanges() {
		fstream fileOrders("Orders.info", ios::binary | ios::out | ios::in | ios::trunc);
		for (int i = 0; i < (int)Vec.size(); i++) fileOrders << Vec[i];
		fstream fileUsers("Users.info", ios::binary | ios::out | ios::in | ios::trunc);
		for (int i = 0; i < (int)Users.size(); i++) fileUsers << Users[i];
	}
	void MainMenu(string UserName) {
		start(UserName);
		if (isMaster) { MasterMenu(); }
		else { UserMenu(); }
	}
	void MasterMenu() {
		bool cycle = true;
		while (cycle) {
			system("pause");
			system("cls");
			saveMasterChanges();
			cout << "Меню мастера " << Jewerlyst.getName() << ":\n";
			cout << "1 - Просмотреть все пока не принятые заказы\n";
			cout << "2 - Просмотреть все заказы в работе\n";
			cout << "3 - Просмотреть все выполненные заказы\n";
			cout << "4 - Обновить состояние какого-либо заказа (Выполнить заказ)\n";
			cout << "5 - Просмотреть свои средства и материалы\n";
			cout << "6 - Купить больше материалов\n";
			cout << "7 - Сортировать заказы\n";
			cout << "0 - Выйти в главное меню\n";
			int choice;
			Inp::InputIntDiapason(choice, 0 , 7);
			system("cls");
			switch (choice) {
			case 1: {
				bool shown = false;
				for (int i = 0; i < (int)Vec.size(); i++) {
					if (Vec[i].getState() == 0)
					{
						if (shown)cout << "----------------------------------------\n\n"; shown = true;
						cout << "Заказ номер " << i+1 << "\n";
						Vec[i].seeOrder();
						cout << endl;
					}
				}
				if (!shown)cout << "В системе отсутствуют пока не принятые заказы.\n"; break;
			}
			case 2: {
				bool shown = false;
				for (int i = 0; i < (int)Vec.size(); i++) {
					if (Vec[i].getState() == 1)
					{
						if (shown)cout << "----------------------------------------\n\n"; shown = true;
						cout << "Заказ номер " << i+1 << "\n";
						Vec[i].seeOrder();
						cout << endl;
					}
				}
				if (!shown)cout << "В системе отсутствуют заказы в работе.\n";
				break;
			}
			case 3: {
				bool shown = false;
				for (int i = 0; i < (int)Vec.size(); i++) {
					if (Vec[i].getState() == 2)
					{
						if (shown)cout << "----------------------------------------\n\n"; shown = true;
						cout << "Заказ номер " << i+1 << "\n";
						Vec[i].seeOrder();
						cout << endl;
					}
				}
				if (!shown)cout << "В системе отсутствуют выполненные заказы.\n";
				break;
			}
			case 4: {
				if ((int)Vec.size() == 0) {
					cout << "В системе сейчас 0 заказов. невозможно обновить.\n";
					break;
				}
				cout << "В системе сейчас " << (int)Vec.size() << " заказ(ов). Введите номер заказа, состояние которого вы хотите обновить:  ";
				int num;
				Inp::InputIntDiapason(num, 1, (int)Vec.size());
				num--;
				Vec[num].editCondition(Jewerlyst);
				break;
			}
			case 5: {
				Jewerlyst.ShowAll(); break;
			}
			case 6: {
				Jewerlyst.buyCycle(); break;
			}
			case 7: {
				if (Vec.size() < 2) {
					cout << "Сортировка невозможна. В системе менее чем 2 заказа.\n";
				}
				sort(Vec.begin(), Vec.end(), compareOrders);
				cout << "Сортировка прошла успешно.\n";
				break;
			}
			case 0: {
				cycle = false; break;
			}
			}
		}
	}
	void UserMenu() {
		bool cycle = true;
		while (cycle) {
			saveUserChanges();
			system("pause");
			system("cls");
			cout << "Меню пользователя " << Users[OurUserNum].getName() << ":\n";
			cout << "1 - Сделать заказ\n";
			cout << "2 - Просмотреть все свои пока не принятые заказы\n";
			cout << "3 - Просмотреть все свои заказы в работе\n";
			cout << "4 - Просмотреть все свои выполненные заказы\n";
			cout << "5 - Редактировать какой-либо свой заказ (пока не принятый)\n";
			cout << "6 - Отменить какой-либо свой заказ (пока не принятый)\n";
			cout << "7 - Просмотреть свои деньги\n";
			cout << "8 - Пополнить свой счет\n";
			cout << "9 - Просмотреть заказ по его номеру\n";
			cout << "0 - Выйти в главное меню\n";
			int choice;
			Inp::InputIntDiapason(choice, 0, 9);
			system("cls");
			switch (choice) {
			case 1: {
				Order a;
				if (a.createOrder(Users[OurUserNum])) {
					Vec.push_back(a);
				}
				break;
			}
			case 2: {
				bool shown = false;
				for (int i = 0; i < (int)Vec.size(); i++) {
					if (Vec[i].getState() == 0 && Vec[i].getOrdName() == Users[OurUserNum].getName())
					{
						if (shown)cout << "----------------------------------------\n\n"; shown = true;
						cout << "Заказ номер " << i+1 << "\n";
						Vec[i].seeOrder();
						cout << endl;
					}
				}
				if (!shown)cout << "В системе отсутствуют пока не принятые заказы.\n";
				break;
			}
			case 3: {
				bool shown = false;
				for (int i = 0; i < (int)Vec.size(); i++) {
					if (Vec[i].getState() == 1 && Vec[i].getOrdName() == Users[OurUserNum].getName())
					{
						if (shown)cout << "----------------------------------------\n\n"; shown = true;
						cout << "Заказ номер " << i+1 << "\n";
						Vec[i].seeOrder();
						cout << endl;
					}
				}
				if (!shown)cout << "В системе отсутствуют заказы в работе.\n";
				break;
			}
			case 4: {
				bool shown = false;
				for (int i = 0; i < (int)Vec.size(); i++) {
					if (Vec[i].getState() == 2 && Vec[i].getOrdName() == Users[OurUserNum].getName())
					{
						if (shown)cout << "----------------------------------------\n\n"; shown = true;
						cout << "Заказ номер " << i+1 << "\n";
						Vec[i].seeOrder();
						cout << endl;
					}
				}
				if (!shown)cout << "В системе отсутствуют выполненные заказы.\n";
				break;
			}
			case 5: {
				if ((int)Vec.size() == 0) { 
					cout << "В базе отсутствуют заказы.\n"; 
					break; 
				}
				cout << "Введите номер заказа для редактирования:  ";
				int redac;
				Inp::InputIntDiapason(redac, 1, (int)Vec.size());
				redac--;
				if (Vec[redac].getOrdName() != Users[OurUserNum].getName())cout << "Этот заказ принадлежит другому пользователю\n";
				if (Vec[redac].getState() > 0)cout << "Этот заказ уже был принят. Невозможно редактировать.\n";
				cout << "Вы хотите редактировать тип ювелирного украшения в заказе? Введите 1/0:  ";
				int ch;
				Inp::InputIntDiapason(ch, 0, 1);
				if (ch) {
					Users[OurUserNum].setMoney(Users[OurUserNum].getMaoney() + Vec[redac].getOrderPrice());
					this->Vec[redac].createOrder(Users[OurUserNum]);
				}
				else {
					Users[OurUserNum].setMoney(Users[OurUserNum].getMaoney() + Vec[redac].getOrderPrice()); 
					this->Vec[redac].redactOrd();
					Users[OurUserNum].setMoney(Users[OurUserNum].getMaoney() - Vec[redac].getOrderPrice());
				}
				break;
			}
			case 6: {
				if ((int)Vec.size() == 0) {
					cout << "В базе отсутствуют заказы. Невозможно удалить.\n";
					break;
				}
				cout << "Введите номер заказа для удаления:  ";
				int redac;
				Inp::InputIntDiapason(redac, 1, (int)Vec.size());
				redac--;
				if (Vec[redac].getOrdName() != Users[OurUserNum].getName()) {
					cout << "Этот заказ принадлежит другому пользователю. Невозможно удалить.\n";
					break;
				}
				if (Vec[redac].getState() > 0) {
					cout << "Этот заказ уже был принят. Невозможно удалить.\n";
					break;
				}
				vector<Order>::iterator del = Vec.begin();
				del += redac;
				Vec.erase(del);
				break;
			}
			case 7: {
				cout << "Баланс:  " << Users[OurUserNum].getMaoney() << " руб.\n";
				break;
			}
			case 8: {
				cout << "На какую сумму вы хотите пополнить баланс?";
				int a;
				Inp::InputIntDiapason(a, 1, 5000);
				Users[OurUserNum].setMoney(Users[OurUserNum].getMaoney() + a);
				break;
			}
			case 9: {
				if ((int)Vec.size() == 0) {
					cout << "В базе отсутствуют заказы. Невозможно просмотреть.\n";
					break;
				}
				cout << "Введите номер заказа для просмотра:  ";
				int redac;
				Inp::InputIntDiapason(redac, 1, (int)Vec.size());
				redac--;
				if (Vec[redac].getOrdName() != Users[OurUserNum].getName()) {
					cout << "Этот заказ принадлежит другому пользователю. Невозможно просмотреть.\n";
					break;
				}
				Vec[redac].seeOrder();
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

class AbstractMenu {
protected:
	virtual void Menu() = 0;
};

class user {
	int hash = 0;   // пароль в виде хеша
	string password = ""; // пароль
	string username = ""; // имя
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
	friend ostream& operator <<(ostream& s, user& U) {
		char Un[FileBufSize];
		strcpy_s(Un, U.username.c_str());
		s.write(Un, sizeof(Un));
		s.write((char*)&U.hash, sizeof((char*)&U.hash));
		return s;
	}
	friend istream& operator >>(istream& s, user& U) {
		char Un[FileBufSize];
		U.username = "";
		U.password = "";
		s.read(Un, sizeof(Un));
		U.username = Un;
		s.read((char*)&U.hash, sizeof((char*)&U.hash));
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
	}
};

class loginMenu : public AbstractMenu {
	user OurUser;
	bool Entered = 0;
public:
	void delUser() {
		fstream file;
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
		file >> Buf;
		while (true) {
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
	void addUser() {
		fstream file;
		int ch;         // Выбор пункта меню
		bool cy = true; // Цикл ввода
		while (cy) {
			cout << "Вы хотите добавить пользователя? Введите 1/0\n";
			Inp::InputIntDiapason(ch, 0, 1);
			if (ch == 1) {
				file.open("users.dat", ios::in | ios::out | ios::binary);
				file.seekp(0);
				bool HasDatUser = false;
				user ne;
				user compare;
				ne.SetUser();
				while (file.eof()) {
					file >> compare;
					if (compare.compareName(ne) == 1)HasDatUser = true;
				}
				if (HasDatUser) {
					cout << "Пользователь с таким именем уже существует. Невозможно добавить\n";
				}
				else {
					file.seekg(0, ios::end);
					file << ne;
					cout << "Новый пользователь добавлен.\n";
					cy = false;
				}
				file.close();
			}
			else
			{
				cy = false;
			}
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
			OurUser.SetUser();
			file << OurUser;
			cout << "Добавленный вами пользователь будет являться мастером.\n";
			Entered = 1;
			file.close();
		}
		else {
			int cho;
			while (!Entered) {
				cout << "Добавьте пользователя или войдите в аккаунт. Введите 1/0:  ";
				Inp::InputIntDiapason(cho, 0, 1);
				if (cho == 0) {
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
								cout << "Вход успешен!\n";
								OurUser.setUsername(Input.GetName());
								Entered = 1;
								break;
							}
						}
						if (file.eof() && cycle == true) {
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
				else {
					addUser();
				}
			}
		}
		system("pause");
	}
	void seeUsers() {
		fstream file;
		user ShowUser;
		file.open("users.dat", ios::in | ios::out | ios::binary);
		file.seekp(0);
		int num = 1;
		while (!file.eof()) {
			file >> ShowUser;
			if (!file.eof()) cout << num++ << " - " << ShowUser.GetName() << endl;
		}
		file.close();
		system("pause");
	}
	void Menu() {
		fstream file;
		ofstream a("users.dat", ios::app);
		a.close();
		if (!Entered) {
			login();
		}
		if (!Entered) {
			cout << "Ок\n";
			exit(2);
		}
		while (true) {
			int choice;
			system("cls");
			cout << "Вы вошли в систему как " << OurUser.GetName() << ", выберите пункт меню : \n";
			cout << "1 - Создать аккаунт\n";
			cout << "2 - Войти в аккаунт\n";
			cout << "3 - Перейти к ювелирному магазину\n";
			cout << "0 - Выйти из программы\n";
			Inp::InputInt(choice);
			switch (choice) {
			case 1: {
				addUser();
				break;
			}
			case 2: {
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
							cout << "Вход успешен!\n";
							OurUser.setUsername(Input.GetName());
							Entered = 1;
							break;
						}
					}
					if (file.eof() && cycle == true) {
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
					break;
				}
				break;
			}
			case 3: {
				MainJewelryMenu B;
				B.MainMenu(OurUser.GetName());
				break;
			}
			case 4: {
				int pss = 0;
				cout << "Для доступа к данной функции необходим пароль администратора. Введите пароь:  ";
				Inp::InputInt(pss);
				if (pss == LoginMenuPassword) {
					seeUsers();
					delUser();
				}
				else {
					cout << "Неверный пароль.\n";
				}
				break;
			}
			case 5: {
				int pss = 0;
				cout << "Для доступа к данной функции необходим пароль администратора. Введите пароь:  ";
				Inp::InputInt(pss);
				if (pss == LoginMenuPassword) {
					seeUsers();
				}
				else {
					cout << "Неверный пароль.\n";
				}
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

int main()
{
	system("chcp 1251");
	system("cls");
	SmartPointer<loginMenu> a(new loginMenu);
	a->Menu();
}