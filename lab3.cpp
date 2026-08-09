#include <bits/stdc++.h>

using namespace std;

// 1. The Observer Interface
class IObserver {
public:
    virtual void onTextChanged(const string& currentText) = 0;
    virtual ~IObserver() = default;
};

// 2. A Concrete Observer: Live Word Counter
class WordCounter : public IObserver {
public:
    void onTextChanged(const string& currentText) override {
        int words = currentText.empty() ? 0 : 1;
        for (char c : currentText) {
            if (c == ' ') words++;
        }
        cout << "   -> [Plugin] Word Count: " << (currentText.empty() ? 0 : words) << "\n";
    }
};

// Another Concrete Observer: Spell Checker
class SpellChecker : public IObserver {
public:
    void onTextChanged(const string& currentText) override {
        cout << "   -> [Plugin] Spell Checker: Checking spelling...\n";
        if (currentText.find("helloo") != string::npos) {
            cout << "      [Warning] Typo detected: 'helloo' might be misspelled!\n";
        }
        if (currentText.find("worldd") != string::npos) {
            cout << "      [Warning] Typo detected: 'worldd' might be misspelled!\n";
        }
    }
};

// 3. The Subject: Broadcasts changes
class EditorEventPublisher {
private:
    vector<shared_ptr<IObserver>> observers;
public:
    void subscribe(shared_ptr<IObserver> observer) {
        observers.push_back(observer);
    }
    
    void notifySubscribers(const string& text) {
        for (auto& obs : observers) {
            obs->onTextChanged(text);
        }
    }
};

// 4. The Memento: A hidden snapshot of the text
class EditorMemento {
private:
    string state;
public:
    EditorMemento(const string& text) : state(text) {}
    string getSavedState() const { return state; }
};

// 5. The Caretaker: Manages the history of snapshots
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

// The Originator: The actual text editor combining both patterns
class SmartTextEditor : public EditorEventPublisher
{
private:
    string document;

public:
    // Core Feature: Write text
    void write(const string &text)
    {
        document += text + " ";
        notifySubscribers(document); // Trigger Member 2's Observers
    }

    // Memento Feature: Create snapshot for Member 1's HistoryManager
    shared_ptr<EditorMemento> createSnapshot()
    {
        return make_shared<EditorMemento>(document);
    }

    // Memento Feature: Restore from snapshot
    void restore(shared_ptr<EditorMemento> memento)
    {
        if (memento)
        {
            document = memento->getSavedState();
        }
        else
        {
            document = "";
        }
        cout << "\n--- UNDO TRIGGERED ---\n";
        notifySubscribers(document); // Alert observers of the restored state
    }

    void printDocument()
    {
        cout << "Document: " << document << "\n";
    }
};

