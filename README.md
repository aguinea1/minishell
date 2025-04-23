<h1 align="center"> 
 	MINISHELL
 </h1>
 
 <p align="center">
 	<img src="https://img.shields.io/badge/Language-C-blue?style=flat-square"/>
 	<img src="https://img.shields.io/badge/Project-Minishell-green?style=flat-square"/>
 	<img src="https://img.shields.io/badge/Unix-Bash%20Clone-yellow?style=flat-square"/>
 </p>
 
 **Minishell** is a project that recreates a simplified version of the Unix shell using **C**. It provides a command-line interface that interprets and executes user commands, handling **builtins**, **pipes**, **redirections**, and **environment variables**. This project helps develop a deep understanding of process control, terminal behavior, parsing, and memory management in Unix systems.
 **Minishell** is a project that recreates a simplified version of Bash using **C**. It provides a command-line interface that interprets and executes user commands, handling **builtins**, **pipes**, **redirections**, and **environment variables**. This project helps develop a deep understanding of process control, terminal behavior, parsing, and memory management in Unix systems.
 
 ---
 
 ## › Features
 - 💬 Executes user-typed **commands** in an interactive shell  
 - 🔁 Supports **pipes** (`|`) and **redirections** (`<`, `>`, `>>`, `<<`)  
 - 🛠 Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`  
 - 🌱 Handles **environment variables**  
 - 🧠 Implements **custom parsing**, **quotes**, and **expansions**  
 - 🧼 Proper **memory management** and **error handling**
 
 ---
 
 ## › Project Overview
 
 </p>
 
 In this project:
 - The shell reads user input, parses it, and executes commands  
 - Commands can be linked via **pipes**, and support **input/output redirection**  
 - Built-in commands are handled internally  
 - External commands are executed using **`execve()`**  
 - Input is managed through **Readline**, with **signal handling** for interactive behavior
 
 ---
 
 ## › Project Requirements
 
 | Feature                | Mandatory            |
 |------------------------|----------------------|
 | Prompt & input parsing | ✅                   |
 | Built-ins              | ✅                   |
 | Redirections           | ✅                   |
 | Pipes                  | ✅                   |
 | Env variables          | ✅                   |
 | Error handling         | ✅                   |
 | Memory leaks           | ✅ (no leaks allowed) |
 
 ## › Technical Concepts
 
 - 🧵 Process creation & management (`fork`, `execve`, `waitpid`)  
 - 📂 File descriptors & redirection (`dup2`, `pipe`)  
 - 🧱 Parsing techniques: lexing & grammar rules  
 - 🔄 Signal handling (`SIGINT`, `SIGQUIT`)  
 - 🧹 Manual memory handling to avoid leaks
 
 ## 📫 Contact
 
 Feel free to reach out or explore more of my work:
 
 [<img src="https://img.shields.io/badge/LinkedIn-0077B5?style=flat-square&logo=linkedin&logoColor=white"/>](https://www.linkedin.com/in/aitor-guinea-961635348/)  
 [<img src="https://img.shields.io/badge/GitHub-aguinea1-black?style=flat-square&logo=github"/>](https://github.com/aguinea1)  
 [<img src="https://img.shields.io/badge/Email-guineaitor36@gmail.com-red?style=flat-square&logo=gmail&logoColor=white"/>](mailto:guineaitor36@gmail.com)
 
 ⭐
