#include<bits/stdc++.h>

typedef long long ll;
typedef std::tuple<ll,ll,std::string,ll> ltt;


ll valor_carta(std::string carta ,int etapa = 1){
    ll valor = 0;
    //Elevando al tamaña de la carta 10 para que asi cada valor tiene un peso
    for(auto i = carta.begin(); i != carta.end(); ++i){
        switch(*i){
            case 'T':
                valor = valor*14 + 10;
                break;
                case 'J':
                if(etapa == 1){
                    valor = valor*14 + 11;
                }else{
                    valor = valor*14 + 1;
                }
                break;
                case 'Q':
                valor = valor*14 + 12;
                break;
                case 'K':
                valor = valor*14 + 13;
                break;
                case 'A':
                valor = valor*14 + 14;
                break;
            default:
                valor = ((*i) - '0') + valor*14;
                break;
        }
    }

    return valor;
}

int identificar_valor(std::string carta, int etapa = 1){

    //  5 CARTAS IGUALES 7
    //  4 CARTAS IGUALES 6
    //  FULL HOUSE 5  3 CARTAS IGUALES Y 2 IGUALES   
    //  3 CARTAS IGUALES 4
    //  2 PARES 3
    //  1 PAR 2
    //  nada 1
    std::map<char,int> apari;
    //Ahora la j sirve como comodin y puede aumentar para convertir en otra lo que puede aumentar
    for(auto i :carta){
        apari[i]++;
    }
    if(apari.size() == 1){
        //cinco iguales
        return 7;
    }else if(apari.size() ==2){
        //Puede ser cuatro iguales o full house
            for(auto i: apari){
                if(i.second == 4 && etapa == 1){ //Si tiene 4 iguales es cuatro iguales xd
                    return 6;
                }else if(i.second == 4 && etapa == 2 && apari.count('J') >= 1){
                    return 7;
                }else if(i.second == 4){
                    return 6;
                }
            }
        //sino es full house  / la segunda parte solo puede 3 y 2 y si tiene un joker es 5 iguales
        if(apari.count('J') >= 1 && etapa == 2){
            return 7;
        }
        return 5;
    }else if(apari.size() == 3){ //Trio o two pair
        for(auto i:apari){
            if(i.second ==3 && etapa == 1){
                return 4 ;// Son 3 iguales
            }else if (i.second == 3 && etapa == 2 && apari.count('J') >= 1){
                // Se puede convertir en 4 iguales
                return 6;            
            }else if(i.second == 3){
                //Esto quiere decir que no tiene joker y es un trio
                return 4;
            }
        }
        //Si no es trio es two pair
        if(apari.count('J') >= 1 && apari['J'] >= 2 && etapa == 2){
            // Se convierte en 4 iguales
            return 6;
        }else if (apari.count('J') == 1 && etapa == 2){
            // Se convierte en 3 iguales
            return 5;
        }
        //Si no es trio es two pair no tiene joker
        return 3;
    }else if(apari.size() == 4){
        //Es un pair porque solo una se repite
        if(apari.count('J') == 1 && etapa == 2){
            // Se convierte en 3 iguales porque o bien hay 2 jokers o 1 joker y una carta igual
            // lo que se convierte en 3 iguales
            return 4;
        }
        //Si no es trio es one pair sin joker
        return 2;
    }else{
        //Si no es nada es high card
        if(apari.count('J') >= 1 && etapa == 2){
            // Se convierte en 2 iguales
            return 2;
        }
        return 1;
    }
}

int main(){

    std::string carta;
    ll apuesta = 0;
    ll valor_mano = 0;
    ll f_mano = 0;
    std::priority_queue<ltt,std::vector<ltt>,std::greater<ltt>> jeraquia;
    while(std::cin >> carta >> apuesta){
        valor_mano = valor_carta(carta,2);
        f_mano = identificar_valor(carta,2);
        jeraquia.push(std::make_tuple(f_mano,valor_mano,carta,apuesta));
    }
    ll contador = 1;
    ll result = 0;
    while(!jeraquia.empty()){
        auto [f,n,c,a] = jeraquia.top(); 
        std::cout << contador << " "  << f << " "  << n << " " << c << " " << a  << "\n";
        result+=contador*a;
    contador++;
    jeraquia.pop();
    }
    std::cout << " contando" << contador << "\n";
    std::cout << result << "\n";
    return 0;
}
//251136060
//248777389 249486190 249640985 249400220