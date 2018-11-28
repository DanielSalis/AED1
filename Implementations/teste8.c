#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Início do TAD
typedef struct struct_node{
	struct struct_node *left;
    struct struct_node *right;
	int key;
}node;

node* createNode(int key){
    node* newElement = (node*)malloc(sizeof(node));
    newElement->key = key;
    newElement->right = NULL;
    newElement->left = NULL;
    return (newElement);
}

node* insert(node* root, int key){
    if(root == NULL){
        return createNode(key);
    }

    if(key < root->key){
        root->left = insert(root->left, key);
    }else if(key > root->key){
        root->right = insert(root->right, key); 
    }

    return root;
}

node* search(node* root, int key){
    if(root == NULL){
        return NULL;
    }

    if (root->key == key)
       return root;
    if (root->key > key)
       return search (root->left, key);
    else
       return search (root->right, key);
}

node* findParent(node *aux, int key_parent){
    if(aux != NULL){
        node *NovoPai = findParent(aux->left, key_parent);
        if(NovoPai == NULL) {
            NovoPai = findParent(aux->right, key_parent);
        }
        return NovoPai;
    }else{
        return NULL;
    }
}

node* searchMinValue(node* root) {
   while (root->left != NULL) {
      root = root->left;
   }
   return root;
}

node* deleteNode(node* root, int key){
    if(root == NULL){
        return root;
    }

    else if(key < root->key){
        root->left = deleteNode(root->left, key);
    }

    else if(key > root->key){
        root->right = deleteNode(root->right, key);
    }

    else{
        //If node has no child------------------
        if(root->left == NULL && root->right == NULL){
            free(root);
            root = NULL;
            return root;
        }

        //If node has one child-----------------
        else if(root->left == NULL){
            node* temp = root;
            root = root->right;
            free(temp);
            return root;
        }
        else if(root->right == NULL){
            node* temp = root;
            root = root->left;
            free(temp);
            return root;
        }

        //If node has 2 children----------------
        else{
            node* temp = searchMinValue(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    return root;
}

void printTree(node* root){
	if(root == NULL){
		return;
    }
	else{
		printTree(root->left);
            printf("%d ",root->key);
            // if((root->right != NULL)||(root->left != NULL))
            //     printf(" ");
		printTree(root->right);
    }
}

//Fim do Tad
int main(){

	node *root;
    node *aux;

	int key;
    int cont = 0; 
    int operacoes = 0;
	char opcao;

	scanf("%d", &operacoes);

    while(cont < operacoes){
        scanf(" %c", &opcao);
        
        if(opcao == 'I'){
            scanf("%d", &key);
            if(cont == 0){
                root = createNode(key);
            }else{
                insert(root, key);
            }
            cont++;
        }

        else if(opcao == 'B'){
            scanf("%d", &key);
            aux = search(root, key);
            if(aux == NULL){
                printf("N");
                printf("\n");
            }else{
                printf("S");
                printf("\n");
            }
            cont++;
        }

        else if(opcao == 'M'){
            //imprimir
            printTree(root);
            printf("\n");
            cont++;
        }

        else if(opcao == 'R'){
            //remover
            scanf("%d", &key);
            root = deleteNode(root, key);
            cont++;
        }
    }
	return 0;
}
