#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int value;
    int data_level;
    struct TreeNode* leftChild;
    struct TreeNode* rightChild;
};


struct TreeNode* createTreeNode(int value);
struct TreeNode* performSkew(struct TreeNode* root);
struct TreeNode* performSplit(struct TreeNode* root);
struct TreeNode* addNode(struct TreeNode* root, int value);
struct TreeNode* removeNode(struct TreeNode* root, int value);
struct TreeNode* findNode(struct TreeNode* root, int value);
struct TreeNode* getMinimumNode(struct TreeNode* root);
struct TreeNode* getMaximumNode(struct TreeNode* root);
int calculateHeight(struct TreeNode* root);
int countTotalNodes(struct TreeNode* root);
int countLeafNodes(struct TreeNode* root);
void freeTree(struct TreeNode* root);
void inorderTraversal(struct TreeNode* root);
void preorderTraversal(struct TreeNode* root);
void postorderTraversal(struct TreeNode* root);


struct TreeNode* createTreeNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->data_level = 1;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

struct TreeNode* performSkew(struct TreeNode* root) {
    if (root == NULL || root->leftChild == NULL)
        return root;
    if (root->leftChild->data_level == root->data_level) {
        struct TreeNode* temp = root->leftChild;
        root->leftChild = temp->rightChild;
        temp->rightChild = root;
        root = temp;
    }
    return root;
}

struct TreeNode* performSplit(struct TreeNode* root) {
    if (root == NULL || root->rightChild == NULL || root->rightChild->rightChild == NULL)
        return root;
    if (root->data_level == root->rightChild->rightChild->data_level) {
        struct TreeNode* temp = root->rightChild;
        root->rightChild = temp->leftChild;
        temp->leftChild = root;
        root = temp;
        root->data_level++;
    }
    return root;
}

struct TreeNode* addNode(struct TreeNode* root, int value) {
    if (root == NULL)
        return createTreeNode(value);
    if (value < root->value)
        root->leftChild = addNode(root->leftChild, value);
    else if (value > root->value)
        root->rightChild = addNode(root->rightChild, value);
    else {
        printf("Duplicate value, ignoring insertion.\n");
        return root;
    }
    root = performSkew(root);
    root = performSplit(root);
    return root;
}

struct TreeNode* removeNode(struct TreeNode* root, int value) {
    if (root == NULL) {
        printf("Element not found, ignoring deletion.\n");
        return root;
    }
    if (value < root->value) {
        root->leftChild = removeNode(root->leftChild, value);
    } else if (value > root->value) {
        root->rightChild = removeNode(root->rightChild, value);
    } else {
        struct TreeNode* temp;
        if (root->leftChild != NULL && root->rightChild != NULL) {
            temp = root->rightChild;
            while (temp->leftChild != NULL) {
                temp = temp->leftChild;
            }
            root->value = temp->value;
            root->rightChild = removeNode(root->rightChild, temp->value);
        } else {
            temp = root;
            if (root->leftChild == NULL) {
                root = root->rightChild;
            } else if (root->rightChild == NULL) {
                root = root->leftChild;
            }
            free(temp);
        }
    }
    if (root == NULL) {
        return root;
    }
    root = performSkew(root);
    root->rightChild = performSkew(root->rightChild);
    if (root->rightChild != NULL) {
        root->rightChild->rightChild = performSkew(root->rightChild->rightChild);
    }
    root = performSplit(root);
    root->rightChild = performSplit(root->rightChild);
    return root;
}

struct TreeNode* findNode(struct TreeNode* root, int value) {
    if (root == NULL || root->value == value)
        return root;
    if (value < root->value)
        return findNode(root->leftChild, value);
    else
        return findNode(root->rightChild, value);
}

struct TreeNode* getMinimumNode(struct TreeNode* root) {
    if (root == NULL)
        return NULL;
    while (root->leftChild != NULL)
        root = root->leftChild;
    return root;
}

struct TreeNode* getMaximumNode(struct TreeNode* root) {
    if (root == NULL)
        return NULL;
    while (root->rightChild != NULL)
        root = root->rightChild;
    return root;
}

int calculateHeight(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    int leftHeight = calculateHeight(root->leftChild);
    int rightHeight = calculateHeight(root->rightChild);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int countTotalNodes(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    return 1 + countTotalNodes(root->leftChild) + countTotalNodes(root->rightChild);
}

int countLeafNodes(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    if (root->leftChild == NULL && root->rightChild == NULL)
        return 1;
    return countLeafNodes(root->leftChild) + countLeafNodes(root->rightChild);
}

void freeTree(struct TreeNode* root) {
    if (root == NULL)
        return;
    freeTree(root->leftChild);
    freeTree(root->rightChild);
    free(root);
}

void inorderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;
    inorderTraversal(root->leftChild);
    printf("%d ", root->value);
    inorderTraversal(root->rightChild);
}

void preorderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;
    printf("%d ", root->value);
    preorderTraversal(root->leftChild);
    preorderTraversal(root->rightChild);
}

void postorderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;
    postorderTraversal(root->leftChild);
    postorderTraversal(root->rightChild);
    printf("%d ", root->value);
}

int main() {
    struct TreeNode* root = NULL;
    int choice, value;

    while (1) {
        printf("\nAA Tree Operations Menu:\n");
        printf("1. Insert Node\n");
        printf("2. Remove Node\n");
        printf("3. Search Node\n");
        printf("4. In-order Traversal\n");
        printf("5. Pre-order Traversal\n");
        printf("6. Post-order Traversal\n");
        printf("7. Find Minimum value Node\n");
        printf("8. Find Maximum value Node\n");
        printf("9. Calculate Height of AA Tree\n");
        printf("10. Count Total Nodes of AA Tree\n");
        printf("11. Count Leaf Nodes of AA Tree\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = addNode(root, value);
                break;
            case 2:
                printf("Enter value to remove: ");
                scanf("%d", &value);
                root = removeNode(root, value);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                struct TreeNode* foundNode = findNode(root, value);
                if (foundNode != NULL)
                    printf("Value %d found in the tree.\n", value);
                else
                    printf("Value %d not found in the tree.\n", value);
                break;
            case 4:
                printf("In-order traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("Pre-order traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 6:
                printf("Post-order traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 7: {
                struct TreeNode* minNode = getMinimumNode(root);
                if (minNode != NULL)
                    printf("Minimum value in the tree: %d\n", minNode->value);
                else
                    printf("The tree is empty.\n");
                break;
            }
            case 8: {
                struct TreeNode* maxNode = getMaximumNode(root);
                if (maxNode != NULL)
                    printf("Maximum value in the tree: %d\n", maxNode->value);
                else
                    printf("The tree is empty.\n");
                break;
            }
            case 9: {
                int height = calculateHeight(root);
                printf("Height of the tree: %d\n", height);
                break;
            }
            case 10: {
                int totalNodes = countTotalNodes(root);
                printf("Total number of nodes in the tree: %d\n", totalNodes);
                break;
            }
            case 11: {
                int leafNodes = countLeafNodes(root);
                printf("Number of leaf nodes in the tree: %d\n", leafNodes);
                break;
            }
            case 12:
                freeTree(root);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
