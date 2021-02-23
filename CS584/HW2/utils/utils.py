#!/usr/bin/env python

import numpy as np

def normalizeRows(x):
    """ Row normalization function

    Implement a function that normalizes each row of a matrix to have
    unit length.
    """
    ### YOUR CODE HERE DONE

    length = np.sqrt(np.sum(x*x, axis=1, keepdims=True))
    x = np.divide(x, length)

    ### END YOUR CODE
    return x

def softmax(x):
    """Compute the softmax function for each row of the input x.
    It is crucial that this function is optimized for speed because
    it will be used frequently in later code. 

    Arguments:
    x -- A D dimensional vector or N x D dimensional numpy matrix.
    Return:
    x -- You are allowed to modify x in-place
    """
    ### YOUR CODE HERE DONE
    col, row = x.shape

    if col == 1 or row == 1:
        x -= np.max(x)
        x = np.exp(x)
        x /= np.sum(x)
    else:
        max_row = np.max(x, axis=1, keepdims=True)
        x = np.subtract(x, max_row)
        x = np.exp(x)
        sum_row = np.sum(x, axis=1, keepdims=True)
        x = np.divide(x, sum_row)

    ### END YOUR CODE
    return x