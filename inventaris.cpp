#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Barang {
    string kode;
    string nama;
    int jumlah;
};

struct Node {
    Barang data;
    Node* next;
    Node* prev;
};

Node* head = nullptr;
Node* tail = nullptr;

void tambahBarang(string kode, string nama, int jumlah) {
    Node* newNode = new Node;
    newNode->data.kode = kode;
    newNode->data.nama = nama;
    newNode->data.jumlah = jumlah;
    newNode->next = nullptr;
    newNode->prev = tail;

    if (tail != nullptr) {
        tail->next = newNode;
    } else {
        head = newNode;
    }
    tail = newNode;
    simpankeFile();
}

void tampilBarang() {
    Node* temp = head;
    cout << "Daftar Barang:" << endl;
    while (temp != nullptr) {
        cout << "Kode: " << temp->data.kode
             << ", Nama: " << temp->data.nama
             << ", Jumlah: " << temp->data.jumlah << endl;
        temp = temp->next;
    }
}

void cariBarang(string nama) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.nama == nama) {
            cout << "Barang ditemukan: "
                 << "Kode: " << temp->data.kode
                 << ", Nama: " << temp->data.nama
                 << ", Jumlah: " << temp->data.jumlah << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Barang dengan " << nama << " tidak ditemukan." << endl;
}

void urutkanBarang() {
    if (head == nullptr) return;
    bool swapped;
    do {
        swapped = false;
        Node* temp = head;
        while (temp->next != nullptr) {
            if (temp->data.kode > temp->next->data.kode) {
                swap(temp->data, temp->next->data);
                swapped = true;
            }
            temp = temp->next;
        }
    } while (swapped);
}

void hapusBarang(string kode) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.kode == kode) {
            if (temp->prev != nullptr) {
                temp->prev->next = temp->next;
            } else {
                head = temp->next;
            }
            if (temp->next != nullptr) {
                temp->next->prev = temp->prev;
            } else {
                tail = temp->prev;
            }
            delete temp;
            cout << "Barang dengan kode " << kode << " telah dihapus." << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Barang dengan kode " << kode << " tidak ditemukan." << endl;
    simpankeFile();
    tampilBarang();
}

void updateBarang(string kode, int jumlah) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.kode == kode) {
            temp->data.jumlah = jumlah;
            cout << "Jumlah barang dengan kode " << kode << " telah diperbarui menjadi " << jumlah << "." << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Barang dengan kode " << kode << " tidak ditemukan." << endl;
    simpankeFile();
}

void simpankeFile() {
    ofstream file("barang.txt");
    if (file.is_open()) {
        Node* temp = head;
        while (temp != nullptr) {
            file << temp->data.kode << "," 
                 << temp->data.nama << "," 
                 << temp->data.jumlah << endl;
            temp = temp->next;
        }
        file.close();
    } else {
        cout << "Tidak dapat membuka file untuk menyimpan data." << endl;
    }
}

void bacadariFile() {
    ifstream file("barang.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            string kode = line.substr(0, pos1);
            string nama = line.substr(pos1 + 1, pos2 - pos1 - 1);
            int jumlah = stoi(line.substr(pos2 + 1));
            tambahBarang(kode, nama, jumlah);
        }
        file.close();
    } else {
        cout << "Tidak dapat membuka file untuk membaca data." << endl;
    }
}

int main () {
    bacadariFile();
    int pilihan;
}