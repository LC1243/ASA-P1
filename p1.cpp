#include <iostream>
#include <vector>

int N, M;

std::vector<int> lines_limits;
std::vector<std::vector<int>> grid;

void initiateGrid() {
    for (int i = 0; i < N; i++) {
        std::vector<int> v1;
        for (int j = 0; j < lines_limits[i]; j++) {
            v1.push_back(0);
        }
    grid.push_back(v1);
    }

}

void displayGrid() {
    for(long unsigned int i = 0; i < grid.size(); i++) {
        for(long unsigned int j = 0; j < grid[i].size(); j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
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
    getInput();
    initiateGrid();
    displayGrid();
    return 0;
}