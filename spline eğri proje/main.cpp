#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

FILE* fp;
char karakter[255];
char const* x_degerleri;
char const* y_degerleri;
int koordinatlar[20][2]; //koordinatlari txtden -20 ile 20 araliginda tuttugumuz liste
int koor_deg[100][2];     //koordinatlari 0 ile 800 arasi degerlere donusturdugumuz liste
int dugumler[1000];

struct Circle
{
    double merkez_x;
    double merkez_y;
    double R;
};


struct Circle cembercember;
struct Circle mec;

int koordinatlari_oku(char const* x_degerleri, char const* y_degerleri)
{
    fp=fopen("koordinatlar.txt","r");

    if(fp==NULL)
    {
        printf("Dosya bulunamadi.");
        return -1;
    }

    int nokta_sayisi=0;

    int i=0;
    while((fscanf(fp, "%s", karakter)) != EOF)
    {
        x_degerleri = strtok(karakter,","); //',' karakterine kadar ayiriyoruz
        y_degerleri = strtok(NULL,",");  //Kaldigi yerden kalan kismi al

        nokta_sayisi++;
        printf("\n%d.noktanin x koordinati: %s\n",nokta_sayisi, x_degerleri);
        printf(" %d.noktanin y koordinati: %s\n\n",nokta_sayisi, y_degerleri);

        int x_sayi=atoi(x_degerleri);
        int y_sayi=atoi(y_degerleri);

        koordinatlar[i][1]=x_sayi;
        koordinatlar[i][2]=y_sayi;
        i++;
    }



    int sistemMerkez_X=400; //koordinat sisteminin (0,0) noktasinin x ve y degerleri grafikte 400'e esittir.
    int sistemMerkez_Y=400;
    int k=0, m=0;


    while(koordinatlar[k][1]<= 20 && koordinatlar[k][1]>=-20)
    {
        for(int j=20; j>=-20; ) //her deger icin kontrol
        {

            if(koordinatlar[k][1]==j) //eger okunan deger 20'ye esitse gir
            {
                koor_deg[m][1]=sistemMerkez_X+(j*20); //yeni degeri hesapla ve yeni listeye esitle
                k++; //dosyadan okunan ikinci degere gec
                m++;
                j--;
            }

            else
            {
                j--; //20 yoksa ayný nokta icin daha dusuk degerleri gez, -20'ye kadar

            }
        }


    }

    int y=0, t=0;
    while(koordinatlar[t][2]<= 20 && koordinatlar[t][2]>=-20)
    {
        for(int j=20; j>=-20; ) //her deger icin kontrol
        {
            if(koordinatlar[t][2]==j) //eger okunan deger 20'ye esitse gir
            {
                koor_deg[y][2]=sistemMerkez_Y-(j*20); //yeni degeri hesapla ve yeni listeye esitle
                t++; //dosyadan okunan ikinci degere gec
                y++;
                j--;
            }

            else
            {
                j--; //20 yoksa ayný nokta icin daha dusuk degerleri gez, -20'ye kadar

            }
        }


    }


    for(int z=0; z<nokta_sayisi; z++)
    {
        printf("\n Noktanin txt'deki x degeri: %d,    grafik ekrandaki x degeri: %d",koordinatlar[z][1], koor_deg[z][1]);
        printf("\n Noktanin txt'deki y degeri: %d,    grafik ekrandaki y degeri: %d",koordinatlar[z][2], koor_deg[z][2]);

    }

    printf("\n Nokta sayisi: %d\n\n",nokta_sayisi);


    fclose(fp); //dosyayi kapat
    return nokta_sayisi;

}

int iceri_disari(int nokta_sayisi) //Disarida kalan nokta var mi kontrol et
{
    int findAPointOut=0;
    for(int k=0; k<nokta_sayisi; k++)
    {

        if((int)sqrt(pow(koor_deg[k][1] - mec.merkez_x, 2.0) + pow(koor_deg[k][2] - mec.merkez_y, 2.0)) > (int)mec.R) //uzerindeki noktalari isleme dahil etmemesi icin int
        {

            findAPointOut++;

        }

    }

    return findAPointOut;
}

