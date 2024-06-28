#include <functional>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cmath>
#define pi 3.14159

using namespace std;
typedef pair<string,string> vp;

pair<float,float> calcularCoordenadas(vector<pair<string,pair<float,float>>> flagsmascercanas,vector<pair<string,vp>> coordenadasABS);
vector<pair<float,float>> corteCircunferencias(float a1, float a2, float R, float b1, float b2, float r);
float calcularAngulo(vector<pair<string,pair<float,float>>> const &flags, vector<pair<string,vp>> const &absolutas);
//--------------------------------------------------------------------------------VECTOR DE COORDENADAS ABSOLUTAS DEL CAMPO
vector<pair<string,vp>>coordenadasABS = {
        // {"cornersupizq", {"-52.5","-34"}},
        // {"cornersupder", {"52.5","-34"}},
        // {"cornerinfizq", {"-52.5","34"}},
        // {"cornerinfder", {"52.5","34"}},
        // {"centrosup", {"0","-34"}},
        // {"centro", {"0","0"}},
        // {"centroinf", {"0","34"}},
        // {"areasupizq", {"-36","-20"}},
        // {"areacentroizq", {"-36","0"}},
        // {"areainfizq", {"-36","20"}},
        // {"areasupder", {"36","-20"}},
        // {"areacentroder", {"36","0"}},
        // {"areainfder", {"36","20"}},
        // {"portsupder", {"52.5","-7"}},
        // {"portcentroder",{"52.5","0"}},
        // {"portinfder", {"52.5","7"}},
        // {"portsupizq", {"-52.5","-7"}},
        // {"portcentroizq", {"-52.5","0"}},
        // {"portinfizq", {"-52.5","7"}},
        //banda superior
        {"((f t l 50) ",{"-50","-39"}},
        {"((f t l 40) ",{"-40","-39"}},
        {"((f t l 30) ",{"-30","-39"}},
        {"((f t l 20) ",{"-20","-39"}},
        {"((f t l 10) ",{"-10","-39"}},
        {"((f t) ",{"0","-39"}},
        {"((f t r 50) ",{"50","-39"}},
        {"((f t r 40) ",{"40","-39"}},
        {"((f t r 30) ",{"30","-39"}},
        {"((f t r 20) ",{"20","-39"}},
        {"((f t r 10) ",{"10","-39"}},
        //banda inferior
        {"((f b l 50) ",{"-50","39"}},
        {"((f b l 40) ",{"-40","39"}},
        {"((f b l 30) ",{"-30","39"}},
        {"((f b l 20) ",{"-20","39"}},
        {"((f b l 10) ",{"-10","39"}},
        {"((f b) ",{"0","39"}},
        {"((f b r 50) ",{"50","39"}},
        {"((f b r 40) ",{"40","39"}},
        {"((f b r 30) ",{"30","39"}},
        {"((f b r 20) ",{"20","39"}},
        {"((f b r 10) ",{"10","39"}},
        //banda derecha
        {"((f r b 30) ",{"57.5","30"}},
        {"((f r b 20) ",{"57.5","20"}},
        {"((f r b 10) ",{"57.5","10"}},
        {"((f r 0) ",{"57.5","0"}},
        {"((f r t 30) ",{"57.5","-30"}},
        {"((f r t 20) ",{"57.5","-20"}},
        {"((f r t 10) ",{"57.5","-10"}},
        //banda izquierda
        {"((f l b 30) ",{"-57.5","30"}},
        {"((f l b 20) ",{"-57.5","20"}},
        {"((f l b 10) ",{"-57.5","10"}},
        {"((f l 0) ",{"-57.5","0"}},
        {"((f l t 30) ",{"-57.5","-30"}},
        {"((f l t 20) ",{"-57.5","-20"}},
        {"((f l t 10) ",{"-57.5","-10"}},

    };

//-------------------------------------------------------------------------------------------------------FUNCIONES
vector<string> separarPalabras(const string &palabra)
{
    int ncaracteres = palabra.size();
    vector<string> resultado;
    string aux;

    for (int i = 0; i < ncaracteres; i++)
    {
        ;
        if (palabra[i] == '(' || palabra[i] == ')')
            continue;
        if (palabra[i] == ' ')
        {
            resultado.push_back(aux);
            aux = "";
            continue;
        }
        aux += palabra[i];
    }
    resultado.push_back(aux); // última palabra
    return resultado;
}

