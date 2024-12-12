#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<tuple<int, int>> directions = { make_tuple(0, 1), make_tuple(1, 0), make_tuple(-1, 0), make_tuple(0, -1) };

vector<vector<int>> grid = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

vector<tuple<int, int>> bfs(tuple<int, int> start, tuple<int, int> end) {
    queue<tuple<int, int>> q;
    unordered_set<string> visited;
    unordered_map<string, tuple<int, int>> parent;
    vector<tuple<int, int>> path;

    q.push(start);
    visited.insert(to_string(get<0>(start)) + "," + to_string(get<1>(start)));

    while (!q.empty()) {
        tuple<int, int> current = q.front();
        q.pop();

        if (current == end) {
            while (current != start) {
                path.push_back(current);
                current = parent[to_string(get<0>(current)) + "," + to_string(get<1>(current))];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        for (auto dir : directions) {
            tuple<int, int> next = make_tuple(get<0>(current) + get<0>(dir), get<1>(current) + get<1>(dir));

            if (get<0>(next) >= 0 && get<1>(next) >= 0 && get<0>(next) < grid.size() && get<1>(next) < grid[0].size() && grid[get<0>(next)][get<1>(next)] == 1) {
                string nextStr = to_string(get<0>(next)) + "," + to_string(get<1>(next));
                if (visited.find(nextStr) == visited.end()) {
                    q.push(next);
                    visited.insert(nextStr);
                    parent[nextStr] = current;
                }
            }
        }
    }

    return path;
}

int main() {
    tuple<int, int> start = make_tuple(13, 0);
    tuple<int, int> end = make_tuple(1, 14);

    vector<tuple<int, int>> path = bfs(start, end);

    if (path.empty()) {
        cout << "No path found!" << endl;
    }
    else {
        cout << "Path found: ";
        for (auto p : path) {
            cout << "[" << get<0>(p) << ", " << get<1>(p) << "] ";
        }
        cout << endl;
    }

    return 0;
}
