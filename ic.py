import cv2

img = cv2.imread('Z:\sem 6\CG Lab\images\girl.jpg',0)

cv2.imshow('image',img)
cv2.waitKey(0)
cv2.destroyAllWindows()

r = img.shape[0]
c = img.shape[1]


for i in range(r):
    for j in range(c):
        img[i][j] = 255 - img[i][j]
        
        
cv2.imshow('image',img)
cv2.waitKey(0)
cv2.destroyAllWindows()

            
    
