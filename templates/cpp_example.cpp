#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cin;

struct Query {
    string type, name;
    int number;
};


class QueryProcessor {
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query> contacts;
    void writeResponse(const string& resp) const {
        std::cout << resp << "\n";
    }
    void processQuery(const Query& query) {
        if (query.type == "add") {
            bool was_found = false;
            // if we already have contact with such number,
            // we should rewrite contact's name
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == query.number) {
                    contacts[j].name = query.name;
                    was_found = true;
                    break;
                }
            // otherwise, just add it
            if (!was_found)
                contacts.push_back(query);
        } else if (query.type == "del") {
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == query.number) {
                    contacts.erase(contacts.begin() + j);
                    break;
                }
        } else {
            string response = "empty";
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == query.number) {
                    response = contacts[j].name;
                    break;
                }
            writeResponse(response);
        }
    }
    Query readQuery() const {
        Query query;
        cin >> query.type >> query.number;
        if (query.type == "add")
            cin >> query.name;
        return query;
    }
public:
    void processQueries() {
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    QueryProcessor proc;
    proc.processQueries();
    return 0;
}


