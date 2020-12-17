def binary_search(alist, item):
    n = len(alist)
    if n > 0:
        mid = n // 2
        if alist[mid] == item:
            return True
        elif item < alist[mid]:
            return binary_search(alist[:mid], item)
        else:
            return binary_search(alist[mid + 1:], item)
    return False


def binary_search_2(alist, item):
    n = len(alist)
    first = 0
    last = n - 1
    while first <= last:
        mid = (first + last) // 2
        if alist[mid] == item:
            return True
        elif item < alist[mid]:
            last = mid - 1
        else:
            first = mid + 1
    return  False

if __name__ == "__main__":
    li = [8, 17, 19.3, 23, 23, 23, 24, 34, 37, 45, 45, 54, 69, 88, 89, 770]
    print(binary_search(li, 37))
    print(binary_search(li, 233333))
