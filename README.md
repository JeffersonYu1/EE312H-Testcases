# EE312H-Testcases
Student-contribution test case repository for UT Austin's EE312H Course (Software Design and Implementation). Unofficial, not directly affiliated with UT. Started Spring 2022.

Thanks to everyone who contributed to this project! **If this repository helped you, please consider giving it a star. Thanks!**

**Do not upload program source code to this repo or its forks!!**

* [How to Use a Test Case](https://github.com/JeffersonYu1/EE312H-Testcases#how-to-use-a-test-case)
* [How to Write a Test Case](https://github.com/JeffersonYu1/EE312H-Testcases#how-to-write-a-test-case)
* [How to Submit a Test Case to this Repository](https://github.com/JeffersonYu1/EE312H-Testcases#how-to-submit-a-test-case-to-this-repository)

## How to Use a Test Case
### Project 8
Place the desired **.blip** file(s) (test case) into the smae folder as your **proj8** executable and other files.
* As mentioned in the assignment instructions document, your main should look like the below:

```
int main(void){
 set_input(<DESIRED BLIP FILE PATH>);
 run();
}
```

Change the Blip filepath to be the test case that you want, and then run your code.
* Note: In many **.blip** test files, the expected output is listed as comments.

Don't forget to try your code on the ECE server :)

### Project 7
#### Method 1: Manual Testing
Place the desired **.txt** file(s) (test case) into the same folder as your **proj7** executable (called **a.out** for this project).
* Navigate to **main.cpp** and scroll down to the **main** function. Find the code snippet below and make the changes:
```
...
readInput("test3.txt");
reset();

// ADD THE BELOW TWO LINES FOR EACH NEW TEST CASE
readInput(DESIRED TXT FILE NAME);
reset();
```
* Save **main.cpp**, then recompile and run. Test case results should be displayed in the console.
* **Don't forget** to try your code on the ECE server :)

#### Method 2: Testing Script
Contributed by David Puma. View the instructions for running at [his README](https://github.com/JeffersonYu1/EE312H-Testcases/tree/main/Project7).

#### Files in Project 7 Folder
* **test1.txt, test2.txt, test3.txt** - test cases provided by instructors
* **test_extra1.txt** - tests processPurchase() with more than in inventory; processInventory() with negative qty, 0 qty; processSummarize() at beginning and end
* **test_extra2.txt** -  tests processPurchase() with zero qty or more than in inventory; processInventory() with negative qty, 0 qty; processSummarize() at beginning and end
* **test_extra3.txt** - tests processPurchase() with zero qty or more than in inventory; processInventory() with negative qty, 0 qty
* **text_extra4.txt** - tests processPurchase() with zero qty; processInventory() with negative qty, 0 qty
* **text_extra5.txt** - processPurchase() stress test

Note: As per the Project 7 PDF, "no customers will attempt to buy negative numbers of anything." Therefore, none of the extra test cases test for negative inputs to processPurchase().

### Project 6
The Project 6 Tester includes an autograder. Your score will be shown at the end of the tests.

1. Remove the original **main.cpp** file (and **main.o** if you have compiled preivously) that was provided in the Project 6 ZIP.
2. Download/save my [main2.cpp](https://github.com/JeffersonYu1/EE312H-Testcases/blob/main/Project6/main2.cpp) file, and place it into the folder with your **Project6.cpp** and other files for this lab. ([Raw](https://raw.githubusercontent.com/JeffersonYu1/EE312H-Testcases/main/Project6/main2.cpp) here.) Make sure the file extension when downloaded is **.cpp** and NOT **.txt**!
3. Rename **main2.cpp** as **main.cpp**.
4. Open your IDE and run 'make' in terminal like normal. (There may be some warnings.)
5. If 'make' is successful, run **./proj6**.
6. Keep running / revising your Project 6 until you get the cat (pass all tests) (:

Note: If you don't want full details for each test to be shown, change **showDetails** at the top of the file to **0** instead of **1**. Then, only the details for failed cases will be shown.

#### Files in Project 6 Folder
* **main.cpp** - Original tester given by instructors.
* **main2.cpp** - Tester for all functions in this lab.

### Project 5
Remove (or move outside of the current folder) the original **main.cpp** file that was provided in the Project 5 ZIP.
* Then, download the desired **.cpp** file with custom test cases into the folder with your **Project5.cpp** and other associated files. You can download a file by navigating to it in the GitHub file explorer, then opening the file and clicking on the **Download** button.
* Run 'make' in terminal like normal.
* If 'make' is successful, run **./proj5**.
#### Files
* **main.cpp** - Original tester given by instructors.
* **main-2.cpp** - Tester for union, intersection, subtraction, and isMember with 1000 randomly generated cases.
  *  Note: If you don't want full details for each case to be shown, change **showDeets** at the top of the file to **0** instead of **1**.
* **Project5testcasegen.py** - Python script used to generate random cases for **main-2.cpp**.


### Project 4
Place the desired **.txt** file(s) (test case) into the same folder as your **proj4** executable.
* Navigate to **main.cpp** and scroll down to the **main** function. Find the code snippet below and make the changes:
```
...
readInput("test3.txt");
reset();

// ADD THE BELOW TWO LINES FOR EACH NEW TEST CASE
readInput(DESIRED TXT FILE NAME);
reset();
```
* Save **main.cpp** and recompile by calling **make** in your Project 4 directory.
* Run your **proj4** executable, and the test case results should be displayed in the console.
* **Don't forget** to try your code on the ECE server :)

## How to Write a Test Case
### Project 8
Like Project 4, but with **.blip** file extension instead of **.txt**.

### Project 7
Like Project 4.

### Project 6
Like Project 5.

### Project 5 
Project 5 cases are **.cpp** (program) based.
* Create a new **.cpp** file based on **main.cpp**. Write your test functions in this new **.cpp** file and have **main()** call on those functions.
* Use **assert()** to check if a result is as expected. If a value is not as expected, execution will halt.
* If you have an idea for a test case / edge case but are unsure how to write the tester, [feel free to open an issue here by clicking **new issue**](https://github.com/JeffersonYu1/EE312H-Testcases/issues), describe what your idea is, and I'll try to help out.

### Project 4
Project 4 is **.txt** input based.
* Create a new **.txt** file, then type commands, such as "Inventory", "Purchase", and "Summarize" as specified by the instructions PDF.
* Be sure to end the list of commands with "Quit."
* After the "Quit", type the expected output in block comment form.
* Please add a new line after the end-of-test line.


## How to Submit a Test Case to this Repository
### Step 1: Create a Fork of this Repository
Navigate to https://github.com/JeffersonYu1/EE312H-Testcases and create a fork of this repository. ([What is a fork?](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/working-with-forks/about-forks)) The created fork will be located in your GitHub account.

<img width="947" alt="Create a Fork of this Repository" src="https://user-images.githubusercontent.com/43518772/156106635-71313b9e-f1a1-4e40-bf9f-3e4bd9ede9e5.png">

### Step 1.5: Fetch Upstream
If it's been a while since you last forked the repo (repository), click "Fetch Upstream" to make sure your fork is up to date.

<img width="947" alt="Fetch Upstream" src="https://user-images.githubusercontent.com/43518772/156107880-3636627a-659c-40a9-93f4-2b7bb3e0beff.png">

### Step 2: Navigate to the Corresponding Folder
Navigate to the corresponding folder to the Project you are working on.

<img width="947" alt="Navigate to the Corresponding Folder" src="https://user-images.githubusercontent.com/43518772/156107988-96a43afb-a600-4281-a594-bb32ecd4b827.png">

### Step 3: Upload or Create Your File
Click on "Add file" to upload or create your test case. If uploading, multiple files can be uploaded at one time.

<img width="947" alt="Upload or Create Your File" src="https://user-images.githubusercontent.com/43518772/156119043-45ba2e87-39cd-444a-acde-d82d55a44c9d.png">

### Step 4: Commit your Test Case
After you are done, commit your test case. Select "Commit directly to the main branch" when committing. Feel free to add an optional description.

<img width="947" alt="Commit your Test Case" src="https://user-images.githubusercontent.com/43518772/156108622-65712d2e-f138-4e1b-957f-421c9a0a9998.png">

### Step 5: Open a Pull Request
If you aren't already back to https://github.com/JeffersonYu1/EE312H-Testcases, navigate to the main page of the repo. Then, click "Contribute" and then "Open a Pull Request."

<img width="947" alt="Open a Pull Request" src="https://user-images.githubusercontent.com/43518772/156109032-ded8be2d-b51d-4683-bcdd-a09172e33431.png">

### Step 6: Create the Pull Request
Click "Create Pull Request". Keep "Allow Edits by Maintainers" checked.

<img width="947" alt="Create the Pull Request 1" src="https://user-images.githubusercontent.com/43518772/156109417-358913dc-b805-4304-aa6d-df94e6676fb6.png">
<img width="947" alt="Create the Pull Request 2" src="https://user-images.githubusercontent.com/43518772/156109589-23f7f965-8d17-4c43-bef1-91e45c796e84.png">

### Step 7: Done!
That's it on your end! Once the test case is approved, your branch will be merged with the main of this repo, and the test case will show up in the folder. Thank you for your contribution! 
