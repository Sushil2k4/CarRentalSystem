
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

char carTypeFinal[20];
//int choice1 = 0;

void printBorder(int j) {
    int i;
    for (i=0; i<=j; ++i)
        printf("\xcd");
}

void carList() {
    system("cls");
    int counter = 0, sno = 0, inv = 0, price = 0;
    char *availability;
    char cName[20];
    FILE *fp;
    int rCnt = 0, i = 0;
    system("cls");
    printHead();
    //printf("\n");
    //printf("\n");
    printf("\t\t ");
    printBorder(18);
    printf(" List Of Cars and Availability ");
    printBorder(18);
    printf("\n\t\t");
    printBorder(70);
    printf("\n");
    printf("\t\tS.No\tCar Type\tNo of Cars\tAvailability\tRate Per Day\n");
    printf("\t\t");
    printBorder(70);
    printf("\n");
    availability = "Available";
    rCnt = recordCnt("CarInventory.txt");
    fp = fopen("CarInventory.txt", "r");
    if(fp==NULL) //@Arnav
    {
        printf("Car Inventory File not found, Press Any Key to Continue....");
        getch();
    } //--
    while (i <= rCnt) {
        fscanf(fp, "%d %s %d %d", &sno, &cName, &inv, &price);
        ++i;
        if (inv == 0) {
            availability = "Not Available";
        }
        else //@Arnav
            availability ="Available"; //--
        printf("\t\t[%d] \t%-15s %3d   \t\t%-15s %10d\n", sno, cName, inv, availability, price); //@Arnav
        counter++;
    }
    fclose(fp);
    printf("\t\t");
    printBorder(70);
    printf("\n");
    //getch();
}

int updateCarFile(int choice) {
    FILE *fp, *ftemp;
    char cName[20], *dFile, *sFile;
    int ch = 0, inv = 0, newInv = 0, price = 0, xx = 0, rCnt = 0, i = 0;
    rCnt = recordCnt("CarInventory.txt");
    fp = fopen("CarInventory.txt", "r");
    if (fp == NULL) {
        printf("File Not found...");
        goto x;
    }
    ftemp = fopen("Temp1.txt", "w");
    do {
        fscanf(fp, "%d %s %d %d", &ch, &cName, &inv, &price);
        ++i;
        if (ch == choice) {
            if (inv != 0) {
                xx = price;
                newInv = inv - 1;
                fprintf(ftemp, "%d %s %d %d\n", ch, cName, newInv, price);
                strcpy(carTypeFinal, cName);
                //choice1 = ch;
            } else {
                fprintf(ftemp, "%d %s %d %d\n", ch, cName, inv, price);
                printf("\n\t\t");
                printBorder(70);
                printf("\n\t\t");
                printf("Invalid Choice. Please choose a car whose inventory is available.\n");
                printf("\n\t\t Press Any Key To Continue.....");
                getch();
            }
        } else {
            fprintf(ftemp, "%d %s %d %d\n", ch, cName, inv, price);
        }
    } while (i <= rCnt);
x:
    fclose(fp);
    fclose(ftemp);
    dFile = "CarInventory.txt";
    sFile = "Temp1.txt";
    updateFile(dFile, sFile);
    printf("File Copied...\n");
    getchar();
    return xx;
}

int recordCnt(char *tFile) {
    FILE *fp;
    int rCnt = 0, no = 0;
    char ch, prevChar;
    fp = fopen(tFile, "r");
    if (fp == NULL) {
        printf("File Not found..from recordCnt function...\n");
    }
    do {
        prevChar = ch;
        ch = fgetc(fp);
        if (prevChar == '\n' && ch == EOF)
            --rCnt;
        if (ch == '\n') {
            rCnt++;
            if (prevChar == '\n')
                rCnt--;
        }
    } while (ch != EOF);
    //printf("Record count: %d\n", rCnt); getch();
    fclose(fp);
    return rCnt;
}

void updateFile(char *dFile, char *tFile) {
    int sno = 0, inv = 0, price = 0;
    int cnt = 0, i = 0;
    char cName[20], tch;
    FILE *fp, *ftemp;
    cnt = recordCnt(tFile);
    fp = fopen(dFile, "w");
    ftemp = fopen(tFile, "r");
    tch=fgetc(ftemp);
    while (tch != EOF) {
        fputc(tch, fp);
        tch = fgetc(ftemp);

    }
    //fputc("\n",fp);
    fclose(fp);
    fclose(ftemp);
}

