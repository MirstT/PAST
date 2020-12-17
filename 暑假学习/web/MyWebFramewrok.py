import time
# from MyWebServer import HTTPServer

HTML_ROOT_DIR = './html'


class Application(object):
    """"""

    def __init__(self, urls):
        self.urls = urls

    def __call__(self, env, start_response):
        path = env.get("PATH_INFO", "/")
        if path.startswith("/static"):
            file_name = path[7:]
            try:
                file = open(HTML_ROOT_DIR + file_name, "rb")
            except IOError:
                status = "404 Not Found"
                headers = []
                start_response(status, headers)
                return "not found"
            else:
                file_data = file.read()
                file.close()

                status = "200 OK"
                headers = []
                start_response(status, headers)
                return file_data.decode("utf-8")

        for url, handler in self.urls:
            if path == url:
                return handler(env, start_response)

        status = "404 Not Found"
        headers = []
        start_response(status, headers)
        return "not found"


def show_ttime(env, start_response):
    status = "200 OK"
    headers = [
        ("Content-Type", "text/plain")
    ]
    start_response(status, headers)
    return time.ctime()


def say_hello(env, start_response):
    status = "200 OK"
    headers = [
        ("Content-Type", "text/plain")
    ]
    start_response(status, headers)
    return "hello haha"



urls = [
    ("/", show_ttime),
    ("/ttime", show_ttime),
    ("/sayhello", say_hello)
]
app = Application(urls)
#     http_server = HTTPServer(app)
#     http_server.bind(8000)
#     http_server.start()
