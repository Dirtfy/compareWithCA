# Introduce

Finding a counterexample is sometimes quite annoying and difficult when studying Problem Solving. In that case, this will be helpful.

# Requirements

1. input generator  
2. correct answer
3. wrong answer  

The three components listed above must be prepared as executable files (for example, if you are using a Windows system, you will need an .exe file).  
Additionally, they should use standard I/O to guarantee proper behavior.

# Use

```sh
./CompareWithCA (input generator path) (correct solver path) (wrong solver path)
```
For example:
```sh
./CompareWithCA ./input ./CA ./WA
```
Alternatively, you can use it without arguments, and the default arguments will be as shown in the example above.

# Behavior

This program keeps running until it finds a counterexample.   
If it finds a counterexample, it stops and prints the number of the first differing line.   
You can find your program's outputs in .txt files named 'input.txt', 'CA.txt', and 'WA.txt'.
