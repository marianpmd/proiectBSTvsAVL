#include <stdio.h>
#include <stdlib.h>

/*
 * Binary Tree struct
 * key->the key of the node (or it's value)
 * left->pointer to the left child of the node
 * right->pointer to the right child of the node
 */
typedef struct Node {
    unsigned long int key;
    struct Node *left;
    struct Node *right;
    unsigned long int height;
}Node;

/*
 * Creates and returns a pointer to an
 * initial node with a key passed as parameter
 */
Node* initNode(unsigned long int key){
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->key = key;
    temp->left=NULL;
    temp->right=NULL;
    temp->height = 1;
    return temp;
}

Node *insert(Node* node, unsigned long int key){
    if (node == NULL) {
        return initNode(key);
    }

    if (key < node->key){
        node->left = insert(node->left , key);
    }else if (key >= node->key){
        node->right = insert(node->right , key);
    }

    return node;
}

void traverseInorder(Node *root){
    if (root!=NULL){
        traverseInorder(root->left);
        printf("%lu ",root->key);
        traverseInorder(root->right);
    }
}

unsigned long int max(unsigned long int a,unsigned long int b)
{
    if (a > b){
        return a;
    } else{
        return b;
    }
}

unsigned long int getHeight(Node *node){
    if (node == NULL){
        return 0;
    }
    return node->height;
}
Node* rotateRight(Node *node){
    Node* leftSub = node->left;
    Node* rightSubOfLeft = leftSub->right;

    leftSub->right = node;
    node->left = rightSubOfLeft;

    node->height = 1+ max(getHeight(node->left),getHeight(node->right));
    leftSub->height = 1+ max(getHeight(leftSub->left),getHeight(leftSub->right));

    return leftSub;
}

Node* rotateLeft(Node *node){
    Node *rightSub = node->right;
    Node *leftSubOfRight = rightSub->left;

    rightSub->left = node;
    node->right = leftSubOfRight;

    node->height = 1+ max(getHeight(node->left),getHeight(node->right));
    rightSub->height = 1+ max(getHeight(rightSub->left),getHeight(rightSub->right));
    return rightSub;
}

long int getEQ(Node *node){
    if (node == NULL){
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);

}


Node* insertAVL(Node *node , unsigned long int key){
    if (node == NULL) {
        return initNode(key);
    }

    if (key < node->key){
        node->left = insertAVL(node->left , key);
    }else if (key > node->key){
        node->right = insertAVL(node->right , key);
    } else{
        return node;
    }

    node->height = 1 + max(getHeight(node->left) , getHeight(node->right));

    long int eq = getEQ(node);

    if (eq > 1 && key < node->left->key){
        return rotateRight(node);
    }

    if (eq < -1 && key > node->right->key){
        return rotateLeft(node);
    }

    if (eq > 1 && key > node->left->key){
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (eq < -1 && key < node->right->key){
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;

}

long int getDistance(Node *root, unsigned long int key)
{
    if (root == NULL){
        return -1;
    }

    long int branchCount = -1;

    if ((root->key == key) || (branchCount = getDistance(root->left, key)) >= 0 || (branchCount = getDistance(root->right, key)) >= 0)
        return branchCount + 1;

    return branchCount;
}

int main(int argc ,char **argv) {
    char* filename;
    filename = argv[1];
    Node *BSTroot = NULL;
    Node *AVLroot = NULL;


    FILE* input;
    FILE* output;
    unsigned long int value;
    input = fopen(argv[1],"r"); 
    output = fopen("output.out","w");

    if (input == NULL){
        exit(EXIT_FAILURE);
    }
    if (output == NULL){
        exit(EXIT_FAILURE);
    }

    while (!feof(input)){
        fscanf(input,"%li",&value);
        BSTroot = insert(BSTroot,value);
        AVLroot = insertAVL(AVLroot,value);
    }

    value = 0;

     unsigned long int BSTcountSum = 0;
     unsigned long int AVLcountSum = 0;

    fseek(input,0,SEEK_SET);

    while (!feof(input)){
        fscanf(input,"%li",&value);
        BSTcountSum += getDistance(BSTroot,value);
        AVLcountSum += getDistance(AVLroot,value);
    }

    printf("BSTcountSum : %li\n",BSTcountSum);
    printf("AVLcountSum : %li\n",AVLcountSum);
    
    double ratio = ((double)BSTcountSum )/ AVLcountSum;
    
    fprintf(output,"%f\n",ratio);

    fclose(input);
    fclose(output);


/*
    Node *BSTroot = NULL;
    BSTroot = initNode(10);
    insert(BSTroot, 20);
    insert(BSTroot, 30);
    insert(BSTroot, 40);
    insert(BSTroot, 50);
    insert(BSTroot, 25);
    insert(BSTroot, 5);
    insert(BSTroot, 26);
    insert(BSTroot, 51);
    insert(BSTroot, 2);

    printf("nr de arce : %lu \n",getDistance(BSTroot, 51));

    Node *AVLroot = NULL;
    AVLroot = insertAVL(AVLroot , 10);
    AVLroot =  insertAVL(AVLroot , 20);
    AVLroot =  insertAVL(AVLroot , 30);
    AVLroot =  insertAVL(AVLroot , 40);
    AVLroot =  insertAVL(AVLroot , 50);
    AVLroot =  insertAVL(AVLroot , 25);
    AVLroot =  insertAVL(AVLroot , 5);
    AVLroot =  insertAVL(AVLroot , 26);
    AVLroot =  insertAVL(AVLroot , 51);
    AVLroot =  insertAVL(AVLroot , 2);
    traverseInorder(AVLroot);

    printf("\nroot bst : %li\n",BSTroot->key);
    printf("root avl : %li\n",AVLroot->key);


    printf("\nnr de arce : %lu \n",getDistance(AVLroot, 51));
    int vals[10] = {10,20,30,40,50,25,5,26,51,2};

    unsigned long int BSTcountSum = 0;
    unsigned long int AVLcountSum = 0;

    printf("\n");
    for (int i = 0; i < 10; ++i) {
        printf("suma BST anterioara :%li\n",BSTcountSum);
        BSTcountSum+=getDistance(BSTroot,vals[i]);
        printf("pana la : %d s-au adunat BST : %li \n",vals[i],BSTcountSum);////////////////////////////////////////////////////////////////////nu functioneaza count
        printf("suma AVL anterioara :%li\n",AVLcountSum);
        AVLcountSum+=getDistance(AVLroot,vals[i]);
        printf("pana la : %d s-au adunat AVL : %li \n",vals[i],AVLcountSum);
    }*/

    return 0;
}
