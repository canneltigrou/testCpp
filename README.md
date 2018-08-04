#Wandercraft C++ programming exercice

Welcome to our C++ programmaing test.

##Presentation
You are given an existing codebase, it is already building and working.
It is a simplified robot simulator.
The purpose of the simulator is to call a method to simulate on the robot at each timestep, and to
output the current state of the robot on the standard output.

Look at the Main.cpp, We create an instance of a Class "Robot",
this class represents a simplified robot that has some private attributes to represent its state (Battery Level, position etc).


The ouput of a program is first a list of column headers separated by one tab `\t` character, each value
represents the name of one variable of the program that we want to log.

Then each line is the current value of each variables of the program, always starting by the simulation time.

At first we call `FormatHeader()` which will print the column headers.

then we call in a loop a method `compute(int const timeStep)` that will update the internal state of the robot,
and perform the simulation.
timeStep is the simulation step in milliseconds.

Then we call a method `getCurrentValue(std::vector<int>& values)`.
It returns a vector of each values to be printed.

A class `AbstractLogObject` provides an interface for logging with virtual methods, each class that needs
to ouput data for the simulation should inherit from this class.

Don't focus on the values that are logged, they are random values just to avoid printing only zeros.

## Build and run
A makefile is provided so you should only need to do `make` to build the binary.
Then to run it:
`./simulator`

It should output the tab separated values as expected.

## Your task

You will need to update the code several times.
Don't hesitate to rewrite everything if necessary, don't take the current version for granted.
Your objective is basically to improve the code, make it simpler to write and improve the architecture.

## Constraints
I recommand you to use git for this exercice. You can for example make a branch for each questions,
or make a tag on each commit that is a valid answer.
Else you should provide an archive containing the code for each answers.

The questions are not necessarily following each other, you can skip some and try the others.
It's better to answer smartly to some questions than badly to all questions.
Do your best, comment your code to explain what you are trying to do.
For each answer you should provide a code that compiles and outputs the correct data.

Help: At the top level there will always be only one instance of Robot.

So the data hierarchy is a tree:
Robot -> LeftLeg -> Foot
Robot -> LeftLeg -> Knee
Robot -> RightLeg -> Knee
... etc.


# Question 1 : Nested headers.

Currently for each class the column header is only "Name.field" Where name is the name of the object
and "field" is the name of the data that is logged.
We would like to have a more complete information of the hierarchy of data in the header of the columns.
For example instead of "Foot.Position" we would like to have "JohnnyFive.LeftLeg.Foot.Position".


# Question 2: Generic api.

For now if we add a new private member to some class, for example if we added a third leg to `Robot`, we would
need to change the `formatHeader` and `getCurrentValue` of the Robot class.
This is not very generic and error prone (what if we mix the order in wich we call formatHeader and getCurrentValue?).

Change the code so that it is simpler to add a new attribute which is already derived from `AbstractLogObject`.
Ideally we would like to handle most of the task in the Abstract class and avoid having to redefine
the virtual methods.
You can apply the same pattern for formatHeader, getCurrentValue and compute.
hint: Think how to handle the parenting relationship between objects. You could add a method "addChild()" somewhere.
Think polymorphism.


# Question 3: Other types of data to log.

For now the program is only able to log int variables.
But in a real situation we would like to log variables with other types.
How would you do it for standard types : float, bool, unsigned int etc ?

Update the code with your new system.
Add some fields with theses types in some classes to show it works.
For example you can change "Position" from int to Float, add a boolean flag "IsEnabled" in the motors etc.


# Question 4: Optional values.

Ok now that we have a good generic system, we want to add a feature to make some values optional.
In a real scenario, we can have a lot of values to log, and we don't always need to log everything.
Basically the sensor values are important to keep, but the result of algorithms that are based on
these sensor values can be reconstructed afterwards.
Change the AbstractClass to add a flag for each value saying if it's optional or not.
Add a way to tell the programm to enable or disable the optional values.

It should be set before the simulation starts, because once the headers are generated we won't be able to
remove them or the data won't make sense. So it is set once and never changed after.


# Question 4 (BONUS): Replay

What is interesting with a simulation is that we can replay several times the scenario.
Change the program so that we can store its output to a file.
Then add a way to load the values from an existing file and replay the program,
it should output a new log file.

The idea behind this is that we can load values from sensors and then check that internal algorithms
behave as expected given these sensor values.

