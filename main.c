#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc,char **argv)
{
    char fonksiyon[50];
    int a,i,b,katsayi,sabitsayi,kss,uss,sonuc,toplam;
    int katsayilar[10];
    int usler[10];
    float birincisayi,ikincisayi,bolmesayisi;
    char yontem[50];
    
    printf("Fonksiyonu Giriniz. (3x^4+2x+5 gibi)\n");
    scanf("%s",fonksiyon);
    printf("Aralığın Başlangıç Noktasını Giriniz.\n");
    scanf("%f",&birincisayi);
    printf("Aralığın Son Noktasını Giriniz.\n");
    scanf("%f",&ikincisayi);
    printf("Fonksiyonun Bölünme Sayısını Giriniz.\n");
    scanf("%f",&bolmesayisi);
    printf("Yöntemi Giriniz.(Midpoint,Rectangle,Simpsons,Trapezoid)\n");
    scanf("%s",yontem);

    i=0;
    b=0;
    kss=0;
    uss=0;
    katsayi=1;

    a=strlen(fonksiyon);//Fonksiyonun uzunluğunu for içinde
                       //kaç kez döndürüleceğini hesaplamak
    while(i<a)        //için fonksiyonun uzunluğunu hesapladım.
    {
        if(fonksiyon[i]=='+')
        {//fonksiyonda +'yı yakaladığında + ile x arasındaki
        // değerleri usler'e atıyor.
            usler[uss]=katsayi;
            uss=uss+1;
            b=0;//katsayı değişkenin değerini sıfırlıyor
            katsayi=1;
        }

        if(fonksiyon[i]=='x')
        {//x değerini yakaladığında x'den öncekiler katsayı
        //olacağından dolayı katsayilar'a atıyor.
            katsayilar[kss]=katsayi;
            kss=kss+1;
            b=0;
            katsayi=1;
        }

        if(fonksiyon[i]=='-')
        {//- değerini bulduğunda bir sorgu yapıyor.
            if(fonksiyon[i-1]=='^')
            {//-'den önceki değer üs ise ve polinom fonksiyonda
            //öyle bir değer olamayacağı için program hata veriyor.
                printf("HATA! Geçerli bir fonksiyon giriniz.\n");
                return 0;
            }
            else
            {//eğer başka bir değerse katsayının eksisi olacağı için
            //katsayıyı -1 ile çarpıyor.
                katsayi=katsayi*(-1);
            }
        }


        if(fonksiyon[i]=='0'||fonksiyon[i]=='1'||fonksiyon[i]=='2'||
        fonksiyon[i]=='3'||fonksiyon[i]=='4'||fonksiyon[i]=='5'||
        fonksiyon[i]=='6'||fonksiyon[i]=='7'||fonksiyon[i]=='8'||fonksiyon[i]=='9')
        {//fonksiyonda sorgulanan değer sayı ise sayıyı
        //katsayi değişkenine atıyor
            b = b+1;

            if (b>1)
            {//eğer birden fazla basamaklı bir değer ise
            //bunu tespit etmek için b değişkeni atadım.
            //varolan katsayıyı 10 ile çarpıp ekliyor.
                katsayi = katsayi*10;
                katsayi = katsayi+(fonksiyon [i]-'0');
                //yukarıdaki işlem char'ı integer'e çeviriyor.

            }
            else
            {//b sayısı 0 ise direk olarak atıyor.
                katsayi = katsayi*(fonksiyon[i]-'0');

            }
            if ((i+1)==a)
            {//eğer fonksiyondaki son değerde isek
            //sabit sayımızı bulmuş oluyoruz.
                if(fonksiyon[i-1]!='^')//önceki değer üs işareti ise
                {sabitsayi=katsayi;//sabit sayı 0 olur.
                }
                else
                {
                sabitsayi=0;
                usler[uss]=katsayi;
                uss=uss+1;
                b=0;//katsayı değişkenin değerini sıfırlıyor
                katsayi=1;
                }
            }
        }

        i=i+1;
    }

    for(int y=0;y<uss;y++){
    printf("%d.değerin katsayısı=%d üssü=%d \n",y+1,katsayilar[y],usler[y]);
    }//Burada değerlerin özelliklerini yazdırdım.
    printf("Sabit sayı=%d\n",sabitsayi);
    //sabit sayıyı da yazdırdım.

    //fonksiyon parçalama işini halletikten sonra
   //fonksiyonda yerine yazma kısmına geldik.

    float u_toplam=0;
    float u_toplam2=0;
    float k_sonuc=0;
    float sayi=0;
    float h,p;

    h=(ikincisayi-birincisayi)/bolmesayisi;
    //h değişkeni farkı bulup bölme sayısına bölüyor
    //böylece her defasında eklenecek değeri buluyoruz.
    p=birincisayi+h;
    //p sonraki değerimiz oluyor.
    switch (yontem[0]){

        case 'M'://burada case değeri int bir değere
        case 'm'://eşit olması nedeniyle ilk harfe bakıyor.
            for(int l=1;l<bolmesayisi;l++){
            //bu döngü bölme sayısı kadar dönüyor.
                for(int j=0;j<uss;j++){
                //bu döngü her x kadar dönüyor.
                //midpointe göre ikisinin ort değerini bulup
                //fonksiyonda yerine yazmak lazım
                    sayi=(p+birincisayi)/2;
                    //ortalamayı buluyor
                    sayi=pow(sayi,usler[j]);
                    //önceden kendi yazdığım üs alma fonksiyonunu
                    //burada çalıştıramadığım için pow kullanmak
                    //zorunda kaldım.
                    sayi=sayi*katsayilar[j];
                    //her x katsayısını aldım.

                    u_toplam=sayi+u_toplam;
                    //hepsini u_toplam değerine aktardım.
                }
            u_toplam+=sabitsayi;
            //en son olarak sabit sayıyı topladım.
            u_toplam*=(p-birincisayi);
            //midpointe göre ikisinin farkı ile çarptım.
            k_sonuc += u_toplam;
            //her değeri karışmaması için k_sonuc'a aktardım.
            u_toplam=0;
            birincisayi = birincisayi + h;
            //yukarıda h kadar ilk sayımızı arttırıyoruz.
            p = p + h;//p de aynı şekilde artıyor.
            }
        break;


        case 'R'://Rectangle kuralına göre soldaki
        case 'r'://değeri ile aradaki farkı çarpmamızı istiyor.
            for(int l=1;l<bolmesayisi;l++){
                for(int j=0;j<uss;j++){
                    sayi=birincisayi;//ortalama bulmaya gerek kalmıyor.
                    sayi=pow(sayi,usler[j]);
                    sayi=sayi*katsayilar[j];
                    u_toplam=sayi+u_toplam;
                }//diğer işlem midpointteki gibi oluyor.
                u_toplam+=sabitsayi;
                u_toplam*=(p-birincisayi);
                k_sonuc += u_toplam;
                u_toplam=0;
                birincisayi = birincisayi + h;
                p = p + h;
            }
        break;

        case 'T':
        case 't':
            for(int l=1;l<bolmesayisi;l++){
                for(int j=0;j<uss;j++){//f(a) kısmını bulduk
                    sayi=birincisayi;
                    sayi=pow(sayi,usler[j]);
                    sayi=sayi*katsayilar[j];
                    u_toplam=sayi+u_toplam;
                }
                u_toplam+=sabitsayi;
                for(int j=0;j<uss;j++){//f(b) kısmını da bulduk
                    sayi=p;
                    sayi=pow(sayi,usler[j]);
                    sayi=sayi*katsayilar[j];
                    u_toplam=sayi+u_toplam;
                }
                u_toplam+=sabitsayi;
                u_toplam = u_toplam / 2;//Trapezoid kuralını
                u_toplam*=(p-birincisayi);//uyguladım
                k_sonuc += u_toplam;
                u_toplam=0;
                birincisayi = birincisayi + h;
                p = p + h;
        }
        break;


        case'S':
        case's':
        for(int l=1;l<bolmesayisi;l++){
            for(int j=0;j<uss;j++){//f(a) kısmı
                sayi=birincisayi;
                sayi=pow(sayi,usler[j]);
                sayi=sayi*katsayilar[j];
                u_toplam=sayi+u_toplam;
            }
            u_toplam+=sabitsayi;
            for(int j=0;j<uss;j++){//f(b) kısmı
                sayi=p;
                sayi=pow(sayi,usler[j]);
                sayi=sayi*katsayilar[j];
                u_toplam=sayi+u_toplam;
            }
            u_toplam+=sabitsayi;

            for(int j=0;j<uss;j++){//simpsons kuralındaki
                sayi=(p+birincisayi)/2;//ara değerin bulunması.
                sayi=pow(sayi,usler[j]);
                sayi=sayi*katsayilar[j];
                u_toplam2=sayi+u_toplam2;
            }//f((a+b)/2) kısmını karışmaması için u_toplam2'ye atadım.
            u_toplam2+=sabitsayi;
            u_toplam = u_toplam + 4*u_toplam2;//kuralın uygulanması
            u_toplam*=(p-birincisayi)/6;
            k_sonuc += u_toplam;
            u_toplam2=0;
            u_toplam=0;
            birincisayi = birincisayi + h;
            p = p + h;
        }
        break;
    }


    printf("%s Fonksiyonuna göre sonuç = |%f| \n",fonksiyon,k_sonuc);
    //Sonucumuzu yazdırıyoruz

    return 0;
}
