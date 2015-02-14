#include "Model/Rectangle.h"

PRectangle::PRectangle(int x, int y, int width, int height){
	 this->x = x;
	 this->y = y;
	 this->width = width;
	 this->height = height;
}
int PRectangle::getY() {
        return y;
}

int PRectangle::getX() {
        return x;
}

int PRectangle::getHeight(){
	return height;
}

int PRectangle::getWidht(){
	return width;
}

bool PRectangle::intersects(PRectangle* r) const {
        int tw = this->width;
        int th = this->height;
        int rw = r->width;
        int rh = r->height;
        if (rw <= 0 || rh <= 0 || tw <= 0 || th <= 0) {
            return false;
        }
        int tx = this->x;
        int ty = this->y;
        int rx = r->x;
        int ry = r->y;
        rw += rx;
        rh += ry;
        tw += tx;
        th += ty;
        //      overflow || intersect
        return ((rw < rx || rw > tx) &&
                (rh < ry || rh > ty) &&
                (tw < tx || tw > rx) &&
                (th < ty || th > ry));
    }
