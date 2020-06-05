import self as self
from sklearn import datasets
import scipy
from scipy.spatial import ConvexHull, convex_hull_plot_2d
from sklearn.cluster import AgglomerativeClustering
from sklearn.cluster import KMeans
from sklearn.mixture import GaussianMixture
from sklearn.metrics import jaccard_score, mean_squared_error
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt
from scipy.stats import mode
import scipy.cluster.hierarchy as hr
import numpy as np

iris = datasets.load_iris()
X = iris.data
Y = iris.target


def find_perm(clusters, Y_real, Y_pred):
    perm = []
    for i in range(clusters):
        idx = Y_pred == i
        # print('!!!!', Y_real[idx])
        new_label = mode(Y_real[idx])[0][0]
        perm.append(new_label)
    return [perm[label] for label in Y_pred]


# Single Linkage
# The distance between two clusters is the shortest distance between two points in each cluster
cluster_single = AgglomerativeClustering(n_clusters=3, linkage='single').fit(X)

# Average Linkage
# The distance between clusters is the average distance between each point in one cluster
# to every point in other cluster
cluster_avg = AgglomerativeClustering(n_clusters=3, linkage='average').fit(X)

# Complete Linkage
# The distance between two clusters is the longest distance between two points in each cluster
cluster_cmp = AgglomerativeClustering(n_clusters=3, linkage='complete').fit(X)

# Ward Linkage
# The distance between clusters is the sum of squared differences within all clusters
cluster_ward = AgglomerativeClustering(n_clusters=3, linkage='ward').fit(X)

print(X)
print(Y)
print(cluster_single.labels_)
print(cluster_avg.labels_)
print(cluster_cmp.labels_)
print(cluster_ward.labels_)

print('\n', np.array(find_perm(3, Y, cluster_single.labels_)))
# funckja sprawdza dla kazdego klastra w Y_pred jakie mu odpowiadaja etykiety w Y_real, po czym
# znajduję tą która jest najczęstsza i zastepuje nią wszystkie w Y_pred
# po zakończeniu rozkład pozostaje taki sam ale probki zostaja przydzielone to wlasciwych klastrow


# Współczynnik Jaccarda mierzy podobieństwo między dwoma zbiorami i jest zdefiniowany
# jako iloraz mocy części wspólnej zbiorów i mocy sumy tych zbiorów:
#
#     J ( A , B ) = | A ∩ B | | A ∪ B |
#
# Wartości przyjmowane przez współczynnik Jaccarda zawierają się w podzbiorze zbioru liczb
# rzeczywistych <0,1>. Jeśli współczynnik Jaccarda przyjmuje wartości bliskie zeru,
# zbiory są od siebie różne, natomiast gdy jest bliski 1, zbiory są do siebie podobne.

print(jaccard_score(cluster_cmp.labels_, Y, average='micro'))



def plot_PCA(data, labels, name):
    _pca = PCA(n_components=2)
    _X_reduced = _pca.fit_transform(data)
    _fig = plt.figure(figsize=(16, 8))
    _ax = _fig.add_subplot(1, 2, 1)
    _ax.set_title(name, fontsize=20)
    _ax2 = _fig.add_subplot(1, 2, 2, projection='3d')

    targets = [0, 1, 2]
    colors = ['r', 'g', 'b']
    for target, color in zip(targets, colors):
        idx = labels == target
        group = _X_reduced[idx]
        grp2 = data[idx]
        _ax.scatter(group[:, 0], group[:, 1], c=color, s=50)
        _ax2.scatter3D(grp2[:, 0], grp2[:, 1], grp2[:, 2], c=color)
        hull = ConvexHull(group)
        for simplex in hull.simplices:
            _ax.plot(group[simplex, 0], group[simplex, 1], 'k-')
    _ax.grid()
    plt.show()


complete_labels = np.array(find_perm(3, Y, cluster_cmp.labels_))
plot_PCA(X, Y, 'Oryginał')
plot_PCA(X, complete_labels, 'Complete')

fig = plt.figure(figsize=(16, 8))
ax = fig.add_subplot(1, 2, 1)
ax2 = fig.add_subplot(1, 2, 2, projection='3d')
ax.set_title("Różnice", fontsize=20)
diff = Y == complete_labels

pca = PCA(n_components=2)
X_reduced = pca.fit_transform(X)
for i, point in enumerate(X_reduced):
    if not diff[i]:
        ax.plot(point[0], point[1], 'ro')
        ax2.scatter3D(X[i, 0], X[i, 1], X[i, 2], c="red")
    else:
        ax.plot(point[0], point[1], 'go')
        ax2.scatter3D(X[i, 0], X[i, 1], X[i, 2], c="green")
ax.grid()
plt.show()
plt.show()

Z = hr.linkage(X, method='complete')
hr.dendrogram(Z)
plt.show()

# 3
from PIL import Image
# Open the image form working directory
image = Image.open('cat.jpg')
im_data = np.asarray(image)
size = image.size
print(size)
im_data = np.reshape(im_data, (size[0]*size[1], 3))
image.show()

# c_sizes = [2, 3, 5, 10, 30, 100]
c_sizes = [5, 3, 2]
for s in c_sizes:
    cluster_KMeans = KMeans(n_clusters=s, init='random').fit(im_data)
    centers = cluster_KMeans.cluster_centers_
    labels = cluster_KMeans.labels_
    data2 = im_data.copy()
    for i in range(s-1):
        for j in range(size[0]*size[1]):
            if i == labels[j]:
                data2[j] = centers[i]
    error = []
    for i in range(size[0]*size[1]):
        error.append(mean_squared_error(im_data[i], data2[i]))
    error = np.array(error).reshape((size[1], size[0]))
    data2 = np.reshape(data2, (size[1], size[0], 3))
    image2 = Image.fromarray(data2)
    image2.show()
    image3 = Image.fromarray(error)
    image3.show()
    # cluster_AC = AgglomerativeClustering(n_clusters=s, linkage='single').fit(im_data)
