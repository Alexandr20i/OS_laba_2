#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <string>
#include <sstream>
#include <ctime>
//#include <unistd.h> //хуй знает, походу на window не работает эта хуйня 
#include <io.h>
#include <set>


using namespace std;

// Sanyoooooooooooooooooooooooooooooooooooooooooooooooooook
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
void get_information(string comand ,const string& file_name) {
    
    int file_descriptor = _open(file_name.c_str(), O_RDONLY);  // открываем файл в ubuntu: open(file_name.c_str(), O_RDONLY) // O_RDONLY - определяет флаг доступа к файлу в режиме "только для чтения" (read-only). Это означает, что файл может быть только прочитан, но не изменен или записан.
    if (file_descriptor == -1) // выходим из функции, при неудачном чтении файла
        cout << "Ошибка открытия файла! " << endl; return;
    
    struct stat file_info; // содержит информацию о файле, такую как размер файла...
    if(fstat(file_descriptor, &file_info) == 0 || stat(file_name.c_str(), &file_info) == 0 /* || lstat(file_name.c_str(), &file_info) == 0* не работает на windows */) {

        if (comand == "size")
            cout << "Размер файла: " << file_info.st_size << " байт" << endl;

        if (comand == "right")
            cout << "Права доступа: " << file_info.st_mode << endl;

        if (comand == "time_last_change")
            cout << "Время последнего изменения: " << ctime(&file_info.st_mtime) << endl;
        _close(file_descriptor); // в ubuntu писать: close(file_descriptor);
    }
    else 
        cout << "Ошибка при получении информации о файле" << endl;
}


/*
0 - никаких прав;
1 - только выполнение;
2 - только запись;
3 - выполнение и запись;
4 - только чтение;
5 - чтение и выполнение;
6 - чтение и запись;
7 - чтение запись и выполнение.
*/
// изменяем права доступа файла
void change_mod(string comand, string file_name) {
    chmod(file_name.c_str(), stoi(comand));
}

bool control_input_chmod(const string& comand) {

    //set <string> list {"---", "--x", "-w-", "-wr", "r--", "r-w", "rw-", "rwx"};
    //return (list.find(comand) != list.end()) ? 1 : 0;

    int num = stoi(comand);
    int count = 0;
    bool flage = true;
    while (num > 0) {
        if (num % 10 >= 0 && num % 10 < 8)
            num /= 10;
        else
            cout << "Неверный режим: " + comand << endl;  return 0;
    }

    return 1;
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
            
            if (comands[0] == "get") {
                if (comands[1] == "size" || comands[1] == "right" || comands[1] == "time_last_change") 
                    get_information(comands[1], comands[2]);
                else
                    cout << "Такой команды не существует! " << endl << "используйте --help " << endl;
            }


            if (comands[0] == "chmod") {
                //cout << "надо так: chmod 777 file.txt" << endl;
                //cout << "не надо так ) : chmod ugo+rwx file.txt" << endl;
                if (control_input_chmod(comands[1]))
                    change_mod(comands[1], comands[2]);
                else
                    cout << "еблан?!? ";
            }

/*
                if (comands[1] == "---" || comands[1] == "000") {
                    change_mod(comands[1]);
                }
                if (comands[1] == "--x" || comands[1] == "001");
                if (comands[1] == "-w-" || comands[1] == "010");
                if (comands[1] == "-wx" || comands[1] == "011");
                if (comands[1] == "r--" || comands[1] == "100");
                if (comands[1] == "r-x" || comands[1] == "101");
                if (comands[1] == "rw-" || comands[1] == "110");
                if (comands[1] == "rwx" || comands[1] == "111");*/
            
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
