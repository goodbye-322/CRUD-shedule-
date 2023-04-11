#include "Header.h"
//////////////////////////////////////////
void removeDay();
void checkday();
void swichDay();
void editionD();
void recording();
void reading();
void editionD();
void editionW();
void mainMenu() {//главное меню выбора
	setlocale(LC_ALL, "rus");
	cout << " Для просмотра расписания на неделю, нажмите - 1\n Для редактирования расписания на неделю, нажмите - 2" << endl;
	cout << "> "; cin >> menuChoose;
}    

/////////////////////////////////////////

int main()
{
	setlocale(LC_ALL, "rus");
	mainMenu();
	switch (menuChoose)
	{
	case 1:
		reading();
		
	case 2:
		editionW();
		system("cls");
		main();
	default:
		cout << " Данного пункта в меню не сущетвует" << endl;
		system("pause");
		system("cls");
		main();
	}
}
void checkday() {// проверка дней недели
	if (dayWeek > 7 || dayWeek < 1) {
		cout << " Такого дня недели не существует!\n" << endl;
		
		system("pause");
		system("cls");
		main();
	}
}
void editionD() {//запись без выбора дня
	SetConsoleCP(1251);
	
		cout << " Введите список дел на " << dayWeek << "й день недели" << endl;
		cout << "> "; cin.get(); getline(cin, arr[dayWeek]);
		cout << "************" << endl;
		recording();
		SetConsoleCP(866);
		system("cls");
		main();
}	
void editionW() {//редактирование c выбором дня
	SetConsoleCP(1251);
		cout << " Введите номер дня недели" << endl;
		cin >> dayWeek;
		checkday();
		swichDay();
		cout << " Удалить расписание(1) Добавить(2)" << endl; cin >> menuChoose;
		switch (menuChoose)
		{
		case 1:
			removeDay();
		case 2:
			cout << " Введите список дел на " << dayWeek << "й день недели" << endl;
			cout << "> "; cin.get(); getline(cin, arr[dayWeek]);
			cout << "************" << endl;
			recording();
			SetConsoleCP(866);
			system("cls");
			main();
		default:
			system("cls");
			main();
			break;
		}
		
}
void reading() {// чтение из файлов
	cout << " Введите номер дня недели" << endl;
	cout << "> "; cin >> dayWeek;
	checkday();
	swichDay();

	myfile.open(path, fstream::in );
	myfile.close();
	myfile.open(path, fstream::in);
	if (myfile.is_open())
	{
		string text;
		
		getline(myfile, text);
		while (text!="") {
			cout << text << endl;
			getline(myfile, text);
				
		}
		
		int choose;
		cout << "\n Добавить дела ? \n 1.(Да)\t2.(Нет)" << endl; cout << ">"; cin >> choose; cout << "************" << endl;
		if (choose == 1) {
			editionD();
		}
		else {
			system("cls");
			main();
		}

		myfile.close();
		system("pause");
	}
	else cout << "Не удалось считать данные из файла!";
}
void recording() {//запись в файлы
	ofstream record;
	setlocale(LC_ALL, "rus");
	swichDay();
	record.open(path, ofstream::app);
	if (record.is_open())
	{
		record << "----------------------------------\n";
		record << arr[dayWeek] << "\n";

		record.close();
	}
	else cout << "Не удалось открыть файл для записи!";
}
void swichDay() { //выбор дня недели с созданием файла
	ofstream record;
	switch (dayWeek)
	{
	case 1:path = "monday.txt";
		record.open(path, ofstream::app);
		break;
	case 2:path = "tuesday.txt"; 
		record.open(path, ofstream::app);
		break;
	case 3:path = "wednesday.txt"; 
		record.open(path, ofstream::app);
		break;
	case 4:path = "thursday.txt"; 
		record.open(path, ofstream::app);
		break;
	case 5:path = "friday.txt"; 
		record.open(path, ofstream::app);
		break;
	case 6:path = "saturday.txt"; 
		record.open(path, ofstream::app);
		break;
	case 7:path = "sunday.txt"; 
		record.open(path, ofstream::app);
		break;

	default:
		break;
	}
}
void removeDay() {
	swichDay();
	remove(path.c_str());
	if (remove(path.c_str())) {
		cout << "Файл " << path << " удален\n";
	}
	else {
		cout << "Ошибка удаления файла \n";
	}
	system("pause");
	system("cls");
	main();
}