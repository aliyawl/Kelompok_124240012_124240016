#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Barang {
    string kode;
    string nama;
    int stok;
};

struct Node {
    Barang data;
    Node* next;
    Node* prev;
};

Node* head = nullptr;
Node* tail = nullptr;

void tambahBarang(string kode, string nama, int stok) {
    Node* newNode = new Node;
    newNode->data.kode = kode;
    newNode->data.nama = nama;
    newNode->data.stok = stok;
    newNode->next = nullptr;
    newNode->prev = tail;

    if (tail != nullptr) {
        tail->next = newNode;
    } else {
        head = newNode;
    }
    tail = newNode;
}

void tampilBarang() {
    Node* temp = head;
    if (temp == nullptr) {
        cout << "Belum ada data barang.\n";
        return;
    }

    cout << "\n=== DAFTAR SEMUA BARANG ===\n";
    cout << left 
         << setw(5)  << "No" 
         << setw(15) << "Kode" 
         << setw(25) << "Nama" 
         << setw(10) << "Stok" << endl;
    cout << string(55, '-') << endl;

    int no = 1;
    while (temp != nullptr) {
        cout << left 
             << setw(5)  << no 
             << setw(15) << temp->data.kode 
             << setw(25) << temp->data.nama 
             << setw(10) << temp->data.stok << endl;
        temp = temp->next;
        no++;
    }
}


void cariBarang(string nama) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.nama == nama) {
            cout << "Barang ditemukan: "
                 << "Kode: " << temp->data.kode
                 << ", Nama: " << temp->data.nama
                 << ", Stok: " << temp->data.stok << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Barang dengan nama \"" << nama << "\" tidak ditemukan." << endl;
}

void urutkanBarang() {
    if (head == nullptr) return;
    bool swapped;
    do {
        swapped = false;
        Node* temp = head;
        while (temp->next != nullptr) {
            if (temp->data.stok > temp->next->data.stok) {
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
}

void updateBarang(string kode, int stok) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.kode == kode) {
            temp->data.stok = stok;
            cout << "Jumlah barang dengan kode " << kode << " telah diperbarui menjadi " << stok << "." << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Barang dengan kode " << kode << " tidak ditemukan." << endl;
}

void simpankeFile() {
    ofstream file("barang.txt");
    if (file.is_open()) {
        Node* temp = head;
        while (temp != nullptr) {
            file << temp->data.kode << "," 
                 << temp->data.nama << "," 
                 << temp->data.stok << endl;
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

    do {
        cout << "\n=== MENU INVENTARIS BARANG GUDANG ===" << endl;
        cout << "1. Tambah Barang" << endl;
        cout << "2. Tampilkan Semua Barang" << endl;
        cout << "3. Cari Barang" << endl;
        cout << "4. Urutkan Barang Berdasarkan Stok" << endl;
        cout << "5. Hapus Barang" << endl;
        cout << "6. Update Jumlah Stok Barang" << endl;
        cout << "7. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        string kode, nama;
        int stok;

        switch(pilihan) {
            case 1: {
                int jumlahBarang;
                cout << "Berapa banyak barang yang ingin ditambahkan?: ";
                cin >> jumlahBarang;
                cin.ignore();

                for (int i = 0; i < jumlahBarang; i++) {
                    cout << "\nBarang ke-" << (i + 1) << endl;
                    cout << "Masukkan kode barang: ";
                    getline(cin, kode);
                    cout << "Masukkan nama barang: ";
                    getline(cin, nama);
                    cout << "Masukkan jumlah stok: ";
                    cin >> stok;
                    cin.ignore();
                    tambahBarang(kode, nama, stok);
                }
                simpankeFile();
                break;
            }
            case 2:
                tampilBarang();
                break;
            case 3:
                cout << "Masukkan nama barang yang dicari: ";
                getline(cin, nama);
                cariBarang(nama);
                break;
            case 4:
                urutkanBarang();
                tampilBarang();
                break;
            case 5:
                cout << "Masukkan kode barang yang ingin dihapus: ";
                getline(cin, kode);
                hapusBarang(kode);
                simpankeFile();
                break;
            case 6:
                cout << "Masukkan kode barang yang ingin diupdate: ";
                getline(cin, kode);
                cout << "Masukkan jumlah stok baru: ";
                cin >> stok;
                cin.ignore();
                updateBarang(kode, stok);
                simpankeFile();
                break;
            case 7:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }

    } while (pilihan != 7);

    return 0;
}
