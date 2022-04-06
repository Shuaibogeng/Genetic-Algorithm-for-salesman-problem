# Genetic-Algorithm-for-salesman-problem
C++ code. Solving salesman problem through genetic algorithm. 

# The general logic

## 1.Initialization
	Set the positions of the salesmen.
	Set the group size.
	Set the iteration up limit or other standard to stop the iteration.

## 2.Generate the distance matrix between every 2 points.

## 3.Create 128(groupsize) random member paths as a group.

## 4.Selection:
	The fitness function is 1/pathlength.
	Select the top(shortest) 64(half-groupsize) paths through the fitness function as the parents.

## 5.Crossover:
	Do crossover in the selected parents group with half-groupsize.
	Every pair of parents would have 2 offsprings.
	The crossover method follows the partially mapped crossover (PMX) method.
	1) generate a random cut point.
	2) the first offspring(o01) will keep the first parent's path string(p01) after the cut point, and take the second parent's path string(p02) before the cut point.
	3) now the offspring may have some repeating numbers and miss some numbers. Find the repeating point index and the missing numbers in one offspring
	4) put the missing numbers at repeating points in the original order.
	5) do the same progress for the second offspring but change the first and the second parent.

	For example:
	p01 = 36124857;
	p02 = 72835146;
	1) The random cut point is 3
	2) o01=72834857;
	3) repeating point index:5, 7; the missing numbers:6,1; o01=72834X5X;
	4) o01=72834651;
	5) o02=36125748;

## 6.Mutation:
	For every offspring, it has a probablity to mutate.

## 7.Check the best(shortest) path.

## 8.Repeat 4. 5. 6. 7., until a stop condition is encountered.


# Modifications
Modifications in salesman_code_v2.cpp:
Replaced findMissing1D() with findMissingFrom1D().
findMissingFrom1D() function gives the missing number in which they appear in the parent path. 
