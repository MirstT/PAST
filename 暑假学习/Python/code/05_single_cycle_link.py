# coding: utf-8

class Node(object):
    def __init__(self, elem):
        self.elem = elem
        self.next = None


class SingleLinkList(object):
    """"""

    def __init__(self, node=None):
        self._head = node
        if node:
            node.next = node

    def is_empty(self):
        """判断链表是否为空"""
        return self._head is None

    def length(self):
        """"""
        if self.is_empty():
            return 0
        cur = self._head
        count = 1
        while cur.next != self._head:
            count += 1
            cur = cur.next
        return count

    def travel(self):
        """"""
        cur = self._head
        if self.is_empty():
            return
        while cur.next != self._head:
            print(cur.elem, end=" ")
            cur = cur.next
        print(cur.elem)

    def add(self, item):
        node = Node(item)
        if self.is_empty():
            self._head = node
            node.next = node
        else:
            cur = self._head
            while cur.next != self._head:
                cur = cur.next
            node.next = self._head
            self._head = node
            cur.next = node

    def append(self, item):
        node = Node(item)
        if self.is_empty():
            self._head = node
            node.next = node
        else:
            cur = self._head
            while cur.next != self._head:
                cur = cur.next
            cur.next = node
            node.next = self._head

    def insert(self, pos, item):
        if pos <= 0:
            self.add(item)
        elif pos > (self.length() - 1):
            self.append(item)
        else:
            pre = self._head
            count = 0
            while count < (pos - 1):
                count += 1
                pre = pre.next
            node = Node(item)
            node.next = pre.next
            pre.next = node

    def remove(self, item):
        if self.is_empty():
            return

        cur = self._head
        pre = None

        while cur.next != self._head:
            if cur.elem == item:
                if cur == self._head:
                    rear = self._head
                    while rear.next != self._head:
                        rear = rear.next
                    self._head = cur.next
                    rear.next = self._head
                else:
                    pre.next = cur.next
                    cur.next = None
                return
            else:
                pre = cur
                cur = cur.next
        if cur.elem == item:
            if cur == self._head:
                self._head = None
        else:
            pre.next = cur.next
            cur.next = None


    def search(self, item):
        cur = self._head
        while cur != self._head:
            if cur.elem == item:
                return True
            else:
                cur = cur.next
        if cur.elem == item:
            return True
        return False


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

    ll.insert(-1, 233)
    ll.insert(2, 100000)
    ll.insert(100, 233333333333)
    ll.append(3)
    ll.remove(3)
    ll.travel()
    print(ll.length())
    print(ll.length())
