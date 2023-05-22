#!/bin/bash

cmds=(
    "ls -l"
    "pwd"
    "echo hello"
    "cat test_minishell.sh"
)

for cmd in "${cmds[@]}"; do
    echo "Testing command: $cmd"

    # Run the command in bash and capture output and exit code
    bash_output=$(bash -c "$cmd" 2>&1)
    bash_exit_code=$?

    # Run the command in minishell and capture output and exit code
    minishell_output=$(timeout 5s ./minishell -n "$cmd" 2>&1)
    minishell_exit_code=$?

    if [[ $minishell_exit_code -eq 124 ]]; then
        echo "Minishell timed out when running '$cmd'"
        continue
    fi

    # Compare outputs
    if [ "$bash_output" != "$minishell_output" ]; then
        echo "FAIL: Output of '$cmd' in bash and minishell do not match"
        echo "bash output: $bash_output"
        echo "minishell output: $minishell_output"
    else
        echo "PASS: Output of '$cmd' in bash and minishell match"
    fi

    # Compare exit codes
    if [ "$bash_exit_code" != "$minishell_exit_code" ]; then
        echo "FAIL: Exit code of '$cmd' in bash ($bash_exit_code) and minishell ($minishell_exit_code) do not match"
    fi
done
