import numpy as np
import math


#Part 1 Size N
def random_list_s( size : int ):
    return np.random.normal(0, 1, size)

#Part 1 Size N with mean and variance
def random_list( mean : float, var : float, size : int ):
    return np.random.normal(mean, math.sqrt(var), size)

#Test of function of value of N size
def test():
    list = random_list_s(10)
    print(f'Mean of size 10 is {np.mean(list)}')
    print(f'Variance of size 10 is {np.std(list, ddof=1) ** 2}')

    list = random_list_s(100)
    print(f'Mean of size 100 is {np.mean(list)}')
    print(f'Variance of size 100 is {np.std(list, ddof=1) ** 2}')

    list = random_list_s(1000)
    print(f'Mean of size 1000 is {np.mean(list)}')
    print(f'Variance of size 1000 is {np.std(list, ddof=1) ** 2}')

    list = random_list_s(10000)
    print(f'Mean of size 10000 is {np.mean(list)}')
    print(f'Variance of size 10000 is {np.std(list, ddof=1) ** 2}')

#Test of 2nd function with given value
def test2():
    list1 = random_list(1, 4, 2000)
    list2 = random_list(4, 9, 1000)

    print(f'Mean of list1 is {np.mean(list1)}')
    print(f'Variance of list1 is {np.std(list1, ddof=1) ** 2}')

    print(f'Mean of list2 is {np.mean(list2)}')
    print(f'Variance of list2 is {np.std(list2, ddof=1) ** 2}')

    print(f'Mean of combined list is {np.mean(np.concatenate((list1,list2), axis=None))}')
    print(f'Variance of combine is {np.std(np.concatenate((list1,list2), axis=None), ddof=1) ** 2}')

if __name__ == "__main__":
    test()
    test2()