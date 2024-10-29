#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <iomanip> //para printpretty
#include <queue> //para print vertical
#include <string>

class ABB {
public:
    int data;  
    ABB* left = nullptr;
    ABB* right = nullptr;

    ABB(int x){
        data = x;
    }
    ABB(int x, ABB* l, ABB* r){
        data = x;
        left = l;
        right = r;
    }
    int search(int x){
        if (x == data){
            return 1;
        }
        if (x < data){
            if (left == nullptr){
                return 0;
            }
            return left->search(x);
        }
        else {
            if (right == nullptr){
                return 0;
            }
            return right->search(x);
        }
    }
    void insert(int x){
        
        if (search(x)){
            std::cout<<x<<" ya tiene un nodo asignado\n";
            return;
        }
        if (x<data){
            if(left==nullptr){
                std::cout<<"ABB insert\n";
                left = new ABB(x);
                return;
            }
            left->insert(x);
            return;
        }
        if(right==nullptr){
            std::cout<<"ABB insert\n";
            right = new ABB(x);
            return;
        }
        right->insert(x);
        return;
    }
    void printPO(){
        std::cout<<"raíz\n";
        std::cout<<data<<" ";
        std::cout<<"subárbol izquierdo\n";
        if(left!=nullptr){
            left->printPO();
        }
        std::cout<<"subárbol derecho\n";
        if(right!=nullptr){
            right->printPO();
        }
        return;
    }
    void printIO(){
        if(left!=nullptr){
            left->printIO();
        }
        std::cout<<data<<" ";
        if(right!=nullptr){
            right->printIO();
        }
        return;
    }
    int getHeight() const {
        if (!this) return 0;
        int leftHeight = left ? left->getHeight() : 0;
        int rightHeight = right ? right->getHeight() : 0;
        return 1 + std::max(leftHeight, rightHeight);
    }

    void printVertical() {
        if (!this) return;

        std::queue<std::pair<const ABB*, int>> q;
        int currentLevel = 0;
        q.push({this, currentLevel});

        while (!q.empty()) {
            auto [abb, level] = q.front();
            q.pop();

            if (level != currentLevel) {
                std::cout << "\n";
                currentLevel = level;
            }
            std::cout << " " << abb->data << " ";

            if (abb->left) q.push({abb->left, level + 1});
            if (abb->right) q.push({abb->right, level + 1});
        }
        std::cout << "\n";
    }
    void prettyPrint(int indent = 0) const {
        if (right) {
            right->prettyPrint(indent + 4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (right) std::cout << " /\n" << std::setw(indent) << ' ';
        std::cout << data << "\n ";
        if (left) {
            std::cout << std::setw(indent) << ' ' << " \\\n";
            left->prettyPrint(indent + 4);
        }
    }
    void prettyPrintfile(int indent = 0, std::ostream& out = std::cout) const {
        if (right) {
            right->prettyPrintfile(indent + 4, out);
        }
        if (indent) {
            out << std::setw(indent) << ' ';
        }
        if (right) out << " /\n" << std::setw(indent) << ' ';
        out << data << "\n";
        if (left) {
            out << std::setw(indent) << ' ' << " \\\n";
            left->prettyPrintfile(indent + 4, out);
        }
    }
};

void showABB(ABB *t,int counter){
	if(t==NULL){
		return;
		
	}
	else{
		showABB(t ->right,counter+1);
		for(int i=0;i<counter;i++){
			printf("   ");
		}
		printf("%d-----\n",t->data);
		showABB(t->left,counter+1);
	}
}

class Node{
public:
    int data;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int x):data(x){}
};

class Splay {
public:
    ABB* root;

    Splay(int x) : root(new ABB(x)) {}

    // Rotación zig (rotación a la derecha)
    ABB* zig(ABB* node) {
        ABB* leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;
        return leftChild;
    }

    // Rotación zag (rotación a la izquierda)
    ABB* zag(ABB* node) {
        ABB* rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;
        return rightChild;
    }

    // Rotación zig-zig (doble derecha)
    ABB* zigZig(ABB* node) {
    // Verificar que node y sus subnodos necesarios no sean nullptr
    if (node == nullptr || node->left == nullptr || node->left->left == nullptr) {
        return node;  // No se puede realizar la rotación zig-zig
    }
    return zig(zig(node)); 
}

    // Rotación zag-zag (doble izquierda)
    ABB* zagZag(ABB* node) {
        if (node == nullptr || node->right == nullptr || node->right->right == nullptr) {
            return node;  // No se puede realizar la rotación zag-zag
        }
        return zag(zag(node)); // Realizar la segunda rotación zag en el nodo actual
    }

    // Rotación zig-zag (derecha-izquierda)
    ABB* zigZag(ABB* node) {
        if (node == nullptr || node->left == nullptr || node->left->right == nullptr) {
            std::cout<<"no se puede hacer el zigzag\n";
            return node;  // No se puede realizar la rotación zig-zag
        }
        node->left = zag(node->left); // Realizar la primera rotación zag en el hijo izquierdo
        return zig(node); // Realizar la segunda rotación zig en el nodo actual
    }

    // Rotación zag-zig (izquierda-derecha)
    ABB* zagZig(ABB* node) {
        if (node == nullptr || node->right == nullptr || node->right->left == nullptr) {
            std::cout<<"no se puede hacer el zagzig\n";
            return node;  // No se puede realizar la rotación zag-zig
        }
        node->right = zig(node->right); // Realizar la primera rotación zig en el hijo derecho
        return zag(node); // Realizar la segunda rotación zag en el nodo actual             
    }

