#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class AncestralTree {
public:
    char name;
    AncestralTree *ancestor;

    explicit AncestralTree(char name) {
        this->name = name;
        this->ancestor = nullptr;
    }

    void addAsAncestor(const vector<AncestralTree *>& descendants);
};

AncestralTree *getAncestor(AncestralTree *lowerDescendant, AncestralTree *higherDescendant, int difference) {
    while(difference > 0) {
        lowerDescendant = lowerDescendant->ancestor;
        difference--;
    }
    while(lowerDescendant != higherDescendant) {
        lowerDescendant = lowerDescendant->ancestor;
        higherDescendant = higherDescendant->ancestor;
    }
    return lowerDescendant;
}

int getDepth(AncestralTree *topAncestor, AncestralTree *descendant) {
    int depth = 0;
    while(descendant != topAncestor) {
        descendant = descendant->ancestor;
        depth++;
    }
    return depth;
}

AncestralTree *getYoungestCommonAncestor(AncestralTree *topAncestor, AncestralTree *descendantOne, AncestralTree *descendantTwo) {
    int depth1 = getDepth(topAncestor, descendantOne);
    int depth2 = getDepth(topAncestor, descendantTwo);
    if(depth1 > depth2) {
        return getAncestor(descendantOne, descendantTwo, depth1 - depth2);
    } else {
        return getAncestor(descendantTwo, descendantOne, depth2 - depth1);
    }
}

void AncestralTree::addAsAncestor(const vector<AncestralTree *>& descendants) {
    for (AncestralTree *descendant : descendants) {
        descendant->ancestor = this;
    }
}

unordered_map<char, AncestralTree *> getAncestralTrees() {
    unordered_map<char, AncestralTree *> trees;
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (char a : alphabet) {
        trees.insert({a, new AncestralTree(a)});
    }
    return trees;
}

int main() {
    auto trees = getAncestralTrees();
    trees.at('A')->addAsAncestor({trees.at('B'), trees.at('C')});
    trees.at('B')->addAsAncestor({trees.at('D'), trees.at('E')});
    trees.at('D')->addAsAncestor({trees.at('H'), trees.at('I')});
    trees.at('C')->addAsAncestor({trees.at('F'), trees.at('G')});
    AncestralTree *YCA = getYoungestCommonAncestor(trees.at('A'), trees.at('E'), trees.at('I'));
    cout<< YCA->name;
    return 0;
}
