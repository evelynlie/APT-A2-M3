Information for compiling and running the program.

To compile the program, you need to run the following command:
```make```
or
```g++ -Wall -Werror -std=c++14 -O -o ftt Coin.cpp Command.cpp DoublyLinkedList.cpp ftt.cpp Helper.cpp LinkedList.cpp Node.cpp```

To run the program, you need to first read the data from the files foods.dat and coins.dat by running the following command:
```./ftt foods.dat coins.dat```

To run the program with the test files, you need to run the following command:
```
./ftt foods.dat coins.dat < <testname>.input > <testname>.actual_output
diff -w <testname>.expected_output <testname>.actual_output
diff -w -y <testname>.expected_coins <actual_saved_coins>
```

For test *req-5-purchase-meal-cannot-refund*, which tests when the system cannot refund the user purchasing a meal, the data file for the coins should be **nocoins.dat**, which will load no coins into the system.
```
./ftt foods.dat nocoins.dat < req-5-purchase-meal-cannot-refund.input > req-5-purchase-meal-cannot-refund.actual_output
```