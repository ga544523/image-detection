It's a straightforward algorithm of object detection,and most of my ideas are referenced from [J. R. R. Uijlings et al., Selective Search for Object Recognition, IJCV, 2013](https://ivi.fnwi.uva.nl/isis/publications/bibtexbrowser.php?key=UijlingsIJCV2013&bib=all.bib).To run this program,all you need to do is to install opencv c++ and then download the whole project.



To do optimization


1.neighboring region preprocess


2.remove from main function

=======================================================================================
deer.png
segment parameters
k=50
minsize 2000
GaussianBlur 3x3 sigma 1

detection parameters
minsize 20000
maxsize (height*width)/2)
random 1000
output region 15


![image](https://github.com/ga544523/image-detection/blob/master/detection1.PNG?raw=true)


lena.png
segment parameters
k=50
minsize 1000
GaussianBlur 3x3 sigma 1


detection parameters
minsize 500
maxsize (height*width)/2)
random 1000
output region 10


![image](https://github.com/ga544523/image-detection/blob/master/detection2.PNG?raw=true)


touhou.png

segment parameters
k=50 minsize 1000 GaussianBlur 3x3 sigma 1


detection parameter s
minsize 2000 
maxsize (height*width)/2)
random 10 
output region 15


![image](https://github.com/ga544523/image-detection/blob/master/detection5.PNG?raw=true)
