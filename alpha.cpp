#include <iostream>
#include <fstream>
#include <ctype.h>
#include <cstring>
#include <Windows.h> 
#include <conio.h>
#include<stdlib.h>
#include <climits>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

/*Create users with fields First name, Last name, User ID, Phone number, Office Phone number, Area in which they reside,
Occupation and Email ID.*/
class people {
public:
	char mid[10], fname[20], lname[20], phn[15], ofphn[15], area[20], occ[30], email[50], buffer[200];
}p;

//Create a hash table of size 50 rows representing 50 users and 8 fields.
vector < vector < string > > hashTable;

//Used to set the position of the cursor in the console.
void gotoxy(int x, int y) 
{
  COORD coord;
  coord.Y = y;
  coord.X = x;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*The hash function takes in the User ID as it's argument and computes the index as the summation of product of the
ASCII value of the characters in the ID and the position at which the character is present in the string.*/
int hashFunc(char *id) 
{
	int sum = 0, index;
	for (int i = 0;i < strlen(id);i++) 
		sum += ((int)id[i] * (i+1));
    index = sum % 50;
	return index;
}

/*To check if the address book has 50 records, the limit. If false, records are added to the address book otherwise,
a suitable message is printed for the user*/
int checkOverflow() 
{
	fstream f1;
	int a=0, flag=0;

	f1.open("address1.txt", ios::in);
	if(!f1) 
	{
		cout<<"\nCannot open file";
		return 1;
	}

	while(!f1.eof()) 
	{
		f1.getline(p.fname, 20, '|');
		f1.getline(p.lname, 20, '|');
		f1.getline(p.mid, 10, '|');
		f1.getline(p.phn, 15, '|');
		f1.getline(p.ofphn, 15, '|');
		f1.getline(p.area, 20, '|');
		f1.getline(p.occ, 30, '|');
		f1.getline(p.email, 50, '\n');
		a++;
	}

	a--;

	if(a==50)
		flag=1;
	return flag;
}

//The unpack function is used to read records from the file and store them dynamically in the hash table.
void unpack() 
{
	fstream f3, f4, f5;
	int index, i, j;
	f3.open("address1.txt", ios::in);
	f4.open("hash1.txt", ios::out);
	if (!f3 || !f4) 
	{
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

		//Linear Probing
		/*When the current index at which the record is to be stored is already occupied by another record, the
		collision algorithm computes the next available index location. If the index crosses 50, the search for
		an empty index is wrapped around to the start.*/
		while(hashTable[index][3] != p.mid && hashTable[index][1] != "-")
			index = (index+1) % 50;

		hashTable[index][1]=p.fname;
		hashTable[index][2]=p.lname;
		hashTable[index][3]=p.mid;
		hashTable[index][4]=p.phn;
		hashTable[index][5]=p.ofphn;
		hashTable[index][6]=p.area;
		hashTable[index][7]=p.occ;
		hashTable[index][8]=p.email;

		f4 << index << "|" << p.fname << "|" << p.lname << "|" << p.mid << "|" << p.phn << "|" << p.ofphn << "|" << p.area << "|" << p.occ << "|" << p.email <<"\n";
	}
	f3.close();
	f4.close();
}

//Writing records to the file.
void write() 
{
	system("cls");
	fstream f1;
	int i, index, flag;

	f1.open("address1.txt", ios::app);
	if (!f1) 
	{
		cout << "\nCannot open the file";
		exit(1);
	}

	flag = checkOverflow();
	if(flag) 
	{
		gotoxy(55, 10);
		cout<<"Address Book is full, please try again";
		goto label2;
	}

	gotoxy(60, 6);
	cout<<"Register at Socialize";
	gotoxy(45, 10);
	cout << "Enter your first name: ";
	cin >> p.fname;
	gotoxy(45, 12);
	cout << "Enter your last name: ";
	cin >> p.lname;
	gotoxy(45, 14);
	cout << "Enter your ID: ";
	cin >> p.mid;
	gotoxy(45, 16);
	cout << "Enter your phone number: ";
	cin >> p.phn;
	gotoxy(45, 18);
	cout << "Enter your office phone number: ";
	cin >> p.ofphn;
	gotoxy(45, 20);
	cout << "Enter the area which you reside in: ";
	cin >> p.area;
	gotoxy(45, 22);
	cout << "Enter your occupation: ";
	cin >> p.occ;
	gotoxy(45, 24);
	cout << "Enter your email-ID: ";
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
	label2:
	gotoxy(58, 27);
	cout<<"Please enter to continue..";
	getch();
	return;
}

//Welcome screen as the initiation of the software.
void welcome() 
{
	system("cls");
	gotoxy(58, 13);
	cout << "Welcome to Socialize";
	gotoxy(54, 18);
	cout << "An Address Management Software";
	gotoxy(56, 23);
	cout << "Press Enter To Continue..";
	getch();
	return;
}

//Delete records by matching the ID of the record to be deleted.
void deletion() 
{
	system("cls");
	fstream f7, f8;
	int flag=0;
	char id[10];
	people obj1[50];
	int i=0;
	f7.open("address1.txt", ios::in);

	if(!f7) 
	{
		cout<<"Cannot open file";
		exit(1);
	}
	gotoxy(60, 6);
	cout<<"Delete your records";
	gotoxy(45, 11);
	cout<<"Enter the ID of the record you wish to delete: ";
	cin>>id;

	while(!f7.eof()) 
	{
		f7.getline(obj1[i].fname, 20, '|');
		f7.getline(obj1[i].lname, 20, '|');
		f7.getline(obj1[i].mid, 10, '|');
		f7.getline(obj1[i].phn, 15, '|');
		f7.getline(obj1[i].ofphn, 15, '|');
		f7.getline(obj1[i].area, 20, '|');
		f7.getline(obj1[i].occ, 30, '|');
		f7.getline(obj1[i].email, 50, '\n');

		if(strcmp(obj1[i].mid, id)==0) 
		{
			flag=1;
			continue;
		}
		i++;
	}
	f7.close();

	if(flag==1) 
	{
		fstream out1; 

		out1.open("address1.txt",ios::out | ios::trunc);
		for(int j=0;j<i-1;j++) 
		{ 
			out1<<obj1[j].fname<<"|"<<obj1[j].lname<<"|"<<obj1[j].mid<<"|"<<obj1[j].phn<<"|"<<obj1[j].ofphn<<"|"<<obj1[j].area<<"|"<<obj1[j].occ<<"|"<<obj1[j].email<<'\n'; 
		}
		out1.close();
		gotoxy(65, 15);
		cout<<"Record Deleted";
	}
	else
	{
		gotoxy(65, 15);
		cout<<"Invalid ID";
	}
	gotoxy(58, 19);
	cout<<"Press Enter to continue..";
	getch();
	return;
}

//Modify the contents of the record if present, by the User ID as the parameter.
void modify() 
{ 
	system("cls");
	people obj[50];
	fstream f3, out1; 
	char id[10]; 
	int i,j;  
	f3.open("address1.txt",ios::in); 
 
	if(!f3) 
	{ 
		cout<<"Unable to open the file in I/P mode"; 
		exit(1); 
	}
	gotoxy(60, 4);
	cout<<"Modify your records";
	gotoxy(49, 8);
	cout<<"Enter the ID of the record to be modified: "; 
	cin>>id; 
	i=0; 
  
	while(!f3.eof()) 
	{ 
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
	for(j=0;j<i;j++) 
	{ 
		if(strcmp(id,obj[j].mid)==0) 
		{ 
			gotoxy(64, 10);
			cout<<"Record Found"<<endl;
			cout<<"\n-------------------------------------------------------------------------------------------------------------------------------------------------\n";
			gotoxy(55, 12);
			cout<<"The old values of the record with ID "<<id<<" are\n"; 
			gotoxy(58, 15);
			cout<<"First Name= "<<obj[j].fname;
			gotoxy(58, 17);
			cout<<"Last Name= "<<obj[j].lname;
			gotoxy(58, 19);
			cout<<"ID= "<<obj[j].mid;
			gotoxy(58, 21);
			cout<<"Phone Number= "<<obj[j].phn;
			gotoxy(58, 23);
			cout<<"Office Phone Number= "<<obj[j].ofphn;
			gotoxy(58, 25);
			cout<<"Area= "<<obj[j].area;
			gotoxy(58, 27);
			cout<<"Occupation= "<<obj[j].occ;
			gotoxy(58, 29);
			cout<<"Email ID= "<<obj[j].email;
			cout<<"\n-------------------------------------------------------------------------------------------------------------------------------------------------\n";
			gotoxy(55, 33);
			cout<<"Enter new values for record with ID "<<id;
			gotoxy(58, 35);
			cout<<"First Name= ";
			cin>>obj[j].fname; 
			gotoxy(58, 37);
			cout<<"Last Name= ";
			cin>>obj[j].lname;
			gotoxy(58, 39); 
			cout<<"ID= ";
			cin>>obj[j].mid;
			gotoxy(58, 41); 
			cout<<"Phone Number= ";
			cin>>obj[j].phn;
			gotoxy(58, 43); 
			cout<<"Office Phone Number= ";
			cin>>obj[j].ofphn;
			gotoxy(58, 45);
			cout<<"Area= ";
			cin>>obj[j].area;
			gotoxy(58, 47);
			cout<<"Occupation= ";
			cin>>obj[j].occ;
			gotoxy(58, 49);
			cout<<"Email= ";
			cin>>obj[j].email; 
			break; 
		} 
	} 
	if(j==i) 
	{ 
		gotoxy(53, 12);
 		cout<<"The record with ID "<<id<<" is not present"; 
		 goto la;
	} 
	f3.close();

	out1.open("address1.txt",ios::out | ios::trunc);
	for(j=0;j<i;j++) 
	{ 
		out1<<obj[j].fname<<"|"<<obj[j].lname<<"|"<<obj[j].mid<<"|"<<obj[j].phn<<"|"<<obj[j].ofphn<<"|"<<obj[j].area<<"|"<<obj[j].occ<<"|"<<obj[j].email<<"\n"; 
	}
	out1.close(); 
	la:
	gotoxy(59, 53);
	cout<<"Press Enter to continue..";
	getch();
	return;
} 

//Displaying the contents of the hash table.
void display() 
{
	system("cls");
	gotoxy(60, 4);
	cout<<"Records at Socialize are";
	cout<<"\n";
    for(int i=1;i<=50;i++) {
		cout<<"\n-------------------------------------------------------------------------------------------------------------------------------------------------\n";
		cout<<"\nIndex= "<<i<<"\n";
        cout<<"\nFirst Name= "<<hashTable[i][1];
		cout<<"\nLast Name= "<<hashTable[i][2];
		cout<<"\nID= "<<hashTable[i][3];
		cout<<"\nPhone Number= "<<hashTable[i][4];
		cout<<"\nOffice Phone Number= "<<hashTable[i][5];
		cout<<"\nArea= "<<hashTable[i][6];
		cout<<"\nOccupation= "<<hashTable[i][7];
		cout<<"\nEmail ID= "<<hashTable[i][8];
        cout<<"\n-------------------------------------------------------------------------------------------------------------------------------------------------\n";
    } 
	cout<<"\n\t\t\t\t\t\t\tPress Enter to continue..";  
	getch();
	return;  
}

//Searching for records in the hash table by computing the index obtained by feeding the User ID as the input.
void search() 
{
	system("cls");
    char id[10];
	gotoxy(60, 4);
	cout<<"Search for records";
	gotoxy(53, 6);
    cout<<"Enter the ID you wish to search: ";
    cin>>id;
    int index = hashFunc(id);

	//Linear probing.
    while(hashTable[index][3] != id && hashTable[index][1] != "-")
        index = (index + 1) % 50;

    if(hashTable[index][1] != "-") 
	{
		gotoxy(64, 9);
        cout << "Record found." << endl;
		cout<<"\n-------------------------------------------------------------------------------------------------------------------------------------------------\n";
		gotoxy(58, 13);
        cout<<"First Name= "<<hashTable[index][1];
		gotoxy(58, 15);
		cout<<"Last Name= "<<hashTable[index][2];
		gotoxy(58, 17);
		cout<<"ID= "<<hashTable[index][3];
		gotoxy(58, 19);
		cout<<"Phone Number= "<<hashTable[index][4];
		gotoxy(58, 21);
		cout<<"Office Phone Number= "<<hashTable[index][5];
		gotoxy(58, 23);
		cout<<"Area= "<<hashTable[index][6];
		gotoxy(58, 25);
		cout<<"Occupation= "<<hashTable[index][7];
		gotoxy(58, 27);
		cout<<"Email ID= "<<hashTable[index][8];
		cout<<"\n-------------------------------------------------------------------------------------------------------------------------------------------------\n";
    }
    else 
	{
		gotoxy(62, 9);
		cout << "Record not found." << endl;
	}
	gotoxy(59, 31);
	cout<<"Press Enter to continue..";
	getch();
	return;
}

int main() 
{
    hashTable.resize(51, vector < string >(9, "-"));
	welcome();
	int ch;
	system("cls");
	for (;;) 
	{
		gotoxy(58, 10);
		cout<<"What do you wish to do?";
		gotoxy(60, 14);
		cout<<"1. Add Records";
		gotoxy(60, 16);
		cout<<"2. Display Records";
		gotoxy(60, 18);
		cout<<"3. Search Record";
		gotoxy(60, 20);
		cout<<"4. Modify Records";
		gotoxy(60, 22);
		cout<<"5. Delete Records";
		gotoxy(60, 24);
		cout<<"6. Exit";
		gotoxy(58, 29);
		cout << "Enter your choice: ";
		cin >> ch;

		switch (ch) 
		{
			case 1:
				write();
				system("cls");
				break;
			case 2:
				unpack();
				display();
				system("cls");
				break;
			case 3:
				unpack();
				search();
				system("cls");
				break;
			case 4:
				modify();
				system("cls");
				break;
			case 5:
				deletion();
				system("cls");
				break;
			case 6:
				exit(0);
			default:
				break;
			}
    }
	system("pause");
    return 0;
}