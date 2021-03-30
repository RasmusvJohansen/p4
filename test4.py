import numpy as np


testarray = np.zeros([2, 2, 3], dtype=np.uint8) #x,y,farver
testarray = [[255,2,3],[1,2,3],[1,2,3],[1,2,3]]

def binary(num):
    array = []

    #makes the binary value
    while(num > 0):
        sol1 = num / 2

        check = sol1 - int(sol1)

        if(check > 0):
            array.append("1")
            num = sol1 - 0.5
        else:
            array.append("0")
            num = sol1
            
    #makes sure the binary value is a minimum of 8 bits long
    while(len(array) < 8):
        array.append("0")

    #reverses the array
    array = array[::-1]

    #joins the array into a string, return the string
    string = ''.join(array)

    return string

#print(binary(testarray[1,1]))


for x in range(len(testarray[0])):
    a = testarray[0][x]
    b = binary(a)
    c = list(b)
    print(c)
    #print(list(str(binary(a))))

    #print(c[1])


