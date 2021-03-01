struct rawEdge {
  int u, v, w;
  rawEdge() {}
  rawEdge(int u, int v, int w) : u(u), v(v), w(w) {}
  inline bool operator<(const rawEdge& r) const {
    return w < r.w;
  }
};
