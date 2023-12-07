# Custom Linux Shell

This is a special Linux/Unix system with a custom shell that provides three specific commands: `word`, `dir`, and `date`.

## Getting Started

### Clone the Repository

```bash
git clone https://github.com/Vikranth3140/Custom-Linux-Shell.git
```

### Navigate to the Project Directory

```bash
cd Custom-Linux-Shell
```

### Compile the Code

```bash
make
```

### Run the Custom Shell

```bash
./source
```

Available Commands
------------------

### 1\. `word`

The `word` command reads the number of words in a text file. It supports the following options:

*   `-n`: Ignores newline characters.
*   `-d`: Compares the word sizes of two text files.

**Syntax:**

```bash
word [-n | -d] [file_name1] [file_name2]
```

### 2\. `dir`

The `dir` command creates a directory and changes the path to that directory. It supports the following options:

*   `-r`: Removes the directory if it already exists and creates a new directory instead of throwing an error.
*   `-v`: Prints a message for each step in the running of this command.

**Syntax:**

```bash
dir [-r | -v] [dir_name]
```

### 3\. `date`

The `date` command returns the last modified date and time of a particular file. It supports the following options:

*   `-d`: Displays time described by STRING.
*   `-R`: Outputs date and time in RFC 5322 format.

**Syntax:**

```bash
date [-d | -R] [file_name]
```

Contributing
------------

Welcome to contribute to the Custom Linux Shell! Feel free to fork the repository, and suggest any improvements. To contribute, follow these steps:

1.  Fork the repository.
2.  Create a new branch for your feature or bug fix.
3.  Make your changes and commit them.
4.  Push the changes to your fork.
5.  Submit a pull request.

Thank you for your contributions!

## Author
[Vikranth Udandarao](https://github.com/Vikranth3140)
\
[Anushka Korlapati](https://github.com/anushka-korlapati)