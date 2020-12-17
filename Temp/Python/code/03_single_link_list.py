# coding: utf-8

class Node(object):
    def __init__(self, elem):
        self.elem = elem
        self.next = None


class SingleLinkList(object):
    """"""

    def __init__(self, node=None):
        self._head = node

    def is_empty(self):
        """判断链表是否为空"""
        return self._head is None

    def length(self):
        """"""
        cur = self._head
        count = 0
        while cur != None:
            count += 1
            cur = cur.next
        return count

    def travel(self):
        """"""
        cur = self._head
        while cur != None:
            print(cur.elem, end=" ")
            cur = cur.next
        print()

    def add(self, item):
        node = Node(item)
        node.next = self._head
        self._head = node

    def append(self, item):
        node = Node(item)
        if self.is_empty():
            self._head = node
        else:
            cur = self._head
            while cur.next != None:
                cur = cur.next
            cur.next = node

    def insert(self, pos, item):
        if pos <= 0:
            self.add(item)
        elif pos >(self.length()-1):
            self.append(item)
        else:
            pre = self._head
            count=0
            while count < (pos-1):
                count +=1
                pre = pre.next
            node = Node(item)
            node.next = pre.next
            pre.next = node


    def remove(self, item):
        cur = self._head
        pre = None
        while cur != None:
            if cur.elem == item:
                if cur == self._head:
                    self._head = cur.next
                else:
                    pre.next = cur.next
                cur.next = None
                break
            else:
                pre = cur
                cur = cur.next


    # def pop(self):
    #     pass

    def search(self, item):
        cur = self._head
        while cur != None:
            if cur.elem == item:
                return True
            else:
                cur = cur.next
        return  False


if __name__ == "__main__":
    ll = SingleLinkList()
    print(ll.is_empty())
    print(ll.length())

    ll.append(1)
    print(ll.is_empty())
    print(ll.length())

    ll.append(2)
    ll.append(2)
    ll.add("start")
    ll.append("2333")
    ll.append(2)
    ll.append(2)
    ll.append(2)

    ll.insert(-1,233)
    ll.insert(2,100000)
    ll.insert(100,233333333333)
    ll.append(3)
    ll.remove(3)
    ll.travel()
    print(ll.length())
    print(ll.length())
