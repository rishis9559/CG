import cv2
from matplotlib import pyplot as plt

img = cv2.imread('Z:\sem 6\CG Lab\images\girl.jpg',0)

cv2.imshow('original image',img)
cv2.waitKey(0)

plt.hist(img.ravel(),256,[0,256]) 
plt.show()

equ = cv2.equalizeHist(img)
cv2.imshow('histo equlaised image',equ)
cv2.waitKey(0)

plt.hist(equ.ravel(),256,[0,256]) 
plt.show()
