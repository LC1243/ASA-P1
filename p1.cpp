#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <map>

int N, M; // Num linhas, N colunas
long long unsigned int combinacoes;
int max_square;

std::vector<int> lines_limits;

// Key, value
std::map<long long unsigned int, long long unsigned int> tree_map;


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

long long  unsigned int hash_function(std::vector<int> vec){
    long long unsigned int result = 0;
    std::hash<long long unsigned int> vector_hash;
    for (auto d : vec)
        result = result * 10 + d;

    return vector_hash(result);

}

// x -> column, y -> line
long long unsigned int solve(int x, int y, std::vector<int> limites_linhas, int square_size) {
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

        // Procura no Map (ou inserção)
        long long unsigned int combs_new;
        long long unsigned int combs_same;

        long long unsigned int key = hash_function(new_line_limits);

        if(tree_map.find(key)!=tree_map.end()){
            combs_new = tree_map[key];
        }
        else{
            combs_new = solve(x2,y2, new_line_limits, 1);

            tree_map.insert({key, combs_new});
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
