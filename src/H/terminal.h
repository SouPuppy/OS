#ifndef TERMINAL_H
#define TERMINAL_H

typedef struct terminal {
    int xlim, ylim;
    char *buff[];
    int cruiser_x, cruiser_y;

    

    void clear_word(int x, int y);
    void clear_line(int x);
    void clear_page();

    void cruiser_set(int x, int y);
    void cruiser_next();
};

#endif  // TERMINAL_H
