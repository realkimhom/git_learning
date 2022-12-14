#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>

struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *newNode(int data) {
    struct TreeNode *node = (struct TreeNode *) malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct TreeNode *findNode(struct TreeNode* node,int key){
    if (node == NULL)
        return NULL;
    else if(node->data == key){
        return node;
    } else{
        struct TreeNode* node1 = findNode(node->left, key);
        if (node1)
            return node1;
        return findNode(node->right,key);
    }
}

unsigned int countNodes(struct TreeNode *root) {
    if (root == NULL)
        return (0);
    return (1 + countNodes(root->left) + countNodes(root->right));
}
int max(int x, int y){
    if(x > y)
        return x;
    return y;
}

int treeHeight(struct TreeNode* root){
    if(root == NULL){
        return 0;
    }else{
        int leftHeight = treeHeight(root->left);
        int rightHeight = treeHeight(root->right);
        return max(leftHeight, rightHeight) + 1;
    }
}

int isBalanced(struct TreeNode* root){
    int leftHeight;
    int rightHeight;

    if (root == NULL)
        return 1;

    leftHeight = treeHeight(root->left);
    rightHeight = treeHeight(root->right);

    if(abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right)){
        return 1;
    }
    return 0;
}

bool isComplete ( struct TreeNode* root, unsigned int index,
                  unsigned int number_nodes)
{
    // An empty tree is complete
    if (root == NULL)
        return (true);
    if (index >= number_nodes)
        return (false);

    // Recur for left and right subtrees
    return (isComplete(root->left, 2*index + 1, number_nodes) &&
            isComplete(root->right, 2*index + 2, number_nodes));
}


int main() {
    FILE *fp;
    int parent = 0;
    fp = fopen("../input_tree.txt", "r");
    struct TreeNode *root = NULL;
    struct TreeNode *globalRoot = NULL;
    char buff[128];
    while (fgets(buff, 128, (FILE *) fp)) {
        printf("%d\n",strlen(buff));
        printf(buff);
        if (strlen(buff) == 0)
            break;
        int node1, node2;

        sscanf(buff, "(%d, %d)", &node1, &node2);
        if (parent == 0) {
            printf("New a root\n");
            root = newNode(node1);
            globalRoot = root;
        }
        printf("root node now is %d\n", node1);
        root = findNode(globalRoot, node1);
        if (node1 != parent) {
            if (root->left == NULL) {
                printf("a naked node %d, with new node %d in left child \n", root->data, node2);
                root->left = newNode(node2);
            } else {
                printf("a full node %d, with a new on the left's %d left, which is %d \n", root->data, root->left->data,
                       node2);
                root = root->left;
                root->left = newNode(node2);
            }
        } else {
            printf("a node %d with left child,  %d, new node on the right %d\n", root->data, root->left->data, node2);
            root->right = newNode(node2);
        }
        parent = node1;
    }

    printf("the tree is %d", treeHeight(globalRoot));

    printf("The tree is balanced %d \n", isBalanced(globalRoot));
    printf("The tree is completed %d \n", isComplete(globalRoot, 0, countNodes(globalRoot)));
    fclose(fp);
    FILE *fo;
    // The output.
    fo = fopen("../tree properties .txt","w");
    if (isComplete(globalRoot, 0, countNodes(globalRoot))){
        fprintf(fo,"Is the tree complete? No\n");
    }
    else{
        fprintf(fo,"Is the tree complete? Yes\n");
    }
    fprintf(fo, "What’s the height of the tree? %d\n", treeHeight(globalRoot));
    if(isBalanced(globalRoot)){
        fprintf(fo,"Is it balanced? Yes\n");
    }
    else{
        fprintf(fo,"Is it balanced? No\n");
    }
    fclose(fo);
    printf("Its all over now baby blue.\n");
    return 0;
}