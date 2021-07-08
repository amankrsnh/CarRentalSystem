//#include "myconio.h"
#include <stdio.h>
#include "car.h"
#include "color.h"
#include <unistd.h>
int main()
{
    gotoxy(25,10);
    printf(YELLOW  "WELCOME TO CAR RENTAL SYSTEM"  );
    gotoxy(20,13);
    printf(GREEN   "* RENT A CAR AND GO WHEREVER YOU NEED *" );
    getch();
    printf(YELLOW);
    addAdmin();
    User *usr;
    int result;
    int choice,type,i;
    while(1)
    {
        clrscr();
        gotoxy(32,2);
        printf(RED "CAR RENTAL SYSTEM"  );
        // UPPER LINE
        gotoxy(1,8);
        for(i=0;i<80;i++)
            printf(YELLOW  "*");
            // LOWER LINE
        gotoxy(1,17);
        for(i=0;i<80;i++)
            printf("*");
        gotoxy(32,10);
        printf(YELLOW "1. ADMIN");
        gotoxy(32,12);
        printf("2. EMPLOYEE"  );
        gotoxy(32,14);
        printf(WHITE);
        int k;
        printf("Select your role :");
        do
        {
            scanf("%d",&type);
            k=0;
            if(type==1)
            {//code for handling admin login
                do
                {
                    usr=getInput();
                    if(usr!=NULL)
                    {//code for validating userid and password
                        k=checkUserExist(*usr,"admin");
                    }
                    else
                    {
                        break;
                    }
                }while(k==0);
                if(k==1)
                {
                    gotoxy(32,14);
                    printf(GREEN  "Login Accepted!");
                    gotoxy(1,20);
                    printf(WHITE  "Press any key to continue...");
                    getch();

                while(1)
                {
                    clrscr();
                    choice=adminMenu();
                    if(choice==7)
                    {
                        clrscr();
                        break;
                    }
                    switch(choice)
                    {
                        case 1:
                                clrscr();
                                addEmployee();
                                break;
                        case 2:
                                clrscr();
                                addCarDetails();
                                break;
                        case 3:
                                clrscr();
                                viewEmployee();
                                break;
                        case 4:

                                clrscr();
                                showCarDetails();
                                break;
                        case 5:
                                clrscr();
                                result=deleteEmp();
                                if(result==0)
                                {
                                    gotoxy(15,14);
                                    printf(RED  "Sorry! No employee with the given Employee Id\n");
                                    printf(WHITE  "Press any key to go back to the main menu");
                                    __fpurge(stdin);
                                    //getchar();
                                    getch();
                                }
                                if(result==1)
                                {
                                    gotoxy(25,14);
                                    printf(GREEN  "Record Deleted Successfully");
                                    printf(WHITE  "\n\nPress any key to go back to the main menu");
                                    __fpurge(stdin);
                                    //getchar();
                                    getch();
                                }
                                break;
                        case 6:
                                clrscr();
                                result=deleteCarModel();
                                if(result==0)
                                {
                                    gotoxy(15,14);
                                    printf(RED  "Sorry! No Car with the given Car Id\n");
                                    printf(WHITE  "Press any key to go back to the main menu");
                                    __fpurge(stdin);
                                    //getchar();
                                    getch();
                                }
                                if(result==1)
                                {
                                    gotoxy(25,14);
                                    printf(GREEN  "Record Deleted Successfully");
                                    printf(WHITE  "\n\nPress any key to go back to the main menu");
                                    __fpurge(stdin);
                                    //getchar();
                                    getch();
                                }
                                break;
                        default:
                                gotoxy(1,18);
                                printf(RED   "Incorrect Choice!!");
                                getch();
                    }
                }
                }
            }
            else if(type==2)
            {//code for handling employee login
                do
                {
                    usr=getInput();
                    if(usr!=NULL)
                    {//code for validating userid and password
                        k=checkUserExist(*usr,"emp");
                    }
                    else
                    {
                        break;
                    }
                }while(k==0);
                if(k==1)
                {
                    gotoxy(30,14);
                    printf(GREEN  "Login Accepted!");
                    gotoxy(1,20);
                    printf(WHITE  "Press any key to continue...");
                    getch();

                while(1)
                {
                    clrscr();
                    choice =empMenu();
                    if(choice==5)
                    {
                        clrscr();
                        break;
                    }
                    switch(choice)
                    {
                        case 1:
                            clrscr();
                            int j;
                            do
                            {
                                clrscr();
                                j=rentCar();
                                if(j==0)
                                {
                                    printf("Booking Cancelled\nTry again!");
                                    getch();
                                }
                            }while(j==0);
                            //getch();
                            break;
                        case 2:
                            clrscr();
                            bookedCarDetails();
                            getch();
                            break;
                        case 3:
                            clrscr();
                            availCarDetails();
                            break;
                        case 4:
                            clrscr();
                            showCarDetails();
                            break;
                        default:
                            printf(RED   "Incorrect Choice!!");
                    }
                }
            }
        }
            else
            {
                getch();
                gotoxy(30,20);
                printf(RED "Invalid User Type!"  );
                gotoxy(30,20);
                printf("                    ");
                gotoxy(50,14);
                printf("        ");
                gotoxy(50,14);
                printf(WHITE);
            }

        }while(type!=1 && type!=2);

    }
    return 0;
}
