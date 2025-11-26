#include "tree.h"

void createTree(adrNode &root) {
    root = nullptr;
}

adrNode createNode(infotype x) {
    adrNode P = new Node;
    if (P != nullptr) {
        P->info = x;
        P->left = nullptr;
        P->right = nullptr;
    }
    return P;
}

infotype inputMatch(string labelBabak) {
    infotype data;
    data.babak = labelBabak;

    cout << "\n--- Input Data " << labelBabak << " ---" << endl;
    cout << "Tim Home: "; getline(cin, data.timHome);
    cout << "Tim Away: "; getline(cin, data.timAway);

    cout << "Skor Leg 1 (" << data.timHome << " vs " << data.timAway << "): ";
    cin >> data.skorLeg1Home >> data.skorLeg1Away;

    cout << "Skor Leg 2 (" << data.timAway << " vs " << data.timHome << "): ";
    cin >> data.skorLeg2Home >> data.skorLeg2Away;

    data.aggHome = data.skorLeg1Home + data.skorLeg2Away;
    data.aggAway = data.skorLeg1Away + data.skorLeg2Home;
    data.isPlayed = true;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return data;
}


void linkNode(adrNode parent, adrNode left, adrNode right) {
    if (parent != nullptr ) {
        parent->left = left;
        parent->right = right;
    }
}

string getWinner(adrNode P) {
    if (P->info.aggHome > P->info.aggAway) return P->info.timHome;
    else return P->info.timAway;
}

void updateBracket(adrNode P) {
    if (P == nullptr) return;
    updateBracket(P->left);
    updateBracket(P->right);


    if (P->left != nullptr && P->right != nullptr) {
        string winnerLeft = getWinner(P->left);
        string winnerRight = getWinner(P->right);

        P->info.timHome = winnerLeft;
        P->info.timAway = winnerRight;
        P->info.isPlayed = true;


        P->info.skorLeg1Home = 1;
        P->info.skorLeg1Away = 0;
        P->info.skorLeg2Home = 0;
        P->info.skorLeg2Away = 0;

        P->info.aggHome = 1;
        P->info.aggAway = 0;
    }
}

void preOrder(adrNode P) {
    if (P != nullptr) {
        cout << "[" << P->info.babak << "] " << P->info.timHome << " vs " << P->info.timAway;
        if (P->info.isPlayed) {
            cout << " (Agg: " << P->info.aggHome << "-" << P->info.aggAway << ")";
        }
        cout << endl;

        preOrder(P->left);
        preOrder(P->right);
    }
}

void inOrder(adrNode P) {
    if (P != nullptr) {
        inOrder(P->left);
        cout << "[" << P->info.babak << "] " << P->info.timHome << " vs " << P->info.timAway << endl;
        inOrder(P->right);
    }
}

void postOrder(adrNode P) {
    if (P != nullptr) {
        postOrder(P->left);
        postOrder(P->right);

        cout << "Stage: " << P->info.babak << " | " << P->info.timHome << " vs " << P->info.timAway;
        if (P->info.isPlayed) {
            cout << " [Leg 1: " << P->info.skorLeg1Home << "-" << P->info.skorLeg1Away << "]";
            cout << " [Leg 2: " << P->info.skorLeg2Home << "-" << P->info.skorLeg2Away << "]";
            cout << " AGG: " << P->info.aggHome << "-" << P->info.aggAway;
        }
        cout << endl;
    }
}
