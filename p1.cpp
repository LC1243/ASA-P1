#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <unistd.h>
int N, M; // Num linhas, N colunas
int combinacoes;

std::vector<int> lines_limits;
std::vector<std::vector<long int>> square_sizes;
std::vector<std::vector<int>> grid;

void initiateGrid() {
    for (int i = 0; i < N; i++) {
        std::vector<int> v1;
        std::vector<long int>v2;
        for (int j = 0; j < lines_limits[i]; j++) {
            v1.push_back(0);
            v2.push_back(0);
        }
    grid.push_back(v1);
    square_sizes.push_back(v2);
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

void storeSquareSize(int y, int x, int size) {
    square_sizes[y][x] = square_sizes[y][x] * 10 + size;
}

bool squareSizeUsed(int y, int x, int digit) {
    std::string digit_str = std::to_string(digit);
    std::string number_str = std::to_string(square_sizes[y][x]);
    if (std::string::npos != number_str.find_first_of(digit_str)) {
        return true;
    }
    return false;

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
    if(x < size - 1 || y < size - 1 || size > MaxSquare() )
        return false;

    //this if it's correct?
    if(x >= limites_linhas[y - size + 1])
        return false;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(grid_[y-i][x-j] != 0)
                return false;
        }
    }
    return true;
}

// Finished 
// x -> column, y -> line
std::vector<std::vector<int>> buildSquare(int x, int y, int size, std::vector<int> limites_linhas, std::vector<std::vector<int>> grid_){
    std::vector<std::vector<int>> new_grid = grid_;
    
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            new_grid[y-i][x-j] += size;

    return new_grid;
}

// Finished 
std::vector<int> decreaseLimit(std::vector<std::vector<int>> grid_, std::vector<int> limites_linhas){

    std::vector<int> new_line_limits = limites_linhas;

    for (unsigned int i = 0; i < grid_.size(); i++)
        if( std::all_of(grid_[i].begin(), grid_[i].end(), [](int j) { return j != 0; }) )
            new_line_limits[i] = 0;
               
    return new_line_limits;
}

/* Falta mudar as coordenadas do ponto após a recursão*/

// returns the x coordinate of the next point where recursion starts
// grid[y][x]
// y is the line 
int getYposition(std::vector<std::vector<int>> grids) {
    for(int i = grids.size() - 1; i >= 0; i--) {
        for(int j = grids[i].size() - 1; j >= 0; j--) {
            if(grids[i][j] == 0) {
                return i;
            }
        }
    }
    return 0;
}

//x is the column
int getXposition(std::vector<std::vector<int>> grids) {
    for(int i = grids.size() - 1; i >= 0; i--) {
        for(int j = grids[i].size() - 1; j >= 0; j--) {
            if(grids[i][j] == 0) {
                return j;
            }
        }
    }
    return 0;
}

// x -> column, y -> line
int solve(int x, int y, std::vector<int> limites_linhas, std::vector<std::vector<int>> grid_, int square_size) {
   
    if (std::all_of(limites_linhas.cbegin(), limites_linhas.cend(), [](int i){ return i == 0; })){
        combinacoes++;
        return combinacoes;
    }

    /* Penso que não é preciso porque a grid só tem os pontos onde pode haver quadrados
    if(x > limites_linhas[y-1])
        solve(x-1, y, limites_linhas, grid_);
    */
    if(canBuildSquare(y, x, square_size, limites_linhas, grid_ ) /*&& 
            squareSizeUsed(y, x, (square_size)) ==  false */) {

            std::vector<std::vector<int>> new_grid = 
            buildSquare(x, y, square_size, limites_linhas, grid_);

            storeSquareSize(y, x, square_size);

            std::vector<int> new_line_limits = 
            decreaseLimit(new_grid, limites_linhas);
      
        int x1 = getXposition(new_grid);
        int y1 = getYposition(new_grid);
        //std::cout << y1 << " " << x1 << std::endl;
        // get x and y position for next call 
        // generates infinite recursion

        return solve(x,y, limites_linhas, grid_, square_size + 1) + solve(x1,y1, new_line_limits, new_grid, 1);
     
        }
        //i++;
    //}
    /*
    if(grid_[y][x] + 1 != 1 && canBuildSquare(y, x, grid_[y][x] + 1, grid_ )) {
        
        std::vector<std::vector<int>> new_grid = 
        buildSquare(x, y, grid_[y][x] + 1, limites_linhas, grid_);

        storeSquareSize(y, x, grid_[y][x] + 1);
        
        std::vector<int> new_line_limits = 
        decreaseLimit(limites_linhas, grid_[y][x] + 1);
            
        //shows output for debugging
        std::cout << "line limits: ";
        for (const int& i : new_line_limits) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        displayGrid(new_grid);

        int x1 = getXposition(new_grid);
        int y1 = getYposition(new_grid);
        return solve(x1,y1,new_line_limits, new_grid);

    }
    */
    /*
    else
        solve(x-1, y, limites_linhas, grid_);
    */
    return 0;
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