#include <iostream>
#include <string>
using namespace std;
int main(){
    string word = "meatloveteamrampdumblumpweep";
    for(int i = 0; i <= 7*4; i+=4){
        cout << i << " to " << i+4 << " :: ";
        cout << word.substr(i, i+4) << endl;
    }
    return 0;
}