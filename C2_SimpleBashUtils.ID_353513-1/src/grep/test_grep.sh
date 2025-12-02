#!/bin/bash

S21_GREP="./s21_grep"
REAL_GREP="grep"

if [[ ! -x "$S21_GREP" ]]; then
    echo "Error: $S21_GREP not found or not executable"
    exit 1
fi

PASSED=0
FAILED=0

run_test() {
    local desc="$1"
    shift
    echo -n "Test: $desc ... "

    local args=("$@")

    local s21_out real_out s21_exit real_exit

    s21_out=$( "$S21_GREP" "${args[@]}" 2>&1 )
    s21_exit=$?

    real_out=$( "$REAL_GREP" "${args[@]}" 2>&1 )
    real_exit=$?

    if [[ $s21_exit -eq $real_exit ]] && [[ "$s21_out" == "$real_out" ]]; then
        echo "PASSED"
        ((PASSED++))
    else
        echo "FAILED"
        echo "  Args: ${args[*]}"
        echo "  Your exit: $s21_exit, real: $real_exit"
        echo "  Diff:"

        diff -u <(echo "$real_out") <(echo "$s21_out")
        ((FAILED++))
    fi
}

#Тесты

# Базовые
run_test "basic match in 1.txt" "hello" "1.txt"
run_test "case insensitive in 1.txt" -i "HELLO" "1.txt"
run_test "match 'hello' in 5.txt" "hello" "5.txt"

# Инверсия
run_test "invert match in 1.txt" -v "hello" "1.txt"
run_test "invert + ignore case" -v -i "hello" "1.txt"

# Подсчёт
run_test "count matches in 1.txt" -c "hello" "1.txt"
run_test "count case-insensitive" -c -i "HELLO" "1.txt"
run_test "count in empty file 3.txt" -c "x" "3.txt"

# Только имена файлов
run_test "list matching files" -l "hello" "1.txt" "5.txt"
run_test "-l with no match" -l "xyz" "1.txt" "2.txt"

# Номера строк
run_test "line numbers in 1.txt" -n "hello" "1.txt"
run_test "-n in 5.txt" -n "привет" "5.txt"

# Несколько файлов
run_test "search in 1.txt and 5.txt" "hello" "1.txt" "5.txt"
run_test "search in all files" "hello" "1.txt" "2.txt" "3.txt" "4.txt" "5.txt"

# Комбинации
run_test "-n and -i together" -n -i "hello" "1.txt"
run_test "-c -v: non-matching lines count" -c -v "hello" "1.txt"

# Регулярные выражения через -e
run_test "explicit pattern with -e" -e "hello" "1.txt"
run_test "multiple -e patterns" -e "hello" -e "ssh" "1.txt" "2.txt"

# Специальные символы
run_test "кириллица" "привет" "5.txt"
run_test "греческие символы" "γειά" "5.txt"

# Пустой шаблон
run_test "empty pattern" "" "1.txt"
run_test "empty pattern in empty file" "" "3.txt"

#Итог
echo
echo "=== Results ==="
echo "Passed: $PASSED"
echo "Failed: $FAILED"

exit $(( FAILED > 0 ? 1 : 0 ))