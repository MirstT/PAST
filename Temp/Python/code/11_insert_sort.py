def insert_sort(alist):
    for j in range(1, len(alist)):
        for i in range(j, 0, -1):
            if alist[i] < alist[i - 1]:
                alist[i], alist[i - 1] = alist[i - 1], alist[i]
            else:
                break


if __name__ == "__main__":
    li = [54, 24, 89, 37, 17, 8, 45, 23, 88, 69, 34, 23, 770, 45, 23, 19.30]
    print(li)
    insert_sort(li)
    print(li)
