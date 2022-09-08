#include <bits/stdc++.h>

using namespace std;

template<typename T>
class AVLTree{
private:
    struct Node{
        T data;
        int height, cnt;
        Node *left_child, *right_child;
        Node(T _data):
            data(_data),
            left_child(nullptr),
            right_child(nullptr),
            height(1),
            cnt(1)
            {}
    } *root;

    void recalc_height(Node *node){
        if (node == nullptr) return;
        int lft = 0;
        if (node->left_child != nullptr) lft = node->left_child->height;
        int rght = 0;
        if (node->right_child != nullptr) rght = node->right_child->height;
        node->height = max(lft, rght) + 1;
    }

    Node *rotate_right(Node *node){
        if (node->left_child == nullptr) return node;
        Node *lft = node->left_child;
        node->left_child = lft->right_child;
        lft->right_child = node;
        recalc_height(lft->right_child);
        recalc_height(lft);
        return lft;
    }

    Node *rotate_left(Node *node){
        if (node->right_child == nullptr) return node;
        Node *rght = node->right_child;
        node->right_child = rght->left_child;
        rght->left_child = node;
        recalc_height(rght->left_child);
        recalc_height(rght);
        return rght;
    }

    int balance(Node *node){
        int lft = 0;
        if (node->left_child != nullptr) lft = node->left_child->height;
        int rght = 0;
        if (node->right_child != nullptr) rght = node->right_child->height;
        return (lft - rght);
    }

    bool is_balanced(Node *node){
        if (node == nullptr) return true;
        return (abs(balance(node)) < 2);
    }

    Node* insert_node(Node* node, T data){
        if (node == nullptr){
            return new Node(data);
        }
        if (node->data == data){
            ++ node->cnt;
            return node;
        }
        if (data > node->data){
            node->right_child = insert_node(node->right_child, data);
        }else{
            node->left_child = insert_node(node->left_child, data);
        }
        if (!is_balanced(node)){
            bool lft1 = false, lft2 = false;
            Node *child = nullptr, *grandchild = nullptr;
            if (data > node->data){
                child = node->right_child;
            }else{
                lft1 = true;
                child = node->left_child;
            }
            if (data > child->data){
                grandchild = child->right_child;
            }else{
                lft2 = true;
                grandchild = child->left_child;
            }
            if (lft1){
                if (lft2){
                    return rotate_right(node);
                }else{
                    node->left_child = rotate_left(node->left_child);
                    return rotate_right(node);
                }
            }else{
                if (lft2){
                    node->right_child = rotate_right(node->right_child);
                    return rotate_left(node);
                }else{
                    return rotate_left(node);
                }
            }
        }
        recalc_height(node);
        return node;
    }

    Node *delete_node(Node *node, T data){
        if (node == nullptr) return node;
        if (node -> data < data){
            node->right_child = delete_node(node->right_child, data);
        }else{
            if (node -> data > data){
                node->left_child = delete_node(node->left_child, data);
            }else{
                if (node->cnt > 1){
                    node->cnt --;
                    return node;
                }else{
                    if (node->right_child == nullptr || node->left_child == nullptr) {
                        Node *tmp = node->right_child;
                        if (tmp == nullptr) tmp = node->left_child;
                        if (tmp == nullptr) {
                            tmp = node;
                            node = nullptr;
                        } else *node = *tmp;
                        free(tmp);
                    } else {
                        Node *rght = node->right_child;
                        while (rght->left_child != nullptr) {
                            rght = rght->left_child;
                        }
                        node->data = rght->data;
                        node->right_child = delete_node(node->right_child, node->data);
                    }
                }
            }
        }
        if (node == nullptr){
            return node;
        }
        node->height --;
        if (!is_balanced(node)){
            bool lft1 = false, lft2 = false;
            Node *child = nullptr;
            if (balance(node) > 0){
                lft1 = true;
                child = node->left_child;
            }else child = node->right_child;
            if (balance(child) > 0){
                lft2 = true;
            }
            if (lft1){
                if (lft2){
                    return rotate_right(node);
                }else{
                    node->left_child = rotate_left(node->left_child);
                    return rotate_right(node);
                }
            }else{
                if (lft2){
                    node->right_child = rotate_right(node->right_child);
                    return rotate_left(node);
                }else{
                    return rotate_left(node);
                }
            }
        }
        recalc_height(node);
        return node;
    }

    void print_inorder(Node *node){
        if (node == nullptr) return;
        print_inorder(node->left_child);
        cout << node->data << ' ';
        print_inorder(node->right_child);
    }

    int count(Node *node, T data){
        if (node == nullptr) return 0;
        if (node->data == data) return node->cnt;
        if (data > node->data) return count(node->right_child, data);
        else return count(node->left_child, data);
    }

    T get_rightest(Node *node){
        if (node->right_child == nullptr) return node->data;
        else return get_rightest(node->right_child);
    }

    bool dfs_for_balance(Node *node){
        if (node == nullptr || !is_balanced(node)) return true;
        return (dfs_for_balance(node->left_child) && dfs_for_balance(node->right_child));
    }

public:
    AVLTree():
        root(nullptr)
        {}

