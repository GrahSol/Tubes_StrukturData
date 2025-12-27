#include <iostream>
#include "mll.h"

using namespace std;

void menuKelolaData(List &L, string babak) {
    int pilihan;
    do {
        cout<<"\n==============================="<<endl;
        cout<< "   MENU KELOLA DATA ("<< babak<< ")"<<endl;
        cout<< "==============================="<<endl;
        cout<< "1. Tampilkan Data Saat Ini"<<endl;
        cout<< "2. Lanjut Fase Berikutnya"<<endl;
        cout<< "3. Ubah Skor "<<endl;
        cout<< "4. Hapus Pertandingan"<<endl;
        cout<< "5. Tambah Pertandingan"<<endl;
        cout<< "6. Keluar"<<endl;
        cout<< "Pilihan: ";
        if (!(cin>> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            pilihan = 0;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch(pilihan) {
            case 1: tampilkanTurnamen(L); break;
            case 2: {
                adrRound r = L.first;
                while (r != nullptr && r->roundName != babak) {
                    r = r->next;
                }

                int jumlah = hitungPertandingan(r);
                int syarat = 0;

                if (babak == "16 Besar") {
                    syarat = 8;
                } else {
                    if (babak == "8 Besar") {
                        syarat = 4;
                    } else {
                        if (babak == "Semifinal") {
                            syarat = 2;
                        } else {
                            syarat = 1;
                        }
                    }
                }

                if (babak != "FINAL" && jumlah != syarat) {
                    cout<< "\nGAGAL LANJUT!"<< endl;
                    cout<< "Jumlah pertandingan di "<< babak<< " saat ini: "<<jumlah<< endl;
                    cout<< "Syarat untuk lanjut: "<< syarat<< " pertandingan."<< endl;
                    cout<< "Perhatikann jumlah pertandingan, Silakan Pilih menu yang sesuai terlebih dahulu."<< endl;
                    pilihan = 0;
                } else {
                    cout<<"Lanjut ke Fase Berikut"<< endl;
                }
                break;
            }
            case 3:
                ubahSkor(L, babak);
                break;
            case 4:
                hapusPertandingan(L, babak);
                break;
            case 5:
                tambahPertandinganManual(L, babak);
                break;
            case 6:
                cout<< "====== Program Selesai ======="<<endl;
                exit(0);
            default: cout<< "Pilihan tidak valid."<< endl;
        }
    } while (pilihan != 2);
}

int main() {
    List L;
    createList(L);
    insertLastRound(L, createNewRound("16 Besar"));
    insertLastRound(L, createNewRound("8 Besar"));
    insertLastRound(L, createNewRound("Semifinal"));
    insertLastRound(L, createNewRound("FINAL"));
    cout << "=========================================="<<endl;
    cout << "PROGRAM 16 BESAR HINGAA FINAL TURNAMEN UCL"<<endl;
    cout << "=========================================="<<endl;
    cout<<"Masukkan Data Pertandingan!"<<endl;


    adrRound round16 = L.first;
    for (int i = 0; i < 8; i++) {
        cout<< "\n=== Pertandingan ke-" << (i + 1)<< " (16 Besar) ===";
        infotype data = inputDataPertandingan("16 Besar");
        insertLastMatch(round16, createNewMatch(data));
    }

    menuKelolaData(L, "16 Besar");
    prosesBabakSelanjutnya(L.first);

    menuKelolaData(L, "8 Besar");
    prosesBabakSelanjutnya(L.first->next);

    menuKelolaData(L, "Semifinal");
    prosesBabakSelanjutnya(L.first->next->next);

    tampilkanTurnamen(L);
    adrRound r = L.first;
    while (r != nullptr) {
        if (r->roundName == "FINAL") {
            if (r->firstMatch != nullptr) {
                cout <<"\n\n==========================================="<<endl;
                cout <<"           JUARA UCL: " << cariPemenang(r->firstMatch->info)<<endl;
                cout <<"==========================================="<<endl;
            } else {
                cout<<"" ;
            }
        } else {
            cout<<"" ;
        }
        r = r->next;
    }

    return 0;
}
