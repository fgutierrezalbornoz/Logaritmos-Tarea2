#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <iomanip> //para printpretty
#include <queue> //para print vertical
#include <string>
#include <algorithm> // Para std::shuffle
#include <random>    // Para std::random_device y std::mt19937
#include <ctime>
#include <filesystem>

using namespace std;

class Node {
    public:
        int info;
        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(int x){
            info = x;
        }
        Node(int x, Node* p){
            info = x;
            parent = p;
        }
        Node(int x, Node* l, Node* r){
            info = x;
            left = l;
            right = r;
        }
        Node(int x, Node* p, Node* l, Node* r){
            info = x;
            parent = p;
            left = l;
            right = r;
        }

        int searchABB(int x){
            if (x == info){
                return 1;
            }
            if (x < info){
                if (left == nullptr){
                    return 0;
                }
                return left->searchABB(x);
            }
            else {
                if (right == nullptr){
                    return 0;
                }
                return right->searchABB(x);
            }
        }
        void insertABB(int x){
            if (searchABB(x)){
                std::cout<<x<<" ya tiene un nodo asignado\n";
                return;
            }
            if (x<info){
                if(left==nullptr){
                    left = new Node(x, this);
                    return;
                }
                left->insertABB(x);
            }
            else {
                if(right==nullptr){
                    right = new Node(x, this);
                    return;
                }
                right->insertABB(x);
            }
        }

        void zig(Node* root){
            Node* y = root;
            Node* x = root->left;
            y->left = x->right;
            x->right = y;
            y->parent = x;
            x->parent = nullptr;
            if (y->left != nullptr){
                y->left->parent = y;
            }
            root = x;
        }
        void zag(Node* root){
            Node* y = root;
            Node* x = root->right;
            y->right = x->left;
            x->left = y;
            y->parent = x;
            x->parent = nullptr;
            if (y->right != nullptr){
                y->right->parent = y;
            }
            root = x;
        }
        void zig_zig(Node* root){
            Node* z = root;
            Node* y = root->left;
            Node* x = root->left->left;
            z->left = y->right;
            y->left = x->right;
            x->right = y;
            y->right = z;
            if (y->left != nullptr){
                y->left->parent = y;
            }
            if (z->left != nullptr){
                z->left->parent = z;
            }
            x->parent = z->parent;
            y->parent = x;
            z->parent = y;
            root = x;
        }
        void zig_zag(Node* root){
            Node* z = root;
            Node* y = root->left;
            Node* x = root->left->right;
            z->left = x->right;
            y->right = x->left;
            x->left = y;
            x->right = z;
            if (y->right != nullptr){
                y->right->parent = y;
            }
            if (z->left != nullptr){
                z->left->parent = z;
            }
            x->parent = z->parent;
            y->parent = x;
            z->parent = x;
            root = x;
        }
        void zag_zig(Node* root){
            Node* z = root;
            Node* y = root->right;
            Node* x = root->right->left;
            z->right = x->left;
            y->left = x->right;
            x->right = y;
            x->left = z;
            if (y->left != nullptr){
                y->left->parent = y;
            }
            if (z->right != nullptr){
                z->right->parent = z;
            }
            x->parent = z->parent;
            y->parent = x;
            z->parent = x;
            root = x;
        }
        void zag_zag(Node* root){
            Node* z = root;
            Node* y = root->right;
            Node* x = root->right->right;
            z->right = y->left;
            y->right = x->left;
            x->left = y;
            y->left = z;
            if (y->right != nullptr){
                y->right->parent = y;
            }
            if (z->right != nullptr){
                z->right->parent = z;
            }
            x->parent = z->parent;
            y->parent = x;
            z->parent = y;
            root = x;
        }

        void prettyPrintfile(Node* node,int indent = 0, std::ostream& out = std::cout) {
            if (node->right) {
                prettyPrintfile(node->right,indent + 4, out);
            }
            if (indent) {
                out << std::setw(indent) << ' ';
            }
            if (node->right) out << " /\n" << std::setw(indent) << ' ';
            out << node->info << "\n";
            if (node->left) {
                out << std::setw(indent) << ' ' << " \\\n";
                prettyPrintfile(node->left,indent + 4, out);
            }
        }

