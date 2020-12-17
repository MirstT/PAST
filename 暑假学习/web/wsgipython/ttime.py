import  time

def say_time():
    return  time.ctime()
def fun_a():
    pass
def application(env,start_response):
    status="200 OK"
    headers=[
        ("Content-Type","text/plain")
    ]
    start_response(status,headers)
    return time.ctime()
