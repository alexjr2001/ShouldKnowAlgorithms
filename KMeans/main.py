import math
import numpy as np
import Cluster as cl 
import pdb
import matplotlib.pyplot as plt

fig = plt.figure()
ax1 = fig.add_subplot(121)
ax2 = fig.add_subplot(122)

dim = 2
n_points = 200
points = np.random.randint(1,200,size=(n_points,dim))

print('Points',points)
x, y = points.T
ax1.scatter(x,y)


def get_cmap(n, name='hsv'):
    '''Returns a function that maps each index in 0, 1, ..., n-1 to a distinct 
    RGB color; the keyword argument name must be a standard mpl colormap name.'''
    return plt.cm.get_cmap(name, n)

def distance(point,cluster):
    dist = 0
    for i in range(dim):
        dist+= (point[i]-cluster[i])**2
    dist = math.sqrt(dist)
    return dist

def kMeans(n_clusters,points):
    center_clusters = np.random.randint(1,200,size=(n_clusters,dim))
    clusters=[]
    x1, y1 = center_clusters.T
    ax1.scatter(x1,y1, color = 'hotpink')

    #print("Clusters")
    for i in center_clusters:
        #print(i)
        clusters.append(cl.Cluster(i))
    change = True
    while change:
        for i in range(len(points)):
            nearest = [float('inf'),-1] #[distance,#cluster]
            for j in range(n_clusters):
                current_distance = distance(points[i],clusters[j].pos)
                if current_distance<nearest[0]:
                    nearest = [current_distance,j]
            currentPoint = points[i].reshape(1, 2)
            #print(currentPoint)
            #print(clusters[nearest[1]].group)
            clusters[nearest[1]].group=np.append(clusters[nearest[1]].group,currentPoint,axis=0)

        change = False
        for i in range(n_clusters):
            if clusters[i].group.size > 0:
                temp=clusters[i].pos
                #print("Grupo", clusters[i].group)
                #print("Promedio",clusters[i].group.mean(axis=0))
                #print("Anterior",temp)
                clusters[i].pos=clusters[i].group.mean(axis=0)
                if (temp!=clusters[i].pos).all():
                    change=True
                    clusters[i].group=np.empty((0,2), int)
    

    cmap = get_cmap(n_clusters)
    for i in range(n_clusters):
        x, y = clusters[i].pos.T
        ax2.scatter(x,y, color = 'black')
        x, y = clusters[i].group.T
        ax2.scatter(x,y, color = cmap(i))
    
    #x1, y1 = clusters[0].pos.T
    #ax2.scatter(x1,y1, color = 'black')
    #x2, y2 = clusters[1].pos.T
    #ax2.scatter(x2,y2, color = 'black')
    #x3, y3 = clusters[0].group.T
    #ax2.scatter(x3,y3, color = 'lime')
    #x4, y4 = clusters[1].group.T
    #ax2.scatter(x4,y4, color = 'orange')
    plt.show()


kMeans(5,points)
