#16124278 王浩 lesson6 code4 20180621
import datetime as d
import random

from copy import deepcopy  #深拷贝用

milk_tea_info={1:[3,'原味冰奶茶'],
               2:[5,'香蕉冰奶茶'],
               3:[5,'草莓冰奶茶'],
               4:[7,'蒟蒻冰奶茶'],
               5:[7,'珍珠冰奶茶']} #奶茶基本信息
end_day=(d.datetime.today()+d.timedelta(days=1)*30).strftime('%Y-%m-%d') #系统自开始30天后的终止日期
vip_discount=0.9 #vip折扣
buy_price=0 #单次消费总金额

buy_num_info={}
buy_price_info={} #记录当前订单金额
vip_tel_info={}   #记录每位会员的电话号码
cus_order_info={} #汇总同一顾客的所有消费情况
all_order_info={} #记录每条历史订单信息
#信息初始化

def gen_vipno():  #生成唯一的vip_no
    now_time=d.datetime.now().strftime("%Y%m%d%H%M%S") #生成当前时间
    randomNum=random.randint(0,100) #生成的随机整数randomNum，其中0<=randomNum<=100
    if randomNum<=10:
        randomNum=str(0)+str(randomNum)  #补全成三位数
    uniqueNum=str('100')+str(now_time)+str(randomNum)
    return uniqueNum
def start():
    print('-----欢迎光临小象奶茶馆!-----\n'
          '本奶茶馆提供以下{}种口味的奶茶:\n'
          '奶茶编号  奶茶口味  奶茶价格'.format(len(milk_tea_info)))
    for milk_tea_no in milk_tea_info.keys():  # j将奶茶基本信息进行格式化展示
        print('   {}     {}   {}元'
              .format(milk_tea_no,
                      milk_tea_info[milk_tea_no][1],
                      milk_tea_info[milk_tea_no][0]))
    print('--------本店特别推荐--------\n'
          '-爆款网红奶茶：4-蒟蒻冰奶茶-\n'
          '----------------------------')


def shopping_procedure():
    start()
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

            if (input('是否继续选购？退出选购按n，否则按任意键继续选购！')=='n'):
                break


def shopping_recommand():
    index=0
    recommand=0
    taste_customer=set(buy_num_info.keys())

    order_taste_len=[]
    order_taste_differ=[]

    if len(all_order_info):
        for order_id in all_order_info.keys():
            taste_others=set(all_order_info[order_id]['Order'].keys())

            inter=taste_others & taste_customer
            differ=taste_others - taste_customer

            order_taste_len.append(len(inter))

            if len(differ)==0 or len(inter)==0 or len(inter)==len(taste_others) or len(inter)<max(order_taste_len):
                continue
            order_taste_differ.append(list(differ))
            recommand = max(order_taste_differ[len(order_taste_differ) - 1])

        if recommand:
            print('---------------------------\n'
                  '根据您的订单信息进行分析\n'
                  '本店推荐您购买:\n'
                  '{}     {}   {}元\n'
                  '---------------------------'
                  .format(recommand,milk_tea_info[recommand][1],milk_tea_info[recommand][0]))

            if input('是否购买？购买请按y，否则按任意键退出选购！')=='y':
                buy_num=int(input('请输入购买数量：'))
                buy_num_info[recommand] = buy_num


def original_money():
    global buy_price #全局修改
    buy_price=0
    for milk_tea_no in buy_num_info.keys():
        buy_price_info[milk_tea_no] = milk_tea_info[milk_tea_no][0] * buy_num_info[milk_tea_no]
        buy_price+=buy_price_info.get(milk_tea_no, 0)

    vip_no=input('您是否为会员？'
              '如果是请输入会员号,'
              '如果不是请输入您的11位手机号，我们将为您分配会员号:')
    if vip_no not in vip_tel_info.keys():
        temp_info={}
        while len(vip_no)!=11:
            vip_no=input('请重新输入正确的11位电话号码：')
        vip_tel=vip_no
        vip_no=gen_vipno()
        vip_tel_info[vip_no]=vip_tel

        print('****************************************\n'
              '          已经为您生成会员号\n'
              '         {}\n'
              '          请您下次购物时使用！\n'
              '****************************************\n'
              '现在需要录入新会员的个人信息，请您如实填写.\n'
              '---------------------------'.format(vip_no))

        temp_info['Birthday']=input('请输入您的出生年月日：')
        temp_info['Gender']=input('请输入您的性别：')
        temp_info['Constellation']=input('请输入您的星座：')
        temp_info['Place']=input('请输入您的所在地:')
        print('---------------------------')

    else:
        print('你的会员认证通过，已享受九折价格优惠！')
        buy_price*=vip_discount

    buy_price=round(buy_price,3)    #价格统一保留两位小数
    temp_basic= {'Telephone': vip_tel_info[vip_no], 'Price': buy_price} #临时信息汇总
    temp_basic['Order']=deepcopy(buy_num_info) #临时信息汇总

    if vip_no not in cus_order_info.keys(): #汇总同一顾客的所有消费情况
        cus_order_info[vip_no]=dict(temp_basic,**temp_info) #写入新的会员信息
    else:
        cus_order_info[vip_no]['Price']+=buy_price
        for milk_tea_no in buy_num_info.keys():
            if milk_tea_no in cus_order_info[vip_no].keys():
                cus_order_info[vip_no][milk_tea_no] += buy_num_info[milk_tea_no]
            else:
                cus_order_info[vip_no][milk_tea_no]=buy_num_info[milk_tea_no]

    order_id=str(300)+str(d.datetime.now().strftime("%Y%m%d%H%M%S")) #唯一订单号
    order_time=d.datetime.now().strftime("%Y-%m-%d %H:%M:%S") #顾客到店信息！
    temp_customer={'Customer':vip_no,'Time':order_time} #临时信息汇总
    all_order_info[order_id]=dict(temp_basic,**temp_customer)  #写入历史订单信息


def shopping_print():  #购物信息打印
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
    shopping_recommand()
    original_money()
    shopping_print()

while d.datetime.today().strftime('%Y-%m-%d')!=end_day:
    print('---------{}----------'.format(end_day))
    for count in range(20): #每天接待二十位顾客
        main()
        print(cus_order_info) #展示顾客消费信息
        print(all_order_info) #展示所有订单信息
    print('------------------------------\n'
          '--今日已闭店，欢迎您明天光临！--\n'
          '------------------------------')
