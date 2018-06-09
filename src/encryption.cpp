// THIS IS A SIMPLE ENCRYPTING PROGRAM
// IT READS TEXT FROM original.txt
// AND INCREASE VALUE OF EVERY LETTER
// FOR VALUE OF KEY THAT YOU HAVE ENTERED

// note that when you create an array,
// c++ automaticly stores some values in it,
// so maybe condition in line 79 won't work properly

#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
using namespace std;


int main()
{
    const int x = 1000;  // must be at least the size of characters in text file
    char text[x];
    char answer;
    bool verify = false;

    int intkey;
    char charkey;

    // READ FROM FILE
    ifstream myfile;
    myfile.open("original.txt");
    if(myfile.fail()) {
        cout << "Error! Couldn't open the file.";
        exit(1);
    }
    else {
        for(int i=0; i<x; i++) {
            myfile >> text[i];
        }
    }

    ofstream newfile;
    newfile.open("encrypted.txt");
    if(newfile.fail()) {
        cout << "Error! Couldn't open the file.";
        exit(1);
    }

    do {
        cout << "Do you want a number(N) or a letter(L) for your key? " << endl;
        // MUST BE A NUMBER (it's not finished)
        cin >> answer;

        switch(answer) {
            case 'n':
            case 'N':
                cout << "Now enter your key: " << endl;
                cin >> intkey;
                verify = true;

                for(int i=0;i<x;i++){

                    // ASCII A=65 , Z=90
                    if( text[i] >= 65 && text[i] <= 90 ) {

                        if( (text[i] + intkey) <= 90 )
                            text[i] += intkey;
                        else
                            text[i] = (intkey - (91 - text[i])) + 65;
                    }

                    // ASCII a=97 , z=122
                    else if( text[i] >= 97 && text[i] <= 122 ) {

                        if( (text[i] + intkey) <= 122 )
                            text[i] += intkey;
                        else
                            text[i] = (intkey - (123 - text[i])) + 97;
                    }
                    newfile << text[i];
                    if(text[i+1] == '\0')
                        break;
                }

                break;
            case 'l':
            case 'L':
                cout << "Now enter your key: " << endl;
                cin >> charkey;
                verify = true;
                break;
            default:
                cout << "Oops, you haven't typed n or l. Try again!" << endl;
                verify = false;
                break;
        }
    } while(verify == false);



    myfile.close();
    newfile.close();

}
