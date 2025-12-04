#!/bin/bash

S21_CAT="./s21_cat"
REAL_CAT="cat"

if [[ ! -x "$S21_CAT" ]]; then
    echo "Error: $S21_CAT not found or not executable"
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

    s21_out=$( "$S21_CAT" "${args[@]}" 2>&1 )
    s21_exit=$?

    real_out=$( "$REAL_CAT" "${args[@]}" 2>&1 )
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

# Базовый вывод
run_test "basic concat 1.txt" "1.txt"
run_test "concat multiple files" "1.txt" "2.txt"
run_test "empty file" "3.txt"
run_test "file with tabs and blank lines" "2.txt"

# Флаг -n: нумерация всех строк
run_test "number all lines (-n)" -n "1.txt"
run_test "-n with empty lines" -n "2.txt"
run_test "-n on empty file" -n "3.txt"

# Флаг -b: нумерация только непустых строк
run_test "number non-blank only (-b)" -b "2.txt"
run_test "-b vs -n on file with blanks" -b "4.txt"

# Флаг -s: сжатие пустых строк
run_test "squeeze blank lines (-s)" -s "2.txt"
run_test "-s on file with many blanks" -s "4.txt"
run_test "-s on empty file" -s "3.txt"

# Флаг -e: показывает $ в конце строк (и включает -v, но в GNU cat -e = -vE)
# В нашем случае: просто добавляет '$' в конец каждой строки
run_test "show line ends (-e)" -e "1.txt"
run_test "-e on empty lines" -e "2.txt"

# Флаг -t: показывает табы как ^I (и включает -v)
run_test "show tabs as ^I (-t)" -t "2.txt"
run_test "-t on file with spaces (no tabs)" -t "1.txt"

# Комбинации флагов
run_test "-n and -s together" -n -s "4.txt"
run_test "-b and -s together" -b -s "4.txt"
run_test "-n and -e together" -n -e "1.txt"
run_test "-b and -e together" -b -e "2.txt"
run_test "-n -b -s -e -t together" -n -b -s -e -t "2.txt"

#Тесты длинных (GNU) флагов

# --number ↔ -n
run_test "GNU --number" --number "1.txt"
run_test "--number same as -n" --number "2.txt"

# --number-nonblank ↔ -b
run_test "GNU --number-nonblank" --number-nonblank "4.txt"
run_test "--number-nonblank same as -b" --number-nonblank "2.txt"

# --squeeze-blank ↔ -s
run_test "GNU --squeeze-blank" --squeeze-blank "4.txt"
run_test "--squeeze-blank on multiple blanks" --squeeze-blank "2.txt"

# -E (только $, без -v)
run_test "GNU -E end marker" -E "1.txt"
run_test "-E on file without trailing newline" -E "2.txt"

# -T (только ^I вместо табов, без -v)
run_test "GNU -T show tabs as ^I" -T "2.txt"
run_test "-T vs -t (should be same on printable text)" -t "2.txt"

# Комбинации с длинными флагами
run_test "-E and --number" -E --number "1.txt"
run_test "--number-nonblank and --squeeze-blank" --number-nonblank --squeeze-blank "4.txt"
run_test "-T and -E together" -T -E "2.txt"
run_test "--number --squeeze-blank -T" --number --squeeze-blank -T "2.txt"

#Непечатаемые символы
run_test "-e includes -v + $" -e "nonprintable.txt"
run_test "-t includes -v + ^I" -t "nonprintable.txt"

# Граничные случаи
run_test "non-existent file" "v.txt"
run_test "mix existing and non-existing" "1.txt" "nonexistent.txt" "v.txt"

# === Итог ===
echo
echo "=== Results ==="
echo "Passed: $PASSED"
echo "Failed: $FAILED"

exit $(( FAILED > 0 ? 1 : 0 ))