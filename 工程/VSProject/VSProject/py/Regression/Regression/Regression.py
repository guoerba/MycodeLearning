import tensorflow as tf  
import numpy as np  
import matplotlib.pyplot as plt   #A
import csv
import time

FilePath = './train.csv'
ColumnCount = 43
intlist = (1,2,3,4,6,8,10,12,15,17,19,21,22,23,25,27,29,34,36,40,42)
floatlist = (13,18,30,31,41)
timelist = (9,11,14,16,24,26,33,35)
timeduringlist = (20,28,32,37,38,39)
ytrain = 43


def input_data(file):
    date1 = "1970-1-2 "
    time1 = "00:00:00"
    time2 = "00:00"
    
    input = list()
    output = list()
    with open(file,'r') as csvfile:
        rows = list(csv.reader(csvfile))
        for i,row in enumerate(rows):
            if i != 0  :              
                #print(i,row)
                rowlist = list()
                for j,element in enumerate(row):

                    if j in intlist:
                        if len(element) == 0:
                            rowlist.append(int(0))
                        else:
                            rowlist.append(int(float(element)))
                    elif j in floatlist:
                        if len(element) == 0:
                            rowlist.append(float(0))
                        else:
                            rowlist.append(float(element))            
                    elif j in timelist:
                        if len(element) == 0:
                            rowlist.append(int(0))
                        else:
                            a = time.mktime(time.strptime(date1+time1,"%Y-%m-%d %H:%M:%S"))                     
                            b = time.mktime(time.strptime(date1+element,"%Y-%m-%d %H:%M:%S"))
                            rowlist.append(abs(b-a))
                    elif j in timeduringlist:
                        if len(element) == 0:
                           #rowlist.append((0,0))
                           rowlist.append(0)
                        else:
                            a = time.mktime(time.strptime(date1+time2,"%Y-%m-%d %H:%M"))
                            b = str(element).split('-')
                           # print(int(b[1].split(':')[0]))
                            if 24 == int(b[1].split(':')[0]):                           
                                b[1] = "23:59"
                            if 24 == int(b[0].split(':')[0]):
                                b[0] = "00:00"   
                            #print(int(b[1].split(':')[0]))
                            pre = time.mktime(time.strptime(date1+b[0],"%Y-%m-%d %H:%M"))
                            last = time.mktime(time.strptime(date1+b[1],"%Y-%m-%d %H:%M"))
                            #rowlist.append((pre - a,last - a))
                            rowlist.append(last - pre)
                    elif j == ytrain:
                        output.append(float(element))                        
                input.append(rowlist)
    #print(input)
    #print(np.array(input).shape)
    #print(np.array(output))
    #return np.array(input),np.array(output) 
    return input,output

