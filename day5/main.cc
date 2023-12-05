#include <bits/stdc++.h>

typedef std::tuple<long long, long long, long long> tupla3;
typedef std::pair<long long, long long> par_p;
// Busca por el segundo elemento de la tupla
struct ComparaPorSegundo {
  bool operator()(long long x, tupla3 const &b) const {
    return x < std::get<1>(b);
  }
  bool operator()(tupla3 const &b, long long x) const {
    return std::get<1>(b) < x;
  }

  bool operator()(tupla3 const &a, tupla3 const &b) const {
    return std::get<1>(a) < std::get<1>(b);
  }
};

void imprimir(std::vector<std::vector<tupla3>> &traduciones) {
  for (int i = 0; i < traduciones.size(); i++) {
    std::cout << "Traduccion " << i + 1 << std::endl;
    for (int j = 0; j < traduciones[i].size(); j++) {
      std::cout << std::get<0>(traduciones[i][j]) << " "
                << std::get<1>(traduciones[i][j]) << " "
                << std::get<2>(traduciones[i][j]) << std::endl;
    }
  }
}

void traducion1(std::vector<std::vector<tupla3>> &traduciones,
                std::vector<long long> &lista_num) {
  for (int i = 0; i < traduciones.size(); i++) {
   // std::cout << "######## Traduccion " << i + 1 << std::endl;
    for (int j = 0; j < lista_num.size(); j++) {
      auto it = std::lower_bound(traduciones[i].begin(), traduciones[i].end(),
                                 lista_num[j], ComparaPorSegundo());
      // Comprobar si lo encontro el valor
    //  std::cout << "Se traduce el numero: " << lista_num[j] << std::endl;
      if (it != traduciones[i].end() && std::get<1>(*it) == lista_num[j]) {
        lista_num[j] = std::get<0>(*it);
      }

      // si no se encuentra se comprueba con el anterior para ver si menor
      else if (it != traduciones[i].begin()) {
        it--;
     //   std::cout << "Tupla " << std::get<1>(*it) << " " << lista_num[j] << "\n"
     //             << std::endl;
        if (std::get<1>(*it) < lista_num[j] &&
            std::get<1>(*it) + std::get<2>(*it) >= lista_num[j]) {
          lista_num[j] =
              std::get<0>(*it) + abs((std::get<1>(*it) - lista_num[j]));
    //      std::cout << "Nuevo numero: " << lista_num[j] << std::endl;
        } else {
          // Traducion no encontrada se deja como esta
        }
      } else {
    //    std::cout << "Tupla " << std::get<1>(*it) << " " << lista_num[j] << "\n"
    //              << std::endl;
        if (std::get<1>(*it) < lista_num[j] &&
            std::get<1>(*it) + std::get<2>(*it) >= lista_num[j]) {
          lista_num[j] =
              std::get<0>(*it) + abs((std::get<1>(*it) - lista_num[j]));
    //      std::cout << "Nuevo numero: " << lista_num[j] << std::endl;
        } else {
          // Traducion no encontrada se deja como esta
        }
      }
      // Imprimir  la lista
   //   for (auto i : lista_num) {
  //      std::cout << i << " ";
  //    }
  //    std::cout << std::endl;
    }
  }
}