int cember_ikinokta(int adet)  //En uzak iki noktayi cap al ve cember ciz
{
    float mes1;
    float maks1=0;
    int ekle_x, ekle_y;

    int x1,y1;
    int x2,y2;


    for (int i=0; i<adet; i++)
    {
        for (int j=i+1; j<adet; j++)
        {
            mes1=sqrt( pow((koor_deg[i][1]-koor_deg[j][1]),2.0) + pow((koor_deg[i][2]-koor_deg[j][2]),2.0) );
            //printf("\n %d.nokta  ile %d.nokta arasindaki mesafe : %1f \n ",i+1,j+1,mes1);

            if (j>i)
            {
                if(mes1>=maks1)
                {
                    maks1=mes1;
                    x1=koor_deg[i][1];
                    x2=koor_deg[j][1];
                    y1=koor_deg[i][2];
                    y2=koor_deg[j][2];
                }

            }

        }
    }

    //printf("\n Noktalar arasi en buyuk mesafe %f\n", maks1);


    mec.R=maks1/2;

    ekle_x=(x1-x2)/2;

    if(ekle_x<0)
        ekle_x=ekle_x*(-1);

    if(x1<x2)
        mec.merkez_x=x1+ekle_x;

    else
        mec.merkez_x=x2+ekle_x;



    ekle_y=(y1-y2)/2;
    if((ekle_y)<0)
        ekle_y=ekle_y*(-1);
    if(y1<y2)
        mec.merkez_y=y2-ekle_y;

    else
        mec.merkez_y=y1-ekle_y;

    printf("iki nokta hesabina gore yaricap: %.2f\n",mec.R);
    printf("Merkez noktasinin x koordinati: %.2f, y koordinati: %.2f\n", mec.merkez_x,mec.merkez_y);


    int disaridakinokta=iceri_disari(adet);

    return disaridakinokta;

}

void cember_tumnokta(int nokta_sayisi) //Tum noktalarin merkezini bul ve cember ciz
{

    int toplamx=0;
    int toplamy=0;
    float mes2;
    float maks2=0;

    for(int i=0; i<nokta_sayisi; i++)
    {
        toplamx=toplamx+koor_deg[i][1];
        toplamy=toplamy+koor_deg[i][2];
    }

    cembercember.merkez_x=toplamx/nokta_sayisi;
    cembercember.merkez_y=toplamy/nokta_sayisi;


    for (int i=0; i<nokta_sayisi; i++)
    {
        mes2=sqrt( pow((koor_deg[i][1]-cembercember.merkez_x),2.0) + pow((koor_deg[i][2]-cembercember.merkez_y),2.0) );
        //printf("\n %d.nokta  ile merkez arasindaki mesafe : %.2f \n ",i+1,mes2);

        if(mes2>=maks2)
        {
            maks2=mes2;
            cembercember.R=maks2;


        }
    }

    printf("\nTum noktalarin ortalamasi hesabina gore yaricap: %.2f\n",cembercember.R);
}


double N(int i, int k, double t)
{
    if(k==1)
    {

        if(t>=dugumler[i] && t<dugumler[i+1])
            return 1;
        else
            return 0;
    }

    else
    {
        return ((t-dugumler[i])/(dugumler[i+k-1] - dugumler[i]))*N(i, k-1, t)
               +  ((dugumler[i+k]-t)/(dugumler[i+k]-dugumler[i+1]))*N(i+1, k-1, t);

    }

}

