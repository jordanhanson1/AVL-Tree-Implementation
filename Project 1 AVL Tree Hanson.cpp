#include <iostream>
#include <string>
#include <vector>

//header for Avl tree
class AvlTree {
public:

    //node class to store data
    class Node {
    public:
        Node() {
            right = nullptr;
            left = nullptr;
            name = "";
            id = 0;
        };
        Node& operator=(Node* nod) {
            right = nod->right;
            left = nod->left;
            name = nod->name;
            id = nod->id;
        };

        std::string name;
        long id;
        Node* right;
        Node* left;
    };

    //store root of tree and success strings
    Node* root;
    std::string success = "successful";
    std::string unsuccess = "unsuccessful";

    //max int helper fucntion
    int maxInt(int a, int b);

    //insert and remove
    Node* Insert(Node* nod, long id, std::string nam);
    bool Remove(Node* rot, long id);

    //healper functions
    Node* min(Node* nod);
    int CheckBalance(Node* rot);
    
    //rotation functions for balance
    Node* RotateLeft(Node* node);
    Node* RotateRight(Node* node);
    Node* RotateLeftRight(Node* node);
    Node* RotateRightLeft(Node* node);

    //height function find height of sub tree
    int Height(Node* node);


    //search for a node or id and return node
    Node* Search(Node* rot, std::string nam);
    Node* SearchId(Node* rot, long id);

    //remove in order finds the node in order and then call remove in main
    Node* RemoveInorder(Node* rot, int index, std::vector<long>& vec, int& count);

    //searches for name inorder and adds to vector
    void SearchName(Node* root, std::string name, std::vector<long>& ids);

    //print functions
    void PrintPostOrder(Node* rot, std::vector<std::string>& vec);
    void PrintPreorder(Node* rot, std::vector<std::string>& vec);
    void PrintInorder(Node* rot, std::vector<std::string>& vec);

    //default constructor
    AvlTree();


};

AvlTree::Node* AvlTree::RotateLeft(Node* node) {

    //rotate left and replace root if needed
    Node* after = node->right;
    node->right = after->left;
    after->left = node;

    if (node->id == root->id) {
        root = after;
    }
    return after;
}

//rotation function
AvlTree::Node* AvlTree::RotateRight(Node* node){

    //rotate right and replace root if needed
    Node* child = node->left;
    node->left = child->right;
    child->right = node;
    if (node->id == root->id) {
        root = child;
    }
    return child;

}

AvlTree::Node* AvlTree::RotateLeftRight(Node* node)
{
    //rotate left child left then rotate node right
    node->left = RotateLeft(node->left);
    Node* ret = RotateRight(node);
    return ret;

}

AvlTree::Node* AvlTree::RotateRightLeft(Node* node) {

    //rotate right child right then rotate node left
    node->right = RotateRight(node->right);
    return RotateLeft(node);

}

//takes in root node and id and name to insert
//returns ancestor node
AvlTree::Node* AvlTree::Insert(Node* rot, long id, std::string nam) {

    //if no root add new root
    if (root == nullptr) {
        Node* newNode = new Node();
        newNode->id = id;
        newNode->name = nam;
        root = newNode;
        return newNode;
    }

    // if rot or root is nullptr or empty make a new node and return it
    if (rot == nullptr) {
        Node* newNode = new Node();
        newNode->id = id;
        newNode->name = nam;
        return newNode;
    }

    //recursivly change childs till its a leaf
    if (rot->id < id) {
        rot->right = Insert(rot->right, id, nam);
    }
    else {
        rot->left = Insert(rot->left, id, nam);
    }

    //check the balance factor with helper functions
    int bFactor = CheckBalance(rot);
    

    //rotate if necessary based on conditions
    if (bFactor > 1) {
        if (id < rot->left->id) {
            return RotateRight(rot);
        }
        else if (id > rot->left->id) {
            return RotateLeftRight(rot);
        }
    }


    if (bFactor < -1) {
        if (id < rot->right->id) {
            return RotateRightLeft(rot);
        }
        else if (id > rot->right->id) {
            return RotateLeft(rot);
        }
    }

    //return ancestor of new node
    return rot;
}

