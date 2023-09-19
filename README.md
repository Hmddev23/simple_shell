# <span style="color:#e8a87c;">SIMPLE SHELL</span>

**Simple Shell** Custom Shell embodies a straightforward realization of a command-line shell using the C programming language. It establishes a fundamental shell environment where users can input commands that the shell subsequently executes.


## Features

  - Processes user commands and carries out their execution.
  - Facilitates essential command-line operations, encompassing the running of external programs.
  - Oversees the creation and management of processes through the utilization of fork() and exec() functions.
  - Provides basic functionalities for redirecting input and output.


## Getting Started

To start using Simple Shell, follow these steps:

1. Clone the repository: `git clone https://github.com/Hmddev23/simple_shell.git`
2. Navigate to the project directory: `cd simple-shell`
3. Compiles all C files `gcc -c *.c`
4. Link object files into the final executable `gcc *.o -o shell`
5. Run the shell: `./shell`


## Usage

Once the shell is operational, you can provide commands just as you would within any typical shell environment. Here are a few illustrative examples:

- Execute an external program:
  
  ```shell
  shell> ls -l
  shell> gcc -o code code.c

- Change the current directory:
  ```shell
  shell> cd /path/to/directory

- Redirect input/output:
  ```shell
  shell> command < input.txt
  shell> command > output.txt

- Exit the shell:
  ```shell
  shell> exit


## Limitations

- The functionality of Simple Shell is constrained when compared to feature-rich shells such as Bash or Zsh. It does not include advanced capabilities like piping, management of environment variables, retention of command history, and more.
- In this implementation, error handling is rudimentary, and error messages might lack specificity.


## Contributing

- If you wish to contribute to this project, kindly refer to the [contributing guidelines](README.md).


## License

- This project is licensed under the ALX Program License.


## Acknowledgements

- This project draws inspiration from the desire to delve into shell internals and gain insights into process management within Unix-like systems.


## Contact

- For questions or feedback, feel free to reach out to us: [@Hmddev23](https://github.com/Hmddev23) and [@Yamix27](https://github.com/Yamix27)

- Email: hamid.maira709@gmail.com, amyne.boutallaght@gmail.com

- Your contributions and feedback will help shape the future of Advanced Simple Shell!
