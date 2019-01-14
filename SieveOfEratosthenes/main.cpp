/** 
https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
In mathematics, the sieve of Eratosthenes is a simple, ancient algorithm for finding all prime numbers up to any given limit.

It does so by iteratively marking as composite (i.e., not prime) the multiples of each prime, starting with the first prime number, 2. 
The multiples of a given prime are generated as a sequence of numbers starting from that prime, with constant difference between them 
that is equal to that prime. This is the sieve's key distinction from using trial division to sequentially test each candidate number 
for divisibility by each prime.

The earliest known reference to the sieve is in Nicomachus of Gerasa's Introduction to Arithmetic, which describes it and attributes 
it to Eratosthenes of Cyrene, a Greek mathematician.

One of a number of prime number sieves, it is one of the most efficient ways to find all of the smaller primes. 
It may be used to find primes in arithmetic progressions. */

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void SieveOfEratosthenes(const int n)
{
    // Create a boolean array "prime[0..n]" and initialize all entries it as true. 
	// A value in prime[i] will finally be false if i is Not a prime, else true.
    bool prime[n + 1];
    memset(prime, true, sizeof(prime));

    for (int p = 2; p * p <= n; ++p)
    {
        // If prime[p] is not changed, then it is a prime
        if (prime[p] == true)
        {
            // Update all multiples of p
            for (int i = p * 2; i <= n; i += p)
                prime[i] = false;
        }
    }

    // Print all prime numbers
    for (int p = 2; p <= n; ++p)
        if (prime[p])
            cout << p << " ";
}

// simplest way version
void SieveOfEratosthenesV2(const int n)
{
    for(int number = 2; number <= n; ++number)
    {
        bool isPrime = true;
        for(int i = 2; i < number; ++i)
        {
            if((number % i) == 0)
                isPrime = false;
        }

        if(isPrime)
            cout << number << " ";
    }
}

// Driver Program to test above function
int main()
{
    const int n = 100;
    cout << "Following are the prime numbers smaller or equal to " << n << endl;
    SieveOfEratosthenes(n);	

    cout << endl;

	// simplest way
    SieveOfEratosthenesV2(n);

    return 0;
}
