#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
pthread_t treat[10];
char pem1[100], pem2[100];
int skor1=0, skor2=0, a, status;
void *namaewa() {
    status=0;
    printf("Masukkan nama pemain1: ");
    gets(pem1);
    printf("Masukkan nama pemain2: ");
    gets(pem2);
    status++;
}

void cetakskor() {
    printf("Skor "); puts(pem1); printf(": %d\n",skor1);
    printf("Skor "); puts(pem2); printf(": %d\n",skor2);
}
void *isi(int *lub) {
    while(status!=1||status!=2) {}
    int jum, temp;
    while(1) {
        printf("mau mengisi berapa lubang?? ");
        scanf("%d",&jum);
        if(jum<5) break;
        else printf("Kebanyakan. Hanya boleh 1 sampai 4 hehe\n");
    }
    while(jum--) {
        printf("masukkan posisi lubang yang ingin dimasukkan MINE ");
        while(1) {
        scanf("%d",&temp);
        if(temp<1||temp>16) printf("posisi lubang tak tersedia, ulangi input\n");
        else {
            if(lub[temp-1]==1) printf("lubang telah terpasang MINE hehe\n");
            else {
                lub[temp-1]=1;
                break;
            }
        }
        }
    }
    status++;
}

void *tebak(int *lub) {
    while(status!=3||status!=4) {}
    int tebak;
    for(int i=0;i<4;i++) {
        printf("Masukkan posisi lubang yang ingin ditebak ");
        while(1) {
            scanf("%d",&tebak);
            if(tebak<1||tebak>16) {
                printf("Posisi lubang tak ada, ulangi input \n");
            }
            else break;
        }
        if(lub[tebak-1]==1) {
            printf("Anda benar! Skor anda ditambah 1\n");
            skor2++;
        }
        else {
            printf("Anda salah, skor lawan ditambah 1\n");
            skor1++;
        }
        cetakskor();
    }
    status++;
}

void *ceklub(int *lub) {
    while(status!=5||status!=6) {}
    for(int i=0;i<16;i++) {
        if(lub[i]==1) a++;
    }
    status++;
}

int main()
{
    int lub1[16], lub2[16];
    int err;
    while(1) {
            a=0;
            //status=0;
            err=pthread_create( &(treat[0]), NULL, &namaewa, NULL);
            if(err) printf("error ma bro\n");
            err=pthread_create( &(treat[1]), NULL, &isi, (int*) lub1);
            if(err) printf("error ma bro\n");
            err=pthread_create( &(treat[2]), NULL, &isi, (int*) lub2);
            if(err) printf("error ma bro\n");
            err=pthread_create( &(treat[3]), NULL, &tebak, (int*) lub1);
            if(err) printf("error ma bro\n");
            err=pthread_create( &(treat[4]), NULL, &tebak, (int*) lub2);
            if(err) printf("error ma bro\n");
            err=pthread_create( &(treat[5]), NULL, &ceklub, (int*) lub1);
            if(err) printf("error ma bro\n");
            err=pthread_create( &(treat[6]), NULL, &ceklub, (int*) lub2);
            if(err) printf("error ma bro\n");

            pthread_join(treat[0],NULL);
            pthread_join(treat[1],NULL);
            pthread_join(treat[2],NULL);
            pthread_join(treat[3],NULL);
            pthread_join(treat[4],NULL);
            pthread_join(treat[5],NULL);
            pthread_join(treat[6],NULL);
            if(a==32||skor1==10||skor2==10) {
            printf("permainan selesai. \n");
            break;
        }
    }
}
