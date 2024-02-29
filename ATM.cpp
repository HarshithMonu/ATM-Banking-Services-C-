#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#include<string>
#include <sstream>
#include<windows.h>
#include"filehandle.h"
//#include <mysql.h>
using namespace std;

class Banking : public bankfiles
{
    public:
    struct customer cust;
        void adminworks(){
            char ch;
        bool boolean = true;
        system("cls");
        cout<<"\n\n\t\t\tAdmin Login\n";
        int qstate;
        string enpin;
        puts("\n\t\t\tEnter your pin :");
        cin>>enpin;
        if(enpin == admin_pass)
        while(boolean){
       	 	system("cls");
        	puts("\n\t Press 'm' for ATM Money deposit");
        	puts("\t Press 'e' for ATM Balance Enquiry");
        	puts("\t Press 'q' to exit ");
    		switch(_getch())
    		{
    			case 'm':
    				system("cls");
        			atmdep();
					break;
    			case 'e':
    				system("cls");
        			atmenqui();
        			boolean=false;
        			break;
    			case 'q' :
					boolean = !boolean;
    			default:
        			puts("Choose correct option");
    		}
    	}
	}
        void atmenqui(){
         float qstate;
        qstate = atm_bal();
                cout<<"\n\tATM Available Money :"<<qstate<<endl;
    	}

        void atmdep(){
           float amount;
        	puts("\n\tEnter money to deposit into ATM : ");
        	cin>>amount;
       		atm_edit(amount,true);
        	cout<<"Money deposited successfully to ATM "<<endl;
		}

    void cash_dep()
    {
    	customer t_cust;
        system("cls");
        int num;
        float bal;
         long long int accno;

         //string id,id1;
         puts("\n\n\t Enter Account Number: ");
        cin>>accno;
        t_cust = get_cust(accno);
        if(accno == t_cust.id)
        {
        	cout<<"\n\n\tEnter money to deposit : ";
        	cin>>bal;
        	atm_edit(bal,true);
        	edit_bal(t_cust.id,bal,true);
        	cout<<"Money deposited successfully to "<<t_cust.fname<<" "<<t_cust.lname<<endl;

     	}
        else
            {
                puts("\n\tEnter a valid Account Number");
                return;
            }


    }
    void acc_bank()
    {
        char ch;
        bool boolean;
        system("cls");
       	long long int accno;
       	int pin;
         puts("\n\n\t Enter Account Number: ");
        cin>>accno;
        cust = get_cust(accno);
        if(cust.id == accno)
        {
            puts("\n\t\t Enter your pin :");
        	cin>>pin;
            cout<<pin + "*";
        	if(cust.PIN == pin){
        	  	boolean=true;
        		while(boolean){
        			system("cls");
        			puts("\n\t Press 'w' for Cash Withdrawl");
        			puts("\t Press 'e' for Balance Enquiry");
        			puts("\t Press 'c' for Change pin");
        			cin>>ch;
       	 			system("cls");
    				switch(ch)
    				{
    					case 'w':
        					withdrawl();
        					boolean=false;
        					break;
    					case 'e':
        					enquiry();
        					boolean=false;
     						break;
  						case 'c':
        					changepin();
       				 		boolean=false;
       	 					break;
    					default:
        					puts("Choose correct option");
    				}
        		}
        	}
        	else{
        		cout<<"\nWrong PIN \n ";
        		return;
			}
		}
		else{
			cout<<"\n\tEnter valid account no.!";
			return;
		}
	}
    void changepin(){
    	int pin1,pin2;
    	system("cls");
    	cout<<"\n\n\tEnter old PIN : ";
    	cin>>pin1;
    	if(pin1 == cust.PIN){
    		cout<<"\n\n\tEnter new PIN : ";
    		cin>>pin2;
    		change_PIN(cust.id,pin2);
    		system("cls");
    		cout<<"\n\n\n\t\tPIN change successfull ";
    		Sleep(2000);
		}
    }

    void enquiry(){
    	cust = get_cust(cust.id);
    	cout<<"Account Holder: "<<cust.fname<<" "<<cust.lname<<endl;
        cout<<"Your Account Balance: "<<cust.balance<<endl;

	}
    void withdrawl(){
        	long long int id;
	float current;
	char choice;
	system("cls");
	//print_time();
		withdraw_check :
		system("cls");
		//print_time();
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
				atm_edit(current,false);
				//system("cls");
				//print_time();
				cout<<" \n\n\t\tTransaction done!! Please take your money\n";
				Sleep(4000);
			}
		}
		else{
			cout<<"\n\n\t\tAmount exceded savings!!Enter another amount\n";
			Sleep(500);
			goto withdraw_check;
		}
	}

};
int main()
{
    cout<<"\n\t\t\t\t\t\tMECS BANK\n\n\n";
    //cout<<"";
    //cout<<"\n\n\t\tPress any key to continue"<<endl;
    cout<<"\n\n\t\t\t\t Press any key to continue \n\n\n\n\n\n\n\n\n\n";
	cout<<"\t\t\t\t\t\t\tDone by\n\t\t\t\t\t\t\tB.Harshith  -050\n\t\t\t\t\t\t\tP.Sai Durga Shashidhar  -051\n";
    getch();
    system("cls");
    bool boolean;
    boolean=true;
    Banking b;
    char ch;
   // page:
    while(boolean){
    system("cls");
    puts("\n\t\tCash Deposit --> Press 'd' ");
    puts("\n\t\tAccount Banking --> Press 'b' ");
    puts("\n\t\tFor Exit --> Press 'e' ");
    cout<<"\n\t\tPress any key to continue\n\n"<<endl;
    switch(_getch())
    {
    case 'd':
        b.cash_dep();
        break;
    case 'a':
        b.adminworks();
        break;
    case 'b':
        b.acc_bank();
        break;
    case 'e':
        exit;
        break;
    default:
        puts("Choose correct option");
    }
    return 0;
}
}
