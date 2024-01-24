# MAP55672-Assignment 1
MAP55672-Case-Studies-Assignment-1

## Question
In this assignment, you are being asked to build a simple communication-avoiding TSQR-factorization of a tall, narrow matrix.
1. Familiarize yourself with the QR factorization routines contained in LAPACK. You will
use a Householder-based QR routine to perform local, on-processor QR factorizations.

2. Implement a method called TSQR() which executes just the communication-avoiding
QR-factorization of a tall-narrow matrix using the technique described in the lecture
video/included technical report. It should use LAPACK’s QR factorization routine for
local QR. Set your code up so that you can choose on how many nodes the matrix will
be distributed. Set up a (relatively) small test problem to demonstrate that your code
works.

3. Included with this assignment is a test matrix: $$A_2 \in R^{10^5×10^3}$$ and right-hand side: $$b_2 ∈ R^{10^5}$$
You can download them from a folder on Microsoft OneDrive. 
Let the Matlab notation 
$$Ai(:, 1 : k)$$ 
denote the 
$N × k$ matrix $(N = 10^5)$ 
with the k columns of Ai. 
Use your CAQR code to factor and solve $$Ai(:, 1 : k)x_k ≈ b_i$$
for 
$$k = 200, 400, . . . , 10^3$$
Similarly, use CAQR to factor and solve $$Ai(1 : j, :)x(j) ≈ bi(1 : j)$$ 
for $$j = 2 ×\frac{N}{10}, 4 × \frac{N}{10} , . . . , N$$

Does your code fail at some point? Report if your code can solve the full problem or
if breaks after a certain size. Please report all your timing results with both tables and
plots, and provide interpretations of them.