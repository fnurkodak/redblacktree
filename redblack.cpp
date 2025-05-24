#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <map>
using namespace std;

enum Color { RED, BLACK };

struct RBTNode {
    char name[50];
    Color color;
    RBTNode *left, *right, *parent;
    int discovery_time;
    int finish_time;
};

class RBTree {
private:
    RBTNode *root;
    RBTNode *NIL;
    int time;
    map<pair<int, int>, RBTNode*> timestamp_map;

    void leftRotate(RBTNode *x) {
        RBTNode *y = x->right;
        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(RBTNode *x) {
        RBTNode *y = x->left;
        x->left = y->right;
        if (y->right != NIL) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void insertFixup(RBTNode *z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                RBTNode *y = z->parent->parent->right;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                RBTNode *y = z->parent->parent->left;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void transplant(RBTNode *u, RBTNode *v) {
        if (u->parent == NIL) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        v->parent = u->parent;
    }

    RBTNode* treeMinimum(RBTNode *x) {
        while (x->left != NIL) x = x->left;
        return x;
    }

    void deleteFixup(RBTNode *x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                RBTNode *w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                RBTNode *w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void dfsHelper(RBTNode *node) {
        if (node == NIL) return;
        node->discovery_time = time++;
        dfsHelper(node->left);
        dfsHelper(node->right);
        node->finish_time = time++;
        timestamp_map[{node->discovery_time, node->finish_time}] = node;
    }

    void printDFS(RBTNode *node) {
        if (node == NIL) return;
        cout << node->name << " (" << (node->color == RED ? "RED" : "BLACK") << "): d="
             << node->discovery_time << ", f=" << node->finish_time << endl;
        printDFS(node->left);
        printDFS(node->right);
    }

    void printRBT(RBTNode *node, int depth = 0) {
        if (node == NIL) return;
        for (int i = 0; i < depth; ++i) cout << ". ";
        cout << node->name << " (" << (node->color == RED ? "RED" : "BLACK") << ")\n";
        printRBT(node->left, depth + 1);
        printRBT(node->right, depth + 1);
    }

public:
    RBTree() {
        NIL = new RBTNode;
        strcpy(NIL->name, "");
        NIL->color = BLACK;
        NIL->left = NIL->right = NIL->parent = NIL;
        root = NIL;
    }

    void insert(const char *name) {
        cout << "Directive-----------------> insert " << name << endl;
        RBTNode *z = new RBTNode;
        strcpy(z->name, name);
        z->color = RED;
        z->left = z->right = z->parent = NIL;
        RBTNode *y = NIL;
        RBTNode *x = root;
        while (x != NIL) {
            y = x;
            if (strcmp(z->name, x->name) < 0) x = x->left;
            else if (strcmp(z->name, x->name) > 0) x = x->right;
            else {
                cout << "Invalid Operation\n";
                delete z;
                return;
            }
        }
        z->parent = y;
        if (y == NIL) root = z;
        else if (strcmp(z->name, y->name) < 0) y->left = z;
        else y->right = z;
        insertFixup(z);
    }

    void dfs() {
        cout << "Directive-----------------> dfs\n";
        time = 1;
        timestamp_map.clear();
        dfsHelper(root);
        printDFS(root);
    }

    void query(int d, int f) {
        cout << "Directive-----------------> query " << d << " " << f << endl;
        if (timestamp_map.count({d, f})) {
            RBTNode *n = timestamp_map[{d, f}];
            cout << "Output: Node " << n->name << " (" << (n->color == RED ? "RED" : "BLACK") << ")\n";
        } else {
            cout << "Invalid Operation\n";
        }
    }

    void remove(const char *name) {
        cout << "Directive-----------------> delete " << name << endl;
        RBTNode *z = root;
        while (z != NIL && strcmp(z->name, name) != 0) {
            if (strcmp(name, z->name) < 0) z = z->left;
            else z = z->right;
        }
        if (z == NIL) {
            cout << "Invalid Operation\n";
            return;
        }
        RBTNode *y = z;
        RBTNode *x;
        Color y_original_color = y->color;
        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = treeMinimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) x->parent = y;
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == BLACK) deleteFixup(x);
    }

    void print() {
        cout << "Directive-----------------> print-rbt\n";
        printRBT(root);
    }
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Please provide input file.\n";
        return 1;
    }
    ifstream infile(argv[1]);
    if (!infile) {
        cout << "Invalid input file.\n";
        return 1;
    }
    RBTree tree;
    string name;
    while (getline(infile, name)) {
        if (!name.empty()) tree.insert(name.c_str());
    }
    string cmd;
    while (getline(cin, cmd)) {
        if (cmd.rfind("insert", 0) == 0) {
            string x = cmd.substr(7);
            tree.insert(x.c_str());
        } else if (cmd.rfind("delete", 0) == 0) {
            string x = cmd.substr(7);
            tree.remove(x.c_str());
        } else if (cmd == "dfs") {
            tree.dfs();
        } else if (cmd.rfind("query", 0) == 0) {
            int d, f;
            sscanf(cmd.c_str(), "query %d %d", &d, &f);
            tree.query(d, f);
        } else if (cmd == "print-rbt") {
            tree.print();
        } else if (cmd == "quit") {
            cout << "Directive-----------------> quit\n";
            break;
        } else {
            cout << "Invalid Operation\n";
        }
    }
    return 0;
}