vector<pair<string,pair<float,float>>> buscarMenores(vector<pair<string,vp>> p){
    float distancia1=99999;
    float distancia2=99999;
    float direccion1;
    float direccion2;
    string flag1;
    string flag2;
    for(auto t: p){  
          if(stof(t.second.first)<distancia1){
            distancia2= distancia1;
            direccion2=direccion1;
            flag2=flag1;
            distancia1=stof(t.second.first);
            direccion1=stof(t.second.second);
            flag1=t.first;
          }  
          else if (stof(t.second.first)<distancia2){
            distancia2=stof(t.second.first);
            direccion2=stof(t.second.second);
            flag2=t.first;
          }
    }
    vector<pair<string,pair<float,float>>> a ;
    a.push_back({flag1,{distancia1,direccion1}});
    a.push_back({flag2,{distancia2,direccion2}});
    return a;
}

pair<string, string> buscarValores(const std::string &input, const std::string &inicio) {
    if (input.find(inicio) == string::npos) {
        return {"-1", "-1"};
    }

    std::string fin = ")";
    size_t inicio_len = inicio.length();

    size_t pos = input.find(inicio);
    while (pos != std::string::npos) {
        // Encontrar el fin de la cadena de valores
        size_t end_pos = input.find(fin, pos + inicio_len);
        if (end_pos == std::string::npos) {
            break; // No se encontró el final de la cadena esperada
        }

        // Extraer la subcadena que contiene los valores
        std::string subcadena = input.substr(pos + inicio_len, end_pos - (pos + inicio_len));
        auto palabras = separarPalabras(subcadena);

        // Asegurarse de que hay suficientes palabras
        if (palabras.size() >= 2) {
            return {palabras[0], palabras[1]};
        }

        // Avanzar la posición para buscar la siguiente ocurrencia del prefijo
        pos = input.find(inicio, end_pos);
    }

    return {"-1", "-1"};
}

//------------------------------------------------------------------------------------------CONTENEDOR DE COORDENADAS INSTANTANEAS DEL JUGADOR (SOLO LAS QUE VE)

struct visioncampo{
    vp cornersupizq; //flt
    vp cornersupder; //frt
    vp cornerinfizq; //flb
    vp cornerinfder; //frb
    vp centrosup; //fct
    vp centro; //fc
    vp centroinf; //fcb
    vp areasupizq; //fplt
    vp areacentroizq; //fplc
    vp areainfizq; //fplb
    vp areasupder; //fprt
    vp areacentroder; //fprc
    vp areainfder; //fprb
    vp portsupizq; //fglt
    vp portcentroizq; //fglc
    vp portinfizq; //fglb
    vp portsupder; //fgrt
    vp portcentroder; //fgrc
    vp portinfder; //fgrb
                                //banda exterior superior derecha e izquierda 
    vp bandasup50ml; //ftl50
    vp bandasup40ml; //ftl40
    vp bandasup30ml; //ftl30
    vp bandasup20ml; //ftl20
    vp bandasup10ml; //ftl10
    vp bandasup50mr; //ftr50
    vp bandasup40mr; //ftr40
    vp bandasup30mr; //ftr30
    vp bandasup20mr; //ftr20
    vp bandasup10mr; //ftr10
    vp bandasup0m; //ft
                                //banda exterior inferior derecha e izquierda
    vp bandainf50ml; //fbl50
    vp bandainf40ml; //ftl40
    vp bandainf30ml; //ftl30
    vp bandainf20ml; //ftl20
    vp bandainf10ml; //ftl10
    vp bandainf50mr; //ftr50
    vp bandainf40mr; //ftr40
    vp bandainf30mr; //ftr30
    vp bandainf20mr; //ftr20
    vp bandainf10mr; //ftr10
    vp bandainf0m; //fb
                                //banda exterior derecha 
    vp bandader30mt; //frt30
    vp bandader20mt; //frt20
    vp bandader10mt; //frt10
    vp bandader30mb; //frb30
    vp bandader20mb; //truct visioncampo const &container,frb20
    vp bandader10mb; //frb10
    vp bandader0m; //fr0
                                //banda exterior izquierda
    vp bandaizq30mt; //flt30
    vp bandaizq20mt; //flt20
    vp bandaizq10mt; //flt10
    vp bandaizq30mb; //flb30
    vp bandaizq20mb; //flb20
    vp bandaizq10mb; //flb10
    vp bandaizq0m; //fl0



};

