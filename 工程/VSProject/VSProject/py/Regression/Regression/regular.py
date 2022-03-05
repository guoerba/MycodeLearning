import numpy as np
from matplotlib import pyplot as plt
from matplotlib import axes as axe

if __name__ == '__main__':
    pnum = 100
    xtimes = 10
    ytimes = 5

    fig = plt.figure()

    axisX = np.array([np.linspace(-xtimes,xtimes,xtimes,dtype='int64'),np.zeros((xtimes,),dtype='int64')])
    axisY = np.array([np.zeros((ytimes,),dtype='int64'),np.linspace(-ytimes,ytimes,ytimes,dtype='int64')])

    x = xtimes * np.random.random(pnum)
    y = ytimes * np.random.random(pnum)

    axes = fig.add_subplot(221)
    axes.scatter(x,y,color='red')
    plt.plot(axisX[0],axisX[1],color='blue')
    plt.plot(axisY[0],axisY[1],color='blue')

    plt.title("initial points set")

    ux = x.sum()/pnum
    uy = y.sum()/pnum
    ux = x - ux
    uy = y - uy

    plt.subplot(222)
    plt.plot(ux,uy,"ob",color='red')
    plt.plot(axisX[0],axisX[1],color='blue')
    plt.plot(axisY[0],axisY[1],color='blue')
    plt.title("after divde the even")

    nx = x**2
    ny = y**2
    ox = nx.sum()/pnum
    oy = ny.sum()/pnum
    ox = ux/ox
    oy = uy/oy

    plt.subplot(223)
    plt.plot(ox,oy,"ob",color='red')
    plt.plot(axisX[0],axisX[1],color='blue')
    plt.plot(axisY[0],axisY[1],color='blue')
    plt.xlim(ox.min() - 1,ox.max() + 1)
    plt.ylim(oy.min() - 1,oy.max() + 1)
    plt.title("after regular")
    
    plt.show()