def Inference(input,output):
    X = tf.placeholder(dtype=tf.float32,shape=[40,None],name='X')
    Y = tf.placeholder(dtype=tf.float32,name='Y')

    W1 = tf.Variable(tf.random_uniform((40,10),minval=-0.5,maxval=0.5,dtype=tf.float32),name='W1')
    b1 = tf.Variable(tf.zeros([10,1],dtype=tf.float32),name='b1')
    W2 = tf.Variable(tf.random_uniform((10,8),minval=-0.5,maxval=0.5,dtype=tf.float32),name='W2')
    b2 = tf.Variable(tf.zeros([8,1],dtype=tf.float32),name='b2')
    W3 = tf.Variable(tf.random_uniform((8,6),minval=-0.5,maxval=0.5,dtype=tf.float32),name='W3')
    b3 = tf.Variable(tf.zeros([6,1],dtype=tf.float32),name='b3')
    W4 = tf.Variable(tf.random_uniform((6,4),minval=-0.5,maxval=0.5,dtype=tf.float32),name='W4')
    b4 = tf.Variable(tf.zeros([4,1],dtype=tf.float32),name='b4')
    W5 = tf.Variable(tf.random_uniform((4,1),minval=-0.5,maxval=0.5,dtype=tf.float32),name='W5')
    b5 = tf.Variable(tf.zeros([1,1],dtype=tf.float32),name='b5')

    Z1 = tf.add(tf.matmul(tf.transpose(W1,perm=[1,0]),X),b1)
    A1 = tf.nn.relu(Z1)
    Z2 = tf.add(tf.matmul(tf.transpose(W2,perm=[1,0]),A1),b2)
    A2 = tf.nn.relu(Z2)
    Z3 = tf.add(tf.matmul(tf.transpose(W3,perm=[1,0]),A2),b3)
    A3 = tf.nn.relu(Z3)
    Z4 = tf.add(tf.matmul(tf.transpose(W4,perm=[1,0]),A3),b4)
    A4 = tf.nn.relu(Z4)
    Z5 = tf.add(tf.matmul(tf.transpose(W5,perm=[1,0]),A4),b5)
    prediction = tf.nn.sigmoid(Z5)

    print(str("The type of Z5 is:{0}").format(type(prediction)))

    optimizier = tf.reduce_mean(tf.square(prediction-Y))
    print(str("The type of optimizier is:{0}").format(type(optimizier)))

    train_op = tf.train.GradientDescentOptimizer(0.001).minimize(optimizier)
    print(str("The type of train_op is:{0}").format(type(train_op)))
   
    with tf.Session() as sess:
        sess.run(tf.global_variables_initializer())
        for step in range(100):
            for x,y in zip(input,output):                  
                sess.run(fetches=train_op,feed_dict={X:np.array(x).reshape([40,1]),Y:y})                             
            if step % 10 == 0:
                print(str("epoch{0}").format(step))
                print(str("W1:{0}\nW2:{1}\nW3:{2}\nW4:{3}\nW5:{4}\nb1:{5}\nb2:{6}\nb3:{7}\nb4:{8}\nb5:{9}\n").format(sess.run(W1),
                                                                                                                     sess.run(W2),
                                                                                                                     sess.run(W3),
                                                                                                                     sess.run(W4),
                                                                                                                     sess.run(W5),
                                                                                                                     sess.run(b1),
                                                                                                                     sess.run(b2),
                                                                                                                     sess.run(b3),
                                                                                                                     sess.run(b4),
                                                                                                                     sess.run(b5)
                                                                                                                     ))
                print(sess.run([prediction,optimizier],feed_dict={X:np.array(x).reshape([40,1]),Y:y}))                          
                #print(str("[prediction,loss]:{0}").format(sess.run([prediction,optimizier],feed_dict={X:np.array(x).reshape([40,1]),Y:y})))

    #return Z5            

def Inference2(input,output):
    X = tf.placeholder(dtype=tf.float32,shape=[40,None],name='X')
    Y = tf.placeholder(dtype=tf.float32,name='Y')

    W1 = tf.Variable(tf.random_uniform((40,10),minval=-0.5,maxval=0.5,dtype=tf.float32),name='W1')
    b1 = tf.Variable(tf.random_uniform([10,1],dtype=tf.float32),name='b1')
    W2 = tf.Variable(tf.random_uniform((10,1),minval=-0.5,maxval=0.5,dtype=tf.float32),name='W2')
    b2 = tf.Variable(tf.random_uniform([1,1],dtype=tf.float32),name='b2')    

    Z1 = tf.add(tf.matmul(tf.transpose(W1,perm=[1,0]),X),b1)
    A1 = tf.nn.relu(Z1)
    Z2 = tf.add(tf.matmul(tf.transpose(W2,perm=[1,0]),A1),b2)
    prediction = tf.nn.sigmoid(Z2)

    print(str("The type of Z5 is:{0}").format(type(prediction)))

    optimizier = tf.reduce_mean(tf.square(prediction-Y))
    print(str("The type of optimizier is:{0}").format(type(optimizier)))

    train_op = tf.train.GradientDescentOptimizer(0.001).minimize(optimizier)
    print(str("The type of train_op is:{0}").format(type(train_op)))
   
    with tf.Session() as sess:
        sess.run(tf.global_variables_initializer())
        for step in range(100):
            for x,y in zip(input,output):      
                _,loss = sess.run(fetches=[train_op,optimizier],feed_dict={X:np.array(x).reshape([40,1]),Y:y})             
                #print(str("loss:{0}").format(loss))
            pred = sess.run(prediction,feed_dict={X:np.array(input[0]).reshape([40,1])})
            print(str("epoch:{0},pred: {1}").format(step,pred))
            #if step % 10 == 0:
                #print(str("epoch{0}").format(step))
                #print(str("W1:{0}\nW2:{1}\nb1:{2}\nb2:{3}").format(sess.run(W1),sess.run(W2),sess.run(b1),sess.run(b2)))                                                                                                                                                                                                                                                                                                                                      
                                                                                                                     
                #print(sess.run([prediction,optimizier],feed_dict={X:np.array(x).reshape([40,1]),Y:y}))
                #print(str("[prediction,loss]:{0}").format(sess.run([prediction,optimizier],feed_dict={X:np.array(x).reshape([40,1]),Y:y})))


