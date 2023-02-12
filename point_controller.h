#ifndef POINT_CONTROLLER_H
#define POINT_CONTROLLER_H

class point_2d
{
    private:
        int x;
        int y;
    public:
        point_2d(int source_x, int source_y);  // constructor
        point_2d(const point_2d& source_point);  // copy constructor
        ~point_2d();  // destructor
        // accessor functions
        int get_x();
        int get_y();
        point_2d get_point();  // get the entire point
        void set_x(int set_x);
        void set_y(int set_y);
        point_2d set_point(int source_x, int source_y);  // set the entire point
};

class line_2d
{
    private:
        point_2d point_0;
        point_2d point_1;
    public:
        line_2d(point_2d source_0, point_2d source_1);  // constructor
        line_2d(const line_2d& source_line);  // copy constructor
        ~line_2d();  // destructor

        // accessor functions
        point_2d get_id_point(int id);  // get point with id
        line_2d get_line();  // get the entire line
        void set_id_point(point_2d source, int id);  // set point with id
        void set_line(point_2d source_0, point_2d source_1);  // set the entire line
};

#endif  // POINT_CONTROLLER_H