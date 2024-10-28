#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

int EuclidAlgGCD(int a, int b);
int ExtendedEuclidAlgGCD(int a, int b, int &s, int &t);
int mod(int a, int n);
int RelativelyPrime(int n);
int inverse(int a, int n);
int Encode(int M, int e, int PQ);
int Decode(int C, int d, int PQ);
bool IsPrime(int n);

int main() {
    const int P = 3;
    const int Q = 7;
    int PQ = P * Q;

    // Step 2: Find e relatively prime to (P-1)(Q-1)
    int e = RelativelyPrime((P - 1) * (Q - 1));

    // Step 3: Calculate d as the inverse modulo (P-1)(Q-1) of e
    int d = inverse(e, (P - 1) * (Q - 1));

    cout << "e: " << e << endl;
    cout << "d: " << d << endl;

    int M;
    cout << "Enter an integer that is smaller than " << PQ << ": ";
    cin >> M;

    // Step 4: Encode M
    int C = Encode(M, e, PQ);

    // Step 5: Decode C
    int M1 = Decode(C, d, PQ);

    // Step 6: Verify that RSA algorithm works using assert
    assert(M == M1);

    cout << "Original message (M): " << M << endl;
    cout << "Encoded message (C): " << C << endl;
    cout << "Decoded message (M1): " << M1 << endl;

    return 0;
}

int EuclidAlgGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int ExtendedEuclidAlgGCD(int a, int b, int &s, int &t) {
    if (b == 0) {
        s = 1;
        t = 0;
        return a;
    } else {
        int s_prev, t_prev;
        int gcd = ExtendedEuclidAlgGCD(b, a % b, s_prev, t_prev);
        s = t_prev;
        t = s_prev - (a / b) * t_prev;
        return gcd;
    }
}

int mod(int a, int n) {
    int result = a % n;
    if (result < 0)
        result += n;
    return result;
}

int RelativelyPrime(int n) {
    for (int i = 2; i < n; ++i) {
        if (EuclidAlgGCD(n, i) == 1)
            return i;
    }
    return -1; // Not found
}

int inverse(int a, int n) {
    int s, t;
    int d = ExtendedEuclidAlgGCD(a, n, s, t);
    if (d == 1) {
        s = mod(s, n);
        if (s < 0)
            s += n;
        return s;
    } else {
        cout << "a and n are not relatively prime!" << endl;
        return -1;
    }
}

int Encode(int M, int e, int PQ) {
    int result = 1;
    for (int i = 0; i < e; ++i) {
        result = mod(result * M, PQ);
    }
    return result;
}

int Decode(int C, int d, int PQ) {
    int result = 1;
    for (int i = 0; i < d; ++i) {
        result = mod(result * C, PQ);
    }
    return result;
}

bool IsPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

