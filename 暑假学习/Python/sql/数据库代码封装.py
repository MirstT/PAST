# coding=gbk
import pymysql


class MysqlHelper(object):
    config = {
        "host": "127.0.0.1",
        "user": "root",
        "password": "20180114",
        "db": "test1",
        "charset": "utf8"
    }

    def __init__(self):
        self.connection = None
        self.cursor = None

    def getOne(self, sql, *args):
        try:
            self.connection = pymysql.connect(**MysqlHelper.config)
            self.cursor = self.connection.cursor()
            self.cursor.execute(sql, args)
            return self.cursor.fetchone()
        except Exception as ex:
            print(ex, ex)
        finally:
            self.close()

    def getAll(self, sql, *args):
        try:
            self.connection = pymysql.connect(**MysqlHelper.config)
            self.cursor = self.connection.cursor()
            self.cursor.execute(sql, args)
            return self.cursor.fetchall()
        except Exception as ex:
            print(ex, ex)
        finally:
            self.close()

    def executeDML(self, sql, *args):
        try:
            self.connection = pymysql.connect(**MysqlHelper.config)
            self.cursor = self.connection.cursor()
            info = self.cursor.execute(sql, args)
            self.connection.commit()
            return info
        except Exception as ex:
            self.connection.rollback()
            print(ex, ex)
        finally:
            self.close()

    def close(self):
        if self.cursor:
            self.cursor.close()
        if self.connection:
            self.connection.close()


if __name__ == '__main__':
    helper = MysqlHelper()
    print(helper.executeDML('delete from t_students where id = %s', 2))
