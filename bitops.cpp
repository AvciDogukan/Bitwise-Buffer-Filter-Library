/**
 * @file bitops.cpp
 * @brief Çoklu Bit Geniþlikleri için Kapsamlý Bitwise Ýþlemleri Kütüphanesi Implementasyonu.
 *
 * Bu dosya, uint8_t'den uint64_t'ye kadar tüm standart tam sayý tipleri için
 * temel manipülasyon, alan yönetimi, akýþ kontrolü ve analiz iþlemlerini
 * gerçekleþtiren fonksiyon aþýrý yüklemelerini içerir.
 * Þablon (template) implementasyonlarý Linker sorununu önlemek için 'bitops.h' dosyasýnda tutulmuþtur.
 *
 * @author Doðukan Avcý
 * @date 15 Aralýk 2025
 * @version 1.1.0 (Template/Overloading Birleþimi)
 * @copyright Telif Hakký (c) 2025 Doðukan Avcý. Tüm Haklarý Saklýdýr.
 */

#include "bitops.h" // Prototipler ve þablon implementasyonlarý burada
#include <cstdio>   // C stili I/O fonksiyonlarý için (Gerekliyse)
#include <limits>   // std::numeric_limits<T>::digits kullanýmý için (RotateLeft/Right'ta N deðeri için)

// =========================================================================
// I. TEMEL MANÝPÜLASYON ÝÞLEMLERÝ (SINGLE BIT OPERATIONS)
// =========================================================================

/**
 * MÜHENDÝSLÝK NOTU: Set/Clear/Toggle iþlemlerinde, tip uyumluluðu ve olasý tamsayý
 * yükseltmeleri (Integer Promotion) nedeniyle `1` literalinin (uintX_t) tipine
 * açýkça cast edilmesi veya doðru suffix (U, UL, ULL) kullanýlmasý KRÝTÝKTÝR.
 */

// SetRegBit (Biti 1 Yapma) Implementasyonlarý (Maskeleme: OR |)
uint8_t SetRegBit(uint8_t reg, int index) {
	return reg | ((uint8_t)1 << index);	// 8-bit maskeleme için (uint8_t)1 cast'ý.
}
uint16_t SetRegBit(uint16_t reg, int index) {
	return reg | ((uint16_t)1 << index);
}
uint32_t SetRegBit(uint32_t reg, int index) {
	return reg | (1U << index);	// 32-bit için 1U suffix'i kullanýlýr.
}
uint64_t SetRegBit(uint64_t reg, int index) {
	return reg | (1ULL << index);	// 64-bit için 1ULL suffix'i KRÝTÝKTÝR.
}


// ClearRegBit (Biti 0 Yapma) Implementasyonlarý (Maskeleme: AND & ~)
uint8_t ClearRegBit(uint8_t reg, int index) {
	return reg & ~((uint8_t)1 << index);
}
uint16_t ClearRegBit(uint16_t reg, int index) {
	return reg & ~((uint16_t)1 << index);
}
uint32_t ClearRegBit(uint32_t reg, int index) {
	return reg & ~(1U << index);
}
uint64_t ClearRegBit(uint64_t reg, int index) {
	return reg & ~(1ULL << index);
}

// ToggleRegBit (Biti Ters Çevirme) Implementasyonlarý (Maskeleme: XOR ^)
uint8_t ToggleRegBit(uint8_t reg, int index) {
	return reg ^ ((uint8_t)1 << index);
}
uint16_t ToggleRegBit(uint16_t reg, int index) {
	return reg ^ ((uint16_t)1 << index);
}
uint32_t ToggleRegBit(uint32_t reg, int index) {
	return reg ^ (1U << index);
}
uint64_t ToggleRegBit(uint64_t reg, int index) {
	return reg ^ (1ULL << index);
}

// isBitSet (Bit Kontrolü) Implementasyonlarý
bool isBitSet(uint8_t reg, int index) {	
	// Shift-and-check (Kaydýr ve kontrol et) yöntemi kullanýlýr.
	return (reg >> index) & 1;
}
bool isBitSet(uint16_t reg, int index) {	
	return (reg >> index) & 1;
}
bool isBitSet(uint32_t reg, int index) {	
	return (reg >> index) & 1U;
}
bool isBitSet(uint64_t reg, int index) {	
	return (reg >> index) & 1ULL; // 64-bit için 1ULL kullanýmý.
}


