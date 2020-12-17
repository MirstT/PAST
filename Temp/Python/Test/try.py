import  datetime as d
start_day=d.datetime.today()
std=start_day.strftime('%Y-%m-%d')
timedelta=d.timedelta(days=1)
end_day=start_day+timedelta*30
ed=end_day.strftime('%Y-%m-%d')

print(type(std))
print(ed)

