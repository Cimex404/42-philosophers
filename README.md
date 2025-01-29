#   Philosophers 42

This is a 42 project that teaches about threads and mutexes.


##	Disclaimer

This project may not run very well or give the expected results on slower PCs.
Please keep this in mind.

##  The Philosopher problem

The philosopher problem is a well know programming task for coding students.
These are the rules of the problem:

-   n number of philosophers sit at a round table.
-   In the center of the table is a bowl of spaghetti.
-   To the left and right of each philosopher is a fork.
-   There are equally as many forks as there are philosophers.
-   A philosopher can only eat when they hold two forks.
-   A philosopher will follow this routine:
	Eat -> Sleep -> Think -> Repeat
-   A philosopher must use the forks to their left and right.
-   The philosophers can't communicate or know when someone is about to die.
-	If a philosopher doesn't eat within a certain time, they will die and the simulation will end.

The hard part is to make sure that all philosophers get to eat some of the spaghetti before they starve.
The simulation has two ways of concluding:
-	A philosopher dies.
-	All philosophers have eaten a certain number of meals.
In any other case the program will run forever. (Kill with ^C if necessary)
Though it may seem like the death of a philosopher is not a valid end to the simulation,
for some outputs this is in fact the desired outcome.
That is to say that the philosophers should avoid dying.

##	How to run

Simply type the "make" command into the terminal to compile the program.
An executable called "philo" will be created and it is run as follows:

´´´bash
./philo 5 800 200 200

./philo 5 800 200 200 5

./philo 200 130 60 60 5
´´´

The program takes four arguments and allows for an optional fifth argument.
-	Argument 1:		The number of philosophers and forks		(1 - 200)
-	Argument 2:		The time it takes a philosopher to die		(> 60)
-	Argument 3:		The time it takes a philosopher to eat		(> 60)
-	Argument 4:		The time it tales a philosopher to sleep	(> 60)
-	Argument 5:		The number of meals everyone has to eat 	(> 1)	(optional)