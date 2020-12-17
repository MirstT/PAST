width=input('Please enter width: ')
iwidth=int(width)
price_width=10
item_width=iwidth-price_width

header_format='%-*s%*s'


print('='*iwidth)
print('%-*s%*s'%(item_width,'Item',price_width,'Price'))
print('-'*iwidth)

print('%-*s%*.2f'%(item_width,'Apples',price_width,0.4))
print('%-*s%*.2f'%(item_width,'Pears',price_width,0.5))
print('%-*s%*.2f'%(item_width,'Cantaloupres',price_width,1.42))
print('%-*s%*.2f'%(item_width,'Dried Apricots',price_width,8))
print('%-*s%*.2f'%(item_width,'Pruns',price_width,12))

print('-'*iwidth)
