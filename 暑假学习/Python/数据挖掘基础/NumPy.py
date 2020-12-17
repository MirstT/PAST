from numpy  import *
'''
a = arange(15).reshape(3, 5)
print(a)
print(a.shape)
print(a.ndim)
print(a.dtype.name)
print(a.itemsize)

print(type(a))
print(a.dtype)

b=array([6,7,8])
print(b)

c=array([1.1,2.2,3.3])
print(c.dtype)
print(c)

print('*****************')
d=array([(1.2,2,3),(4,5,6)])
print(d)

print('################')
e=array([[1,2],[3,4]],dtype=complex)
print(e)
'''
"""
print(zeros((3,4)))
print('$$$$$$$$$$$$$$$$')
print(ones((2,3,4),dtype=int16))
print('!!!!!!!!!!!!!')
print(empty((2,3)))
"""
# print(arange(6))
# print(arange(12).reshape(4,3))
# print(arange(24).reshape(2,3,4))
# print(arange(10000))
#
# a=array([20,30,40,50])
# b=arange(4)
# print(a,b,a-b,b**2,a<35,10*sin(a))

# a=ones(3,dtype=int32)
# b=linspace(0,pi,3)
# print(a,b,b.dtype.name,a+b)
# c=a+b
# d=exp(c*1j)
# print()
# print(d,d.dtype.name)
#
# a=random.random((2,3))
# print(a,a.sum(),a.min(),a.max())


# b=arange(12).reshape(3,4)
#
# print(b)
# print('*******************')
# print(b.sum(axis=1),b.min(axis=0))
# print('###############')
# print(b.cumsum(axis=0))
# print(b.cumsum(axis=1))
#
# b=arange(3)
# c=array([2.,-1,4.5])
# print(exp(b),sqrt(b),add(b,c))

# a=arange(10)**3
# print(a)
# print(a[:10:2])
# a[:6:2]=-1000
# print(a)
# print(a[::-1])
# for i in a:
# #     print( i**(1/3))
#
# def f(x,y):
#     return  10*x+y
#
# b=fromfunction(f,(5,4),dtype=int)
# #
# # print(b)
# #
# # print(b[2],b[0:5,1],b[:,1],b[1:3])
#
# for row in b:
#     print(row)
#
# for element in b.flat:
#     print(element,end=' ')


# a=floor(10*random.random((3,4)))
# print(a)
# print(a.shape)
# print(a.ravel())
# a.shape=(6,2)
# print(a)
# print(a.transpose())
# a.resize((4,3))
# print(a)

# a=floor(10*random.random((2,2)))
# b=floor(10*random.random((2,2)))
# print(a)
# print(b)
# print('**************')
# print(vstack((a,b)))
# print(hstack((a,b)))
# print(column_stack((a,b)))
# print('~~~~~~~~~~~~~~~~~~~~~~~~')
# a=array([4.,2.])
# b=array([2.,8.])
# # print(a[:,newaxis])
# # print('~~~~~~~~~~~~~~~')
# # print(b[:,newaxis])
#
# # print(column_stack((a[:newaxis],b[:,newaxis])))
# print(vstack((a[:,newaxis],b[:,newaxis])))


# r_[1:4,0,4]
# print(r_)

# a=floor(10*random.random((2,12)))
# print(a)
# print(hsplit(a,3))
# print(hsplit(a,(1,4)))

a=arange(12)
b=a
b.shape=3,4
print(a,b,b.shape,a.shape)

def f(x):
    print(id(x))

print(id(a))
print(f(a))

c=a.view()
print('*************')
print(c,c.base,c.flags.owndata)
print('~~~~~~~~~~~~~~~~~~~~~~~')

c.shape=2,6
print(a.shape)
c[0,4]=1234
print(a)

print('$$$$$$$$$$$$$$$$$$$$$$$')
s=a[:,1:3]
print(s)
s[:]=10
print(a)
