# Automatic batch testing

* Unzip `Project8_ExtraTestCases.zip` into the testcase directory of your project.
* Move `testAll.sh` to the lab8 root directory (the same directory as your makefile)
	* run `chmod +x` on `testAll.sh`
* In the main function of your interpreter modify set_input to take in element 1 from the array of passed in arguments
	* Note add `int argc, char* argv[]` as input parameters to your main functions and optionally add an if else block to check that `argc > 1` where the base case causes `run()` to be invoked as outlined in the lab doc, and the branch causes `argv[1]` to be passed to `set_input()`.
	* The modified main function should look similar to the following:
	```c
	int main(int argc, char* argv[]) {
		if (argc > 1) {
			// First argument must be path
			int vIn = set_input(argv[1]);
			if (vIn)
				run();
		} else {
			// All non-cleanup code which was in your main 
			// function previously
		}

		// *Your cleanup code goes here*
		return 1;
	}
	```
	* ## *Make sure to revert your main function as described in the lab document before submitting!*
* Now simply run `./testAll.sh` and follow the on screen indicators to step through each test case.
	* run `./testAll.sh -v` to run with valgrind.
* Congratulations on finishing the final lab and good luck on the midterm!! -David
