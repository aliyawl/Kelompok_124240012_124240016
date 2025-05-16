#include <iostream>
#include <string>
using namespace std;

struct Barang {
    string kode;
    string nama;
    int jumlah;
};

struct Node {
    Barang data;
    Node* next;
};

Node* head = nullptr;
Node* tail = nullptr;
