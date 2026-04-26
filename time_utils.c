#include "philo.h"

// Milisaniye cinsinden şu anki zamanı döndürür
long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		printf("Error: gettimeofday failed\n");
		return (0);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// Standart usleep fonksiyonu işletim sistemine göre hassasiyet kaybedebilir.
// Bu yüzden kendi hassas bekleme fonksiyonumuzu yazıyoruz.
// Ayrıca bekleme sırasında birisi ölürse hemen çıkmak için end_simulation kontrolü ekliyoruz.
void	ft_usleep(long msec, t_table *table)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < msec)
	{
		// Eğer simülasyon bittiyse beklemeyi kes (şık bir detay!)
		if (get_bool(&table->table_mtx, &table->end_simulation))
			break ;
		usleep(500); // 500 mikrosaniye = 0.5 ms aralıklarla uyuyup kontrol et
	}
}
