#ifndef PRectangle_H_
#define PRectangle_H_
class PRectangle {
private:
    int x;
    int y;
    int width;
    int height;

public:
    PRectangle(int x, int y, int width, int height);
    bool intersects(PRectangle* r) const;
    int getY();
    int getX();
    int getWidht();
    int getHeight();

};
#endif /* PRectangle_H_ */
