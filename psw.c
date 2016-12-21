/*
    Password manager:
        
        - Enter password to access the program :
            - Register :
                - Are you sure that you want this password?      DONE
            - Login         DONE 
        - Crypt/decrypt               DONE
        - Create files if they don't already exist   DONE
        - When to crypt/decrypt for the passwords    DONE
        - When to crypt/decrypt for the main password             MAYBE DONE
        
        
        - Error checking if the person closed the program while entering a record    NOT STARTED
        
        
        - Menu       DONE
        - Enter      DONE         
        - Display   DONE
        - Option select      DONE
        - List records  DONE
        - Delete        DONE 
            - Position found
            - Temp created
            - Overwriting  done
        - Edit password                                       DONE          

        Main pass nu se mai cripteaza iar cand pornesc programul iar se decripteaza desi nu este nevoie 
        Cand inchid programul gresit. A doua oara cand il deschid apare doar mesajul ca l-am inchis din greseala si nu imi mai cere parola ca sa il deschid
        se crypteaza sau decrypteaza de doua ori cand il inchid gresit.
        Cred ca problema este cand decrypt_access este chemat. Trebuie sa existe o conditie care verifica daca este nevoie de decriptare
        
        - Crypt          DONE 
        - Delete_Temp    DONE
*/

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
struct record
{
    char title[25];
    char username[30];
    char password[30];
    char email[35];
    char notes[50];    
};

//Global declaration area
static int number=1;

// Function prototypes
void secret_access(void);
void crypt_access(void);
void decrypt_access(void);
void crypt(void);
void decrypt(void);
int to_crypt_or_not_to_crypt(void);
int crypt_main_pass(void);
void menu(void);
int option_select(int);
void enter(void);
void display(void);
void list_records(void);
void delete_record(void);
void delete_temp(void);
void edit_password(void);
void list(void);
void exit(void);  
void yesorno(void);

// Global declaration area
int global_exit_condition;

main()
{
    // Declaration Area
    FILE *fp1, *fp2;
    int answer, condition, crypt_value, main_pass_crypt, first_run=0;
    
    
    // Code Area
    
    // Checking if the main pass file (crypt_condition.txt) was closed properly 
    global_exit_condition=0;
    
    main_pass_crypt = crypt_main_pass();
    if(main_pass_crypt == 1)
    {
        fp2=fopen("access_crypt.txt", "w");
        fprintf(fp2, "0");
        fclose(fp2);
        
        secret_access();
        
    }
    else
    {
        if(main_pass_crypt == 0)               // Aici este eroarea. Problema: se decrypteaza cand nu este nevoie
        {
            system("cls");        
            printf("\t\t\t\t\tYou closed the program in an improper way. \n\t\t\t\t\tThis could leave your main password uncrypted.");
            printf("\n\t\t\t\t\tPlease close the program properly");
            
            getchar();
            secret_access(); 
        }
        else
        {
            first_run=1;         // This branch means that it's the first time when we open the program
        }                            
    }
    
    
    
    
    crypt_value= to_crypt_or_not_to_crypt();
    if( crypt_value == 1)                      // Marking the program as not closed properly
    {
        fp1= fopen("crypt_condition.txt", "w");
        if(fp1==NULL)
        {
            printf("Error could not open Crypt_condition.txt");
            getchar();
            exit(1);
        }
        fprintf(fp1, "0");
        fclose(fp1);
        
        decrypt();
    }
    else
    {
        if(crypt_value == 0)
        {                
            system("cls");
            
            printf("\t\t\t\t\tYou closed the program in an improper way. \n\t\t\t\t\tThis could leave passwords uncrypted.");
            printf("\n\t\t\t\t\tPlease close the program properly");
            
            getchar();
            secret_access();             
        }
        else
        {
            first_run=1;                  // This branch means that it's the first time when we open the program       
        }
    }
    
    if(first_run==1)
    {
        secret_access();
    }
    
    do
    {
        
        menu();
        if(global_exit_condition==0)
        {
            do
            {
                printf("\t\t");
                scanf("%d", &answer);
                flushall();
                condition=option_select(answer);
            }
            while(condition == 1);
        }
        else
        {
            answer=6;
            system("cls");
        }
    }
    while(answer != 6);
    
    main_pass_crypt = crypt_main_pass();
    if(main_pass_crypt == 0)
    {                     
        fp1=fopen("access_crypt.txt","w");
        if(fp1==NULL)
        {
            printf("Error could not open access_crypt.txt");
            getchar();
            exit(1);
        }
        fprintf(fp1, "1");
        fclose(fp1);
        
    }
    
    crypt_value= to_crypt_or_not_to_crypt();
    if( crypt_value == 0)                      // Marking the program as closed properly
    {
        fp1= fopen("crypt_condition.txt", "w");
        if(fp1==NULL)
        {
            printf("Error could not open Crypt_condition.txt");
            getchar();
            exit(1);
        }
        fprintf(fp1, "1");
        fclose(fp1);
        
        crypt();
        
    }                         
    
}// End main