void carBooking() {
    int choice = 0, price = 0;
    system("cls");
    printHead();
    carList();
    printf("\t\t");
    printf("Enter Your Choice: ");
    scanf("%d", &choice);
    printf("\t\t");
    printBorder(70);
    price = updateCarFile(choice);
    if (price > 0) {
        printf("\t\t");
        printf("Enter Customer Name: ");
        char name[50];
        scanf("%s", &name);
        printf("\t\t");
        printf("Enter Customer Mobile No: ");
        int mobileNo;
        scanf("%d", &mobileNo);
        printf("\t\t");
        printf("No of Days to Book the Car: ");
        int days;
        scanf("%d", &days);
        int totalAmount = price * days;
        FILE *fp = fopen("CustData.txt", "a");
        fprintf(fp, "%s %d %s %d %d %d\n", name, mobileNo, carTypeFinal, price, days, totalAmount);
        fclose(fp);
        printf("\t\t");
        printBorder(70);
        printf("\n");
        printf("\t\t");
        printf("CONGRATULATIONS....Your car booking is confirmed.\n");
        printf("\t\t");
        printf("You have booked: %s for %d days and paid: %d\n", carTypeFinal, days, totalAmount);
        printf("\t\t");
        printf("Price per day is: %d\n\n", price);
        printf("\t\t");
        printf("Wish you a happy ride. Press any key to continue...\n");
        printf("\t\t");
        printBorder(70);
        printf("\n");
        getch();
    }
}

void carReturn() {
    FILE *fp, *fpt;
    char cName[20], cusName[20], carType[20], cType[20];
    int mobileNo, price, days, totalAmount, cnt, i = 0, xx, flag=0;
    system("cls");
    printHead();
    printf("\t\t  ");
    printBorder(25);

    printf(" Return the Car ");
    printBorder(25);

    cnt = recordCnt("CustData.txt");
    printf("\n");
    displayBookedCarList();
    printf("\t\t");
    printf("Enter Customer Name: ");
    scanf("%s", &cName);
    printf("\t\t");
    printf("Enter Car Type: ");
    scanf("%s", &cType);

    fp = fopen("CustData.txt", "r");
    if (fp == NULL) {
        printf("\t\t");
        printf("There is no bookings. Press any key to continue...");
        getch();
        return;
    }

    fpt = fopen("CustDataTemp.txt", "w");

    while (i<=cnt) {
        fscanf(fp, "%s %d %s %d %d %d", &cusName, &mobileNo, &carType, &price, &days, &totalAmount);
        ++i;
        if ((strcmp(strupr(cName), strupr(cusName)) == 0) && (strcmp (strupr(cType),strupr(carType))==0))
        {
            addInventory(strupr(carType)); //@arnav
            //printf("Matching...CarType %s\n", carType);
            *cName=' ';
            printf("\t\t");
            printBorder(70);
            flag=1;

            printf("\n\t\tYour Return is Successful... Press Any Key to Continue...");
            getch();

            // Here you can update the car inventory or perform other operations when a car is returned.
        } else {
            fprintf(fpt, "%s %d %s %d %d %d\n", cusName, mobileNo, carType, price, days, totalAmount);
            //printf("Writing in temp cust file..%s %d %s %d %d %d\n", cusName, mobileNo, carType, price, days, totalAmount); getch();
        }
    }
    fclose(fp);
    fclose(fpt);
    if(flag==0) {printf("\t\t Car Return Input is Incorrect...Please Try Again....");
    getch();}
    updateFile("CustData.txt", "CustDataTemp.txt");

}
displayBookedCarList()
{
    FILE *fp;
    int rCnt=0, phNo, price, days, totPrice, i=0;
    char cName[20], cType[20];
    rCnt=recordCnt("CustData.txt");
    fp = fopen("CustData.txt","r");
    printf("\t\t");
    printBorder(90);
    printf("\n\t\t");
    printf(" Name\t\tMobile No\tCar Type\tCar Price \t No Of Days \t Total Price\n");
    printf("\t\t");
    printBorder(90);
    printf("\n");
    while (i <= rCnt)
    {
        fscanf(fp, "%s %d %s %d %d %d", &cName, &phNo, &cType, &price, &days, &totPrice);
        ++i;
        printf("\t\t%-10s %10d   \t%-15s %10d \t%3d %20d\n", cName, phNo, cType, price, days, totPrice);
    }
    printf("\t\t");
    printBorder(90);
    printf("\n");
    fclose(fp);

}
addInventory(char carType[20]) //@Arnav
{
    FILE *fp, *fpt;
    char cType[20];
    int rCnt =0, i=0, sno, cnt, price;
    rCnt = recordCnt("CarInventory.txt");
    fp=fopen("CarInventory.txt","r");
    fpt = fopen("Temp1.txt","w");
    while(i<=rCnt)
    {
        fscanf(fp,"%d %s %d %d",&sno, &cType, &cnt, &price);
        //printf("Inside AddInventory...CarType %s %s, Count %d\n", carType, cType, cnt);
        if(strcmp(carType,strupr(cType))==0)
        {
          ++cnt;
          //printf("%s %s Increasing Inventory.....\n", carType, cType);
        }
        fprintf(fpt,"%d %s %d %d\n",sno, cType, cnt, price);
        ++i; cType[0]=" ";
    }
    fclose(fp);
    fclose(fpt);
    updateFile("CarInventory.txt","Temp1.txt");

}

