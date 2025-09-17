#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>
#include <fstream>

using namespace std;

bool testing = false;

void test(string x) {
    if (testing)
        cout << x << endl;
}
void repeat(string x, int y) {
    for (int i = 0; i < y; i++)
        cout << x;
}
void delay(int t) {
    this_thread::sleep_for(chrono::milliseconds(t));
}
void typer(string x) {
    for (int i = 0; i < x.length(); i++) {
        cout << x[i];
        delay(0);
    }
}
void clear() {
    //system("cls");
    system("clear");
}
int genRand(int upto) {
    //returns an int n as 0 <= n < upto
    return rand() % upto;
}
string genHex(int x) {
    stringstream ss;
    ss << hex << x;
    string res(ss.str());
    return res;
}

class wordLink {
private:
    class node {
    public:
        string word;
        node* next;
        node(string x) {
            word = x;
            next = nullptr;
        }
    };
    node* head;
    int size;
public:
    wordLink() {
        head = nullptr;
        size = 0;
    }
    void push(string x) {
        size++;
        node* p = new node(x);
        if (head == nullptr)
            head = p;
        else {
            node* b = head;
            while (b->next != nullptr)
                b = b->next;
            b->next = p;
        }
        test("Pushed:");
        test(x);
    }
    string pick() {
        if (size == 0) return ""; // safety
        int spot = genRand(size); // 0 <= spot < size
        node* b = head;
        node* prev = nullptr;
    
        for (int i = 0; i < spot; i++) {
            prev = b;
            b = b->next;
        }
    
        string re = b->word;
    
        if (prev == nullptr) { // removing head
            head = b->next;
        } else {
            prev->next = b->next;
        }
    
        delete b;
        size--;
        test("Picked:");
        test(re);
        return re;
    }

};

class GUI {
private:
    wordLink list;
    int attempts;
    int level;
    string words[11];
    string word;
    string addys[34];
    string content;
    string commands[17];
    char miscContent[18] = {'!', '@', '#', '$', '%', '^', '&', '*', ':', ';', ',', '.', '?', '-', '+', '=', '"', '\''};
public:
    GUI() {
        for(int i = 0; i < 17; i++)
            commands[i] = " ";
        commands[16] = ">";
        
        attempts = 4;
        level = chooseLevel() + 2;
        test("Level Chosen");

        getWords();
        test("Words Grabbed");

        chooseWords();
        test("Words Chosen");

        word = chooseTheWord();
        test("Word Chosen");

        getAddys();
        test("Addys Grabbed");

        test("Level Chosen ::");
        test(to_string(level));
        test("Word List ::");
        for (int i = 0; i < 11; i++)
            test(words[i]);
        test("Addy List ::");
        for (int i = 0; i < 34; i++)
            test(addys[i]);
    }
    int chooseLevel() {
        typer("Select level of difficulty from '1' (least difficult) through '12' (most difficult).");
        int opt;
        cout << "\n>";
        cin >> opt;
        while (opt < 1 || opt > 12) {
            cout << "ERROR - INVALID OPTION\n";
            cout << ">";
            cin >> opt;
        }
        return opt;
    }
    void getWords() {
        string search = to_string(level);
        ifstream in("sortedWordList.txt");
        string curr;
        in >> curr;
        while (curr != search)
            in >> curr;
        while (curr != "END" + search) {
            list.push(curr);
            in >> curr;
        }
    }
    void chooseWords() {
        for (int i = 0; i < 11; i++)
            words[i] = list.pick();
    }
    string chooseTheWord() {
        int chose = genRand(11);
        return words[chose];
    }
    void getAddys() {
        for (int i = genRand(70000), iter = 0; iter < 34; i += 12, iter++) {
            string add = "0x";
            add += genHex(i);
            addys[iter] = add;
        }
    }

    void print() {
        clear();
        cout << "ROBCO INDUSTRIES (TM) TERMLINK PROTOCOL\nENTER PASSWORD NOW\n\n";
        cout << attempts << " ATTEMPT(S) LEFT: ";
        for(int i = 0; i < attempts; i++)
            cout << "@ ";
        cout << "\n\n";
        for(int i = 0; i < 17; i++){
            //12 length for content each
            cout << addys[i] << "  " << addys[i + 16] << " ";
            if(i < 16)
                cout << commands[i];
            if(i != 16)
                cout << endl;
        }
    }
    void commandHandler(string opt){
        
    }
    void getCommand(bool overrideOpt, string opt){
        cout << ">";
        if(!overrideOpt)
            cin >> opt;
        commandHandler(opt);
        for(int i = 0; i < 15; i++)
            commands[i] = commands[i + 1];
        commands[15] = ">";
        commands[15] += opt;
    }
};

int main() {
    srand(time(0));
    GUI game;

    while(true){
        game.print();
        game.getCommand(false, "");
    }
    
	return 0;
}