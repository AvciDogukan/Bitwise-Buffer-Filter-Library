/**
 * @file main.cpp
 * @brief BITOPS Kütüphanesi Test ve Doðrulama Uygulamasý.
 *
 * Bu dosya, tüm aþýrý yüklenmiþ (overloaded) ve þablonlu (templated) bitwise
 * manipülasyon fonksiyonlarýnýn (SetRegBit, CreateMask, RotateLeft vb.)
 * çeþitli veri tipleri (uint8_t, uint32_t, uint64_t) üzerindeki
 * doðru çalýþtýðýný göstermek için kullanýlýr.
 *
 * @author Doðukan Avcý
 * @date 15 Aralýk 2025
 */

#include <iostream>
#include <iomanip>
#include <string>
#include "bitops.h" // Kütüphane implementasyonu

// =========================================================================
// YARDIMCI FONKSÝYONLAR
// =========================================================================

/**
 * @brief Verilen tam sayýyý ikili (binary) formatta, okunabilir gruplar halinde (genellikle 8'li) yazdýrýr.
 * @tparam T Test edilen tam sayý tipi (uint8_t, uint16_t, uint32_t, uint64_t).
 * @param description Çýktýda gösterilecek açýklayýcý metin.
 * @param value Yazdýrýlacak sayýsal deðer.
 */
template<typename T>
void print_binary(const std::string& description, T value) {
    std::cout << description << " (Dec: " << std::dec << value << "): 0b";
    
    // T tipinin bit sayýsýný hesapla
    const int bits = sizeof(T) * 8;
    
    // Yüksek bitten (MSB) baþla
    for (int i = bits - 1; i >= 0; --i) {
        // Her 8 bitten sonra (Byte sýnýrý) boþluk ekleyerek okunabilirliði artýr.
        if ((i + 1) % 8 == 0 && i != bits - 1) {
            std::cout << " ";
        }
        // Ýlgili biti kontrol et ve yazdýr
        std::cout << ((value >> i) & 1);
    }
    std::cout << std::endl;
}

// =========================================================================
// TEST SÜÝTÝ
// =========================================================================

/**
 * @brief BITOPS kütüphanesindeki tüm fonksiyonlarý test eden ana süit.
 */
