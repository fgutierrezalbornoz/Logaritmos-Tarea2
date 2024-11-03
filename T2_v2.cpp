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
    Node* left = nullptr;
    Node* right = nullptr;
    int n_insert=0;
    int n_search=0;
    int n_rot=0;

    Node(int x){
        info = x;
    }
    Node(int x, Node* l, Node* r){
        info = x;
        left = l;
        right = r;
    }

    int searchABB(int x){
        n_search++;
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
        n_insert++;
        if (searchABB(x)){
            std::cout<<x<<" ya tiene un nodo asignado\n";
            return;
        }
        if (x<info){
            if(left==nullptr){
                left = new Node(x);
                return;
            }
            left->insertABB(x);
            return;
        }
        if(right==nullptr){
            right = new Node(x);
            return;
        }
        right->insertABB(x);
        return;
    }
};


Node* zig(Node* node) {
    node->n_rot++;
    Node* y = node->left;
    node->left = y->right;
    y->right = node;
    return y;
}

Node* zag(Node* node) {
    node->n_rot++;
    Node* y = node->right;
    node->right = y->left;
    y->left = node;
    return y;
}

// Rotación zig-zig (doble derecha)
Node* zigZig(Node* node) {
    // Verificar que node y sus subnodos necesarios no sean nullptr
    if (node == nullptr || node->left == nullptr || node->left->left == nullptr) {
        return node;  // No se puede realizar la rotación zig-zig
    }
    return zig(zig(node)); 
}

// Rotación zag-zag (doble izquierda)
Node* zagZag(Node* node) {
    if (node == nullptr || node->right == nullptr || node->right->right == nullptr) {
        return node;  // No se puede realizar la rotación zag-zag
    }
    return zag(zag(node)); // Realizar la segunda rotación zag en el nodo actual
}

// Rotación zig-zag (derecha-izquierda)
Node* zigZag(Node* node) {
    if (node == nullptr || node->left == nullptr || node->left->right == nullptr) {
        std::cout<<"no se puede hacer el zigzag\n";
        return node;  // No se puede realizar la rotación zig-zag
    }
    node->left = zag(node->left); // Realizar la primera rotación zag en el hijo izquierdo
    return zig(node); // Realizar la segunda rotación zig en el nodo actual
}

// Rotación zag-zig (izquierda-derecha)
Node* zagZig(Node* node) {
    if (node == nullptr || node->right == nullptr || node->right->left == nullptr) {
        std::cout<<"no se puede hacer el zagzig\n";
        return node;  // No se puede realizar la rotación zag-zig
    }
    node->right = zig(node->right); // Realizar la primera rotación zig en el hijo derecho
    return zag(node); // Realizar la segunda rotación zag en el nodo actual             
}
    
