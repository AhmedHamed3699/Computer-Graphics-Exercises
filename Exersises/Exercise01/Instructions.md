# Graphics Exercise 01: Rasterization (Integer coordinates only)

**Learning goals:**
- Implement line and triangle rasterization algorithms in C++.
- Exercise line and triangle rasterization by hand.

This exercise is divided into two parts: a programming part and a handwritten part. For each part, there are different tiers of required work. It is enough to finish and deliver the minimum tier (you will get the full mark at this tier). The other tiers are added as a recommendation to improve your skills and knowledge with the topics of the exercise.

## Part 1: Programming Exercise

In the file `src/rasterize.cpp`, you will find the following empty functions:
1. `draw_line`
2. `draw_triangle`

The goal of this exercise is to implement these two functions.

To run your code on the test cases (which you can find in `tests/scenes`), you can:
* Use the `rasterizer` executable which is implemented in `src/main.cpp`. This executable expects two command line arguments: the path to a test case file and the path to which the rasterized image will be saved. If you are using Visual Studio Code, you can run `rasterizer` via `Ctrl-F5` (or `F5` to debug), and you can configure the command line arguments inside `.vscode/settings.json` (For the configuring the debugger, use `.vscode/launch.json` instead).
* Use the `ctest` command, which will run the `tester` executable for each test case and compare the results with the expected results. The `tester` executable is implemented in `src/test.cpp`. To run the `ctest` command, go to the build directory in the terminal (e.g., using `cd build`), then run `ctest`.

**Requirements:**
* **Minimum Tier:** At least one test case passes.
* **Recommended Tier:** All the test cases pass.

## Part 2: Handwritten Exercise

The goal of this exercise is to apply Bresenham's line drawing algorithm and the scanline triangle drawing algorithm by hand. This part should be down by hand and the steps should be shown in the submitted solution.

**Requirements:**
* **Minimum Tier:** Apply the algorithms to `line_test_00.txt` and `tri_test_02.txt`.
* **Recommended Tier:** Also apply the algorithms to `line_test_05.txt` and `tri_test_05.txt`.

# Submission Instructions

**Deadline:** Check the deadline for the exercise on Google Classroom.

**Deliverable:** One PDF File containing the following:
- You name and ID.
- [Part 1] The result of running `ctest` (the output that appears on the console), put it into a text file and submit it. Make sure that what you copy shows that at least one test case has passed.
- [Part 2] A scan of your solution (clearly showing the work you've done by hand to reach the solution).

**Important:** Don't compress your submission (don't submit them in a zip file, rar file, etc), since I plan to grade your work directly on Google Classroom without downloading the files.