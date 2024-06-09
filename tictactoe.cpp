#include <iostream>
#include <vector>

using namespace std;

// Struct untuk menyimpan informasi gerakan
struct Gerakan {
    int baris;
    int kolom;
    Gerakan(int b, int k) : baris(b), kolom(k) {}
};

// Class untuk papan permainan Tic-Tac-Toe
class Papan {
private:
    // Pointer ke array 2D untuk menyimpan papan permainan
    char (*papan)[3];

public:
    // Konstruktor untuk menginisialisasi papan
    Papan() {
        papan = new char[3][3];  // Alokasi dinamis untuk array 2D
        resetPapan();
    }

    // Destruktor untuk menghapus alokasi dinamis
    ~Papan() {
        delete[] papan;
    }

    // Fungsi untuk mengatur ulang papan ke keadaan awal (semua kosong)
    void resetPapan() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                papan[i][j] = ' ';
    }

    // Fungsi untuk menampilkan papan permainan
    void tampilkanPapan() const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << papan[i][j];
                if (j < 2) cout << " | ";
            }
            cout << endl;
            if (i < 2) cout << "---------" << endl;
        }
    }

    // Fungsi untuk memeriksa apakah papan penuh
    bool papanPenuh() const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (papan[i][j] == ' ')
                    return false;
            }
        }
        return true;
    }

    // Fungsi untuk memeriksa apakah pemain tertentu menang
    bool cekKemenangan(char pemain) const {
        // Memeriksa baris
        for (int i = 0; i < 3; ++i) {
            if (papan[i][0] == pemain && papan[i][1] == pemain && papan[i][2] == pemain)
                return true;
        }
        // Memeriksa kolom
        for (int j = 0; j < 3; ++j) {
            if (papan[0][j] == pemain && papan[1][j] == pemain && papan[2][j] == pemain)
                return true;
        }
        // Memeriksa diagonal
        if (papan[0][0] == pemain && papan[1][1] == pemain && papan[2][2] == pemain)
            return true;
        if (papan[0][2] == pemain && papan[1][1] == pemain && papan[2][0] == pemain)
            return true;

        return false;
    }

    // Fungsi untuk mengatur posisi di papan
    bool setPosisi(int baris, int kolom, char pemain) {
        if (baris >= 0 && baris < 3 && kolom >= 0 && kolom < 3 && papan[baris][kolom] == ' ') {
            papan[baris][kolom] = pemain;
            return true;
        }
        return false;
    }
};

// Class untuk permainan Tic-Tac-Toe
class TicTacToe {
private:
    Papan* papan;  // Pointer ke objek papan
    char pemainSaatIni;  // Variabel untuk menyimpan pemain saat ini
    vector<Gerakan> riwayatGerakan;  // Vector untuk menyimpan riwayat gerakan

public:
    // Konstruktor untuk menginisialisasi permainan
    TicTacToe() {
        papan = new Papan();
        pemainSaatIni = 'X';
    }

    // Destruktor untuk menghapus alokasi dinamis
    ~TicTacToe() {
        delete papan;
    }

    // Fungsi untuk menjalankan logika utama permainan
    void mainkan() {
        bool gameSelesai = false;

        cout << "Selamat datang di permainan Tic-Tac-Toe!" << endl;

        // Loop utama permainan
        while (!gameSelesai) {
            papan->tampilkanPapan();
            int baris, kolom;

            // Meminta input dari pemain
            cout << "Pemain " << pemainSaatIni << ", masukkan baris (0, 1, atau 2): ";
            cin >> baris;
            cout << "Pemain " << pemainSaatIni << ", masukkan kolom (0, 1, atau 2): ";
            cin >> kolom;

            // Memeriksa apakah input valid dan tempat di papan kosong
            if (papan->setPosisi(baris, kolom, pemainSaatIni)) {
                riwayatGerakan.push_back(Gerakan(baris, kolom));  // Menyimpan gerakan

                // Memeriksa apakah pemain saat ini menang
                if (papan->cekKemenangan(pemainSaatIni)) {
                    papan->tampilkanPapan();
                    cout << "Pemain " << pemainSaatIni << " menang!" << endl;
                    gameSelesai = true;
                // Memeriksa apakah papan penuh
                } else if (papan->papanPenuh()) {
                    papan->tampilkanPapan();
                    cout << "Permainan seri!" << endl;
                    gameSelesai = true;
                } else {
                    // Mengganti pemain saat ini
                    pemainSaatIni = (pemainSaatIni == 'X') ? 'O' : 'X';
                }
            } else {
                cout << "Langkah tidak valid, coba lagi." << endl;
            }
        }
    }

    // Fungsi untuk menampilkan riwayat gerakan
    void tampilkanRiwayatGerakan() const {
        cout << "Riwayat Gerakan:" << endl;
        for (const auto& gerakan : riwayatGerakan) {
            cout << "(" << gerakan.baris << ", " << gerakan.kolom << ")" << endl;
        }
    }
};

// Fungsi utama untuk menjalankan program
int main() {
    // Membuat objek permainan TicTacToe
    TicTacToe game;
    // Memulai permainan
    game.mainkan();
    // Menampilkan riwayat gerakan
    game.tampilkanRiwayatGerakan();

    return 0;
}