        void splay(Node* x){
            if (x->parent == nullptr){
                return;
            }
            if (x->parent->parent == nullptr){
                if (x->parent->left == x){
                    zig(x->parent);
                }
                else{
                    zag(x->parent);
                }
            }
            else{
                if (x->parent->left == x && x->parent->parent->left == x->parent){
                    zig_zig(x->parent->parent);
                }
                else if (x->parent->right == x && x->parent->parent->right == x->parent){
                    zag_zag(x->parent->parent);
                }
                else if (x->parent->left == x && x->parent->parent->right == x->parent){
                    zag_zig(x->parent->parent);
                }
                else{
                    zig_zag(x->parent->parent);
                }
            }
            splay(x);
        }

    int searchSplay(int x){
        if (info == x){
            splay(this);
            return 1;
        }
        if (x < info){
            if (left == nullptr){
                splay(this);
                return 0;
            }
            return left->searchSplay(x);
        }
        else {
            if (right == nullptr){
                splay(this);
                return 0;
            }
            return right->searchSplay(x);
        }
    }

    void insertSplay(int x){
        if (info == x){
            splay(this);
            prettyPrintfile(this);
            return;
        }
        if (x < info){
            if (left == nullptr){
                left = new Node(x, this);
                splay(left);
            }
            else{
                left->insertSplay(x);
            }
        }
        else {
            if (right == nullptr){
                right = new Node(x, this);
                splay(right);
            }
            else{
                right->insertSplay(x);
            }
        }
        prettyPrintfile(this);
        return;
    }
};

void prettyPrintfile(Node* node,int indent = 0, std::ostream& out = std::cout) {
    if (node->right) {
        prettyPrintfile(node->right,indent + 4, out);
    }
    if (indent) {
        out << std::setw(indent) << ' ';
    }
    if (node->right) out << " /\n" << std::setw(indent) << ' ';
    out << node->info << "\n";
    if (node->left) {
        out << std::setw(indent) << ' ' << " \\\n";
        prettyPrintfile(node->left,indent + 4, out);
    }
}
void print(Node* node, const std::string& suffix){
    std::string filename = "arbol" + suffix + ".txt";

    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        // Imprimir en el archivo
        prettyPrintfile(node, 0, outFile);
        outFile.close();
    } else {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
    }
}

bool contains(std::queue<int> q, int x) {
    while (!q.empty()) {
        if (q.front() == x) {
            return true; // El elemento x se encontró en la cola
        }
        q.pop(); // Avanza al siguiente elemento
    }
    return false; // El elemento x no está en la cola
}

bool contieneElemento(const std::vector<int>& vec, int x) {
    for (int n : vec) {
        if (n == x) {
            return true; // El elemento fue encontrado
        }
    }
    return false; // El elemento no fue encontrado
}

void permutarVector(std::vector<int>& vec) {
    // Inicializar el generador de números aleatorios
    std::random_device rd;
    std::mt19937 generador(rd());

    // Permutar aleatoriamente el vector
    std::shuffle(vec.begin(), vec.end(), generador);
}

int hora(){
        std::time_t tiempo_actual = std::time(nullptr);

        // Convertir el tiempo a la estructura tm (tiempo local)
        std::tm* tiempo_local = std::localtime(&tiempo_actual);

        // Mostrar la hora actual en formato HH:MM:SS
        std::cout << "Hora actual: " 
                << tiempo_local->tm_hour << ":"
                << tiempo_local->tm_min << ":"
                << tiempo_local->tm_sec << std::endl;

        return 0;
}

double calculaC(int N) {
    double sum = 0.0;
    for (int i = 1; i <= N; ++i) {
        sum += 1.0 / (i * i);
    }
    // Calcular C
    double C = 1.0 / sum;
    return C;
}

double f(int N,int i){
    double C = calculaC(N);
    return (C / ((i+1)*(i+1)));
}

//--------------------//
// main experimento 4 //
//--------------------//

