#include "mll.h"

void createList(List &L) {
    L.first = nullptr;
}

adrRound createNewRound(string nama) {
    adrRound r = new ElementRound;
    r->roundName = nama;
    r->firstMatch = nullptr;
    r->next = nullptr;
    return r;
}

adrMatch createNewMatch(infotype data) {
    adrMatch m = new ElementMatch;
    m->info = data;
    m->next = nullptr;
    return m;
}

void insertLastRound(List &L, adrRound r) {
    if (L.first == nullptr) {
        L.first = r;
    } else {
        adrRound p = L.first;
        while (p->next != nullptr) {
            p = p->next;
        }
        p->next = r;
    }
}

void insertLastMatch(adrRound r, adrMatch m) {
    if (r->firstMatch == nullptr) {
        r->firstMatch = m;
    } else {
        adrMatch p = r->firstMatch;
        while (p->next != nullptr) {
            p = p->next;
        }
        p->next = m;
    }
}

void deleteMatch(adrRound r, adrMatch m) {
    if (r->firstMatch == nullptr || m == nullptr) {
        return;
    } else {
        if (r->firstMatch == m) {
            r->firstMatch = m->next;
            delete m;
        } else {
            adrMatch p = r->firstMatch;
            while (p->next != nullptr && p->next != m) {
                p = p->next;
            }
            if (p->next == m) {
                p->next = m->next;
                delete m;
            } else {
                return;
            }
        }
    }
}

adrMatch findMatch(adrRound r, string teamName) {
    adrMatch p = r->firstMatch;
    while (p != nullptr) {
        if (p->info.timHome == teamName || p->info.timAway == teamName) {
            return p;
        } else {
            p = p->next;
        }
    }
    return nullptr;
}

