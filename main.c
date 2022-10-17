#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*TO DO:
    - hely szerinti kiiratas
    - adatok modositasa
    - adatok torlese
*/

char locations[7][30] = {"Baratfa", "Lovas", "Szula", "Kigyos-patak", "Malom-telek", "Paskom", "Kaposztas-kert"};
char name[30];
int times;
FILE *filePointer, *tempFilePointer;

void createFile() {
    filePointer = fopen("nyuszik.txt", "a");
    fclose(filePointer);
}

void readData() {
    filePointer = fopen("nyuszik.txt", "a");

    char tempName[30];
    char tempLocation[30];
    int tempTimes;

    printf("\n---Adatok beolvasasa---\n\n");

    printf("Nyuszi neve:\n");
    scanf("%s", tempName);

    bool valid = false;
    while(!valid) {
        printf("Lakoterulet:\n");
        scanf("%s", tempLocation);
        for(int i = 0; i < 7; i++) if (strcmp(tempLocation,locations[i]) == 0) valid = true;
        if (!valid) printf("Ervenytelen lakoterulet, kerem probalja ujra\n");
    }

    printf("Hanyadik alkalommal jelentkezett:\n");
    scanf("%d", &tempTimes);

    printf("\nUj adatok felveve\n");
    printf("Nev: %s, lakoterulet: %s, alkalom: %d\n", tempName, tempLocation, tempTimes);

    fprintf(filePointer, "%s;%s;%d\n", tempName, tempLocation, tempTimes);
    fclose(filePointer);
}

void printFile() {
    filePointer = fopen("nyuszik.txt", "r");
    char c;
    while ((c = getc(filePointer)) != EOF) {
            printf("%c", c);
        }
    fclose(filePointer);
}

void printFileByLocation() {
    char tempL[30];
    printf("Melyik lakoterulet jelentkezoit szeretne kiiratni?:\n");

    bool valid = false;
    while(!valid) {
        printf("Lakoterulet:\n");
        scanf("%s", tempL);
        for(int i = 0; i < 7; i++) if (strcmp(tempL,locations[i]) == 0) valid = true;
        if (!valid) printf("Ervenytelen lakoterulet, kerem probalja ujra\n");
    }

    filePointer = fopen("nyuszik.txt", "r");
    char line[100];
    char *ret;
    bool was= false;
    while(fgets(line, 100, filePointer)){
        ret = strstr(line, tempL);
        if (ret){
            was = true;
            printf(line);
        }
    } if (!was) printf("Nincs ilyen telepulesrol jelentkezo!\n");

    fclose(filePointer);
}

void modifyData() {
    char tempN[30];
    printf("Melyik nyuszi adatait szeretne modositani?:\n");
    scanf("%s", tempN);

    filePointer = fopen("nyuszik.txt", "r");
    tempFilePointer = fopen("temp.txt", "w");

    char line[100];
    char *ret;
    bool was= false;
    while(fgets(line, 100, filePointer)){
        ret = strstr(line, tempN);
        if (ret){
            was = true;
            printf(line);

            printf("\n---Adatok beolvasasa---\n\n");
            char tempName[30];
            char tempLocation[30];
            int tempTimes;
            printf("Nyuszi neve:\n");
            scanf("%s", tempName);

            bool valid = false;
            while(!valid) {
                printf("Lakoterulet:\n");
                scanf("%s", tempLocation);
                for(int i = 0; i < 7; i++) if (strcmp(tempLocation,locations[i]) == 0) valid = true;
                if (!valid) printf("Ervenytelen lakoterulet, kerem probalja ujra\n");
            }

            printf("Hanyadik alkalommal jelentkezett:\n");
            scanf("%d", &tempTimes);

            printf("\nUj adatok felveve\n");
            printf("Nev: %s, lakoterulet: %s, alkalom: %d\n", tempName, tempLocation, tempTimes);

            fprintf(tempFilePointer, "%s;%s;%d\n", tempName, tempLocation, tempTimes);
        } else {
            fprintf(tempFilePointer, "%s", line);
        }
    } if (!was) printf("Nincs ilyen nevu jelentkezo!\n");

    fclose(tempFilePointer);
    fclose(filePointer);

    remove("nyuszik.txt");
    rename("temp.txt", "nyuszik.txt");
}

void deleteData() {
    char tempN[30];
    printf("Melyik nyuszi adatait szeretne torolni?:\n");
    scanf("%s", tempN);

    filePointer = fopen("nyuszik.txt", "r");
    tempFilePointer = fopen("temp.txt", "w");

    char line[100];
    char *ret;
    bool was= false;
    while(fgets(line, 100, filePointer)){
        ret = strstr(line, tempN);
        if (ret){
            was = true;
            printf("Adatok torolve: %s", line);
        } else {
            fprintf(tempFilePointer, "%s", line);
        }
    } if (!was) printf("Nincs ilyen nevu jelentkezo!\n");

    fclose(tempFilePointer);
    fclose(filePointer);

    remove("nyuszik.txt");
    rename("temp.txt", "nyuszik.txt");
}

void menu() {
    bool exit = false;
    int inputNum;

    while (!exit) {
        printf("\n1: Uj adat felvetele\n2: Adat modositasa\n3: Adat torlese\n4: Osszes adat kiiratasa\n5: Adatok kiiratasa hely szerint\n0: Kilepes\n");
        scanf("%d", &inputNum);
        if (inputNum == 0) {
            printf("Kilepes...");
            exit = true;
        }
        else {
            switch (inputNum) {
                case 1: {
                    readData();
                    break;
                }
                case 2: {
                    modifyData();
                    break;
                }
                case 3: {
                    deleteData();
                    break;
                }
                case 4: {
                    printFile();
                    break;
                }
                case 5: {
                    printFileByLocation();
                    break;
                }
                default: {
                    printf("Helytelen parancs");
                    break;
                }
            }
        }
    }

}

int main() {
    printf("Ervenyes helyek:\n");
    for(int i = 0; i < 7; i++) {
        printf("%s\n", locations[i]);
    }
    createFile();
    menu();
    return 0;
}
