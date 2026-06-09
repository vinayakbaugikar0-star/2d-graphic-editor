#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 80
#define HEIGHT 24
#define EMPTY '_'
#define PIXEL '*'
#define MAX_OBJECTS 100

char picture[HEIGHT][WIDTH];

// Object types
#define SHAPE_LINE      1
#define SHAPE_RECT      2
#define SHAPE_CIRCLE    3
#define SHAPE_TRIANGLE  4

typedef struct {
    int type;
    int params[6]; // x1,y1,x2,y2 or cx,cy,r or x1,y1,x2,y2,x3,y3
} Shape;

Shape objects[MAX_OBJECTS];
int objectCount = 0;

// ---- Drawing primitives ----

void clearPicture() {
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            picture[y][x] = EMPTY;
}

void setPixel(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        picture[y][x] = PIXEL;
}

void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2-x1), dy = abs(y2-y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    while (1) {
        setPixel(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 <  dx) { err += dx; y1 += sy; }
    }
}

void drawRectangle(int x1, int y1, int x2, int y2) {
    drawLine(x1, y1, x2, y1);
    drawLine(x2, y1, x2, y2);
    drawLine(x2, y2, x1, y2);
    drawLine(x1, y2, x1, y1);
}

void drawCircle(int cx, int cy, int radius) {
    int x = 0, y = radius, d = 1 - radius;
    #define PLOT8(px, py) \
        setPixel(cx+(px),cy+(py)); setPixel(cx-(px),cy+(py)); \
        setPixel(cx+(px),cy-(py)); setPixel(cx-(px),cy-(py)); \
        setPixel(cx+(py),cy+(px)); setPixel(cx-(py),cy+(px)); \
        setPixel(cx+(py),cy-(px)); setPixel(cx-(py),cy-(px));
    while (x <= y) {
        PLOT8(x, y);
        if (d < 0) d += 2*x+3;
        else { d += 2*(x-y)+5; y--; }
        x++;
    }
    #undef PLOT8
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

// ---- Render all objects onto canvas ----

void renderAll() {
    clearPicture();
    for (int i = 0; i < objectCount; i++) {
        int *p = objects[i].params;
        switch (objects[i].type) {
            case SHAPE_LINE:     drawLine(p[0],p[1],p[2],p[3]); break;
            case SHAPE_RECT:     drawRectangle(p[0],p[1],p[2],p[3]); break;
            case SHAPE_CIRCLE:   drawCircle(p[0],p[1],p[2]); break;
            case SHAPE_TRIANGLE: drawTriangle(p[0],p[1],p[2],p[3],p[4],p[5]); break;
        }
    }
}

void displayPicture() {
    renderAll();
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++)
            printf("%c", picture[y][x]);
        printf("\n");
    }
}

// ---- Menu helpers ----

void printMainMenu() {
    printf("2D Graphics Editor\n");
    printf("Canvas size: %d x %d\n", WIDTH, HEIGHT);
    printf("1. Add object\n");
    printf("2. Delete object\n");
    printf("3. Modify object\n");
    printf("4. Display picture\n");
    printf("5. List objects\n");
    printf("0. Exit\n");
    printf("Enter choice: \n");
}

void printShapeMenu() {
    printf("Choose shape type:\n");
    printf("1. Line\n");
    printf("2. Rectangle\n");
    printf("3. Circle\n");
    printf("4. Triangle\n");
    printf("Enter shape type: ");
}

// ---- Main ----