void secret_access(void)
{
    // Declaration area
    char secret_access_code[30], secret_access_code_fp2[30];
    char set_password[30], decision_answer[10];
    FILE *fp1, *fp2;
    int read_secret;
    
    // Code area
    
    decrypt_access();               // Put condition if Access2.bin was not crypted
    
    fp1= fopen("Access.bin", "r");
    if(fp1==NULL)
    {
        fclose(fp1);
        fp1=fopen("Access.bin","w");
        fclose(fp1);                              // Creating the "Access.bin" file if it doesn't already exist
        fp1=fopen("Access.bin","r");
    }
    
    // Register test
    if( (fscanf(fp1, "%d", &read_secret ) == 1 ) )      
    {
        fp2=fopen("Access2.bin", "r");                 
        if(fp2==NULL)
        {
            printf("Could not open Access2.bin"); 
        }
        
        fscanf(fp2, "%s", secret_access_code_fp2);
        flushall();
        fclose(fp1);
        fclose(fp2);
        
    }
    else
    {
        fp2= fopen("Access2.bin", "w");
        if(fp2==NULL)
        {
            printf("\n Error. Could not open Access2.txt\n");
        }
        
        
        
        // Setting up the password to protect the file
        system("cls");
        printf("\t\t\t\tYou don't have a password set up yet\n ");
        printf("\t\t\t\tPlease set up your password\n");
        printf("\t\t\t\tOr type \"exit\" in order to close the program: ");          // EXIT is recognized but the program keeps going and puts 1 in the access file
        
        do
        {
            scanf("%s", set_password);
            flushall();
            system("cls");
            
            
            // TEST HERE           <---------------------------------------------------
            if(((strcmp(set_password,"Exit"))==0) || ((strcmp(set_password,"exit"))==0) || ((strcmp(set_password,"EXIT"))==0) ) 
            {
                exit();
                global_exit_condition=1;
                break;// HERE
            }
            
            
            
            
            textcolor(CYAN);
            printf("\t\t\t");
            cprintf("Are you sure that you want ");
            textcolor(LIGHTCYAN);
            cprintf("%s ", set_password);
            textcolor(CYAN);
            cprintf("to be your password?");
            yesorno();
            printf("\t\t\t");
            scanf("%s", decision_answer);
            flushall();
            
            if((strcmp(decision_answer,"Yes")!=0) && (strcmp(decision_answer,"yes")!=0) && (strcmp(decision_answer,"y")!=0) && (strcmp(decision_answer,"Y")!=0))
            {
                system("cls");
                if((strcmp(decision_answer,"No")!=0) && (strcmp(decision_answer,"no")!=0) && (strcmp(decision_answer,"n")!=0) && (strcmp(decision_answer,"N")!=0))
                {
                    do
                    {
                        system("cls");
                        printf("\t\t\t\t\t\tAnswer not recognized\n\t\t\t\t\t\tTry again");
                        
                        textcolor(YELLOW);
                        cprintf("(");
                        textcolor(LIGHTGREEN);
                        cprintf("Y");
                        textcolor(YELLOW);
                        cprintf("/");
                        textcolor(LIGHTGREEN);
                        cprintf("N");
                        textcolor(YELLOW);
                        cprintf(")");
                        printf(": ");
                        scanf("%s", decision_answer);
                        flushall();
                        
                    }while((strcmp(decision_answer,"No")!=0) && (strcmp(decision_answer,"no")!=0)
                    && (strcmp(decision_answer,"n")!=0) && (strcmp(decision_answer,"N")!=0) &&
                    (strcmp(decision_answer,"Yes")!=0) && (strcmp(decision_answer,"yes")!=0) && 
                    (strcmp(decision_answer,"y")!=0) && (strcmp(decision_answer,"Y")!=0));
                    
                    if((strcmp(decision_answer,"No")==0) || (strcmp(decision_answer,"no")==0)
                    || (strcmp(decision_answer,"n")==0) || (strcmp(decision_answer,"N")==0))
                    {
                        system("cls");
                        printf("\t\t\t\t\t\tChoose another password: ");
                    }
                }
                else
                {
                    printf("\t\t\t\t\t\tChoose another password: ");
                }
            }
        }while( (strcmp(decision_answer,"Yes")!=0) && (strcmp(decision_answer,"yes")!=0) && (strcmp(decision_answer,"y")!=0) && (strcmp(decision_answer,"Y")!=0) );   
        
        system("cls");
        textcolor(LIGHTGREEN);
        printf("\t\t\t");
        
        
        
        
        if(((strcmp(set_password,"Exit"))!=0) && ((strcmp(set_password,"exit"))!=0) && ((strcmp(set_password,"EXIT"))!=0) )
        {
            fprintf(fp2, "%s", set_password);
            fclose(fp1);
            fp1= fopen("Access.bin", "w");
            fprintf(fp1, "1");
            strcpy(secret_access_code_fp2, set_password);
        }
        
        fclose(fp1);
        fclose(fp2);
    }
    
    
    // Login 
    if(((strcmp(set_password,"Exit"))!=0) && ((strcmp(set_password,"exit"))!=0) && ((strcmp(set_password,"EXIT"))!=0) )
    {
        
        do
        {                          // Add some colours here?
            system("cls");
            printf("\n\t\t\tEnter the password so you can access the records.\n\t\t\tOr type \"exit\" to close the program: ");
            scanf("%s", secret_access_code);
            flushall();
            
            if(((strcmp(secret_access_code,"Exit"))==0) || ((strcmp(secret_access_code,"exit"))==0) || ((strcmp(secret_access_code,"EXIT"))==0) ) 
            {
                exit();
                global_exit_condition=1;
                break;
            }
            if((strcmp(secret_access_code,secret_access_code_fp2))==0)
            {
                system("cls");
                printf("\t\t\t\t\t\t");
                textcolor(LIGHTGREEN);
                cprintf("Access granted!");
                getchar();
            }
            else
            {
                system("cls");
                printf("\t\t\t\t\t\t");
                textcolor(LIGHTRED);
                cprintf("Wrong password!");
                getchar();
            }
        }while((strcmp(secret_access_code,secret_access_code_fp2))!=0);            
    }// end if answer is exit
    
    
    
    crypt_access();
}// End secret_access

