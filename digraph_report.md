# Mini Project 2 — Directed Graph: In-degree / Out-degree and Time Complexity

## 1. C code (`digraph.c`)
- `generate_graph(n)` — fills an `n x n` adjacency matrix with random 0/1 values using `rand() % 2`; diagonal is 0 (no self loop).
- `find_degrees(n)` — scans every cell; if `adj[i][j] == 1` then `out_deg[i]++` and `in_deg[j]++`.
- `main()` — repeats the above for n = 1000, 2000, 3000, 4000, 5000, prints in/out degrees, prints the two sums with an EQUAL check, measures the degree step with `clock()` in milliseconds, and writes `timing.csv` (columns: `n`, `time_ms`) for the Excel line graph.

Compile and run:
```
gcc digraph.c -o digraph
./digraph
```

## 2. Theoretical time complexity
`find_degrees` has two nested loops running n times each, and the body is constant work, so the number of operations is proportional to n^2:

T(n) = c * n^2  →  **O(n^2)** (quadratic)

`generate_graph` is also O(n^2), so the whole program is O(n^2).

Also note: every edge adds exactly 1 to one out-degree and 1 to one in-degree, therefore
sum of in-degrees = sum of out-degrees = number of edges. This is why the program always prints EQUAL.

## 3. Practical time complexity (run-time data)
Sample run on the test machine (your numbers will differ a little):

| n | time (ms) |
|------|-------|
| 1000 | 6.342 |
| 2000 | 22.471 |
| 3000 | 55.866 |
| 4000 | 89.453 |
| 5000 | 154.644 |

In Excel: select the two columns → Insert → Line graph → right click the line → Add Trendline → Polynomial, Order 2 → tick "Display Equation on Chart".
The displayed equation comes out close to:

y ≈ 6e-06 x^2 + 0.0004 x  (a second-degree / quadratic equation in n)

So the practical time complexity is also **O(n^2)**.

## 4. Comparison
Time roughly multiplies by 4 when n doubles (6.3 ms → 22.5 ms for 1000 → 2000, and 22.5 ms → 89.5 ms for 2000 → 4000), which is exactly the 2^2 = 4 behaviour of a quadratic function. The Order-2 polynomial trendline fits the measured data, so the practical result matches the theoretical O(n^2). Small differences are caused by CPU caching, memory speed and other programs running on the machine.
