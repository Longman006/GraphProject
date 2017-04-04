import networkx as nx
import sys

n, k = int(sys.argv[1]), int(sys.argv[2])

a = nx.random_regular_graph(k, n)

for numer, skladowe in a.adjacency_iter():
	c = ""
	for x in skladowe.items():
		c += str(x[0])+" "
	sys.stdout.write(c+"\n")
