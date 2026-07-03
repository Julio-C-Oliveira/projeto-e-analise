import json
import glob
import os
import statistics

res = {"dense": {}, "sparse": {}}
for density in ["dense", "sparse"]:
    for v in [10, 100, 1000]:
        files = glob.glob(f"grafos/graph_V{v}_{density}_S*.json")
        k_times = []
        p_times = []
        for f in files:
            with open(f) as fd:
                data = json.load(fd)
                k_times.append(data["kruskal"]["execution_time_ms"])
                p_times.append(data["prim"]["execution_time_ms"])
        if k_times:
            res[density][v] = {"kruskal": statistics.mean(k_times), "prim": statistics.mean(p_times)}

print("Dense:")
for v, times in sorted(res["dense"].items()):
    print(f"V={v}: Kruskal={times['kruskal']:.4f} ms, Prim={times['prim']:.4f} ms")
print("Sparse:")
for v, times in sorted(res["sparse"].items()):
    print(f"V={v}: Kruskal={times['kruskal']:.4f} ms, Prim={times['prim']:.4f} ms")
