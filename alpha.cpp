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
	int sum = 0, index;
	for (int i = 0;i < strlen(id);i++) {
		sum += ((int)id[i] * (i+1));
	}
    index = sum % 50;
	return index;
}

void unpack() {
	fstream f3, f4;
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
		if(hashTable[index][1] == "-")
			goto label1;
		while(hashTable[index][1] != "-")
			index = (index+1) % 50;

        label1: 
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

void modify() { 
	people obj[50];
	fstream f3; 
	char id[10]; 
	int i,j;  
	f3.open("address.txt",ios::in); 
 
	if(!f3) { 
		cout<<"Unable to open the file in I/P mode"; 
		exit(1); 
	} 
	cout<<"\nEnter the ID of the record to be modified\n"; 
	cin>>id; 
	i=0; 
  
	while(!f3.eof()) { 
		f3.getline(obj[i].fname, 20, '|');
		f3.getline(obj[i].lname, 20, '|');
		f3.getline(obj[i].mid, 10, '|');
		f3.getline(obj[i].phn, 15, '|');
		f3.getline(obj[i].ofphn, 15, '|');
		f3.getline(obj[i].area, 20, '|');
		f3.getline(obj[i].occ, 30, '|');
		f3.getline(obj[i].email, 50, '\n'); 
		i++; 
	} 
	for(j=0;j<i;j++) { 
		if(strcmp(id,obj[j].mid)==0) { 
			cout<<"Record Found"<<endl;
			cout<<"\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
			cout<<"\nThe old values of the record with ID "<<id<<" are\n"; 
			cout<<"First Name= "<<obj[j].fname<<"\nLast Name= "<<obj[j].lname<<"\nID= "<<obj[j].mid<<"\nPhone Number= "<<obj[j].phn<<"\nOffice Phone Number= "<<obj[j].ofphn<<"\nArea= "<<obj[j].area<<"\nOccupation= "<<obj[j].occ<<"\nEmail ID= "<<obj[j].email<<"\n";
			cout<<"\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"; 
			cout<<"\nEnter the new values"; 
			cout<<"\nFirst Name= ";cin>>obj[j].fname; 
			cout<<"Last Name= ";cin>>obj[j].lname; 
			cout<<"ID= ";cin>>obj[j].mid; 
			cout<<"Phone Number= ";cin>>obj[j].phn; 
			cout<<"Office Phone Number= ";cin>>obj[j].ofphn;
			cout<<"Area= ";cin>>obj[j].area;
			cout<<"Occupation= ";cin>>obj[j].occ;
			cout<<"Email= \n";cin>>obj[j].email; 
			break; 
		} 
	} 
	if(j==i) { 
 		cout<<"\n The record with ID "<<id<<" is not present"; 
		exit(0); 
	} 
	f3.close(); 
	fstream out1; 

	out1.open("address.txt",ios::out | ios::trunc);
	for(j=0;j<i;j++) { 
		out1<<obj[j].fname<<"|"<<obj[j].lname<<"|"<<obj[j].mid<<"|"<<obj[j].phn<<"|"<<obj[j].ofphn<<"|"<<obj[j].area<<"|"<<obj[j].occ<<"|"<<obj[j].email<<'\n'; 
	}
	out1.close(); 
} 

void deletion() {
	fstream f7, f8;
	char id[10];
	people obj1[50];
	int i=0;
	f7.open("address.txt", ios::in);

	if(!f7) {
		cout<<"Cannot open file";
		exit(1);
	}

	cout<<"\nEnter the ID of the record you wish to delete: ";
	cin>>id;

	while(!f7.eof()) {
		f7.getline(obj1[i].fname, 20, '|');
		f7.getline(obj1[i].lname, 20, '|');
		f7.getline(obj1[i].mid, 10, '|');
		f7.getline(obj1[i].phn, 15, '|');
		f7.getline(obj1[i].ofphn, 15, '|');
		f7.getline(obj1[i].area, 20, '|');
		f7.getline(obj1[i].occ, 30, '|');
		f7.getline(obj1[i].email, 50, '\n');

		if(strcmp(obj1[i].mid, id)==0)
			continue;
		strcpy(obj1[i].buffer, obj1[i].fname);
		strcat(obj1[i].buffer, "|");
		strcat(obj1[i].buffer, obj1[i].lname);
		strcat(obj1[i].buffer, "|");
		strcat(obj1[i].buffer, obj1[i].mid);
		strcat(obj1[i].buffer, "|");
		strcat(obj1[i].buffer, obj1[i].phn);
		strcat(obj1[i].buffer, "|");
		strcat(obj1[i].buffer, obj1[i].ofphn);
		strcat(obj1[i].buffer, "|");
		strcat(obj1[i].buffer, obj1[i].area);
		strcat(obj1[i].buffer, "|");
		strcat(obj1[i].buffer, obj1[i].occ);
		strcat(obj1[i].buffer, "|");
		strcat(obj1[i].buffer, obj1[i].email);
		strcat(obj1[i].buffer, "\n");
		i++;
	}
	f7.close();
	// f8.open("address.txt",ios::out | ios::trunc);
	// for(int j=0;j<i;j++) { 
	// 	f8<<obj1[j].fname<<"|"<<obj1[j].lname<<"|"<<obj1[j].mid<<"|"<<obj1[j].phn<<"|"<<obj1[j].ofphn<<"|"<<obj1[j].area<<"|"<<obj1[j].occ<<"|"<<obj1[j].email<<'\n'; 
	// 	// f8<<obj1[j].buffer; 
	// }
	// f8.close();

	fstream out1; 

	out1.open("address.txt",ios::out | ios::trunc);
	for(int j=0;j<i;j++) { 
		out1<<obj1[j].fname<<"|"<<obj1[j].lname<<"|"<<obj1[j].mid<<"|"<<obj1[j].phn<<"|"<<obj1[j].ofphn<<"|"<<obj1[j].area<<"|"<<obj1[j].occ<<"|"<<obj1[j].email<<'\n'; 
	}
	out1.close();
}

void display() {
    for(int i=1;i<=50;i++) {
		cout<<"\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
		cout<<"\nIndex= "<<i<<"\n";
        cout<<"First Name= "<<hashTable[i][1]<<"\nLast Name= "<<hashTable[i][2]<<"\nID= "<<hashTable[i][3]<<"\nPhone Number= "<<hashTable[i][4]<<"\nOffice Phone Number= "<<hashTable[i][5]<<"\nArea= "<<hashTable[i][6]<<"\nOccupation= "<<hashTable[i][7]<<"\nEmail ID= "<<hashTable[i][8];
        cout<<"\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------------	";
    }      
}

void search() {
    char id[10];
    cout<<"\nEnter your ID: ";
    cin>>id;
    int index = hashFunc(id);
	cout<<index;

    while(hashTable[index][3] != id && hashTable[index][1] != "-")
        index = (index + 1) % 50;
    if(hashTable[index][1] != "-") {
        cout << "\nRecord found." << endl;
		cout<<"\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
         cout<<"First Name= "<<hashTable[index][1]<<"\nLast Name= "<<hashTable[index][2]<<"\nID= "<<hashTable[index][3]<<"\nPhone Number= "<<hashTable[index][4]<<"\nOffice Phone Number= "<<hashTable[index][5]<<"\nArea= "<<hashTable[index][6]<<"\nOccupation= "<<hashTable[index][7]<<"\nEmail ID= "<<hashTable[index][8];
		 cout<<"\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        return;
    }
    else
        cout << "\nRecord not found." << endl;
}

int main() {
	int ch;
    hashTable.resize(51, vector < string >(9, "-"));
	for (;;) {
		cout<<"\n1. Add Records\n2. Display Records\n3. Search Record\n4. Modify\n";
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
			break;
		case 4:
			modify();
			break;
		case 5:
			deletion();
			break;
		default:
			break;
		}
    }
	system("pause");
    return 0;
}