//------------------------------------------------------------------------------------------FUNCION QUE RELLENA EL CONTENEDOR EN CADA ITERACIÓN 
pair<float,pair<float,float>>  rellenaContenedor(visioncampo &container, const string &p) {
    vector<pair<string, vp*>> flagMap = {
        //{"((f l t) ", &container.cornersupizq},
        //{"((f r t) ", &container.cornersupder},
        //{"((f l b) ", &container.cornerinfizq},
        //{"((f r b) ", &container.cornerinfder},
        {"((f c t) ", &container.centrosup},
        {"((f c) ", &container.centro},
        {"((f c b) ", &container.centroinf},
        //{"((f p l t) ", &container.areasupizq},
        //{"((f p l c) ", &container.areacentroizq},
        //{"((f p l b) ", &container.areainfizq},
        //{"((f p r t) ", &container.areasupder},
        //{"((f p r c) ", &container.areacentroder},
        //{"((f p r b) ", &container.areainfder},
        {"((f g r t) ", &container.portsupder},
        {"((f g r c) ", &container.portcentroder},
        {"((f g r b) ", &container.portinfder},
        {"((f g l t) ", &container.portsupizq},
        {"((f g l c) ", &container.portcentroizq},
        {"((f g l b) ", &container.portinfizq},

        // Banda exterior superior derecha e izquierda 
        {"((f t l 50) ", &container.bandasup50ml},
        {"((f t l 40) ", &container.bandasup40ml},
        {"((f t l 30) ", &container.bandasup30ml},
        {"((f t l 20) ", &container.bandasup20ml},
        {"((f t l 10) ", &container.bandasup10ml},
        {"((f t r 50) ", &container.bandasup50mr},
        {"((f t r 40) ", &container.bandasup40mr},
        {"((f t r 30) ", &container.bandasup30mr},
        {"((f t r 20) ", &container.bandasup20mr},
        {"((f t r 10) ", &container.bandasup10mr},
        {"((f t) ", &container.bandasup0m},

        // Banda exterior inferior derecha e izquierda
        {"((f b l 50) ", &container.bandainf50ml},
        {"((f b l 40) ", &container.bandainf40ml},
        {"((f b l 30) ", &container.bandainf30ml},
        {"((f b l 20) ", &container.bandainf20ml},
        {"((f b l 10) ", &container.bandainf10ml},
        {"((f b r 50) ", &container.bandainf50mr},
        {"((f b r 40) ", &container.bandainf40mr},
        {"((f b r 30) ", &container.bandainf30mr},
        {"((f b r 20) ", &container.bandainf20mr},
        {"((f b r 10) ", &container.bandainf10mr},
        {"((f b) ", &container.bandainf0m},

        // Banda exterior derecha 
        {"((f r t 30) ", &container.bandader30mt},
        {"((f r t 20) ", &container.bandader20mt},
        {"((f r t 10) ", &container.bandader20mb},
        {"((f r b 30) ", &container.bandader30mb},
        {"((f r b 20) ", &container.bandader20mb},
        {"((f r b 10) ", &container.bandader10mb},
        {"((f r 0) ", &container.bandader0m},

        // Banda exterior izquierda
        {"((f l t 30) ", &container.bandaizq30mt},
        {"((f l t 20) ", &container.bandaizq20mt},
        {"((f l t 10) ", &container.bandaizq10mt},
        {"((f l b 30) ", &container.bandaizq30mb},
        {"((f l b 20) ", &container.bandaizq20mb},
        {"((f l b 10) ", &container.bandaizq10mb},
        {"((f l 0) ", &container.bandaizq0m},
    };

    //string auxflag="((f l t) ";
    //se inicializa un vector para cada banda para recoger el nombre de la flag, la distancia a esta y el angulo. {"(f r b)",{"50","-10"}}
    vector<pair<string,vp>> bandaextizq;
    vector<pair<string,vp>> bandaextder;
    vector<pair<string,vp>> bandaextinf;
    vector<pair<string,vp>> bandaextsup;
    for (const auto &flagPair : flagMap) {
        auto resultados = buscarValores(p, flagPair.first);
        if (resultados.first == "-1") {
            *(flagPair.second) = {"-1", "-1"};
        } else {
            *(flagPair.second) = resultados;
            
            if(flagPair.first.compare(0,8,"((f l t ")==0||flagPair.first.compare(0,8,"((f l 0)")==0||flagPair.first.compare(0,8,"((f l b ")==0){ //no puedo comparar la ultima parte (los numeros)
                bandaextizq.push_back({flagPair.first,*flagPair.second});
            }else if(flagPair.first.compare(0,8,"((f r t ")==0||flagPair.first.compare(0,8,"((f r 0)")==0||flagPair.first.compare(0,8,"((f r b ")==0){
                bandaextder.push_back({flagPair.first,*flagPair.second});
            }
            else if(flagPair.first.compare(0,8,"((f b l ")==0||flagPair.first.compare(0,6,"((f b)")==0||flagPair.first.compare(0,8,"((f b r ")==0){
                bandaextinf.push_back({flagPair.first,*flagPair.second});
            }
            else if(flagPair.first.compare(0,8,"((f t l ")==0||flagPair.first.compare(0,6,"((f t)")==0||flagPair.first.compare(0,8,"((f t r ")==0){
                bandaextsup.push_back({flagPair.first,*flagPair.second});
            }
        }
    }
    //se inicializan unos valores suma elevados para que no interfieran en caso de no ser utilizados
    float sumaizq=9999999, sumader=9999999, sumasup=9999999, sumainf=9999999;

    //se inicializa un vector para cada banda para recoger los 2 flags mas cercanos. [{"(f r b)",{50,10}},"(f r b 10)",{30,10}}]
    vector<pair<string,pair<float,float>>> menoresizq;
    vector<pair<string,pair<float,float>>> menoresder;
    vector<pair<string,pair<float,float>>> menoressup;
    vector<pair<string,pair<float,float>>> menoresinf;
    //vector para almacenar la suma de la distancia de los flags cercanos. [50+30,...]
    vector<float> sumas;
    //VARIABLES PARA LAS COORDENADAS RESULTANTES DEL JUGADOR Y LOS DOS FLAGS QUE PERMITEN EL CALCULO
    pair<float,float> xy;
    float alpha;

    menoresizq = buscarMenores(bandaextizq); //funcion para encontrar los 2 valores de distancia mas cercanos
    sumaizq=menoresizq[0].second.first+menoresizq[1].second.first;  //funcion para sumar ambos valores de distancia
    menoresder = buscarMenores(bandaextder);    
    sumader=menoresder[0].second.first+menoresder[1].second.first;
    menoressup = buscarMenores(bandaextsup);
    sumasup=menoressup[0].second.first+menoressup[1].second.first;
    menoresinf = buscarMenores(bandaextinf);
    sumainf=menoresinf[0].second.first+menoresinf[1].second.first;

    if(bandaextizq.size()>=2){ //comprobamos que la banda tenga al menos 2 flags
        sumas.push_back(sumaizq); //metemos el valor de la suma de las distancias en el vector sumas
    }
    if(bandaextder.size()>=2){
        sumas.push_back(sumader);
    }
    if(bandaextsup.size()>=2){
        sumas.push_back(sumasup);
    }
    if(bandaextinf.size()>=2){
        sumas.push_back(sumainf);
    }
    

    float distancia1=99999;
    for(auto t: sumas){   //buscamos el valor mas pequeño de todas las sumas de distancias
          if(t<distancia1){
            distancia1=t;
          }  

    }
    if(distancia1==sumaizq){ //comprobamos que el valor mas pequeño de todas las sumas de distancias coincida con nuestra banda
        xy = calcularCoordenadas(menoresizq,coordenadasABS); //utilizamos la funcion calcularCoordenadas que incluye el uso de corteCircunferencias
        alpha = calcularAngulo(menoresizq,coordenadasABS);
    }
    else if(distancia1==sumader){
        xy = calcularCoordenadas(menoresder,coordenadasABS);
        alpha = calcularAngulo(menoresder,coordenadasABS);
    }
    else if(distancia1==sumasup){
        xy = calcularCoordenadas(menoressup,coordenadasABS);
        alpha = calcularAngulo(menoressup,coordenadasABS);
    }
    else if(distancia1==sumainf){
        xy = calcularCoordenadas(menoresinf,coordenadasABS);
        alpha = calcularAngulo(menoresinf,coordenadasABS);
    }

    return {alpha,xy};
    
}

