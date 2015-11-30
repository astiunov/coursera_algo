#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> data(n);
    for (int i = 0; i < n; ++i) {
        cin >> data[i].type;
        if (data[i].type == "add")
            cin >> data[i].number >> data[i].name;
        else
            cin >> data[i].number;
    }
    return data;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(vector<Query> data) {
    vector<string> result;
    for (size_t i = 0; i < data.size(); ++i)
        if (data[i].type == "del") {
            for (size_t j = 0; j < i; ++j)
                if (data[j].type == "add" && data[j].number == data[i].number) {
                    data[j].name = "empty";
                    break;
                }
        } else if (data[i].type == "find") {
            string cur_res = "empty";
            for (size_t j = 0; j < i; ++j)
                if (data[j].type == "add" && data[j].number == data[i].number) {
                    cur_res.swap(data[j].name);
                    break;
                }
            result.push_back(cur_res);

        }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
