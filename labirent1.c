#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// math kütüphanesi matematiksel işlemleri içerir (sqrt(karekök alma),pow(kuvvet alma))

// struck yapısı kişilerinkonum ve mesafe verilerini tutar
// typedef bir veri tipine yeni bir isim vermek için kullanılır
typedef struct
{
    int x, y;
    double mesafe;
} Person;

// öklid teoremi iki noka arasındaki kuş uçuşu mesafeyi hesaplamaya yarar
// sqrt, karekök alma fonksiyonudur
// pow, kuvvet alma fonksiyonudur örneğin pow(2,5) 2 üzeri 5 amlamına gelir
double oklidMesafesi(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// manhattan teoremi iki nokta arasındaki dikey ve yatay uzaklığın toplamını hesaplar
// abs mutlak değer fonksiyonunu ifade eder
double manhattanMesafesi(int x1, int y1, int x2, int y2)
{
    return abs(x2 - x1) + abs(y2 - y1);
}

int main()
{
    int genislik, yukseklik, kisiSayisi, kendiX, kendiY, tespitMesafesi; // programda kullanacağımız tam sayı türündeki verileri alır
    char secim;                                                          // teorem seçme karakteri(m,e)

    // labirentin boyutları kullanıcıdan alınır
    printf("Labirent genisligi ve yuksekligi: ");
    scanf("%d %d", &genislik, &yukseklik);

    // kişi sayısı kullanıcıdan alınır
    printf("Kac kisi var? ");
    scanf("%d", &kisiSayisi);

    // girilen kişi sayısı diziye dönüştürülür ve struct yapısı yardımıyla kullanıcıdan her biri kişi için konum bilgisi alınır
    Person kisiler[kisiSayisi];

    for (int i = 0; i < kisiSayisi; i++)
    {

        do
        {
            printf("Kisi %d konumunu gir (x y): ", i + 1);
            scanf("%d %d", &kisiler[i].x, &kisiler[i].y);

            if (kisiler[i].x < 0 || kisiler[i].x >= genislik || kisiler[i].y < 0 || kisiler[i].y >= yukseklik)
            {
                printf("Hata: Kisi %d'nin konumu labirent sinirlari icinde olmalidir!\n", i + 1);
            }
        } while (kisiler[i].x < 0 || kisiler[i].x >= genislik || kisiler[i].y < 0 || kisiler[i].y >= yukseklik);
    }

    // kişnin kendi konumu alınır

    do
    {
        printf("Kendi konumunu gir (x y): ");
        scanf("%d %d", &kendiX, &kendiY);

        if (kendiX < 0 || kendiX >= genislik || kendiY < 0 || kendiY >= yukseklik)
        {
            printf("Hata: Konumun labirent sinirlari icinde olmalidir!\n");
        }
    } while (kendiX < 0 || kendiX >= genislik || kendiY < 0 || kendiY >= yukseklik);

    // kişinin en fazla kaç birim uzğındaki kişileri tespit edileceğini bilmek için tespit mesafesi girilir
    printf("Tespit mesafesini gir: ");
    scanf("%d", &tespitMesafesi);

    // hangi mesafe ölçüm yolu kullanılacağı kullanıcıya soruulur
    printf("Oklid mi kullanilsin yoksa manhattan mi? "); // E girilirse öklid, başka bir karakter girilirse manhattan kullanılacak
    scanf(" %c", &secim);

    // mesafeFonksiyonu adlı fonksiyon işaretçisi tanımlanır
    // Kullanıcının seçimine göre Öklid veya Manhattan mesafe hesaplama fonksiyonunu kullanacak şekilde ayarlanır.
    double (*mesafeFonksiyonu)(int, int, int, int);
    mesafeFonksiyonu = (secim == 'E') ? oklidMesafesi : manhattanMesafesi;

    // en yakın ve en uzak kişiler önce 1. kişiye eşitlenir
    Person enYakin = kisiler[0], enUzak = kisiler[0];
    
    // girilen tespit mesafesi içerisinde olan kişiler bulunur ve ekrana yazdırılır
    printf("\nBelirtilen mesafe icinde olan kisiler:\n");
    for (int i = 0; i < kisiSayisi; i++)
    {
        // kisiler[i].mesafe = mesafeFonksiyonu(kendiX, kendiY, kisiler[i].x, kisiler[i].y);
        enYakin.mesafe = mesafeFonksiyonu(kendiX, kendiY, kisiler[0].x, kisiler[0].y);
        enUzak.mesafe = enYakin.mesafe; // İlk kişiyle başlat

        if (kisiler[i].mesafe <= tespitMesafesi)
        {
            printf("Kisi %d (%d, %d) - Mesafe: %.2lf\n", i + 1, kisiler[i].x, kisiler[i].y, kisiler[i].mesafe);
        }

        if (kisiler[i].mesafe < enYakin.mesafe) // en yakın ve en uzak kişiler karşılaştırma yoluyla belirlenir ve ekrana yazdırılır
        {
            enYakin = kisiler[i];
        }

        if (kisiler[i].mesafe > enUzak.mesafe)
        {
            enUzak = kisiler[i];
        }
    }

    printf("\nEn yakin kisi: %d  (%d, %d) - Mesafe: %lf\n",enYakin, enYakin.x, enYakin.y, enYakin.mesafe);
    printf("En uzak kisi: %d  (%d, %d) - Mesafe: %lf\n",enUzak, enUzak.x, enUzak.y, enUzak.mesafe);

    return 0;
}