void run_tests() {
    
    // --- TEST 1: TEMEL MANÝPÜLASYONLAR (uint32_t) ---
    std::cout << "=== TEST 1: TEMEL MANÝPÜLASYONLAR (uint32_t) ===" << std::endl;
    // Baþlangýç deðeri: 0x550000AA (0101...1010)
    uint32_t reg = 0x550000AA; 
    print_binary("1. Baþlangýç Register'ý", reg);

    // SetRegBit Testi: 12. biti (0) 1 yapar.
    reg = SetRegBit(reg, 12); 
    print_binary("2. SetRegBit(12) Sonrasý", reg); 

    // ClearRegBit Testi: 31. (MSB) biti (0) 0 yapar (etkisiz olmalý, zaten 0'dý, ancak 30. biti deneyelim: 30. bit 0'dýr, SetRegBit'te 31. bit 0 olur).
    // Testin anlamlý olmasý için 30. biti temizleyelim (önce 1'dir).
    reg = ClearRegBit(reg, 30); 
    print_binary("3. ClearRegBit(30) Sonrasý", reg); // 30. bit 0 olmalý

    // ToggleRegBit Testi: 1. biti ters çevirir (önce 1'di, þimdi 0 olmalý)
    reg = ToggleRegBit(reg, 1); 
    print_binary("4. ToggleRegBit(1) Sonrasý", reg); 

    // isBitSet Testi: 12. bitin set olup olmadýðýný kontrol eder (TRUE bekliyoruz).
    bool is_12_set = isBitSet(reg, 12);
    std::cout << "5. isBitSet(12)? " << (is_12_set ? "TRUE" : "FALSE") << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
    
    
    // --- TEST 2: ÞABLONLU MASKE ÝÞLEMLERÝ ---
    std::cout << "=== TEST 2: ÞABLONLU MASKE ÝÞLEMLERÝ ===" << std::endl;
    
    // CreateMask Testi: uint16_t tipi için 5 bit uzunluðunda, 4. indexten baþlayan maske oluþturur.
    uint16_t mask16 = CreateMask<uint16_t>(5, 4); 
    print_binary("1. CreateMask<uint16_t>(5, 4)", mask16); 

    // ReverseMask Testi: uint8_t tipi için 3 bit uzunluðunda, 5. indexten baþlayan alaný 0 yapan maske.
    uint8_t mask8 = ReverseMask<uint8_t>(3, 5); 
    print_binary("2. ReverseMask<uint8_t>(3, 5)", mask8); 

    // ReverseMask Testi: uint64_t tipi için 63. biti (MSB) 0 yapan maske.
    uint64_t mask64 = ReverseMask<uint64_t>(1, 63); 
    print_binary("3. ReverseMask<uint64_t>(1, 63)", mask64); 
    std::cout << "----------------------------------------------------" << std::endl;
    
    
    // --- TEST 3: BÝT ALANI ÝÞLEMLERÝ (uint16_t) ---
    std::cout << "=== TEST 3: BÝT ALANI ÝÞLEMLERÝ ===" << std::endl;
    // Baþlangýç deðeri: 1101 0110 1010 0001
    uint16_t field_reg = 0b1101011010100001;
    print_binary("1. Baþlangýç Register'ý", field_reg);
    
    int start = 4; // Baþlangýç: 4. index
    int length = 5; // Uzunluk: 5 bitlik alan

    // get_bit_field Testi: 4. indexten 5 bit oku (Deðer 01010 olmalý)
    uint16_t value = get_bit_field(field_reg, start, length);
    print_binary("2. Okunan Bit Alaný (4-8)", value); 

    // set_bit_field Testi: Ayný alana 11111 deðerini yaz.
    uint16_t new_value = 0b11111; 
    field_reg = set_bit_field(field_reg, start, length, new_value);
    print_binary("3. set_bit_field Sonrasý", field_reg); 
    std::cout << "----------------------------------------------------" << std::endl;
    
    
    // --- TEST 4: AKIÞ VE ANALÝZ ÝÞLEMLERÝ (uint64_t) ---
    std::cout << "=== TEST 4: AKIÞ VE ANALÝZ ÝÞLEMLERÝ ===" << std::endl;
    // Baþlangýç deðeri: Sadece MSB ve en saðdaki 4 bit set. Toplam 5 bit set.
    uint64_t large_reg = 0x800000000000000FULL; 
    print_binary("1. Baþlangýç Register'ý", large_reg); 

    // count_set_bits Testi: Set bit sayýsýný hesapla (5 bekliyoruz).
    std::cout << "2. count_set_bits: " << count_set_bits(large_reg) << std::endl;

    // is_power_of_two Testi: Sadece tek bir bit set edilip edilmediðini kontrol eder.
    uint16_t pwr2 = 1024; // 0b10000000000 (tek bit set)
    std::cout << "3. is_power_of_two(1024): " << (is_power_of_two(pwr2) ? "TRUE" : "FALSE") << std::endl; 
    
    // RotateLeft Testi: 4 bit sola dairesel kaydýrma.
    uint64_t rotated_left = RotateLeft(large_reg, 4); 
    print_binary("4. RotateLeft(4) Sonrasý", rotated_left);
    
    // find_first_set_bit Testi: En saðdaki (LSB) set bitin indexini bulur.
    std::cout << "5. find_first_set_bit(0): " << find_first_set_bit((uint32_t)0) << " (Hata kodu: -1)" << std::endl; 
}

/**
 * @brief Programýn ana giriþ noktasý. Test süitini çalýþtýrýr.
 */
int main() {
    // std::hex ve std::dec gibi formatlama fonksiyonlarýnýn kullanýmý için not.
    run_tests();
    return 0;
}
