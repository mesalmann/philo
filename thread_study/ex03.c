#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
int counter = 0;
void    *increment(void *arg)
{
    int i = 0;
    
    while(i < 1000)
    {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
        i++;
    }
    return NULL;
}
int main()
{
    int i = 0;
    pthread_mutex_init(&mutex, NULL);
    pthread_t thread[5];

    while(i < 5)
    {
        pthread_create(&thread[i], NULL, increment, NULL);
        i++;
    }
    i = 0;
    while (i < 5)
    {
        pthread_join(thread[i], NULL);
        i++;
    }
    pthread_mutex_destroy(&mutex);
    printf("%d", counter);
}





/*
Mutex = bir critical section'a aynı anda sadece bir thread girebilsin diye kullanılan kilit.

Tanımlama

pthread_mutex_t mutex;
Tıpkı int tanımlar gibi. Global ya da struct içinde olabilir.

pthread_mutex_init

pthread_mutex_init(&mutex, NULL);
Kullanmadan önce hazırla. NULL = default ayarlar. malloc gibi düşün — önce init etmeden kullanamazsın.

pthread_mutex_lock

pthread_mutex_lock(&mutex);
Kilidi al. Başka bir thread zaten aldıysa burada bekler, bırakılana kadar geçemez.

pthread_mutex_unlock

pthread_mutex_unlock(&mutex);
Kilidi bırak. Bekleyen thread artık girebilir.

pthread_mutex_destroy

pthread_mutex_destroy(&mutex);
İş bitti, kaynakları serbest bırak. free gibi düşün.

Critical section

Lock ile unlock arasındaki kod — aynı anda sadece bir thread burayı çalıştırır:

pthread_mutex_lock(&mutex);
counter++;              // critical section
pthread_mutex_unlock(&mutex);
Önemli kurallar

Her lock için mutlaka unlock olmalı — unutursan program kilitlenir (deadlock)
Critical section mümkün olduğunca kısa tut — içinde ne kadar az iş olursa o kadar iyi
Init etmeden kullanma, destroy etmeden bitirme
*/