def quick_sort(alist,first,last):
    if first >= last:
        return
    mid_value = alist[first]
    low = first
    high = last

    while low < high:
        while low < high and alist[high] >= mid_value:
            high -= 1
        alist[low] = alist[high]

        while low < high and alist[low] < mid_value:
            low += 1
        alist[high] = alist[low]
    alist[low] = mid_value

    quick_sort(alist,first,low-1)
    quick_sort(alist,low+1,last)

if __name__ == "__main__":
    li = [54, 24, 89, 37, 17, 8, 45, 23, 88, 69, 34, 23, 770, 45, 23, 19.30]
    print(li)
    quick_sort(li,0,len(li)-1)
    print(li)
