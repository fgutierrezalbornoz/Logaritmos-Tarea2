#include <iostream>
#include <fstream>
#include <set>
#include <unordered_set>
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
#include <chrono>

using namespace std;

class Node {
    public:
    int info;
    Node* parent;
    Node* left;
    Node* right;

    Node(int x) : info(x), parent(nullptr), left(nullptr), right(nullptr) {}
    Node(int x, Node* p) : info(x), parent(p), left(nullptr), right(nullptr) {}

    void clean(){
        if (this->left != nullptr){
            this->left->clean();
            delete this->left;
        }
        if (this->right != nullptr){
            this->right->clean();
            delete this->right;
        }
    };
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
                current = nullptr;
                delete current;
                return;
            }
            if (x < current->info){
                if (current->left == nullptr){
                    current->left = new Node(x, current);
                    current = nullptr;
                    delete current;
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
                current = nullptr;
                delete current;
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

    void cleanABB(){
        if (this->root != nullptr){
            this->root->clean();
            delete this->root;
        }
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
        y = nullptr;
        delete y;
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
        y = nullptr;
        delete y;
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
            y = nullptr;
            delete y;
            z = nullptr;
            delete z;
            return;
        }
        else if (x->parent->left == z){
            x->parent->left = x;
        }
        else{
            x->parent->right = x;
        }
        y = nullptr;
        delete y;
        z = nullptr;
        delete z;
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
             y = nullptr;
            delete y;
            z = nullptr;
            delete z;
            return;
        }
        else if (x->parent->left == z){
            x->parent->left = x;
        }
        else{
            x->parent->right = x;
        }
        y = nullptr;
        delete y;
        z = nullptr;
        delete z;
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
            y = nullptr;
            delete y;
            z = nullptr;
            delete z;
            return;
        }
        else if (x->parent->left == z){
            x->parent->left = x;
        }
        else{
            x->parent->right = x;
        }
        y = nullptr;
        delete y;
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
            y = nullptr;
            delete y;
            z = nullptr;
            delete z;
            return;
        }
        else if (x->parent->left == z){
            x->parent->left = x;
        }
        else{
            x->parent->right = x;
        }
        y = nullptr;
        delete y;
        z = nullptr;
        delete z;
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
        if (root->info == x){
            return 1;
        }
        Node* current = root;
        while (current != nullptr){
            if (current->info == x){
                splay(current);
                current = nullptr;
                delete current;
                return 1;
            }
            if (x < current->info){
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        delete current;
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
                current = nullptr;
                delete current;
                return;
            }
            if (x < current->info){
                if (current->left == nullptr){
                    current->left = new Node(x, current);
                    splay(current->left);
                    current = nullptr;
                    delete current;
                    return;
                }
                current = current->left;
            }
            else {
                if (current->right == nullptr){
                    current->right = new Node(x, current);
                    splay(current->right);
                    current = nullptr;
                    delete current;
                    return;
                }
                current = current->right;
            }
        }
        delete current;
    };

    void cleanSplay(){
        if (this->root != nullptr){
            this->root->clean();
            delete this->root;
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

std::string hora() {
    // Obtener el tiempo actual con precisión de milisegundos
    auto ahora = std::chrono::system_clock::now();
    auto tiempo_actual = std::chrono::system_clock::to_time_t(ahora);
    auto tiempo_local = std::localtime(&tiempo_actual);

    // Extraer los milisegundos
    auto duracion = ahora.time_since_epoch();
    auto milisegundos = std::chrono::duration_cast<std::chrono::milliseconds>(duracion) % 1000;

    // Formatear la cadena de tiempo
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << tiempo_local->tm_hour << ":"
        << std::setw(2) << std::setfill('0') << tiempo_local->tm_min << ":"
        << std::setw(2) << std::setfill('0') << tiempo_local->tm_sec << "."
        << std::setw(3) << std::setfill('0') << milisegundos.count();

    return oss.str();
}

double calculaC(int N) {
    double sum = 0.0;
    for (int i = 1; i <= N; ++i) {
        sum += 1.0 / ((double)i * (double)i);
    }
    // Calcular C
    
    double C = 1.0 / sum;
    return C;
}

double f(int N,int i, double C){
    return (C / (((double)i+1)*((double)i+1)));
}


//--------------------//
// main experimento 1 //
//--------------------//

int experimento1(int N0, int Nf){
    std::string carpeta = "Exp_1";
    std::filesystem::create_directory(carpeta); // Crea la carpeta
    std::ofstream file;
    std::string nombreArchivo = carpeta + "/Experimento_1.csv";
    file.open(nombreArchivo, std::ios::app);
    file << "N Elementos, hora inicio ABB, hora término ABB, hora inicio Splay, hora término Splay, tiempo búsqueda ABB, tiempo búsqueda Splay Tree\n";
    file.close();
    //int N0 = 100000;
    //for (int N=N0; N<=10*N0; N+=N0){   
    std::clock_t start;
    double duration_abb = 0;
    double duration_splay = 0;
    for (int N=N0; N<=Nf; N+=N0){   
        file.open(nombreArchivo, std::ios::app);     
        std::cout<<hora()<<"\n";
        std::cout<<"N= "<<N<<"\n";
        int M = 100*N;
        
        std::unordered_set<int> A;
        std::vector<int> B;
        B.reserve(M);
        int count=0;

        while (A.size()<N){
            int x = rand() % (2 * N) + 1;
            A.insert(x);
        }
        std::cout<<"vector A creado \n";
        for(auto it = A.begin(); it != A.end(); ++it){
            for (int j=0;j<(M/N);j++){
                B.push_back(*it);
            }
        }
        permutarVector(B);
        std::cout<<"vector B creado y permutado \n";
        ABB* abb = new ABB(*A.begin());
        SplayTree* Splay = new SplayTree(*A.begin());
        for(auto it = std::next(A.begin()); it != A.end(); ++it){
            abb->insertABB(*it);
            Splay->insertSplay(*it);

        }
        std::cout<<"inserciones completadas \n";
        std::string tiABB=hora();
        std::cout<<tiABB<<"\n";
        start = std::clock();
        for(int i=0;i<M;i++){
            abb->searchABB(B[i]);
        }
        duration_abb += ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        std::string tfABB=hora();
        std::cout<<"terminan las búsquedas en ABB "<<tfABB<<"\n";
        std::string tiSplay=hora();
        std::cout<<tiSplay<<"\n";
        start = std::clock();
        for(int i=0;i<M;i++){
            Splay->searchSplay(B[i]);
        }
        duration_splay += ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        std::string tfSplay=hora();
        std::cout<<"terminan las búsquedas en Splay "<<tfSplay<<"\n";
        
        
        std::cout<<"búsquedas completadas \n";
        file << N << ","<<tiABB<<","<<tfABB<< ","<<tiSplay<<","<<tfSplay<<","<< duration_abb << "," << duration_splay <<","<<"\n";
        file.close();
        abb->cleanABB();
        Splay->cleanSplay();
    }
    
    return 0;
}

//--------------------//
// main experimento 2 //
//--------------------//

int experimento2(int N0, int Nf){
    std::string carpeta = "Exp_2";
    std::filesystem::create_directory(carpeta); // Crea la carpeta
    std::ofstream file;
    std::string nombreArchivo = carpeta + "/Experimento_2.csv";
    file.open(nombreArchivo, std::ios::app);
    file << "N Elementos, hora inicio ABB, hora término ABB, hora inicio Splay, hora término Splay, tiempo búsqueda ABB, tiempo búsqueda Splay Tree\n";
    file.close();
    //int N0 = 100000;
    //for (int N=N0; N<=10*N0; N+=N0){ 
    std::clock_t start;
    double duration_abb = 0;
    double duration_splay = 0;
    for (int N=N0; N<=Nf; N+=N0){ 
        file.open(nombreArchivo, std::ios::app);      
        std::cout<<hora()<<"\n";
        std::cout<<"N= "<<N<<"\n";
        int M = 100*N;
        
        std::unordered_set<int> A;
        std::vector<int> B;
        int count=0;

        while (A.size()<N){
            int x = rand() % (2 * N) + 1;
            A.insert(x);
        }
        std::cout<<"vector A creado \n";
        double C=calculaC(N);
        std::cout<<"C = "<<C<<"\n";
        for(auto it = A.begin(); it != A.end(); ++it){
            int i = std::distance(A.begin(), it);
            double j_aux = floor(M*f(N,i,C));
            for (double j=0;j<j_aux;j++){
                B.push_back(*it);
            }
        }
        std::cout<<"El vector A tiene un tamaño de "<<A.size()<<"\n";
        std::cout<<"El vector B tiene un tamaño de "<<B.size()<<"\n";
        permutarVector(B);
        std::cout<<"vector B creado y permutado \n";
        ABB* abb = new ABB(*A.begin());
        SplayTree* Splay = new SplayTree(*A.begin());
        for(auto it = std::next(A.begin()); it != A.end(); ++it){
            abb->insertABB(*it);
            Splay->insertSplay(*it);

        }
        
        std::cout<<"inserciones completadas \n";
        std::string tiABB=hora();
        std::cout<<tiABB<<"\n";
        start = std::clock();
        for(int i=0;i<M;i++){
            abb->searchABB(B[i]);
        }
        duration_abb += ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        std::string tfABB=hora();
        std::cout<<"terminan las búsquedas en ABB "<<tfABB<<"\n";
        std::string tiSplay=hora();
        std::cout<<tiSplay<<"\n";
        start = std::clock();
        for(int i=0;i<M;i++){
            Splay->searchSplay(B[i]);
        }
        duration_splay += ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        std::string tfSplay=hora();
        std::cout<<"terminan las búsquedas en Splay "<<tfSplay<<"\n";
        
        
        std::cout<<"búsquedas completadas \n";
        file << N << ","<<tiABB<<","<<tfABB<< ","<<tiSplay<<","<<tfSplay<<","<< duration_abb << "," << duration_splay <<","<<"\n";
        file.close();
        abb->cleanABB();
        Splay->cleanSplay();
    }
    return 0;
}

//--------------------//
// main experimento 3 //
//--------------------//

int experimento3() {
    std::string carpeta = "Exp_3";
    std::filesystem::create_directory(carpeta);  // Crea la carpeta
    std::ofstream file(carpeta + "/Experimento_3.csv", std::ios::app);
    file << "N Elementos, tiempo búsqueda ABB, tiempo búsqueda Splay Tree\n";

    int N0 = 300000;
    for (int N = N0; N <= 1000000; N += 100000) {
        std::cout << hora() << "\n";
        std::cout << "N = " << N << "\n";
        int M = 100 * N;

        std::set<int> A;
        std::vector<int> B;
        B.reserve(M);

        // Generar elementos en A
        while (A.size() < N) {
            int x = rand() % (2 * N) + 1;
            A.insert(x);
        }
        std::cout << "vector A creado \n";

        // Generar el vector B con M/N copias de cada elemento de A
        for (int element : A) {
            B.insert(B.end(), M / N, element);
        }
        permutarVector(B);  // Permutar el vector B
        std::cout << "vector B creado y permutado \n";
        std::cout << hora() << "\n";
        // Crear y poblar los árboles
        ABB* abb = new ABB(*A.begin());
        SplayTree* splay = new SplayTree(*A.begin());
        for (auto it = std::next(A.begin()); it != A.end(); ++it) {
            abb->insertABB(*it);
            splay->insertSplay(*it);
        }
        std::cout << "inserciones completadas \n";
        std::cout << hora() << "\n";
        // Medir tiempo de búsqueda en ABB
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < M; i++) {
            abb->searchABB(B[i]);
            if (i % 100000 == 0) {
                std::cout << "Búsqueda " << i << " en ABB \n";
            }
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_abb = end_time - start_time;
        cout << "terminan las búsquedas en ABB \n";
        cout << hora() << "\n";
        // Medir tiempo de búsqueda en Splay Tree
        start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < M; i++) {
            splay->searchSplay(B[i]);
        }
        end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_splay = end_time - start_time;

        // Guardar resultados en el archivo
        file << N << "," << duration_abb.count() << "," << duration_splay.count() << "\n";

        std::cout << "búsquedas completadas \n";
        
        // Limpiar memoria
        abb->cleanABB();
        splay->cleanSplay();
        delete abb;
        delete splay;
    }

    file.close();
    return 0;
}

//--------------------//
// main experimento 4 //
//--------------------//

int experimento4(){
    std::string carpeta = "Exp_4";
    std::filesystem::create_directory(carpeta); // Crea la carpeta
    std::ofstream file;
    std::string nombreArchivo = carpeta + "/Experimento_4.csv";
    file.open(nombreArchivo, std::ios::app);
    file << "N Elementos, tiempo búsqueda ABB, tiempo búsqueda Splay Tree\n";
    file.close();
    int N0 = 100000;
    //for (int N=N0; N<=10*N0; N+=N0){
    std::clock_t start;
    double duration_abb = 0;
    double duration_splay = 0;
    for (int N=N0; N<=10*N0; N+=N0){  
        file.open(nombreArchivo, std::ios::app);      
        hora();
        std::cout<<"N= "<<N<<"\n";
        int M = 100*N;
        
        std::vector<int> A;
        A.reserve(N);
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
        double Cf=calculaC(N);
        for(int i=0;i<N;i++){
            double j_aux = floor(M*f(N,i,Cf));
            for (double j=0;j<j_aux;j++){
                B.push_back(A[i]);
            }
        }
        permutarVector(B);
        std::cout<<"vector B creado y permutado \n";
        ABB* abb = new ABB(A[0]);
        SplayTree* Splay = new SplayTree(A[0]);
        for(int i=1;i<N;i++){
            abb->insertABB(C[i]);
            Splay->insertSplay(C[i]);

        }
        std::cout<<"inserciones completadas \n";
        hora();
        start = std::clock();
        for(int i = 0; i < B.size() ; i++){
            abb->searchABB(B[i]);
        }
        duration_abb = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        hora();
        start = std::clock();
        for (int i = 0; i < B.size(); i++){
            Splay->searchSplay(B[i]);
        }
        duration_splay = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        std::cout<<"búsquedas completadas \n";
        file << N << "," << duration_abb << "," << duration_splay <<","<<"\n";
        file.close();
        abb->cleanABB();
        Splay->cleanSplay();
    }
    
    return 0;
}


int main(){
    //int N = 100000;
    //std::cout<<"Inicia Experimento 1\n";
    //experimento1(N, 10*N);
    //std::cout<<"Inicia Experimento 2\n";
    //experimento2(N, 10*N);
    std::cout<<"Inicia Experimento 3\n";
    experimento3();
    std::cout<<"Inicia Experimento 4\n";
    experimento4();
    return 0;
}