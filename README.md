# Dining Philosophers Problem  [![license](https://img.shields.io/github/license/herrera-diego/dining-philosophers)](./LICENSE) [![Makefile CI](https://github.com/herrera-diego/dining-philosophers/actions/workflows/makefile.yml/badge.svg?branch=main)](https://github.com/herrera-diego/dining-philosophers/actions/workflows/makefile.yml)


Implementation on Dining Philosophers problem on C++

![Image](https://upload.wikimedia.org/wikipedia/commons/7/7b/An_illustration_of_the_dining_philosophers_problem.png)

## Problem Statement

A certain number of philosophers spend their lives alternating between thinking and eating. They are seated around a circular table. There is a fork placed between each pair of neighboring philosophers. Each philosopher has access to the forks at her left and right. In order to eat, a philosopher must be in possession of both forks. A philosopher may only pick up one fork at a time. Each philosopher attempts to pick up the left fork first and then the right fork. When done eating, a philosopher puts both forks back down on the table and begins thinking. Since the philosophers are sharing forks, it is not possible for all of them to be eating at the same time.

This was originally formulated in 1965 by Edsger Dijkstra as a student exam exercise.

## Solution

### Waiting State
 - The philosopher enters into a waiting state when neighbors are eating
 - When its neighbors are done, go for the forks
 - Its neighbors can't enter into the waiting state if there is a neighbor already waiting

## Tests

Tests are done using googletests
