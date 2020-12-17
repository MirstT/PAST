#16124278 王浩 lesson5 code1 test3 20180621
import datetime
import random

milk_tea_info={1:[3,'原味冰奶茶'],
               2:[5,'香蕉冰奶茶'],
               3:[5,'草莓冰奶茶'],
               4:[7,'蒟蒻冰奶茶'],
               5:[7,'珍珠冰奶茶']} #奶茶基本信息
vip_discount=0.9 #vip折扣

buy_num_info={}
buy_price_info={} #记录当前订单金额
vip_tel_info={}   #记录每位会员的电话号码
cus_order_info={} #汇总同一顾客的所有消费情况
all_order_info={} #记录每条历史订单信息
#信息初始化


def gen_vipno():  #生成唯一的vip_no
    now_time=datetime.datetime.now().strftime("%Y%m%d%H%M%S") #生成当前时间
    randomNum=random.randint(0,100) #生成的随机整数randomNum，其中0<=randomNum<=100
    if randomNum<=10:
        randomNum=str(0)+str(randomNum)  #补全成三位数
    uniqueNum=str('100')+str(now_time)+str(randomNum)
    return uniqueNum


def shopping_procedure():
    print('-----欢迎光临小象奶茶馆!-----\n'
          '本奶茶馆提供以下{}种口味的奶茶:\n'
          '奶茶编号  奶茶口味  奶茶价格'.format(len(milk_tea_info)))
    for milk_tea_no in milk_tea_info.keys():    #j将奶茶基本信息进行格式化展示
        print('   {}     {}   {}元'
              .format(milk_tea_no,
                      milk_tea_info[milk_tea_no][1],
                      milk_tea_info[milk_tea_no][0]))

    while True:
        milk_tea_no_float=float(input('请输入想购买的奶茶口味编号（1-5）:'))
        milk_tea_no=int(milk_tea_no_float)
        if milk_tea_no!=milk_tea_no_float:
            print('请输入整数来选择奶茶！')
        elif milk_tea_no==milk_tea_no_float and milk_tea_no<1 or milk_tea_no>5:
            print('Woops!我们只售卖以上5种奶茶哦，新的口味尽情期待！')
        else:
            buy_num_float=float(input('请输入购买数量：'))
            buy_num=int(buy_num_float)
            while buy_num!= buy_num_float or buy_num<=0:
                buy_num_float = float(input('请输入正确的购买数量：'))
                buy_num = int(buy_num_float)

            if milk_tea_no not in buy_num_info.keys():
                buy_num_info[milk_tea_no]=buy_num
            else:
                buy_num_info[milk_tea_no]+=buy_num

            if (input('是否继续选购？退出选购按n/N，否则按任意键继续选购！')==('n'or'N') ):
                break



def original_money():
    buy_price=0
    for milk_tea_no in buy_num_info.keys():
        buy_price_info[milk_tea_no] = milk_tea_info[milk_tea_no][0] * buy_num_info[milk_tea_no]
        buy_price+=buy_price_info.get(milk_tea_no, 0)

    vip_no=int(input('您是否为会员？'
              '如果是请输入会员号,'
              '如果不是请输入您的手机号，我们将为您分配会员号:'))      #将会员号转化为int型录入！
    if vip_no not in vip_tel_info.keys():
        vip_tel=vip_no
        vip_no=gen_vipno()
        vip_tel_info[vip_no]=vip_tel
        print('已经为您生成会员号{}，请您下次购物时使用！'.format(vip_no))
    else:
        print('你的会员认证通过，已享受九折价格优惠！')
        buy_price*=vip_discount

    buy_price=round(buy_price,2)    #价格统一保留两位小数
    temp = {'Telephone': vip_tel_info[vip_no], 'Price': buy_price}
    temp.update(buy_num_info)

    if vip_no not in cus_order_info.keys(): #汇总同一顾客的所有消费情况
        cus_order_info[vip_no]=temp
    else:
        cus_order_info[vip_no]['Price']+=buy_price
        for milk_tea_no in buy_num_info.keys():
            if milk_tea_no in cus_order_info[vip_no].keys():
                cus_order_info[vip_no][milk_tea_no] += buy_num_info[milk_tea_no]
            else:
                cus_order_info[vip_no][milk_tea_no]=buy_num_info[milk_tea_no]

    order_id=str(datetime.datetime.now().strftime("%Y%m%d%H%M%S"))
    temp_customer={'Customer':vip_no}
    all_order_info[order_id]=dict(temp,**temp_customer)  #写入历史订单信息

    return buy_price


def shopping_print(buy_price):  #购物信息打印
    print('==========================\n'
          '---------购物清单---------\n'
          '编号    名称    数量 原价')

    for milk_tea_no in buy_num_info.keys():  #购物清单输出
        print(' {}   {}  {}   {}元'
              .format(milk_tea_no,
                      milk_tea_info[milk_tea_no][1],
                      buy_num_info[milk_tea_no],
                      buy_price_info[milk_tea_no]))

    print('------实际付款：{}元------\n'
          '==========================\n'
          .format(buy_price))

    buy_num_info.clear()


def main():  #主程序
    shopping_procedure()
    shopping_print(original_money())


for count in range(20): #每天接待二十位顾客
    main()
    #print(cus_order_info) #展示顾客消费信息
    #print(all_order_info) #展示所有订单信息
print('------------------------------\n'
      '--今日已闭店，欢迎您明天光临！--\n'
      '------------------------------')