int main() {
    int choice;
    clearPicture();

    while (1) {
        printMainMenu();
        scanf("%d", &choice);

        if (choice == 1) {
            // Add object
            int shapeType;
            printShapeMenu();
            scanf("%d", &shapeType);

            Shape s;
            s.type = shapeType;

            if (shapeType == SHAPE_LINE) {
                printf("Enter x1 y1 x2 y2: ");
                scanf("%d %d %d %d", &s.params[0], &s.params[1], &s.params[2], &s.params[3]);
            } else if (shapeType == SHAPE_RECT) {
                printf("Enter top-left x y and bottom-right x y: ");
                scanf("%d %d %d %d", &s.params[0], &s.params[1], &s.params[2], &s.params[3]);
            } else if (shapeType == SHAPE_CIRCLE) {
                printf("Enter center x y and radius: ");
                scanf("%d %d %d", &s.params[0], &s.params[1], &s.params[2]);
            } else if (shapeType == SHAPE_TRIANGLE) {
                printf("Enter x1 y1 x2 y2 x3 y3: ");
                scanf("%d %d %d %d %d %d",
                    &s.params[0], &s.params[1], &s.params[2],
                    &s.params[3], &s.params[4], &s.params[5]);
            }

            objects[objectCount] = s;
            printf("Object added with index %d.\n", objectCount);
            objectCount++;

        } else if (choice == 2) {
            // Delete object
            int idx;
            printf("Enter index to delete: ");
            scanf("%d", &idx);
            if (idx >= 0 && idx < objectCount) {
                for (int i = idx; i < objectCount - 1; i++)
                    objects[i] = objects[i+1];
                objectCount--;
                printf("Object %d deleted.\n", idx);
            } else {
                printf("Invalid index.\n");
            }

        } else if (choice == 3) {
            // Modify object
            int idx;
            printf("Enter index to modify: ");
            scanf("%d", &idx);
            if (idx >= 0 && idx < objectCount) {
                int shapeType;
                printShapeMenu();
                scanf("%d", &shapeType);
                objects[idx].type = shapeType;

                if (shapeType == SHAPE_LINE) {
                    printf("Enter x1 y1 x2 y2: ");
                    scanf("%d %d %d %d",
                        &objects[idx].params[0], &objects[idx].params[1],
                        &objects[idx].params[2], &objects[idx].params[3]);
                } else if (shapeType == SHAPE_RECT) {
                    printf("Enter top-left x y and bottom-right x y: ");
                    scanf("%d %d %d %d",
                        &objects[idx].params[0], &objects[idx].params[1],
                        &objects[idx].params[2], &objects[idx].params[3]);
                } else if (shapeType == SHAPE_CIRCLE) {
                    printf("Enter center x y and radius: ");
                    scanf("%d %d %d",
                        &objects[idx].params[0], &objects[idx].params[1],
                        &objects[idx].params[2]);
                } else if (shapeType == SHAPE_TRIANGLE) {
                    printf("Enter x1 y1 x2 y2 x3 y3: ");
                    scanf("%d %d %d %d %d %d",
                        &objects[idx].params[0], &objects[idx].params[1],
                        &objects[idx].params[2], &objects[idx].params[3],
                        &objects[idx].params[4], &objects[idx].params[5]);
                }
                printf("Object %d modified.\n", idx);
            } else {
                printf("Invalid index.\n");
            }

        } else if (choice == 4) {
            // Display picture
            displayPicture();

        } else if (choice == 5) {
            // List objects
            for (int i = 0; i < objectCount; i++) {
                int *p = objects[i].params;
                printf("Object %d: ", i);
                switch (objects[i].type) {
                    case SHAPE_LINE:
                        printf("Line (%d,%d) to (%d,%d)\n", p[0],p[1],p[2],p[3]); break;
                    case SHAPE_RECT:
                        printf("Rectangle (%d,%d) to (%d,%d)\n", p[0],p[1],p[2],p[3]); break;
                    case SHAPE_CIRCLE:
                        printf("Circle center (%d,%d) radius %d\n", p[0],p[1],p[2]); break;
                    case SHAPE_TRIANGLE:
                        printf("Triangle (%d,%d) (%d,%d) (%d,%d)\n",
                            p[0],p[1],p[2],p[3],p[4],p[5]); break;
                }
            }
} else if (choice == 0) {
            printf("Goodbye.\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}
