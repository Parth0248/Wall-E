# Wall-E 
Wall-E is the clone of the Bash shell. It is written in C, and supports various features of a traditional Bash shell. <br>

## To execute
* Run the makefile then: <br>
```
./a.out
```

## Features

#### Command Prompt

Wall-E has a command prompt that is similar to the one in a Bash shell. The prompt is displayed in the form of `<username@system_name:curr_dir>`.
The root directory is the one from which the shell is started.
It is implemented in CWD.c

### Built-In Commands

#### 1. cd
Changes the current directory to another directory specified and displays an error if the specified directory does not exist just like traditional Bash Shell.
`.`, `..`, `~`, and `-` are all valid directory names.

```bash
cd <path_to_destination_directory>
```

#### 2.  pwd

Outputs the path of the current working directory

```bash
pwd
```

#### 3.  echo

Prints the specified message on the terminal and accounts for tabs and spaces

``` bash
echo <message>
```


#### 4.  ls

Lists all the files and directories in the given directory. It handles multiple flags and directories as arguments.

```bash
ls <path_to_directory> 
```

**Flags supported:**  
- `-a`: Lists all the files and directories in the given directory, along with symbolic links and hidden files and folders.

```bash 
ls -a <path_to_directory> 
```

- `-l`: Lists all the files and directories in the given directory with detailed information.
```bash
ls -l <path_to_directory> 
```

These flags can be used together in different orders, while giving the output intended.
<br>


### System Commands

Commands other than the built-in commands are system commands. For example, `vim`, `sleep`, `gedit` etc.

#### 1. Foreground Processes
To run processes in the foreground, just enter the command and the process will start up.
Wall-E will wait for this process to complete and regain control when this process exits.
It handles all errors 

```bash
<command>
```


#### 2. Background Processes
To run processes in the background, enter an `&` after the command and the process will start up.
Wall-E will create the process and doesn't wait for it to exit. It will keep taking other user commands.
After the background process terminates, the shell displays the exit status details on the terminal.

```bash
<command> &
```
or 
```bash
<command>&
```

### Additional Commands

#### 1. pinfo
Displays information about the process, including its PID, status, memory, and executable path.
```
pinfo <PID>
```
Running just `pinfo` without any arguments will display information about the shell program.

#### 2. Repeat

Executes the given instruction multiple times. The first argument to the command repeat gives the number of times the following command has to be repeated.

```
repeat <no_of_times> <command>
```