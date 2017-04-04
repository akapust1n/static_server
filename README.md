# Benchmark
Server for returning static files
## Server
```
 ab -n 100000 -c 100 127.0.0.1:80/httptest/wikipedia_russia.htm
This is ApacheBench, Version 2.3 <$Revision: 1706008 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking 127.0.0.1 (be patient)
Completed 10000 requests
Completed 20000 requests
Completed 30000 requests
Completed 40000 requests
Completed 50000 requests
Completed 60000 requests
Completed 70000 requests
Completed 80000 requests
Completed 90000 requests
Completed 100000 requests
Finished 100000 requests


Server Software:        WebServer/1.0
Server Hostname:        127.0.0.1
Server Port:            80

Document Path:          /httptest/wikipedia_russia.htm
Document Length:        85 bytes

Concurrency Level:      100
Time taken for tests:   5.769 seconds
Complete requests:      100000
Failed requests:        0
Non-2xx responses:      100000
Total transferred:      24300000 bytes
HTML transferred:       8500000 bytes
Requests per second:    17334.43 [#/sec] (mean)
Time per request:       5.769 [ms] (mean)
Time per request:       0.058 [ms] (mean, across all concurrent requests)
Transfer rate:          4113.54 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    3  36.0      1    1026
Processing:     0    3   2.2      3     212
Waiting:        0    2   2.2      2     211
Total:          2    6  36.1      4    1029

Percentage of the requests served within a certain time (ms)
  50%      4
  66%      5
  75%      6
  80%      6
  90%      6
  95%      7
  98%      7
  99%      8
 100%   1029 (longest request)
 ```
 ## nginx
 ```
 ab -n 100000 -c 100 127.0.0.1:80/httptest/wikipedia_russia.htm
This is ApacheBench, Version 2.3 <$Revision: 1706008 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking 127.0.0.1 (be patient)
Completed 10000 requests
Completed 20000 requests
Completed 30000 requests
Completed 40000 requests
Completed 50000 requests
Completed 60000 requests
Completed 70000 requests
Completed 80000 requests
Completed 90000 requests
Completed 100000 requests
Finished 100000 requests


Server Software:        nginx/1.10.1
Server Hostname:        127.0.0.1
Server Port:            80

Document Path:          /httptest/wikipedia_russia.htm
Document Length:        178 bytes

Concurrency Level:      100
Time taken for tests:   3.575 seconds
Complete requests:      100000
Failed requests:        0
Non-2xx responses:      100000
Total transferred:      33700000 bytes
HTML transferred:       17800000 bytes
Requests per second:    27974.76 [#/sec] (mean)
Time per request:       3.575 [ms] (mean)
Time per request:       0.036 [ms] (mean, across all concurrent requests)
Transfer rate:          9206.54 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    1   0.4      1       3
Processing:     1    2   0.5      2       6
Waiting:        0    2   0.5      2       5
Total:          2    4   0.6      3       8
WARNING: The median and mean for the total time are not within a normal deviation
        These results are probably not that reliable.

Percentage of the requests served within a certain time (ms)
  50%      3
  66%      4
  75%      4
  80%      4
  90%      5
  95%      5
  98%      5
  99%      5
 100%      8 (longest request)
```
