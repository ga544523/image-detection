Most of my ideas reference from J. R. R. Uijlings et al., Selective Search for Object Recognition, IJCV, 2013


To do optimization
1.neighboring region preprocess
2.remove from main function


deer.png
segment parameter
k=50
minsize 2000
GaussianBlur 3x3 sigma 1

detection parameter
minsize 20000
maxsize (height*width)/2)
random 1000
output region 25


![image](https://github.com/ga544523/image-detection/blob/master/detection1.PNG?raw=true)


lena.png
segment parameter
k=50
minsize 1000
GaussianBlur 3x3 sigma 1


detection parameter
minsize 500
maxsize (height*width)/2)
random 1000
output region 10


![image](https://github.com/ga544523/image-detection/blob/master/detection2.PNG?raw=true)


pa.png
segment parameter
k=50
minsize 2000
GaussianBlur 3x3 sigma 1



detection parameter
minsize 500
maxsize (height*width)/2)
random 1000
output region 15


![image](https://github.com/ga544523/image-detection/blob/master/detection3.PNG?raw=true)

touhou.png

segment parameter k=50 minsize 1000 GaussianBlur 3x3 sigma 1
detection parameter 
minsize 2000 
maxsize (height*width)/2)
random 10 
output region 10


![image](https://github.com/ga544523/image-detection/blob/master/detection4.PNG?raw=true)
