struct point{
    int x,y;
    point(int x=0,int y=0):x(x),y(y){}
    friend point operator+(point u,point v){
        return point(u.x+v.x,u.y+v.y);
    }    
};