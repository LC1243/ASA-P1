#include <iostream>
#include <vector>

int N, M;

std::vector<int> lines_limits;

void getInput() {
    int c;
    std::cin >> N;
    std::cin >> M;
    for(int i = 0; i < N; i++) {
        std::cin >> c;
        lines_limits.push_back(c);
    }

}

int MaxSquare() {
    int diagonal = 0;
    int j = 0;
    int i = N;
    while( i  > 0 && j <= lines_limits[i-1]) {
        std::cout << lines_limits[i-1] << std::endl;
        diagonal++;
        i--;
        j++;
    }

    if(diagonal < N && diagonal < M) {
        return diagonal;
    } else if( N < diagonal && N < M) {
        return N;
    } else {
        return M;
    }
}
int main() {
    int x;
    getInput();
    x = MaxSquare();
    std::cout << x;
    return 0;
}