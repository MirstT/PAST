people={
    'Alice':{'phone':'2341','addr':'Foo drive 23'},
     'Beth':{'phone':'9102','addr':'Bar street 42'},
     'Alice':{'phone':'3158','addr':'Baz avenue 90'}
    }


labels={'phone':'phone number','addr':'address'}

name=input('Name:')

request=input('Phone number (p) or address (a):')

key=request

if request=='p':key='phone'
if request=='a':key='addr'

person=people.get(name,{})
label=labels.get(key,key)
result=person.get(key,'not available')

print("%s's %s is %s" %(name,label,result))
