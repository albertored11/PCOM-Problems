#include <iostream>
#include <vector>
#include <string>

using namespace std;

int nCaso = 1;

class FenwickTree {

    vector<int> ft;

    public:

        FenwickTree(int n) {
            ft.assign(n + 1, 0);
        }

        int getSum(int b) {

            int ret = 0;

            while (b) {
                ret += ft[b];
                b -= (b & -b);
            }

            return ret;

        }

        void add(int pos, int val) {

            while (pos < ft.size()) {
                ft[pos] += val;
                pos += (pos & -pos);
            }

        }

        int getSum(int a, int b) {

            return getSum(b) - getSum(a - 1);

        }

        int getValue(int pos) {

            return getSum(pos) - getSum(pos - 1);

        }

        void setValue(int pos, int val) {

            add(pos, val - getValue(pos));

        }

};

bool resuelve() {

    int N;

    cin >> N;

    if (N == 0)
        return false;

    FenwickTree f(N);

    for (int i = 1; i <= N; ++i) {

        int pot;

        cin >> pot;

        f.setValue(i, pot);

    }

    if (nCaso != 1)
        cout << '\n';

    cout << "Case " << nCaso << ":\n";

    string operation;

    cin >> operation;

    while (operation != "END") {

        int a, b;

        cin >> a >> b;

        if (operation == "S")
            f.setValue(a, b);
        else
            cout << f.getSum(a, b) << '\n';

        cin >> operation;

    }

    return true;

}

int main() {

    while (resuelve()) ++nCaso;

    return 0;

}
