#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

using ii = pair <int,int>;
using iii = pair <int,ii>;
const int MAX_TAM = 1000;
bool visitedJOE[MAX_TAM][MAX_TAM];
bool visitedFIRE[MAX_TAM][MAX_TAM];


int f_mov [] = {-1, 0, 1, 0};
int c_mov [] = {0, 1, 0, -1};

bool inBounds (int f, int c, ii square) {
    return square.first >= 0 && square.first < f && square.second >= 0 && square.second < c;
}

void resuelve() {

    int f, c;

    cin >> f >> c;

    memset(visitedJOE, 0, sizeof(visitedJOE));    
    memset(visitedFIRE, 0, sizeof(visitedFIRE));
    queue<iii> joe;
    queue<iii> fire;
    bool fin = false;

    for (int i = 0; i < f; ++i)
        for (int j = 0; i < c; ++j){
            char square;
            cin >> square;

            if (square == '#') {
                visitedJOE[i][j] = true;
                visitedFIRE[i][j] = true;
            }
            else if (square == 'F') {
                visitedJOE[i][j] = true;
                visitedFIRE[i][j] = true;
                fire.push({0, {i, j}});
            }
            else if (square == 'J') {
                visitedJOE[i][j] = true;
                joe.push({0, {i, j}});
            }

        }
    


    while (!joe.empty()) {
       

        if(!fire.empty()) {

            int dist = fire.front().first;

            while(fire.front().first == dist) {
                iii fuego = fire.front();
                for (int i = 0; i < 4 ; ++i) {
                    ii next;
                    next.first = fuego.second.first + f_mov[i];
                    next.second = fuego.second.second + c_mov[i];
                    if(inBounds(f, c, next) && !visitedFIRE[next.first][next.second]) {
                        visitedFIRE[next.first][next.second] = true;
                        visitedJOE[next.first][next.second] = true;
                        fire.push({dist + 1, next});
                    }
                }
                fire.pop();
            }
        }

        int dist = joe.front().first;

        while(joe.front().first == dist) {
            iii joeS = joe.front();
            for(int i = 0; i < 4; ++i) {
                ii next;
                next.first = joeS.second.first + f_mov[i];
                next.second = joeS.second.second + c_mov[i];
                if (!inBounds(f, c, next)) {
                    cout << dist + 1 << '\n';
                    return;
                }
                else if(!visitedJOE[next.first][next.second]) {
                    visitedFIRE[next.first][next.second] = true;
                    visitedJOE[next.first][next.second] = true;
                    fire.push({dist + 1, next});
                }
            }  
            joe.pop();
        }
    }
    cout << "IMPOSSIBLE\n";    
}



int main() {

    int nCasos;

    cin >> nCasos;

    while(nCasos--)resuelve();

    return 0;
}
