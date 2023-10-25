# AVL Tree Implementation of a Set
This project is a C++ implementation of a set using an AVL (Adelson-Velsky and Landis) tree. AVL trees are self-balancing binary search trees, where the difference in heights between the left and right subtrees of any node (balance factor) is no more than one, ensuring that the tree remains approximately balanced and operations such as insertion, deletion, and lookup can be performed in logarithmic time.

> The main goal of this project was to get familiar with working with AVL trees and to implement some operations with sets on the tree itself. During the project, I got acquainted with the implementation of the operations of inserting elements into the tree itself, rotating and balancing the tree.
> 
> This project was developed as the [first university assignment](instructions.pdf) for "Algorithms and Data Structures 2", University of Belgrade School of Electrical Engineering majoring Software Engineering. Please refer to the file for detailed assignment instructions.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Compilation and Execution](#compilation-and-execution)
  - [Usage](#usage)
- [Note](#note)

## Features

- **Create an Empty Set**: Initializes an empty AVL tree.
- **Insert Elements into Set**: Allows for the addition of unique elements into the AVL tree, maintaining the tree's balanced nature.
- **Element Belongs to a Set?**: Checks for the existence of a specific element within the AVL tree.
- **Symmetric Difference of Two Sets**: Calculates and displays the symmetric difference between two AVL trees.
- **Print the Tree**: Visually displays the structure of the AVL tree and performs an inorder traversal, printing the elements.
- **Delete the Set**: Removes all elements from the AVL tree, freeing up the allocated memory.

## Getting Started

### Prerequisites

To compile and run the Lozanic Triangle simulation, you need a C++ compiler (e.g. GCC) installed on your system.

 ### Compilation and Execution

1. Ensure you have a C++ compiler installed.
2. Clone this repository.
3. Navigate to the directory containing the source code.
4. Compile the code using a command such as `g++ -o avl_tree main.cpp`.
5. Run the compiled program using `./avl_tree`.

 ### Usage

Upon execution, the program presents a menu with various options, as explained in [Features](#features) section, to interact with the user. Follow the on-screen prompts to perform operations.

## Note
Ensure that your terminal supports ASCII escape codes to view the colorized and formatted output correctly.