    void add(T data){
        root = insert_node(root, data);
    }

    void remove(T data){
        root = delete_node(root, data);
    }

    void print(){
        print_inorder(root);
        cout << '\n';
    }

    int count(T data){
        return count(root, data);
    }

    T max_element(){
        return get_rightest(root);
    }

    bool check_for_balance(){
        return dfs_for_balance(root);
    }

};

template<typename T>
class RBTree{
    enum NODE_COLOR{
        RED, BLACK
    };
    struct Node{
        T val;
        Node *left_child, *right_child, *parent;
        NODE_COLOR color;
        Node(T _val):
            val(_val),
            left_child(nullptr),
            right_child(nullptr),
            parent(nullptr),
            color(RED)
        {}
        bool is_left(){
            return (this->parent != nullptr && this == this->parent->left_child);
        }
    } *root;
    int size;

    void rotate_right(Node *node){
        if (node == nullptr) return;
        Node *lft = node->left_child;
        if (lft == nullptr) return;
        Node *LR = lft->right_child;
        lft->right_child = node;
        lft->parent = node->parent;
        node->parent = lft;
        node->left_child = LR;
        if (LR != nullptr){
            LR->parent = node;
        }
        if (lft->parent != nullptr){
            if (lft->val < lft->parent->val){
                lft->parent->left_child = lft;
            }else{
                lft->parent->right_child = lft;
            }
        }
    }

    void rotate_left(Node *node){
        if (node == nullptr) return;
        Node *rght = node->right_child;
        if (rght == nullptr) return;
        Node *RL = rght->left_child;
        rght->left_child = node;
        rght->parent = node->parent;
        node->parent = rght;
        node->right_child = RL;
        if (RL != nullptr){
            RL->parent = node;
        }
        if (rght->parent != nullptr){
            if (rght->val < rght->parent->val){
                rght->parent->left_child = rght;
            }else{
                rght->parent->right_child = rght;
            }
        }
    }

    bool is_red(Node *node){
        return (node != nullptr && node->color == RED);
    }

    void fixRR(Node *node){
        if (node->parent == nullptr){
            node->color = BLACK;
            return;
        }
        Node *parent = node->parent;
        Node *grandparent = parent->parent;
        Node *uncle = (grandparent == nullptr ? nullptr : (parent->is_left() ? grandparent->right_child : grandparent->left_child));
        if (is_red(parent)) {
            if (is_red(uncle)) {
                parent->color = BLACK;
                uncle->color = BLACK;
                if (grandparent != nullptr) {
                    grandparent->color = RED;
                    fixRR(grandparent);
                }
            } else {
                if (parent->is_left()) { // L
                    if (!node->is_left()) { // LR
                        rotate_left(parent);
                        swap(node->color, grandparent->color);
                    } else {
                        swap(parent->color, grandparent->color);
                    }
                    // LL
                    rotate_right(grandparent);
                } else { // R
                    if (node->is_left()) { // RL
                        rotate_right(parent);
                        swap(node->color, grandparent->color);
                    } else {
                        swap(parent->color, grandparent->color);
                    }
                    // RR
                    rotate_left(grandparent);
                }
            }
        }
    }

    void fixDB(Node *node){
        if (node == root){
            return;
        }
        Node *parent = node->parent;
        Node *sibling = (node->is_left() ? parent->right_child : parent->left_child);
        if (is_red(sibling)){
            swap(sibling->color, parent->color);
            if (sibling->is_left()){
                rotate_right(sibling);
            }else{
                rotate_left(sibling);
            }
            fixDB(node);
        }else{
            if (sibling == nullptr  || (!is_red(sibling->left_child) && !is_red(sibling->right_child))){
                if (sibling != nullptr){
                    sibling->color = RED;
                    if (parent->color == BLACK) {
                        fixDB(node->parent);
                    }else{
                        node->parent->color = BLACK;
                    }
                }
            }else{
                if (sibling->is_left()){
                    if (is_red(sibling->left_child)){ // LL
                        sibling->left_child->color = sibling->color;
                        sibling->color = parent->color;
                        rotate_right(parent);
                    }else{ // LR
                        sibling->right_child->color = parent->color;
                        rotate_left(sibling);
                        rotate_right(parent);
                    }
                }else{
                    if (is_red(sibling->right_child)){ // RR
                        sibling->right_child->color = sibling->color;
                        sibling->color = parent->color;
                        rotate_left(parent);
                    }else{ // RL
                        sibling->left_child->color = parent->color;
                        rotate_right(sibling);
                        rotate_left(parent);
                    }
                }
                parent->color = BLACK;
            }
        }
    }

    Node *find_by_val(T _val){
        Node *node = root;
        while(node != nullptr){
            if (node->val == _val){
                break;
            }
            if (node->val > _val){
                node = node->left_child;
            }else{
                node = node->right_child;
            }
        }
        return node;
    }

