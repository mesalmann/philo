# 🍝 Philosophers

> *I never thought philosophy would be so deadly*

42 okulunun klasik eşzamanlılık (concurrency) projesi. Dining Philosophers problemi üzerine kurulu olup, thread'ler ve mutex'ler ile çalışır.

## 📋 Konu

Yuvarlak bir masada belirli sayıda filozof oturmaktadır. Her filozofun önünde bir tabak spagetti ve her iki filozofun arasında bir çatal bulunur. Filozoflar sırasıyla **düşünür**, **yer** ve **uyur**. Yemek yemek için iki çatala ihtiyaçları vardır. Eğer bir filozof yeterince uzun süre yemek yemezse açlıktan ölür.

## 🚀 Kullanım

```bash
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Argümanlar

| Argüman | Açıklama |
|---|---|
| `number_of_philosophers` | Filozof sayısı (aynı zamanda çatal sayısı) |
| `time_to_die` (ms) | Son yemekten itibaren ölme süresi |
| `time_to_eat` (ms) | Yemek yeme süresi |
| `time_to_sleep` (ms) | Uyuma süresi |
| `number_of_times_each_philosopher_must_eat` | *(opsiyonel)* Her filozofun yemesi gereken minimum yemek sayısı |

### Örnekler

```bash
./philo 5 800 200 200       # 5 filozof, kimse ölmemeli
./philo 4 310 200 100       # Bir filozof ölecek
./philo 5 800 200 200 7     # Herkes 7 kez yedikten sonra durur
./philo 1 800 200 200       # Tek filozof, 800ms sonra ölür
```

## 🛠️ Makefile Komutları

```bash
make        # Derleme
make clean  # .o dosyalarını sil
make fclean # .o ve philo binary'sini sil
make re     # Temizle ve yeniden derle
```

## 📁 Dosya Yapısı

```
philo/
├── Makefile            # Derleme kuralları
├── philo.h             # Header: struct tanımları ve prototipler
├── main.c              # Giriş noktası ve akış kontrolü
├── parsing.c           # Argüman ayrıştırma ve ft_atoi
├── arg_check.c         # Argüman doğrulama
├── init.c              # Veri başlatma ve temizleme (clean)
├── dinner.c            # Simülasyon döngüsü ve monitör
├── synchro_utils.c     # Thread-safe getter/setter fonksiyonları
├── time_utils.c        # Zaman yönetimi (get_time_ms, ft_usleep)
└── utils.c             # Yardımcı fonksiyonlar (error_exit, write_status)
```

## ⚙️ Teknik Detaylar

- **Deadlock önleme:** Çift id'li filozoflar rutinin başında kısa bir süre bekletilerek çatal sıralaması bozulur.
- **Data race koruması:** Paylaşılan değişkenler mutex arkasında getter/setter fonksiyonları ile okunur ve yazılır.
- **Hassas zamanlama:** `ft_usleep` fonksiyonu, standart `usleep`'in hassasiyet kaybını 0.5ms aralıklarla kontrol ederek telafi eder.
- **Monitör:** Ayrı bir thread açmak yerine, boşa çıkan `main` thread ölüm kontrolcüsü olarak kullanılır.
