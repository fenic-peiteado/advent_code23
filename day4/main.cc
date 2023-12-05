#include <bits/stdc++.h>

typedef std::vector<std::vector<char>> vi_c;
typedef std::vector<char> li_c;
typedef std::vector<bool> li_b;
typedef std::vector<std::vector<bool>> vi_b;
typedef std::pair<int, int> pa;
void print_map(vi_c mapa) {
  for (auto i : mapa) {
    for (auto j : i) {
      std::cout << j;
    }
    std::cout << std::endl;
  }
}

std::vector<std::pair<int, int>> mov_8{{1, 1}, {-1, 1}, {1, -1}, {-1, -1},
                                     {0, 1}, {1, 0},  {0, -1}, {-1, 0}};
std::vector<std::pair<int,int>> mov_4{{0, 1}, {1, 0},  {0, -1}, {-1, 0}};
    
void fun(){

}

int main(){
    std::string line;
    long long sum = 0;
    int linea_num = 1;
    int sum2 =0;
    std::vector<int> valores(400,1);  // Este vector se utiliza como acumulador para la segunda parte
    while(std::getline(std::cin,line)){
    long long num = 0;
    int contador =0;
        std::set<int> conjunto;
        std::regex patron(":.+");
         std::smatch match;
        std::regex_search(line,match,patron);
        std::string line2 = match[0].str();
        std::regex patron1(".+\\|");
        std::regex patron2("(\\d)+");
        std::regex_search(line2,match,patron1);
        std::string line3 = match[0].str();
        std::sregex_iterator it (line3.begin(),line3.end(),patron2);
        std::sregex_iterator end;
        // primera mita
        while(it != end){
            std::smatch match2 = *it;
            std::cout << match2[0].str() << " ";
            conjunto.insert(stoi(match2[0].str()));
            it++;
        }
        //segunda mitad
        std::regex patron3("\\|.+");
        std::regex_search(line2,match,patron3);
        std::string line5 = match[0].str();
        std::sregex_iterator it2 (line5.begin(),line5.end(),patron2);
        bool find = false;
        while(it2 != end){
        std::smatch match2 = *it2;
        if(conjunto.count(stoi(match2[0].str()))){
            contador++;
            if(find){
            num=num*2;
            }else{
                num=1;
            find =true;            
            }
        }
        it2++;
        }
        if(!find){
            num =0;
        }{
            for(int i = linea_num+1; i <= linea_num+contador;i++){
                valores[i] = valores[i] + valores[linea_num];
            }
            sum2+= valores[linea_num];
        }
        std::cout << "Potencia 2" << num << "\n";
        std::cout << "Copias" << valores[linea_num] << "\n";
        linea_num++;
        sum+=num;
    }
    std::cout << "\n Suma1 "<< sum << "\n";
    std::cout << "\n Suma2 "<< sum2 << "\n";

    return 0;
 }