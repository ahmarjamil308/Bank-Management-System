#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

class account
{
private:
	int acno;
	
	char fname[20];
	
	char lname[20];
	
	int cnic[20];
	
	char address[50]; 
	
	int deposit;
	
	char type;
	
public:
	
	void create_account();
	
	void show_account() const;
	
	void modify();
	
	void dep(int);
	
	void draw(int);
	
	void report() const;
	
	int retacno() const;
	
	int retdeposit() const;
	
	char rettype() const;
};       

void account::create_account()

{
	cout<<"\n\n\t\t\t\t| A P N A B A N K |\n";
	cout<<"\n\n\tEnter The account No. :\n";
	cin>>acno;
	
	cout<<"\n\n\tEnter First Name of The account Holder :\n ";
	cin.ignore();
	cin.getline(fname,20);
	
	cout<<"\n\n\tEnter Last Name of The account Holder :\n ";
	cin.ignore();
	cin.getline(lname,20);
	
	cout<<"\n\n\tEnter Account Holder CNIC :\n";
	cin>>cnic[20];
	
	cout<<"\n\n\tEnter Account Holder Address :\n";
	cin.ignore();
	cin.getline(address,50);
	
	cout<<"\n\tEnter Type of The account C for Current And S for Saving :\n ";
	cin>>type;
	type=toupper(type);
	
	cout<<"\n\tEnter The Initial amount(>=10,000 for Saving and >=1,50,000 for current ) :\n ";
	cin>>deposit;
	
	cout<<"\n\n\n\t\t\tAccount Created..\n";
}

void account::show_account() const

{
	cout<<"\n\n\t\t\t\t| A P N A B A N K |\n";
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : "<<fname;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


void account::modify()

{
	cout<<"\n\n\t\t\t\t| A P N A  B A N K |\n";
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(fname,50);
	
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}

	
void account::dep(int x)
{
	deposit+=x;
}
	
void account::draw(int x)
{
	deposit-=x;
}
	
void account::report() const
{
	cout<<acno<<"\t\t"<<fname<<"\t\t"<<type<<"\t"<<deposit<<endl;
}

	
int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}

void write_account();

void display_sp(int);

void modify_account(int);

void delete_account(int);

void display_all();

void deposit_withdraw(int, int);

void intro();

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\t\t\t\t| A P N A  B A N K |"<<endl;
		cout<<"\n\n\t\t\tCUSTOMER CARE CENTRE ::\n";
		cout<<"\n\t\t1. NEW ACCOUNT ::\n";
		cout<<"\n\t\t2. DEPOSIT AMOUNT ::\n";
		cout<<"\n\t\t3. WITHDRAW AMOUNT ::\n";
		cout<<"\n\t\t4. BALANCE CHECK ::\n";
		cout<<"\n\t\t5. ALL ACCOUNT HOLDER LIST ::\n";
		cout<<"\n\t\t6. CLOSE AN ACCOUNT ::\n";
		cout<<"\n\t\t7. MODIFY AN ACCOUNT ::\n";
		cout<<"\n\t\t8. EXIT ::\n";	
		cout<<"\n\t\tSelect Your Options ::";
		cin>>ch;
		system("cls");
		switch(ch)
		{
			
		case '1':
			write_account();
			break;
			
		case '2':
			
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
			
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
			
		case '4': 
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
			
		case '5':
			display_all();
			break;
			
		case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
			
		 case '7':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
			
		 case '8':
			cout<<"\n\n\tThanks for using bank managemnt system";
			break;
			
			
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}
	while(ch!='8');
	return 0;
}

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}

void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}


void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\t\t\t| A P N A B A N K |\n";
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.\t\tNAME\t\tType\tBalance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac),       sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}


void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\t\t\t\t| A P N A B A N K |\n";
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\t\t\t\t| A P N A B A N K |\n";
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<5,000 && ac.rettype()=='S') || (bal<1,00000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

void intro()
{
	cout<<"|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|\n";
	cout<<"            _           __________   ____            ___            _"<<endl;
	cout<<"           / \\           | |     .)  | |\\\\           | |           / \\"<<endl;
	cout<<"          /   \\          | |      .) | | \\\\          | |          /   \\"<<endl;
	cout<<"         / / \\ \\         | |       .)| |  \\\\         | |         / / \\ \\"<<endl;
	cout<<"        / /   \\ \\        | |       .)| |   \\\\        | |        / /   \\ \\"<<endl;
    cout<<"       / /     \\ \\       | |       `)| |    \\\\       | |       / /     \\ \\"<<endl;
	cout<<"      / /       \\ \\      | |      `) | |     \\\\      | |      / /       \\ \\"<<endl;
	cout<<"     / /---------\\ \\     | |_____.)  | |      \\\\     | |     / /---------\\ \\"<<endl;
	cout<<"    / /-----------\\ \\    | |         | |       \\\\    | |    / /-----------\\ \\"<<endl;
	cout<<"   / /             \\ \\   | |         | |        \\\\   | |   / /             \\ \\"<<endl;
	cout<<"  / /               \\ \\  | |         | |         \\\\  | |  / /               \\ \\"<<endl;
	cout<<" / /                 \\ \\ | |         | |          \\\\ | | / /                 \\ \\"<<endl;
	cout<<"/_/                   \\_\\|_|         |_|           \\\\|_|/_/                   \\_\\"<<endl;
	cout<<"  ____                                        |       P R E P A R E D  B Y :     |"<<endl;
	cout<<"  ||  ))        /\\       ||\\      || ||   //  |------------------------------------|"<<endl;
	cout<<"  ||   ))      //\\\\      || \\     || ||  //   |  AHMAR  JAMIL ,  SIDRA IKRAM      |"<<endl;
	cout<<"  ||__))      //  \\\\     ||  \\    || || //    |--------------------------------|"<<endl;
	cout<<"  ||   ))    //    \\\\    ||   \\   || ||<<     |--( 48972 )--- ,---( 48805 )--------|"<<endl;
	cout<<"  ||    ))  //------\\\\   ||    \\  || || \\\\    |     RIPHAH INTERNATIONAL     |"<<endl;
	cout<<"  ||   ))  //        \\\\  ||     \\ || ||  \\\\   |        UNIVERSITY          |"<<endl;
	cout<<"  ||__))  //          \\\\ ||      \\|| ||   \\\\  |-------------------------------|"<<endl;
	cout<<"\n|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|\n";
	cout<<"              Press Any key And Then Enter To Access Customer Care Service   "<<endl;
	cin.get();
	
}