//return balance factor
int AvlTree::CheckBalance(Node* nod) {

    //balance = left height - right subtree height
    int heightL = Height(nod->left);
    int heightR = Height(nod->right);
    return heightL - heightR;
}

//basic max function
int AvlTree::maxInt(int one, int two) {
    if (one > two) {
        return one;
    }
    else {
        return two;
    }
}

//find height function using recursion
//go there each node and return max height of left and right subtree
int AvlTree::Height(Node* nod) {

    //nothing to search
    if (nod == nullptr) {
        return 0;
    }

    //add one each time and return max height of left or right subtree
    return (1 + maxInt(Height(nod->left), Height(nod->right)));
}

void AvlTree::PrintPostOrder(Node* rot, std::vector<std::string>& vec) {
    //exit if empty
    if (rot == nullptr) {
        return;
    }

    //go left then right recursivly
    PrintPostOrder(rot->left, vec);
    PrintPostOrder(rot->right, vec);

    //put in vector that is gonna be printed
    vec.push_back(rot->name);
}


//default constructor
AvlTree::AvlTree() {

    //start with 0 and nullptr
    root = nullptr;

}

//search function return node
AvlTree::Node* AvlTree::Search(Node* rot, std::string nam) {

    //if nothing to search return nullptr
    if (rot == nullptr) {
        return rot;
    }

    //if found return it
    if (rot->name.compare(nam) == 0) {
        return rot;
    }

    //check left subtree and return if not nullptr
    Node* left = Search(rot->left, nam);
    if (left != nullptr) {
        return left;
    }

    //same as left with right subtree
    Node* right = Search(rot->right, nam);
    if (right != nullptr) {
        return right;
    }

    //if cant find return nullptr
    return nullptr;
}


//search tree and return parent node
AvlTree::Node* AvlTree::SearchId(Node* rot, long id) {

    //if is nullptr return it base case
    if (rot == nullptr) {
        return rot;
    }

    //check left for id
    if (rot->left != nullptr) {
        if (rot->left->id == id) {
            return rot;
        }
    }

    //check right for id
    if (rot->right != nullptr) {
        if (rot->right->id == id) {
            return rot;
        }
    }

    //if id is smaller then go right
    if (rot->id < id) {
        return SearchId(rot->right, id);
    }
    //if id is bigger then go left
    else {
        return SearchId(rot->left, id);
    }
  

}

//find min node
//helper function for delete
AvlTree::Node* AvlTree::min(Node* nod) {
    if (nod->left == nullptr) {
        return nod;
    }
    else {
        return min(nod->left);
    }

}


//remove function with a root and id
bool AvlTree::Remove(Node* rot, long id) {

    //if tree is empty
    if (rot == nullptr) {
        return false;
    }

    //find parent with helper function
    Node* nodDelete = root;
    Node* parent;
    parent = SearchId(root, id);

    //if parent isnt nullptr
    if (parent != nullptr) {

        //check for id
        if (parent->left->id == id) {
            nodDelete = parent->left;
        }
        if (parent->right->id == id) {
            nodDelete = parent->right;
        }
    }

    //if parent is null and havent foudn yet
    if (nodDelete->id != id && parent == nullptr) {
        return false;
    }
    //node to delete has 2 childs have to replace it with smallest node
    if (nodDelete->left != nullptr && nodDelete->right != nullptr) {
        Node* replace;
        replace = min(nodDelete->right);
        long valReplace = replace->id;
        std::string naem = replace->name;

        //call recursivly delete on replace
        Remove(root, valReplace);

        //swap min with delete node
        nodDelete->id = valReplace;
        nodDelete->name = naem;
    }

    //if node to delete is at bottom
    else if (nodDelete->left == nullptr && nodDelete->right == nullptr) {

        //if its the root then set to nullptr and delete if not
        if (nodDelete->id != root->id) {

            //set child of parent to nullptr depending on left or right
            if (parent->left->id == nodDelete->id) {
                parent->left = nullptr;
            }
            else {
                parent->right = nullptr;
            }
        }

        //if its root then set root=nullptr
        else {
            root = nullptr;
        }
        delete nodDelete;
    }

    //delete node with 1 succesor
    else {

        Node* temp;
        if (nodDelete->left != nullptr) {
            temp = nodDelete->left;
        }
        else {
            temp = nodDelete->right;
        }

        if (nodDelete->id == root->id) {
            root = temp;
        }
        else {
            if (parent->right->id == nodDelete->id) {
                parent->right = temp;
            }
            else {
                parent->left = temp;
            }
        }
        delete nodDelete;
    }
    return true;
}