def Loss(Z:tf.Tensor,Y):
    return tf.reduce_mean(tf.square(Z-Y))

def Train(loss,rate,times,input:list,output:list):
    train_op = tf.train.GradientDescentOptimizer(rate).minimize(loss)

    with tf.Session() as sess:
        sess.run(tf.initialize_all_variables())
        for step in range(times):
            for i,x in enumerate(input):
                print(sess.run(train_op,feed_dict={X:x,Y:output}))

if __name__ == '__main__':
    #d.DataInput(FilePath)
    input,output = input_data(FilePath)
    Inference2(input,output)
    #Y = Inference(tf.Variable(tf.zeros([42,1],dtype=tf.float32),name='X'))
    #loss = Loss(Y,tf.Variable(tf.zeros([1,1],dtype=tf.float32),name='Y'))
    #Train(loss,0.1,1000,input,output)


def model(X, w):  #E    
     return tf.multiply(X, w)

def old():
    learning_rate = 0.01  #B
    training_epochs = 100  #B

    x_train = np.linspace(-1, 1, 101)  #C
    print("x_train type: %s" % type(x_train))
    y_train = 2 * x_train + np.random.randn(*x_train.shape) * 0.33  #C
    print("y_train type: %s" % type(y_train))

    X = tf.placeholder("float")  #D
    Y = tf.placeholder("float")  #D
    print("X type: %s" % type(X))
    print("Y type: %s" % type(Y))

    w = tf.Variable(0.0, name="weights")  #F
    print("y_train type: %s" % type(y_train))

    y_model = model(X, w)  #G
    cost = tf.square(Y-y_model)  #G

    train_op = tf.train.GradientDescentOptimizer(learning_rate).minimize(cost)  #H
    print("train_op type: %s" % type(train_op))

    sess = tf.Session()  #I
    init = tf.global_variables_initializer()  #I
    sess.run(init)  #I
    for epoch in range(training_epochs):  #J   
        for (x, y) in zip(x_train, y_train):  #K
            sess.run(train_op, feed_dict={X: x, Y: y})  #L

    w_val = sess.run(w)  #M

    sess.close() #N
    plt.scatter(x_train, y_train)  #O
    y_learned = x_train*w_val  #P
    plt.plot(x_train, y_learned, 'r')  #P
    plt.show()  #P

#A：载入 TensorFlow 包用于学习算法，载入 NumPy 包来设置初始数据，载入 matplotlib 包来可视化数据

#B：定义学习算法使用的一些常数，称为超参数

#C：初始化线性模拟数据

#D：将输入和输出节点设置为占位符，而真实数值将传入 x_train 和 y_train

#E：将模型定义为 y=w*x

#F：设置权重变量

#G：定义成本函数

#H：定义在学习算法的每次迭代中将被调用的操作

#I：设置会话并初始化所有变量

#J：多次循环遍历数据集

#K：循环遍历数据集中的每个数据

#L：更新模型参数以尝试最小化成本函数

#M：得到最终参数值

#N：关闭会话

#O：绘制原始数据

#P：绘制最佳拟合直线