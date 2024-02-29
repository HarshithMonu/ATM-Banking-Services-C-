#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include"filehandle.h"
#include<windows.h>
#include<conio.h>

using namespace std;

class Bank : public bankfiles
{
	public:
		long long int t_id;
	struct employee emp;
	void start();
	void check_admin();
//	bool emp_login();
	void main_menu();
	void cash_deposit();
	void cash_withdraw();
	void fund_transfer();
	void pass_book();
	void cust_details();
	void profile();
	void emp_details(long long int);
};

void Bank::check_admin()
	{
		string pass;
		char k;
		cout<<"\n\n\t\tWelcome, Admin\n";
		cout<<"\n\t\tEnter password : ";
		while(1){
				k = _getch();
				if(k == 13)
					break;
				else{
					pass =pass + k;
					cout<<"*";
				}
			}
		if(pass == admin_pass){
			check_admin :
			system("cls");
			print_time();
			cout<<"\tPress 'm' for normal menu \n";
			cout<<"\n\tPress 'c' for creating new employee \n";
			cout<<"\n\tPress 'd' for employee details \n";
			switch(_getch())
			{
				case 'm' : system("cls");
							main_menu();
							break;
				case 'c' : system("cls");
							put_emp();
							Sleep(5000);
							break;
				case 'd' : system("cls");
							print_time();
							cout<<"\n\tEnter UID : ";
							cin>>t_id;
							emp_details(t_id);
							break;
				default : system("cls");
							break; 			
			}
			goto check_admin;
		}	
	}
void Bank::start()
{
	sign_check :
	system("cls");
	print_time();
	char k;
	long int uid;
	string pass;
	cout<<"\n\t\t\t SIGN IN \n\n\t\t    UID : ";
	cin>>uid;
	emp = get_emp(uid);
	cout<<"\n\n\t\tPassword : ";
	while(1){
				k = _getch();
				if(k == 13)
					break;
				else{
					pass =pass + k;
					cout<<"*";
				}
			}
	if(strcmp(emp.pass,pass.c_str())== 0)
		main_menu();
	else{
		system("cls");
		print_time();
		cout<<"\n\n\t\t\tInvalid credentials\n";
		Sleep(1000);
		system("cls");
		goto sign_check;
	}
}

void Bank :: main_menu()
{
	char k;
	system("cls");
	print_time();
	cout<<"\t\tMAIN MENU\n\n";
	cout<<"\n\t1. Create new account \t\t 2. cash deposit \n\n";
	cout<<"\t3. Fund Transfer \t\t 4. passbook \n\n";
	cout<<"\t5. customer details \t\t 6. Profile \n\n\t7. Cash Withdraw \t";
	cout<<"\t 8.Log Out\n\n\t";
	switch(_getch())
	{
		case '1' : system("cls");
					put_cust();
					break;
		case '2' : cash_deposit();
					break;
		case '3' : fund_transfer();
					break;
		case '4' : pass_book();
					break;
		case '5' : cust_details();
					break;
		case '6' : emp_details(emp.uid);
					break;
		case '7' : cash_withdraw();
					break;
		case '8' : system("cls");
					log_check :
					cout<<"\n\n\n\n\t\tAre you Sure? (y/n) \n\t\t";
					k=_getch();
					if(k == 'y')
						start();
					else if(k =='n')
						break;
					else
						goto log_check;
		default : cout<<"Choose the right one!!!!";
	}
	system("cls");
	main_menu();
}

void Bank :: cash_deposit()
{
	long long int id;
	float current;
	char choice;
	customer cust;
	system("cls");
	print_time();
	cout<<"\t\tEnter Account number : ";
	cin>>id;
	cust = get_cust(id);
	if(cust.id != 0){
		system("cls");
		print_time();
		cout<<"\n\t"<<cust.fname<<" "<<cust.lname<<endl;
		cout<<"\n\t\tEnter amount : ";
		cin>>current;
		cout<<"\n\t Current balance : "<<cust.balance;
		cout<<"\n\n\tNew balance : "<<(cust.balance+current);
		cout<<"\n\n\t Are you sure (y/n) ? : ";
		cin>>choice;
		if(choice == 'y'){
			edit_bal(cust.id,current,true);
			system("cls");
			print_time();
			cout<<" \n\n\t\tTransaction done!! Please collect money\n";
			Sleep(4000);
		}
	}
	else{
		cout<<"Account not found!! \n";
		Sleep(1000);
	}
		
}

