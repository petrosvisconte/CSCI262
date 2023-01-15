/*
    pathfinder.cpp
        
    Method implementations for the pathfinder class.
    
    assignment: CSCI 262 Project - Pathfinder        

    author: <Pierre Visconti>
*/

#include <iostream>
#include "pathfinder.h"
#include <fstream>

using namespace std;

// constructor - optional, in case you need to initialize anything
pathfinder::pathfinder() { ; }

// public run() method - invokes private methods to do everything;
// returns the total elevation change cost of the best optimal path.
int pathfinder::run(string data_file_name, string save_file_name) {
    // suggested implementation - modify as desired!
    if (!_read_data(data_file_name)) {
        cout << "Error reading map data from \"" << data_file_name << "\"!" << endl;
	return -1;
    }

    _draw_map();
    
    int best_cost = _draw_paths();

    _save_image(save_file_name);

    return best_cost;
}

/*******************/
/* PRIVATE METHODS */
/*******************/

// _read_data - read and store width, height, and elevation data from the
// provided data file; return false if something goes wrong
bool pathfinder::_read_data(string data_file_name) {
    ifstream file;
    file.open(data_file_name);

    if (file.is_open()) {
        string cols;
        string rows;
        file >> cols >> _width >> rows >>_height;
        _elevations = vector<vector<int>>(_height, vector<int>(_width));
        for (int i = 0; i < _height; i++) {
            for (int j  = 0; j < _width; j++) {
                file >> _elevations[i][j];
                if (_elevations[i][j] < _min) {
                    _min = _elevations[i][j];
                } else if (_elevations[i][j] > _max) {
                    _max = _elevations[i][j];
                }
            }
        }
        file.close();
        //cout << _min << endl << _max;
        return true;
    }
}

// _draw_map - draw the elevation data as grayscale values on our Picture
// object.
void pathfinder::_draw_map() {
    //TO DO: determine min/max elevation values in map

    //Created private variables in pathfinder.h called _min and _max, and then found them while
    //in the for loop that read the data from the file and saved to the 2D vector in the _read_data() function
    _image.set(_width - 1, _height - 1, 0, 0, 0);
    vector<vector<int>> gray;
    gray = vector<vector<int>>(_height, vector<int>(_width));
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            double rgb = (double(_elevations[i][j] - (double)_min)) / (_max - _min) * 255;
            gray[i][j] = (int)rgb;
        }
    }
    //Sets all rgb values in vector to gray
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            int r, g, b;
            r = g = b = gray[y][x];
            _image.set(x, y, r, g, b);
        }
    }
}

