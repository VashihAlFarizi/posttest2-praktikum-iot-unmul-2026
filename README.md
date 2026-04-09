# posttest2-praktikum-iot-unmul-2026

## **Nama Kelompok:**

Kelompok 7

## **Anggota:**

1. Muhamad Ihsan (2209106099)
2. Muhammad Aidil Saputra (2309106042)
3. Vashih Al Farizi (23091006076)
4. Muhammad Rafif Hanif (2309106044)

---

## **Judul studi kasus**

smart house memiliki sistem pencahayaan dan keamanan terintegrasi yang dapat dikontrol melalui Telegram Bot. Terdapat n+1 LED dan 2 buah sensor, DHT11 untuk suhu/kelembapan dan MQ-2 untuk deteksi kebocoran gas)

---

## **Deskripsi**

1. Setiap anggota kelompok memiliki LED pribadi. Anggota A hanya boleh mengontrol LED A, Anggota B hanya LED B, dan seterusnya.
2. Terdapat 1 LED Utama (Ruang Tamu) yang bisa dikontrol oleh siapa saja.
3. Jika sensor MQ-2 mendeteksi gas di atas ambang batas, bot harus mengirimkan Warning ke grup secara otomatis (Push Notification).
4. Seluruh anggota dapat mengecek suhu dan kelembapan kapan saja.

---

## **Pembagian Tugas**

- Muhammad Aidil Saputra: Pembukan dan menjelaskan alat alat yang digunakan
- Muhamad Ihsan:  Membuat Board Schematic dan penjelasan pin alat
- Vashih Al Farizi: Membuat config Control telegram bot, membuat coment control semua lampu dan menjelasaka cara menggunakan
- Muhammad Rafif Hanif: Membuat Control MQ2 dan DHT11 dan Menjelaskan cara penggunaan sensor

---

## **Komponen yang Digunakan** ##
- ESP32 c3
- Sensor Gas MQ-2
- Sensor Suhu DTH11
- LED (3 buah: Merah, Kuning, Hijau)
- Breadboard
- Kabel jumper
- Sumber daya kabel type c

---

## **Board Schematic** ##
<img width="950" height="590" alt="image" src="https://github.com/user-attachments/assets/73a2eeb4-aa2d-4859-a43c-416b93d70a36" />


---

## **Link Video Demo** ##

LINK: https://youtu.be/1UBeoprrq2o

---
