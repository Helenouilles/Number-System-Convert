#include<stdio.h>  // for: input & output 
#include<stdlib.h> // for: exit(0) function 
#include<conio.h>  // for: getch() function 
#include<ctype.h>  // for: isdigit(variable-name) function 

// Define Constant KeyWords: for tracking user key press event (used in: HexaDecimal input validation) 
#define ENTER 13
#define TAB 9
#define BKSP 8

void welcomeScreen(void);  // Introduction Page & choice screen 
void exitScreen(void);     // program end screen with credits 
void screenCleaner(void);  // clears the output screen and input buffers 
void userInput(int);    // takes the user input and validates for further opertaions 
int digitChecker(int, int);  // validates each digit of input number 

// Binary Conversion functions 
void binary_decimal(long int);
void binary_octal(long int);
void binary_hexadecimal(long int);

// Decimal Conversion functions 
void decimal_binary(long int);
void decimal_octal(long int);
void decimal_hexadecimal(long int);

// Octal Conversion functions 
void octal_binary(long int);
void octal_decimal(long int);
void octal_hexadecimal(long int);

// Hexadecimal Convesion functions 
void hexadecimal_binary(char []);
void hexadecimal_octal(char []);
void hexadecimal_decimal(char []);

// C-Program main function 
void main()
{
    welcomeScreen();
}

// Intro screen 
void welcomeScreen()
{
    int choice;

label1:
    screenCleaner();
    printf("-------------------------------------------\n");
    printf(">>> Welcome to Number System Converter <<< \n");
    printf("-------------------------------------------\n\n");

    printf(">> Select Conversion Type: \n");
    printf("> 1. Binary Conversion \n");
    printf("> 2. Decimal Conversion \n");
    printf("> 3. Octal Conversion \n");
    printf("> 4. Hexadecimal Conversion \n");
    printf("> 5. Exit the Program \n\n");
    printf("Enter the number & Hit ENTER: ");
    scanf("%d", &choice);

    // passes the user input for conversion 
    switch(choice)
    {
        case 1:
            userInput(1);
            break;
        case 2:
            userInput(2);
            break;
        case 3:
            userInput(3);
            break;
        case 4:
            userInput(4);
            break;
        case 5:
            exitScreen();
            break;
        default:
            printf("\nError: the number must be between 1 to 5.\n");
            printf("Press any key to continue... \n");
            getch();
            goto label1;
    }
}

// program exit screen (credit page) 
void exitScreen()
{
    screenCleaner();
    printf("-------------------------------------------\n");
    printf(" >>> Creator: @Alkaison (Ganesh Mourya) <<< \n");
    printf("-------------------------------------------\n\n");

    printf("> GitHub: https://github.com/Alkaison \n");
    printf("> Twitter: https://twitter.com/Alkaison \n");
    printf("> LinkedIn: https://www.linkedin.com/in/Alkaison \n\n");

    exit(0);  // exit() function to close the program safely 
}

void screenCleaner()
{
    system("cls");  // clears the output screen 
    fflush(stdin);  // clears the input buffer 
}

void userInput(int choice)
{
    screenCleaner();

    if(choice == 1) // Binary input validation code 
    {    
        long int bi;
        int flag = 0;

        printf("Enter the binary: ");
        scanf("%ld", &bi);

        flag = digitChecker(bi, choice);

        if(flag == 1)
        {
            printf("\nError: Binary can only have the digits 0, 1. \n");
            printf("Press any key to continue... \n");
            getch();
            welcomeScreen();
        }
        else
        {
            binary_decimal(bi);
            binary_octal(bi);
            binary_hexadecimal(bi);
        }
    }
    else if(choice == 2)  // Decimal input validation code 
    {
        long int deci;
        int flag = 0;

        printf("Enter the decimal: ");
        scanf("%ld", &deci);

        if(deci > 0)
            flag = digitChecker(deci, choice);
        else
            flag = 1;
        
        if(flag == 1)
        {
            printf("\nError: Decimal number can't be negative. \n");
            printf("Press any key to continue... \n");
            getch();
            welcomeScreen();
        }
        else
        {
            decimal_binary(deci);
            decimal_octal(deci);
            decimal_hexadecimal(deci);
        }
    }
    else if(choice == 3)  // Octal input validation code 
    {
        long int octal;
        int flag = 0;

        printf("Enter the octal: ");
        scanf("%ld", &octal);

        flag = digitChecker(octal, choice);
  
        if(flag == 1)
        {
            printf("\nError: Octal digits can only be between 0 to 7. \n");
            printf("Press any key to continue... \n");
            getch();
            welcomeScreen();
        }
        else
        {
            octal_binary(octal);
            octal_decimal(octal);
            octal_hexadecimal(octal);
        }
    }
    else if(choice == 4)  // HexaDecimal input validation code 
    {
        char hexa[50];
        char ch;
        int i=0, j=0, k=0, flag=0;

        printf("Enter the hexadecimal: ");

        while(1)
        {
            ch = getch();
            if(ch == ENTER || ch == TAB)
            {
                hexa[i] = '\0';
                break;
            }
            else if(ch == BKSP)
            {
                if(i > 0)
                {
                    i--;
                    printf("\b \b"); // for backspace
                }
            }
            else
            {
                hexa[i++] = ch;
                printf("%c", ch);
            }
        }   

        for(j=0; j<i; j++)
        {
            if((hexa[j] >= 'A' && hexa[j] <= 'F') || (hexa[j] >= 'a' && hexa[j] <= 'f') || isdigit(hexa[j]))
                k++;
            else
            {
                flag = 1;
                break;
            }
        }   

        if(flag == 1)
        {
            printf("\n\nError: Hexadecimal digits can only be between 0 to 9 & A to F. \n");
            printf("Press any key to continue... \n");
            getch();
            welcomeScreen();
        }
        else
        {
            hexadecimal_binary(hexa);
            hexadecimal_octal(hexa);
            hexadecimal_decimal(hexa);
        }
    }
    else  // Very rare case message 
        printf("\n>> Unexpected Error occured. Report to program Administrator << \n");
}

// validation function for each single digit of a number according to conversion condition 
int digitChecker(int num, int choice)
{
    long int rem, temp=0, flag=0;
    temp = num;

        while(temp != 0)
        {    
            rem = temp % 10;

            if((rem == 0 || rem == 1) && choice == 1) // binary, choice = 1 
                temp = temp / 10;
            else if(rem >= 0 && rem <= 9 && choice == 2) // decimal, choice = 2
                temp = temp / 10;
            else if(rem >= 0 && rem <=7 && choice == 3) // octal, choice = 3
                temp = temp / 10;
            else
            {
                flag = 1;
                break;
            }
        }
    return flag;
}

// Binary Conversion functions
void binary_decimal(long int bi)
{

}

void binary_octal(long int bi)
{

}

void binary_hexadecimal(long int bi)
{

}

// Decimal Conversion functions 
void decimal_binary(long int deci)
{

}

void decimal_octal(long int deci)
{

}

void decimal_hexadecimal(long int deci)
{

}

// Octal Conversion functions 
void octal_binary(long int octal)
{

}

void octal_decimal(long int octal)
{

}

void octal_hexadecimal(long int octal)
{

}

// Hexadecimal Convesion functions 
void hexadecimal_binary(char hexa[])
{

}

void hexadecimal_octal(char hexa[])
{

}

void hexadecimal_decimal(char hexa[])
{

}