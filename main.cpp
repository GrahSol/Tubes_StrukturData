#include <iostream>
#include <limits>
#include "tree.h"

using namespace std;

int main() {
    adrNode root;
    createTree(root);

    // Array untuk menampung 8 node pertandingan 16 besar
    adrNode match16Besar[8];
    infotype dataMatch;

    cout << "=============================================" << endl;
    cout << "   SISTEM TURNAMEN UCL (16 BESAR -> FINAL)   " << endl;
    cout << "=============================================" << endl;

    for (int i = 0; i < 8; i++) {
        cout << "\n===Pertandingan ke-" << (i + 1) << " (16 Besar)===";
        dataMatch = inputMatch("16 Besar");
        match16Besar[i] = createNode(dataMatch);
    }


    infotype blank;
    blank.babak = "TBD"; blank.timHome="TBD"; blank.timAway="TBD"; blank.isPlayed=false;

    //Node Quarter Final (4 Node Induk)
    adrNode qf1 = createNode(blank); qf1->info.babak = "Quarter Final";
    adrNode qf2 = createNode(blank); qf2->info.babak = "Quarter Final";
    adrNode qf3 = createNode(blank); qf3->info.babak = "Quarter Final";
    adrNode qf4 = createNode(blank); qf4->info.babak = "Quarter Final";

    // Hubungkan 16 Besar ke Quarter Final
    linkNode(qf1, match16Besar[0], match16Besar[1]);

    linkNode(qf2, match16Besar[2], match16Besar[3]);

    linkNode(qf3, match16Besar[4], match16Besar[5]);

    linkNode(qf4, match16Besar[6], match16Besar[7]);

    //  Node Semifinal
    adrNode sf1 = createNode(blank); sf1->info.babak = "Semifinal";
    adrNode sf2 = createNode(blank); sf2->info.babak = "Semifinal";

    // Hubungkan QF ke Semifinal
    linkNode(sf1, qf1, qf2);
    linkNode(sf2, qf3, qf4);

    // Node Final
    root = createNode(blank);
    root->info.babak = "FINAL";

    // Hubungkan SF ke Final
    linkNode(root, sf1, sf2);

    // PROSES HITUNG PEMENANG (REKURSIF)
    updateBracket(root);

    // TRAVERSAL
    cout << "\n=============================================" << endl;
    cout << "       RIWAYAT PERTANDINGAN (POST-ORDER)     " << endl;
    cout << "=============================================" << endl;
    postOrder(root);

    cout << "\n=============================================" << endl;
    cout << "       STRUKTUR HIERARKI (PRE-ORDER)         " << endl;
    cout << "=============================================" << endl;
    preOrder(root);

    cout << "\n=============================================" << endl;
    cout << "       DAFTAR MATCH (IN-ORDER)               " << endl;
    cout << "=============================================" << endl;
    inOrder(root);

    return 0;
}
