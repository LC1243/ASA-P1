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

void displayGrid(std::vector<std::vector<int>> grid_) {
    for(long unsigned int i = 0; i < grid_.size(); i++) {
        for(long unsigned int j = 0; j < grid_[i].size(); j++) {
            std::cout << grid_[i][j] << " ";
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

/* Falta mudar as coordenadas do ponto após a recursão*/
// returns the x coordinate of the next point where recursion starts
// grid[x][y]
int getXposition(std::vector<std::vector<int>> grid_) {
    for(long unsigned int i = grid_.size(); i > 0; i--) {
        for(long unsigned int j = grid_[i].size(); j > 0; j--) {
            if(grid_[i][j] == 0)
                return i;
        }
    }
    return 0;
}

int getYposition(std::vector<std::vector<int>> grid_) {
    for(long unsigned int i = grid_.size(); i > 0; i--) {
        for(long unsigned int j = grid_[i].size(); j > 0; j--) {
            if(grid_[i][j] == 0)
                return j;
        }
    }
    return 0;
}

int solve(int x, int y, std::vector<int> limites_linhas, std::vector<std::vector<int>> grid_){

    if (std::all_of(limites_linhas.cbegin(), limites_linhas.cend(), [](int i){ return i == 0; })){
        combinacoes++;
        return combinacoes;
    }

    if(x > limites_linhas[y])
        solve(x-1, y, limites_linhas, grid_);

    //Corpo da função
    if(canBuildSquare(x, y, grid_[x][y] + 1, grid_ ) ) {
        std::vector<std::vector<int>> new_grid_ = 
        buildSquare(x, y, grid_[x][y] + 1, limites_linhas, grid_);
        std::vector<int> new_line_limits = 
        decreaseLimit(limites_linhas, grid_[x][y] + 1);
        return solve(x,y, limites_linhas, grid_) + solve(x,y, new_line_limits, new_grid_);
    }
    return solve(x,y, limites_linhas, grid_);

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
    displayGrid(grid);
    solve(M-1, N-1, lines_limits, grid);
    std::cout << combinacoes << std::endl;
    return 0;
}