vector<pair<float,float>> corteCircunferencias(float a1, float a2, float R, float b1, float b2, float r) {
    vector<pair<float,float>> resultado;
    if (b1 != a1)
    {
        float A = b1 * b1 - a1 * a1 + b2 * b2 - a2 * a2 - r * r + R * R;
        float B = -2 * (b2 - a2);
        float C = 2 * (b1 - a1);
        float D = -a1 * C + A;
        float H = D * D + (C * C * a2 * a2) - (R * R * C * C);
        float V = B * B + C * C;
        float W = 2 * B * D - 2 * a2 * C * C;

        float discriminant = W * W - 4 * V * H;
        if (discriminant < 0) {
            // No hay solución real si el discriminante es negativo
            resultado.push_back({999999999,999999999});
            return resultado;
        }

        float sqrt_discriminant = sqrt(discriminant);

        float p1_y = (-W + sqrt_discriminant) / (2 * V);
        float p1_x = (A + B * p1_y) / C;

        float p2_y = (-W - sqrt_discriminant) / (2 * V);
        float p2_x = (A + B * p2_y) / C;

        pair<float,float> pt1 = { p1_x, p1_y };
        pair<float,float> pt2 = { p2_x, p2_y };
        resultado.push_back(pt1);
        resultado.push_back(pt2);

        return resultado;

    }

    float A = b1 * b1 - a1 * a1 + b2 * b2 - a2 * a2 - r * r + R * R;
    float B = 2 * (b2 - a2);
    float p1_y = A / B;
    float W = -2 * a1;
    float H = a1 * a1 + p1_y * p1_y - 2 * p1_y * a2 + a2 * a2 - R * R;

    
    float p1_x = (-W + sqrt(W * W - 4 * H)) / 2;

    float p2_y = p1_y;
    float p2_x = (-W - sqrt(W * W - 4 * H)) / 2;

    
    pair<float,float> pt1 = { p1_x, p1_y };
    pair<float,float> pt2 = { p2_x, p2_y };
    resultado.push_back(pt1);
    resultado.push_back(pt2);

    return resultado;
}

