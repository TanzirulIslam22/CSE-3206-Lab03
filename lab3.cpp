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


