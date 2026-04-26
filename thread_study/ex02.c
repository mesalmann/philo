#include <stdio.h>
#include <pthread.h>

int counter = 0;

void *increment(void *arg)
{
    int i = 0;
    while (i < 1000)
    {
        counter++;
        i++;
    }
    return NULL;
}

int main()
{
   pthread_t thread[5];
   
   int i = 0;
   while(i < 5)
   {
        pthread_create(&thread[i], NULL, increment, NULL);
        i++;
   }

   i = 0;
   while(i < 5)
   {
        pthread_join(thread[i], NULL);
        i++;
   }

   printf("%d", counter);
}

/*
Race condition = iki thread aynı anda aynı veriye erişince sonucun tahmin edilemez olması.

Neden olur?

counter++ tek işlem gibi görünür ama CPU'da 3 adım:

1. oku   → counter = 4
2. artır → 4 + 1 = 5
3. yaz   → counter = 5
İki thread aynı anda girerse:

Thread A okur → 4
Thread B okur → 4   ← A henüz yazmadı
Thread A yazar → 5
Thread B yazar → 5  ← A'nın artışı kayboldu
2 artış olması gerekirken 1 oldu.

Sonuç

5 thread × 1000 = beklenen 5000
Ama çıktı 4648 ya da her çalıştırmada farklı bir şey — çünkü thread'ler birbirinin üstüne yazıyor.

Çözüm: Mutex — aynı anda sadece bir thread o 3 adımı yapsın, diğerleri beklesin.
*/