void Bank :: cash_withdraw()
{
	long long int id;
	float current;
	char choice;
	customer cust;
	system("cls");
	print_time();
	cout<<"\t\tEnter Account number : ";
	cin>>id;
	cust = get_cust(id);
	if(cust.id != 0){
		withdraw_check :
		system("cls");
		print_time();
		cout<<"\n\n\t\t"<<cust.fname<<" "<<cust.lname<<endl;
		cout<<"\n Available balance : "<<cust.balance;
		cout<<"\n\n\t\tEnter amount : ";
		cin>>current;
		if(current <= cust.balance){
			cout<<"\n\n\t Current balance : "<<cust.balance;
			cout<<"\n\n\tNew balance : "<<(cust.balance-current);
			cout<<"\n\n\t Are you sure (y/n) ? : ";
			cin>>choice;
			if(choice == 'y'){
				edit_bal(cust.id,current,false);
				system("cls");
				print_time();
				cout<<" \n\n\t\tTransaction done!! Please hand over money\n";
				Sleep(4000);
			}
		}
		else{
			cout<<"\n\n\t\tAmount exceded savings!!Enter another amount\n";
			Sleep(500);
			goto withdraw_check;
		}
	}
	else{
		cout<<"Account not found!! \n";
		Sleep(1000);
	}
		
}
void Bank :: fund_transfer()
{
	customer cust1,cust2;
	long long int id1,id2;
	float current;
	system("cls");
	print_time();
	cout<<"\t\tEnter withdraw accuunt no : ";
	cin>>id1;
	cust1 = get_cust(id1);
	cout<<"\n "<<cust1.fname<<" "<<cust1.lname<<endl;
	cout<<"\t\tEnter deposit accuunt no : ";
	cin>>id2;
	cust2 = get_cust(id2);
	cout<<"\n "<<cust2.fname<<" "<<cust2.lname<<endl;
	Sleep(1000);
	if(cust1.id != 0 && cust2.id != 0)
	{
		system("cls");
		print_time();
		bal_check :
		cout<<"\tAvailable amount : "<<cust1.balance;
		cout<<"\n\tEnter amount to be transferred : ";
		cin>>current;
		if(current <= cust1.balance){
			edit_bal(cust1.id,current,false);
			edit_bal(cust2.id,current,true);
			system("cls");
			print_time();
			cout<<"\n\tFund Transfer Successfull!!\n\t"<<cust2.lname<<" balance :"<<cust2.balance + current;
			Sleep(4000);
		}
		else
			goto bal_check ;
	}
}


void Bank :: pass_book()
{
	long long int id;
	customer cust;
	system("cls");
	print_time();
	cout<<"\n\t\tEnter account number : ";
	cin>>id;
	cust = get_cust(id);
	if(id == cust.id){
		system("cls");
		print_time();
		cout<<"\n\t\t Passbook of "<<cust.fname<<" "<<cust.lname<<endl;
			display_pass(id);
		
	}
	
}

void Bank::cust_details()
{
	customer cust;
	long long int id;
	system("cls");
	print_time();
	jump_emp :
	cout<<"\n\tEnter account no : ";
	cin>>id;
	cust = get_cust(id);
	if(id == cust.id){
		system("cls");
		print_time();
		cout<<"\n\t\t\t"<<cust.id<<endl;
		cout<<"\n\t1.First name : \t"<<cust.fname;
		cout<<"\n\t2.Last name : \t"<<cust.lname;
		cout<<"\n\t3.Gender : \t"<<cust.gender;
		cout<<"\n\t4.Aadhar no : \t"<<cust.aadhar;
		printf("\n\t5.Date of birth : %d/%d/%d\t",cust.dob[0],cust.dob[1],cust.dob[2]);
		printf("\n\t6.Phone no : %llu\t",cust.phno);
		cout<<"\n\n\t\tACCOUNT BALANCE : "<<cust.balance;
		cout<<"\n\tTo exit,press any key ";
		switch(_getch())
		{
			default : break;
		}	
	}
	else{
		system("cls");
		print_time();
		cout<<"\n\tAccount does not exist!!";
	}
}

void Bank::emp_details(long long int id)
{
	employee emp_t;
	system("cls");
	print_time();
	emp_t = get_emp(id);
	if(id == emp_t.uid){
		system("cls");
		print_time();
		cout<<"\n\t\t\t"<<emp_t.uid<<endl;
		cout<<"\n\t1.First name : \t"<<emp_t.fname;
		cout<<"\n\t2.Last name : \t"<<emp_t.lname;
		cout<<"\n\t3.Gender : \t"<<emp_t.gender;
		cout<<"\n\t4.Aadhar no : \t"<<emp_t.aadhar;
		printf("\n\t5.Date of birth : %d/%d/%d\t",emp_t.dob[0],emp_t.dob[1],emp_t.dob[2]);
		printf("\n\t6.Phone no : %llu\t",emp_t.phno);
		cout<<"\n\tTo exit,press any key ";
		switch(_getch())
		{
			default : break;
		}	
	}
	else{
		system("cls");
		print_time();
		cout<<"\n\tAccount does not exist!!";
	}
}


int main()
{
	struct customer cust;
	struct employee emp;
	Bank b;char c;
	b.print_time();
	cout<<"\n\n\t\tpress any key to continue \n\n\n\n\n\n\n\n\n\n";
	cout<<"\t\t\t\t\tDone by\n\t\t\t\tP.Sai Durga Shashidhar  -051\n\t\t\t\tB.Harshith\t\t-050\n";
	if(_kbhit)
	{
		switch(_getch())
		{
			
			case 'a':   c=_getch();
						system("cls");
						if(c=='d')
							b.check_admin();
						break;
			default : //Sleep(10000);
			           b.start();
		}
	}
}
