# VikShell 

VikShell is a custom Linux/Unix shell that provides various commands to perform file and directory operations. 

<img width="1232" alt="image" src="https://github.com/Vikranth3140/VikShell/assets/122410275/7609d2c0-7524-46e0-ab89-ad5d6613e620">


## Getting Started  

### Clone the Repository 
```bash 
git clone https://github.com/Vikranth3140/VikShell.git
```

### Navigate to the Project Directory

```bash
cd VikShell
```

### Compile & Run the Code

```bash
make
```

Available Commands
------------------

### 1\. `ls`

The `ls` command lists files and directories. It supports the following options:

*   `-r`: Reverse the order of the sort.
*   `-v`: Display additional information about each file.

**Syntax:**

```bash
ls [-r | -v] [directory]
```

### 2\. `cd`

The `cd` command changes the current directory.

**Syntax:**

```bash
cd [directory]
```

### 3\. `mkdir`

The `mkdir` command creates a new directory.

**Syntax:**


```bash
mkdir [directory]
```

### 4\. `help`

The `help` command displays information about available commands.

**Syntax:**

```bash
help
```

### 5\. `word`

The `word` command reads the number of words in a text file. It supports the following options:

*   `-n`: Ignores newline characters.
*   `-d`: Compares the word sizes of two text files.

**Syntax:**

```bash
word [-n | -d] [file_name1] [file_name2]
```

### 6\. `dir`

The `dir` command creates a directory and changes the path to that directory. It supports the following options:

*   `-r`: Removes the directory if it already exists and creates a new directory instead of throwing an error.
*   `-v`: Prints a message for each step in the running of this command.

**Syntax:**

```bash
dir [-r | -v] [dir_name]
```

### 7\. `date`

The `date` command returns the last modified date and time of a particular file. It supports the following options:

*   `-d`: Displays time described by STRING.
*   `-R`: Outputs date and time in RFC 5322 format.

**Syntax:**

```bash
date [-d | -R] [file_name]
```

### 8\. `exit`

The `exit` command exits VikShell.

**Syntax:**

```bash
exit
```

Contributing
------------

Welcome to contribute to VikShell! Feel free to fork the repository and suggest any improvements. To contribute, follow these steps:

1.  Fork the repository.
2.  Create a new branch for your feature or bug fix.
3.  Make your changes and commit them.
4.  Push the changes to your fork.
5.  Submit a pull request.

Thank you for your contributions!

License
-------

This project is licensed under the [MIT License](LICENSE.md).

Authors
-------

*   [Vikranth Udandarao](https://github.com/Vikranth3140)
*   [Anushka Korlapati](https://github.com/anushka-korlapati)
