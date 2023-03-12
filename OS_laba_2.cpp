#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <string>
#include <sstream>
#include <ctime>
#include <unistd.h>
#include <io.h>


using namespace std;

// есть: rename, remove, open, close, 
// есть: переименовывание, удаление, открытие (если 3 то норм открыл), закрытие(если 0 то норм закрыл)


void welcome() {
    cout << "Select command date: " << endl;
    cout << "- copy (copy file)" << endl;
    cout << "- move (moving file)" << endl;
    cout << "- get_information (get information: access, weight, time changes)" << endl;
    cout << "- change_access (change access)" << endl;
}

// получаем информацию о файле 
int get_information(string comand ,string file_name) {
    
    int file_descriptor = open(file_name, O_RDONLY);  // открываем файл // O_RDONLY - определяет флаг доступа к файлу в режиме "только для чтения" (read-only). Это означает, что файл может быть только прочитан, но не изменен или записан.
    if (file_descriptor == -1) {
        cout << "Ошибка открытия файла! " << endl;
        return 1;
    }
    
    struct stat file_info; // содержит информацию о файле, такую как размер файла...
    if(fstat(file_descriptor, &file_info) == 0 || stat(file_name, &file_info) == 0 || lstat(file_name, &file_info) == 0 ){

        if (comand == "size")
            cout << "Размер файла: " << file_info.st_size << " байт" << endl;

        if (comand == "right")
            cout << "Права доступа: " << file_info.st_mode << endl;

        if (comand == "time_last_change")
            cout << "Время последнего изменения: " << ctime(&file_info.st_mtime) << endl;
    }
    else 
        cout << "Ошибка при получении информации о файле" << endl;
}




int main() {
    setlocale(LC_ALL, "Russian");
    welcome(); //приветствие 

    //bool Contunue;
    do {

        string str; // сюда будет записана строка, введённая с клавиатуры
        getline(cin, str); // считывания всей строки 
        stringstream ss(str); // создаём поток ввода из строки
        vector<string> comands; // создаём вектор в который будем добавлять слова
        string words; // создаём переменную в которой будет храниться слово
        while (ss >> words) // используем потоковый ввод для разбиения строки на слова 
            comands.push_back(words); // добавляем слово в вектор

        //for (int i = 0; i < comands.size(); ++i) cout << comands[i] << " "; // выводим все слова в векторе 

        // Проверяем есть ли ключ "--help" и выполняем команду с ключом 
        if (comands.size() == 2 && comands[1] == "--help") {
            cout << endl << "yes" << endl;
            map<string, string> double_string;
            string key = comands[1]; // = "--help"
            string value = comands[0]; // = команда (rename, )
            double_string[key] = value;

            // выводим ключ и его значение 
            for (auto i : double_string) {
                cout << "Проверка ключа-значения" << endl;
                cout << "Key: " << i.first << endl;
                cout << "Value: " << i.second << endl;
            }

        }
        // выполняем команды терминала
        if (comands.size() == 3) {
            //if (comands[0] == "rename") {}
            //if (comands[0] == "copy") {}
            //if (comands[0] == "lol") {}
            if (comands[0] == "get") {
                if (comands[1] == "size" || comands[1] == "right" || comands[1] == "time_last_change") {
                    get_information(comands[1], comands[2]);
                    
                }/*
                if (comands[1] == "right") {
                    get_information();
                }
                if (comands[1] == "tmchange") {
                    get_information();
                }*/
                else
                    cout << "Такой команды не существует! " << endl;

            }
        }
        if (comands.size() == 4) {

        }

    } while (true);
    
    return 0;
}


















/* без ключа 
vector<string> comand;
string word;
for (int i = 0; i < 3; ++i) {
    cin >> word;
    comand.push_back(word);
}
cout << comand.size() << endl;
for (int i = 0; i < comand.size(); ++i)
    cout << comand[i] << " ";
*/
/*
vector<string> comand;
string str;
getline(cin, str);

comand.push_back(str);

cout << comand.size() << endl;
cout << str << endl;
for (int i = 0; i < comand.size(); ++i)
    cout << comand[i];


if (comand[comand.size()-1] == "--help")
    cout << "Yes" << '\n';*/


    /*
    string str ;
    string free = "";
    vector<string> text;
    getline(cin, str);
    cout << str.length()<<'\n';
    for (int i = 0, count = 0; i < str.length()-1; ++i) {


        if (str[i] != ' ' && str[i+1] != ' ')
            if (str[])
            */
            /*
            if (str[i] != ' ' ) {
                free += str[i] + str[count];
            }
            else {
                ++count;
                text.push_back(free);
                cout << free << endl;
                free = "";
            }*/
            /*
            }
            for (int i = 0; i < text.size(); ++i) {
                cout << text[i] << " ";

            }
            cout << endl;*/



            /*
            map <string, string> str;
            string key;
            string comand;

            */

            /*

            // самая рабочая
            map <string, vector<string>> str;


            //map <vector<string>, string > mp;

            string key;
            vector<string> comand;


            string word;
            for (int i = 0; i < 2; ++i) {
                cin >> word;
                comand.push_back(word);
            }
            cin >> key;

            cout << "----------------------------------" << '\n';

            str[key] = comand;


            //mp[comand] = key;
            //cout << comand[];


            for (auto i : str) {
                cout << "Key: ";

                cout << i.first << '\n';
                cout << "value: ";
                for (auto p : i.second) {
                    cout << p << " ";
                }
            }
            if (str[key] == str["--help"])
                cout << "Yes" << '\n';
                */


                /*
                for (auto i : mp) {
                    cout << "Key: ";
                    for (auto p : i.first) {
                        cout << p << " ";
                    }
                    cout << '\n';
                    cout << "value: " << i.second;
                }*/

                /*
                string key_find = "--help";


                if (mp[key_find] != mp[comand]) {
                    cout << "key not found" << '\n';
                }*/

                /*

                string word;
                vector<string> comand;
                for (int i = 0; i < 3; ++i) {
                    cin >> word;
                    comand.push_back(word);
                }
                if (comand[1] == "txt")
                    cout << "Yes";
                */












                /*welcome();
                    //char action;
                    //cin >> action;
                    //cout << action << '\n';

                    string old_file_name = "File_name.txt";
                    string new_file_name = "NEw_file";

                    //cin >> old_file_name;
                    //cin >> new_file_name;

                    rename(old_file_name.c_str(), new_file_name.c_str());

                    string file_name = "example.txt";

                    // Открытие файла для записи
                    ofstream outfile(file_name);

                    if (outfile.is_open()) {
                        // Запись данных в файл
                        outfile << "Привет, мир!" << endl;

                        // Закрытие файла
                        outfile.close();

                        cout << "Файл успешно создан" << endl;
                    }
                    else {
                        cout << "Не удалось создать файл" << endl;
                    }

                    */
                    //remove("example");
