#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<sstream>
#include<bits/stdc++.h>
#include<conio.h>
#include<ctime>
using namespace std;

struct customer
{
	char fname[15];
	char lname[15];
	long long int id;
	unsigned long long aadhar;
	int PIN;
	char gender;
	unsigned long long int phno;
	float balance;
	int dob[3];
};

struct employee
{
	char fname[15];
	char lname[15];
	long long int uid;
	char pass[30];
	char gender;
	unsigned long long aadhar;
	unsigned long long phno;
	int dob[3];
};

class bankfiles
{
	time_t now = time(0);
	tm *l_time = localtime(&now);
	public://access specifier
	void print_time()
	{
		time_t now = time(0);
		char *dt = ctime(&now);
		cout<<"\t\t\tMECS Bank \n";
		cout<<"\t\t   "<<dt<<"\n\n\n";
	}


	protected:
	string admin_pass = "mpj2018";
	struct customer get_cust(long long int cid)
	{
		struct customer cust,cust_main;
		FILE *fp;
		cust_main = (const struct customer){ 0 };
		//cout<<cust.balance;
		fp = fopen("custbase.dat","r");
		if(fp==NULL)
			cout<<"File not found!!\n";
		else
		{
			while(!feof(fp))
			{
				fscanf(fp,"%lld ",&cust.id);
					fscanf(fp,"%s %s %s %llu %d ",cust.fname,cust.lname,&cust.gender,&cust.phno,&cust.PIN);
					fscanf(fp,"%f %llu %d/%d/%d \n",&cust.balance,&cust.aadhar,&cust.dob[0],&cust.dob[1],&cust.dob[2]);
				if(cust.id== cid)
					cust_main = cust;
			}
			return cust_main;
		}
		cout<<"Account holder not found!";
	}
	 void put_cust()
	{
		struct customer cust;
		FILE *fp;
		FILE *fpp;
		fp = fopen("custbase.dat","a+");
		cout<<"Enter first name : ";
		cin>>cust.fname;
		cout<<"Enter last name : ";
		cin>>cust.lname;
		cout<<"Enter Gender : 'm' for male  'f' for female 'o' for others\n\t";
		cin>>cust.gender;
		cout<<"Enter 10 digit ph.no : ";
		cin>>cust.phno;//cout<<cust.id;
		//cout<<"enter the balance "
		cust.balance = 0;
		cout<<"Enter Aadhar no. : ";
		cin>>cust.aadhar;
		cout<<"Enter Date Of Birth : dd/mm/yyyy \n\t" ;
		scanf("%d/%d/%d",&cust.dob[0],&cust.dob[1],&cust.dob[2]);
		if(check_dob( cust.dob[1] , cust.dob[2]) == true)
		{
			srand(time(NULL));
			cust.id=create_id(1);
			cout<<"\t The assigned ID is : "<<cust.id<<endl;
			cout<<"\n\t\t *PIN must be a 4 digit number \n\t\t *PIN must only be a number \n\t  Enter PIN : ";
			cin>>cust.PIN;
			fprintf(fp,"%lld %s %s %c %llu %d ",cust.id,cust.fname,cust.lname,cust.gender,cust.phno,cust.PIN);
			fprintf(fp,"%f %llu %d/%d/%d \n",cust.balance,cust.aadhar,cust.dob[0],cust.dob[1],cust.dob[2]);
			fpp = fopen("custdetails.csv","a");
			fprintf(fpp,"%lld, %s, %s, %f, \n",cust.id,cust.fname,cust.lname,cust.balance);
			fclose(fp);
			fclose(fpp);
		}
		else
			cout<<"\n\n NOT 18 YEARS!! ACCOUNT CANNOT BE CREATED \n\n\n";
	}


	void edit_bal(long long int id,float current,bool deposit)
	{
		FILE *fp,*fpp,*fcs;

		float new_bal;
		char status;
		fp = fopen("custbase.dat","a+");
		fpp = fopen("records.dat","a+");
		fcs = fopen("Recordsheet.csv","a");
		feof(fp);
		customer cust;
		cust = get_cust(id);
		if(deposit == true){
			new_bal = cust.balance + current ;
			status = 'd';
		}
		else{
			new_bal = cust.balance - current ;
			status = 'w';
		}
		fprintf(fp,"%lld %s %s %c %llu %d ",cust.id,cust.fname,cust.lname,cust.gender,cust.phno,cust.PIN);
		fprintf(fp,"%f %llu %d/%d/%d \n",new_bal,cust.aadhar,cust.dob[0],cust.dob[1],cust.dob[2]);
		fprintf(fpp,"%lld %f %c %f %f ",cust.id,cust.balance,status,current,new_bal);
		fprintf(fpp,"%d/%d/%d \n",l_time->tm_mday,1+l_time->tm_mon,(1900+l_time->tm_year));
		fprintf(fcs,"%lld, %s, %f, %c, %f, %f,\n",cust.id,cust.lname,cust.balance,status,current,new_bal);
		fclose(fp);
		fclose(fpp);
		fclose(fcs);
	}

	void change_PIN(long long int cid,int new_pin)
	{
		customer cust,cust1;
		FILE *fp,*fpp;
		int old_pin;
		fp = fopen("custbase.dat","r");
		fpp = fopen("custbase.dat","a+");
		while(!feof(fp))
		{
				fscanf(fp,"%lld ",&cust.id);
					fscanf(fp,"%s %s %s %llu %d ",cust.fname,cust.lname,&cust.gender,&cust.phno,&cust.PIN);
					fscanf(fp,"%f %llu %d/%d/%d \n",&cust.balance,&cust.aadhar,&cust.dob[0],&cust.dob[1],&cust.dob[2]);
				if(cust.id== cid)
					cust1 = cust;
		}
		fprintf(fpp,"%lld %s %s %c %llu %d ",cust.id,cust.fname,cust.lname,cust.gender,cust.phno,new_pin);
		fprintf(fpp,"%f %llu %d/%d/%d \n",cust.balance,cust.aadhar,cust.dob[0],cust.dob[1],cust.dob[2]);
		fclose(fp);
		fclose(fpp);
	}