int crypt_main_pass(void)   // Aici cred ca este problema lunga
{
    FILE *fp1;
    int crypt_condition;
    
    fp1=fopen("access_crypt.txt", "r");         // FIXED
    
    if(fp1==NULL)
    {
        fclose(fp1);
        fp1=fopen("access_crypt.txt", "w");
        fprintf(fp1, "0");
        fclose(fp1);
    }
    else
    {
        
        if(fscanf(fp1, "%d", &crypt_condition) == EOF)
        {
            fclose(fp1);
            fp1=fopen("access_crypt.txt", "w");
            fprintf(fp1, "0");
            fclose(fp1);
            return(3);
        }            
        else
        {
            return(crypt_condition);
        }
    }
    fclose(fp1);
    return(3);
    
}// end crypt_main_pass
int to_crypt_or_not_to_crypt(void)
{
    FILE *fp1;
    int closing_error;
    
    fp1= fopen("crypt_condition.txt","r");         // Fixed
    if(fp1==NULL)
    {
        fclose(fp1);
        fp1=fopen("crypt_condition.txt", "w");
        fprintf(fp1, "0");
        fclose(fp1);
    }
    else
    {
        
        if(fscanf(fp1, "%d", &closing_error) == EOF)
        {
            fclose(fp1);
            fp1=fopen("crypt_condition.txt", "w");
            fprintf(fp1, "0");
            fclose(fp1);
            return(3);
        }            
        else
        {
            return(closing_error);
        }
    }
    fclose(fp1);
    return(3);
    
} // End to_crypt_or_not_to_crypt

