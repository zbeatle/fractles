#include <ncurses.h>
#include <cmath>
#include <complex>
#include <iostream>
using namespace std;

double depth = 100;
long power = 2;

class window{
    public:
        long h, w;

        window(long hi, long wi){
            h = hi;
            w = wi;
        }

        void set(long x, long y, char val){
            attron(COLOR_PAIR(1));
            mvaddch(y,x, val);
            //win[(y * h) + x] = val;
        }

        void setcolor(long x, long y, char val, int color){
            attron(COLOR_PAIR(color));
            mvaddch(y,x, val);
            attroff(COLOR_PAIR(color));
        }

        void print(){
            refresh();
        }
};
void fillwin(window win, long double x, long double y, long double hei, long double wid);
long part(long double x, long double y);
int depthToColor(long d);

int main(){
    initscr();

    cbreak();
    noecho();
    start_color();

    long h, w;
    getmaxyx(stdscr, h, w);
    long double x1, y1, hei, wid, speed;
    x1 = -2.5;
    y1 = 2.5;
    hei = 5;
    wid = hei * (static_cast<long double> (w) / static_cast<long double> (h)) * (static_cast<long double> (9) / static_cast<long double> (16));
    speed = .1;
    

    window win (h, w);
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_GREEN, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_RED, COLOR_BLACK);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);
    bool go = true;
    while (go){
        getmaxyx(stdscr, h, w);
        int ch = getch();

        switch (ch){
            case 'h':
                x1 -= wid*speed;
                break;
            case 'j':
                y1 -= hei*speed;
                break;
            case 'k':
                y1 += hei*speed;
                break;
            case 'l':
                x1 += wid*speed;
                break;
            case 'a':
                wid -= wid/2;
                hei -= hei/2;
                x1 += wid/2;
                y1 -= hei/2;
                break;
            case 'z':
                x1 -= wid/2;
                y1 += hei/2;
                wid += wid;
                hei += hei;
                break;
            case 'i':
                depth *= 2;
                break;
            case 'o':
                depth /= 2;
                break;
            case ',':
                power--;
                break;
            case '.':
                power++;
                break;
                
            case 'q':
                go = false;
        }

        fillwin(win, x1, y1, hei, wid);
        win.print();

    }

    endwin();
    cout << wid << endl;
    cout << w << " " << h;
    return 0;
} 
void fillwin(window win, long double x, long double y, long double hei, long double wid){
    for(int i = 0; i < win.h; i++ ){
        for(int j = 0; j < win.w; j++ ){
            win.setcolor(j, i, '#', depthToColor(part((j * (wid/win.w)) + x, (-1 * (i * (hei/win.h))) + y)));
        }
    }

}

long part(long double x, long double y){
    std::complex<long double> c (x, y);
    std::complex<long double> val (x, y);
    long i = 0;
    for(; i < depth; i++){
        val = pow(val, power);
        val = val + c;
        if (abs(val) > 2){
            break;
        }
    }
    return i;
}

int depthToColor(long d){
    long double close = static_cast<long double> (d) / static_cast<long double> (depth);

    if(close >= 1){
        return 1;
    }if(close >= (double) 6.0/ (double) 7.0){
        return 2;
    }if(close >= (double) 5.0/ (double) 7.0){
        return 3;
    }if(close >= (double) 4.0/ (double) 7.0){
        return 4;
    }if(close >= (double) 3.0/ (double) 7.0){
        return 5;
    }if(close >= (double) 2.0/ (double) 7.0){
        return 6;
    }if(close >= (double) 1.0/ (double) 7.0){
        return 7;
    }
    return 8;
    

    
}
