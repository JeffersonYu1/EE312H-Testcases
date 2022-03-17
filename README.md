# EE312H-Testcases
Unofficial, student-contribution test case repository for UT Austin's EE312H Course (Software Design and Implementation). Started Spring 2022.

Thanks to everyone who contributed to this project! **Do not upload program source code to this repo or its forks!!**

* [How to Write a Test Case](https://github.com/JeffersonYu1/EE312H-Testcases#how-to-write-a-test-case)
* [How to Use a Test Case](https://github.com/JeffersonYu1/EE312H-Testcases#how-to-use-a-test-case)
* [How to Submit a Test Case to this Repository](https://github.com/JeffersonYu1/EE312H-Testcases#how-to-submit-a-test-case-to-this-repository)

## How to Write a Test Case
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


## How to Use a Test Case
### Project 5
Remove (or move outside of the current folder) the original **main.cpp** file that was provided in the Project 5 ZIP.
* Then, place the desired **.cpp** file with custom test cases into the folder with your **Project5.cpp** and other associated files.
* Run 'make' in terminal like normal.
* If 'make' is successful, run **./proj5**.
* Note: For the **main-2.cpp** test cases, if you don't want full details for each case to be shown, change **showDeets** at the top of the file to **0** instead of **1**.


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