/*
int experimento4(){
    std::string carpeta = "Exp_4";
    std::filesystem::create_directory(carpeta); // Crea la carpeta
    std::ofstream file;
    std::string nombreArchivo = carpeta + "/Experimento_4.csv";
    file.open(nombreArchivo, std::ios::app);
    file << "N Elementos, N Inserciones ABB, N Búsquedas ABB, N Splay\n";
    int N0 = 100000;
    for (int N=N0; N<=10*N0; N+=N0){        
        hora();
        std::cout<<"N= "<<N<<"\n";
        int M = 100*N;
        
        std::vector<int> A;
        std::vector<int> B;
        int count=0;

        while (A.size()<N){
            int x = rand() % (2 * N) + 1;
            if(!contieneElemento(A,x)){
                A.push_back(x);
            }
        }
        std::vector<int> C(A);
        sort(C.begin(), C.end());
        std::cout<<"vector A creado \n";
        for(int i=0;i<N;i++){
            for (int j=0;j<floor(M*f(N,i));j++){
                B.push_back(A[i]);
            }
        }
        std::cout<<"vector B creado \n";
        permutarVector(B);
        Node* ABB = new Node(A[0]);
        Node* Splay = new Node(A[0]);
        for(int i=1;i<N;i++){
            ABB->insertABB(C[i]);
            Splay=insertSplay(Splay,C[i]);

        }
        std::cout<<"inserciones completadas \n";
        for(int i=0;i<M;i++){
            ABB->searchABB(B[i]);
            Splay=searchSplay(Splay,B[i]);
        }
        std::cout<<"búsquedas completadas \n";
        file << N << "," <<  n_insert_total(ABB) << "," <<  n_search_total(ABB) << "," <<  n_rot_total(Splay) << "\n";
    }
    file.close();
    return 0;
}

//--------------------//
// main experimento 2 //
//--------------------//

int experimento2(){
    std::string carpeta = "Exp_2";
    std::filesystem::create_directory(carpeta); // Crea la carpeta
    std::ofstream file;
    std::string nombreArchivo = carpeta + "/Experimento_2.csv";
    file.open(nombreArchivo, std::ios::app);
    file << "N Elementos, N Inserciones ABB, N Búsquedas ABB, N Splay\n";
    int N0 = 100000;
    for (int N=N0; N<=10*N0; N+=N0){       
        hora();
        std::cout<<"N= "<<N<<"\n";
        int M = 100*N;
        
        std::vector<int> A;
        std::vector<int> B;
        int count=0;

        while (A.size()<N){
            int x = rand() % (2 * N) + 1;
            if(!contieneElemento(A,x)){
                A.push_back(x);
            }
        }
        //sort(A.begin(), A.end());
        std::cout<<"vector A creado \n";
        for(int i=0;i<N;i++){
            for (int j=0;j<floor(M*f(N,i));j++){
                B.push_back(A[i]);
            }
        }
        std::cout<<"vector B creado \n";
        permutarVector(B);
        Node* ABB = new Node(A[0]);
        Node* Splay = new Node(A[0]);
        for(int i=1;i<N;i++){
            ABB->insertABB(A[i]);
            Splay=insertSplay(Splay,A[i]);

        }
        std::cout<<"inserciones completadas \n";
        for(int i=0;i<M;i++){
            ABB->searchABB(B[i]);
            Splay=searchSplay(Splay,B[i]);
        }
        std::cout<<"búsquedas completadas \n";
        file << N << "," <<  n_insert_total(ABB) << "," <<  n_search_total(ABB) << "," <<  n_rot_total(Splay) << "\n";
    }
    file.close();
    return 0;
}

//--------------------//
// main experimento 3 //
//--------------------//

int experimento3(){
    std::string carpeta = "Exp_3";
    std::filesystem::create_directory(carpeta); // Crea la carpeta
    std::ofstream file;
    std::string nombreArchivo = carpeta + "/Experimento_3.csv";
    file.open(nombreArchivo, std::ios::app);
    file << "N Elementos, N Inserciones ABB, N Búsquedas ABB, N Splay\n";
    int N0 = 100000;
    for (int N=N0; N<=10*N0; N+=N0){
        hora();
        std::cout<<"N= "<<N<<"\n";
        int M = 100*N;
        
        std::vector<int> A;
        std::vector<int> B;
        int count=0;

        while (A.size()<N){
            int x = rand() % (2 * N) + 1;
            if(!contieneElemento(A,x)){
                A.push_back(x);
            }
        }
        sort(A.begin(), A.end());
        std::cout<<"vector A creado \n";
        for(int i=0;i<N;i++){
            for (int j=0;j<(M/N);j++){
                B.push_back(A[i]);
            }
        }
        std::cout<<"vector B creado \n";
        permutarVector(B);
        Node* ABB = new Node(A[0]);
        Node* Splay = new Node(A[0]);
        for(int i=1;i<N;i++){
            ABB->insertABB(A[i]);
            Splay=insertSplay(Splay,A[i]);

        }
        std::cout<<"inserciones completadas \n";
        for(int i=0;i<M;i++){
            ABB->searchABB(B[i]);
            Splay=searchSplay(Splay,B[i]);
        }
        std::cout<<"búsquedas completadas \n";
        file << N << "," <<  n_insert_total(ABB) << "," <<  n_search_total(ABB) << "," <<  n_rot_total(Splay) << "\n";
    }
    file.close();
    return 0;
}
*/