void cekSeri(infotype &data) {
    if (data.aggHome == data.aggAway) {
        data.isPenalty = true;
        int pilihan;
        while (true) {
            cout<<" Skor Imbang ("<< data.aggHome << "-"<<data.aggAway << ")!" << endl;
            cout<<" Siapa pemenang adu penalti?" << endl;
            cout<<"   1. " << data.timHome << endl;
            cout<<"   2. " << data.timAway << endl;
            cout<<"Pilih (1/2): ";
            if (cin>>pilihan) {
                if (pilihan == 1 || pilihan == 2) {
                    break;
                } else {
                    cout<<"Pilihan tidak valid."<< endl;
                }
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        if (pilihan == 1) {
            data.aggHome++;
        } else {
            data.aggAway++;
        }
    } else {
        data.isPenalty = false;
    }
}

infotype inputDataPertandingan(string namaBabak) {
    infotype data;
    data.babak = namaBabak;
    data.isPenalty = false;
    cout<<" "<<endl;
    cout<< "Tim A: "; getline(cin, data.timHome);
    cout<< "Tim B: "; getline(cin, data.timAway);
    while (true) {
        cout<< "Skor Leg 1 ("<< data.timHome << " vs "<< data.timAway << "): ";
        if (cin>>data.skorLeg1Home>> data.skorLeg1Away) {
            break;
        } else {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    while (true) {
        cout<<"Skor Leg 2 (" << data.timAway << " vs "<< data.timHome<< "): ";
        if (cin >> data.skorLeg2Home >> data.skorLeg2Away) {
            break;
        } else {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    data.aggHome = data.skorLeg1Home + data.skorLeg2Away;
    data.aggAway = data.skorLeg1Away + data.skorLeg2Home;
    data.isPlayed = true;
    cekSeri(data);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return data;
}

string cariPemenang(infotype data) {
    if (data.aggHome > data.aggAway) {
        return data.timHome;
    } else {
        return data.timAway;
    }
}

int hitungPertandingan(adrRound r) {
    int count = 0;
    if (r != nullptr) {
        adrMatch p = r->firstMatch;
        while (p != nullptr) {
            count++;
            p = p->next;
        }
    } else {
        return 0;
    }
    return count;
}

void prosesBabakSelanjutnya(adrRound currentRound) {
    if (currentRound == nullptr || currentRound->next == nullptr) {
        return;
    } else {
        int jumlahMatch = hitungPertandingan(currentRound);
        int syarat = 0;
        if (currentRound->roundName == "16 Besar") {
            syarat = 8;
        } else {
            if (currentRound->roundName == "8 Besar") {
                syarat = 4;
            } else {
                if (currentRound->roundName == "Semifinal") {
                    syarat = 2;
                } else {
                    syarat = 0;
                }
            }
        }
        if (syarat > 0 && jumlahMatch != syarat) {
            cout<< "\nJumlah pertandingan di " << currentRound->roundName <<" tidak sesuai ("<< jumlahMatch<< "/"<< syarat<< ")."<<endl;
            cout<< "Silakan tambah pertandingan manual." <<endl;
            return;
        } else {
            if (currentRound->firstMatch == nullptr) {
                return;
            } else {
                adrRound nextRound = currentRound->next;
                adrMatch p = currentRound->firstMatch;
                int i = 1;
                cout<< "\n=============================================" <<endl;
                cout<< "   INPUT SKOR: " << nextRound->roundName <<endl;
                cout<< "=============================================" <<endl;
                while (p != nullptr && p->next != nullptr) {
                    cout<< "\n========= Pertandingan ke-"<< i<< " (" << nextRound->roundName << ") =========";
                    infotype dataBaru;
                    dataBaru.babak = nextRound->roundName;
                    dataBaru.isPenalty = false;
                    dataBaru.timHome = cariPemenang(p->info);
                    dataBaru.timAway = cariPemenang(p->next->info);
                    cout<< "\n"<< dataBaru.timHome << " vs "<< dataBaru.timAway<<endl;
                    if (nextRound->roundName == "FINAL") {
                        while(true) {
                            cout<<"Skor Pertandingan Final: ";
                            if(cin>>dataBaru.aggHome>>dataBaru.aggAway) {
                                dataBaru.skorLeg1Home = dataBaru.aggHome;
                                dataBaru.skorLeg1Away = dataBaru.aggAway;
                                dataBaru.skorLeg2Home = 0;
                                dataBaru.skorLeg2Away = 0;
                                break;
                            } else {
                                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        }
                    } else {
                        while(true) {
                            cout<<"Skor Leg 1 ("<<dataBaru.timHome << " vs " << dataBaru.timAway << "): ";
                            if(cin>>dataBaru.skorLeg1Home>> dataBaru.skorLeg1Away) {
                                break;
                            } else {
                                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        }
                        while(true) {
                            cout<<"Skor Leg 2 (" << dataBaru.timAway << " vs " << dataBaru.timHome << "): ";
                            if(cin>> dataBaru.skorLeg2Home >> dataBaru.skorLeg2Away) {
                                break;
                            } else {
                                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        }
                        dataBaru.aggHome = dataBaru.skorLeg1Home + dataBaru.skorLeg2Away;
                        dataBaru.aggAway = dataBaru.skorLeg1Away + dataBaru.skorLeg2Home;
                    }
                    dataBaru.isPlayed = true;
                    cekSeri(dataBaru);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    insertLastMatch(nextRound, createNewMatch(dataBaru));
                    p = p->next->next;
                    i++;
                }
            }
        }
    }
}

void tampilkanTurnamen(List L) {
    adrRound r = L.first;
    while (r != nullptr){
        cout << "\n==========================================================================" << endl;
        cout << "                          BABAK: " << r->roundName << endl;
        cout << "==========================================================================" << endl;
        adrMatch m = r->firstMatch;
        int i = 1;
        while (m != nullptr) {
            cout<< i<< ". "<< m->info.timHome << " [" << m->info.aggHome << "] - [" << m->info.aggAway << "] " << m->info.timAway;
            cout<< "  >>>  WINNER: " << cariPemenang(m->info);
            if (m->info.isPenalty) {
                cout<< " (Adu Penalti)";
            } else {
                cout<< "";
            }
            cout << endl;
            m = m->next;
            i++;
        }
        r = r->next;
    }
}

void ubahSkor(List L, string namaBabak) {
    adrRound r = L.first;
    while (r != nullptr && r->roundName != namaBabak) {
        r = r->next;
    }
    if (r != nullptr) {
        string tim;
        cout << "Nama tim: "; getline(cin, tim);
        adrMatch m = findMatch(r, tim);
        if (m != nullptr) {
            if (r->roundName == "FINAL") {
                while(true) {
                    cout << "Skor Baru Final: ";
                    if(cin >> m->info.aggHome >> m->info.aggAway) {
                        break;
                    } else {
                        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
            } else {
                while(true) {
                    cout << "Skor Baru Leg 1: ";
                    if(cin >> m->info.skorLeg1Home >> m->info.skorLeg1Away) {
                        break;
                    } else {
                        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                while(true) {
                    cout << "Skor Baru Leg 2: ";
                    if(cin >> m->info.skorLeg2Home >> m->info.skorLeg2Away) {
                        break;
                    } else {
                        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                m->info.aggHome = m->info.skorLeg1Home + m->info.skorLeg2Away;
                m->info.aggAway = m->info.skorLeg1Away + m->info.skorLeg2Home;
            }
            cekSeri(m->info);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return;
        }
    } else {
        return;
    }
}

void hapusPertandingan(List &L, string namaBabak) {
    adrRound r = L.first;
    while (r != nullptr && r->roundName != namaBabak) {
        r = r->next;
    }
    if (r != nullptr) {
        string tim;
        cout<< "Hapus tim: "; getline(cin, tim);
        adrMatch m = findMatch(r, tim);
        if (m != nullptr) {
            deleteMatch(r, m);
            cout << "Pertandingan dihapus." <<endl;
        } else {
            return;
        }
    } else {
        return;
    }
}

void tambahPertandinganManual(List &L, string namaBabak) {
    adrRound r = L.first;
    while (r != nullptr && r->roundName != namaBabak) {
        r = r->next;
    }
    if (r != nullptr) {
        infotype data = inputDataPertandingan(namaBabak);
        insertLastMatch(r, createNewMatch(data));
        cout << "Pertandingan berhasil ditambahkan." <<endl;
    } else {
        return;
    }
}
