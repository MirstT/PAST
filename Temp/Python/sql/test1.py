import pymysql
import datetime
import time

connection = None
cursor = None
try:
    connection = pymysql.connect("127.0.0.1", "root", "20180114", "test1")

    cursor = connection.cursor()

    # sql = 'select * from t_students'
    # sql = 'insert into t_students values (0,"tt","hangzhou",0)'
    # sql = 'insert into t_students values (%s,"%s","%s",%s)' % (0, 'ff', 'gg', 1)
    sql = 'insert into t_students values (0,%s,%s,%s)'

    try:
        cursor.execute(sql,('name','bb',0))
        connection.commit()
    except Exception as ex:
        connection.rollback()
        print(ex)

except Exception as ex:
    print(ex)
finally:
    if cursor:
        cursor.close()
    if connection:
        connection.close()
