#include<bits/stdc++.h>

using namespace std;

// Helper: Euclidean distance
double euclideanDistance(const vector<double>& a, const vector<double>& b) {
    assert(a.size() == b.size());
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i)
        sum += (a[i] - b[i]) * (a[i] - b[i]);
    return sqrt(sum);
}

// Node structure

struct GHNode {
    vector<double> p1; // First pivot
    vector<double> p2; // Second pivot

    vector<vector<double>> points; // Points at leaf node

    unique_ptr<GHNode> left;
    unique_ptr<GHNode> right;

    bool isLeaf = false;
};

// Build GH Tree

unique_ptr<GHNode> buildGHTree(const vector<vector<double>>& points, int leafSize = 1) {
    if (points.empty()) return nullptr;

    auto node = make_unique<GHNode>();

    if (points.size() <= leafSize) {
        node->points = points;
        node->isLeaf = true;
        return node;
    }

    // Pick first point as pivot 1
    node->p1 = points[0];

    // Pick pivot 2: find first different point
    size_t i = 1;
    while (i < points.size() && points[i] == node->p1) i++;
    if (i == points.size()) {
        // All points identical → make leaf
        node->points = points;
        node->isLeaf = true;
        return node;
    }
    node->p2 = points[i];

    // Partition points by hyperplane
    vector<vector<double>> leftSet, rightSet;
    for (const auto& pt : points) {
        double d1 = euclideanDistance(pt, node->p1);
        double d2 = euclideanDistance(pt, node->p2);
        if (d1 < d2) leftSet.push_back(pt);
        else rightSet.push_back(pt);
    }

    // Degenerate split check: if one side empty, stop splitting
    if (leftSet.empty() || rightSet.empty()) {
        node->points = points;
        node->isLeaf = true;
        return node;
    }

    node->left = buildGHTree(leftSet, leafSize);
    node->right = buildGHTree(rightSet, leafSize);

    return node;
}

// Search GH Tree for nearest neighbor

void searchGHTree(
    GHNode* node,
    const vector<double>& query,
    vector<double>& bestPoint,
    double& bestDist
) {
    if (!node) return;

    if (node->isLeaf) {
        for (const auto& pt : node->points) {
            double d = euclideanDistance(query, pt);
            if (d < bestDist) {
                bestDist = d;
                bestPoint = pt;
            }
        }
        return;
    }

    double d_p1 = euclideanDistance(query, node->p1);
    double d_p2 = euclideanDistance(query, node->p2);

    GHNode* nearChild = (d_p1 < d_p2) ? node->left.get() : node->right.get();
    GHNode* farChild  = (d_p1 < d_p2) ? node->right.get() : node->left.get();

    // --- Correct pruning condition (with 1/2 factor) ---
    double margin = fabs(d_p1 - d_p2);

    searchGHTree(nearChild, query, bestPoint, bestDist);

    if (0.5 * margin < bestDist) {
        searchGHTree(farChild, query, bestPoint, bestDist);
    }
}


// Main

int main() {
    int numPoints, dimension;
    cout << "Enter number of points: ";
    cin >> numPoints;
    cout << "Enter dimension: ";
    cin >> dimension;

    vector<vector<double>> points(numPoints, vector<double>(dimension));
    cout << "Enter each point as " << dimension << " coordinates:\n";
    for (int i = 0; i < numPoints; ++i) {
        cout << "Point " << i + 1 << ": ";
        for (int j = 0; j < dimension; ++j) {
            cin >> points[i][j];
        }
    }

    cout << "\nBuilding Generalized Hyperplane Tree...\n";
    auto tree = buildGHTree(points);

    vector<double> query(dimension);
    cout << "\nEnter query point: ";
    for (int j = 0; j < dimension; ++j) {
        cin >> query[j];
    }

    assert(query.size() == dimension);

    vector<double> nearestNeighbor;
    double bestDist = numeric_limits<double>::max();

    searchGHTree(tree.get(), query, nearestNeighbor, bestDist);

    cout << "\nNearest Neighbor: ";
    for (double x : nearestNeighbor) cout << x << " ";
    cout << "\nDistance: " << bestDist << endl;

    return 0;
}
