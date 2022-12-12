#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include<unistd.h>

int N, M; // Num linhas, N colunas
long long int combinacoes;
int max_square;

std::vector<int> lines_limits;
std::vector<std::vector<int>> columns_configs;
std::vector<long long int> memos;

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
bool canBuildSquare(int y, int x, int size, std::vector<int> limites_linhas){
    if(x < size - 1 || y < size - 1 || size > max_square)
        return false;

    //this if it's correct?
    if(x >= limites_linhas[y - size + 1])
        return false;

    return true;
}

std::vector<int> decreaseLimit(int start_index, int size, std::vector<int> new_line_limits){
    int cont = 0;

    for (int i = start_index; i >= 0; i--){
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
    std::cout << "\n";
}

// x -> column, y -> line
long long int solve(int x, int y, std::vector<int> limites_linhas, int square_size) {
    std::vector<int> lims = limites_linhas;
    lims.erase(lims.begin());
    int x2 = 0;
    int y2 = 0;

    if (std::all_of(lims.cbegin(), lims.cend(), [](int i){ return i <= 1; }))
        return 1;
    

    if(square_size == 1 || canBuildSquare(y, x, square_size, limites_linhas) ) {

        std::vector<int> new_line_limits = 
        decreaseLimit(y, square_size, limites_linhas);

        int last = new_line_limits.back();
        int index = N - 1;

        
        for(int i = N - 2; i >= 0; i--){
            if(new_line_limits[i] > last){
                last = new_line_limits[i];
                index = i;
            }
        }
        x2 = last - 1;
        y2 = index;


        long long int combs_new = -1;
        long long int combs_same;
        
        for(unsigned int i = 0; i < columns_configs.size(); i++) {
            if(std::equal(new_line_limits.begin(), new_line_limits.end(), columns_configs[i].begin()) ) {
                combs_new = memos[i];    
                printf("%lld\n", memos[i]);       
                break;
            } 
        }     
        
        if(combs_new == -1){
            std::vector<int> lims_new;
            
            combs_new = solve(x2,y2, new_line_limits, 1);
            
            columns_configs.push_back(new_line_limits);
            memos.push_back(combs_new);
        }
        combs_same = solve(x,y, limites_linhas, square_size + 1);

        return combs_new + combs_same;
    }
   
    return 0;
}

int main() {
    getInput();
    max_square = MaxSquare();
    if(N == 0 || M == 0) {
        std::cout << combinacoes << std::endl;
        return 0;
    }
    if (std::all_of(lines_limits.cbegin(), lines_limits.cend(), [](int i){ return i == 0; })){
        std::cout << combinacoes << std::endl;
        return 0;
    }
    combinacoes = solve(lines_limits[N-1] - 1, N-1, lines_limits, 1);
    std::cout << combinacoes << std::endl;
    return 0;
}
