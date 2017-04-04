# Benchmark
Server for returning static files
* [404](#404)
* [html](#page-html)
* [403](#403)
## 404
### Server
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
 ### nginx
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
## Page html
### Server
```
ab -n 100000 -c 4 localhost/httptest/wikipedia_russia.html
This is ApacheBench, Version 2.3 <$Revision: 1706008 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking localhost (be patient)
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
Server Hostname:        localhost
Server Port:            80

Document Path:          /httptest/wikipedia_russia.html
Document Length:        954824 bytes

Concurrency Level:      4
Time taken for tests:   98.358 seconds
Complete requests:      100000
Failed requests:        0
Total transferred:      95497900000 bytes
HTML transferred:       95482400000 bytes
Requests per second:    1016.70 [#/sec] (mean)
Time per request:       3.934 [ms] (mean)
Time per request:       0.984 [ms] (mean, across all concurrent requests)
Transfer rate:          948168.09 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.3      0      11
Processing:     1    4   2.2      3      73
Waiting:        0    1   1.0      0      62
Total:          1    4   2.3      3      73
WARNING: The median and mean for the waiting time are not within a normal deviation
        These results are probably not that reliable.

Percentage of the requests served within a certain time (ms)
  50%      3
  66%      4
  75%      5
  80%      5
  90%      6
  95%      7
  98%     10
  99%     12
 100%     73 (longest request)
```
### nginx
```
ab -n 100000 -c 4 localhost/httptest/wikipedia_russia.html
This is ApacheBench, Version 2.3 <$Revision: 1706008 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking localhost (be patient)
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
Server Hostname:        localhost
Server Port:            80

Document Path:          /httptest/wikipedia_russia.html
Document Length:        954824 bytes

Concurrency Level:      4
Time taken for tests:   41.853 seconds
Complete requests:      100000
Failed requests:        0
Total transferred:      95507100000 bytes
HTML transferred:       95482400000 bytes
Requests per second:    2389.32 [#/sec] (mean)
Time per request:       1.674 [ms] (mean)
Time per request:       0.419 [ms] (mean, across all concurrent requests)
Transfer rate:          2228482.20 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.1      0      19
Processing:     0    2   0.9      1      48
Waiting:        0    0   0.4      0      38
Total:          0    2   0.9      1      48
WARNING: The median and mean for the processing time are not within a normal deviation
        These results are probably not that reliable.
WARNING: The median and mean for the total time are not within a normal deviation
        These results are probably not that reliable.

Percentage of the requests served within a certain time (ms)
  50%      1
  66%      2
  75%      2
  80%      2
  90%      2
  95%      3
  98%      4
  99%      5
 100%     48 (longest request)
```
## 403
### Server 
```
alexey@alexey-GE60-2PL:~/park/3sem/highload/static_server/build-untitled-Desktop_Qt_5_8_0_GCC_64bit-Release$ ab -n 50000 -c 100 localhost/
This is ApacheBench, Version 2.3 <$Revision: 1706008 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking localhost (be patient)
Completed 5000 requests
Completed 10000 requests
Completed 15000 requests
Completed 20000 requests
Completed 25000 requests
Completed 30000 requests
Completed 35000 requests
Completed 40000 requests
Completed 45000 requests
Completed 50000 requests
Finished 50000 requests


Server Software:        WebServer/1.0
Server Hostname:        localhost
Server Port:            80

Document Path:          /
Document Length:        85 bytes

Concurrency Level:      100
Time taken for tests:   2.617 seconds
Complete requests:      50000
Failed requests:        0
Non-2xx responses:      50000
Total transferred:      12150000 bytes
HTML transferred:       4250000 bytes
Requests per second:    19109.48 [#/sec] (mean)
Time per request:       5.233 [ms] (mean)
Time per request:       0.052 [ms] (mean, across all concurrent requests)
Transfer rate:          4534.77 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    3  43.9      1    1025
Processing:     0    2   2.5      2     205
Waiting:        0    2   2.5      1     205
Total:          1    5  44.1      3    1030

Percentage of the requests served within a certain time (ms)
  50%      3
  66%      3
  75%      3
  80%      5
  90%      5
  95%      6
  98%      7
  99%      7
 100%   1030 (longest request)
```
###nginx
```ab -n 50000 -c 100 localhost/
This is ApacheBench, Version 2.3 <$Revision: 1706008 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking localhost (be patient)
Completed 5000 requests
Completed 10000 requests
Completed 15000 requests
Completed 20000 requests
Completed 25000 requests
Completed 30000 requests
Completed 35000 requests
Completed 40000 requests
Completed 45000 requests
Completed 50000 requests
Finished 50000 requests


Server Software:        nginx/1.10.1
Server Hostname:        localhost
Server Port:            80

Document Path:          /
Document Length:        170 bytes

Concurrency Level:      100
Time taken for tests:   2.022 seconds
Complete requests:      50000
Failed requests:        0
Non-2xx responses:      50000
Total transferred:      17600000 bytes
HTML transferred:       8500000 bytes
Requests per second:    24728.29 [#/sec] (mean)
Time per request:       4.044 [ms] (mean)
Time per request:       0.040 [ms] (mean, across all concurrent requests)
Transfer rate:          8500.35 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    1   0.7      1       3
Processing:     1    3   2.5      3      57
Waiting:        0    2   2.6      2      57
Total:          2    4   2.5      4      58

Percentage of the requests served within a certain time (ms)
  50%      4
  66%      4
  75%      5
  80%      5
  90%      5
  95%      5
  98%      6
  99%      6
 100%     58 (longest request)
```

