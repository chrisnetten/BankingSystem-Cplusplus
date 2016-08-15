/* Author: Christopher Netten
   Due Date: August 15th, 2016
   # 200230280
*/

#include "Header.h";


// Main

int main()
{


		char choice;
		int num;
		do
		{

			cout << "Hello and welcome to Netten's Banking system! I hope you enjoy your visit and save lots of money! \n\n";
			cout << "\n" << "1. CREATE NEW ACCOUNT";
			cout << "\n" << "2. DEPOSIT MONEY";
			cout << "\n" << "3. WITHDRAW MONEY";
			cout << "\n" << "4. SINGLE ACCOUNT INFORMATION";
			cout << "\n" << "5. LIST ALL CURRENT ACCOUNTS";
			cout << "\n" << "6. CLOSE AN ACCOUNT";
			cout << "\n" << "7. EDIT AN ACCOUNT";
			cout << "\n" << "8. EXIT";
			cout << "\n" << "Select One of The Options [ 1 - 8 ] ";
			cout << "\n" << "Please only enter one number. \n";
			cin >> choice;
			switch (choice)
			{
			case '1':
				write_account();
				break;
			case '2':
				cout << "\n\n\tEnter The account No. : "; cin >> num;
				depositORwithdraw(num, 1);
				break;
			case '3':
				cout << "\n\n\tEnter The account No. : "; cin >> num;
				depositORwithdraw(num, 2);
				break;
			case '4':
				cout << "\n\n\tEnter The account Number. : "; cin >> num;
				display_sp(num);
				break;
			case '5':
				display_all();
				break;
			case '6':
				cout << "\n\n\tEnter The account Number. : "; cin >> num;
				delete_account(num);
				break;
			case '7':
				cout << "\n\n\tEnter The account Number. : "; cin >> num;
				edit_account(num);
				break;
			case '8':
				cout << "\n\n\t Thank you for using my Banking System :)!";
				exit(0);
			}
			cin.ignore();
			cin.get();
		} while (choice != '8');
		return 0;
	}

void write_account();
void display_sp(int);
void edit_account(int);
void delete_account(int);
void display_all();
void depositORwithdraw(int, int);

void account::dep(int x)
{
	deposit += x;
}

void account::draw(int x)
{
	deposit -= x;
}

void account::list() const
{
	cout << "\t" << accnum << setw(10) << " " << name << setw(10) << " " << acctype << setw(10) << deposit << endl;
}


int account::grabacnum() const
{
	return accnum;
}

int account::grabdeposit() const
{
	return deposit;
}

char account::grabtype() const
{
	return acctype;
}
