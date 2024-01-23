#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define bufferLength 128

typedef struct wallet {
    char numeCard[52];
    char number[20];
    char name[52];
    char expiredate[52];
    char cvc2[4];
    long nrviz;
} wallet;

void printCard(wallet *card) {
    printf("Nume: %s | Numar: %s | Posesor: %s | CVC: %s\n",card->numeCard,card->number,card->name,card->cvc2);
    card->nrviz++;
}


void createCard(wallet *newCard, int nrcarduri) {
    char nume[64];
    fflush(stdin);
    int ok;
    do {
        ok = 1;
        printf("Introdu un nume pentru card-ul tau(fara spatii/caractere speciale): \n");
        fgets(nume, sizeof(nume), stdin);
        nume[strlen(nume)-1] = '\0';
        for(int i = 0; i < strlen(nume); ++i) {
            if(!isalpha(nume[i])) {
                ok = 0;
                break;
            }
        }
    } while(!ok);
    strcpy(newCard->numeCard, nume);
    char nrcard[64];
    fflush(stdin);
    do {
        ok = 1;
        printf("Introdu numarul cardului(16 cifre): \n");
        fgets(nrcard, sizeof(nrcard), stdin);
        fflush(stdin);
        nrcard[strlen(nrcard)-1] = '\0';
        for(int i = 0; i < strlen(nrcard); ++i) {
            if(!isdigit(nrcard[i])) {
                ok = 0;
                break;
            }
        }
        if(strlen(nrcard) != 16) ok = 0;
    } while(!ok);
    strcpy(newCard->number,nrcard);
    char numePosesor[64];
    printf("Introdu numele posesorului: \n");
    fflush(stdin);
    fgets(numePosesor, sizeof(numePosesor), stdin);
    numePosesor[strlen(numePosesor)-1] = '\0';
    strcpy(newCard->name,numePosesor);
    fflush(stdin);
    char expiredatea[64];
    do {
        ok = 1;
        printf("Introdu data de expirare(mm/yy): \n");
        fgets(expiredatea, sizeof(expiredatea), stdin);
        expiredatea[strlen(expiredatea)-1] = '\0';
        if(strlen(expiredatea) != 5) ok = 0;
        if(!(isdigit(expiredatea[0])&&isdigit(expiredatea[1])&&expiredatea[2]=='/'&&isdigit(expiredatea[3])&&isdigit(expiredatea[4])))
            ok = 0;
    } while(!ok);
    strcpy(newCard->expiredate,expiredatea);
    char cvc[4];
    fflush(stdin);
    do {
        ok = 1;
        printf("Introdu cvc-ul cardului tau: \n");
        fgets(cvc, sizeof(cvc), stdin);
        fflush(stdin);
        if(strlen(cvc)!=3) ok = 0;
        for(int i = 0; i < strlen(cvc); ++i) {
            if(!isdigit(cvc[i])) { ok = 0; break; }
        }
    } while(!ok);
    strcpy(newCard->cvc2,cvc);
    newCard->nrviz = 0;
}

