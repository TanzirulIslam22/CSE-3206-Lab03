#include <bits/stdc++.h>

using namespace std;

// 1. The Memento: A hidden snapshot of the text
class EditorMemento {
private:
    string state;
public:
    EditorMemento(const string& text) : state(text) {}
    string getSavedState() const { return state; }
};

// 2. The Caretaker: Manages the history of snapshots
class HistoryManager {
private:
    vector<shared_ptr<EditorMemento>> history;
public:
    void saveState(shared_ptr<EditorMemento> memento) {
        history.push_back(memento);
    }

    shared_ptr<EditorMemento> undo() {
        if (history.empty()) return nullptr;
        
        history.pop_back(); // Remove current state
        if (history.empty()) return make_shared<EditorMemento>(""); // Return to empty
        
        return history.back(); // Return the previous state
    }
};

