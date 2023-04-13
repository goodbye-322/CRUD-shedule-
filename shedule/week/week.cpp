#include "Header.h"
//////////////////////////////////////////
void edidionList();
void removeDay();
void checkday();
void swichDay();
void recording();
void reading();
void addD();
void editMenu();
void mainMenu() {//главное меню выбора
	setlocale(LC_ALL, "rus");
	cout << " Просмотр недельного расписания (1)\n Редактирование недельного расписания (2)\n" ;
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
		editMenu();
		system("cls");
		main();
	default:
		cout << " Данного пункта в меню не сущетвует\n";
		system("pause");
		system("cls");
		main();
	}
}
void checkday() {// проверка дней недели
	cout << " Введите номер дня недели\n> "; cin >> dayWeek;
	if (dayWeek > 7 || dayWeek < 1) {
		cout << " Такого дня недели не существует!\n";

		system("pause");
		system("cls");
		main();
	}
}
void addD() {//добавлеение данных без выбора дня
	SetConsoleCP(1251);

	cout << "Введите данные\n> "; cin.get(); getline(cin, arr[dayWeek]);//ввод пользователем данных, их запись по дню недели
	recording();
	SetConsoleCP(866);
	system("cls");
	main();
}
void editMenu() {//добавление данных c выбором дня
	SetConsoleCP(1251);
	checkday();
	swichDay();
	cout << " Добавить(1) Удалить расписание(2)\n> " ; cin >> menuChoose;
	switch (menuChoose)
	{
	case 1:
		addD();
	case 2:
		cout << " Удалить день(1) Удалить пункт дня(2)\n> "; cin >> menuChoose;
		if (menuChoose==1){removeDay();}
		else if (menuChoose == 2) {edidionList();}
		else {
			cout << " Данного пункта в меню не сущетвует" << endl;
			system("pause");
			system("cls");
			editMenu();
		}

	default:
		cout << " Данного пункта в меню не сущетвует" << endl;
		system("pause");
		system("cls");
		main();
	}

}
void reading() {// чтение из файлов
	checkday();
	swichDay();

	myfile.open(path, fstream::in);
	if (myfile.is_open())
	{
		string text;
		cout << endl;
		while (getline(myfile, text)) {
			cout <<" "<< text << endl;
		}
		myfile.close();
		
		int choose;
		cout << "\n Добавить пункты?  Да(1) Нет(2)" << endl; cout << ">"; cin >> choose;
		if (choose == 1) {
			addD();
			
		}
		else {
			system("cls");
			main();
		}
		system("pause");
	}
	else cout << "Не удалось считать данные из файла!";
}
void recording() {//запись в файлы

	ofstream record;
	string text;
	int numberLine = 1;

	setlocale(LC_ALL, "rus");
	swichDay();
	myfile.open(path, fstream::in);
	record.open(path, ofstream::app);

	if (record.is_open())
	{
		while (getline(myfile, text)) {//получение номера в списке
			numberLine++;
		}

		record << numberLine <<") " << arr[dayWeek] << "\n";

		record.close();
		myfile.close();
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
void removeDay() {//удаление файла
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
void edidionList() {//редактирование списка 
	swichDay();

	string text, arrText[99];
	int listZize = 0, deletePoint, newlistZize = 0;
	ofstream record;
	
	myfile.open(path, fstream::in);
	while (getline(myfile, text)) { \
		cout << text << endl;
		listZize++;//получение кол-ва строк в списке
	}
	myfile.close();

	cout << "Введите номер пункта для удаления\n> "; cin >> deletePoint;
	if (deletePoint>listZize){
		cout << "Этого пункта нет";
		system("pause");
		system("cls");
		edidionList();
	}

	myfile.open(path, fstream::in);
	if (myfile.is_open()) {
		
		int i = 0;
		while (getline(myfile, text)) {//копирование строк не попапших под удаление 
			if (i != deletePoint-1){
				text.erase(0, text.find_first_of(")"));
				arrText[i] = text;
			}
			i++;
		}
		myfile.close();
		remove(path.c_str());//удаление старого файла
		record.open(path, ofstream::app);//создание нового 
		if (remove(path.c_str()) && record.is_open()){//записть скопированных строк
			
			for (size_t i = 0; i < listZize; i++){
				if (arrText[i]!="") {
					newlistZize++;
					record << newlistZize << arrText[i] << "\n";
				}
			}
			cout << "Отредактированно\n";
			record.close();
			system("pause");
			system("cls");
			main();
			
		}
		else {
			cout << "Ошибка редактирования";
			system("pause");
			system("cls");
			main();
		}

	}
	else cout << "Не удалось открыть файл для записи!";
	
}