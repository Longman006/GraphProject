import networkx as nx
from sys import argv

def print_usage():
    print("{0} <number_of_vertices> <degree_of_each_vertice> <output_file>".format(argv[0]))


if len(argv)<4:
    print_usage()
    exit()

n, k, out_name = int(argv[1]), int(argv[2]), argv[3]

a = nx.random_regular_graph(k, n)
f = open(out_name, "w")

f.write("{0} {1}\n".format(n, k))

for numer, skladowe in a.adjacency_iter():
	c = str(numer)+" "
	for x in skladowe.items():
		c += str(x[0])+" "
	f.write(c+"\n")
f.close()
