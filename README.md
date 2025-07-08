# Generalized Hyperplane Tree (GHT) Nearest Neighbor Search

This project implements a **Generalized Hyperplane Tree (GHT)** in C++ for performing efficient **nearest neighbor search** in high-dimensional space using Euclidean distance.

---

## 🧠 Key Features

- Builds a binary GHT for given multidimensional points  
- Efficient nearest neighbor querying using a recursive tree search  
- Handles:
  - Identical input points  
  - High-dimensional data  
  - Edge cases like empty input, single point, duplicate entries  
- Uses **Euclidean distance** as the metric  

---

## 📂 File Structure

```
.
├── main.cpp        # Complete GHT implementation and nearest neighbor query
└── README.md       # This file
```

---

## 🛠️ How It Works

1. **Tree Construction (`build_tree`)**:
   - Recursively selects two pivot points from the dataset.
   - Splits the data based on which pivot each point is closer to.
   - Stops splitting when a leaf has `≤ leaf_size` points or degenerate cases occur.

2. **Querying (`GHsearch`)**:
   - Searches recursively down the "near" child.
   - Prunes the "far" child if it's guaranteed not to contain a closer point (based on triangle inequality).

3. **Cleanup (`free_tree`)**:
   - Frees all dynamically allocated tree nodes after use.

---

## 📌 Sample Input

```
Enter No. of Points:
3
Enter the Dimension of the points:
2
Enter point no. 1
0 0
Enter point no. 2
3 4
Enter point no. 3
5 12
Enter Query point
3 4
```

**Output:**
```
Nearest point to the Query point is:
3 4 
Distance from the Nearest Neighbor to the Query point is:
0
```

---

## ✅ Edge Cases Handled

- ✅ Query point matches one of the input points  
- ✅ All points are identical  
- ✅ Empty input (graceful exit)  
- ✅ High dimensional vectors (e.g., 10D, 100D)  
- ✅ Single input point  

---

## 🚀 Getting Started

### Compile and Run

```bash
g++ main.cpp -o ghtree
./ghtree
```

### Requirements

- C++17 or later
- Standard libraries (`<iostream>`, `<vector>`, `<cmath>`, etc.)

---

## 📌 Notes

- Distance calculation uses `sqrt(sum((xi - yi)^2))`.
- Assert checks ensure dimension consistency between points.
- You can adjust the `leaf_size` parameter in `build_tree()` for performance tuning.

---

## 📜 License

This project is open source and free to use for academic, research, or personal use.

---

## 🙌 Acknowledgements

- Inspired by space-partitioning tree data structures  
- Designed and implemented with flexibility and robustness in mind

---

## 🔗 Related Concepts

- KD-Tree  
- Ball Tree  
- Metric Trees  
- Nearest Neighbor Search
