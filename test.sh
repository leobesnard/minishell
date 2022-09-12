while IFS= read -r line
do
	echo "--------------"
	echo "Doing test: '$line'"
	echo -n $line | ./minishell
	echo "bash result:"
	bash -c "$line"
	echo "-------------\n"
done <  test.txt
