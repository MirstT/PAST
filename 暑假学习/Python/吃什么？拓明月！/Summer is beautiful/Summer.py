import pygame,sys,time
from random import randint

class TankMain(object):
    width=1000
    height=1000
    wall=None
    my_tank_missile_list = []
    #enemy_list = []
    enemy_list = pygame.sprite.Group() #敌方坦克族群
    explode_list=[]
    enemy_missile_list=pygame.sprite.Group()
    my_tank =None  # 创建我方坦克 and 默认指定位置

    def startGmae(self):
        pygame.init() #初始化

        screen=pygame.display.set_mode((TankMain.width,TankMain.height),32,32) #初始窗口

        pygame.display.set_caption('吃拓拓啦~~~~~')  #标题


        TankMain.my_tank=My_Tank(screen)  #初始化坦克和子弹
        for i in range(1,15): #小护士话化敌方坦克
            TankMain.enemy_list.add(Enemy_Tank(screen))


        while True:
            screen.fill((255,255,255)) #bg色


            for i, text in enumerate(self.write_text(),0):
                screen.blit(text,(0,5+(22*i))) #字体



            self.get_event(TankMain.my_tank)  #获取事件

            TankMain.my_tank.hit_enemy_missile() #我方坦克和敌方的炮弹进行碰撞检测
            if TankMain.my_tank.live:
                TankMain.my_tank.display()  # 我方展示
                TankMain.my_tank.move()
            else:
                print('GAME OVER')
                sys.exit()
                # TankMain.my_tank=None


            for enemy in TankMain.enemy_list:
                enemy.display()
                enemy.random_move()


            for m in TankMain.my_tank_missile_list:
                if m.live:
                    m.display()

                    m.move()
                else:
                    TankMain.my_tank_missile_list.remove(m)

            for m in TankMain.enemy_missile_list:
                if m.live:
                    m.display()

                    m.move()
                else:
                    TankMain.enemy_missile_list.remove(m)

            for explode in TankMain.explode_list:
                explode.display()

                pygame.display.update()

            # time.sleep(0.05)  休眠
            pygame.display.update() #显示重置！ 界面刷新

    def get_event(self,my_tank):
        for event in pygame.event.get():
            if event.type == pygame.QUIT: #X
                self.stopGame() #程序退出
            if event.type == pygame.KEYDOWN and my_tank.live: #按键按下
                if event.key==pygame.K_LEFT or event.key==pygame.K_a:
                    my_tank.direction='L'
                    my_tank.stop=False
                    # my_tank.move()
                if event.key==pygame.K_RIGHT or event.key==pygame.K_d:
                    my_tank.direction = 'R'
                    my_tank.stop=False
                    # my_tank.move()
                if event.key==pygame.K_UP or event.key==pygame.K_w:
                    my_tank.direction = 'U'
                    my_tank.stop=False
                    # my_tank.move()
                if event.key==pygame.K_DOWN or event.key==pygame.K_s:
                    my_tank.direction = 'D'
                    my_tank.stop=False
                    # my_tank.move()
                if event.key==pygame.K_SPACE:
                    m=my_tank.fire()
                    m.good=True #我方坦克发射的炮弹
                    TankMain.my_tank_missile_list.append(m)
                if event.key==pygame.K_ESCAPE:
                    self.stopGame() #esc 程序退出
            if event.type==pygame.KEYUP:
                if event.key==pygame.K_LEFT or event.key==pygame.K_RIGHT or event.key==pygame.K_UP or event.key==pygame.K_DOWN:
                    my_tank.stop=True

    def set_title(self):
        pass

    def stopGame(self):
        sys.exit()

    def write_text(self):
        font=pygame.font.SysFont("华文琥珀",20)
        text_sf1=font.render('敌方坦克数量为：%d'%len(TankMain.enemy_list),True,(0,0,0))
        text_sf2=font.render('我方坦克炮弹数量：%d'%len(TankMain.my_tank_missile_list),True,(0,0,0))
        return  text_sf1,text_sf2



class BaseItem(pygame.sprite.Sprite):
    def __init__(self,screen):
        pygame.sprite.Sprite.__init__(self)
        self.screen=screen

    def display(self):
        if self.live:
            self.image = self.images[self.direction]
            self.screen.blit(self.image, self.rect)



