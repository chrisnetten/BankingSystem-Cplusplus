#pragma once
#include<fstream>
#include<iostream>
#include<iomanip>
#include<cctype>
using namespace std;


// Account Class 


class account
{
	int accnum;
	char name[30];
	int deposit;
	char acctype;
public:
	void create_new_account();
	void show_account() const;
	void edit();
	void dep(int);
	void draw(int);
	void list() const;
	int grabacnum() const;
	int grabdeposit() const;
	char grabtype() const;
};         




//Create Account Menu

void account::create_new_account()
{

	cout << "\nEnter The account Number (Please use less than 10 numbers) :";
		cin >> accnum;
	
	cout << "\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nEnter The Type of Account (Chequing/Saving) Type C or S : ";
	cin >> acctype;
	acctype = toupper(acctype);
	cout << "\nEnter The Starting amount: ";
	cin >> deposit;
	cout << "\n\n\nThe Account Was Created :)..";
}

//Show Account Menu

void account::show_account() const
{
	cout << "\nAccount No. : " << accnum;
	cout << "\nAccount User Name : ";
	cout << name;
	cout << "\nAccount Type : " << acctype;
	cout << "\nBalance amount : " << deposit;
}

//Edit Account Menu

void account::edit()
{
	cout << "\nAccount No. : " << accnum;
	cout << "\nEdit Account User Name : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nEdit Type of Account : ";
	cin >> acctype;
	acctype = toupper(acctype);
	cout << "\nEdit Balance amount : ";
	cin >> deposit;
}




// Reading from the account file

void display_sp(int n)
{
	account acc;
	bool noerror = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File just wont open :(.. Press any Key to Continue...";
		return;
	}
	cout << "\n YOUR ACCOUNT BALANCE DETAILS\n";

	while (inFile.read(reinterpret_cast<char *> (&acc), sizeof(account)))
	{
		if (acc.grabacnum() == n)
		{
			acc.show_account();
			noerror = true;
		}
	}
	inFile.close();
	if (noerror == false)
		cout << "\n\nAccount number does not exist";
}


// Display all accounts in a table

void display_all()
{
	account acc;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File just wont open :(.. Press any Key...";
		return;
	}
	cout << "\n\n\t\t All of The Current Accounts \n\n";
	cout << "\n\n\t C = Cheqing Account -- S = Savings Account \n\n";
	cout << "\t_______________________________________________________\n";
	cout << "\tAccount #.  | User Name |  Type  | Balance\n";
	cout << "\t_______________________________________________________\n";
	while (inFile.read(reinterpret_cast<char *> (&acc), sizeof(account)))
	{
		acc.list();
	}
	inFile.close();
}
//Changing Information in Account file

void edit_account(int n)
{
	bool found = false;
	account acc;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File just wont open :(.. Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *> (&acc), sizeof(account));
		if (acc.grabacnum() == n)
		{
			acc.show_account();
			cout << "\n\nEnter The New Details of The Account" << endl;
			acc.edit();
			int pos = (-1)*static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&acc), sizeof(account));
			cout << "\n\n\t Account Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Account Not Found ";
}

// Deleting from file

void delete_account(int n)
{
	account acc;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File just wont open :(.. Press any Key...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char *> (&acc), sizeof(account)))
	{
		if (acc.grabacnum() != n)
		{
			outFile.write(reinterpret_cast<char *> (&acc), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << "\n\n\tRecord Deleted ..";
}


// Deposit to account or withdraw

void depositORwithdraw(int n, int option)
{
	int amt;
	bool found = false;
	account acc;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File just wont open :(.. Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *> (&acc), sizeof(account));
		if (acc.grabacnum() == n)
		{
			acc.show_account();
			if (option == 1)
			{
				cout << "\n\n\tDepositing to account ";
				cout << "\n\nEnter The amount you would like to deposit";
				cin >> amt;
				acc.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tWidthdrawing from account ";
				cout << "\n\nEnter The amount you would like to withdraw";
				cin >> amt;
				int bal = acc.grabdeposit() - amt;
				acc.draw(amt);
				int pos = (-1)*static_cast<int>(sizeof(acc));
				File.seekp(pos, ios::cur);
				File.write(reinterpret_cast<char *> (&acc), sizeof(account));
				cout << "\n\n\t Updated Account";
				found = true;
			}
		}
		File.close();
		if (found == false)
			cout << "\n" << "Account Record Not Found ";
	}
}

// Write to account file
void write_account()
{
	account acc;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	acc.create_new_account();
	outFile.write(reinterpret_cast<char *> (&acc), sizeof(account));
	outFile.close();
}