void crypt_access(void)
{
    FILE *fp1, *fp2;               //Fixed
    char read;
    int ret, ascii;
    
    fp1=fopen("Access2.bin", "rb");
    fp2=fopen("Access2_scramble.bin", "wb");
    
    if((fp1==NULL) || (fp2==NULL))
    {
        fclose(fp1);
        fp1=fopen("Access2.bin", "wb");
        fclose(fp1);
        fp1=fopen("Access2.bin", "rb");
    }
    
    while(fread(&read, 1, 1, fp1)==1)
    {
        ascii= read;
        ascii+=3;
        fprintf(fp2,"%c", ascii);
    }
    fclose(fp1); fclose(fp2);
    
    fp1=fopen("Access2.bin", "wb");
    fp2=fopen("Access2_scramble.bin", "rb");
    if((fp1==NULL) || (fp2==NULL))
    {
        printf("Could not crypt \"Access2.bin\"!\n");
    }
    
    while(fread(&read, 1, 1, fp2)==1)
    {
        fwrite(&read, 1, 1, fp1);
    }
    fclose(fp1); fclose(fp2);
    
    ret = remove("Access2_scramble.bin");
    if(ret != 0) 
    {
        printf("Error: unable to delete the temp file!");
    }
    
}// End crypt_access

void decrypt_access(void)
{                                   
    FILE *fp1, *fp2;                   //Fixed
    char read;
    int ret, ascii;
    
    fp1=fopen("Access2.bin", "rb");
    fp2=fopen("Access2_unscramble.bin", "wb");
    if((fp1==NULL) || (fp2==NULL))
    {
        fclose(fp1);
        fp1=fopen("Access2.bin", "w");
        fclose(fp1);
        fp1=fopen("Access2.bin", "rb");
    }
    
    // Decrypting psw 
    while(fread(&read, 1, 1, fp1)==1)
    {
        ascii= read;
        ascii-=3;
        fprintf(fp2,"%c", ascii);
    }
    fclose(fp1); fclose(fp2);
    
    fp1=fopen("Access2.bin", "wb");
    fp2=fopen("Access2_unscramble.bin", "rb");
    if((fp1==NULL) || (fp2==NULL))
    {
        exit(1);
    }
    
    // Copying the contents into psw
    while(fread(&read, 1, 1, fp2)==1)
    {
        fwrite(&read, 1, 1, fp1);
    }
    fclose(fp1); fclose(fp2);
   
    ret = remove("Access2_unscramble.bin");
    if(ret != 0) 
    {
        printf("Error: unable to delete the temp file!");
    } 

}// End decrypt_access

