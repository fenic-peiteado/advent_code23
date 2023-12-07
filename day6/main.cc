#include <bits/stdc++.h>


typedef std::vector<int> vi;
typedef long long ll;


int main(){

    std::string line;
    vi times;
    vi distances;
    int time, distance;
    std::regex re_num("(\\d)+");
    std::getline(std::cin, line);
    std::sregex_iterator it(line.begin(), line.end(), re_num);
    std::sregex_iterator end;
    while(it != end) {
        times.push_back(std::stoi((*it)[0]));
        ++it;
    }
    std::getline(std::cin, line);
    it = std::sregex_iterator(line.begin(), line.end(), re_num);
    while(it != end) {
        distances.push_back(std::stoi((*it)[0]));
        ++it;
    }
    //Ecuacion de segundo grado resuelve los limites y se puede calcula el rango de valores
    // la formula es V*(T-V) > D
    // -V^2 + V*T - D < 0
    // V = (T + sqrt(T^2 - 4*(-D)*-1))/2
    // V = (T - sqrt(T^2 - 4*(-D)*-1))/2
    // Se simplifica a
    // V = (T + sqrt(T^2 + 4*(-D)))/2
    // V = (T - sqrt(T^2 + 4*(-D)))/2
     ll v1 = 0, v2 = 0;
     ll result = 1;
    for(int i = 0; i < times.size(); ++i){
        time = times[i];
        distance = distances[i];
        v1 = (time + sqrt(time*time + 4*(-distance)))/2;
        v2 = (time - sqrt(time*time + 4*(-distance)))/2;
        ll v3 = std::max(v1, v2);
        ll v4 = std::min(v1, v2);
        if(v3*(time - v3) <= distance){
            v3--;
        }
        //Calcula diferencia entre los valores
        std::cout << std::abs(v3-v4) << std::endl;
        result *= std::abs(v3 - v4);
    }

    std::cout << result << std::endl;  
    //Parte 2
    ll super_time = 0;
    ll super_distance = 0;
    //Forma numero con los numeros de los vectore 
    std::stringstream ss1;
    std::stringstream ss2;
    for(int i = 0; i < times.size(); ++i){
        ss1 << times[i];
        ss2 << distances[i];
    }
    //Convierte a numeros
    super_time = std::stoll(ss1.str());
    super_distance = std::stoll(ss2.str());
    std::cout << super_time << std::endl;
    std::cout << super_distance << std::endl;
    //Calcula la velocidad
    v1 = (super_time + sqrt(super_time*super_time + 4*(-super_distance)))/2;
    v2 = (super_time - sqrt(super_time*super_time + 4*(-super_distance)))/2;
    v1 = std::max(v1, v2);
    v2 = std::min(v1, v2);
    if(v1*(super_time - v1) <= super_distance){
        v1--;
    }
    std::cout << std::abs(v1-v2) << std::endl;
    return 0;
}