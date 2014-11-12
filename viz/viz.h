#ifndef VIZ_H
#define VIZ_H

namespace apf {
  class Mesh;
  class MeshEntity;
};

struct milo;

class Visualization {
public:
  void new_viz(int num_parts);
  void breakpoint();
  bool drawPoint(apf::Mesh* m, apf::MeshEntity* ent);
  bool drawLine(apf::Mesh* m, apf::MeshEntity* ent);
  bool drawTriangle(apf::Mesh* m, apf::MeshEntity* ent);
  bool watchEntity(apf::Mesh* m, apf::MeshEntity* ent);
  bool watchDimension(apf::Mesh* m, int d);
  bool watchMesh(apf::Mesh* m);
  void end_viz();
private:
  milo* mil;
  int max_parts;
  int color_mode;

  bool getPoint(apf::Mesh* m, apf::MeshEntity* ent, double* point);
  void getPartColor(double* color, int parts);

};

#endif