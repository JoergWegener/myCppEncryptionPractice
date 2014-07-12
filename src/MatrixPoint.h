/*
 * MatrixPoint.h
 *
 *  Created on: 12.07.2014
 *      Author: joergw
 */

#ifndef MATRIXPOINT_H_
#define MATRIXPOINT_H_

struct MatrixPoint {
public:
	int x;
	int y;

	// Standard constructor takes the X and Y coordinates
	MatrixPoint( int inX, int inY) : x(inX), y(inY) {};

	// We can also calculate a MatrixPoint from a counter (running number)
	// and the matrix dimensions
	MatrixPoint ( int count, short matrixDimension );

	virtual ~MatrixPoint();
};

#endif /* MATRIXPOINT_H_ */
