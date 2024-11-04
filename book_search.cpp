#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 

using namespace std;

struct Kitap {
    string ad;
    string yazar;
    int yayinYili;
    string isbn;

    static Kitap fromCSVLine(const string& line) {
        Kitap kitap;

        size_t pos = line.find_first_of(',');
        kitap.ad = line.substr(0, pos);

        size_t prevPos = pos + 1;
        pos = line.find_first_of(',', prevPos);
        kitap.yazar = line.substr(prevPos, pos - prevPos);

        prevPos = pos + 1;
        pos = line.find_first_of(',', prevPos);
        kitap.yayinYili = stoi(line.substr(prevPos, pos - prevPos));

        prevPos = pos + 1;
        kitap.isbn = line.substr(prevPos);

        return kitap;
    }
};

vector<Kitap> dosyadanVeriOku(const string& dosyaAdi) {
    ifstream dosya(dosyaAdi);
    vector<Kitap> kitaplar;

    if (!dosya.is_open()) {
        cerr << "Dosya açılamadı: " << dosyaAdi << endl;
        return kitaplar;
    }

    string satir;
    // Başlık satırını atla
    getline(dosya, satir);
    while (getline(dosya, satir)) {
        kitaplar.push_back(Kitap::fromCSVLine(satir));
    }

    dosya.close();
    return kitaplar;
}

Kitap ara(const vector<Kitap>& kitaplar, const string& anahtar) {
    auto iter = find_if(kitaplar.begin(), kitaplar.end(), [&](const Kitap& kitap) {
        return kitap.ad == anahtar || kitap.yazar == anahtar;
    });

    if (iter != kitaplar.end()) {
        return *iter;
    }

    return {"", "", 0, ""};
}

int main() {
    vector<Kitap> kitaplar = dosyadanVeriOku("kitaplar.csv");

    cout << "Aranacak kitap adı veya yazar adını girin: ";
    string anahtar;
    getline(cin, anahtar);

    Kitap sonuc = ara(kitaplar, anahtar);

    if (sonuc.ad.empty()) {
        cout << "Kitap bulunamadı." << endl;
    } else {
        cout << "Kitap Bilgileri:" << endl;
        cout << "Ad: " << sonuc.ad << endl;
        cout << "Yazar: " << sonuc.yazar << endl;
        cout << "Yayın Yılı: " << sonuc.yayinYili << endl;
        cout << "ISBN: " << sonuc.isbn << endl;
    }

    return 0;
}
