#include <iostream>
#include <cmath>

using namespace std;

// Hàm tính (base^exp) % mod bằng thuật toán lũy thừa nhanh
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return res;
}

// Hàm tìm nghịch đảo modulo bằng định lý Fermat nhỏ (vì q là số nguyên tố)
// Công thức: a^(q-2) % q
long long modInverse(long long n, long long q) {
    return power(n, q - 2, q);
}

int main() {
    long long q, a, xA, k, M;

    // Nhập dữ liệu đầu vào
    cout << "--- Nhập thông số hệ thống ---" << endl;
    cout << "Nhập số nguyên tố q: "; cin >> q;
    cout << "Nhập căn nguyên thủy a: "; cin >> a;
    cout << "Nhập khóa bí mật của An (xA < q-1): "; cin >> xA;
    cout << "Nhập số ngẫu nhiên k (để Ba mã hóa): "; cin >> k;
    cout << "Nhập thông điệp M (M < q): "; cin >> M;

    // --- a) Tạo khóa công khai PU ---
    // Công thức: YA = a^xA mod q
    long long YA = power(a, xA, q);
    cout << "\n[a] Khóa công khai của An: PU = {" << q << ", " << a << ", " << YA << "}" << endl;

    // --- b) Ba mã hóa thông điệp M ---
    // Công thức: C1 = a^k mod q
    //            K = (YA^k) mod q
    //            C2 = (K * M) mod q
    long long C1 = power(a, k, q);
    long long K_mahoa = power(YA, k, q);
    long long C2 = (K_mahoa * M) % q;
    
    cout << "[b] Ba mã hóa M, bản mã thu được là: (C1, C2) = (" << C1 << ", " << C2 << ")" << endl;

    // --- c) An giải bản mã (C1, C2) ---
    // Công thức: K = (C1^xA) mod q
    //            M = (C2 * K^-1) mod q
    long long K_giaima = power(C1, xA, q);
    long long K_nghichdao = modInverse(K_giaima, q);
    long long M_giaima = (C2 * K_nghichdao) % q;

    cout << "[c] An giải mã bản mã (C1, C2) được M = " << M_giaima << endl;

    return 0;
}