#include <iostream>
#include <fstream>
#include <ctype.h>
#include <cstring>
#include <windows.h>
#include <conio.h>
#include<stdlib.h>
#include <climits>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class people {
public:
	char mid[10], fname[20], lname[20], phn[15], ofphn[15], area[20], occ[30], email[50], buffer[200];
}p;

vector < vector < string > > hashTable;

void write() {
	fstream f1;
	int i;
	f1.open("address.txt", ios::app);
	if (!f1) {
		cout << "\nCannot open the file in write mode";
		exit(1);
	}
	cout << "\nEnter your first name: ";
	cin >> p.fname;
	cout << "\nEnter your last name: ";
	cin >> p.lname;
	cout << "\nEnter your ID: ";
	cin >> p.mid;
	cout << "\nEnter your phone number: ";
	cin >> p.phn;
	cout << "\nEnter your office phone number: ";
	cin >> p.ofphn;
	cout << "\nEnter the area which you reside in: ";
	cin >> p.area;
	cout << "\nEnter your occupation: ";
	cin >> p.occ;
	cout << "\nEnter your email-ID: ";
	cin >> p.email;

	strcpy(p.buffer, p.fname);
	strcat(p.buffer, "|");
	strcat(p.buffer, p.lname);
	strcat(p.buffer, "|");
	strcat(p.buffer, p.mid);
	strcat(p.buffer, "|");
	strcat(p.buffer, p.phn);
	strcat(p.buffer, "|");
	strcat(p.buffer, p.ofphn);
	strcat(p.buffer, "|");
	strcat(p.buffer, p.area);
	strcat(p.buffer, "|");
	strcat(p.buffer, p.occ);
	strcat(p.buffer, "|");
	strcat(p.buffer, p.email);
	strcat(p.buffer, "\n");
	f1 << p.buffer;
	f1.close();
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void welcome() {
	system("cls");
	//gotoxy(50, 100);
	cout << "\nWelcome to Blah";
	//gotoxy(70, 80);
	cout << "\nAddress Management Software";
	//gotoxy(80,100);
	cout << "\nEnter To Continue..";
	getch();
	return;
}

int hashFunc(char *id) {
	char set[10];
	int sum = 0, index;
	for (int i = 1;i <= strlen(id);i++)
		sum += ((int)id[i] * i);
    index = sum % 50;
    //Linear Probing
    //  while(hashTable[index][1] != "empty")
    //     index = (index + 1) % 50;
	return index;
}

void unpack() {
	fstream f3, f4, f5;
	int index, i, j;
	f3.open("address.txt", ios::in);
	f4.open("hash.txt", ios::out);
	if (!f3) {
		cout << "\nCannot open file";
		exit(1);
	}
	if (!f4) {
		cout << "\nCannot open file";
		exit(1);
	}
	while (!f3.eof())
	{
		f3.getline(p.fname, 20, '|');
		f3.getline(p.lname, 20, '|');
		f3.getline(p.mid, 10, '|');
		f3.getline(p.phn, 15, '|');
		f3.getline(p.ofphn, 15, '|');
		f3.getline(p.area, 20, '|');
		f3.getline(p.occ, 30, '|');
		f3.getline(p.email, 50, '\n');

		index = hashFunc(p.mid);

        hashTable[index][1]=p.fname;
        hashTable[index][2]=p.lname;
        hashTable[index][3]=p.mid;
        hashTable[index][4]=p.phn;
        hashTable[index][5]=p.ofphn;
        hashTable[index][6]=p.area;
        hashTable[index][7]=p.occ;
        hashTable[index][8]=p.email;

		f4 << index << "|" << p.fname << "|" << p.lname << "|" << p.mid << "|" << p.phn << "|" << p.ofphn << "|" << p.area << "|" << p.occ << "|" << p.email << "\n";
	}
	f3.close();
	f4.close();
}

void display() {
    for(int i=1;i<=50;i++) {
        for(int j=1;j<=8;j++) {
            //cout<<i<<"\t";
            cout<<hashTable[i][j];
            cout<<"\t";
        }
        cout<<endl;
    }      
}

void search() {
    char id[10];
    cout<<"\nEnter your ID: ";
    cin>>id;
    int index = hashFunc(id);
    // while(hashTable[index][3] != id and hashTable[index][1] != "empty")
    //     index = (index + 1) % 50;
    if(hashTable[index][1] != "empty") {
        cout <<"Record found." << endl;
        for(int i=1;i<=8;i++)
            cout<<hashTable[index][i]<<"\t";
        return;
    }
    else
        cout <<"Record not found." << endl;
}

int main() {
	int ch;
    hashTable.resize(51, vector < string >(9, "empty"));
	for (;;) {
		cout << "\nEnter your choice: ";
		cin >> ch;

		switch (ch)
		{
		case 1:
			write();
			break;
		case 2:
			unpack();
            display();
			break;
        case 3:
            unpack();
            search();
		default:
			break;
		}
    }
    system("pause");
    return 0;
}