class Explode(BaseItem):
    def __init__(self,screen,rect):
        super().__init__(screen)
        self.live=True
        self.images=[pygame.image.load('images/1.gif'),pygame.image.load('images/1.gif'),pygame.image.load('images/1.gif'),pygame.image.load('images/1.gif'),pygame.image.load('images/1.gif'),pygame.image.load('images/1.gif'),pygame.image.load('images/1.gif'),          \
                    pygame.image.load('images/1.gif'),pygame.image.load('images/1.gif'),pygame.image.load('images/1.gif'),pygame.image.load('images/1.gif'),pygame.image.load('images/1.gif'),pygame.image.load('images/1.gif'),pygame.image.load('images/1.gif'),          \
                     pygame.image.load('images/2.gif'), pygame.image.load('images/2.gif'),pygame.image.load('images/2.gif'),pygame.image.load('images/2.gif'),pygame.image.load('images/2.gif'),pygame.image.load('images/2.gif'),pygame.image.load('images/2.gif'),        \
                     pygame.image.load('images/3.gif'),pygame.image.load('images/3.gif'),pygame.image.load('images/3.gif'),pygame.image.load('images/3.gif'),pygame.image.load('images/3.gif'),pygame.image.load('images/3.gif'),pygame.image.load('images/3.gif'),         \
                     pygame.image.load('images/4.gif'), pygame.image.load('images/4.gif'),pygame.image.load('images/4.gif'),pygame.image.load('images/4.gif'),pygame.image.load('images/4.gif'),pygame.image.load('images/4.gif'),pygame.image.load('images/4.gif'),        \
                     pygame.image.load('images/4.gif'), pygame.image.load('images/4.gif'),pygame.image.load('images/4.gif'),pygame.image.load('images/4.gif'),pygame.image.load('images/4.gif'),pygame.image.load('images/4.gif'),pygame.image.load('images/4.gif'),        \
                     pygame.image.load('images/5.gif'),pygame.image.load('images/5.gif'),pygame.image.load('images/5.gif'),pygame.image.load('images/5.gif'),pygame.image.load('images/5.gif'),pygame.image.load('images/5.gif'),pygame.image.load('images/5.gif'),      \
                     pygame.image.load('images/5.gif'),pygame.image.load('images/5.gif'),pygame.image.load('images/5.gif'),pygame.image.load('images/5.gif'),pygame.image.load('images/5.gif'),pygame.image.load('images/5.gif'),pygame.image.load('images/5.gif'),      \
                     pygame.image.load('images/5.gif'),pygame.image.load('images/5.gif'),pygame.image.load('images/5.gif'),pygame.image.load('images/5.gif'),pygame.image.load('images/5.gif'),pygame.image.load('images/5.gif'),pygame.image.load('images/5.gif'),      \
                     pygame.image.load('images/6.gif'), pygame.image.load('images/6.gif'),pygame.image.load('images/6.gif'),pygame.image.load('images/6.gif'),pygame.image.load('images/6.gif'),pygame.image.load('images/6.gif'),pygame.image.load('images/6.gif'),        \
                     pygame.image.load('images/6.gif'), pygame.image.load('images/6.gif'),pygame.image.load('images/6.gif'),pygame.image.load('images/6.gif'),pygame.image.load('images/6.gif'),pygame.image.load('images/6.gif'),pygame.image.load('images/6.gif'),        \
                     pygame.image.load('images/7.gif'),pygame.image.load('images/7.gif'), pygame.image.load('images/7.gif'), pygame.image.load('images/7.gif'), pygame.image.load('images/7.gif'), pygame.image.load('images/7.gif'), pygame.image.load('images/7.gif'),         \
                     pygame.image.load('images/8.gif'), pygame.image.load('images/8.gif'),pygame.image.load('images/8.gif'),pygame.image.load('images/8.gif'),pygame.image.load('images/8.gif'),pygame.image.load('images/8.gif'),pygame.image.load('images/8.gif'),        \
                     pygame.image.load('images/9.gif'),pygame.image.load('images/9.gif'),pygame.image.load('images/9.gif'),pygame.image.load('images/9.gif'),pygame.image.load('images/9.gif'),pygame.image.load('images/9.gif'),pygame.image.load('images/9.gif'),         \
                     pygame.image.load('images/10.gif'), pygame.image.load('images/10.gif'),pygame.image.load('images/10.gif'),pygame.image.load('images/10.gif'),pygame.image.load('images/10.gif'),pygame.image.load('images/10.gif'),pygame.image.load('images/10.gif'),     ]

        self.step=0
        self.rect=rect #爆炸位置获取 参数获取

    def display(self):
        if self.live:
            if self.step==len(self.images): #最后一张爆炸图片已经显示
                self.live=False
            else:
                self.image=self.images[self.step]
                self.screen.blit(self.image,self.rect)
                self.step+=1
        else:
            pass




