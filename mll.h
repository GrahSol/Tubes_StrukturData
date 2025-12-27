#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED

#include <iostream>
using namespace std;
#include <string>
#include <limits>


struct MatchData {
    string babak, timHome, timAway;
    int skorLeg1Home, skorLeg1Away;
    int skorLeg2Home, skorLeg2Away;
    int aggHome, aggAway;
    bool isPlayed;
    bool isPenalty;
};

typedef MatchData infotype;
typedef struct ElementMatch *adrMatch;
typedef struct ElementRound *adrRound;

struct ElementMatch {
    infotype info;
    adrMatch next;
};

struct ElementRound {
    string roundName;
    adrMatch firstMatch;
    adrRound next;
};

struct List {
    adrRound first;
};

void createList(List &L);
adrRound createNewRound(string nama);
adrMatch createNewMatch(infotype data);
void insertLastRound(List &L, adrRound r);
void insertLastMatch(adrRound r, adrMatch m);
void deleteMatch(adrRound r, adrMatch m);

adrMatch findMatch(adrRound r, string teamName);
infotype inputDataPertandingan(string namaBabak);
void cekSeri(infotype &data);
string cariPemenang(infotype data);
void prosesBabakSelanjutnya(adrRound currentRound);
void tampilkanTurnamen(List L);
void ubahSkor(List L, string namaBabak);
void hapusPertandingan(List &L, string namaBabak);
void tambahPertandinganManual(List &L, string namaBabak);
int hitungPertandingan(adrRound r);

#endif // MLL_H_INCLUDED