void decrypt(void)
{
    FILE *fp1, *fp2;          // Fixed
    char read;
    int ret, ascii;
    
    fp1=fopen("psw.bin", "rb");
    fp2=fopen("psw_unscramble.bin", "wb");
    
    if((fp1==NULL) || (fp2==NULL))
    {
        fclose(fp1);
        fp1=fopen("psw.bin","wb");
        fclose(fp1);
        fp1=fopen("psw.bin","rb");
    }
    
    // Decrypting psw 
    while(fread(&read, 1, 1, fp1)==1)
    {
        ascii= read;
        ascii-=3;
        fprintf(fp2,"%c", ascii);
    }
    fclose(fp1); fclose(fp2);
    
    fp1=fopen("psw.bin", "wb");
    fp2=fopen("psw_unscramble.bin", "rb");
    if((fp1==NULL) || (fp2==NULL))
    {
        exit(1);
    }
    
    // Copying the contents into psw
    while(fread(&read, 1, 1, fp2)==1)
    {
        fwrite(&read, 1, 1, fp1);
    }
    fclose(fp1); fclose(fp2);
   
    ret = remove("psw_unscramble.bin");
    if(ret != 0) 
    {
        printf("Error: unable to delete the temp file!");
    } 
    
}// End decrypt

void menu(void)
{
    system("cls");
    list();
    printf("Enter record");
    list();
    printf("Read records");
    list();
    printf("List records");
    list();
    printf("Edit record");
    list();
    printf("Delete record");
    list();
    printf("Exit\n\n");
} // End menu

int option_select(int answer)
{
    
    switch(answer)
    {
        case 1:
        {
            enter();
            break;
        }
        case 2:
        {
            display();
            break;
        }
        case 3:
        {
            list_records();
            break;
        }
        case 4:
        {
            edit_password();
            break;
        }
        case 5:
        {
            delete_record();
            break;
        }
        case 6:
        {
            exit();
            break;
        }
        default:
        {
            return(1);
        }
    }// End switch
    
    return(0);
} // End option_select

void enter(void)
{
    FILE *fp1;                     // Fixed
    struct record read;
    struct record test;
    int condition;
    
    fp1=fopen("psw.bin", "r"); 

    if(fp1==NULL)
    {
        fclose(fp1);
        fp1=fopen("psw.bin", "w");
        fclose(fp1);
        fp1=fopen("psw.bin", "r");
    }

    system("cls");
    textcolor(CYAN);
    do
    {
        condition=0;
        cprintf("Title: ");
        scanf("%s", read.title);
        flushall();
        fseek(fp1, 0, SEEK_SET);
        while(fscanf(fp1, "%s %s %s %s %s", test.title, test.username, test.password, test.email, test.notes )!= EOF)
        {
            if((strcmp(read.title, test.title))==0)
            {
                condition=1;
            }
        }
        if(condition==1)
        {
            system("cls");
            printf("The record with this name already exists!\n");
        }
    }
    while(condition==1);
    
    fclose(fp1);
    
    fp1=fopen("psw.bin", "a");
    if(fp1==NULL)
    {
        exit(1);
    }
    
    cprintf("Username: ");
    scanf("%s", read.username);
    cprintf("password: ");
    scanf("%s", read.password);
    cprintf("Email used: ");
    scanf("%s", read.email);
    cprintf("Notes: ");
    scanf("%s",read.notes);

    fprintf(fp1,"%s %s %s %s %s\n", read.title, read.username, read.password, read.email, read.notes);
    
    system("cls");
    textcolor(LIGHTGREEN);
    cprintf("Record added!");
    getchar();
    fclose(fp1);
    number=1;
} // End enter

void display(void)
{
    struct record get;               // Fixed
    char name[20];
    
    FILE *fp1;
    
    fp1= fopen("psw.bin", "r");
    
    if(fp1==NULL)
    {
        fclose(fp1);
        fp1=fopen("psw.bin", "w");
        fclose(fp1);
        fp1=fopen("psw.bin", "r");
    }
    
    system("cls");
    textcolor(CYAN);
    cprintf("Site name: ");
    gets(name);
    
    // Find and display the record
    while(fscanf(fp1, "%s %s %s %s %s", get.title, get.username, get.password, get.email, get.notes )!= EOF)
    {
        if((strcmp(get.title, name))==0)
        {
            printf("\nTitle: %s\n Username: %s\n Password: %s\n Email: %s\n Notes: %s", get.title, get.username, get.password, get.email, get.notes);
            break;
        }
    }
    if(strcmp(get.title, name)!=0)
    {
        printf("Nu exista acest record");
    }
    number=1;
    getchar();
    system("cls");
    fclose(fp1);
} // End display