	struct employee get_emp(long long int cid)
	{
		struct employee emp,emp_main;
		emp_main = (const struct employee){0};
		FILE *fp;
		fp = fopen("emplbase.dat","r");
		while(!feof(fp))
		{
			fscanf(fp," %s %s %lld %s ",emp.fname,emp.lname,&emp.uid,emp.pass);
			fscanf(fp,"%c %llu %llu %d/%d/%d \n",&emp.gender,&emp.phno,&emp.aadhar,&emp.dob[0],&emp.dob[1],&emp.dob[2]);
			if(emp.uid == cid)
				emp_main = emp;
		}
		return emp_main;
	}
	void put_emp()
	{
		FILE *fp;int i = 0;char k;
		struct employee emp;
		string pass1,pass2;
		fp = fopen("emplbase.dat","a+");
		cout<<"Enter first name : ";
		cin>>emp.fname;
		cout<<"Enter last name : ";
		cin>>emp.lname;
		cout<<" Gender : 'm' for male 'f' for female \n\t";
		cin>>emp.gender;
		cout<<"Enter date of birth : dd/mm/yyyy \n\t";
		scanf("%d/%d/%d",&emp.dob[0],&emp.dob[1],&emp.dob[2]);
		if(check_dob(emp.dob[1],emp.dob[2]) == true)
		{
			cout<<"Enter Aadhar Number : ";
			cin>>emp.aadhar;
			cout<<"Enter 10 digit phone number : ";
			cin>>emp.phno;
			cout<<"Enter your password : ";
			while(1){
				k = _getch();
				if(k == 13)
					break;
				else{
					pass1 =pass1 + k;
					cout<<"*";
				}
			}
			//cout<<pass1;
			cout<<"\nconfirm password : ";
			while(1){
				k = _getch();
				if(k == 13)
					break;
				else{
					pass2 =pass2 +k;
					cout<<"*";
				}
			}
			//cout<<pass2;
			if(pass1 == pass2){
				system("cls");
				strcpy(emp.pass,pass1.c_str());
				srand(time(NULL));
				emp.uid = create_id(0);
				cout<<"\nEmployee Created!!\n\n\t The assigned ID is : "<<emp.uid<<endl;
				fprintf(fp,"%s %s %lld %s %c ",emp.fname,emp.lname,emp.uid,emp.pass,emp.gender);
				fprintf(fp,"%llu %llu %d/%d/%d \n",emp.phno,emp.aadhar,emp.dob[0],emp.dob[1],emp.dob[2]);
			}
			else{
				cout<<"\n\tPasswords did not match , try again ";
				put_emp();
			}
		}
		else
			cout<<"\n\n NOT 18 YEARS!! ACCOUNT CANNOT BE CREATED \n\n\n";
	}

	void display_pass(long long int cid)
	{
		FILE *fp;
		customer cust;
		int d,m,y;
		float current,new_bal;
		char status;
		fp = fopen("records.dat","r");
		cout<<"\n\n\t INITIAL BALANCE   TYPE     AMOUNT \t FINAL BALANCE \t DATE\n\n";
		cout<<"---------------------------------------------------------------------------\n\n";
		while(!feof(fp))
		{
			fscanf(fp,"%lld %f %c %f %f ",&cust.id,&cust.balance,&status,&current,&new_bal);
			fscanf(fp,"%d/%d/%d \n",&d,&m,&y);
			if(cid == cust.id){
				printf("\t %f \t    %c  \t %f \t %f  ",cust.balance,status,current,new_bal);
				printf("%d/%d/%d \n",d,m,y);
			}
		}
		fclose(fp);
		cout<<"\n\n\n\nPress any key to return to main menu\n\t";
		if(_getch())
			return;
	}

	void atm_edit(float current,bool deposit){
		FILE *fp,*fpp;
		float bal;
		fpp = fopen("atmrecord.dat","r");
		while(!feof(fpp)){
			fscanf(fpp,"%f \n",&bal);
		}
		fclose(fpp);
		//cout<<bal;
		fp = fopen("atmrecord.dat","a+");
		//feof(fpp);
		if(deposit == true)
			bal = bal+ current;
		else
			bal-=current;
		fprintf(fp,"%f \n",bal);
	}

	float atm_bal(){
		FILE *fp;
		float bal;
		fp = fopen("atmrecord.dat","r");
		while(!feof(fp))
			fscanf(fp,"%f \n",&bal);
		return bal;
	}


	private:
	long long int create_id(int choice)
	{
		string init,s,a,final;long long int id=0;
		int k;
		if(choice == 1){
			init = "1608";
			k=4;
		}
		else if(choice == 0){
			k=3;
			init = "733";
		}
		s="0123456789";
		int n = s.length();
		for(int i=0;i<k;i++)
			final.push_back(s[rand() % n]);
		a = init + final;
		stringstream idcreate(a);
		idcreate>>id;
		return id;
	}

	bool check_dob(int m, int y)
	{
		int b = 1+l_time->tm_mon - m;
		int c = (1900 +l_time->tm_year)- y;
		cout<<"AGE : "<<c<<endl;
		if(c >= 18)
			return true;
		else
			return false;
	}
};


