#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include<unistd.h>

int N, M; // Num linhas, N colunas
int combinacoes;
int max_square;

std::vector<int> lines_limits;
std::vector<std::vector<int>> grid;
std::vector<std::vector<int>> columns_configs;

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

    /*for(int j = 0; j < size; j++){
        if(grid_[y][x-j] != 0)
            return false;
    }*/
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
std::vector<int> decreaseLimit(int size, std::vector<int> new_line_limits){
    int cont = 0;

    for (int i = new_line_limits.size() - 1; i >= 0; i--){
        if(cont < size && new_line_limits[i] != 0){
            new_line_limits[i] -= size;
            cont++;
        }
    }
               
    return new_line_limits;
}

//note the const
void display_vector(const std::vector<int> &v)
{
    std::copy(v.begin(), v.end(),
        std::ostream_iterator<int>(std::cout, " "));
}

// x -> column, y -> line
int solve(int x, int y, std::vector<int> limites_linhas, std::vector<std::vector<int>> grid_, int square_size) {
    std::vector<int> lims = limites_linhas;
    lims.erase(lims.cbegin());
    int x2 = 0;
    int y2 = 0;
    if (std::all_of(lims.cbegin(), lims.cend(), [](int i){ return i == 0; })){
        combinacoes++;
        return combinacoes;
    }

    if(square_size == 1 || canBuildSquare(y, x, square_size, limites_linhas, grid_ ) ) {

        std::vector<std::vector<int>> new_grid = 
        buildSquare(x, y, square_size, limites_linhas, grid_);

        std::vector<int> new_line_limits = 
        decreaseLimit(square_size, limites_linhas);

        columns_configs.push_back(new_line_limits);
        displayGrid(new_grid);
        sleep(1);
        std::cout << std::endl;
        display_vector(new_line_limits);
        std::cout << std::endl;

        /*if(y == 0) {
            y2  = N - square_size;
            x2  = x - square_size;
        } else {
            y2 = y - square_size;
            x2 = x;
        }*/

        
        for(unsigned int i = 0; i < columns_configs.size(); i++) {
            if(columns_configs[i] == lines_limits) {
                combinacoes++;
                return combinacoes;
            }
        }

        return solve(x,y, limites_linhas, grid_, square_size + 1) + solve(x2,y2, new_line_limits, new_grid, 1);
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