// =========================================================================
// II. BÝT ALANI ÝÞLEMLERÝ (BIT FIELD OPERATIONS)
// =========================================================================

// get_bit_field (Bit Alaný Oku) Implementasyonlarý
uint8_t get_bit_field(uint8_t reg, int start_bit, int length) {
	// Maske: (1 << length) - 1. Okuma: Önce kaydýr, sonra maskele.
	uint8_t mask = (1U << length) - 1U;
	return (reg >> start_bit) & mask; 
}
uint16_t get_bit_field(uint16_t reg, int start_bit, int length) {
	uint16_t mask = (1U << length) - 1U;
	return (reg >> start_bit) & mask;
}
uint32_t get_bit_field(uint32_t reg, int start_bit, int length) {
	uint32_t mask = (1U << length) - 1U;
	return (reg >> start_bit) & mask;
}
uint64_t get_bit_field(uint64_t reg, int start_bit, int length) {
	// 64-bit için maske oluþturulurken 1ULL kullanýlýr.
	uint64_t mask = (1ULL << length) - 1ULL; 
	return (reg >> start_bit) & mask;
}


// set_bit_field (Bit Alaný Yaz) Implementasyonlarý
uint8_t set_bit_field(uint8_t reg, int start_bit, int length, uint8_t new_value) {
	uint8_t mask = (1U << length) - 1U;
	reg &= ~(mask << start_bit);	 	 // 1. Alaný ters maske ile temizle.
	new_value &= mask;				     // 2. Yeni deðeri, taþmayý önlemek için maskele.
	reg |= (new_value << start_bit);	 // 3. Yeni deðeri kaydýrarak alana yerleþtir (OR).
	return reg;
}
uint16_t set_bit_field(uint16_t reg, int start_bit, int length, uint16_t new_value) {
	uint16_t mask = (1U << length) - 1U;
	reg &= ~(mask << start_bit);
	new_value &= mask;
	reg |= (new_value << start_bit);
	return reg;
}
uint32_t set_bit_field(uint32_t reg, int start_bit, int length, uint32_t new_value) {
	uint32_t mask = (1U << length) - 1U;
	reg &= ~(mask << start_bit);
	new_value &= mask;
	reg |= (new_value << start_bit);
	return reg;
}
uint64_t set_bit_field(uint64_t reg, int start_bit, int length, uint64_t new_value) {
	uint64_t mask = (1ULL << length) - 1ULL;
	reg &= ~(mask << start_bit);
	new_value &= mask;
	reg |= (new_value << start_bit);
	return reg;
}


// =========================================================================
// IV. POZÝSYON VE AKIÞ ÝÞLEMLERÝ (POSITION & FLOW OPERATIONS)
// =========================================================================

// RotateLeft (Sola Döndür) Implementasyonlarý
uint8_t RotateLeft(uint8_t reg, int shift) {
	const int N = 8;
	shift %= N;
	// Dairesel kaydýrma formülü: (reg << shift) | (reg >> (N - shift))
	return (reg << shift) | (reg >> (N - shift));
}
uint16_t RotateLeft(uint16_t reg, int shift) {
	const int N = 16;
	shift %= N;
	return (reg << shift) | (reg >> (N - shift));
}
uint32_t RotateLeft(uint32_t reg, int shift) {
	const int N = 32;
	shift %= N;
	return (reg << shift) | (reg >> (N - shift));
}
uint64_t RotateLeft(uint64_t reg, int shift) {
	const int N = 64;
	shift %= N;
	return (reg << shift) | (reg >> (N - shift));
}

// RotateRight (Saða Döndür) Implementasyonlarý
uint8_t RotateRight(uint8_t reg, int shift) {
	const int N = 8;
	shift %= N;
	// Dairesel kaydýrma formülü: (reg >> shift) | (reg << (N - shift))
	return (reg >> shift) | (reg << (N - shift));
}
uint16_t RotateRight(uint16_t reg, int shift) {
	const int N = 16;
	shift %= N;
	return (reg >> shift) | (reg << (N - shift));
}
uint32_t RotateRight(uint32_t reg, int shift) {
	const int N = 32;
	shift %= N;
	return (reg >> shift) | (reg << (N - shift));	
}
uint64_t RotateRight(uint64_t reg, int shift) {
	const int N = 64;
	shift %= N;
	return (reg >> shift) | (reg << (N - shift));
}


