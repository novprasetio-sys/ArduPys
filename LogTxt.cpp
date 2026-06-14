#include<stdio.h>
#include<stdlib.h>

int main()
{
    float I,nM,Imean,Tres;

    Tres = 1.48;

    printf("menghitung arus rata-rata per panel\n");

    printf("masukkan nilai Arus Terukur : ");
    scanf("%f",&I);

    printf("masukkan jumlah motor per kolam : ");
    scanf("%f",&nM);

    if(nM == 0){
        printf("jumlah motor tidak boleh nol");
        return 1;
    }

    Imean = I/nM;

    printf("nilai arus rata-rata adalah : %.2f ampere\n",Imean);

    if(Imean < Tres)
        printf("motor anda aman\n");
    else
        printf("motor anda berpotensi terbakar\n");
    FILE *fp;
    // choose your preferences csv or txt
    // fp = fopen("monitoring.csv","a");
    
    // fprintf(fp,"%.2f,%.0f,%.2f\n", I,nM,Imean);
    
    fp = fopen("monitoring.txt","a");

    fprintf(fp,"%.2f/%.0f/%.2f\n",
            I,nM,Imean);

    fclose(fp);

    printf("Data tersimpan\n");


    return 0;
}