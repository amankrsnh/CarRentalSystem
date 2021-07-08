#include"myconio.h"
#include "car.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdio_ext.h>
void sub_str(char *str,char *sub,char c)
{
    int i,f=0,j=0;
    for(i=0;str[i]!=c;i++)
    {
        f++;
    }
    for(i=++f;str[i]!='\0';i++)
    {
        sub[j]=str[i];
        j++;
    }
    sub[j]='\0';
}
void addAdmin()
{
    FILE *fp=fopen("admin.bin","rb");
    if(fp==NULL)
    {
        fp=fopen("admin.bin","wb");
        User u[2]={{"admin","abc","Ramesh"},{"aftab","abc","Md Aftab Ahmad"}};
        fwrite(u,sizeof(u),1,fp);
        fclose(fp);
        printf("File saved.");
        getch();
    }
    else
    {
        fclose(fp);
    }
}
User* getInput()
{
    int i;
    clrscr();
    gotoxy(32,1);
    printf(YELLOW "CAR RENTAL SYSTEM\n");
    for(i=0;i<80;i++)
    {
        printf("~");
    }
    gotoxy(32,5);
    printf("* LOGIN PANEL *");
    gotoxy(1,7);
    printf(CYAN);
    for(i=0;i<80;i++)
         printf("~");
    gotoxy(1,15);
    for(i=0;i<80;i++)
         printf("~");
    gotoxy(60,8);
    printf(WHITE  "Press 0 to exit");
    gotoxy(25,10);
    printf(CYAN  "Enter user id:");
    //getchar();
    __fpurge(stdin);
    printf(WHITE);
    static User usr;
    fgets(usr.userid,sizeof(usr.userid),stdin);
    char *pos;
    pos=strchr(usr.userid,'\n');
    *pos='\0';
    if(strcmp(usr.userid,"0")==0)
    {   printf(RED);
        gotoxy(30,17);
        //getch();
        printf("Login Cancelled!");
        getch();
        printf(YELLOW);
        return NULL;
    }
    gotoxy(25,11);
    printf(CYAN);
    printf("Enter Password:");
    //fflush(stdin);
    __fpurge(stdin);
    int j=41;
    i=0;
    printf(WHITE);
    gotoxy(j,11);
    for(;;)
    {
        usr.pwd[i]=getch();
        if(usr.pwd[i]=='\n')
            break;
        printf("*");
        i++;
    }
    usr.pwd[i]='\0';
    if(strcmp(usr.pwd,"0")==0)
    {
        gotoxy(30,17);
        printf(RED "LOGIN CANCELLED!" );
        getch();
        printf(YELLOW);
        return NULL;
    }
    return &usr;
}
int checkUserExist(User u,char *usertype)
{
    if(strcmp(u.userid,"")==0 || strcmp(u.pwd,"")==0)
    {
        gotoxy(28,20);
        printf(RED "BOTH FIELDS ARE MANDATORY");
        getch();
        gotoxy(28,20);
        printf("                                    ");
        return 0;
    }
    int found=0;
    if(!(strcmp(usertype,"admin")))
    {
        FILE *fp=fopen("admin.bin","rb");
        User user;
        while(fread(&user,sizeof(User),1,fp)==1)
        {
            if(strcmp(u.userid,user.userid)==0  &&  strcmp(u.pwd,user.pwd)==0)
            {
                found =1;
                break;
            }
        }
        if(!found)
        {
            gotoxy(27,20);
            printf(RED "INVALID USERNAME AND PASSWORD");
            getch();

            fclose(fp);
            printf(WHITE);
            return 0;
        }
        fclose(fp);
        return 1;
    }
    else if(!(strcmp(usertype,"emp")))
    {
        FILE *fp=fopen("emp.bin","rb");    //code for reading emp.bin
        User user;
        while(fread(&user,sizeof(user),1,fp)==1)
        {
            if(strcasecmp(u.userid,user.userid)==0 && strcmp(u.pwd,user.pwd)==0)
            {
                found=1;
                break;
            }
        }
        if(!found)
        {
            gotoxy(27,48);
            printf(RED "INVALID USERNAME AND PASSWORD");
            getch();
            fclose(fp);
            printf(WHITE);
            return 0;
        }
        fclose(fp);
        return 1;

    }
}
int adminMenu()
{
    int choice,i;
    gotoxy(32,2);
    printf(RED  "CAR RENTAL SYSTEM");
    gotoxy(35,6);
    printf(GREEN  "ADMIN MENU\n");
    for(i=0;i<80;i++)
    {
        printf("*");
    }
    gotoxy(32,8);
    printf(YELLOW  "1. Add Employee");
    gotoxy(32,9);
    printf("2. Add Car Details");
    gotoxy(32,10);
    printf("3. Show Employee");
    gotoxy(32,11);
    printf("4. Show Car Details");
    gotoxy(32,12);
    printf("5. Delete Employee");
    gotoxy(32,13);
    printf("6. Delete Car Details");
    gotoxy(32,14);
    printf("7. Exit");
    gotoxy(32,16);
    printf("Enter Choice:");
    printf(WHITE);
    scanf("%d",&choice);
    return choice;
}
void addEmployee()
{
    FILE *fp=fopen("emp.bin","rb");
    int id;
    char uchoice;
    char emp[10]="EMP-";
    char empid[10];
    User u,ur;
    if(fp==NULL)
    {
        fp=fopen("emp.bin","ab");
        id=1;
        sprintf(empid,"%d",id);
        strcat(emp,empid);
        strcpy(u.userid,emp);
        strcpy(emp,"EMP-");
    }
    else
    {
        fp=fopen("emp.bin","ab+");
        fseek(fp,-60,SEEK_END);
        fread(&ur,sizeof(ur),1,fp);
        char sub[3];
        char str[20];
        strcpy(str,ur.userid);
        sub_str(str,sub,'-');
        id=atoi(sub);
        id++;
        sprintf(empid,"%d",id);
        strcat(emp,empid);
        strcpy(u.userid,emp);
        strcpy(emp,"EMP-");
    }
    do
    {
        clrscr();
        gotoxy(32,2);
        printf(RED  "CAR RENTAL APP");
        printf(GREEN);
        int i;
        gotoxy(1,3);
        for(i=0;i<80;i++)
        {
            printf("~");
        }
        printf(WHITE);
        gotoxy(25,5);
        printf("***** ADD EMPLOYEE DETAILS *****");
        gotoxy(1,8);
        for(i=0;i<80;i++)
        {
            printf("~");
        }
        gotoxy(1,10);
        printf(YELLOW  "Enter Employee name:");
        //fflush(stdin);
        __fpurge(stdin);
        printf(WHITE);
        fgets(u.name,20,stdin);
        char *pos;
        pos=strchr(u.name,'\n');
        *pos='\0';
        printf(YELLOW);
        printf("Enter Employee Pwd:");
        //fflush(stdin);
        __fpurge(stdin);
        printf(WHITE);
        fgets(u.pwd,20,stdin);
        pos=strchr(u.pwd,'\n');
        *pos='\0';
        printf(YELLOW);
        fseek(fp,0,SEEK_END);
        fwrite(&u,sizeof(User),1,fp);
        gotoxy(30,15);
        printf(GREEN "Employee Added Successfully.\n\n");
        printf("Employee Id is: %s",u.userid);
        gotoxy(1,20);
        printf(RED  "Do You Want To Add More Employee(Y/N) :");
        printf(WHITE);
        //fflush(stdin);
        __fpurge(stdin);
        scanf("%c",&uchoice);
        id++;
        sprintf(empid,"%d",id);
        strcat(emp,empid);
        strcpy(u.userid,emp);
        strcpy(emp,"EMP-");
    }
    while(uchoice=='Y' || uchoice=='y');
    fclose(fp);
}
void viewEmployee()
{
    FILE *fp=fopen("emp.bin","rb");
    User ur;
    int i;
    printf(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=0;i<80;i++)
    {
        printf("%c",126);
    }
    gotoxy(31,5);
    printf("* EMPLOYEE DETAILS *");
    gotoxy(1,7);
    printf(GREEN);
    for(i=0;i<80;i++)
    {
        printf("%c",126);
    }
    gotoxy(1,8);
    printf(" Employee ID\t\t\tName\t\t\tPassword ");
    gotoxy(1,9);
    for(i=0;i<80;i++)
    {
        printf("%c",126);
    }
    int x=10;
    printf(YELLOW);
    while(fread(&ur,sizeof(ur),1,fp)==1)
    {
        gotoxy(2,x);
        printf("%s",ur.userid);
        gotoxy(33,x);
        printf("%s",ur.name);
        gotoxy(57,x);
        printf("%s",ur.pwd);
        x++;
    }
    fclose(fp);
    //getchar();
    __fpurge(stdin);
    getch();
}
int deleteEmp()
{
    FILE *fp1=fopen("emp.bin","rb");
    char empid[10];
    int i;
    gotoxy(32,1);
    printf(YELLOW  "CAR RENTAL SYSTEM\n");
    for(i=0;i<80;i++)
    {
        printf("%c",126);
    }
    gotoxy(29,5);
    printf("* DELETE EMPLOYEE RECORD *");
    gotoxy(1,7);
    printf(GREEN);
    for(i=0;i<80;i++)
    {
        printf("%c",126);
    }
    gotoxy(1,12);
    for(i=0;i<80;i++)
    {
        printf("%c",126);
    }
    if(fp1==NULL)
    {
        printf(RED  "\nNo Employee Added Yet!");
        return -1;
    }
    FILE *fp2=fopen("temp.bin","wb+");
    gotoxy(10,9);
    printf(YELLOW  "Enter Employee Id to delete the record:");
    printf(WHITE);
    scanf("%s",empid);
    User U;
    int found=0;
    while(fread(&U,sizeof(U),1,fp1)==1)
    {
        if(strcmp(U.userid,empid)!=0)
        {
            fwrite(&U,sizeof(U),1,fp2);
        }
        else
        {
            found=1;
        }
    }
    if(found==1)
    {
        rewind(fp2);
        fp1=fopen("emp.bin","wb");
        while(fread(&U,sizeof(U),1,fp2)==1)
        {
            fwrite(&U,sizeof(U),1,fp1);
        }
        fclose(fp1);
    }
    fclose(fp1);
    fclose(fp2);
    remove("temp.bin");
    return found;
}
void addCarDetails()
{
    FILE *fp=fopen("car.bin","ab");
    FILE *fp1=fopen("availcar.bin","ab");
    Car C;
    char c_choice;
    do
    {
        clrscr();
        gotoxy(32,2);
        printf(RED  "CAR RENTAL APP");
        printf(GREEN);
        int i;
        gotoxy(1,3);
        for(i=0;i<80;i++)
        {
            printf("~");
        }
        printf(WHITE);
        gotoxy(25,5);
        printf("***** ADD CAR DETAILS *****");
        gotoxy(1,8);
        for(i=0;i<80;i++)
        {
            printf("~");
        }
        gotoxy(1,10);
        printf(YELLOW  "Enter Car id: ");
        printf(WHITE);
        scanf("%d",&C.car_id);
        //fflush(stdin);
        __fpurge(stdin);
        //getchar();
        printf(YELLOW);
        printf("Enter Car name: ");
        printf(WHITE);
        fgets(C.car_name,50,stdin);
        char *pos;
        pos=strchr(C.car_name,'\n');
        *pos='\0';
        printf(YELLOW);
        printf("Enter Capacity:");
        printf(WHITE);
        scanf("%d",&C.capacity);
        //fflush(stdin);
        __fpurge(stdin);
        //getchar();
        printf(YELLOW);
        printf("Enter no. of cars:");
        printf(WHITE);
        scanf("%d",&C.car_count);
        //fflush(stdin);
        __fpurge(stdin);
        //getchar();
        printf(YELLOW);
        printf("Enter Price:");
        printf(WHITE);
        scanf("%d",&C.price);
        //fflush(stdin);
        __fpurge(stdin);
        //getchar();
        fseek(fp,0,SEEK_END);
        fseek(fp1,0,SEEK_END);
        fwrite(&C,sizeof(Car),1,fp);
        fwrite(&C,sizeof(Car),1,fp1);
        gotoxy(30,15);
        printf(GREEN "Car Details Added Successfully.");
        gotoxy(1,20);
        printf(RED  "Do You Want To Add More Cars(Y/N):");
        printf(WHITE);
        //fflush(stdin);
        __fpurge(stdin);
        //getchar();
        scanf("%c",&c_choice);
        //fflush(stdin);
        __fpurge(stdin);
        //getchar();
    }while(c_choice=='Y'  ||  c_choice=='y');
    fclose(fp);
    fclose(fp1);

}
int empMenu()
{
    int choice,i;
    gotoxy(32,2);
    printf(RED  "CAR RENTAL SYSTEM");
    gotoxy(35,6);
    printf(GREEN  "EMPLOYEE MENU\n");
    for(i=0;i<80;i++)
    {
        printf("*");
    }
    printf(YELLOW);
    gotoxy(32,8);
    printf("1. Rent A Car");
    gotoxy(32,9);
    printf("2. Booking Details");
    gotoxy(32,10);
    printf("3. Available Car Details");
    gotoxy(32,11);
    printf("4. Show All Car Details");
    gotoxy(32,12);
    printf("5. Exit");
    gotoxy(32,15);
    printf("Enter Choice: ");
    printf(WHITE);
    scanf("%d",&choice);
    return choice;
}
int selectCarModel()
{
    int flag;
    FILE *fp=fopen("car.bin","rb");
    Car C;
    int choice,x=9;
    gotoxy(34,x);
    while(fread(&C,sizeof(C),1,fp)==1)
    {
        if(C.car_count>0)
        {
            printf("%d. %s",C.car_id,C.car_name);
            gotoxy(34,++x);
        }
    }
    gotoxy(34,x+2);
    __fpurge(stdin);
    printf("Enter your choice:");
    while(1)
    {
        flag=0;
        scanf("%d",&choice);
        rewind(fp);
        while(fread(&C,sizeof(C),1,fp)==1)
        {
            if(C.car_id==choice && C.car_count>0)
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            fclose(fp);
            return choice;
        }
        else
        {
            gotoxy(37,x+4);
            printf(RED  "Wrong Input");
            getch();
            gotoxy(35,x+4);
            printf("        ");
            gotoxy(52,x+2);
            printf("    ");
            gotoxy(52,x+2);
            printf(WHITE);
        }
    }
}
int deleteCarModel()
{
    FILE *fp1=fopen("car.bin","rb");
    FILE *fp2=fopen("availcar.bin","rb");
    int carid;
    int i;
    gotoxy(32,1);
    printf(YELLOW  "CAR RENTAL SYSTEM\n");
    for(i=0;i<80;i++)
    {
        printf("%c",126);
    }
    gotoxy(29,5);
    printf("* DELETE CARS RECORD *");
    gotoxy(1,7);
    printf(GREEN);
    for(i=0;i<80;i++)
    {
        printf("%c",126);
    }
    gotoxy(1,12);
    for(i=0;i<80;i++)
    {
        printf("%c",126);
    }
    if(fp1==NULL)
    {
        printf(RED  "\nNo Cars Added Yet!");
        return -1;
    }
    FILE *fp3=fopen("tempcar1.bin","wb+");
    FILE *fp4=fopen("tempcar2.bin","wb+");
    gotoxy(10,9);
    printf(YELLOW  "Enter Car Id to delete the record:");
    printf(WHITE);
    scanf("%d",&carid);
    Car C,C1;
    int found=0;
    int found1=0;
    while(fread(&C,sizeof(C),1,fp1)==1)
    {
        if(C.car_id!=carid)
        {
            fwrite(&C,sizeof(C),1,fp3);
        }
        else
        {
            found=1;
        }
    }
    while(fread(&C1,sizeof(C1),1,fp2)==1)
    {
        if(C1.car_id!=carid)
        {
            fwrite(&C1,sizeof(C1),1,fp4);
        }
        else
        {
            found1=1;
        }
    }
    if(found==1)
    {
        rewind(fp3);
        fp1=fopen("car.bin","wb");
        while(fread(&C,sizeof(C),1,fp3)==1)
        {
            fwrite(&C,sizeof(C),1,fp1);
        }

        fclose(fp1);
    }
    if(found1==1)
    {
        rewind(fp3);
        fp2=fopen("availcar.bin","wb");
        while(fread(&C1,sizeof(C1),1,fp4)==1)
        {
            fwrite(&C1,sizeof(C1),1,fp2);
        }

        fclose(fp2);
    }
    fclose(fp1);
    fclose(fp2);
    remove("tempcar1.bin");
    remove("tempcar2.bin");
    return found;
}
int isValidDate(struct tm dt)
{
    if(dt.tm_year>=2020 && dt.tm_year<=2022)
    {
        if(dt.tm_mon>=1 && dt.tm_mon<=12)
        {
            if((dt.tm_mday>=1 && dt.tm_mday<=31) && (dt.tm_mon==1 || dt.tm_mon==3 || dt.tm_mon==5 || dt.tm_mon==7 ||dt.tm_mon==8 || dt.tm_mon==10 || dt.tm_mon==12))
                return 1;
            else if((dt.tm_mday>=1 && dt.tm_mday<=30) && (dt.tm_mon==4 || dt.tm_mon==6  || dt.tm_mon==9 || dt.tm_mon==11))
                return 1;
            else if((dt.tm_mday>=1 && dt.tm_mday<=28) && (dt.tm_mon==2))
                return 1;
            else if(dt.tm_mday==29 && dt.tm_mon==2 && (dt.tm_year%400==0 || (dt.tm_year%4==0 && dt.tm_year%100!=0)))
                return 1;
            else
                return 0;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
void updateCarCount(int x)
{
    int y=x;
    FILE *fp1=fopen("availcar.bin","rb+");
    Car C1;
    while(fread(&C1,sizeof(Car),1,fp1)==1)
    {
        if(C1.car_id==y)
        {
            int cc_new=C1.car_count-1;
            fseek(fp1,-8,SEEK_CUR);
            fwrite(&cc_new,sizeof(4),1,fp1);
        }
    }
    fclose(fp1);
}
char * getCarName(int car_id)
{
    FILE *fp=fopen("car.bin","rb");
    static Car C;
    while(fread(&C,sizeof(C),1,fp)==1)
    {
        if(C.car_id==car_id)
        {
            break;
        }
    }
    fclose(fp);
    return C.car_name;
}
void bookedCarDetails()
{
    clrscr();
    FILE *fp=fopen("customer.bin","rb");
    if(fp==NULL)
    {
        printf("No cars booked yet!");
        return;
    }
    Customer_Car_Details CC;
    int i;
    printf(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=80;i++)
    {
        printf("~");
    }
    gotoxy(31,5);
    printf("* BOOKED CAR DEATILS *");
    gotoxy(1,7);
    printf(GREEN);
    for(i=0;i<80;i++)
        printf("~");
    gotoxy(1,8);
    printf("Model\t   Cust Name\t    Pick Up\t   Drop\t\t  S_Date\tE_date");
    gotoxy(1,9);
    printf(GREEN);
    for(i=0;i<80;i++)
        printf("~");
    int x=10;
    printf(YELLOW);
    while(fread(&CC,sizeof(Customer_Car_Details),1,fp)==1)
    {
        gotoxy(1,x);
        printf("%s",getCarName(CC.car_id));
        gotoxy(12,x);
        printf("%s",CC.cust_name);
        gotoxy(27,x);
        printf(" %s",CC.pick);
        gotoxy(44,x);
        printf("%s",CC.drop);
        gotoxy(58,x);
        printf("%d-%d-%d",CC.sd.tm_mday,CC.sd.tm_mon,CC.sd.tm_year);
        gotoxy(70,x);
        printf(" %d-%d-%d",CC.ed.tm_mday,CC.ed.tm_mon,CC.ed.tm_year);
        x++;
    }
    fclose(fp);
    getch();
}
int rentCar()
{
    Customer_Car_Details CC;
    //char pick[30],drop[30];
    int c,i;
    printf(RED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    printf(GREEN);
    gotoxy(35,6);
    printf("EMPLOYEE MENU\n");
    for(i=0;i<80;i++)
    {
        printf("*");
    }
    printf(YELLOW);
    gotoxy(32,8);
    c=selectCarModel();
    CC.car_id=c;
    clrscr();
    printf(RED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    printf(GREEN);
    gotoxy(35,6);
    printf("EMPLOYEE MENU\n");
    for(i=0;i<80;i++)
    {
        printf("*");
    }
    gotoxy(1,17);
    for(i=0;i<80;i++)
    {
        printf("*");
    }
    printf(YELLOW);
    gotoxy(27,9);
    printf("Enter Customer Name:");
    __fpurge(stdin);
    //fflush(stdin);
    //getchar();
    printf(WHITE);
    fgets(CC.cust_name,30,stdin);
    char *pos;
    pos=strchr(CC.cust_name,'\n');
    *pos='\0';
    gotoxy(27,10);
    printf(YELLOW);
    printf("Enter Pickup Point:");
    //fflush(stdin);
    __fpurge(stdin);
    printf(WHITE);
    fgets(CC.pick,30,stdin);
    pos=strchr(CC.pick,'\n');
    *pos='\0';
    gotoxy(27,11);
    printf(YELLOW);
    printf("Enter Drop Point:");
    __fpurge(stdin);
    //fflush(stdin);
    printf(WHITE);
    fgets(CC.drop,30,stdin);
    pos=strchr(CC.drop,'\n');
    *pos='\0';
    gotoxy(27,12);
    printf(YELLOW);
    printf("Enter Start Date (dd/mm/yyyy):");
    printf(WHITE);
    do
    {
        scanf("%d/%d/%d",&CC.sd.tm_mday,&CC.sd.tm_mon,&CC.sd.tm_year);
        int datevalid=isValidDate(CC.sd);
        if(datevalid==0)
        {
            gotoxy(27,18);
            printf(RED  "Wrong Starting Date");
            getch();
            gotoxy(27,18);
            printf("        ");
            gotoxy(56,12);
            printf("            ");
            gotoxy(56,12);
            printf(WHITE);
        }
        else
        {
            break;
        }
    }while(1);
    gotoxy(27,13);
    printf(YELLOW   "Enter end date (dd/mm/yyyy):");
    printf(WHITE);
    do
    {
        int datevalid;
        scanf("%d/%d/%d",&CC.ed.tm_mday,&CC.ed.tm_mon,&CC.ed.tm_year);
        if(CC.ed.tm_year<CC.sd.tm_year)
        {
            datevalid=0;
        }
        else if(CC.ed.tm_year==CC.sd.tm_year)
        {
            if(CC.ed.tm_mon<CC.sd.tm_mon)
            {
                datevalid=0;
            }
            else if(CC.ed.tm_mon==CC.sd.tm_mon)
            {
                if(CC.ed.tm_mday<CC.sd.tm_mday && CC.ed.tm_mday==CC.sd.tm_mday)
                {
                    datevalid=0;
                }
                else
                    datevalid=1;
            }
            else
                datevalid=1;
        }
        else
            datevalid=1;
        int dateval=isValidDate(CC.ed);
        if(datevalid==0 && dateval==0)
        {
            gotoxy(27,18);
            printf(RED  "Wrong Ending Date");
            getch();
            gotoxy(27,18);
            printf("        ");
            gotoxy(56,13);
            printf("            ");
            gotoxy(56,13);
            printf(WHITE);
        }
        else
        {
            break;
        }
    }while(1);
    FILE *fp=fopen("customer.bin","ab");
    fwrite(&CC,sizeof(Customer_Car_Details),1,fp);
    printf("\nPress any key to continue...");
    __fpurge(stdin);
    //getchar();
    getch();
    fclose(fp);
    updateCarCount(c);
    bookedCarDetails();
    return 1;
    }
void showCarDetails()
{
    FILE *fp=fopen("car.bin","rb");
    if(fp==NULL)
    {
        printf("No cars added yet!!");
        getch();
        return;
    }
    Car C;
    int i;
    printf(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=0;i<80;i++)
    {
        printf("%c",126);
    }
    gotoxy(31,5);
    printf("* CAR DETAILS *");
    gotoxy(1,7);
    printf(GREEN);
    for(i=0;i<80;i++)
    {
        printf("%c",126);
    }
    gotoxy(1,8);
    printf(" Car_Id\t\tName\t\tCapacity\tCar_Count\tPrice(Rs) ");
    gotoxy(1,9);
    for(i=0;i<80;i++)
    {
        printf("%c",126);
    }
    int x=10;
    printf(YELLOW);
    while(fread(&C,sizeof(C),1,fp)==1)
    {
        gotoxy(2,x);
        printf("%d\t\t%s\t\t%d\t\t%d\t\t%d",C.car_id,C.car_name,C.capacity,C.car_count,C.price);
        x++;
    }
    fclose(fp);
    __fpurge(stdin);
    //getchar();
    getch();
}

void availCarDetails()
{
    FILE *fp1=fopen("availcar.bin","rb");
    Car C;
    int i;
    printf(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=0;i<80;i++)
    {
        printf("%c",126);
    }
    gotoxy(31,5);
    printf("* AVAILABLE CAR DETAILS *");
    gotoxy(1,7);
    printf(GREEN);
    for(i=0;i<80;i++)
    {
        printf("%c",126);
    }
    gotoxy(1,8);
    printf(" Car_Id\t\tName\t\tCapacity\tCar_Count\tPrice(Rs) ");
    gotoxy(1,9);
    for(i=0;i<80;i++)
    {
        printf("%c",126);
    }
    int x=10;
    printf(YELLOW);
    while(fread(&C,sizeof(Car),1,fp1)==1)
    {
        gotoxy(2,x);
        printf("%d\t\t%s\t\t%d\t\t%d\t\t%d",C.car_id,C.car_name,C.capacity,C.car_count,C.price);
        x++;
    }
    fclose(fp1);
    __fpurge(stdin);
    //getchar();
    getch();
}

