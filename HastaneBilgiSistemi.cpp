#include <iostream>
#include <string>

using namespace std;

#define MAKS_DOKTOR 10
#define MAKS_HASTA 10
#define MAKS_RANDEVU 20

class Kisi {
protected:
    string isim;
    string soyisim;
    string telefon;

public:
    Kisi(string isim, string soyisim, string telefon)
        : isim(isim), soyisim(soyisim), telefon(telefon) {}

    virtual void bilgiYazdir() {
        cout << "Ad: " << isim << ", Soyad: " << soyisim << ", Telefon: " << telefon << endl;
    }

    virtual ~Kisi() {}
};

class Doktor : public Kisi {
private:
    string uzmanlik;
    int doktorID;

public:
    Doktor(string isim, string soyisim, string telefon, string uzmanlik, int doktorID)
        : Kisi(isim, soyisim, telefon), uzmanlik(uzmanlik), doktorID(doktorID) {}

    void bilgiYazdir() override {
        cout << "Doktor ID: " << doktorID << ", ";
        Kisi::bilgiYazdir();
        cout << "Uzmanlık: " << uzmanlik << endl;
    }

    int getDoktorID() { return doktorID; }
};

class Hasta : public Kisi {
private:
    int yas;
    string hastaID;

public:
    Hasta(string isim, string soyisim, string telefon, int yas, string hastaID)
        : Kisi(isim, soyisim, telefon), yas(yas), hastaID(hastaID) {}

    void bilgiYazdir() override {
        cout << "Hasta ID: " << hastaID << ", ";
        Kisi::bilgiYazdir();
        cout << "Yaş: " << yas << endl;
    }

    string getHastaID() { return hastaID; }
};

class Randevu {
private:
    int randevuID;
    Doktor* doktor;
    Hasta* hasta;
    string tarih;

public:
    Randevu(int randevuID, Doktor* doktor, Hasta* hasta, string tarih)
        : randevuID(randevuID), doktor(doktor), hasta(hasta), tarih(tarih) {}

    void randevuBilgisi() {
        cout << "Randevu ID: " << randevuID << endl;
        cout << "Tarih: " << tarih << endl;
        cout << "Doktor: ";
        doktor->bilgiYazdir();
        cout << "Hasta: ";
        hasta->bilgiYazdir();
    }
};

class HastaneYonetim {
private:
    Doktor* doktorlar[MAKS_DOKTOR];
    Hasta* hastalar[MAKS_HASTA];
    Randevu* randevular[MAKS_RANDEVU];
    int doktorSayisi;
    int hastaSayisi;
    int randevuSayisi;

public:
    HastaneYonetim() : doktorSayisi(0), hastaSayisi(0), randevuSayisi(0) {}

    void doktorEkle(Doktor* doktor) {
        if (doktorSayisi < MAKS_DOKTOR) {
            doktorlar[doktorSayisi++] = doktor;
            cout << "Doktor eklendi: " << doktor->getDoktorID() << endl;
        }
        else {
            cout << "Maksimum doktor sayısına ulaşıldı!" << endl;
        }
    }

    void hastaEkle(Hasta* hasta) {
        if (hastaSayisi < MAKS_HASTA) {
            hastalar[hastaSayisi++] = hasta;
            cout << "Hasta eklendi: " << hasta->getHastaID() << endl;
        }
        else {
            cout << "Maksimum hasta sayısına ulaşıldı!" << endl;
        }
    }

    void randevuOlustur(int randevuID, Doktor* doktor, Hasta* hasta, string tarih) {
        if (randevuSayisi < MAKS_RANDEVU) {
            randevular[randevuSayisi++] = new Randevu(randevuID, doktor, hasta, tarih);
            cout << "Randevu oluşturuldu: ID " << randevuID << endl;
        }
        else {
            cout << "Maksimum randevu sayısına ulaşıldı!" << endl;
        }
    }

    void doktorlariListele() {
        cout << "\nTüm Doktorlar:\n";
        for (int i = 0; i < doktorSayisi; i++) {
            doktorlar[i]->bilgiYazdir();
            cout << endl;
        }
    }

    void hastalariListele() {
        cout << "\nTüm Hastalar:\n";
        for (int i = 0; i < hastaSayisi; i++) {
            hastalar[i]->bilgiYazdir();
            cout << endl;
        }
    }

    void randevulariListele() {
        cout << "\nTüm Randevular:\n";
        for (int i = 0; i < randevuSayisi; i++) {
            randevular[i]->randevuBilgisi();
            cout << endl;
        }
    }
};

int main() {
    HastaneYonetim hastane;

    Doktor* doktor1 = new Doktor("Ahmet", "Yılmaz", "123456789", "Kardiyoloji", 101);
    Doktor* doktor2 = new Doktor("Mehmet", "Kaya", "987654321", "Ortopedi", 102);

    hastane.doktorEkle(doktor1);
    hastane.doktorEkle(doktor2);

    Hasta* hasta1 = new Hasta("Ali", "Demir", "456123789", 35, "H001");
    Hasta* hasta2 = new Hasta("Ayşe", "Çelik", "789456123", 28, "H002");

    hastane.hastaEkle(hasta1);
    hastane.hastaEkle(hasta2);

    
    hastane.randevuOlustur(1, doktor1, hasta1, "2024-11-20");
    hastane.randevuOlustur(2, doktor2, hasta2, "2024-11-21");

    hastane.doktorlariListele();
    hastane.hastalariListele();
    hastane.randevulariListele();

    return 0;
}
