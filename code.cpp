#include <bits/stdc++.h>
using namespace std;


// Function to compute Euclidean distance between two points

double dist(const vector<double> &p1, const vector<double> &p2) {
    assert(p1.size() == p2.size());
    double sum = 0;
    for (int i = 0; i < p1.size(); i++) {
        sum += ((p1[i] - p2[i]) * (p1[i] - p2[i]));
    }
    return sqrt(sum);
}


// Generalized Hyperplane Tree Node structure

struct GHNode {
    vector<double> p1, p2;                     // Pivots
    vector<vector<double>> points;             // Points in leaf
    GHNode* left = NULL;                       // Left child
    GHNode* right = NULL;                      // Right child
    bool isleaf = false;                       // Leaf flag
};


// Function to build GH Tree recursively

GHNode* build_tree(vector<vector<double>> &points, int leaf_size = 1) {
    if (points.size() == 0) return NULL;

    GHNode* node = new GHNode();

    if (points.size() <= leaf_size) {
        node->isleaf = true;
        node->points = points;
        return node;
    }

    vector<vector<double>> left;
    vector<vector<double>> right;

    node->p1 = points[0];

    int i = 1;
    while (i < points.size() && points[i] == points[0]) i++;

    if (i == points.size()) {
        node->isleaf = true;
        node->points = points;
        return node;
    } else {
        node->p2 = points[i];
    }

    // Partition the points based on distance to pivots
    for (auto pts : points) {
        if (dist(pts, node->p1) < dist(pts, node->p2))
            left.push_back(pts);
        else
            right.push_back(pts);
    }

    // Degenerate case: if one side is empty, stop splitting
    if (left.size() == 0 || right.size() == 0) {
        node->points = points;
        node->isleaf = true;
        return node;
    }

    // Recurse for both sides
    node->left = build_tree(left);
    node->right = build_tree(right);

    return node;
}


// Function to search for nearest neighbor in GH Tree

void GHsearch(double &best_dist, vector<double> &nearest_pt, GHNode* root, vector<double> &query) {
    if (!root) return;

    if (root->isleaf) {
        for (auto pts : root->points) {
            double d = dist(query, pts);
            if (d < best_dist) {
                nearest_pt = pts;
                best_dist = d;
            }
        }
        return;
    }

    double d_p1 = dist(query, root->p1);
    double d_p2 = dist(query, root->p2);

    GHNode* near = (d_p1 < d_p2) ? root->left : root->right;
    GHNode* far  = (d_p1 < d_p2) ? root->right : root->left;

    double d = abs(d_p1 - d_p2);

    GHsearch(best_dist, nearest_pt, near, query);

    if (d < best_dist) {
        GHsearch(best_dist, nearest_pt, far, query);
    }
}


// Function to deallocate GH Tree

void free_tree(GHNode* node) {
    if (!node) return;
    free_tree(node->left);
    free_tree(node->right);
    delete node;
}


// Main function

int main() {
    int num_points;
    int dimension;

    cout << "Enter No. of Points:" << endl;
    cin >> num_points;

    cout << "Enter the Dimension of the points:" << endl;
    cin >> dimension;

    vector<vector<double>> points(num_points, vector<double>(dimension));
    for (int i = 0; i < num_points; i++) {
        cout << "Enter point no. " << i + 1 << endl;
        for (int j = 0; j < dimension; j++) {
            cin >> points[i][j];
        }
    }
    
    if (points.empty()) {
    cout << "No points provided. Exiting." << endl;
    return 0;
}

    vector<double> query(dimension);
    cout << "Enter Query point" << endl;
    for (int i = 0; i < dimension; i++) {
        cin >> query[i];
    }

    GHNode* root = build_tree(points);
    vector<double> nearest_pt;
    double best_dist = numeric_limits<double>::max();

    GHsearch(best_dist, nearest_pt, root, query);

    cout << "Nearest point to the Query point is:" << endl;
    for (auto at : nearest_pt) {
        cout << at << " ";
    }
    cout << endl;

    cout << "Distance from the Nearest Neighbor to the Query point is:" << endl;
    cout << best_dist;

    free_tree(root);
}
