#ifndef MYCELL
#define MYCELL

class Cell{
    public:
    Cell();
    Cell(const Cell&);
    int neighbor = 0;
    int status = 0;
    bool filled = false;
    char tac;
    int state() const;
    void reset();
    bool isFilled();
    void setX();
    void setO();


   // ~Cell();
};
#endif