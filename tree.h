#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct MatchData {
    string babak, timHome, timAway;

    int skorLeg1Home, skorLeg1Away;
    int skorLeg2Home, skorLeg2Away;
    int aggHome, aggAway;

    bool isPlayed;
};

typedef MatchData infotype;
typedef struct Node *adrNode;

struct Node {
    infotype info;
    adrNode left;
    adrNode right;
};

void createTree(adrNode &root);
adrNode createNode(infotype x);
infotype inputMatch(string labelBabak);
void linkNode(adrNode parent, adrNode left, adrNode right);
string getWinner(adrNode P);
void updateBracket(adrNode P);
void preOrder(adrNode P);
void inOrder(adrNode P);
void postOrder(adrNode P);

#endif // TREE_H_INCLUDED
