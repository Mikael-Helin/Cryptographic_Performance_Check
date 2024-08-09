# Cryptographic Performance Check

Testing Hashing in different programming languages. In this experiment, there is 100MB data in memory that is cryptographically hashed at different lengths.

In the Python directory, a script for generating the data is created.

    cd Python
    Python3 generate_data.py

which will generate a half GB of random strings.

## Python Results

    Sample size: 100 bytes
    Min time: 1.163145 s
    Average time: 1.207036 s
    Max time: 1.460245 s

    Sample size: 1024 bytes
    Min time: 0.404225 s
    Average time: 0.418009 s
    Max time: 0.455754 s

    Sample size: 10240 bytes
    Min time: 0.307495 s
    Average time: 0.327774 s
    Max time: 0.383767 s

    Sample size: 102400 bytes
    Min time: 0.298663 s
    Average time: 0.309943 s
    Max time: 0.335702 s

    Sample size: 1048576 bytes
    Min time: 0.296375 s
    Average time: 0.307202 s
    Max time: 0.336676 s

    Sample size: 10485760 bytes
    Min time: 0.302097 s
    Average time: 0.309063 s
    Max time: 0.347985 s

## C Results

To compile the C program, type

    sudo apt-get install libssl-dev
    gcc -o benchmark benchmark.c -lssl -lcrypto

The results show that there is not much benefit in using C

    Sample size: 100 bytes
    Min time: 0.937474 s
    Average time: 0.942406 s
    Max time: 0.952156 s

    Sample size: 1024 bytes
    Min time: 0.365221 s
    Average time: 0.366876 s
    Max time: 0.372274 s

    Sample size: 10240 bytes
    Min time: 0.303146 s
    Average time: 0.307467 s
    Max time: 0.318857 s

    Sample size: 102400 bytes
    Min time: 0.293339 s
    Average time: 0.294989 s
    Max time: 0.299096 s

    Sample size: 1048576 bytes
    Min time: 0.293975 s
    Average time: 0.295199 s
    Max time: 0.299407 s

    Sample size: 10485760 bytes
    Min time: 0.300684 s
    Average time: 0.306418 s
    Max time: 0.311455 s

## Elixir Results

To run the Elixir script

    elixir benchmark.exs

The results show that Elixir is not bad

    Sample size: 100 bytes
    Min time: 0.685381 s
    Average time: 0.7149591000000001 s
    Max time: 0.87971 s

    Sample size: 1024 bytes
    Min time: 0.337712 s
    Average time: 0.3428278 s
    Max time: 0.348308 s

    Sample size: 10240 bytes
    Min time: 0.293933 s
    Average time: 0.29564060000000003 s
    Max time: 0.298746 s

    Sample size: 102400 bytes
    Min time: 0.297922 s
    Average time: 0.3000482 s
    Max time: 0.309242 s

    Sample size: 1048576 bytes
    Min time: 0.294495 s
    Average time: 0.2957666 s
    Max time: 0.298909 s

    Sample size: 10485760 bytes
    Min time: 0.294072 s
    Average time: 0.2987049 s
    Max time: 0.329492 s