//--------------------//
// main experimento 1 //
//--------------------//

int experimento1(){
    std::string carpeta = "Exp_1";
    std::filesystem::create_directory(carpeta); // Crea la carpeta
    std::ofstream file;
    std::string nombreArchivo = carpeta + "/Experimento_1.csv";
    file.open(nombreArchivo, std::ios::app);
    file << "N Elementos, Insert ABB, Búsqueda ABB, Insert Splay, Búsqueda Splay\n";
    int N0 = 100000;
    float time_insert_ABB = 0;
    float time_search_ABB = 0;
    float time_insert_Splay = 0;
    float time_search_Splay = 0;
    for (int N=N0; N<=10*N0; N+=N0){        
        hora();
        std::cout<<"N= "<<N<<"\n";
        int M = 100*N;
        
        std::vector<int> A;
        std::vector<int> B;
        int count=0;

        while (A.size()<N){
            int x = rand() % (2 * N) + 1;
            if(!contieneElemento(A,x)){
                A.push_back(x);
            }
        }
        std::cout<<"vector A creado \n";
        for(int i=0;i<N;i++){
            for (int j=0;j<(M/N);j++){
                B.push_back(A[i]);
            }
        }
        std::cout<<"vector B creado \n";
        permutarVector(B);
        //Node* ABB = new Node(A[0]);
        Node* Splay = new Node(A[0]);
        for(int i=1;i<N;i++){
            //float start = clock();
            //ABB->insertABB(A[i]);
            //float end = clock();
            //time_insert_ABB += (end - start) / CLOCKS_PER_SEC;
            //start = clock();
            Splay->insertSplay(A[i]);
            //end = clock();
            //time_insert_Splay += (end - start) / CLOCKS_PER_SEC;
        }
        std::cout<<"inserciones completadas \n";
        for(int i=0;i<M;i++){
            //float start = clock();
            //ABB->searchABB(B[i]);
            //float end = clock();
            //time_search_ABB += (end - start) / CLOCKS_PER_SEC;
            //start = clock();
            Splay->insertSplay(B[i]);
            //end = clock();
            //time_search_Splay += (end - start) / CLOCKS_PER_SEC;
        }
        std::cout<<"búsquedas completadas \n";
        file << N << "," << time_insert_ABB << "," <<  time_search_ABB << "," <<  time_insert_Splay << "," << time_search_Splay << "\n";
    }
    file.close();
    return 0;
}

int main(){
    /*
    std::cout<<"Inicia Experimento 2\n";
    experimento2();
    std::cout<<"Inicia Experimento 3\n";
    experimento3();
    std::cout<<"Inicia Experimento 4\n";
    experimento4();
    */
    std::cout<<"Inicia Experimento 1\n";
    experimento1();
    return 0;
}