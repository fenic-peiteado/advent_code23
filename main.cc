#include<bits/stdc++.h>



typedef std::tuple<long long,long long,long long> tupla3;

//Busca por el segundo elemento de la tupla
struct ComparaPorSegundo {
     bool operator()(long long x, tupla3 const & b) const {
        return x < std::get<1>(b);
    }
    bool operator()(tupla3 const & b, long long x) const {
        return std::get<1>(b) < x;
    }
};

void imprimir(std::vector<std::vector<tupla3>> &traduciones){
    for(int i=0;i<traduciones.size();i++){
        std::cout<<"Traduccion "<<i+1<<std::endl;
        for(int j=0;j<traduciones[i].size();j++){
            std::cout<<std::get<0>(traduciones[i][j])<<" "<<std::get<1>(traduciones[i][j])<<" "<<std::get<2>(traduciones[i][j])<<std::endl;
        }
    }
}

void traducion(std::vector<std::vector<tupla3>> &traduciones,std::vector<long long> &lista_num){
    for(int i=0;i<traduciones.size();i++){
        for(int j = 0;j< lista_num.size();j++){
            int x = 0;
            auto it = std::lower_bound(traduciones[i].begin(),traduciones[i].end(),lista_num[j],ComparaPorSegundo());
            //Comprobar si lo encontro el valor 
            if(it != traduciones[i].end() && std::get<1>(*it) == lista_num[j]){
                lista_num[j] = std::get<0>(*it);
            }
            // si no se encuentra se comprueba con el anterior para ver si menor
            else if(it != traduciones[i].begin()){
                it--;
                if(std::get<1>(*it) < lista_num[j] && std::get<0>(*it) + std::get<2>(*it) >= lista_num[j]){
                    //
                    lista_num[j] = std::get<0>(*it) + (std::get<1>(*it) + std::get<2>(*it) - lista_num[j]);
                }
                else{
                   //Traducion no encontrada se deja como esta
                }
            }
            //Imprimir  la lista
            for(auto i:lista_num){
                std::cout<<i<<" ";
            }
            std::cout<<std::endl;
        }
    }
}

int main(){

    std::regex patron("(\\d)+");
    std::string line;
    getline(std::cin,line);
    std::vector<long long> lista_num;
    std::smatch match;
    while(std::regex_search(line,match,patron)){
        lista_num.push_back(std::stoll(match.str()));
        line = match.suffix();
    }
    std::sort(lista_num.begin(),lista_num.end());
    for(auto i:lista_num){
        std::cout<<i<<" ";
    }
    //declara una vector de tuplas tuplas
    std::vector<tupla3> seed_to_soil;
    getline(std::cin,line); //Se borra line blanco
    getline(std::cin,line); //Titulo se va
    while(getline(std::cin,line) && line!=""){
        std::regex_search(line,match,patron);
        long long seed = std::stoll(match.str());
        line = match.suffix();
        std::regex_search(line,match,patron);
        long long soil = std::stoll(match.str());
        line = match.suffix();
        std::regex_search(line,match,patron);
        long long cost = std::stoll(match.str());
        seed_to_soil.push_back(std::make_tuple(seed,soil,cost));
    }
    sort(seed_to_soil.begin(),seed_to_soil.end());
    //Se crear un vector con cada uno es un vector de tuplas que    representa la traudicones
    std::vector<std::vector<tupla3>> traduciones;
    traduciones.push_back(seed_to_soil);
    
    //Se repite  7 veces para vector
    std::vector<tupla3> aux;
    for(int i=0;i<7;i++){
       getline(std::cin,line); //Titulo se va
        while(getline(std::cin,line) && line!=""){
        std::regex_search(line,match,patron);
        long long seed = std::stoll(match.str());
        line = match.suffix();
        std::regex_search(line,match,patron);
        long long soil = std::stoll(match.str());
        line = match.suffix();
        std::regex_search(line,match,patron);
        long long cost = std::stoll(match.str());
        aux.push_back(std::make_tuple(seed,soil,cost));
        }
        sort(aux.begin(),aux.end());
        traduciones.push_back(aux);
        aux.clear();
    }
    imprimir(traduciones);
    traducion(traduciones,lista_num);
    std::cout<<std::endl;
    for(auto i:lista_num){
        std::cout<<i<<" ";
    }
    return 0;
}