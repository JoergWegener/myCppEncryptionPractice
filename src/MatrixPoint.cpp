/*
 * MatrixPoint.cpp
 *
 *  Created on: 12.07.2014
 *      Author: joergw
 */

#include "MatrixPoint.h"

MatrixPoint::MatrixPoint( int count, short matrixDimension ) {
	this->x = count % matrixDimension; // x is the rest (MODULO)
	this->y = count / matrixDimension; // y is number of full rows (DIV)
}

MatrixPoint::~MatrixPoint() {}

