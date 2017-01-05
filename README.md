# A realization of two famous algorithms in the field of stream processing

This project was finished When I was a 3rd year student at Supélec.

Thank my tutor professor Frédéric PENNERATH who helped me a lot with his intelligence and patience during this project.

The papers of these two algorithms are shown below:

- [A Simple Algorithm for Finding Frequent Elements in Streams and Bags](http://www.cs.umd.edu/~samir/498/karp.pdf)
- [Estimating Entropy and Entropy Norm on Data Streams](http://people.csail.mit.edu/doba/docs/imath-entropy-ds.pdf)

## Installation

### Systems Tested:

- Fedora 20

### Requirements:

- g++

### Start

In this directory, it contains three files, generate_stream.cpp, stream_processing.cpp and makefile.

You can input the command $make to generate the executable files of these two cpp files.

generate_stream is a program to print a pseudo random stream. 

#### Command: 
    $ ./generate_stream <number of lines> <number of symbols> <type of distribution> <times> <seed> (<r>)  
- <number of lines>: the number of lines of the stream.
- <number of symbols>: all the different values in the stream, each value is a random number.
- <type of distribution>: the type of the distribution of the random number. [uni] represents uniform distribution and [geo] is geometric distribution.  
- <times>: the times of the printing of the stream, i.e 1 means to print the stream once, 10 means to print the stream 10 times.(the first(maj) and second(ent) algorithms need 2 passes)
- <seed>: seed for random number generator, i.e 1.  
- <r>: r for the geometric law, needed when you choose geometric distribution.  

#### Example: 
after entering $/generate_stream 10 10 uni 1, you will get a stream with 10 symbols(lines) which generated by the uniform distribution like this:

1
4
2
6
9
5
0
5
0
0
\*

character '*' is the end of the stream.

---------------------------------------------------------------------------------------------------

stream_processing contains the two algorithms I have mentioned above and two naive and brute-force algorithm for comparison.
#### Command: 
    $ ./stream_processing <name of the algorithm\> (<threshold\>).
- <name of the algorithm\>: [maj], [majB], [ent] and [entB] represent the first algorithm(find frequent element), the brute-force algorithm for comparing with the first algorithm, the second algorithm(estimate entropy) and he brute-force algorithm for comparing with the second algorithm.
- <threshold\>: a number between 0 and 1, is the frequency threshold for finding the majority items(only needed when you choose [maj] or [majB]). 

#### Example:
$ stream_processing maj 0.5 will run the first algorithm and find the elements with a frequency more than 0.5.

----------------------------------------------------------------------------------------------------

### Testing procedure:

Here is a testing procedure I used:

The input stream has 10000000 symbols(lines) drew from 10000000 different numbers which is generated by the uniform distribution.

- Execute the first alforithm and find the elements with frequency more than 0.1.
    $ ./generate_stream 10000000 10000000 uni 2 1| ./stream_processing maj 0.1. 

- Execute the brute-force alforithm for finding the elements with frequency more than 0.1.
    $ ./generate_stream 10000000 10000000 uni 1 1| ./stream_processing majB 0.1. 

- Execute the second alforithm and estimate the entropy of the input stream.

    $ ./generate_stream 10000000 10000000 uni 2 1| ./stream_processing ent. 

- Execute tthe brute-force alforithm for estimating the entropy of the input stream.
    $ ./generate_stream 10000000 10000000 uni 1 1| ./stream_processing entB. 

### PS 

You can see the detail of this program by reading Report.pdf


