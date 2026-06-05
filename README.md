# 2D Graphics Editor in C

## Project Description

This project implements a simple 2D Graphics Editor using the C programming language. The editor uses a 2D character array to represent a drawing canvas. Shapes are drawn using the `*` character, while empty spaces are represented using the `_` character.

The program provides functions to create, modify, and remove graphical objects from the canvas and display the resulting picture on the screen.

---

## Features

* Draw a Line
* Draw a Rectangle
* Draw a Circle
* Draw a Triangle
* Add objects to the picture
* Delete objects from the picture
* Modify existing objects
* Display the picture on the console
* Menu-driven interface for user interaction

---

## Technologies Used

* C Programming Language
* Standard C Libraries
* Optional: ncurses library for enhanced menu and display support

---

## Data Structure Used

The picture is stored using a two-dimensional character array.

```c
char picture[HEIGHT][WIDTH];
```

* `*` represents a drawn pixel.
* `_` represents an empty pixel.

---

## Functions Implemented

### clearPicture()

Initializes the canvas by filling it with `_`.

### displayPicture()

Displays the current picture on the screen.

### setPixel(int x, int y)

Plots a single pixel at the specified coordinates.

### drawLine(int x1, int y1, int x2, int y2)

Draws a line between two points.

### drawRectangle(int x1, int y1, int x2, int y2)

Draws a rectangle using four lines.

### drawCircle(int cx, int cy, int radius)

Draws a circle with the specified center and radius.

### drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3)

Draws a triangle by connecting three points.

### deleteObject()

Removes a selected object from the canvas.

### modifyObject()

Allows editing of an existing object.

---

## Algorithm

1. Create a blank canvas using a 2D character array.
2. Display a menu to the user.
3. Accept user input for the desired shape and coordinates.
4. Draw the selected shape on the canvas.
5. Allow the user to add, delete, or modify objects.
6. Display the updated picture.
7. Repeat until the user chooses to exit.

---

## Sample Output

```text
________________________________________
____*****_______________________________
____*___*_______________________________
____*****_______________________________
________________________________________
```

---

## Compilation

Using GCC:

```bash
gcc graphics_editor.c -o graphics_editor -lm
```

If ncurses is used:

```bash
gcc graphics_editor.c -o graphics_editor -lncurses -lm
```

---

## How to Run

```bash
./graphics_editor
```

Follow the on-screen menu to draw and edit shapes.

---

## Learning Outcomes

* Understanding of 2D arrays
* Graphics representation using characters
* Modular programming using functions
* Shape drawing algorithms
* User interaction through menu-driven programs

---

## Author

Vinayak

B.E. Engineering Student

