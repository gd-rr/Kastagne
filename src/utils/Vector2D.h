/*******************************************************************************
 * @file Vector2D.h
 * @brief Defines the Vector2D struct for representing a position in two 
 *        dimension.
 ******************************************************************************/

#ifndef _VECTOR_2D_H
#define _VECTOR_2D_H

/*******************************************************************************
 * @struct Vector2D
 * @brief Represents a 2D vector with integer coordinates.
 * 
 * This struct represents a 2D vector with integer coordinates. It consists of 
 * two integer fields: x and y, representing the horizontal and vertical 
 * components of the vector, respectively.
 ******************************************************************************/
struct Vector2D {
    int x; /**< The x-coordinate of the vector. */
    int y; /**< The y-coordinate of the vector. */
};

#endif // _VECTOR_2D_H