void traducion(std::vector<std::vector<tupla3>> &traduciones,
               std::list<par_p> &lista_num) {
  // Vector de tuplas que representa la traducion
  long long menor = -1;
  for (auto i : lista_num) {
    std::vector<par_p> traducido;
    std::list<par_p> falta_traducir;
    falta_traducir.push_back(i);
    for (int j = 0; j < traduciones.size(); j++) {
      /*  std::cout << "######## Traduccion " << j + 1 << std::endl;
        std::cout << "Falta traducir" << std::endl;
        for(auto i: falta_traducir){
            std::cout << i.first << " " << i.second << std::endl;
        }
        std::cout << std::endl;
        std::cout << "--Traducidos--" << std::endl;
        for(auto i: traducido){
            std::cout << i.first << " " << i.second << std::endl;
        }*/
        traducido.clear();
      while (!falta_traducir.empty()) {
        par_p par = falta_traducir.front();
      //  std::cout << "Se traduce el numero: " << par.first << " " << par.second
        //          << std::endl;
        falta_traducir.pop_front();
        // Se comprueba hasta donde se puede traducir se desde el inicio
        auto it2 = std::lower_bound(traduciones[j].begin(), traduciones[j].end(),
                             par.first, ComparaPorSegundo());
        // Se comprueba si se encontro el valor
        if (it2 != traduciones[j].end() && std::get<1>(*it2) == par.first) {
         //   std::cout << "Misma posicion" <<  par.first << " " << par.second
          //        << std::endl;
          // Comprobamos hasta donde se puede traducir y lo que sobre a la lista
          // de numeros y quitamos el par
          if (std::get<1>(*it2) + std::get<2>(*it2) >= par.first + par.second) {
            // Se traduce el numero
        //    std::cout << "Esta totalmente dentro" << std::endl;
            par.first =
                std::get<0>(*it2) + abs((std::get<1>(*it2) - par.first));
            // Se agrega a la lista de numeros a traducir
            traducido.push_back(par);
          } else {
            // Comprobar hasta donde puedo traducir
            // Nuevo par el inicio coincide pero el final no que esta hasta get2
         //   std::cout << "Esta parcialmente dentro por el principio" << std::endl;
            long long indice_inferior = std::get<0>(*it2);
            long long indice_superior = std::get<2>(*it2);
            // Pero necesito calcular hasta donde llego
            long long inicio = par.first + std::get<2>(*it2);
            long long fin = par.second - std::get<2>(*it2);
            // se añade
            falta_traducir.push_back(std::make_pair(inicio, fin));
            traducido.push_back(
                std::make_pair(indice_inferior, indice_superior));
          }
        } else if (it2 != traduciones[j].begin()) {
          it2--;
        //  std::cout << "Tupla " << std::get<1>(*it2) << " " << par.first << std::endl;
          long long ti = std::get<1>(*it2);
          long long tf = std::get<1>(*it2) + std::get<2>(*it2);
          long long pi = par.first;
          long long pf = par.first + par.second;
          // Esta totalmente dentro del rango total mente dentro
          if (ti <= pi && tf >= pf) {
            // std::cout << "Esta totalmente dentro" << std::endl;
            // Se traduce el numero
            par.first =
                std::get<0>(*it2) + abs((std::get<1>(*it2) - par.first));
            // Se agrega a la lista de numeros a traducir
            traducido.push_back(par);
          }
          // El parte del final por dentro
          else if (ti > pi && ti < pf && tf >= pf) {
          //  std::cout << "Esta parcialmente dentro por el final" << std::endl;
            // Se calcula el 2 nuevo par uno que estara traducido y el otro que
            // estara por fuera
            long long inicio_fuera = pi;
            long long distancia_fuera = ti - pi;
            long long inicio_dentro = std::get<0>(*it2);
            long long distancia_dentro = pf - ti;
            // Se añade el par que esta por fuera
            falta_traducir.push_back(
                std::make_pair(inicio_fuera, distancia_fuera));
            // Se añade el par que esta por dentro
            traducido.push_back(
                std::make_pair(inicio_dentro, distancia_dentro));
          }
          // El parte del inicio por dentro
          else if (ti < pi && tf > pi && tf < pf) {
        //    std::cout << "Esta parcialmente dentro por el principio" << std::endl;
            // Se calcula el 2 nuevo par uno que estara traducido y el otro que
            // estara por fuera
            long long inicio_fuera = tf;
            long long distancia_fuera = pf - tf;
            long long inicio_dentro = pi - ti + std::get<0>(*it2);
            long long distancia_dentro = tf - pi;
            // Se añade el par que esta por fuera
            falta_traducir.push_back(
                std::make_pair(inicio_fuera, distancia_fuera));
            // Se añade el par que esta por dentro
            traducido.push_back(
                std::make_pair(inicio_dentro, distancia_dentro));
          }else{
            // No se puede traducir
          //  std::cout << "No se puede traducir" << std::endl;
            traducido.push_back(par);
          }
        } else {
          // No se puede traducir
        //    std::cout << "No se puede traducir" << std::endl;
          traducido.push_back(par);
        }
      }
      //std::cout << "Traducidos" << std::endl;
       // for(auto i: traducido){
      //      std::cout << i.first << " " << i.second << std::endl;
     //   }
     //   std::cout << std::endl;
        for(auto i: traducido){
            falta_traducir.push_back(i);
        }
    }
    sort(traducido.begin(), traducido.end());
   // for (auto i : traducido) {
    //  std::cout << i.first << " " << i.second << std::endl;
   // }
   // std::cout << std::endl;
    if(menor == -1){
      menor = traducido.front().first;
    }else{
      if(menor > traducido.front().first){
        menor = traducido.front().first;
      }
    }
  }
  std::cout << "2 ) El menor es: " << menor << std::endl;
}

