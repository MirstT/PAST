# coding: utf-8

def shell_sort(alist):
    n = len(alist)
    gap = n // 2
    while gap>0:
        for j in range(gap, n):
            for i in range(j, 0, -gap):
                if alist[i] < alist[i - 1]:
                    alist[i], alist[i - 1] = alist[i - 1], alist[i]
                else:
                    break
        gap //= 2


if __name__ == "__main__":
    li = [54, 24, 89, 37, 17, 8, 45, 23, 88, 69, 34, 23, 770, 45, 23, 19.30]
    print(li)
    shell_sort(li)
    print(li)
