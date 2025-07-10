# 🐚 Minishell

## ℹ️ About
A simple shell written in C for the 42 school project.
Supports built-in commands, pipes, redirections, and more.

## ⚙️ 🛠️ Features
- Command execution with PATH resolution
- Built-in commands: \`echo\`, \`cd\`, \`pwd\`, \`export\`, \`unset\`, \`env\`, \`exit\`
- Pipes `|`
- Redirections `>, <, >>, <<`
- Proper signal handling (Ctrl+C, Ctrl+\, Ctrl+D)
- Environment variable expansion `$`
- Last exit status `$?`
- Quote parsing ("..." and '...')

## 📂 Project Structure
- \`src/\`: Source files
- \`include/\`: Header files
- \`libft/\`: Custom library functions
- \`Makefile\`: Build instructions

## 🗂️ How It Works
This project implements a simple shell in C that mimics basic shell behavior.
The core stages are:

1. **Lexical Analysis (Lexer / Tokenization)**
   The input line is split into **tokens** like words, pipes, and redirections.

   **Example:**
   ```bash
   cat < input.txt | grep "hello" | sort -r > output.txt

[TOKEN_WORD: "cat"] 
[TOKEN_REDIRECT_IN: "<"]
[TOKEN_WORD: "input.txt"]
[TOKEN_PIPE: "|"]
[TOKEN_WORD: "grep"]
[TOKEN_DOUBLE_QUOTES: "hello"]
[TOKEN_PIPE: "|"]
[TOKEN_WORD: "sort"]
[TOKEN_WORD: "-r"]
[TOKEN_REDIRECT_OUT: ">"]
[TOKEN_WORD: "output.txt"]

2. **Syntax Validation**
After tokenization, the tokens are validated to ensure they form a correct command.

✅ Valid:
\`\`\`bash
cat < input.txt | grep "hello"
\`\`\`

❌ Invalid examples:
\`\`\`bash
\> 
minishell: syntax error near unexpected token '>'
cat <
minishell: syntax error near unexpected token '>'
| cat  
minishell: syntax error near unexpected token '|'
cat | |  
minishell: syntax error near unexpected token '|'
echo "blablabla  
minishell: syntax error: unclosed quotes
\`\`\`

3. **AST Construction (Abstract Syntax Tree)**
Valid tokens are converted into an AST (tree structure) that represents the execution pipeline.

Example AST for:
\`\`\`bash
cat < input.txt | grep hello | sort -r > output.txt
\`\`\`

parse_pipeline("cat < input.txt | grep hello | sort -r > output.txt")
    ├── parse_command("cat < input.txt")  -> AST_CMD(cat)
    │   ├── Redirection: < input.txt
    ├── parse_pipeline("grep hello | sort -r > output.txt")
        ├── parse_command("grep hello")  -> AST_CMD(grep hello)
        ├── parse_pipeline("sort -r > output.txt")
            ├── parse_command("sort -r")  -> AST_CMD(sort -r)
            ├── Redirection: > output.txt

Final AST:
Node Type: AST_PIPE (|)
  ├── Node Type: AST_PIPE (|)
  │     ├── Node Type: AST_CMD
  │     │     ├── Arg: cat
  │     │     ├── Redirection: < input.txt
  │     ├── Node Type: AST_CMD
  │           ├── Arg: grep
  │           ├── Arg: hello
  ├── Node Type: AST_CMD
        ├── Arg: sort
        ├── Arg: -r
        ├── Redirection: > output.txt

## ✅ How to Run
\`\`\`bash
make
./minishell
\`\`\`

## 👩🏻‍💻👩🏻‍💻 Authors
- Tanya Kremnova ([@TanyaKremnova](https://github.com/TanyaKremnova))
- Lidiia Perekhrest