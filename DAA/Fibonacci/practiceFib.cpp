#include <iostream>
using namespace std;

class Fibonacci
{
private:
    int fibSolve(int n)
    {
        if (n < 2)
            return n;

        return fibSolve(n - 1) + fibSolve(n - 2);
    }

public:
    void fibonacciRecursive(int n)
    {
        cout << "\n\nThe Fibonacci Series by Recursive Algorithm is......" << endl;

        for (int i = 0; i < n; i++)
        {
            cout << fibSolve(i) << endl;
        }

        cout << endl;
    }

    void fibonacciIterative(int n)
    {
        cout << "\n\nThe Fibonacci Series by Iterative Algorithm is......" << endl;

        int f1 = 0, f2 = 1;
        cout << f1 << " " << f2 << " ";

        for (int i = 0; i < n - 2; i++)
        {
            int f3 = f1 + f2;
            cout << f3 << " ";
            f1 = f2;
            f2 = f3;
        }

        cout << endl;
    }
};

int main()
{
    Fibonacci fib;

    int no = 0;
    cout << "\nEnter the Number: " << endl;
    cin >> no;

    fib.fibonacciRecursive(no);
    fib.fibonacciIterative(no);

    return 0;
}