int nokta_goster(int nokta_sayisi, int secim)
{
    int gd=DETECT, gm;
    initwindow(801,801,"Koordinat Sisteminde Verilen Noktalar");
    line(getmaxx()/2,0,getmaxx()/2,getmaxy());
    line(0,getmaxy()/2,getmaxx(),getmaxy()/2);


    float xy_merkezx=getmaxx()/2.0;
    float xy_merkezy=getmaxy()/2.0;

    int i=0;
    for(int j=0; j<400; j=j+20)
    {
        outtextxy(380-j, 395,"'");
        outtextxy(420+j, 395, "'");
        outtextxy(395, 380-j,"-");
        outtextxy(395, 420+j,"-");
    }


//x ekseni için -20,20 araliginin gosterimi
    outtextxy(375, 405,"-1");
    outtextxy(295, 405,"-5");
    outtextxy(190, 405,"-10");
    outtextxy(90, 405,"-15");
    outtextxy(0, 405,"-20");


    outtextxy(420, 405,"1");
    outtextxy(500, 405,"5");
    outtextxy(595, 405,"10");
    outtextxy(695, 405,"15");
    outtextxy(785, 405,"20");

//y ekseni için -20,20 araliginin gosterimi
    outtextxy(405, 375,"1");
    outtextxy(405, 295,"5");
    outtextxy(405, 190,"10");
    outtextxy(405, 90,"15");
    outtextxy(405, 0,"20");

    outtextxy(405, 420,"-1");
    outtextxy(405, 500,"-5");
    outtextxy(405, 595,"-10");
    outtextxy(405, 695,"-15");
    outtextxy(405, 785,"-20");

    char koordinat_bilgi[80];//noktalarýn koordinatlarýnýn gösterimi için bir char dizisi olusturduk


//Noktalarin koordinat degerlerine gore gosterilmesi
    for(int i=0; i<nokta_sayisi; i++)
    {
        sprintf(koordinat_bilgi, " (%d, %d)",koordinatlar[i][1],koordinatlar[i][2] );
        outtextxy(koor_deg[i][1],koor_deg[i][2], koordinat_bilgi);
        setcolor(WHITE);
        outtextxy(koor_deg[i][1],koor_deg[i][2],".");


    }



    int distakalan;

    int n = nokta_sayisi-1;
    int k = n+2;
    double t, x, y;

    while(secim!=0)
    {
        if(secim==1) //Cember
        {
            distakalan=cember_ikinokta(nokta_sayisi);
            //Dista nokta varsa tum noktalara gore cember ciz
            if(distakalan!=0)
            {
                cember_tumnokta(nokta_sayisi);
                setcolor(LIGHTRED);
                circle(cembercember.merkez_x,cembercember.merkez_y+14,cembercember.R); //14 birimlik sapmayi ekle

            }

            //Dista nokta yoksa 2nokta uzakligina gore cember ciz
            else
            {
                setcolor(LIGHTGREEN);
                circle(mec.merkez_x, mec.merkez_y+14, mec.R); //14 birimlik sapmayi ekle
            }

        }

        else if(secim==2) //Bspline
        {
            for(i=0; i<n+k+2; i++)
            {
                dugumler[i] = i+1;
            }

            for(t=3; t<=10; t+=0.001)
            {
                x=y=0;
                for(i=0; i<=n; i++)
                {
                    x += N(i, k, t)*koor_deg[i][1];
                    y += N(i, k, t)*koor_deg[i][2];
                }

                putpixel(x, y, CYAN);
                //delay(5);
            }
        }

        else if (secim==0)
        {
            getch();
            closegraph();
            break;
        }


        else
        {
            printf("Yanlis secim yaptiniz.");
            getch();
            closegraph();
            break;

        }

        printf("\nLutfen seciminizi belirtin.\n");
        scanf("%d",&secim);

    }



    return 0;
}



int main()
{
    printf("Programa hosgeldiniz.\n");
    printf("\n 1- Noktalari iceren cemberi gormek icin 1'e basin.\n");
    printf("\n 2- B-spline egrisi icin 2'ye basin.\n");
    printf("\n 0- Cikmak icin 0'a basin.\n ");

    int secim;
    int nokta_sayisi;


    printf("\nLutfen seciminizi belirtin.\n");
    scanf("%d",&secim);

    if(secim==0)
        return 0;

    else if(secim==1 || secim==2 )
    {
        nokta_sayisi= koordinatlari_oku(x_degerleri,y_degerleri);
        nokta_goster(nokta_sayisi, secim);
    }

    else
        printf("Yanlis secim yaptiniz.");

    return 0;


}
