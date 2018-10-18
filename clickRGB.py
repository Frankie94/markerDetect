#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Oct 16 20:05:49 2018

@author: fangkai
"""

import cv2
from sys import argv

#fileNAME = argv[1]
print(argv[1])

img = cv2.imread(argv[1])
# mouse callback function
def draw_circle(event,x,y,flags,param):
    if event == cv2.EVENT_LBUTTONDOWN:
        bgr_val = img[y,x]
        cv2.putText(img, str(bgr_val), (x, y), cv2.FONT_HERSHEY_PLAIN, 1, (0,255,0), 1, cv2.LINE_AA)

# Create a window and bind the function to window

cv2.namedWindow('image')
cv2.setMouseCallback('image',draw_circle)

while(1):
    cv2.imshow('image',img)
    if cv2.waitKey(20) & 0xFF == 27:
        break
cv2.destroyAllWindows()
