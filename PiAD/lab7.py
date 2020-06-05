from sklearn import datasets
from scipy.spatial import ConvexHull, convex_hull_plot_2d
from sklearn.cluster import AgglomerativeClustering
from sklearn.metrics import jaccard_score
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt
from scipy.stats import mode
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

pca = PCA(n_components=2)
X_reduced = pca.fit_transform(X)


def plot_PCA_2D(_pca, labels, name):
    fig = plt.figure(figsize=(8, 8))
    ax = fig.add_subplot(1, 1, 1)
    ax.set_title(name, fontsize=20)

    targets = [0, 1, 2]
    colors = ['r', 'g', 'b']
    for target, color in zip(targets, colors):
        idx = labels == target
        group = _pca[idx]
        ax.scatter(group[:, 0], group[:, 1], c=color, s=50)
        hull = ConvexHull(group)
        for simplex in hull.simplices:
            ax.plot(group[simplex, 0], group[simplex, 1], 'k-')
    ax.grid()
    plt.show()


complete_labels = np.array(find_perm(3, Y, cluster_cmp.labels_))
plot_PCA_2D(X_reduced, Y, 'Oryginał')
plot_PCA_2D(X_reduced, complete_labels, 'Complete')

fig = plt.figure(figsize=(8, 8))
ax = fig.add_subplot(1, 1, 1)
ax.set_title("Różnice", fontsize=20)
diff = Y == complete_labels
for i, point in enumerate(X_reduced):
    if not diff[i]:
        ax.plot(point[0], point[1], 'ro')
    else:
        ax.plot(point[0], point[1], 'go')
ax.grid()
plt.show()
