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

string repeatReturn(string rep, int t){
	string re = "";
	for(int i = 0; i < t; i++)
		re += rep;
	return re;
}
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
	int dudsRm = 0;
    string words[11];
    string word;
    string addys[34];
    string content = "";
    string commands[16];
    char miscContent[24] = {'!', '@', '#', '$', '%', 
							'^', '&', '*', ':', ';', 
							',', '.', '?', '-', '+', 
							'=', '"', '\'', '(', ')',
							'[', ']', '{', '}'};
	char miscHelp[6]      = {'[', ']', '{', '}', '(', ')'};
public:
    GUI() {
        for(int i = 0; i < 16; i++)
            commands[i] = " ";
        commands[15] = ">";
        
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
        
        test("Content generating");
        int indexWord = 0;
        for(int i = 0; i < 12*17*2 + 11; i++){
            if(i % 34 == 0 && i < 408 - level && indexWord < 11){
                content += words[indexWord];
                i += level;
                indexWord++;
            }
            else
				content += miscContent[genRand(24)];
        }
		while(content.length() < 408)
			content += miscContent[genRand(24)];
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
            cout << addys[i] << " " <<
                content.substr(i*12, 12) << " " <<
                addys[i + 16] << " " <<
                content.substr(i*12+204, 12) <<
                " ";
            if(i < 15)
                cout << commands[i];
            if(i != 16)
                cout << endl;
        }
		test(content);
        test(to_string(content.length()));
    }
    void commandHandler(string opt){
        if(opt == word){
            getCommand(true, "Exact match!");
            getCommand(true, "Please wait");
            getCommand(true, "while system");
            getCommand(true, "is accessed.");
        }
		else if(opt[0] == '[' || opt[0] == '{' || opt[0] == '('){
			int miscHelpIndex = 0;
			bool hasHelp = false;
			for(int i = 0; i < 6; i+=2)
				if(opt[0] == miscHelp[i])
					miscHelpIndex = i;
			if(opt[opt.length() - 1] == miscHelp[miscHelpIndex + 1]){
				for(int i = 0; i < content.length() - opt.length(); i++){
					if(opt == content.substr(i, opt.length())){
						hasHelp = true;
						//getCommand(true, "bouta for");
						for(int o = i; i < opt.length() + i; i++){
							//getCommand(true, "entered for");
							if(!((int)content[o] >= (int)'A' && (int)content[o] <= (int)'Z'))
								content.replace(o, 1, ".");
						}
						//content.replace(i, opt.length(), repeatReturn(".", opt.length()));
						getCommand(true, "bouta break");
						break;
					}
				}
			}
			if(hasHelp){
				if(genRand(2) == 0 || dudsRm >= 10){
					attempts = 4;
					getCommand(true, "Allowance");
					getCommand(true, "replenished.");
				}
				else{
					int rmIndex = genRand(11);
					while(words[rmIndex] == word)
						rmIndex = genRand(11);
					for(int i = 0; i < content.length() - level; i++)
						if(words[rmIndex] == content.substr(i, level))
							content.replace(i, level, repeatReturn(".", level));
					getCommand(true, "Dud removed.");
					dudsRm++;
				}
			}
			else{
				getCommand(true, "Entry denied.");
				attempts--;
			}
		}
		else{
			if(attempts > 1){
				attempts--;
			getCommand(true, "Entry denied.");
			int numCharCorrect = 0;
			for(int i = 0; i < opt.length(); i++)
				if(word[i] == opt[i])
				numCharCorrect++;
			getCommand(true, to_string(numCharCorrect) + "/" + to_string(level) + " correct.");
			}
			else{
				attempts = 0;
				getCommand(true, "SYSTEM LOCK");
			}
		}
    }
    bool getCommand(bool overrideOpt, string opt){
        if(!overrideOpt){
			cout << ">";
            cin >> opt;
		}
        
        for(int i = 0; i < 14; i++)
            commands[i] = commands[i + 1];
        commands[14] = ">";
        commands[14] += opt;
        if(!overrideOpt)
            commandHandler(opt);
		return attempts == 0;
    }
};

int main() {
	clear();
    srand(time(0));
    GUI game;

    while(true){
        game.print();
        if(game.getCommand(false, ""))
			break;
    }
	clear();
	repeat("\n", 5);
    typer("                  TERMINAL LOCKED");
	cout << endl;
	typer("          PLEASE CONTACT AN ADMINISTRATOR");
	repeat("\n", 5);
	return 0;
}
