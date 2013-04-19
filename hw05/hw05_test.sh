#
#	hw05_test.sh
#
#
#	test the NFA grammar
#
make clean
cp gramNFA.y gram.y
make
mv y.output yNFA.output
./hw05test +yydebug test1.c
./hw05test test2.c
./hw05test test3.c
#
#	test the DFA grammar
#
make clean
cp gramDFA.y gram.y
make
mv y.output yDFA.output
./hw05test +yydebug test1.c
./hw05test test2.c
./hw05test test3.c
