#include <bits/stdc++.h>
using namespace std;

const int MaxDataSize = 100;
const int INF = 1e9;

int V, E, F;
int CapacityInfo[MaxDataSize][MaxDataSize];
int CostInfo[MaxDataSize][MaxDataSize];
int FlowInfo[MaxDataSize][MaxDataSize];
int Previous[MaxDataSize];
int Distance[MaxDataSize];

bool findAugmentingPath(const int start, const int end, int &curMinFlow) {
    int curNode;
    queue<int> nodeList;

    fill(Distance, Distance + MaxDataSize, INF);

    Distance[start] = 0;
    nodeList.push(start);
    while (!nodeList.empty()) {
        curNode = nodeList.front();
        nodeList.pop();

        for (int next = 0; next < V; ++next) {
            if (CapacityInfo[curNode][next] > FlowInfo[curNode][next] &&
                Distance[next] > Distance[curNode] + CostInfo[curNode][next]) {
                Distance[next] = Distance[curNode] + CostInfo[curNode][next];
                curMinFlow = min(curMinFlow, CapacityInfo[curNode][next] - FlowInfo[curNode][next]);
                Previous[next] = curNode;
                nodeList.push(next);
            }
        }
    }

    if (Distance[end] == INF) {
        return false;
    }
    return true;
}

void solve(const int start, const int end) {
    int minCost, curMinFlow;

    fill(FlowInfo[0], FlowInfo[0] + MaxDataSize*MaxDataSize, 0);
    fill(Previous, Previous + MaxDataSize, 0);

    minCost = 0;
    while (true) {
        curMinFlow = INF;
        if (!findAugmentingPath(start, end, curMinFlow)) {
            if (F > 0) {
                minCost = -1;
            }
            break;
        }

        curMinFlow = min(curMinFlow, F);
        minCost += Distance[end] * curMinFlow;
        //cout << "current Min Flow = " << curMinFlow << endl;
        //cout << "current Min Dist=" << Distance[end] << endl;
        //cout << "Ans=" << minCost << endl;
        F -= curMinFlow;
        if (F <= 0) {
            break;
        }
        for (int next = end; next != start; next = Previous[next]) {
            FlowInfo[Previous[next]][next] += curMinFlow;
            FlowInfo[next][Previous[next]] -= curMinFlow;
        }
    }

    cout << minCost << endl;
}

int main() {
    int u, v, c, d;

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    fill(CapacityInfo[0], CapacityInfo[0] + MaxDataSize*MaxDataSize, 0);
    fill(CostInfo[0], CostInfo[0] + MaxDataSize*MaxDataSize, INF);

    cin >> V >> E >> F;
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> c >> d;
        CapacityInfo[u][v] = c;
        CostInfo[u][v] = d;
        CostInfo[v][u] = -d;
    }
    solve(0, V - 1);

    return 0;
}