// find_first_set_bit (Ýlk '1' Bitini Bul) Implementasyonlarý (LSB'den baþlar)
int find_first_set_bit(uint8_t reg) {
	if (reg == 0) return -1;
    // MÜHENDÝSLÝK NOTU: Modern C++'ta __builtin_ctz (count trailing zeros) veya
    // std::countr_zero daha hýzlýdýr, ancak bu saf C++ mantýðýdýr.
	int count = 0;
	while (!(reg & 1U)) { // LSB 0 olduðu sürece
		reg >>= 1;
		count++;
	}
	return count;
}
int find_first_set_bit(uint16_t reg) {
	if (reg == 0) return -1;
	int count = 0;
	while (!(reg & 1U)) {
		reg >>= 1;
		count++;
	}
	return count;
}
int find_first_set_bit(uint32_t reg) {
	if (reg == 0) return -1;
	int count = 0;
	while (!(reg & 1U)) {
		reg >>= 1;
		count++;
	}
	return count;
}
int find_first_set_bit(uint64_t reg) {
	if (reg == 0) return -1;
	int count = 0;
	while (!(reg & 1ULL)) { // 64-bit için 1ULL ile kontrol
		reg >>= 1;
		count++;
	}
	return count;
}


// =========================================================================
// V. KONTROL VE ANALÝZ ÝÞLEMLERÝ (CONTROL & ANALYSIS)
// =========================================================================

// count_set_bits (Popcount) Implementasyonlarý (Klasik Kaydýrma Yöntemi)
int count_set_bits(uint8_t reg) {
    // MÜHENDÝSLÝK NOTU: Bu, O(N) karmaþýklýðýna sahiptir. Brian Kernighan'ýn
    // O(K) karmaþýklýðýna sahip algoritmasý veya __builtin_popcount daha hýzlýdýr.
	int count = 0;
	while (reg != 0) {
		if (reg & 1U) count++;
		reg >>= 1;
	}
	return count;
}
int count_set_bits(uint16_t reg) {
	int count = 0;
	while (reg != 0) {
		if (reg & 1U) count++;
		reg >>= 1;
	}
	return count;
}
int count_set_bits(uint32_t reg) {
	int count = 0;
	while (reg != 0) {
		if (reg & 1U) count++;
		reg >>= 1;
	}
	return count;
}
int count_set_bits(uint64_t reg) {
	int count = 0;
	while (reg != 0) {
		if (reg & 1ULL) count++; // 64-bit için 1ULL ile kontrol
		reg >>= 1;
	}
	return count;
}

// getParity (Parity Kontrolü) Implementasyonlarý (count_set_bits'e dayanýr)
bool getParity(uint8_t reg) {
	// Parity (Teklik/Çiftlik): Set edilen bit sayýsýnýn LSB'sini kontrol et. (Modül 2'ye eþdeðer)
	return count_set_bits(reg) & 1; 
}
bool getParity(uint16_t reg) {
	return count_set_bits(reg) & 1;
}
bool getParity(uint32_t reg) {
	return count_set_bits(reg) & 1;
}
bool getParity(uint64_t reg) {
	return count_set_bits(reg) & 1;
}

// is_power_of_two (2'nin Kuvveti Kontrolü) Implementasyonlarý
bool is_power_of_two(uint8_t num) {
	// Sayý > 0 VE sadece tek bir bit set edilmiþse.
	return (num > 0) && ((num & (num - 1)) == 0);
}
bool is_power_of_two(uint16_t num) {
	return (num > 0) && ((num & (num - 1)) == 0);
}
bool is_power_of_two(uint32_t num) {
	return (num > 0) && ((num & (num - 1)) == 0);
}
bool is_power_of_two(uint64_t num) {
	return (num > 0) && ((num & (num - 1)) == 0);
}

// =========================================================================
// EK NOT: getParityAdvanced gibi opsiyonel fonksiyonlarýn implementasyonlarý
// istenirse buraya eklenebilir. Örneðin:
//
// bool getParityAdvanced(uint32_t num) {
//     num ^= num >> 16;
//     num ^= num >> 8;
//     num ^= num >> 4;
//     num ^= num >> 2;
//     num ^= num >> 1;
//     return num & 1;
// }
// =========================================================================
