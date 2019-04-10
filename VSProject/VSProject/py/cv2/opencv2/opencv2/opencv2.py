import numpy as np
import cv2 as cv
import sys
import os

def Translate(img,dx,dy):
    rows = img.shape[0]
    cols = img.shape[1]
    M = np.float32([[1,0,dx],[0,1,dy]])
    return cv.warpAffine(img,M,(rows,cols))

def CenterRotate(img,angle):
    rows = img.shape[0]
    cols = img.shape[1]
    M = cv.getRotationMatrix2D(((rows-1)/2,(cols-1)/2),angle,1)
    return cv.warpAffine(img,M,(rows,cols))

def drawPoint(x:int,y:int,img):
    cv.circle(img,(x,y),63,(255,0,0))

if __name__ == '__main__':
    print('?')
    img = cv.imread("G:\VSProject\py\cv2\opencv2\pic.png",cv.IMREAD_COLOR)

    #img = cv.resize(img,(720,1440))
    if img is None:
        print('No image found!!!')
    else:
        #cv.imwrite("G:\VSProject\py\cv2\opencv2\plate.png",img)
        print(type(img),img.dtype,img.shape)
        print(int(img.shape[0]/2 - 1),int(img.shape[1]/2 - 1))
        #print(list(img))

        nimg = CenterRotate(img,180)
        #nimg = Translate(img,img.shape[0]/2,0)
        #drawPoint(int(nimg.shape[0]/4),int(nimg.shape[1]/2 - 1),nimg)
        #cv.namedWindow('showimage')
        cv.imshow('img',nimg)
       # cv.imshow('img',img)
        cv.waitKey(0)
        cv.destroyAllWindows()
    