int main()
{
    FILE* ptr;
    ptr = fopen("cards.txt","r");
    int countCards = 0;
    char buffer[bufferLength];
    wallet *Cards = (wallet*)calloc(50,sizeof(wallet));
    fscanf(ptr,"%d\n",&countCards);
    for(int i = 0; i < countCards; ++i) {
        fgets(buffer,bufferLength,ptr);
        buffer[strlen(buffer)-1] = '\0';
        strcpy(Cards[i].numeCard, buffer);
        //
        //
        fgets(buffer,bufferLength,ptr);
        buffer[strlen(buffer)-1] = '\0';
        strcpy(Cards[i].number, buffer);
        //
        //
        fgets(buffer,bufferLength,ptr);
        buffer[strlen(buffer)-1] = '\0';
        strcpy(Cards[i].name, buffer);
        //
        //
        fgets(buffer,bufferLength,ptr);
        buffer[strlen(buffer)-1] = '\0';
        strcpy(Cards[i].expiredate, buffer);
        //
        //
        fgets(buffer,bufferLength,ptr);
        buffer[strlen(buffer)-1] = '\0';
        strcpy(Cards[i].cvc2, buffer);
        //
        //
        fscanf(ptr,"%ld\n",&Cards[i].nrviz);
        //
    }
    fclose(ptr);
    /*

    */
    int ch = 0;
    while(1) {
        printf("~ YOUR WALLET MENU ~\n");
        printf("1. Vizualizeaza cardurile\n");
        printf("2. Adauga un card nou\n");
        printf("3. Sterge un card\n");
        printf("4. Exit\n");
        do {
            printf("Introdu actiunea pe care doresti sa o faci: ");
            scanf("%d", &ch);
        }
        while(ch < 1 || ch >  4);
        switch(ch)
        {
            case 1:
                system("cls");
                if(countCards) {
                    printf("~ Cardurile Tale ~\n");
                    for(int i = 0; i < countCards-1; ++i) {
                        for(int j = i+1; j < countCards; ++j)
                            if(Cards[i].nrviz < Cards[j].nrviz) {
                                wallet auxCard = Cards[i];
                                Cards[i] = Cards[j];
                                Cards[j] = auxCard;
                            }
                    }
                    for(int i = 0; i < countCards; ++i) {
                        printf("%d.%s - Posesor: %s\n", i+1, Cards[i].numeCard, Cards[i].name);
                    }
                    int idcard;
                    do {
                    printf("Alege un card pe care vrei sa il vizualizezi:\n");
                    scanf("%d", &idcard);
                    }while(idcard < 1 || idcard > countCards);
                    printCard(&Cards[idcard-1]);
                    ptr = fopen("cards.txt", "w");
                    fprintf(ptr, "%d\n", countCards);
                    for(int i = 0; i < countCards; ++i) {
                        fprintf(ptr, "%s\n", Cards[i].numeCard);
                        fprintf(ptr, "%s\n", Cards[i].number);
                        fprintf(ptr, "%s\n", Cards[i].name);
                        fprintf(ptr, "%s\n", Cards[i].expiredate);
                        fprintf(ptr, "%s\n", Cards[i].cvc2);
                        fprintf(ptr, "%d\n", Cards[i].nrviz);
                    }
                    fclose(ptr);
                }
                else printf("Nu exista niciun card salvat in wallet\n");
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                printf("~ Adauga un card nou ~\n");
                wallet *tmpCard;
                tmpCard = (wallet*)malloc(sizeof(wallet));
                createCard(tmpCard, countCards);
                Cards[countCards++] = *tmpCard;
                ptr = fopen("cards.txt", "w");
                fprintf(ptr, "%d\n", countCards);
                for(int i = 0; i < countCards; ++i) {
                    fprintf(ptr, "%s\n", Cards[i].numeCard);
                    fprintf(ptr, "%s\n", Cards[i].number);
                    fprintf(ptr, "%s\n", Cards[i].name);
                    fprintf(ptr, "%s\n", Cards[i].expiredate);
                    fprintf(ptr, "%s\n", Cards[i].cvc2);
                    fprintf(ptr, "%d\n", Cards[i].nrviz);
                }
                fclose(ptr);
                printf("Cardul tau a fost salvat. Il poti vizualiza in sectiunea 'Vizualizeaza-ti cardurile'.\n");
                system("pause");
                system("cls");
                break;
            case 3:
                system("cls");
                printf("~ Sterge un card ~\n");
                for(int i = 0; i < countCards; ++i) {
                    printf("%d.%s - Posesor: %s\n", i+1, Cards[i].numeCard, Cards[i].name);
                }
                printf("Introdu id-ul cardului pe care vrei sa il stergi...\n");
                int idd;
                scanf("%d",&idd);
                for(int i = idd-1; i < countCards-1; ++i)
                    Cards[i] = Cards[i+1];
                countCards--;
                ptr = fopen("cards.txt", "w");
                fprintf(ptr, "%d\n", countCards);
                for(int i = 0; i < countCards; ++i) {
                    fprintf(ptr, "%s\n", Cards[i].numeCard);
                    fprintf(ptr, "%s\n", Cards[i].number);
                    fprintf(ptr, "%s\n", Cards[i].name);
                    fprintf(ptr, "%s\n", Cards[i].expiredate);
                    fprintf(ptr, "%s\n", Cards[i].cvc2);
                    fprintf(ptr, "%d\n", Cards[i].nrviz);
                }
                fclose(ptr);
                printf("Ai sters cardul cu id-ul: %d\n", idd);
                system("pause");
                system("cls");
                break;
            case 4:
                printf("Ai inchis programul.");
                ptr = fopen("cards.txt", "w");
                fprintf(ptr, "%d\n", countCards);
                for(int i = 0; i < countCards; ++i) {
                    fprintf(ptr, "%s\n", Cards[i].numeCard);
                    fprintf(ptr, "%s\n", Cards[i].number);
                    fprintf(ptr, "%s\n", Cards[i].name);
                    fprintf(ptr, "%s\n", Cards[i].expiredate);
                    fprintf(ptr, "%s\n", Cards[i].cvc2);
                    fprintf(ptr, "%d\n", Cards[i].nrviz);
                }
                fclose(ptr);
                return 1;
                break;
            default:
                system("cls");
        }
    }
    return 0;
}