class Tank(BaseItem):
    #定义类属性，所有坦克的高度和宽度都一样
    width=73
    height=73
    def __init__(self,screen,left,top):
        super().__init__(screen)
        self.direction='D' # 坦克的方向，默认向下
        self.speed=1 #v
        self.stop = False  # 静止状态
        self.images={} #坦克的所有图片，key：方向，value：图片（surface）
        self.images['L']=pygame.image.load('images/tankL.gif')
        self.images['R']=pygame.image.load('images/tankR.gif')
        self.images['U']=pygame.image.load('images/tankU.gif')
        self.images['D']=pygame.image.load('images/tankD.gif')
        self.image=self.images[self.direction] #坦克的图片由方向决定
        self.rect=self.image.get_rect()
        self.rect.left=left
        self.rect.top=top

        self.live=True #存活与否！

        self.oldtop=self.rect.top
        self.oldleft=self.rect.left

    def stay(self):
        self.rect.top=self.oldtop
        self.rect.left=self.oldleft

    def move(self):
        if self.live:
            if not self.stop:   #如果不是停止状态则移动！
                self.oldleft=self.rect.left
                self.oldtop=self.rect.top
                if self.direction=='L':
                    if self.rect.left>0: #屏幕左边界
                        self.rect.left-=self.speed
                    else:
                        self.rect.left=0
                elif self.direction=='R':
                    if self.rect.right<TankMain.width:
                        self.rect.right+=self.speed
                    else:
                        self.rect.right=TankMain.width
                elif self.direction=='U':
                    if self.rect.top>0:
                        self.rect.top-=self.speed
                    else:
                        self.rect.top=0
                elif self.direction=='D':
                    if self.rect.top<TankMain.height-Tank.height:
                        self.rect.top+=self.speed
                    else:
                        self.rect.top=TankMain.height-Tank.height
    def fire(self):
        m=Missile(self.screen,self)
        return m



class My_Tank(Tank):
    def __init__(self,screen):
        super().__init__(screen,460,760)
        self.stop=True #静止状态
        self.live=True

    def hit_enemy_missile(self):
        hit_list=pygame.sprite.spritecollide(self,TankMain.enemy_missile_list,False)
        for m in hit_list: #我方坦克中弹
            m.live=False
            TankMain.enemy_missile_list.remove(m)
            self.live=False
            explode=Explode(self.screen,self.rect)
            TankMain.explode_list.append(explode)




class Enemy_Tank(Tank):
    def __init__(self,screen):
        super().__init__(screen,randint(1,10)*100,250)
        self.speed=1
        self.step=randint(50,200)
        self.get_random_direction()



    def get_random_direction(self):
        r = randint(0, 4)
        if r == 4:
            self.stop = True
        elif r == 3:
            self.direction = 'L'
            self.stop = False
        elif r == 2:
            self.direction = 'U'
            self.stop = False
        elif r == 1:
            self.direction = 'D'
            self.stop = False
        elif r == 0:
            self.direction = 'R'
            self.stop = False

    #敌方坦克，随机移动
    def random_move(self):
        if self.live:
            if self.step==0:
                self.get_random_direction()
                self.step=randint(50,200)
            else:
                self.move()
                self.step-=1

    def random_fire(self):
        r=randint(0,100)
        if r>99:
            m=self.fire()
            TankMain.enemy_missile_list.add(m)
        else:
            return






class Missile(BaseItem):
    width=9
    height=38
    def __init__(self,screen,tank):
        super().__init__(screen)
        self.tank=tank
        self.direction=tank.direction #方向一致
        self.speed = 4  # v
        self.images = {}  # 炮弹的所有图片，key：方向，value：图片（surface）
        self.images['L'] = pygame.image.load('images/missileL.gif')
        self.images['R'] = pygame.image.load('images/missileR.gif')
        self.images['U'] = pygame.image.load('images/missileU.gif')
        self.images['D'] = pygame.image.load('images/missileD.gif')
        self.image = self.images[self.direction]  # 坦克的图片由方向决定
        self.rect = self.image.get_rect()
        self.rect.left = tank.rect.left+(tank.width-self.width)//2
        self.rect.top = tank.rect.top+(tank.width-self.width)//2

        self.live = True  # 存活与否！
        self.good=False


    def move(self):
        if self.live:
             if self.direction == 'L':
                 if self.rect.left > -10:  # 屏幕左边界
                     self.rect.left -= self.speed
                 else:
                     self.live=False
             elif self.direction == 'R':
                 if self.rect.right < TankMain.width:
                     self.rect.right += self.speed
                 else:
                     self.live = False
             elif self.direction == 'U':
                 if self.rect.top > -10:
                     self.rect.top -= self.speed
                 else:
                     self.live = False
             elif self.direction == 'D':
                 if self.rect.top < TankMain.height:
                     self.rect.top += self.speed
                 else:
                     self.live = False











if __name__=='__main__':
    game=TankMain()
    game.startGmae()


