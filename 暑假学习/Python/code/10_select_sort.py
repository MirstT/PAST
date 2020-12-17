def select_sort(alist):
    n = len(alist)
    for j in range(n - 1):
        min_index = j
        for i in range(j + 1, n):
            if alist[min_index] > alist[i]:
                min_index = i
        alist[j], alist[min_index] = alist[min_index], alist[j]


if __name__ == "__main__":
    li = [54, 24, 89, 37, 17, 8, 45, 23, 88, 69, 34, 23, 770, 45, 23, 19.30]
    print(li)
    select_sort(li)
    print(li)
