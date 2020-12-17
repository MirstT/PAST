# coding: utf-8

def bubble_sort(alist):
    n = len(alist)
    for j in range(len(alist)-1, 0, -1):
        for i in range(j):
            if alist[i] > alist[i + 1]:
                alist[i], alist[i + 1] = alist[i + 1], alist[i]



if __name__ == "__main__":
    li = [54, 24, 89, 37, 17, 8, 45, 23, 88, 69, 34, 23, 770, 45, 23, 19.30]
    print(li)
    bubble_sort(li)
    print(li)