pair<float,float>  calcularCoordenadas(vector<pair<string,pair<float,float>>> flagsmascercanas,vector<pair<string,vp>> coordenadasABS){
     float x1abs,y1abs,x2abs,y2abs; //inicializamos valores absolutos de ambos flags
     vector<pair<float,float>> xy;
     for(auto v: coordenadasABS){ //recorremos el vector coordenadasABS y buscamos nuestros 2 flags
        
        if(v.first == flagsmascercanas[0].first){  //flagsmascercanas EJEMPLO: [{"(f r b)",{50,10}},"(f r b 10)",{30,10}}]
            x1abs=stof(v.second.first);
            y1abs=stof(v.second.second);
        }
        if(v.first == flagsmascercanas[1].first){
            x2abs=stof(v.second.first);
            y2abs=stof(v.second.second);
        }
        
    }
    xy = corteCircunferencias(x1abs,y1abs,flagsmascercanas[0].second.first,x2abs,y2abs,flagsmascercanas[1].second.first); //utilizamos la funcion corteCircunferencias para resolver los 2 puntos de corte
    if( (abs(xy[0].first) > 57.5)   || (abs(xy[0].second) >  39)){ //nos quedamos con el punto de corte que este dentro del campo
        return xy[1];
    }else {return xy[0];}
}


//se inicializa un vector para cada banda para recoger los 2 flags mas cercanos. [{"(f r b)",{50,10}},"(f r b 10)",{30,10}}]

