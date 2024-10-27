#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <iomanip> //para printpretty
#include <queue> //para print vertical

class Node {
public:
    int data;  
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int x){
        data = x;
    }
    Node(int x, Node* l, Node* r){
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
                left = new Node(x);
                return;
            }
            left->insert(x);
            return;
        }
        if(right==nullptr){
            right = new Node(x);
            return;
        }
        right->insert(x);
        return;
    }
    void print(){
        if(left!=nullptr){
            left->print();
        }
        std::cout<<data<<" ";
        if(right!=nullptr){
            right->print();
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

        std::queue<std::pair<const Node*, int>> q;
        int currentLevel = 0;
        q.push({this, currentLevel});

        while (!q.empty()) {
            auto [node, level] = q.front();
            q.pop();

            if (level != currentLevel) {
                std::cout << "\n";
                currentLevel = level;
            }
            std::cout << " " << node->data << " ";

            if (node->left) q.push({node->left, level + 1});
            if (node->right) q.push({node->right, level + 1});
        }
        std::cout << "\n";
    }
};

void showABB(Node *t,int counter){
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

int main(){
    int x = rand() % 100 + 1;
    int i = 0;
    Node ABB(x);
    while (i<80){
        ABB.insert(rand() % 100 + 1);
        i++;
    }
    
    /* ABB.insert(4);
    ABB.insert(9);
    ABB.insert(5); */
    /* std::cout << ABB.data<<"\n"; 
    std::cout << ABB.right->data<<"\n";
    std::cout << ABB.left->data<<"\n";
    std::cout << ABB.left->right->data<<"\n"; */
    //ABB.prettyPrint();
    ABB.print();
    //ABB.printVertical();
    //showABB(&ABB,0);
    std::cout<<"\n";
    std::cout<<"está el 5? "<<ABB.search(5)<<"\n";
    std::cout<<"está el 10? "<<ABB.search(10)<<"\n";
    return 0;
}