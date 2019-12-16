# -*- coding: utf-8 -*-
# @Author: MarkJiYuan
# @Date:   2019-11-12 20:45:02
# @Last Modified by:   MarkJiYuan
# @email: zhengjiy16@163.com
# @Last Modified time: 2019-11-16 09:31:09
# @Abstract: 

def isSym(l):
    center = int(len(l)/2)
    if center == 0:
        return False
    i = 0
    while i <= center:
        if l[i] != l[-(i+1)]:
            return False
        i += 1
    return True

l = [1,2,3,2,1]
print(isSym(l))