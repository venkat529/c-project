#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>                 
#include<ctype.h>                   
#include<dos.h>                    \
#define RETURNTIME 15
#include<time.h>
char catagories[][15]={"Samsung","Apple","Nokia","Sony","LG","HTC"};
void returnfunc(void);
void mainmenu(void);
void addbrands(void);
void deletebrands(void);
void editbrands(void); 
void searchbrands(void);
void viewbrands(void);
void closeapplication(void);
int  getdata();
int  checkid(int);
int t(void);
void Password();
void loaderanim();
FILE *fp,*ft,*fs;
int s;
char findstaff;
char password[10]="venkat";
//{
//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
//}
struct meroDate
{
int mm,dd,yy;
};
struct staff
{
int id;
char stname[20];
char name[20];
char available[20];
int qty;
int price;
int count;
char *cat;
struct meroDate issued;
struct meroDate duedate;
};
struct staff a;
int main()
{
Password();
getch();
return 0;
}
void mainmenu()
{
system("cls");
int i;
printf(" \t\tMAIN MENU \n ");
printf("\t\t\\*******************************************************************\\n");
printf("\n<1> Add Mobile Record   ");
printf("\n<2> Delete Mobile Record");
printf("\n<3> Search Mobile Record");
printf("\n<4> View Mobile list");
printf("\n<5> Edit Mobile Record");
printf("\n<6> Close The Application");
t();
printf("\nEnter your choice:");
switch(getch())
{
case '1':
addbrands();
break;
case '2':
deletebrands();
break;
case '3':
searchbrands();
break;
case '4':
viewbrands();
break;
case '5':
editbrands();
break;
case '6':
{
system("cls");
exit(0);
}
default:
{
printf("\n\aWrong Entry!!Please re-entered correct option");
if(getch())
mainmenu();
}
}
}
void addbrands(void)    
{
system("cls");
int i;
printf("\t\t\t\tSELECT BRANDS\t\t\t\t");
printf("\n<1> Samsung");
printf("\n<2> Apple");
printf("\n<3> Nokia");
printf("\n<4> Sony");
printf("\n<5> LG");
printf("\n<6> HTC");
printf("\n<7> Back to main menu");
printf("\nEnter your choice:");
scanf("%d",&s);
if(s==7)
mainmenu() ;
system("cls");
fp=fopen("stf.dat","ab+");
if(getdata()==1)
{
a.cat=catagories[s-1];
fseek(fp,0,SEEK_END);
fwrite(&a,sizeof(a),1,fp);
fclose(fp);
printf("The record is sucessfully saved");
printf("Save any more?(Y / N):");
if(getch()=='n')
mainmenu();
else
system("cls");
addbrands();
}
}
void deletebrands()    
{
system("cls");
int d;
char another='y';
while(another=='y')  
{
system("cls");
printf("Enter the Mobile ID to  delete:");
scanf("%d",&d);
fp=fopen("stf.dat","rb+");
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.id==d)
{
printf("The Mobile record is available");
printf("Staff name is %s",a.name);
findstaff='t';
}
}
if(findstaff!='t')
{
printf("No record is found modify the search");
if(getch())
mainmenu();
}
if(findstaff=='t' )
{
printf("Do you want to delete it?(Y/N):");
if(getch()=='y')
{
ft=fopen("test.dat","wb+");  
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.id!=d)
{
fseek(ft,0,SEEK_CUR);
fwrite(&a,sizeof(a),1,ft); 
}                              
}
fclose(ft);
fclose(fp);
remove("stf.dat");
rename("test.dat","stf.dat"); 
fp=fopen("stf.dat","rb+");    
if(findstaff=='t')
{
printf("The record is sucessfully deleted");
printf("\n\tDelete another record?(Y/N)");
}
}
else
mainmenu();
fflush(stdin);
another=getch();
}
}
mainmenu();
}
void searchbrands()
{
system("cls");
int d;
printf("************************************search mobiles*************************************");
printf("1. Search By ID");
printf("2. Search By Name");
printf("Enter Your Choice");
fp=fopen("stf.dat","rb+"); 
rewind(fp);   
switch(getch())
{
case '1':
{
system("cls");
printf("************************************mobile id*************************************");
printf("Enter the Mobile id:");
scanf("%d",&d);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.id==d)
{
Sleep(2);
printf("The Mobile is available\n");
printf("ID:%d",a.id);
printf("Brand:%s",a.cat);
printf("Name:%s",a.name);
printf("Availability:%s ",a.available);
printf("Quantity:%i ",a.qty);
printf("Price:%i ",a.price);
findstaff='t';
}
}
if(findstaff!='t')  
{
printf("\aNo Record Found");
}
printf("Try another search?(Y/N)");
if(getch()=='y')
searchbrands();
else
mainmenu();
break;
}
case '2':
{
char s[15];
system("cls");
printf("************************************search mobile by name*************************************");
printf("Enter Mobile Name:");
scanf("%s",s);
int d=0;
while(fread(&a,sizeof(a),1,fp)==1)
{
if(strcmp(a.name,(s))==0) 
{
	//printf("The Staff is available");
	printf("ID:%d",a.id);
	printf("Name:%s",a.name);
		printf("Availability:%s",a.available);
	printf("Quantity:%i",a.qty);
	printf("Price:%i",a.price);
	getch();
	d+=6;
}
}
if(d==0)
printf("\aNo Record Found");
printf("Try another search?(Y/N)");
if(getch()=='y')
	searchbrands();
else
	mainmenu();
break;
}
default :
getch();
searchbrands();
}
fclose(fp);
}
void viewbrands(void)  
{
int i=0,j;
system("cls");
printf("************************************mobile list*************************************");
printf(" BRAND        ID    BRAND NAME    AVAILABILITY  QUANTITY   PRICE ");
j=4;
fp=fopen("stf.dat","rb");
while(fread(&a,sizeof(a),1,fp)==1)
{
printf("%s",a.cat);
printf("%d",a.id);
printf("%s",a.name);
printf("%s",a.available);
printf("%i",a.qty);
printf("%i",a.price);
printf("\n\n");
j++;
}
fclose(fp);
returnfunc();
}
void editbrands(void)  
{
system("cls");
int c=0;
int d,e;
printf("\xB2\xB2\xB2\xB2\xB2\xB2Edit Mobile Section \xB2\xB2\xB2\xB2\xB2\xB2");
char another='y';
while(another=='y')
{
system("cls");
printf("Enter Mobile Id to be edited:");
scanf("%d",&d);
fp=fopen("stf.dat","rb+");
while(fread(&a,sizeof(a),1,fp)==1)
{
if(checkid(d)==0)
{
printf("The Mobile is availble");
printf("The Mobile ID:%d",a.id);
printf("Enter new name:");
scanf("%s",a.name);
printf("Enter new Availability Status:");
scanf("%s",a.available);
printf("Enter new Quantity:");
scanf("%i",&a.qty);
printf("Enter new Price:");
scanf("%i",&a.price);
printf("The record is modified");
fseek(fp,ftell(fp)-sizeof(a),0);
fwrite(&a,sizeof(a),1,fp);
fclose(fp);
c=1;
}
if(c==0)
{
printf("No record found");
}
}
printf("Modify another Record?(Y/N)");
fflush(stdin);
another=getch() ;
}
returnfunc();
}
void returnfunc(void)
{
{
printf("Press ENTER to return to main menu");
}
a:
if(getch()==13) 
mainmenu();
else
goto a;
}
int getdata()
{
int t;
printf("Enter the Information Below");
printf("Brand:");
printf("%s",catagories[s-1]);
printf("MBL ID:\t");
scanf("%d",&t);
if(checkid(t) == 0)
{
printf("\aThe id already exists\a");
getch();
mainmenu();
return 0;
}
a.id=t;
printf("Model Name:");
scanf("%s",a.name);
printf("Availability:");
scanf("%s",a.available);
printf("Quantity:");
scanf("%i",&a.qty);
printf("Price:");
scanf("%i",&a.price);
return 1;
}
int checkid(int t)  
{
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
if(a.id==t)
return 0;  
return 1; 
}
int t(void) 
{
time_t t;
time(&t);
printf("Date and time:%s\n",ctime(&t));
return 0 ;
}
void Password(void) 
{
system("cls");
char d[25]="Password Protected";
char ch,pass[10];
int i=0,j;
	printf("\t\t\t\tWELCOME\n\t\t\t\t  To \n\t\t   *******************mobile store management system**********************\n");
	printf("\t \n\n\n Enter Password:");
while(ch!=13)
{
ch=getch();
if(ch!=13 && ch!=8){
putch('*');
pass[i] = ch;
i++;
}
}
pass[i] = '\0';
if(strcmp(pass,password)==0)
{
printf("\n\n\n\t\tPassword matched!!");
printf("\n\n\tPress any key to countinue.....:");
getch();
mainmenu();
}
else
{
printf("\n\n\n\t\t\aWarning!! \n\t   Incorrect Password");
getch();
Password();
}
}
