#include <stdio.h>
#include <pthread.h>

void    *hey(void *arg)
{
    int i = *(int *)arg;
    printf("Thread got: %d", i);
    return NULL;
}

int main()
{
    pthread_t thread;
    int a = 42;
    pthread_create(&thread, NULL, hey, &a);
    pthread_join(thread, NULL);
}

/*
Thread nedir?

Program normalde tek sıra çalışır. Thread = aynı anda birden fazla iş yapabilmek. Aynı belleği paylaşırlar.

pthread_create

pthread_create(&thread, NULL, fonksiyon, arg);
&thread — oluşturulan thread buraya kaydedilir
NULL — özel ayar yok, default
fonksiyon — thread bu fonksiyonu çalıştırır, imzası void *f(void *) olmak zorunda
arg — fonksiyona gönderilecek argüman, pointer olmalı (&a gibi), göndermeyeceksen NULL
pthread_join

pthread_join(thread, NULL);
Main bu thread bitene kadar bekler. Çağırmazsan main erken kapanır, thread yarıda kalır.

Birden fazla thread için önce hepsini create et, sonra hepsini join et — yoksa sıralı çalışır, paralellik olmaz.

void *fonksiyon(void *arg)

pthread_create her fonksiyonu bu imzayla bekler. void * = herhangi bir tip pointer. İçinde kullanmak için cast edersin:

int i = *(int *)arg;  // önce int*'a çevir, sonra değeri al
*/