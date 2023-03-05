import requests
import time
import polling
import queue



#https://github.com/justiniso/polling 
def test(response):
    global status_code
    status_code = response.status_code
    return response.status_code == 200

my_queue = queue.Queue()

result = polling.poll(lambda: requests.get('http://google.com'), 
                      step=60, 
                      poll_forever=True, 
                      check_success=test,
                      collect_value=my_queue)



while True:
    if my_queue.empty():
        print("empty {}".format(status_code))
    else:
        print("{} {}".format(my_queue.get()), status_code)
    time.sleep(300)  # Sleep for 5 minutes