void list_records(void)
{
    struct record get;              // Fixed
    FILE *fp;
    
    fp=fopen("psw.bin", "rb");
    if(fp==NULL)
    {
        fclose(fp);
        fp=fopen("psw.bin", "w");
        fclose(fp);
        fp=fopen("psw.bin", "r");
    }
    system("cls");
    
    textcolor(CYAN);
    cprintf("The list of your current saved records:");
    printf("\n");
    
    while((fscanf(fp, "%s %s %s %s %s", get.title, get.username, get.password, get.email, get.notes))!= EOF )
    {
        printf(" -%s\n", get.title);
    }
    
    getchar();
    number=1;
} // end list_records


void delete_record(void)
{
    // Declaration Area
    FILE *fp1, *fp2;
    char name[15];
    struct record get;
    int index=1, index2=0, condition=0;
    
    // Code Area
    fp1= fopen("psw.bin", "rb+wb");
    if(fp1==NULL)
    {
        exit(1);
    }
    system("cls");
    
    textcolor(CYAN);
    cprintf("Delete record: ");
    gets(name);

    // Finding the position of the deleting file
    fseek(fp1, 0, SEEK_SET);
    while((fscanf(fp1, "%s %s %s %s %s", get.title, get.username, get.password, get.email, get.notes))!= EOF )
    { 
        if(strcmp(get.title, name)==0)
        {
            condition=1;
            break;
        }
        else                                            
        {
            index++;
        }
    }
    
    // Creating the temp file
    if(condition==1)   // condition==1 means that there the record exists in the list
    {
        fp2= fopen("Temp.bin", "w");
        if(fp2==NULL)
        {
            exit(1);
        }
        fseek(fp1, 0, SEEK_SET);
        while((fscanf(fp1, "%s %s %s %s %s", get.title, get.username, get.password, get.email, get.notes))!= EOF )
        {
            index2++;
            if(index2!=index)
            {
                fprintf(fp2, "%s %s %s %s %s\n", get.title, get.username, get.password, get.email, get.notes);
            }
        } // End while
        
        
        fclose(fp1); fclose(fp2);
        
        fp1=fopen("psw.bin", "w");
        fp2=fopen("temp.bin", "r");
        if((fp2==NULL) || (fp1==NULL))
        {
            printf("ERROR file not opened\n");      // copying from temp file to  the original
        }
        
        while((fscanf(fp2, "%s %s %s %s %s", get.title, get.username, get.password, get.email, get.notes))!= EOF )
        {
            fprintf(fp1, "%s %s %s %s %s\n", get.title, get.username, get.password, get.email, get.notes);
        }
        
        fclose(fp1); fclose(fp2);
        
        delete_temp();
        printf("\n The record was deleted");    
    }
    else
    {
        printf(" There record \"%s\" does not exist!\n", name);
    }
    
    getchar();
    number=1;
} // Delete_record

void delete_temp(void)
{
    // Declaration Area
    int ret;
    
    // Code Area
    ret = remove("temp.bin");
    if(ret != 0) 
    {
        printf("Error: unable to delete the temp file!");
    }
} // End delete_temp