    Node *find_replacement(Node *node){
        if (node == nullptr) return nullptr;
        if (node->left_child == nullptr && node->right_child == nullptr) return nullptr;
        if (node->left_child != nullptr && node->right_child != nullptr){
            Node *tmp = node->right_child;
            while(tmp->left_child != nullptr){
                tmp = tmp->left_child;
            }
            return tmp;
        }
        if (node->left_child != nullptr) return node->left_child;
        else return node->right_child;
    }

    void remove_node(Node *node){
        if (node == nullptr) return;
        Node *u = find_replacement(node);
        bool both_are_black = (!is_red(node) && !is_red(u));
        if (u == nullptr){
            if (node == root){
                root = nullptr;
            }else{
                if (both_are_black){
                    fixDB(node);
                }else{
                    Node *sibling = (node->is_left() ? node->parent->right_child : node->parent->left_child);
                    if (sibling != nullptr){
                        sibling->color = RED;
                    }
                }
                if (node->is_left()){
                    node->parent->left_child = nullptr;
                }else{
                    node->parent->right_child = nullptr;
                }
            }
            delete node;
            return;
        }

        if (node->left_child == nullptr || node->right_child == nullptr){
            if (node == root){
                node->val = u->val;
                node->left_child = node->right_child = nullptr;
                delete u;
            }else{
                if (node->is_left()){
                    node->parent->left_child = u;
                }else{
                    node->parent->right_child = u;
                }
                u->parent = node->parent;
                delete node;
                if (both_are_black){
                    fixDB(u);
                }else{
                    u->color = BLACK;
                }
            }
            return;
        }

        swap(node->val, u->val);
        remove_node(u);
    }

    void print_inorder(Node *node){
        if (node == nullptr) return;
        print_inorder(node->left_child);
        cout << node->val << ' ' << (node->color == BLACK ? 'B' : 'R') << ' ' << (node->parent != nullptr ? node->parent->val : -1) << '\n';
        print_inorder(node->right_child);
    }

    bool dfs_for_db(Node *node, int cnt_of_black, set<int> &s){
        if (node == nullptr) return true;
        cnt_of_black += (node->color == BLACK);
        bool ok = true;
        if (node->left_child == nullptr) {
            s.insert(cnt_of_black);
            if (s.size() > 1) return false;
        }
        ok = (ok && dfs_for_db(node->left_child, cnt_of_black, s));
        if (node->right_child == nullptr) {
            s.insert(cnt_of_black);
            if (s.size() > 1) return false;
        }
        ok = (ok && dfs_for_db(node->right_child, cnt_of_black, s));
        return ok;
    }
public:
    RBTree():
        root(nullptr),
        size(0)
    {}

    void add(T _val){
        if (contains(_val)) return;
        ++ size;
        Node *new_node = new Node(_val);
        if (root == nullptr){
            root = new_node;
            root->color = BLACK;
        }else{
            Node *parent = root;
            while(new_node->parent == nullptr){
                if (parent->val < _val){
                    if (parent->right_child == nullptr){
                        parent->right_child = new_node;
                        new_node->parent = parent;
                        break;
                    }else{
                        parent = parent->right_child;
                    }
                }else{
                    if (parent->left_child == nullptr){
                        parent->left_child = new_node;
                        new_node->parent = parent;
                        break;
                    }else{
                        parent = parent->left_child;
                    }
                }
            }
            fixRR(new_node);
            while(root->parent != nullptr){
                root = root->parent;
            }
        }
    }

    void remove(T _val){
        if (root == nullptr) return;
        if (!contains(_val)) return;
        -- size;
        Node *v = find_by_val(_val);
        remove_node(v);
    }

    bool contains(T _val){
        return (find_by_val(_val) != nullptr);
    }

    int get_size(){
        return size;
    }

    void print(){
        cout << "Inorder traversal:\n";
        print_inorder(root);
        cout << '\n';
    }

    bool check_for_rr(){
        if (root == nullptr) return true;
        queue < Node* > q;
        q.push(root);
        while(!q.empty()){
            Node *v = q.front();
            q.pop();
            if (is_red(v) && is_red(v->left_child)) return false;
            if (is_red(v) && is_red(v->right_child)) return false;
            if (v->left_child != nullptr){
                q.push(v->left_child);
            }
            if (v->right_child != nullptr){
                q.push(v->right_child);
            }
        }
        return true;
    }

    bool check_for_db(){
        set < int > s;
        return (!is_red(root) && dfs_for_db(root, 0, s));
    }

};

int main() {
    int x;
    char t;
    AVLTree < int > tree;
    while(cin >> t >> x){
        if (t == '+'){
            tree.add(x);
        }else{
            tree.remove(x);
        }
        tree.print();
        if (!tree.check_for_balance()){
            cout << "Balance violated!\n";
        }
        /*
        if (!tree.check_for_db()){
            cout << "Black distance rule violated!\n";
        }
        if (!tree.check_for_rr()){
            cout << "Red->Red rule violated!\n";
        }
        */
    }
    return 0;
}
/*
+1
+3
+6
+7
+11
+19
-6
-7
-7
-3
 */
