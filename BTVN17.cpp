#include <iostream>
#include <string>
using namespace std;

/* ====== KHAI BAO NODE ====== */
struct Node {
    int index;
    string title;
    int pages;
    Node* firstChild;
    Node* nextSibling;

    Node(int i, string t, int p) {
        index = i;
        title = t;
        pages = p;
        firstChild = NULL;
        nextSibling = NULL;
    }
};

/* ====== THEM CON ====== */
void addChild(Node* parent, Node* child) {
    if (parent->firstChild == NULL)
        parent->firstChild = child;
    else {
        Node* p = parent->firstChild;
        while (p->nextSibling != NULL)
            p = p->nextSibling;
        p->nextSibling = child;
    }
}

/* ====== DEM SO CHUONG ====== */
int demSoChuong(Node* root) {
    int dem = 0;
    Node* p = root->firstChild;
    while (p != NULL) {
        dem++;
        p = p->nextSibling;
    }
    return dem;
}

/* ====== TONG SO TRANG ====== */
int tongTrang(Node* root) {
    if (root == NULL) return 0;
    int sum = root->pages;
    Node* p = root->firstChild;
    while (p != NULL) {
        sum += tongTrang(p);
        p = p->nextSibling;
    }
    return sum;
}

/* ====== TIM CHUONG DAI NHAT ====== */
Node* chuongDaiNhat(Node* root) {
    Node* p = root->firstChild;
    Node* maxChuong = p;
    int maxTrang = 0;

    while (p != NULL) {
        int t = tongTrang(p);
        if (t > maxTrang) {
            maxTrang = t;
            maxChuong = p;
        }
        p = p->nextSibling;
    }
    return maxChuong;
}

/* ====== IN MOT CHUONG ====== */
void inChuong(Node* root, int level = 0) {
    if (root == NULL) return;

    for (int i = 0; i < level; i++)
        cout << "  ";
    cout << root->title << " (" << root->pages << " trang)" << endl;

    inChuong(root->firstChild, level + 1);
    inChuong(root->nextSibling, level);
}

/* ====== XOA MOT MUC ====== */
bool xoaMuc(Node*& root, int key) {
    if (root == NULL) return false;

    if (root->index == key) {
        root = root->nextSibling;
        return true;
    }

    Node* p = root->firstChild;
    Node* prev = NULL;

    while (p != NULL) {
        if (p->index == key) {
            if (prev == NULL)
                root->firstChild = p->nextSibling;
            else
                prev->nextSibling = p->nextSibling;
            return true;
        }
        if (xoaMuc(p, key))
            return true;
        prev = p;
        p = p->nextSibling;
    }
    return false;
}

/* ====== SO SANH HAI CAY (COPY SACH) ====== */
bool laBanCopy(Node* a, Node* b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;

    if (a->index != b->index ||
        a->title != b->title ||
        a->pages != b->pages)
        return false;

    return laBanCopy(a->firstChild, b->firstChild) &&
           laBanCopy(a->nextSibling, b->nextSibling);
}

/* ====== MAIN ====== */
int main() {
    /* TAO CUON SACH 1 */
    Node* sach1 = new Node(0, "SACH LAP TRINH C++", 0);

    Node* c1 = new Node(1, "Chuong 1", 10);
    Node* c2 = new Node(2, "Chuong 2", 15);

    addChild(sach1, c1);
    addChild(sach1, c2);

    addChild(c1, new Node(11, "Muc 1.1", 5));
    addChild(c1, new Node(12, "Muc 1.2", 8));
    addChild(c2, new Node(21, "Muc 2.1", 6));

    cout << "So chuong: " << demSoChuong(sach1) << endl;

    Node* max = chuongDaiNhat(sach1);
    cout << "Chuong dai nhat: " << max->title << endl;

    cout << "\nNoi dung Chuong 1:\n";
    inChuong(c1);

    xoaMuc(sach1, 12);
    cout << "\nSau khi xoa Muc 1.2:\n";
    inChuong(c1);

    /* TAO CUON SACH 2 */
    Node* sach2 = new Node(0, "SACH LAP TRINH C++", 0);
    Node* c1b = new Node(1, "Chuong 1", 10);
    Node* c2b = new Node(2, "Chuong 2", 15);

    addChild(sach2, c1b);
    addChild(sach2, c2b);
    addChild(c1b, new Node(11, "Muc 1.1", 5));
    addChild(c2b, new Node(21, "Muc 2.1", 6));

    if (laBanCopy(sach1, sach2))
        cout << "\nHai cuon sach la ban copy cua nhau";
    else
        cout << "\nHai cuon sach KHONG phai ban copy";

    return 0;
}