float calcularAngulo(vector<pair<string,pair<float,float>>> const &flags, vector<pair<string,vp>> const &absolutas){
    float alpha = 0.0; //Nuestro resultado final    
    //Primero almacenamos los valores de los flasg cercanos
    float x1abs,y1abs,x2abs,y2abs;
    vector<pair<float,float>> xy_aux;
    pair<float,float>xy,unitario,JP,JPunitario;
    for(auto v: coordenadasABS){ //Recorremos el vector coordenadasABS y buscamos nuestros 2 flags
        if(v.first == flags[0].first){
            x1abs=stof(v.second.first);
            y1abs=stof(v.second.second);
        }
        if(v.first == flags[1].first){
            x2abs=stof(v.second.first);
            y2abs=stof(v.second.second);
        }
    }
    //En este punto tenemos almacenadas en las variables las posiciones de los flags absolutas
    //Ahora calculamos las coordenadas absolutas del jugador y con eso y el ángulo con el que ve dicho flag podremos calcular el angulo de vision absoluto
    
    xy_aux = corteCircunferencias(x1abs,y1abs,flags[0].second.first,x2abs,y2abs,flags[1].second.first); //utilizamos la funcion corteCircunferencias para resolver los 2 puntos de corte
    if( (abs(xy_aux[0].first) > 57.5)   || (abs(xy_aux[0].second) >  39)){ //nos quedamos con el punto de corte que este dentro del campo
        xy= xy_aux[1];
    }else {xy = xy_aux[0];}

    //En xy almacenamos la posicion de nuestro jugador y sólo nos hará falta un flag para calcular su ángulo absoluto.
    //flags EJEMPLO: flags = [{"(f r b)",{50,10}},"(f r b 10)",{30,10}}]
    //Escogeremos el primero de ellos, en el ejemplo: flag = flags[0].first , distancia = flags[0].second,first , anguloBETA = flags[0].second.second
    //Necesitamos necesariamente el BETA, x1abs , y1abs, xy.first , xy.second que corresponden a las posiciones absolutas del flag, del jugador, y el angulo con el que el jugador ve el flag escogido
    //Nuestro vector director provisional es el (0,1) : unitario vertical
    unitario = {0.0,1.0};
    //Necesitamos tambien el vector que une el jugador con el flag y su direcion o vector unitario
    JP = {x1abs-xy.first,y1abs-xy.second};
    float moduloJP = sqrt(JP.first*JP.first+JP.second*JP.second);
    JPunitario = {JP.first/moduloJP,JP.second/moduloJP};

    //Primero sacamos el ángulo con el unitario con la formula del dot_product: A·B = x1*x2 + y1*y2 (utilizamos los unitarios)
    float cos_angle = JPunitario.first*unitario.first+JPunitario.second*unitario.second;
    //Asegurarse de que el valor esté dentro del rango válido para acos
    if (cos_angle < -1.0) cos_angle = -1.0;
    if (cos_angle > 1.0) cos_angle = 1.0;
    float theta = acos(cos_angle); //RADIANES

    //DISTINGUIMOS DOS CASOS: FLAG A LA IZQUIERDA Y FLAG A LA DERECHA DEL JUGADOR
    if(x1abs<xy.first){ //---------------------------flag a la izquierda
        float alpha = -theta-flags[0].second.second - pi/2;
    }else{              //---------------------------flag a la derecha
        float alpha = -theta-flags[0].second.second - pi/2;
    }
    return alpha;
}



int main(){
    string palabra="(see 57 ((f c) 50.9 0) ((f c t) 61.6 -34) ((f c b) 61.6 34) ((f r t) 108.9 -18) ((f r b) 108.9 18) ((f g r b) 103.5 4) ((g r) 103.5 0) ((f g r t) 103.5 -4) ((G) 1.5 180) ((f p r b) 89.1 13) ((f p r c) 87.4 0) ((f p r t) 89.1 -13) ((f p l b) 25 53 0 0) ((f p l c) 15 0 0 0) ((f p l t) 25 -53 0 0) ((f t 0) 64.1 -37) ((f t r 10) 72.2 -33) ((f t r 20) 80.6 -29) ((f t r 30) 90 -26) ((f t r 40) 99.5 -23) ((f t r 50) 107.8 -21) ((f t l 10) 56.8 -44) ((f t l 20) 49.9 -52) ((f b 0) 64.1 37) ((f b r 10) 72.2 33) ((f b r 20) 80.6 29) ((f b r 30) 90 26) ((f b r 40) 99.5 23) ((f b r 50) 107.8 21) ((f b l 10) 56.8 44) ((f b l 20) 49.9 52) ((f r 0) 108.9 0) ((f r t 10) 108.9 -5) ((f r t 20) 109.9 -10) ((f r t 30) 112.2 -15) ((f r b 10) 108.9 5) ((f r b 20) 109.9 10) ((f r b 30) 112.2 15) ((b) 49.4 0) ((l r) 103.5 90))";
    struct visioncampo micontainer;
    
    auto coordenadas = rellenaContenedor(micontainer, palabra);
    cout<<"La posicion de mi jugador es: "<<coordenadas.second.first<<" "<<coordenadas.second.second<<" y el angulo con el que mira: "<<coordenadas.first<<endl;
    
    return 0;
}