// _draw_paths() - find and draw optimal paths from west to east using 
// dynamic programming; return the best optimal path cost
int pathfinder::_draw_paths() {
    //Vector that holds minimum costs values for all steps
    vector<vector<int>> minCost = vector<vector<int>>(_height, vector<int>(_width));
    //Vector that holds the direction of path for all steps
    vector<vector<char>> dir = vector<vector<char>>(_height, vector<char>(_width));
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            int cost;
            int costE;
            int costNE;
            int costSE;
            char direct;
            if (j == _width - 1) {
                cost = 0;
                direct = 'w';
            } else if (j == 0) {
                cost = 1;
            } else {
                if (i == 0) {
                    costE = abs(_elevations[i][j+1] - _elevations[i][j]);
                    costSE = abs(_elevations[i+1][j+1] - _elevations[i][j]);
                    if (costE < costSE) {
                        cost = costE;
                        direct = 'e';
                    } else if (costSE < costE) {
                        cost = costSE;
                        direct = 's';
                    } else {
                        cost = costE;
                        direct = 'e';
                    }
                } else if (i == _height - 1) {
                    costE = abs(_elevations[i][j+1] - _elevations[i][j]);
                    costNE = abs(_elevations[i-1][j+1] - _elevations[i][j]);
                    if (costE < costNE) {
                        cost = costE;
                        direct = 'e';
                    } else if (costNE < costE) {
                        cost = costNE;
                        direct = 'n';
                    } else {
                        cost = costE;
                        direct = 'e';
                    }
                } else {
                    costE = abs(_elevations[i][j+1] - _elevations[i][j]);
                    costNE = abs(_elevations[i-1][j+1] - _elevations[i][j]);
                    costSE = abs(_elevations[i+1][j+1] - _elevations[i][j]);
                    cost = costE;
                    direct = 'e';
                    if (costSE < cost) {
                        cost = costSE;
                        direct = 's';
                    } else if (costNE < cost) {
                        cost = costNE;
                        direct = 'n';
                    }
                }
            }
            //Cost at i,j = lowest cost calculated above
            minCost[i][j] = cost;
            //cout << cost << "  ";
            //Direction of path of lowest cost at i,j
            dir[i][j] = direct;
            //cout << direct << " ";
        }
        //cout << endl;
    }
    //Change 0 to -1
    //Calculates the location of where to draw the pixel in a 2D vector initialized to all 0
    //If path exists there then change value to 1
    vector<vector<int>> draw = vector<vector<int>>(_height, vector<int>(_width));
    int costE, costNE, costSE, cost = 0;
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            if (i == 0) {
                costE = abs(minCost[i][j+1] - minCost[i][j]);
                costSE = abs(minCost[i+1][j+1] - minCost[i][j]);
                if (costE < costSE) {
                    cost = costE;
                    if (j != _width -1 && dir[i][j+1] == 'e') {
                        draw[i][j+1] = 1;
                    }
                } else if (costSE < costE) {
                    cost = costSE;
                    //draw[i+1][j+1] = 1;
                } else {
                    cost = costE;
                    if (j != _width -1) {
                        //draw[i][j+1] = 1;
                    }
                }
            } else if (i == _height - 1) {
                costE = abs(minCost[i][j+1] - minCost[i][j]);
                costNE = abs(minCost[i-1][j+1] - minCost[i][j]);
                if (costE < costNE) {
                    cost = costE;
                    if (j != _width -1 && dir[i][j+1] == 'e') {
                        draw[i][j+1] = 1;
                    }
                } else if (costNE < costE) {
                    cost = costNE;
                    //draw[i-1][j+1] = 1;
                } else {
                    cost = costE;
                    if (j != _width -1) {
                        //draw[i][j+1] = 1;
                    }
                }
            } else {
                costE = abs(minCost[i][j+1] - minCost[i][j]);
                costNE = abs(minCost[i-1][j+1] - minCost[i][j]);
                costSE = abs(minCost[i+1][j+1] - minCost[i][j]);
                cost = costE;
                if (costSE < cost) {
                    cost = costSE;
                    //draw[i+1][j+1] = 1;
                } else if (costNE < cost) {
                    cost = costNE;
                    //draw[i-1][j+1] = 1;
                } else if (cost == costE) {
                    if (j != _width -1 && dir[i][j+1] == 'e') {
                        draw[i][j+1] = 1;
                    }
                }
            }
            if(j == 0) {
                draw[i][j] = 1;
            } else if (j == _width - 1) {
                draw[i][j] = 0;
            }
            //draw[i][j] = cost;
            //cout << cost << " ";
        }
        //cout << endl;
    }

    //Draws all the optimal paths
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            if (draw[i][j] == 1) {
                _image.set(j,i,0,0,255);
            }
        }
    }
    int min = minCost[0][0];
    int minLoc = 0;
    char direct;
    for (int i = 0; i < _width; i++) {
        for (int j = 0; j < _height; j++) {
            if (minCost[j][i] < min) {
                min = minCost[j][i];
            }
        }
    }
}

// _save_image - we'll do this one for you :)
void pathfinder::_save_image(string save_file_name) {
    _image.save(save_file_name);
}

