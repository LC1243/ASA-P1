#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>


int N, M; // Num linhas, N colunas
int combinacoes;
int max_square;

std::vector<int> lines_limits;
std::vector<std::vector<int>> grid;

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

// y -> line, x -> column
bool canBuildSquare(int y, int x, int size, std::vector<int> limites_linhas, std::vector<std::vector<int>> grid_){
    if(x < size - 1 || y < size - 1 || size > max_square)
        return false;

    //this if it's correct?
    if(x >= limites_linhas[y - size + 1])
        return false;

    for(int j = 0; j < size; j++){
        if(grid_[y][x-j] != 0)
            return false;
    }
    return true;
}

// Finished 
// x -> column, y -> line
std::vector<std::vector<int>> buildSquare(int x, int y, int size, std::vector<int> limites_linhas, std::vector<std::vector<int>> new_grid){
    
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            new_grid[y-i][x-j] += size;

    return new_grid;
}

// Finished 
std::vector<int> decreaseLimit(std::vector<std::vector<int>> grid_, std::vector<int> new_line_limits){


    for (unsigned int i = 0; i < grid_.size(); i++)
        if( std::all_of(grid_[i].begin(), grid_[i].end(), [](int j) { return j != 0; }) )
            new_line_limits[i] = 0;
               
    return new_line_limits;
}

// x -> column, y -> line
int solve(int x, int y, std::vector<int> limites_linhas, std::vector<std::vector<int>> grid_, int square_size) {
    std::vector<int> lims = limites_linhas;
    lims.erase(lims.cbegin());

    if (std::all_of(lims.cbegin(), lims.cend(), [](int i){ return i == 0; })){
        combinacoes++;
        return combinacoes;
    }

    if(square_size == 1 || canBuildSquare(y, x, square_size, limites_linhas, grid_ ) ) {

        std::vector<std::vector<int>> new_grid = 
        buildSquare(x, y, square_size, limites_linhas, grid_);

        std::vector<int> new_line_limits = 
        decreaseLimit(new_grid, limites_linhas);

    	// Get x and y coordinates
        int x1 = -1; 
        int y1 = -1;
        
        for(int i = new_grid.size() - 1; i >= 0; i--) {
            for(int j = new_grid[i].size() - 1; j >= 0; j--) {
                if(new_grid[i][j] == 0) {
                    y1 = i;
                    x1 = j;
                    break;
                }
            }
            if(y1 == i)
                break;
        }

        return solve(x,y, limites_linhas, grid_, square_size + 1) + solve(x1,y1, new_line_limits, new_grid, 1);
    }
   
    return 0;
}

void initiateGrid() {
    for (int i = 0; i < N; i++) {
        std::vector<int> v1;
        for (int j = 0; j < lines_limits[i]; j++) {
            v1.push_back(0);
        }
    grid.push_back(v1);
    }
    max_square = MaxSquare();
}

int main() {
    getInput();
    initiateGrid();

    if(N == 0 || M == 0) {
        std::cout << combinacoes << std::endl;
        return 0;
    }
    if (std::all_of(lines_limits.cbegin(), lines_limits.cend(), [](int i){ return i == 0; })){
        std::cout << combinacoes << std::endl;
        return 0;
    }
    solve(lines_limits[N-1] - 1, N-1, lines_limits, grid, 1);
    std::cout << combinacoes << std::endl;
    return 0;
}
