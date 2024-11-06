#include <iostream>
#include <fstream>
#include <set>
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
    Node* parent;
    Node* left;
    Node* right;

    Node(int x) : info(x), parent(nullptr), left(nullptr), right(nullptr) {}
    Node(int x, Node* p) : info(x), parent(p), left(nullptr), right(nullptr) {}
};

class ABB {
    public:
    Node* root = nullptr;

    ABB(int x){
        root = new Node(x);
    };

    void insertABB(int x){
        if (root == nullptr){
            root = new Node(x);
            return;
        }
        Node* current = this->root;
        while (current != nullptr){
            if (current->info == x){
                return;
            }
            if (x < current->info){
                if (current->left == nullptr){
                    current->left = new Node(x, current);
                    return;
                }
                current = current->left;
            }
            else {
                if (current->right == nullptr){
                    current->right = new Node(x, current);
                    return;
                }
                current = current->right;
            }
        }
    };

    int searchABB(int x){
        if (root == nullptr){
            return 0;
        }
        Node* current = root;
        while (current != nullptr){
            if (current->info == x){
                return 1;
            }
            if (x < current->info){
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return 0;
    };
};

class SplayTree {
    public:
    Node* root = nullptr;

    SplayTree(int x){
        root = new Node(x);
    };

    void zig(Node* x){
        Node* y = x->parent;
        y->left = x->right;
        if (y->left != nullptr){
            y->left->parent = y;
        }
        x->right = y;
        x->parent = nullptr;
        y->parent = x;
    };

    void zag(Node* x){
        Node* y = x->parent;
        y->right = x->left;
        if (y->right != nullptr){
            y->right->parent = y;
        }
        x->left = y;
        x->parent = nullptr;
        y->parent = x;
    };

    void zig_zig(Node* x){
        Node* y = x->parent;
        Node* z = y->parent;
        z->left = y->right;
        if (z->left != nullptr){
            z->left->parent = z;
        }
        y->left = x->right;
        if (y->left != nullptr){
            y->left->parent = y;
        }
        x->right = y;
        x->parent = z->parent;
        y->right = z;
        y->parent = x;
        z->parent = y;
        if (x->parent == nullptr){
            return;
        }
        else if (x->parent->left == z){
            x->parent->left = x;
        }
        else{
            x->parent->right = x;
        }
    };

    void zag_zag(Node* x){
        Node* y = x->parent;
        Node* z = y->parent;
        z->right = y->left;
        if (z->right != nullptr){
            z->right->parent = z;
        }
        y->right = x->left;
        if (y->right != nullptr){
            y->right->parent = y;
        }
        x->left = y;
        x->parent = z->parent;
        y->left = z;
        y->parent = x;
        z->parent = y;
        if (x->parent == nullptr){
            return;
        }
        else if (x->parent->left == z){
            x->parent->left = x;
        }
        else{
            x->parent->right = x;
        }
    };

    void zig_zag(Node* x){
        Node* y = x->parent;
        Node* z = y->parent;
        z->left = x->right;
        if (z->left != nullptr){
            z->left->parent = z;
        }
        y->right = x->left;
        if (y->right != nullptr){
            y->right->parent = y;
        }
        x->left = y;
        x->right = z;
        x->parent = z->parent;
        y->parent = x;
        z->parent = x;
        if (x->parent == nullptr){
            return;
        }
        else if (x->parent->left == z){
            x->parent->left = x;
        }
        else{
            x->parent->right = x;
        }
    };

    void zag_zig(Node* x){
        Node* y = x->parent;
        Node* z = y->parent;
        z->right = x->left;
        if (z->right != nullptr){
            z->right->parent = z;
        }
        y->left = x->right;
        if (y->left != nullptr){
            y->left->parent = y;
        }

        x->right = y;
        x->left = z;
        x->parent = z->parent;
        y->parent = x;
        z->parent = x;
        if (x->parent == nullptr){
            return;
        }
        else if (x->parent->left == z){
            x->parent->left = x;
        }
        else{
            x->parent->right = x;
        }
    };

    void splay(Node* x){
        while (x->parent != nullptr){
            if (x->parent->parent == nullptr){
                if (x->parent->left == x){
                    zig(x);
                }
                else{
                    zag(x);
                }
            }
            else{
                if (x->parent->left == x && x->parent->parent->left == x->parent){
                    zig_zig(x);
                }
                else if (x->parent->right == x && x->parent->parent->right == x->parent){
                    zag_zag(x);
                }
                else if (x->parent->left == x && x->parent->parent->right == x->parent){
                    zag_zig(x);
                }
                else{
                    zig_zag(x);
                }
            }
        }
        this->root = x;
    };

    int searchSplay(int x){
        if (root == nullptr){
            return 0;
        }
        Node* current = root;
        while (current != nullptr){
            if (current->info == x){
                splay(current);
                return 1;
            }
            if (x < current->info){
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return 0;
    };

    void insertSplay(int x){
        if (root == nullptr){
            root = new Node(x);
            return;
        }
        Node* current = this->root;
        while (current != nullptr){
            if (current->info == x){
                splay(current);
                return;
            }
            if (x < current->info){
                if (current->left == nullptr){
                    current->left = new Node(x, current);
                    splay(current->left);
                    return;
                }
                current = current->left;
            }
            else {
                if (current->right == nullptr){
                    current->right = new Node(x, current);
                    splay(current->right);
                    return;
                }
                current = current->right;
            }
        }
    };
};


void print2DUtil(Node* root, int space)
{
    // Base case
    if (root == nullptr)
        return;
 
    // Increase distance between levels
    space += 2;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    cout << endl;
    for (int i = 2; i < space; i++)
        cout << " ";
    cout << root->info << "\n";
 
    // Process left child
    print2DUtil(root->left, space);
};
 
// Wrapper over print2DUtil()
void print2D(Node* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
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
};
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
};

bool contains(std::queue<int> q, int x) {
    while (!q.empty()) {
        if (q.front() == x) {
            return true; // El elemento x se encontró en la cola
        }
        q.pop(); // Avanza al siguiente elemento
    }
    return false; // El elemento x no está en la cola
};

bool contieneElemento(const std::vector<int>& vec, int x) {
    for (int n : vec) {
        if (n == x) {
            return true; // El elemento fue encontrado
        }
    }
    return false; // El elemento no fue encontrado
};

void permutarVector(std::vector<int>& vec) {
    // Inicializar el generador de números aleatorios
    std::random_device rd;
    std::mt19937 generador(rd());

    // Permutar aleatoriamente el vector
    std::shuffle(vec.begin(), vec.end(), generador);
};

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
};

double calculaC(int N) {
    double sum = 0.0;
    for (int i = 1; i <= N; ++i) {
        sum += 1.0 / (i * i);
    }
    // Calcular C
    double C = 1.0 / sum;
    return C;
};

double f(int N,int i){
    double C = calculaC(N);
    return (C / ((i+1)*(i+1)));
};

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
        ABB* abb = new ABB(A[0]);
        hora();
        SplayTree* splay = new SplayTree(A[0]);
        cout<<"raiz "<<splay->root->info<<"\n";
        float start = 0;
        float end = 0;
        for(int i=1;i<N;i++){
            start = clock();
            abb->insertABB(A[i]);
            end = clock();
            time_insert_ABB += (end - start) / CLOCKS_PER_SEC;
            start = clock();
            //cout<<"insertando "<<A[i]<<"\n";
            splay->insertSplay(A[i]);
            //print2D(Splay->root);
            end = clock();
            time_insert_Splay += (end - start) / CLOCKS_PER_SEC;
        };
        std::cout<<"inserciones completadas \n";
        hora();
        for(int i=0;i<M;i++){
            start = clock();
            abb->searchABB(B[i]);
            end = clock();
            time_search_ABB += (end - start) / CLOCKS_PER_SEC;
            start = clock();
            splay->searchSplay(B[i]);
            end = clock();
            time_search_Splay += (end - start) / CLOCKS_PER_SEC;
        }
        std::cout<<"búsquedas completadas \n";
        hora();
        file << N << "," << time_insert_ABB << "," <<  time_search_ABB << "," <<  time_insert_Splay << "," << time_search_Splay << "\n";
    }
    file.close();
    return 0;
}
*/


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
    std::string carpeta = "Exp_1";
    std::filesystem::create_directory(carpeta); // Crea la carpeta
    std::ofstream file;
    std::string nombreArchivo = carpeta + "/Experimento_1.csv";
    file.open(nombreArchivo, std::ios::app);
    file << "N Elementos, Insert ABB, Búsqueda ABB, Insert Splay, Búsqueda Splay\n";
    //experimento1();
    int N = 10000000 * 0.1;
    int M = N * 100;
    std::set<int> A;
    std::random_device rd;
    std::mt19937 gen(rd());
    //std::uniform_int_distribution<int> dis(1, 2 * N);

    while (A.size() < N) {
        int num = rand() % (2 * N) + 1;
        A.insert(num);
    }
    cout << "set A creado \n";
    std::vector<int> B(M, 0);
    for (auto it = A.begin(); it != A.end(); ++it) {
        for (int j = 0; j < M / N; ++j) {
            B[j] = *it;
        }
    }
    std::shuffle(B.begin(), B.end(), gen);
    cout << "vector B creado \n";
    float time_insert_ABB = 0;
    float time_search_ABB = 0;
    float time_insert_Splay = 0;
    float time_search_Splay = 0;
    hora();
    float start = clock();
    ABB* abb = new ABB(*A.begin());
    float end = clock();
    time_insert_ABB += (end - start) / CLOCKS_PER_SEC;
    //start = clock();
    //SplayTree* splay = new SplayTree(*A.begin());
    //end = clock();
    time_insert_Splay += (end - start) / CLOCKS_PER_SEC;
    for (auto it = std::next(A.begin()); it != A.end(); ++it) {
        start = clock();
        abb->insertABB(*it);
        end = clock();
        time_insert_ABB += (end - start) / CLOCKS_PER_SEC;
        //cout << "insertando " << *it << "\n";
        //start = clock();
        //splay->insertSplay(*it);
        //end = clock();
        //time_insert_Splay += (end - start) / CLOCKS_PER_SEC;
    }
    hora();
    for (int i = 0; i < M; ++i) {
        start = clock();
        abb->searchABB(B[i]);
        end = clock();
        time_search_ABB += (end - start) / CLOCKS_PER_SEC;
        //start = clock();
        //splay->searchSplay(B[i]);
        //end = clock();
        //time_search_Splay += (end - start) / CLOCKS_PER_SEC;
    }
    hora();
    file << N << "," << time_insert_ABB << "," <<  time_search_ABB << "," <<  time_insert_Splay << "," << time_search_Splay << "\n";
    return 0;
}