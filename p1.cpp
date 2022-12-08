#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int N, M; // Num linhas, N colunas
int combinacoes;

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
    while( i  > 0 && j < lines_limits[i-1]) {
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

bool canBuildSquare(int x, int y, int size, std::vector<std::vector<int>> grid_){
    if(x + 1 == size || y+1 == size || size > MaxSquare() )
        return false;

    if(x > lines_limits[y - size])
        return false;

    return true;
}

// Finished 
std::vector<std::vector<int>> buildSquare(int x, int y, int size, std::vector<int> limites_linhas, std::vector<std::vector<int>> grid_){
    std::vector<std::vector<int>> new_grid = grid_;
    
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            grid_[x-i][j-i]++;

    return grid_;
}

// Finished 
std::vector<int> decreaseLimit(std::vector<int> limites_linhas, int size){
    int cont = 0;

    for (auto it = limites_linhas.rbegin(); it != limites_linhas.rend(); it++){
        if(cont < size && *it != 0){
            it -= size;
            cont++;
        }
        else
            return limites_linhas;
    }
    return limites_linhas;
}


void solve(int x, int y, std::vector<int> limites_linhas, std::vector<std::vector<int>> grid_){

    if ( std::adjacent_find( limites_linhas.begin(), limites_linhas.end(), std::not_equal_to<int>() ) == limites_linhas.end() ){
        combinacoes++;
        return;
    }

    if(x > limites_linhas[y])
        solve(x-1, y, limites_linhas, grid_);

    //Corpo da função

    if(1){

    }

    //

    if(!x){
        if(y)
            solve(limites_linhas[y - 1] - 1, y -1, limites_linhas, grid_);
    }
    else
        solve(x-1, y, limites_linhas, grid_);
}

int main() {
    getInput();
    initiateGrid();
    displayGrid();
    return 0;
}