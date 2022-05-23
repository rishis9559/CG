import cv2

img = cv2.imread(r"S:\\STUDY\\6th SEM\\CG\\CG-surya\\Python\\IMG_f3gceg.jpg")

cv2.imshow('image',img)
cv2.waitKey(0)
cv2.destroyAllWindows()

im_bw = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU )[1]

cv2.imshow('image',im_bw)
cv2.waitKey(0)
cv2.destroyAllWindows()
