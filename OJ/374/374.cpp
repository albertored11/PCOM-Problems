#include <iostream>

using namespace std;

int potencia(int B, int P, int M) {

    if (P == 0)
        return 1;

    if (P == 1)
        return B;

    if (P % 2 == 0)
        return (potencia((B * B) % M, P / 2, M)) % M;

    return ((B % M) * potencia(B % M, P - 1, M)) % M;

}

bool resuelve() {

    int B;

    cin >> B;

    if (!cin)
        return false;

    int P, M;

    cin >> P >> M;

    cout << potencia(B % M, P, M) % M << '\n';

    return true;

}

int main() {

    while (resuelve());

    return 0;

}
