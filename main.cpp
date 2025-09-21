#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <windows.h> // for sleep
using namespace std;

char board[4][4]; // เก็บตัวอักษรจริง (ซ่อนอยู่)
char display[4][4]; // แสดงให้น้องดู (มี * หรืออักษร)
bool matched[4][4]; // จำว่าจับคู่ได้หรือยัง

void initBoard() {
    char letters[] = { 'A','A','B','B','C','C','D','D',
    'E','E','F','F','G','G','H','H' };

    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < 16; i++) {
        int r = rand() % 16;
        swap(letters[i], letters[r]);
    }

    int k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = letters[k++];
            display[i][j] = '*';
            matched[i][j] = false;
        }
    }
}

void drawBoard() {
    cout << "   0 1 2 3\n";
    for (int i = 0; i < 4; i++) {
        cout << i << "  ";
        for (int j = 0; j < 4; j++) {
            cout << display[i][j] << " ";
        }
        cout << endl;
    }
}

void getChoice(int& row, int& col) {
    string input;
    while (true) {
        cout << "Enter the row and column (eg 1 2):";
        getline(cin, input); // รับข้อมูลเป็นข้อความ

        stringstream ss(input); // สร้าง stream เพื่อแยกคำ
        if ((ss >> row >> col) && ss.eof()) { // ถ้าแยกได้ 2 ค่า และไม่มีค่าขยะเหลือ
            if (row >= 0 && row < 4 && col >= 0 && col < 4 && !matched[row][col]) {
                break;
            }
            else {
                cout << "❗ This channel is invalid or exceeds its limit.\n";
            }
        }
        else {
            cout << "❗ Invalid data format. Please enter only two numbers, e.g. : 1 2\n";
        }
    }
}

int main() {
    int matchedPairs = 0; // นับจำนวนคู่ที่จับได้
    int turns = 0;        // ✅ ตัวแปรนับรอบ

    initBoard();

    while (matchedPairs < 8) {
        drawBoard();

        int r1, c1, r2, c2;
        cout << "Pick first card:\n";
        getChoice(r1, c1);
        display[r1][c1] = board[r1][c1]; // แสดงค่าจริง

        drawBoard();

        cout << "Pick second card:\n";
        getChoice(r2, c2);
        display[r2][c2] = board[r2][c2]; // แสดงค่าจริง

        drawBoard(); // แสดงกระดานอีกรอบให้เห็น 2 ช่อง

        turns++; // ✅ เพิ่มรอบเมื่อเลือกครบ 2 ใบ

        if (board[r1][c1] == board[r2][c2] && !(r1 == r2 && c1 == c2)) {
            cout << "✅ Matched!\n";
            matched[r1][c1] = matched[r2][c2] = true;
            matchedPairs++; // ✅ เพิ่มจำนวนคู่ที่สำเร็จ
        }
        else {
            cout << "❌ Not matched...\n";
            Sleep(1500); // หน่วงเวลา 1500 มิลลิวินาที = 1.5 วินาที
            display[r1][c1] = display[r2][c2] = '*';
            display[r2][c2] = '*';
        }
        Sleep(500); // เว้นเล็กน้อยก่อนรอบใหม่
    }

    // GAME END
    cout << "---------------------------------------------\n";
    cout << "🎉 You matched all pairs successfully!\n";
    cout << "📌 Total turns used: " << turns << endl; // ✅ แสดงจำนวนรอบ
    system("pause");

    return 0;
}