void edit_password(void)
{
    FILE *fp1, *fp2;
    char name[15], new_password[30];
    struct record get;
    int index=1, index2=0, condition=0;
    
    // Code Area
    fp1= fopen("psw.bin", "rb+wb");
    if(fp1==NULL)
    {
        printf("Could not open psw.bin");
        getchar();
        exit(1);
    }
    system("cls");
    
    textcolor(CYAN);
    cprintf("Edit record: ");
    gets(name);

    // Finding the position of the deleting file
    fseek(fp1, 0, SEEK_SET);
    while((fscanf(fp1, "%s %s %s %s %s", get.title, get.username, get.password, get.email, get.notes))!= EOF )
    { 
        if(strcmp(get.title, name)==0)
        {
            condition=1;
            break;
        }
        else                                            
        {
            index++;
        }
    }
    
    // Creating the temp file
    if(condition==1)   // condition==1 means that there the record exists in the list
    {
        fp2= fopen("Temp.bin", "w");
        if(fp2==NULL)
        {
            printf("Can't open temp.bin");
            getchar();
            exit(1);
        }
        
        // Ask the user for the new password
        system("cls");
        textcolor(CYAN);
        cprintf("Please choose a new password for the ");
        textcolor(LIGHTCYAN);
        cprintf("%s", name);
        textcolor(CYAN);
        cprintf(" record: ");
        scanf("%s", new_password);
        flushall();
        
        fseek(fp1, 0, SEEK_SET);
        while((fscanf(fp1, "%s %s %s %s %s", get.title, get.username, get.password, get.email, get.notes))!= EOF )
        {
            index2++;
            if(index2!=index)
            {
                fprintf(fp2, "%s %s %s %s %s\n", get.title, get.username, get.password, get.email, get.notes);
            }
            else
            {
                fprintf(fp2, "%s %s %s %s %s\n", get.title, get.username, new_password, get.email, get.notes);
            }
        } // End while
        
        
        fclose(fp1); fclose(fp2);
        
        fp1=fopen("psw.bin", "w");
        fp2=fopen("temp.bin", "r");
        if((fp2==NULL) || (fp1==NULL))
        {
            printf("ERROR file not opened\n");      // copying from temp file to  the original
        }
        
        while((fscanf(fp2, "%s %s %s %s %s", get.title, get.username, get.password, get.email, get.notes))!= EOF )
        {
            fprintf(fp1, "%s %s %s %s %s\n", get.title, get.username, get.password, get.email, get.notes);
        }
        
        fclose(fp1); fclose(fp2);
        
        delete_temp();
        printf("\n The password was replaced");    
    }
    else
    {
        printf(" There record \"%s\" does not exist!\n", name);
    }
    
    getchar();
    number=1;
} // End edit password

void list(void)
{
    
    textcolor(CYAN);
    printf("\n\t\t\t");
    cprintf("%d", number);
    printf(". ");
    number++;
    
} // End list

void exit(void)
{
    system("cls");
    printf("\n\t\t\t\t\t\t Good Bye!");
    getchar();
} // End exit

void yesorno(void)
{
    textcolor(YELLOW);
    cprintf("(");
    textcolor(LIGHTGREEN);
    cprintf("Y");
    textcolor(YELLOW);
    cprintf("/");
    textcolor(LIGHTGREEN);
    cprintf("N");
    textcolor(YELLOW);
    cprintf(")");
    printf("\n");
}// End yesorno


void crypt(void)
{
    FILE *fp1, *fp2;                // Fixed
    char read;
    int ret, ascii;
    
    fp1=fopen("psw.bin", "rb");
    fp2=fopen("psw_scramble.bin", "wb");
    
    if((fp1==NULL) || (fp2==NULL))
    {
        fclose(fp1);
        fp1=fopen("psw.bin","wb");
        fclose(fp1);
        fp1=fopen("psw.bin","rb");
    }
    
    while(fread(&read, 1, 1, fp1)==1)
    {
        ascii= read;
        ascii+=3;
        fprintf(fp2,"%c", ascii);
    }
    fclose(fp1); fclose(fp2);
    
    fp1=fopen("psw.bin", "wb");
    fp2=fopen("psw_scramble.bin", "rb");
    if((fp1==NULL) || (fp2==NULL))
    {
        exit(1);
    }
    
    while(fread(&read, 1, 1, fp2)==1)
    {
        fwrite(&read, 1, 1, fp1);
    }
    fclose(fp1); fclose(fp2);
    
    ret = remove("psw_scramble.bin");
    if(ret != 0) 
    {
        printf("Error: unable to delete the temp file!");
    }
}// End crypt

