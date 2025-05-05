
# Understanding `mid = (l + r) / 2` vs. `mid = l + (r - l) / 2`

In binary search and similar algorithms, calculating the midpoint correctly is crucial for both correctness and safety.

---

## ✅ Option 1: `mid = (l + r) / 2`

### Pros:
- Simple and easy to understand.
- Works well when `l` and `r` are within a small, safe range (e.g., competitive programming or LeetCode-style problems).

### Cons:
- **Risk of integer overflow** when `l` and `r` are large.
- Example of overflow:

  ```cpp
  int l = INT_MAX - 1;
  int r = INT_MAX;
  int mid = (l + r) / 2;  // This can overflow!
  ```

  - `INT_MAX` for a 32-bit signed integer is 2,147,483,647.
  - Adding two large numbers like `l + r` may exceed the max `int` value and cause undefined behavior.

---

## ✅ Option 2: `mid = l + (r - l) / 2`

### Pros:
- Mathematically equivalent to `(l + r) / 2`, but avoids direct addition of two potentially large numbers.
- Eliminates the possibility of overflow in the calculation.
- Works safely even when `l` and `r` are near `INT_MAX`.

### How it works:
- Instead of computing the midpoint directly from the sum, it calculates the offset from `l`:

  ```cpp
  int mid = l + (r - l) / 2;
  ```

- This rearrangement ensures the arithmetic stays within safe bounds.

---

## 💡 Which One Should You Use?

| Scenario                      | Recommended Expression         |
|-------------------------------|--------------------------------|
| Coding interviews             | `(l + r) / 2` is fine          |
| Small datasets or problems    | `(l + r) / 2` is acceptable    |
| Production code               | ✅ `l + (r - l) / 2`            |
| Working with large numbers    | ✅ `l + (r - l) / 2`            |
| Performance-critical systems  | ✅ `l + (r - l) / 2`            |

---

## 📌 Summary

While `(l + r) / 2` is simpler and may be fine in controlled environments, it's good practice to use the safer version `l + (r - l) / 2` — especially in production-grade or performance-critical code — to avoid potential overflow and ensure correctness under all conditions.
