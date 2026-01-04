#include <iostream>
#include <vector>
using namespace std;

/* ======================================================
   KHAI BÁO CẤU TRÚC NODE DÙNG CHUNG
   ====================================================== */
struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int v) {
        value = v;
        left = right = NULL;
    }
};

/* ======================================================
   BÀI 1: CÂY NHỊ PHÂN + DUYỆT + VUN ĐỐNG (HEAP)
   ====================================================== */

/* Duyệt trước (Preorder): Root - Left - Right */
void preorder(Node* root) {
    if (root == NULL) return;
    cout << root->value << " ";
    preorder(root->left);
    preorder(root->right);
}

/* Duyệt giữa (Inorder): Left - Root - Right */
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->value << " ";
    inorder(root->right);
}

/* Duyệt sau (Postorder): Left - Right - Root */
void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->value << " ";
}

/* ===== Chuyển cây sang mảng (duyệt level) ===== */
void treeToArray(Node* root, vector<int>& a) {
    if (!root) return;
    a.push_back(root->value);
    treeToArray(root->left, a);
    treeToArray(root->right, a);
}

/* ===== Vun đống Max-Heap ===== */
void heapify(vector<int>& a, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && a[l] > a[largest]) largest = l;
    if (r < n && a[r] > a[largest]) largest = r;

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

/* ===== Xây dựng Heap ===== */
void buildHeap(vector<int>& a) {
    int n = a.size();
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(a, n, i);
}

/* ======================================================
   BÀI 2: KIỂM TRA 2 CÂY NHỊ PHÂN CÓ GIỐNG NHAU KHÔNG
   ====================================================== */

bool isSameTree(Node* t1, Node* t2) {
    if (t1 == NULL && t2 == NULL) return true;
    if (t1 == NULL || t2 == NULL) return false;
    if (t1->value != t2->value) return false;

    return isSameTree(t1->left, t2->left) &&
           isSameTree(t1->right, t2->right);
}

/* Độ phức tạp: O(n)
   Với n > 100000 → duyệt mỗi node đúng 1 lần */

/* ======================================================
   BÀI 3: CÂY NHỊ PHÂN TÌM KIẾM (BST)
   ====================================================== */

class BSTree {
private:
    Node* root;

    void insert(int val, Node*& t) {
        if (t == NULL)
            t = new Node(val);
        else if (val < t->value)
            insert(val, t->left);
        else if (val > t->value)
            insert(val, t->right);
    }

    Node* search(int val, Node* t) {
        if (t == NULL) return NULL;
        if (t->value == val) return t;
        if (val < t->value)
            return search(val, t->left);
        return search(val, t->right);
    }

    void makeEmpty(Node*& t) {
        if (!t) return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = NULL;
    }

public:
    BSTree() {
        root = NULL;
    }

    ~BSTree() {
        makeEmpty();
    }

    bool isEmpty() {
        return root == NULL;
    }

    void makeEmpty() {
        makeEmpty(root);
    }

    void insert(int val) {
        insert(val, root);
    }

    Node* search(int val) {
        return search(val, root);
    }

    Node* getRoot() {
        return root;
    }
};

/* Duyệt cây BST */
void PREORDER_travl(Node* t) {
    if (!t) return;
    cout << t->value << " ";
    PREORDER_travl(t->left);
    PREORDER_travl(t->right);
}

/* ======================================================
   MAIN – CHẠY TOÀN BỘ BÀI
   ====================================================== */

int main() {

    /* ---------- BÀI 1 ---------- */
    Node* root = new Node(4);
    root->left = new Node(16);
    root->right = new Node(14);
    root->left->left = new Node(2);
    root->left->right = new Node(8);
    root->right->left = new Node(1);
    root->right->right = new Node(3);

    cout << "Bai 1 - Duyet truoc: ";
    preorder(root);
    cout << "\nBai 1 - Duyet giua: ";
    inorder(root);
    cout << "\nBai 1 - Duyet sau: ";
    postorder(root);

    vector<int> a;
    treeToArray(root, a);
    buildHeap(a);

    cout << "\n\nCay sau khi vun dong (Heap - Preorder): ";
    for (int x : a) cout << x << " ";

    /* ---------- BÀI 2 ---------- */
    Node* t1 = new Node(1);
    t1->left = new Node(2);
    t1->right = new Node(3);

    Node* t2 = new Node(1);
    t2->left = new Node(2);
    t2->right = new Node(3);

    cout << "\n\nBai 2 - Hai cay ";
    if (isSameTree(t1, t2))
        cout << "GIONG NHAU\n";
    else
        cout << "KHONG giong nhau\n";

    /* ---------- BÀI 3 ---------- */
    BSTree bst;
    bst.insert(5);
    bst.insert(6);
    bst.insert(3);
    bst.insert(8);
    bst.insert(7);
    bst.insert(4);
    bst.insert(2);

    cout << "\nBai 3 - Duyet truoc BST: ";
    PREORDER_travl(bst.getRoot());

    Node* n1 = bst.search(4);
    Node* n2 = bst.search(9);

    cout << "\n";
    if (n1) cout << "Tim thay node 4\n";
    if (!n2) cout << "Khong tim thay node 9\n";

    bst.makeEmpty();
    if (bst.isEmpty())
        cout << "Cay da bi xoa rong\n";

    return 0;
}