//print functions


void AvlTree::PrintPreorder(Node* rot, std::vector<std::string>& vec) {
    if (rot == nullptr) {
        return;
    }
    //add then recurse left then right
    vec.push_back(rot->name);
    if (rot->left != nullptr) {
        PrintPreorder(rot->left, vec);
    }
    if (rot->right != nullptr) {
        PrintPreorder(rot->right, vec);
    }

}

void AvlTree::PrintInorder(Node* rot, std::vector<std::string>& vec) {
    if (rot == nullptr) {
        return;
    }
    //go left then add to vector then add to right
    if (rot->left != nullptr) {
        PrintInorder(rot->left, vec);
    }
    vec.push_back(rot->name);
    if (rot->right != nullptr) {
        PrintInorder(rot->right, vec);
    }
}



//remove in order goes in order till get to index then return it
AvlTree::Node* AvlTree::RemoveInorder(Node* rot, int index, std::vector<long>& vec, int& count) {

    //while count is smaller than index
    if (count < index) {

        //go left then check condition then go right
        if (rot->left != nullptr) {
            RemoveInorder(rot->left, index, vec, count);
        }

        //when count is reached return nod
        count++;
        if (count == index) {
            return rot;
        }
        if (rot->right != nullptr) {
            RemoveInorder(rot->right, index, vec, count);
        }
    }

    //if over index return nullptr
    else {
        return nullptr;
    }
}