int main() {
  std::regex patron("(\\d)+");
  std::string line;
  getline(std::cin, line);
  std::vector<long long> lista_num;
  std::smatch match;
  while (std::regex_search(line, match, patron)) {
    lista_num.push_back(std::stoll(match.str()));
    line = match.suffix();
  }
  // Vector de pares de numeros a partir de la lista de numeros
  std::list<std::pair<long long, long long>> lista_num_pares;
  for (int i = 0; i < lista_num.size(); i++) {
    lista_num_pares.push_back(std::make_pair(lista_num[i], lista_num[i + 1]));
  i++;
  }

  // De adorno xd
  std::sort(lista_num.begin(), lista_num.end());
  //for (auto i : lista_num) {
  //  std::cout << i << " ";
 // }
  // declara una vector de tuplas tuplas
  std::vector<tupla3> seed_to_soil;
  getline(std::cin, line);  // Se borra line blanco
  getline(std::cin, line);  // Titulo se va
  while (getline(std::cin, line) && line != "") {
    std::regex_search(line, match, patron);
    long long seed = std::stoll(match.str());
    line = match.suffix();
    std::regex_search(line, match, patron);
    long long soil = std::stoll(match.str());
    line = match.suffix();
    std::regex_search(line, match, patron);
    long long cost = std::stoll(match.str());
    seed_to_soil.push_back(std::make_tuple(seed, soil, cost));
  }
  sort(seed_to_soil.begin(), seed_to_soil.end(), ComparaPorSegundo());
  // Se crear un vector con cada uno es un vector de tuplas que representa
  // la traudicones
  std::vector<std::vector<tupla3>> traduciones;
  traduciones.push_back(seed_to_soil);

  // Se repite  7 veces para vector
  std::vector<tupla3> aux;
  for (int i = 1; i <= 6; i++) {
    getline(std::cin, line);  // Titulo se va
    while (getline(std::cin, line) && line != "") {
      std::regex_search(line, match, patron);
      long long seed = std::stoll(match.str());
      line = match.suffix();
      std::regex_search(line, match, patron);
      long long soil = std::stoll(match.str());
      line = match.suffix();
      std::regex_search(line, match, patron);
      long long cost = std::stoll(match.str());
      aux.push_back(std::make_tuple(seed, soil, cost));
    }
    sort(aux.begin(), aux.end(), ComparaPorSegundo());
    traduciones.push_back(aux);
    aux.clear();
  }
 // imprimir(traduciones);
 // Medir tiempo de ejecucion de la traducion1
    auto start = std::chrono::high_resolution_clock::now();
    traducion1(traduciones,lista_num);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
 //Tiempo de ejecucion de la traducion2
    sort(lista_num.begin(), lista_num.end());
    std::cout << "1 ) El menor es: " << lista_num.front() << std::endl;
    std::cout << "Tiempo de ejecucion: " << diff.count() << " s" << std::endl;
    
    start = std::chrono::high_resolution_clock::now();
    traducion(traduciones, lista_num_pares);
    end = std::chrono::high_resolution_clock::now();
    diff = end-start;
    std::cout << "Tiempo de ejecucion: " << diff.count() << " s" << std::endl;
    std::cout << std::endl;
  return 0;
}