printHead()
{
    printf("\n");
    printf("\t\t");
    printBorder(70);
    printf("\n");
    printf("\t\t\t\t\t   CAR RENTAL");
    printf("\n");
    printf("\t\t");
    printBorder(70);
    printf("\n\n");
}

int mainMenu() {
    system("cls");
    printf("Press Enter..");
    getchar();
    system("cls");
    printHead();
    printf("\t\t\t\t \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd MAIN MENU \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n\n");
    printf("\t\t\t\t [1] View Car List\n\n");
    printf("\t\t\t\t [2] Book A Car\n\n");
    printf("\t\t\t\t [3] Return the Car\n\n");
    printf("\t\t\t\t [4] View Booked Car\n\n");
    printf("\t\t\t\t [0] Exit\n\n");
    printf("\t\t");
    printBorder(70);
    printf("\n\t\t\t  Enter Your Choice: ");
    int choice = 0;
    scanf("%d", &choice);
    return choice;
}

void login() {
    int a=0,i=0;
    char uname[10],c=' ';
    char pword[10],code[10];
    char username[10],passw[10];
    FILE *fp;
    do
    {
        system("cls");
        printf("\n");
        printf("\t\t");
        printBorder(90);
        printf("\n\t\t\t\t\t CAR RENTAL SYSTEM\n");
        printf("\t\t");
        printBorder(90);
        printf("\n\t\t\t\t\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd LOGIN FORM \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd ");
        printf("\n\n \t\tENTER USERNAME: ");
        scanf("%s", &uname);
        printf(" \n \t\tENTER PASSWORD: ");
        while(i<10)
        {
            pword[i]=getch();
            c=pword[i];
            if(c==13) break;
            else printf("*");
            i++;
        }
        pword[i]='\0';
        i=0;
        fp=fopen("Logindetails.txt","r");
        if(fp==NULL){
            printf("file not found");
        }
        fscanf(fp,"%s %s",&username,&passw);
        if((strcmp(uname,username)==0) && (strcmp(pword,passw)==0))
        {
            printf("\n \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd");
            printf(" \n\n WELCOME USER !!!!");
            printf("\n\n\n Press any key to continue...");
            getch();//holds the screen
            break;
        }
        else
        {
            printf("\n \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd");
            printf("\n\n LOGIN IS UNSUCESSFUL...PLEASE TRY AGAIN...");
            a++;
            continue;
            getch();//holds the screen
        }
        fclose(fp);
    }
    while(a<=2);
    if (a>2)
    {
        printf("\nSorry you have entered the wrong username and password for four times!!!");
        getch();
    }
    system("cls");
}

int main() {
    int choice = 0;
    login();

    do {
        choice = mainMenu();
        switch (choice) {
            case 1:
                carList();
                printf("\n\t\t Press Any Key To Continue.......");
                getch();
                break;
            case 2:
                carBooking();
                break;
            case 3:
                carReturn();
                break;
            case 4:
                displayBookedCarList();
                printf("\t\t Press Any Key To Continue.....");
                getch();
                break;
            case 0:
                break;
            default:
                printf("Not a correct choice. Please try again...\n");
        }
    } while (choice != 0);

    return 0;
}

