/*
 * MatrixPoint.cpp
 *
 *  Created on: 12.07.2014
 *      Author: joergw
 */

#include "MatrixPoint.h"

MatrixPoint::MatrixPoint( int count, short matrixDimension ) {
	this->x = count % matrixDimension;
	this->y = count / matrixDimension;
}

MatrixPoint::~MatrixPoint() {

}

