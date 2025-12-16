/**
 * @file bitops.h
 * @brief Çoklu Bit Geniþlikleri için Kapsamlý Bitwise Ýþlemleri Kütüphanesi Deklarasyonlarý.
 *
 * Bu dosya, uint8_t'den uint64_t'ye kadar tüm standart tam sayý tipleri için
 * temel manipülasyon, alan yönetimi, akýþ kontrolü ve analiz iþlemlerini
 * gerçekleþtiren fonksiyon aþýrý yüklemelerinin prototiplerini içerir.
 * Þablon (Template) fonksiyonlarýnýn implementasyonlarý da Linker sorununu çözmek için
 * bu dosyanýn sonundadýr.
 *
 * @author Doðukan Avcý
 * @date 15 Aralýk 2025
 * @version 1.1.0 (Template/Overloading Birleþimi)
 * @copyright Telif Hakký (c) 2025 Doðukan Avcý. Tüm Haklarý Saklýdýr.
 */

#ifndef BITOPS_H
#define BITOPS_H

#include <iostream>
#include <cstdint> // uintX_t tipleri için (std::uint32_t vb.)
// bool, true, false C++ dilinin yerleþik anahtar kelimeleridir, stdbool.h gerekmez.

// Makro: Tek bir biti set eden maskeyi hýzlýca oluþturur.
#define BIT(N) (1U << (N))

// =========================================================================
// I. TEMEL MANÝPÜLASYON ÝÞLEMLERÝ (SINGLE BIT OPERATIONS)
// =========================================================================

/**
 * @brief Belirtilen indeksteki biti '1' (Set) yapar. 
 *
 * @param reg Ýþlem yapýlacak register deðeri.
 * @param index Bitin konumu (0'dan (N-1)'e kadar).
 * @return Deðiþtirilmiþ register deðerini, giriþ tipiyle ayný tipte döndürür.
 */
uint8_t SetRegBit(uint8_t reg, int index);
uint16_t SetRegBit(uint16_t reg, int index);
uint32_t SetRegBit(uint32_t reg, int index);
uint64_t SetRegBit(uint64_t reg, int index);

/**
 * @brief Belirtilen indeksteki biti '0' (Clear) yapar. 
 *
 * @param reg Ýþlem yapýlacak register deðeri.
 * @param index Bitin konumu (0'dan (N-1)'e kadar).
 * @return Deðiþtirilmiþ register deðerini, giriþ tipiyle ayný tipte döndürür.
 */
uint8_t ClearRegBit(uint8_t reg, int index);
uint16_t ClearRegBit(uint16_t reg, int index);
uint32_t ClearRegBit(uint32_t reg, int index);
uint64_t ClearRegBit(uint64_t reg, int index);

/**
 * @brief Belirtilen indeksteki bitin deðerini tersine çevirir (Toggle). 
 *
 * @param reg Ýþlem yapýlacak register deðeri.
 * @param index Bitin konumu (0'dan (N-1)'e kadar).
 * @return Deðiþtirilmiþ register deðerini, giriþ tipiyle ayný tipte döndürür.
 */
uint8_t ToggleRegBit(uint8_t reg, int index);
uint16_t ToggleRegBit(uint16_t reg, int index);
uint32_t ToggleRegBit(uint32_t reg, int index);
uint64_t ToggleRegBit(uint64_t reg, int index);

/**
 * @brief Belirtilen indeksteki bitin '1' olup olmadýðýný kontrol eder.
 *
 * @param reg Ýþlem yapýlacak register deðeri.
 * @param index Bitin konumu (0'dan (N-1)'e kadar).
 * @return Bit '1' ise true, deðilse false döndürür.
 */
bool isBitSet(uint8_t reg, int index);
bool isBitSet(uint16_t reg, int index);
bool isBitSet(uint32_t reg, int index);
bool isBitSet(uint64_t reg, int index);


// =========================================================================
// II. BÝT ALANI ÝÞLEMLERÝ (BIT FIELD OPERATIONS)
// =========================================================================

/**
 * @brief Belirtilen baþlangýç bitinden itibaren 'length' uzunluðundaki bit alanýný okur. 
 *
 * @param reg Okunacak register deðeri.
 * @param start_bit Baþlangýç indeksi (0-tabanlý).
 * @param length Bit alanýnýn uzunluðu.
 * @return Okunan bit alanýnýn deðerini döndürür (Saða hizalanmýþ). Dönüþ tipi, giriþ tipiyle aynýdýr.
 */
uint8_t get_bit_field(uint8_t reg, int start_bit, int length);
uint16_t get_bit_field(uint16_t reg, int start_bit, int length);
uint32_t get_bit_field(uint32_t reg, int start_bit, int length);
uint64_t get_bit_field(uint64_t reg, int start_bit, int length);

/**
 * @brief Belirtilen bit alanýna yeni bir deðer yazar (Önce temizleme, sonra yazma). 
 *
 * @param reg Ýþlem yapýlacak register deðeri.
 * @param start_bit Baþlangýç indeksi (0-tabanlý).
 * @param length Bit alanýnýn uzunluðu.
 * @param new_value Alana yazýlacak yeni deðer. New_value, reg ile ayný tipte olmalýdýr.
 * @return Deðiþtirilmiþ register deðerini döndürür. Dönüþ tipi, giriþ tipiyle aynýdýr.
 */
uint8_t set_bit_field(uint8_t reg, int start_bit, int length, uint8_t new_value);
uint16_t set_bit_field(uint16_t reg, int start_bit, int length, uint16_t new_value);
uint32_t set_bit_field(uint32_t reg, int start_bit, int length, uint32_t new_value);
uint64_t set_bit_field(uint64_t reg, int start_bit, int length, uint64_t new_value);


