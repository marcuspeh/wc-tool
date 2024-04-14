# wc-tool
This project is based on [challenge #1](https://codingchallenges.fyi/challenges/challenge-wc/) from [codingchallenges.fyi](https://codingchallenges.fyi/)

# Running the project
1) Compile the codes
```
cmake CMakeLists.txt && make
```
2) Running the compiled codes
```
// With file input
./ccwc sampleText/test.txt

// With stdin
cat sampleText/test.txt | ./ccwc
```

# Task
Create my own version of the Unix command line tool wc.

# Technical requirements and examples of usage
This wc tool should count the following:
1) Number of bytes in the file
```
>ccwc -c test.txt
  342190 test.txt
```
2) Number of lines in the file
```
>ccwc -l test.txt
    7145 test.txt
```
3) Number of words in the file
```
>ccwc -w test.txt
   58164 test.txt
```
4) Number of characters in the file
Note that if the current locale does not support multibyte characters, this will match the -c option
```
>ccwc -m test.txt
  339292 test.txt
```

If none of the options are given, the output should be -c -l -w.
```
>ccwc test.txt
  7145   58164  342190 test.txt
```

If no file name is given, the program should read from standard input
```
>cat test.txt | ccwc -l
  7145
```

If multiple of the same option is given, the program should only return the value once
```
>ccwc -m -m test.txt
  339292 test.txt
```

Lastly, the program should support multiple options and order will be based on the above order (ie, -c, -l, -w, -m)
```
>ccwc -c -l -w -m test.txt
  342190  7145  58164  339292 test.txt
```

# Testing
This program will use `doctest` for testing. Refer to [this](https://blog.jetbrains.com/rscpp/2019/07/10/better-ways-testing-with-doctest/) for a quick guide on doctest.

I have placed the tests in a separate directory to make things clearer.

Instructions to run:
```
cd test
g++ -o test main.cpp
./test
```