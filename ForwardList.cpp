#include <iostream>

template <typename T>
class Forward_List {
class Node {
public:
    Node(): value{} {
        next = nullptr;
    }
    Node(const T& m_value) {
        value = m_value;
    }
    Node(Node&& obj) {
        value = obj.value;
        next = obj.next;
    }
    Node(const Node& other): value{other.value}, next{other.next} {}
public:
    T value;
    Node* next;
};
private:
    Node* head;
public:
    Forward_List(): head{} {}
    Forward_List(int count) {
        head = new Node();
        auto curr = head;
        for(int i = 0; i < count - 1; ++i) {
            curr->next = new Node();
            curr = curr->next;
        }
    }
    Forward_List(int count, const T& value) {
        head = new Node(value);
        auto curr = head;
        for(int i = 0; i < count - 1; ++i) {
            curr->next = new Node(value);
            curr = curr->next;
        }
    }
    Forward_List(const Forward_List<T>& obj) {
        head = new Node(obj.head->value); 
        Node* curr = head;
        Node* curr1 = obj.head->next;
        while(curr1 != nullptr) {
            curr->next = new Node(curr1->value);
            curr = curr->next;
            curr1 = curr1->next;
        }
    }
    Forward_List(Forward_List&& obj) {
        head = obj.head;
        obj.head = nullptr;
    }
    ~Forward_List() {
        delete head;
        head = nullptr;
    }
    bool empty() const{
        return head == nullptr;
    }
    void print() const{
        auto curr = head;
        int i = 0;
        while(curr) {
            std::cout << i << ": -->" << curr->value << std::endl;
            curr = curr->next; 
        }
    }
    void clear() {
        delete head;
        head = nullptr;
    }
    void insert(const T& value, int pos) {
        auto curr = head;
        int i = 0;
        while(pos != i && curr != nullptr) {
            ++i;
            curr = curr->next;
        }
        Node* tmp = curr->next;
        tmp->value = value;
        curr->next = tmp;
        tmp = nullptr;
    }
    void erase_after(int pos) {
        auto curr = head;
        int i = 0;;
        while(i != pos && curr) {
            curr = curr->next;
            ++i;
        }
        if(curr->next) {
            Node* tmp = curr->next;
            curr->next = curr->next->next;
            tmp = nullptr;
        }
    } 
    void push_front(const T& value) {
        Node* tmp = new Node(value);
        tmp->next = head;
        head = tmp;
        tmp = nullptr;
    }
    void pop_front() {
        if(head != nullptr){
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    void unique() {
        auto curr = head;
        while(curr->next != nullptr) {
            if(curr->value == curr->next->value) {
                auto tmp = curr->next;
                curr->next = curr->next->next;
                delete tmp;
            }
            else {
                curr = curr->next;
            }
        }    
    }
    void sort() {
        auto curr = head;
        int i = 0;
        while(curr != nullptr) {
            ++i;
            curr = curr->next;
        }
        curr = head;
        for(int j = i - 1 ; j > 0; j--) {
            curr = head;
            for(int k = 0; k < j; k++) {
                if(curr->value > curr->next->value){
                    T tmp = curr->value;
                    curr->value = curr->next->value;
                    curr->next->value = tmp;
                }
                curr = curr->next;
            }
        }
    }
};

int main() {
    Forward_List<int> f1(3,4);
    f1.push_front(1239);
    f1.push_front(1);
    f1.push_front(5);
    f1.push_front(10);
    f1.push_front(8);
    f1.push_front(9);
    f1.sort();
    f1.print();
}