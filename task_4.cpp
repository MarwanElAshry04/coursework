#include <iostream>
using namespace std;

int towerOfHanoi_restricted(int n, char first, char middle, char last) {
    int moves = 0;

    if (n == 1) {
        cout << "Move disk " << n << " from " << first << " to " << middle << endl;
        cout << "Move disk " << n << " from " << middle << " to " << last << endl;
        moves += 2;
        return moves;
    }

    moves += towerOfHanoi_restricted(n - 1, first, middle, last);
    cout << "Move disk " << n << " from " << first << " to " << middle << endl;
    moves++;
    moves += towerOfHanoi_restricted(n - 1, last, middle, first);
    cout << "Move disk " << n << " from " << middle << " to " << last << endl;
    moves++;
    moves += towerOfHanoi_restricted(n - 1, first, middle, last);

    return moves;
}

int main() {
    int disks;
    cout << "Enter the number of disks: " << endl;
    cin >> disks;

    cout << "Moves for Twisted Tower of Hanoi:" << endl;

    int total_moves = towerOfHanoi_restricted(disks, 'A', 'B', 'C');

    cout << "Total number of moves: " << total_moves << endl;

    return 0;
}