Node* splay(Node* root, int key) {
    if (root == nullptr || root->info == key)
        return root;

    if (root->info > key) {
        if (root->left == nullptr)
            return root;
        if (root->left->info > key) {
            root->left->left = splay(root->left->left, key);
            root = zig(root);
        }
        else if (root->left->info < key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != nullptr)
                root->left = zag(root->left);
        }
        return (root->left == nullptr) ? root : zig(root);
    }
    else {
        if (root->right == nullptr)
            return root;
        if (root->right->info > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != nullptr)
                root->right = zig(root->right);
        }
        else if (root->right->info < key) {
            root->right->right = splay(root->right->right, key);
            root = zag(root);
        }
        return (root->right == nullptr) ? root : zag(root);
    }
}
Node* searchSplay(Node* root, int x) {
    if (!root) {
        return nullptr;
    }
    return splay(root, x);
}
Node* insertSplay(Node* root, int x){
    root->insertABB(x);
    return splay(root, x);
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

int n_insert_total(Node* node){
    if (node == nullptr)
        return 0;
    return (node->n_insert + n_insert_total(node->left) + n_insert_total(node->right));
}

int n_search_total(Node* node){
    if (node == nullptr)
        return 0;
    return (node->n_search + n_search_total(node->left) + n_search_total(node->right));
}

int n_rot_total(Node* node){
    if (node == nullptr)
        return 0;
    return (node->n_rot + n_rot_total(node->left) + n_rot_total(node->right));
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


int main(){
    std::string carpeta = "Exp_1";
    std::filesystem::create_directory(carpeta); // Crea la carpeta
    std::ofstream file;
    std::string nombreArchivo = carpeta + "/Experimento_1.csv";
    file.open(nombreArchivo, std::ios::app);
    file << "N Elementos, N Inserciones ABB, N Búsquedas ABB, N Splay\n";
    int N0 = 100000;
    //for (int N=N0; N<=10*N0; N+=N0){
    for (int N=N0; N<=N0; N+=N0){
        
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
        file << N << "," <<  n_insert_total(ABB) << "," <<  n_search_total(ABB) << "," <<  n_rot_total << "\n";
    }
    file.close();
    return 0;
}
    //-------------------//
    // main para testing //
    //-------------------//

//int main(){
    //-------------//
    // testing ABB //
    //-------------//

    /* int x = rand() % 100 + 1;
    int i = 0;
    Node* ABB = new Node(x);
    while (i<80){
        ABB->insertABB(rand() % 100 + 1);
        i++;
    }
    print(ABB, "test_ABB");
    std::cout<<"\n";
    std::cout<<"está el 5? "<<ABB->searchABB(5)<<"\n";
    std::cout<<"está el 10? "<<ABB->searchABB(10)<<"\n"; */

    //--------------------//
    // testing rotaciones //
    //--------------------//

    /* int y = rand() % 50 + 1;
    int i = 0;
    Node* Splay = new Node(y);
    std::queue<int> q;
    std::cout<<y<<" ";
    int x;
    while (i<30){
        x = rand() % 50 + 1;
        if (!contains(q, x)){
            q.push(x);
            i++;
        }
    }
    int z;
    while (!q.empty()){
        z = q.front();
        q.pop();
        std::cout<<z<<" ";
        Splay = insertSplay(Splay, z);
    }
    std::cout<<"\ninserta 29\n";
    Splay = insertSplay(Splay, 29);
    print(Splay, std::to_string(y));
    std::cout<<"zagzag\n";
    Splay = zagZag(Splay);
    print(Splay, std::to_string(y) + "zagzag");
    std::cout<<"zigzag\n";
    Splay = zigZag(Splay);
    print(Splay, std::to_string(y) + "zigzag");
    std::cout<<"zigzig\n";
    Splay = zigZig(Splay);
    print(Splay, std::to_string(y) + "zigzig");
    std::cout<<"zagzig\n";
    Splay = zagZig(Splay);
    print(Splay, std::to_string(y) + "zagzig"); */

    //---------------//
    // testing splay //
    //---------------//

    /* Node* S = new Node(10);

    S->left = new Node(6);
    S->left->left = new Node(4);
    S->left->left->left= new Node(3);
    S->left->left->right= new Node(5);
    S->left->right = new Node(8);
    S->left->right->left= new Node(7);
    S->left->right->right= new Node(9);
    S->right = new Node(14);
    S->right->left = new Node(12);
    S->right->left->left= new Node(11);
    S->right->left->right= new Node(13);
    S->right->right = new Node(16);
    S->right->right->left= new Node(15);
    S->right->right->right= new Node(17);
    S->right->right->right->right= new Node(18);
    print(S,"test_splay_inicio");
    S = splay(S, 18);
    print(S, "test_splay_18"); */


    //----------------//
    // testing insert //
    //----------------//

    /* int x = rand() % 50 + 1;
    int i = 0;
    int j = 0;
    Node* Splay = new Node(x);
    std::queue<int> q;
    q.push(x);
    std::cout<<x<<" ";
    print(Splay,"insert_"+std::to_string(j));
    while (i<30){
        x = rand() % 50 + 1;
        //Splay.insert(rand() % 100 + 1);
        if (!contains(q, x)){
            q.push(x);
            i++;
        }
        
    }
    int y;
    j=1;
    q.pop();
    
    while (!q.empty()){
        y = q.front();
        q.pop();
        std::cout<<y<<" ";
        Splay = insertSplay(Splay,y);
        print(Splay,"insert_"+std::to_string(j));
        j++;
    }
    std::cout<<"\n"; */

    //----------------//
    // testing search //   Esto funciona teniendo descomentado el test anterior
    //----------------//

    /* Splay = searchSplay(Splay, 41);
    print(Splay, "busqueda_41");
    Splay = searchSplay(Splay, 60);
    print(Splay, "busqueda_60"); */
//    return 0;
//} 