    // Función para hacer splay de un nodo con un valor dado
    ABB* splay(ABB* node, int key) {
        if (node==nullptr||node->data==key){
            return node;
        }
        if (node->data > key){
            if (node->left == nullptr) return node;
            if (node->left->data == key){
                return zig(node);
            }
            else if (node->left->data > key){
                if (node->left->left->data == key){
                    node = zigZig(node);
                    return node;
                }
                /* else{ //if (node->left->left->data > key){
                    node->left = splay(node->left, key);
                    return splay(node,key);
                } */
            }
            else{
                if (node->left->right->data == key){
                    node = zigZag(node);
                    return node;
                }
            }
            node->left = splay(node->left, key);
            return splay(node,key);
        }
        else{
            if (node->right == nullptr) return node;
            if (node->right->data == key){
                node = zag(node);
                return node;
            }
            else if (node->right->data > key){
                if (node->right->left->data == key){
                    node = zagZig(node);
                    return node;
                }
                /* else if (node->right->left->data < key){
                    node->right = splay(node->right,key);
                    return node;
                } */
            }
            else{
                if (node->right->right->data == key){
                    node = zagZag(node);
                    return node;
                }
            }
            node->right = splay(node->right,key);
            return splay(node,key);
        }
    }
    // Método público para hacer splay en la raíz
    void splay(int key) {
        root = splay(root, key);
    }

    ABB* insert(ABB* root, int key) {
        root->insert(key);
        root = splay(root,key);
        return root;
    }
    void insert(int key) {
        root = insert(root,key);
    }
    ABB* search(int x) {
        // Si el árbol está vacío, retornar nullptr
        if (!root) {
            return nullptr;
        }
        
        // Aplicar splay en el nodo más cercano al valor buscado (o en el nodo mismo si se encuentra)
        root = splay(root, x);

        // Verificar si el valor en la raíz es el valor buscado
        if (root->data == x) {
            return root;  // El valor se ha encontrado, y está en la raíz
        } else {
            return nullptr;  // El valor no se encuentra en el árbol
        }
    }
    void print(const std::string& suffix){
        std::string filename = "arbol" + suffix + ".txt";
        /* root->prettyPrint();
        std::cout<<"\n"; */
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            // Imprimir en el archivo
            root->prettyPrintfile(0, outFile);
            outFile.close();
        } else {
            std::cerr << "No se pudo abrir el archivo." << std::endl;
        }
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
}

int main(){
    // testing ABB
    /* int x = rand() % 100 + 1;
    int i = 0;
    ABB ABB(x);
    while (i<80){
        ABB.insert(rand() % 100 + 1);
        i++;
    }
    ABB.print();
    std::cout<<"\n";
    std::cout<<"está el 5? "<<ABB.search(5)<<"\n";
    std::cout<<"está el 10? "<<ABB.search(10)<<"\n"; */

    //testing rotaciones
    /* int y = rand() % 50 + 1;
    int i = 0;
    Splay Splay(y);
    std::queue<int> q;
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
        Splay.insert(z);
    }
    std::cout<<"inserta 31\n";
    Splay.insert(25);
    Splay.print(std::to_string(y));
    std::cout<<"zagzag\n";
    Splay.root=Splay.zagZag(Splay.root);
    Splay.print(std::to_string(y) + "zagzag");
    std::cout<<"zigzag\n";
    Splay.root=Splay.zigZag(Splay.root);
    Splay.print(std::to_string(y) + "zigzag");
    std::cout<<"zigzig\n";
    Splay.root=Splay.zigZig(Splay.root);
    Splay.print(std::to_string(y) + "zigzig");
    std::cout<<"zagzig\n";
    Splay.root=Splay.zagZig(Splay.root);
    Splay.print(std::to_string(y) + "zagzig"); */

    //testing insert
    /* int x = rand() % 50 + 1;
    int i = 0;
    int j = 0;
    Splay Splay(x);
    std::queue<int> q;
    q.push(x);
    std::cout<<x<<" ";
    Splay.print("insert_"+std::to_string(j));
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
        Splay.insert(y);
        Splay.print("insert_"+std::to_string(j));
        j++;
    }
    std::cout<<"\n"; */

    //testing splay

    Splay S(10);
    S.root->left = new ABB(6);
    S.root->left->left = new ABB(4);
    S.root->left->left->left= new ABB(3);
    S.root->left->left->right= new ABB(5);
    S.root->left->right = new ABB(8);
    S.root->left->right->left= new ABB(7);
    S.root->left->right->right= new ABB(9);
    S.root->right = new ABB(14);
    S.root->right->left = new ABB(12);
    S.root->right->left->left= new ABB(11);
    S.root->right->left->right= new ABB(13);
    S.root->right->right = new ABB(16);
    S.root->right->right->left= new ABB(15);
    S.root->right->right->right= new ABB(17);
    S.root->insert(18);
    S.print("test_splay_inicio");
    S.splay(18);
    S.print("test_splay_18");

    //testing search

    /* Splay.search(41);
    Splay.print("busqueda_41");
    Splay.search(60);
    Splay.print("busqueda_60"); */
    return 0;
} 