//search each node for name
void AvlTree::SearchName(Node* rot, std::string nam, std::vector<long>& vec) {

    //if node is null exit
    if (rot == nullptr) {
        return;
    }

    // go left then check if name and add to vector ref
    SearchName(rot->left, nam, vec);
    if (rot->name.compare(nam) == 0) {
        vec.push_back(rot->id);
    }

    //search right subtree
    SearchName(rot->right, nam, vec);

}
int main() {

    //tree object
    AvlTree tree;
    std::string input;
    std::string command;
    int numCommands = 0;
    std::cin >> numCommands;

    for (int i = 0; i < numCommands + 1; i++)
    {
        std::getline(std::cin, input);
        if (input.find(' ') != std::string::npos) {
            command = input.substr(0, input.find(' '));
        }
        else {
            command = input;
        }

        if (command.compare("insert") == 0) {


            std::string name = input.substr(input.find('"') + 1);
            name = name.substr(0, name.find('"'));
            bool isValid = true;

            //check if valid name
            for (char& c : name) {
                if ((c < 'a' || c > 'z')&&(c < 'A' || c > 'Z')&&c!=' ')
                    isValid = false;
            }


            std::string sub = input.substr(input.find('"') + 1);
            std::string ed = sub.substr(sub.find('"') + 2);

            //if the id is right size and name is valid
            if (ed.size() == 8 && isValid==true ) {
                bool isDig = true;
                for (char& c : ed) {
                    if (c < '0' || c > '9')
                        isDig=false;
                }
                if (isDig != false) {
                    long id = std::stol(ed);
                    tree.Insert(tree.root, id, name);
                    std::cout << tree.success << std::endl;
                }
                else {
                    std::cout << tree.unsuccess << std::endl;
                }
                
            }
            else {
                std::cout << tree.unsuccess << std::endl;
            }
        }

        //print post order based on vector found with function
        if (command.compare("printPostorder") == 0) {

            //get vector
            std::vector<std::string> vec;
            tree.PrintPostOrder(tree.root, vec);

            //print with comma
            for (unsigned int i = 0; i < vec.size() - 1;i++) {
                std::cout << vec.at(i) << ", ";
            }
            if (vec.size() != 0) {
                std::cout << vec.at(vec.size() - 1) << std::endl;
            }
        }

        //print level count with height function
        if (command.compare("printLevelCount") == 0) {
            int height = tree.Height(tree.root);
            std::cout << height << std::endl;
        }


        if (command.compare("printInorder") == 0) {
            std::vector<std::string> vec;
            tree.PrintInorder(tree.root, vec);
            for (unsigned int i = 0;i < vec.size() - 1;i++) {
                std::cout << vec.at(i) << ", ";
            }
            if (vec.size() != 0) {
                std::cout << vec.at(vec.size() - 1) << std::endl;
            }
        }


        if (command.compare("printPreorder") == 0) {
            std::vector<std::string> vec;
            tree.PrintPreorder(tree.root, vec);
            for (unsigned int i = 0;i < vec.size() - 1;i++) {
                std::cout << vec.at(i) << ", ";
            }
            if (vec.size() != 0) {
                std::cout << vec.at(vec.size() - 1) << std::endl;
            }
        }



        if (command.compare("remove") == 0) {
            long id = std::stol(input.substr(input.find(' ')));
            bool succ = tree.Remove(tree.root, id);
            if (succ == true) {
                std::cout << tree.success << std::endl;
            }
            else {
                std::cout << tree.unsuccess << std::endl;
            }
        }



        //remove by finding node with remove in order function first
        if (command.compare("removeInorder") == 0) {
            int ind = std::stoi(input.substr(input.find(' '))) + 1;
            std::vector<long> vec;
            int count = 0;
            AvlTree::Node* ned;
            bool succ = false;
            ned = tree.RemoveInorder(tree.root, ind, vec, count);
            if (ned != nullptr) {
                succ = tree.Remove(tree.root, ned->id);
            }
            if (succ == true) {
                std::cout << tree.success << std::endl;
            }
            else {
                std::cout << tree.unsuccess << std::endl;
            }
        }

        //search command for both id and name
        if (command.compare("search") == 0) {
            std::string intro = input.substr(input.find(' '));
            AvlTree::Node* nod = nullptr;
            AvlTree::Node* prin = nullptr;

            //if no quotation search for id
            if (intro.find('"') == std::string::npos) {
                long ed = std::stoi(intro);
                if (tree.root != nullptr) {
                    if (tree.root->id == ed) {
                        std::cout << tree.root->name << std::endl;
                    }
                    else {
                        nod = tree.SearchId(tree.root, ed);
                        if (nod != nullptr) {
                            if (nod->left != nullptr) {
                                if (nod->left->id == ed) {
                                    std::cout << nod->left->name << std::endl;
                                }
                            }
                            if (nod->right != nullptr) {
                                if (nod->right->id == ed) {
                                    std::cout << nod->right->name << std::endl;
                                }
                            }
                        }
                        else {
                            std::cout << tree.unsuccess << std::endl;
                        }
                    }
                }
                else {
                    std::cout << tree.unsuccess << std::endl;
                }

            }


            //has quotes search for name
            else {
                std::string name = input.substr(input.find('"') + 1);
                name = name.substr(0, name.find('"'));
                std::vector<long> ids;
                tree.SearchName(tree.root, name, ids);

                //print out ids of name
                for (unsigned int i = 0; i < ids.size(); i++) {
                    std::string print = std::to_string(ids.at(i));

                    //check case that id is 00000001
                    int numZero = 8 - print.size();
                    for (unsigned int s = 0; s < numZero; s++) {
                        std::cout << 0;
                    }
                    std::cout << ids.at(i) << std::endl;
                }

                //if no id print out unsucesse
                if (ids.size() == 0) {
                    std::cout << tree.unsuccess << std::endl;
                }
            }


        }

    }
}