// =========================================================================
// IV. POZÝSYON VE AKIÞ ÝÞLEMLERÝ (POSITION & FLOW OPERATIONS)
// =========================================================================

/**
 * @brief Bitleri sola dairesel olarak kaydýrýr (Rotate Left). 
 *
 * @param reg Ýþlem yapýlacak register deðeri.
 * @param shift Kaydýrma miktarý.
 * @return Döndürülmüþ register deðerini, giriþ tipiyle ayný tipte döndürür.
 */
uint8_t RotateLeft(uint8_t reg, int shift);
uint16_t RotateLeft(uint16_t reg, int shift);
uint32_t RotateLeft(uint32_t reg, int shift);
uint64_t RotateLeft(uint64_t reg, int shift);

/**
 * @brief Bitleri saða dairesel olarak kaydýrýr (Rotate Right). 
 *
 * @param reg Ýþlem yapýlacak register deðeri.
 * @param shift Kaydýrma miktarý.
 * @return Döndürülmüþ register deðerini, giriþ tipiyle ayný tipte döndürür.
 */
uint8_t RotateRight(uint8_t reg, int shift);
uint16_t RotateRight(uint16_t reg, int shift);
uint32_t RotateRight(uint32_t reg, int shift);
uint64_t RotateRight(uint64_t reg, int shift);

/**
 * @brief En saðdan (LSB) baþlayarak ilk '1' bitinin konumunu (indeksini) bulur.
 *
 * @param reg Ýþlem yapýlacak register deðeri.
 * @return Ýlk '1' bitinin indeksini (0'dan (N-1)'e) veya reg 0 ise -1 döndürür.
 */
int find_first_set_bit(uint8_t reg);
int find_first_set_bit(uint16_t reg);
int find_first_set_bit(uint32_t reg);
int find_first_set_bit(uint64_t reg);


// =========================================================================
// V. KONTROL VE ANALÝZ ÝÞLEMLERÝ (CONTROL & ANALYSIS)
// =========================================================================

/**
 * @brief Sayýdaki set edilmiþ ('1') bitlerin sayýsýný bulur (Popcount).
 *
 * @param reg Ýþlem yapýlacak register deðeri.
 * @return Set edilmiþ bit sayýsýný döndürür. Dönüþ tipi int'tir.
 */
int count_set_bits(uint8_t reg);
int count_set_bits(uint16_t reg);
int count_set_bits(uint32_t reg);
int count_set_bits(uint64_t reg);

/**
 * @brief Sayýnýn tek/çift parity durumunu kontrol eder (count_set_bits'e dayanýr).
 *
 * @param reg Ýþlem yapýlacak register deðeri.
 * @return Parity Tek ise true (1), Çift ise false (0) döndürür.
 */
bool getParity(uint8_t reg);
bool getParity(uint16_t reg);
bool getParity(uint32_t reg);
bool getParity(uint64_t reg);

/**
 * @brief Sayýnýn parity durumunu geliþmiþ bitwise teknikleri kullanarak kontrol eder (Daha hýzlý XOR yöntemi). 
 *
 * @param reg Ýþlem yapýlacak register deðeri.
 * @return Parity Tek ise true (1), Çift ise false (0) döndürür.
 */
bool getParityAdvanced(uint8_t reg);
bool getParityAdvanced(uint16_t reg);
bool getParityAdvanced(uint32_t reg);
bool getParityAdvanced(uint64_t reg);

/**
 * @brief Sayýnýn 2'nin tam kuvveti olup olmadýðýný kontrol eder (N & (N-1) == 0 hilesi).
 *
 * @param num Kontrol edilecek sayý.
 * @return Sayý 2'nin kuvveti ise true, deðilse false döndürür.
 */
bool is_power_of_two(uint8_t num);
bool is_power_of_two(uint16_t num);
bool is_power_of_two(uint32_t num);
bool is_power_of_two(uint64_t num);


// =========================================================================
// III. YARDIMCI MASKE ÝÞLEMLERÝ (TEMPLATE IMPLEMENTATION)
// KRÝTÝK NOT: Linker hatasýný önlemek için þablon implementasyonlarý buradadýr.
// =========================================================================

/**
 * @brief Belirtilen uzunlukta ve baþlangýç konumunda, hedef tipte bir maske oluþturur (Örn: 0b00011100).
 * @tparam T Maskenin tipini belirler (uint8_t, uint32_t vb.).
 * @param length Maskenin '1' olan bit uzunluðu.
 * @param start_bit Maskenin baþlangýç indeksi (LSB'den).
 * @return Oluþturulmuþ maske deðeri.
 */
template<typename T>
T CreateMask(int length, int start_bit) {
    // 1. (T)1 << length: length uzunluðunda 1'lerden oluþan bir alan oluþturmak için.
    // 2. - (T)1: Tüm '1'ler alanýný elde etmek için.
    T mask = ( (T)1 << length) - (T)1;
    return mask << start_bit;
}

/**
 * @brief Belirtilen alaný '0' yapmak için kullanýlan ters maskeyi oluþturur (Örn: 0b11100011).
 * @tparam T Maskenin tipini belirler.
 * @param length '0' yapýlacak alanýn uzunluðu.
 * @param start_bit '0' yapýlacak alanýn baþlangýç indeksi.
 * @return Oluþturulmuþ ters maske deðeri.
 */
template<typename T>
T ReverseMask(int length, int start_bit) {
    // 1. Önce normal maske oluþturulur.
    T mask = ( (T)1 << length) - (T)1;
    // 2. Konumlandýrýlýr ve tersi alýnýr (~), böylece hedef alan 0, diðerleri 1 olur.
    return ~(mask << start_bit);
}

#endif // BITOPS_H
